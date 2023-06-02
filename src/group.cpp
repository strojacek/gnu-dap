/* Grouping Routines for observations */

#include <cstdio>
#include <cmath>
#include "externs.h"
#include "dap_make.h"
#include "typecompare.h"

extern dataobs dap_obs[];
extern FILE *dap_lst;
extern FILE *dap_log;
extern FILE *dap_err;
extern char *dap_dapname;

extern char dap_sttnm[NSTATS][STATLEN + 1];

static int (*cmp)(const void *, const void *) = &dblcmp;
static int (*dcmp)(const void *, const void *) = &ddblcmp;


/* codes for type of grouping */
#define grpnumber (-1)
#define grpfraction (-2)
#define grppercent (-3)

/* bits for coding descending or not, starting at 0 or not */
#define grpdesc 0x1
#define grp0 0x2

/* construct vector of variable ids (varv) and grouping types:
 * if simply getting count, fraction, or percent, classtype constructed from
 * oring of grpdesc and grp0, otherwise
 * classtype > 0 for number of equal count groups, < 0 for equal width groups.
 * return number of variables found, but if simply getting count, fraction, or
 * percent, negate with this info tucked into low order bits.
 */
static int groupparse(char *varspec, int varv[], int classtype[])
{
	int s;
	int i;
	int v;
	char *varname; /* variable name or other token from varspec */
	int n;
	int nvar;
	int number; /* are we going to simply get observation number, fraction, or percent,
				 * (indicated by number == 0) or do grouping (indicated by number == 1?)?
				 * this is specified by first character in varspec.
				 */

	if (!varspec)
		return 0;
	varname = dap_malloc(dap_namelen + 1, (char*) "");
	for (s = 0; varspec[s] == ' '; s++) /* skip leading blanks */
		;
	for (nvar = 0, number = 0; varspec[s];)
	{
		classtype[nvar] = 0; /* initialize to innocent */
		for (i = 0; varspec[s + i] && varspec[s + i] != ' '; i++)
		{ /* copy variable name or leading character in varspec only */
			if (i < dap_namelen)
				varname[i] = varspec[s + i];
			else
			{
				varname[i] = '\0';
				fprintf(dap_err, "(groupparse) variable name too long: %s\n",
						varname);
				exit(1);
			}
		}
		varname[i] = '\0';
		s += i; /* get past variable name or leading character */
		/* if it's a variable, get its id */
		if ((v = dap_varnum(varname)) >= 0)
		{							  /* ok, it's a variable */
			varv[nvar] = v;			  /* and place in vector */
			while (varspec[s] == ' ') /* skip blanks to get to grouping type or next variable */
				s++;
			if (number) /* if we got leading character in varspec to specifying grouping */
			{
				if (dap_obs[0].do_len[v] != dbl)
				{
					fprintf(dap_err,
							"(groupparse) grouping variable must be of type double: %s\n",
							varname);
					exit(1);
				}
			}
			else /* else we have to get the grouping type */
			{
				if ('0' <= varspec[s] && varspec[s] <= '9')
				{ /* first there has to be a number */
					if (dap_obs[0].do_len[v] == dbl)
					{ /* we're only going to group numbers of type double */
						for (n = 0, i = 0;
							 '0' <= varspec[s + i] && varspec[s + i] <= '9';
							 i++)
							n = 10 * n + varspec[s + i] - '0';
						if (!n || (varspec[s + i] != '#' &&
								   varspec[s + i] != '^'))
						{ /* ok, we either didn't get a number or it wasn't followed
						   * by either # (equal count groups) or ^ (equal width groups)
						   */
							fprintf(dap_err,
									"(groupparse) invalid number of groups: %s\n",
									varspec + s);
							exit(1);
						}
						switch (varspec[s + i])
						{
						case '^':
							classtype[nvar] = -n; /* < 0 indicates equal width */
							break;
						case '#':
							classtype[nvar] = n; /* > 0 indicates equal count */
							break;
						default:
							fprintf(dap_err,
									"(groupparse) invalid class type: %s\n",
									varspec + s + i);
							exit(1);
						}
						s += i + 1;
						while (varspec[s] == ' ') /* on to next variable */
							s++;
						if (n > dap_maxbars)
						{
							fprintf(dap_err,
									"(groupparse) too many classes: %d\n", n);
							exit(1);
						}
					}
					else /* guess it wasn't a double... */
					{
						fprintf(dap_err,
								"(groupparse) grouping variable must be of type double: %s\n",
								varname);
						exit(1);
					}
				}
				else /* guess there wasn't a number... */
				{
					fprintf(dap_err,
							"(groupparse) missing number of groups for %s\n",
							varname);
					exit(1);
				}
			}
			nvar++;
		}
		else if (number < 0)
		{						   /* then varname was really a variable name, because we already found
									* a #, /, or % at the beginning of varspec
									*/
			if (varname[0] == '-') /* descending */
				classtype[0] |= grpdesc;
			if (varname[1] == '0') /* lowest group is numbered 0 */
				classtype[0] |= grp0;
		}
		else if (!nvar)
		{ /* at the beginning of varspec: want count, fraction, or percent? */
			if (!strcmp(varname, "#"))
				number = grpnumber;
			else if (!strcmp(varname, "/"))
				number = grpfraction;
			else if (!strcmp(varname, "%"))
				number = grppercent;
			classtype[0] = 0;
			nvar++;
		}
		else /* ok, look: we're not at the beginning and it's not a variable. what gives? */
		{
			fprintf(dap_err, "(groupparse) unknown variable: %s\n", varname);
			exit(1);
		}
		while (varspec[s] == ' ') /* on to next */
			s++;
	}
	dap_free(varname, (char*) "");
	if (number < 0) /* if were just finding count, fraction, or percent */
		return -4 * nvar + number;
	return nvar;
}

/* get the grouping points for each variable */
static void getpoints(double **numval, int nonum,
					  int *ctype, int nobs, double **point)
{
	int v;
	double width;
	int p;
	int index;
	double excess;

	for (v = 0; v < nonum; v++)
	{
		qsort((void *)numval[v], (size_t)nobs, /* sort values for each variable separately */
			  (size_t)sizeof(double), cmp);
		if (ctype[v] < 0)
		{
			width = (numval[v][nobs - 1] - numval[v][0]) /
					((double)-ctype[v]);
			for (p = 0; p < -ctype[v]; p++)
				point[v][p] = numval[v][0] +
							  ((double)p) * width;
			point[v][p] = numval[v][nobs - 1];
		}
		else if (ctype[v] > 0)
		{
			for (p = 0; p < ctype[v]; p++)
			{
				index = (int)floor(((double)(p * nobs)) /
								   ((double)ctype[v]));
				excess = ((double)(p * nobs)) / ((double)ctype[v]) -
						 (double)index;
				if (excess > 0.0 && index < nobs - 1)
					point[v][p] = 0.5 *
								  (numval[v][index] + numval[v][index + 1]);
				else
					point[v][p] =
						numval[v][(int)rint(((double)(p * nobs)) /
											((double)ctype[v]))];
			}
			point[v][p] = numval[v][nobs - 1];
		}
	}
}

void group(char *fname, char *varspec, char *marks)
{
	char *outname;
	int *markv; /* vector of ids of partitioning variables */
	int nmark;	/* and number of those */
	int *varv;	/* vector of ids of variables */
	int *ctype; /* grouping type; see groupparse above for details */
	double *nummem;
	double **numval;
	int nvar;
	int number;
	int v;
	char *grpname; /* to hold name of group variables */
	int *grpv;	   /* vector of ids of grouping variables */
	int nobs;
	int nnan;
	int allgood; /* all vars selected are finite */
	double *ptmem;
	double **point;
	double dnobs;
	double count;
	double countinc;
	int p;
	int more; /* to see if another dataset line was read */

	if (!fname)
	{
		fputs("(group) no dataset name given.\n", dap_err);
		exit(1);
	}
	outname = dap_malloc(strlen(fname) + 5, (char*) "");
	dap_suffix(outname, fname, (char*) ".grp");
	grpname = dap_malloc(dap_namelen + 3, (char*) ""); /* +3 for two '_' and null */
	markv = (int *)dap_malloc(sizeof(int) * dap_maxvar, (char*) "");
	varv = (int *)dap_malloc(sizeof(int) * dap_maxvar, (char*) "");
	ctype = (int *)dap_malloc(sizeof(int) * dap_maxvar, (char*) "");
	inset(fname);
	nmark = dap_list(marks, markv, dap_maxvar);
	/* construct vector of variable ids (varv) and grouping types (ctype) */
	nvar = groupparse(varspec, varv, ctype);
	if (nvar < 0) /* means we're simply getting count, fraction, or percent */
	{
		number = -((-nvar) % 4);	 /* recover codes for descending or not, start from 0 or not */
		nvar = -(nvar - number) / 4; /* and get true number of variables */
	}
	else
		number = 0; /* indicates true grouping */
	grpv = (int *)dap_malloc(sizeof(int) * (number ? 1 : nvar), (char*) "");
	if (!number) /* true grouping requires: */
	{
		strcpy(grpname, "_"); /* variable names for group variables */
		for (v = 0; v < nvar; v++)
		{
			strcpy(grpname + 1, dap_obs[0].do_nam[varv[v]]);
			grpname[dap_namelen] = '\0';
			strcat(grpname, " -1");
			grpv[v] = dap_vd(grpname, 0);
		}
	}
	else /* counting, etc., simply requires one new variable */
	{
		grpv[0] = dap_vd((char*) "_n_ -1", 0);
		varv[0] = grpv[0];
	}
	outset(outname, (char*) "");
	nummem = null;
	numval = null;
	if (!number) /* if true grouping, need some memory to sort and manipulate the numbers */
	{
		nummem = (double *)dap_malloc(sizeof(double) * nvar * dap_maxval, (char*) "dap_maxval");
		numval = (double **)dap_malloc(nvar * dap_maxval * sizeof(double *), (char*) "dap_maxval");
		ptmem = (double *)dap_malloc(sizeof(double) * nvar * (dap_maxbars + 1), (char*) "dap_maxbars");
		point = (double **)dap_malloc(sizeof(double *) * nvar, (char*) "");
		for (v = 0; v < nvar; v++) /* set up pointers for array referencing */
		{
			numval[v] = nummem + v * dap_maxval;
			point[v] = ptmem + v * (dap_maxbars + 1);
		}
	}
	for (dap_mark(), nobs = 0, nnan = 0, more = 1; more;)
	{
		more = step();
		if (dap_newpart(markv, nmark)) /* reached a new part of dataset, time to do stuff */
		{
			if (!number)									 /* if true grouping, need... */
				getpoints(numval, nvar, ctype, nobs, point); /* to get grouping points */
			dnobs = (double)nobs;
			dap_rewind(); /* have to pass through this part again */
			count = 1.0;
			countinc = 1.0;
			if (nnan > 0)
				fprintf(dap_log, "(group) %d nans\n", nnan);
			if (number)
			{
				if (ctype[0] & grp0)
					count = 0.0;
				if (ctype[0] & grpdesc)
				{
					countinc = -1.0;
					count = dnobs - 1.0 + count;
				}
			}
			for (; step() && !dap_newpart(markv, nmark);)
			{
				if (number)
				{
					for (v = 1, allgood = 1; v < nvar; v++)
					{
						if (!isfinite(dap_obs[0].do_dbl[varv[v]]))
						{
							allgood = 0;
							break;
						}
					}
					if (allgood)
					{
						switch (number)
						{
						case grpnumber:
							dap_obs[0].do_dbl[grpv[0]] = count;
							break;
						case grpfraction:
							dap_obs[0].do_dbl[grpv[0]] = count / dnobs;
							break;
						case grppercent:
							dap_obs[0].do_dbl[grpv[0]] = 100.0 * count / dnobs;
							break;
						}
						count += countinc;
					}
					else
						dap_obs[0].do_dbl[grpv[0]] = 0.0 / 0.0;
				}
				else
				{
					for (v = 0, allgood = 1; v < nvar; v++)
					{
						if (!isfinite(dap_obs[0].do_dbl[varv[v]]))
						{
							allgood = 0;
							break;
						}
					}
					if (allgood)
					{
						for (v = 0; v < nvar; v++)
						{
							for (p = 1;
								 dap_obs[0].do_dbl[varv[v]] >
								 point[v][p];
								 p++)
								;
							dap_obs[0].do_dbl[grpv[v]] = (double)p;
						}
					}
					else
						for (v = 0; v < nvar; v++)
							dap_obs[0].do_dbl[grpv[v]] = 0.0 / 0.0;
				}
				output();
				dap_mark();
			}
			nobs = 0;
			nnan = 0;
		}
		if (number)
		{
			for (v = 1, allgood = 1; v < nvar; v++)
			{
				if (!isfinite(dap_obs[0].do_dbl[varv[v]]))
				{
					allgood = 0;
					break;
				}
			}
			if (allgood)
				nobs++;
			else
				nnan++;
		}
		else
		{
			if (nobs < dap_maxval)
			{
				for (v = 0, allgood = 1; v < nvar; v++)
				{
					if (!isfinite(dap_obs[0].do_dbl[varv[v]]))
					{
						allgood = 0;
						break;
					}
					numval[v][nobs] = dap_obs[0].do_dbl[varv[v]];
				}
				if (allgood)
					nobs++;
				else
					nnan++;
			}
			else
			{
				fputs("(group) too many data.\n", dap_err);
				exit(1);
			}
		}
	}
	if (!number)
	{
		dap_free(nummem, (char*) "");
		dap_free(numval, (char*) "");
		dap_free(ptmem, (char*) "");
		dap_free(point, (char*) "");
	}
	dap_free(outname, (char*) "");
	dap_free(grpname, (char*) "");
	dap_free(grpv, (char*) "");
	dap_free(markv, (char*) "");
	dap_free(varv, (char*) "");
	dap_free(ctype, (char*) "");
}



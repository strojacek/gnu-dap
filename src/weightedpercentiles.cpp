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

/* Convert double percentile point to integer index, excess.  */
static void pctpttest(double wtpt, double cumwt, double nextcum,
					  int *pctpt, int n, int *excess)
{
	if (cumwt <= wtpt && wtpt < nextcum)
	{
		*pctpt = n;
		if (wtpt > cumwt)
			*excess = 1;
	}
}

/* Weighted percentiles */
static void pctile2(double ***val, int nobs,
					int nvar, int *varv, int *wtvar, int *stats)
{
	int v;
	int *pctptmem;
	int **pctpt;
	int *excessmem;
	int **excess;
	int pn; /* number of user-specified percentiles */
	int pi; /* index to user-specified percentiles */
	double pct;
	static double sumwt;   /* total sum of weights for specified variable */
	static double cumwt;   /* cumulative sum of wts for specified var */
	static double nextcum; /* cumwt + next wt to be added in */
	static double wtpt;	   /* fraction of sumwt for specified percentile */
	double upct[MAXPCTPT]; /* percent values for user-specified percentiles */
	int n;
	int ptindex;
	int s;
	double q1, q3;
	int typen;

	dap_swap();
	if ((typen = dap_varnum((char*) "_type_")) < 0)
	{
		fprintf(dap_err, "(pctile2) missing _type_ variable\n");
		exit(1);
	}
	pctptmem = (int *)dap_malloc(sizeof(int) * nvar * (9 + MAXPCTPT), (char*) "");
	pctpt = (int **)dap_malloc(sizeof(int *) * nvar, (char*) "");
	excessmem = (int *)dap_malloc(sizeof(int) * nvar * (9 + MAXPCTPT), (char*) "");
	excess = (int **)dap_malloc(sizeof(int *) * nvar, (char*) "");
	for (pn = 0; pn < MAXPCTPT && stats[NSTATS - MAXPCTPT + pn]; pn++)
	{
		if (sscanf(dap_sttnm[NSTATS - MAXPCTPT + pn] + 1,
				   "%lf", &upct[pn]) != 1)
		{
			fprintf(dap_err, "(pctile2) invalid percentile: %s\n",
					dap_sttnm[NSTATS - MAXPCTPT + pn]);
			exit(1);
		}
	}
	for (v = 0; v < nvar; v++)
	{
		pctpt[v] = pctptmem + v * (9 + MAXPCTPT);
		excess[v] = excessmem + v * (9 + MAXPCTPT);
		qsort((void *)val[v], (size_t)nobs, (size_t)(sizeof(double *)), dcmp);
		for (n = 0, sumwt = 0.0; n < nobs; n++)
			sumwt += val[v][n][1];
		for (s = 0; s < 9 + pn; s++)
		{
			excess[v][s] = 0;
			pctpt[v][s] = nobs - 1;
		}
		for (n = 0, cumwt = 0.0; n < nobs; n++, cumwt = nextcum)
		{
			nextcum = cumwt + val[v][n][1];
			pctpttest(sumwt / 100.0, cumwt, nextcum, pctpt[v], n, excess[v]);
			pctpttest(sumwt / 20.0, cumwt, nextcum, pctpt[v] + 1, n, excess[v] + 1);
			pctpttest(sumwt / 10.0, cumwt, nextcum, pctpt[v] + 2, n, excess[v] + 2);
			pctpttest(sumwt / 4.0, cumwt, nextcum, pctpt[v] + 3, n, excess[v] + 3);
			pctpttest(sumwt / 2.0, cumwt, nextcum, pctpt[v] + 4, n, excess[v] + 4);
			pctpttest(3.0 * sumwt / 4.0, cumwt, nextcum, pctpt[v] + 5, n, excess[v] + 5);
			pctpttest(9.0 * sumwt / 10.0, cumwt, nextcum, pctpt[v] + 6, n, excess[v] + 6);
			pctpttest(95.0 * sumwt / 100.0, cumwt, nextcum, pctpt[v] + 7, n, excess[v] + 7);
			pctpttest(99.0 * sumwt / 100.0, cumwt, nextcum, pctpt[v] + 8, n, excess[v] + 8);
			for (pi = 0; pi < pn; pi++)
			{
				pctpttest(upct[pi] * sumwt / 100.0,
						  cumwt, nextcum, pctpt[v] + 9 + pi,
						  n, excess[v] + 9 + pi);
			}
		}
	}
	for (s = 0; s < 9 + pn; s++)
	{
		if (stats[P1 + s])
		{
			for (v = 0; v < nvar; v++)
			{
				ptindex = pctpt[v][s] - 1;
				if (ptindex < 0)
					ptindex = 0;
				if (excess[v][s])
					dap_obs[0].do_dbl[varv[v]] = val[v][pctpt[v][s]][0];
				else
					dap_obs[0].do_dbl[varv[v]] =
						0.5 * (val[v][pctpt[v][s]][0] + val[v][ptindex][0]);
			}
			strcpy(dap_obs[0].do_str[typen], dap_sttnm[P1 + s]);
			output();
		}
	}
	if (stats[N])
	{
		for (v = 0; v < nvar; v++)
			dap_obs[0].do_dbl[varv[v]] = (double)nobs;
		strcpy(dap_obs[0].do_str[typen], "N");
		output();
	}
	if (stats[MIN])
	{
		for (v = 0; v < nvar; v++)
			dap_obs[0].do_dbl[varv[v]] = val[v][0][0];
		strcpy(dap_obs[0].do_str[typen], "MIN");
		output();
	}
	if (stats[MAX])
	{
		for (v = 0; v < nvar; v++)
			dap_obs[0].do_dbl[varv[v]] = val[v][nobs - 1][0];
		strcpy(dap_obs[0].do_str[typen], "MAX");
		output();
	}
	if (stats[QRANGE])
	{
		for (v = 0; v < nvar; v++)
		{
			ptindex = pctpt[v][3] - 1;
			if (ptindex < 0)
				ptindex = 0;
			if (excess[v][3])
				q1 = val[v][pctpt[v][3]][0];
			else
				q1 = 0.5 * (val[v][pctpt[v][3]][0] + val[v][ptindex][0]);
			ptindex = pctpt[v][5] - 1;
			if (ptindex < 0)
				ptindex = 0;
			if (excess[v][5])
				q3 = val[v][pctpt[v][5]][0];
			else
				q3 = 0.5 * (val[v][pctpt[v][5]][0] + val[v][ptindex][0]);
			dap_obs[0].do_dbl[varv[v]] = q3 - q1;
		}
		strcpy(dap_obs[0].do_str[typen], "QRANGE");
		output();
	}
	dap_swap();
	dap_free(pctptmem, (char*) "");
	dap_free(pctpt, (char*) "");
	dap_free(excessmem, (char*) "");
	dap_free(excess, (char*) "");
}

static void pctile1(double ***val, int nobs, int nvar, int *varv, int *stats)
{
	int v;
	double dnobs;
	static int pctpt[9 + MAXPCTPT];
	int pn;
	double pct;
	static int excess[9 + MAXPCTPT];
	int ptindex;
	int s;
	double q1, q3;
	int typen;

	dap_swap();
	if ((typen = dap_varnum((char*) "_type_")) < 0)
	{
		fprintf(dap_err, "(pctile1) missing _type_ variable\n");
		exit(1);
	}
	dnobs = (double)nobs;
	pctpt[0] = (int)floor(dnobs / 100.0);
	excess[0] = ((dnobs / 100.0) > floor(dnobs / 100.0));
	pctpt[1] = (int)floor(dnobs / 20.0);
	excess[1] = ((dnobs / 20.0) > floor(dnobs / 20.0));
	pctpt[2] = (int)floor(dnobs / 10.0);
	excess[2] = ((dnobs / 10.0) > floor(dnobs / 10.0));
	pctpt[3] = (int)floor(dnobs / 4.0);
	excess[3] = ((dnobs / 4.0) > floor(dnobs / 4.0));
	pctpt[4] = (int)floor(dnobs / 2.0);
	excess[4] = ((dnobs / 2.0) > floor(dnobs / 2.0));
	pctpt[5] = (int)floor(3.0 * dnobs / 4.0);
	excess[5] = ((3.0 * dnobs / 4.0) > floor(3.0 * dnobs / 4.0));
	pctpt[6] = (int)floor(9.0 * dnobs / 10.0);
	excess[6] = ((9.0 * dnobs / 10.0) > floor(9.0 * dnobs / 10.0));
	pctpt[7] = (int)floor(95.0 * dnobs / 100.0);
	excess[7] = ((95.0 * dnobs / 100.0) > floor(95.0 * dnobs / 100.0));
	pctpt[8] = (int)floor(99.0 * dnobs / 100.0);
	excess[8] = ((99.0 * dnobs / 100.0) > floor(99.0 * dnobs / 100.0));
	for (pn = 0; pn < MAXPCTPT && stats[NSTATS - MAXPCTPT + pn]; pn++)
	{
		sscanf(dap_sttnm[NSTATS - MAXPCTPT + pn] + 1, "%lf", &pct);
		pctpt[9 + pn] = (int)floor(pct * dnobs / 100.0);
		excess[9 + pn] = ((pct * dnobs / 100.0) > floor(pct * dnobs / 100.0));
	}
	for (v = 0; v < nvar; v++)
		qsort((void *)val[v], (size_t)nobs, (size_t)sizeof(double *), dcmp);
	for (s = 0; s < 9 + pn; s++)
	{
		if (stats[P1 + s])
		{
			for (v = 0; v < nvar; v++)
			{
				ptindex = pctpt[s] - 1;
				if (ptindex < 0)
					ptindex = 0;
				if (excess[s])
					dap_obs[0].do_dbl[varv[v]] = val[v][pctpt[s]][0];
				else
					dap_obs[0].do_dbl[varv[v]] =
						0.5 * (val[v][pctpt[s]][0] + val[v][ptindex][0]);
			}
			strcpy(dap_obs[0].do_str[typen], dap_sttnm[P1 + s]);
			output();
		}
	}
	if (stats[N])
	{
		for (v = 0; v < nvar; v++)
			dap_obs[0].do_dbl[varv[v]] = dnobs;
		strcpy(dap_obs[0].do_str[typen], "N");
		output();
	}
	if (stats[MIN])
	{
		for (v = 0; v < nvar; v++)
			dap_obs[0].do_dbl[varv[v]] = val[v][0][0];
		strcpy(dap_obs[0].do_str[typen], "MIN");
		output();
	}
	if (stats[MAX])
	{
		for (v = 0; v < nvar; v++)
			dap_obs[0].do_dbl[varv[v]] = val[v][nobs - 1][0];
		strcpy(dap_obs[0].do_str[typen], "MAX");
		output();
	}
	if (stats[RANGE])
	{
		for (v = 0; v < nvar; v++)
			dap_obs[0].do_dbl[varv[v]] = val[v][nobs - 1][0] - val[v][0][0];
		strcpy(dap_obs[0].do_str[typen], "RANGE");
		output();
	}
	if (stats[QRANGE])
	{
		for (v = 0; v < nvar; v++)
		{
			ptindex = pctpt[3] - 1;
			if (ptindex < 0)
				ptindex = 0;
			if (excess[3])
				q1 = val[v][pctpt[3]][0];
			else
				q1 = 0.5 * (val[v][pctpt[3]][0] + val[v][ptindex][0]);
			ptindex = pctpt[5] - 1;
			if (ptindex < 0)
				ptindex = 0;
			if (excess[5])
				q3 = val[v][pctpt[5]][0];
			else
				q3 = 0.5 * (val[v][pctpt[5]][0] + val[v][ptindex][0]);
			dap_obs[0].do_dbl[varv[v]] = q3 - q1;
		}
		strcpy(dap_obs[0].do_str[typen], "QRANGE");
		output();
	}
	dap_swap();
}

void pctiles(char *fname, char *varlist, char *statlist, char *marks)
{
	char *outname;
	int stats[NSTATS];
	int *varv;
	int *markv;
	int nvar;
	int nmark;
	int nobs;
	char *outlist;
	int *wtvar;
	int v;
	double *valmem;
	double **valpair;
	double ***val;
	int weighted;
	int more;

	if (!fname)
	{
		fputs("(pctiles) No dataset name given.\n", dap_err);
		exit(1);
	}
	outname = dap_malloc(strlen(fname) + 5, (char*) "");
	dap_suffix(outname, fname, (char*) ".pct");
	varv = (int *)dap_malloc(sizeof(int) * dap_maxvar, (char*) "");
	markv = (int *)dap_malloc(sizeof(int) * dap_maxvar, (char*) "");
	wtvar = (int *)dap_malloc(sizeof(int) * dap_maxvar, (char*) "");
	/* outlist = dap_malloc(strlen(varlist) + strlen(marks) + 2, ""); ?? */
	outlist = dap_malloc(dap_listlen + 1, (char*) "");
	inset(fname);
	dap_stats(statlist, stats);
	nvar = dap_mnsparse(varlist, outlist, varv, wtvar, stats);
	if (marks && marks[0])
	{
		strcat(outlist, " ");
		strcat(outlist, marks);
	}
	outset(outname, outlist);
	nmark = dap_list(marks, markv, dap_maxvar);
	valmem = (double *)dap_malloc(sizeof(double) * nvar * 2 * dap_maxval, (char*) "");
	valpair = (double **)dap_malloc(sizeof(double *) * nvar * dap_maxval, (char*) "");
	val = (double ***)dap_malloc(sizeof(double *) * nvar, (char*) "");
	for (v = 0, weighted = 0; v < nvar; v++)
	{
		if (wtvar[v] >= 0)
			weighted = 1;
	}
	for (nobs = 0, more = 1; more; nobs++)
	{
		more = step();
		if (dap_newpart(markv, nmark))
		{
			if (weighted)
				pctile2(val, nobs, nvar, varv, wtvar, stats);
			else
				pctile1(val, nobs, nvar, varv, stats);
			nobs = 0;
		}
		if (more)
		{
			if (nobs < dap_maxval)
			{
				for (v = 0; v < nvar; v++)
				{
					valpair[dap_maxval * v + nobs] =
						valmem + 2 * (dap_maxval * v + nobs);
					val[v] = valpair + v * dap_maxval;
					val[v][nobs][0] = dap_obs[0].do_dbl[varv[v]];
					if (wtvar[v] >= 0)
						val[v][nobs][1] = dap_obs[0].do_dbl[wtvar[v]];
					else
						val[v][nobs][1] = 1.0;
					if (!isfinite(val[v][nobs][0]) || !isfinite(val[v][nobs][1]))
					{
						fprintf(dap_err,
								"(pctiles) NaN value %d for %s\n",
								nobs, dap_obs[0].do_nam[varv[v]]);
						exit(1);
					}
				}
			}
			else
			{
				fputs("(pctiles) Too many data.\n", dap_err);
				exit(1);
			}
		}
	}
	dap_free(outname, (char*) "");
	dap_free(varv, (char*) "");
	dap_free(markv, (char*) "");
	dap_free(wtvar, (char*) "");
	dap_free(outlist, (char*) "");
	dap_free(valmem, (char*) "");
	dap_free(valpair, (char*) "");
	dap_free(val, (char*) "");
}



/* Correllations for Gnu Dap */

#include <cstdio>
#include <cmath>
#include "externs.h"
#include "dap_make.h"
#include "typecompare.h"

static void corr1(int *varv, int nvar, double **cormat, double ss[], int nobs)
{
	int varn[3];
	int typen;
	double nf;
	int v, w;
	double r;

	if (nobs < 2)
		return;
	dap_swap();
	nf = sqrt((double)(nobs - 2));
	varn[0] = dap_varnum((char*) "_var1_");
	varn[1] = dap_varnum((char*) "_var2_");
	varn[2] = dap_varnum((char*) "_corr_");
	typen = dap_varnum((char*) "_type_");
	for (v = 0; v < nvar; v++)
		for (w = 0; w < v; w++)
			cormat[v][w] = cormat[w][v];
	strcpy(dap_obs[0].do_str[typen], "N");
	for (v = 0; v < nvar; v++)
	{
		strcpy(dap_obs[0].do_str[varn[0]], dap_obs[0].do_nam[varv[v]]);
		for (w = 0; w < nvar; w++)
		{
			strcpy(dap_obs[0].do_str[varn[1]],
				   dap_obs[0].do_nam[varv[w]]);
			dap_obs[0].do_dbl[varn[2]] = (double)nobs;
			output();
		}
	}
	strcpy(dap_obs[0].do_str[typen], "CORR");
	for (v = 0; v < nvar; v++)
	{
		strcpy(dap_obs[0].do_str[varn[0]], dap_obs[0].do_nam[varv[v]]);
		for (w = 0; w < nvar; w++)
		{
			strcpy(dap_obs[0].do_str[varn[1]],
				   dap_obs[0].do_nam[varv[w]]);
			if (w == v)
				cormat[v][w] = 1.0;
			else
				cormat[v][w] /= sqrt(ss[v] * ss[w]);
			dap_obs[0].do_dbl[varn[2]] = cormat[v][w];
			output();
		}
	}
	strcpy(dap_obs[0].do_str[typen], "PCORR");
	for (v = 0; v < nvar; v++)
	{
		strcpy(dap_obs[0].do_str[varn[0]], dap_obs[0].do_nam[varv[v]]);
		for (w = 0; w < nvar; w++)
		{
			strcpy(dap_obs[0].do_str[varn[1]],
				   dap_obs[0].do_nam[varv[w]]);
			r = fabs(cormat[v][w]);
			if (r == 1.0)
				dap_obs[0].do_dbl[varn[2]] = 0.0;
			else
				dap_obs[0].do_dbl[varn[2]] =
					2.0 * probt(nf * r / sqrt(1.0 - r * r),
								nobs - 2);
			output();
		}
	}
	dap_swap();
}

void corr(char *fname, char *varlist, char *marks)
{
	char *outname;
	char varstr[11];
	char *outlist;
	int *markv;
	int nmark;
	int *varv;
	int nvar;
	int nobs;
	double *cormem;
	double **cormat;
	int v, w;
	double *sum;
	double *ss;
	double vtmp;
	double tmp;
	double dn;
	int more;

	if (!fname)
	{
		fputs("(corr) No dataset name given.\n", dap_err);
		exit(1);
	}
	markv = (int *)dap_malloc(sizeof(int) * dap_maxvar, (char*) "");
	varv = (int *)dap_malloc(sizeof(int) * dap_maxvar, (char*) "");
	outname = dap_malloc(strlen(fname) + 5, (char*) "");
	dap_suffix(outname, fname, (char*) ".cor");
	outlist = dap_malloc(strlen(marks) + 22, (char*) "");
	inset(fname);
	nvar = dap_list(varlist, varv, dap_maxvar);
	cormem = (double *)dap_malloc(sizeof(double) * nvar * nvar, (char*) "");
	cormat = (double **)dap_malloc(sizeof(double *) * nvar, (char*) "");
	for (v = 0; v < nvar; v++)
		cormat[v] = cormem + v * nvar;
	sum = (double *)dap_malloc(sizeof(double) * nvar, (char*) "");
	ss = (double *)dap_malloc(sizeof(double) * nvar, (char*) "");
	strcpy(outlist, marks);
	for (v = 0; v < nvar; v++)
	{
		if (dap_obs[0].do_len[varv[v]] >= 0)
		{
			fprintf(dap_err, "(corr) Variable not of type dap_double: %s\n",
					dap_obs[0].do_nam[varv[v]]);
			exit(1);
		}
	}
	sprintf(varstr, "_var1_ %d", dap_namelen);
	dap_vd(varstr, 0);
	sprintf(varstr, "_var2_ %d", dap_namelen);
	dap_vd(varstr, 0);
	sprintf(varstr, "_corr_ %d", DBL);
	dap_vd(varstr, 0);
	strcat(outlist, " _var1_ _var2_ _corr_");
	outset(outname, outlist);
	nmark = dap_list(marks, markv, dap_maxvar);
	for (v = 0; v < nvar; v++)
	{
		if (dap_obs[0].do_len[varv[v]] != DBL)
		{
			fprintf(dap_err, "(corr) variables must be of type double: %s\n",
					dap_obs[0].do_nam[varv[v]]);
			exit(1);
		}
		for (w = v + 1; w < nvar; w++)
			cormat[v][w] = 0.0;
		sum[v] = 0.0;
		ss[v] = 0.0;
	}
	for (nobs = 0, more = 1; more; nobs++)
	{
		more = step();
		if (dap_newpart(markv, nmark))
		{
			corr1(varv, nvar, cormat, ss, nobs);
			for (v = 0; v < nvar; v++)
			{
				for (w = v + 1; w < nvar; w++)
					cormat[v][w] = 0.0;
				sum[v] = 0.0;
				ss[v] = 0.0;
			}
			nobs = 0;
		}
		if (more)
		{
			dn = (double)nobs;
			for (v = 0; v < nvar; v++)
			{
				vtmp = dap_obs[0].do_dbl[varv[v]];
				if (!isfinite(vtmp))
				{
					fprintf(dap_err,
							"(corr) NaN value %d for %s\n",
							nobs, dap_obs[0].do_nam[varv[v]]);
					exit(1);
				}
				if (nobs)
				{
					tmp = sum[v] - dn * vtmp;
					for (w = v + 1; w < nvar; w++)
					{
						cormat[v][w] += tmp * (sum[w] - dn * dap_obs[0].do_dbl[varv[w]]) /
										(dn * (dn + 1.0));
					}
					ss[v] += tmp * tmp / (dn * (dn + 1.0));
				}
				sum[v] += vtmp;
			}
		}
	}
	dap_free(markv, (char*) "");
	dap_free(varv, (char*) "");
	dap_free(outname, (char*) "");
	dap_free(outlist, (char*) "");
	dap_free(cormem, (char*) "");
	dap_free(cormat, (char*) "");
	dap_free(sum, (char*) "");
	dap_free(ss, (char*) "");
}



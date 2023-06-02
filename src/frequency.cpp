/* Frequency Routines for Dap */

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


#define NFREQSTAT 13
#define FREQCNT 0
#define FREQPCT 1
#define FREQFRA 2
#define FREQEXP 3
#define FREQCHISQ 4
#define FREQODDRAT 5
#define FREQORD 6
#define FREQFISHER 7
#define FREQCMH 8
#define FREQROW 9
#define FREQCOL 10
#define FREQPAIR 11
#define FREQNOM 12

static void freq1(int *varv, int nvar, double count, double sumcount, int *statv,
				  int typen, int celln)
{
	dap_swap();
	if (statv[FREQCNT])
	{
		strcpy(dap_obs[0].do_str[typen], "COUNT");
		dap_obs[0].do_dbl[celln] = count;
		output();
	}
	if (statv[FREQPCT])
	{
		strcpy(dap_obs[0].do_str[typen], "PERCENT");
		dap_obs[0].do_dbl[celln] = 100.0 * count / sumcount;
		output();
	}
	if (statv[FREQFRA])
	{
		strcpy(dap_obs[0].do_str[typen], "FRACTION");
		dap_obs[0].do_dbl[celln] = count / sumcount;
		output();
	}
	dap_swap();
}

static void statparse(char *stats, int *statv)
{
	int s;
	int i;
	char *stat;

	stat = dap_malloc(dap_namelen + 1, (char*) "");
	for (s = 0; s < NFREQSTAT; s++)
		statv[s] = 0;
	for (s = 0; stats[s] == ' '; s++)
		;
	while (stats[s])
	{
		for (i = 0; stats[s + i] && stats[s + i] != ' '; i++)
		{
			if (i < dap_namelen)
				stat[i] = stats[s + i];
			else
			{
				stat[i] = '\0';
				fprintf(dap_err, "(statparse) Statistic name too long: %s\n", stat);
				exit(1);
			}
		}
		stat[i] = '\0';
		s += i;
		if (!strcmp(stat, "COUNT"))
			statv[FREQCNT] = 1;
		else if (!strcmp(stat, "PERCENT"))
			statv[FREQPCT] = 1;
		else if (!strcmp(stat, "ROWPERC"))
			statv[FREQROW] = 1;
		else if (!strcmp(stat, "COLPERC"))
			statv[FREQCOL] = 1;
		else if (!strcmp(stat, "FRACTION"))
			statv[FREQFRA] = 1;
		else if (!strcmp(stat, "EXPECTED"))
			statv[FREQEXP] = 1;
		else if (!strcmp(stat, "CHISQ"))
			statv[FREQCHISQ] = 1;
		else if (!strcmp(stat, "ODDSRAT"))
			statv[FREQODDRAT] = 1;
		else if (!strcmp(stat, "ORDINAL"))
			statv[FREQORD] = 1;
		else if (!strcmp(stat, "FISHER"))
			statv[FREQFISHER] = 1;
		else if (!strcmp(stat, "CMH"))
			statv[FREQCMH] = 1;
		else if (!strcmp(stat, "PAIR"))
			statv[FREQPAIR] = 1;
		else if (!strcmp(stat, "NOMINAL"))
			statv[FREQNOM] = 1;
		else
		{
			fprintf(dap_err, "(statparse) Invalid statistic name: %s\n", stat);
			exit(1);
		}
		while (stats[s] == ' ')
			s++;
	}
	dap_free(stat, (char*) "");
}

static int findlev(int v, char **level, int *nlevels)
{
	int l;
	static char *str = NULL;
	char *s;

	if (!str)
		str = dap_malloc(21, (char*) "");
	if (dap_obs[0].do_len[v] > 0)
		s = dap_obs[0].do_str[v];
	else
	{
		s = str;
		if (dap_obs[0].do_len[v] == INT)
			sprintf(str, "%d", dap_obs[0].do_int[v]);
		else
			sprintf(str, "%g", dap_obs[0].do_dbl[v]);
	}
	for (l = 0; l < *nlevels; l++)
	{
		if (!strcmp(s, level[l]))
			return l;
	}
	if (*nlevels < dap_maxlev)
	{
		strcpy(level[l], s);
		(*nlevels)++;
		return l;
	}
	else
	{
		fprintf(dap_err, "(findlev) Too many levels at: %s\n", s);
		exit(1);
	}
}

static void tabentry(int *varv, double **tab,
					 char **level[2], int nlevels[2], double count)
{
	dap_swap();
	tab[findlev(varv[0], level[0], nlevels)][findlev(varv[1], level[1], nlevels + 1)] = count;
	dap_swap();
}

static void valcpy(int v, char *val)
{
	if (dap_obs[0].do_len[v] > 0)
		strcpy(dap_obs[0].do_str[v], val);
	else if (dap_obs[0].do_len[v] == INT)
		dap_obs[0].do_int[v] = atoi(val);
	else
		dap_obs[0].do_dbl[v] = atof(val);
}

static void freq2(double **tab, char **level[2],
				  int nlevels[2], int *statv, int *markv, int nmark, int *varv,
				  int typen, int celln)
{
	int v;
	int l;
	double *expmem;
	double **expect;
	double *rowsum;
	double *colsum;
	double sum;
	double *amem;
	double **a;
	double *dmem;
	double **d;
	double p, q;
	double tmp1, tmp2, tmp3, tmp4;
	double w;
	double t;
	double var;
	int r, c;
	double diff;
	double chisq;
	int rr, cc;
	double upleft, dnleft;
	double denom, prob, oneprob, othprob;
	double hx, hy, hxy;
	double uv;

	sum = 0.0;
	oneprob = 0.0;
	expmem = (double *)dap_malloc(sizeof(double) * dap_maxlev * dap_maxlev, (char*) "");
	expect = (double **)dap_malloc(sizeof(double *) * dap_maxlev, (char*) "");
	for (l = 0; l < dap_maxlev; l++)
		expect[l] = expmem + l * dap_maxlev;
	rowsum = (double *)dap_malloc(sizeof(double) * dap_maxlev, (char*) "");
	colsum = (double *)dap_malloc(sizeof(double) * dap_maxlev, (char*) "");
	amem = (double *)dap_malloc(sizeof(double) * dap_maxlev * dap_maxlev, (char*) "");
	dmem = (double *)dap_malloc(sizeof(double) * dap_maxlev * dap_maxlev, (char*) "");
	a = (double **)dap_malloc(sizeof(double *) * dap_maxlev, (char*) "");
	d = (double **)dap_malloc(sizeof(double *) * dap_maxlev, (char*) "");
	for (l = 0; l < dap_maxlev; l++)
	{
		a[l] = amem + l * dap_maxlev;
		d[l] = dmem + l * dap_maxlev;
	}
	dap_swap();
	if (statv[FREQCHISQ] || statv[FREQODDRAT] || statv[FREQORD] ||
		statv[FREQFISHER] || statv[FREQPAIR] || statv[FREQNOM])
	{
		dap_head(markv, nmark);
		fputs("Variable: Levels\n", dap_lst);
		fputs("----------------\n", dap_lst);
		for (v = 0; v < 2; v++)
		{
			fprintf(dap_lst, "%s:", dap_obs[0].do_nam[varv[v]]);
			for (l = 0; l < nlevels[v]; l++)
				fprintf(dap_lst, " %s", level[v][l]);
			putc('\n', dap_lst);
		}
		putc('\n', dap_lst);
	}
	if (statv[FREQEXP] || statv[FREQCHISQ] || statv[FREQORD] || statv[FREQFISHER] ||
		statv[FREQROW] || statv[FREQCOL] || statv[FREQPAIR] || statv[FREQNOM])
	{
		for (r = 0, sum = 0.0; r < nlevels[0]; r++)
		{
			rowsum[r] = 0.0;
			for (c = 0; c < nlevels[1]; c++)
				rowsum[r] += tab[r][c];
			sum += rowsum[r];
		}
		for (c = 0; c < nlevels[1]; c++)
		{
			colsum[c] = 0.0;
			for (r = 0; r < nlevels[0]; r++)
				colsum[c] += tab[r][c];
		}
		for (r = 0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
				expect[r][c] = rowsum[r] * colsum[c] / sum;
	}
	if (statv[FREQEXP])
	{
		strcpy(dap_obs[0].do_str[typen], "EXPECTED");
		for (r = 0; r < nlevels[0]; r++)
		{
			valcpy(varv[0], level[0][r]);
			for (c = 0; c < nlevels[1]; c++)
			{
				valcpy(varv[1], level[1][c]);
				dap_obs[0].do_dbl[celln] = expect[r][c];
				output();
			}
		}
	}
	if (statv[FREQROW])
	{
		strcpy(dap_obs[0].do_str[typen], "ROWPERC");
		for (r = 0; r < nlevels[0]; r++)
		{
			valcpy(varv[0], level[0][r]);
			for (c = 0; c < nlevels[1]; c++)
			{
				valcpy(varv[1], level[1][c]);
				dap_obs[0].do_dbl[celln] = 100.0 * tab[r][c] / rowsum[r];
				output();
			}
		}
	}
	if (statv[FREQCOL])
	{
		strcpy(dap_obs[0].do_str[typen], "COLPERC");
		for (r = 0; r < nlevels[0]; r++)
		{
			valcpy(varv[0], level[0][r]);
			for (c = 0; c < nlevels[1]; c++)
			{
				valcpy(varv[1], level[1][c]);
				dap_obs[0].do_dbl[celln] = 100.0 * tab[r][c] / colsum[c];
				output();
			}
		}
	}
	if (statv[FREQCHISQ])
	{
		for (r = 0, chisq = 0.0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				diff = tab[r][c] - expect[r][c];
				chisq += diff * diff / expect[r][c];
			}
		fprintf(dap_lst, "Chisq0[%d] = %g, Prob[Chisq > Chisq0] = %.5f\n",
				(nlevels[0] - 1) * (nlevels[1] - 1), chisq,
				ceil(100000.0 *
					 probchisq(chisq, (nlevels[0] - 1) * (nlevels[1] - 1))) /
					100000.0);
	}
	if (statv[FREQODDRAT])
	{
		if (nlevels[0] == 2 && nlevels[1] == 2)
		{
			tmp1 = (tab[0][0] + 0.5) * (tab[1][1] + 0.5) /
				   ((tab[0][1] + 0.5) * (tab[1][0] + 0.5));
			fprintf(dap_lst,
					"Odds ratio = %g\nlog(Odds ratio) = %g, ASE = %g\n",
					tmp1, log(tmp1),
					sqrt(1.0 / (tab[0][0] + 0.5) + 1.0 / (tab[1][0] + 0.5) +
						 1.0 / (tab[0][1] + 0.5) + 1.0 / (tab[1][1] + 0.5)));
		}
		else
			fputs("(freq2) Odds ratio computed for 2 x 2 tables only.\n", dap_log);
	}
	if (statv[FREQFISHER])
	{
		if (nlevels[0] == 2 && nlevels[1] == 2) /* only do for 2x2 tables */
		{
			if (tab[0][0] >= expect[0][0]) /* right-tail test: assoc stronger than expected */
			{
				denom = dap_bincoeff(sum, colsum[0]); /* number of tables given column sums */
				for (upleft = tab[0][0], dnleft = tab[1][0], prob = 0.0;
					 upleft <= rowsum[0] && upleft <= colsum[0];
					 upleft += 1.0, dnleft -= 1.0)
				{
					if (prob == 0.0)
					{
						oneprob = dap_bincoeff(rowsum[0], upleft) *
								  dap_bincoeff(rowsum[1], dnleft);
						prob = oneprob;
					}
					else
						prob += dap_bincoeff(rowsum[0], upleft) *
								dap_bincoeff(rowsum[1], dnleft);
				}
				fprintf(dap_lst, "Fisher's exact test: right     %g\n",
						prob / denom);
				for (upleft = ceil(expect[1][0]), dnleft = colsum[0] - upleft;
					 upleft <= rowsum[1] && upleft <= colsum[0];
					 upleft += 1.0, dnleft -= 1.0)
				{
					othprob = dap_bincoeff(rowsum[1], upleft) *
							  dap_bincoeff(rowsum[0], dnleft);
					if (othprob <= oneprob)
						prob += othprob;
				}
				if (tab[0][0] == expect[0][0])
					/* this is a kluge for tables satisfying independence */
					prob = 1.0;
				fprintf(dap_lst, "                     2-tailed  %g\n",
						prob / denom);
			}
			if (tab[0][0] <= expect[0][0])
			{
				denom = dap_bincoeff(sum, colsum[1]);
				for (upleft = tab[1][0], dnleft = tab[0][0], prob = 0.0;
					 upleft <= rowsum[1] && upleft <= colsum[0];
					 upleft += 1.0, dnleft -= 1.0)
				{
					if (prob == 0.0)
					{
						oneprob = dap_bincoeff(rowsum[1], upleft) *
								  dap_bincoeff(rowsum[0], dnleft);
						prob = oneprob;
					}
					else
						prob += dap_bincoeff(rowsum[1], upleft) *
								dap_bincoeff(rowsum[0], dnleft);
				}
				fprintf(dap_lst, "Fisher's exact test: left      %g\n",
						prob / denom);
				for (upleft = ceil(expect[0][0]), dnleft = colsum[0] - upleft;
					 upleft <= rowsum[0] && upleft <= colsum[0];
					 upleft += 1.0, dnleft -= 1.0)
				{
					othprob = dap_bincoeff(rowsum[0], upleft) *
							  dap_bincoeff(rowsum[1], dnleft);
					if (othprob <= oneprob)
						prob += othprob;
				}
				if (tab[0][0] == expect[0][0])
					/* this is a kluge for tables satisfying independence */
					prob = 1.0;
				fprintf(dap_lst, "                     2-tailed  %g\n",
						prob / denom);
			}
		}
		else
			fputs("(freq2) Fisher's exact test computed for 2 x 2 tables only.\n", dap_log);
	}
	if (statv[FREQORD])
	{
		for (r = 0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				a[r][c] = 0.0;
				d[r][c] = 0.0;
				for (rr = 0; rr < nlevels[0]; rr++)
					for (cc = 0; cc < nlevels[1]; cc++)
					{
						if ((rr < r && cc < c) || (rr > r && cc > c))
							a[r][c] += tab[rr][cc];
						else if ((rr < r && cc > c) || (rr > r && cc < c))
							d[r][c] += tab[rr][cc];
					}
			}
		for (r = 0, p = 0.0, q = 0.0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				p += tab[r][c] * a[r][c];
				q += tab[r][c] * d[r][c];
			}
		fprintf(dap_lst, "Statistic          Value   ASE\n");
		for (r = 0, var = 0.0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				tmp1 = q * a[r][c] - p * d[r][c];
				var += tab[r][c] * tmp1 * tmp1;
			}
		tmp2 = p + q;
		tmp2 *= tmp2;
		tmp2 *= tmp2;
		var *= 16.0 / tmp2;
		fprintf(dap_lst, "Gamma             %6.3f  %5.3f\n",
				(p - q) / (p + q), sqrt(var));
		for (r = 0, tmp1 = sum * sum; r < nlevels[0]; r++)
			tmp1 -= rowsum[r] * rowsum[r];
		for (c = 0, tmp2 = sum * sum; c < nlevels[1]; c++)
			tmp2 -= colsum[c] * colsum[c];
		w = sqrt(tmp1 * tmp2);
		t = (p - q) / w;
		for (r = 0, var = 0.0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				tmp3 = 2.0 * w * (a[r][c] - d[r][c]) +
					   t * (rowsum[r] * tmp2 + colsum[c] * tmp1);
				var += tab[r][c] * tmp3 * tmp3;
			}
		tmp4 = tmp1 + tmp2;
		var = (var - sum * sum * sum * t * t * tmp4 * tmp4) / (w * w * w * w);
		fprintf(dap_lst, "Kendall's Tau-b   %6.3f  %5.3f\n", t, sqrt(var));
		for (r = 0, var = 0.0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				tmp3 = tmp1 * (a[r][c] - d[r][c]) - (p - q) * (sum - rowsum[r]);
				var += tab[r][c] * tmp3 * tmp3;
			}
		var *= 4.0 / (tmp1 * tmp1 * tmp1 * tmp1);
		fprintf(dap_lst, "Somers' D C|R     %6.3f  %5.3f\n", (p - q) / tmp1, sqrt(var));
		for (r = 0, var = 0.0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				tmp3 = tmp2 * (a[r][c] - d[r][c]) - (p - q) * (sum - colsum[c]);
				var += tab[r][c] * tmp3 * tmp3;
			}
		var *= 4.0 / (tmp2 * tmp2 * tmp2 * tmp2);
		fprintf(dap_lst, "Somers' D R|C     %6.3f  %5.3f\n", (p - q) / tmp2, sqrt(var));
	}
	if (statv[FREQPAIR])
	{
		if (nlevels[0] != nlevels[1])
		{
			fprintf(dap_err, "(freq2) PAIR requires square table, table is %d x %d.\n",
					nlevels[0], nlevels[1]);
			exit(1);
		}
		for (r = 0, p = 0.0, q = 0.0, tmp1 = 0.0, tmp2 = 0.0; r < nlevels[0]; r++)
		{
			p += tab[r][r];	   /* Po */
			q += expect[r][r]; /* Pe */
			tmp1 += tab[r][r] * (rowsum[r] + colsum[r]);
			for (c = 0; c < nlevels[0]; c++)
			{
				tmp3 = (rowsum[c] + colsum[r]);
				tmp2 += tab[r][c] * tmp3 * tmp3;
			}
		}
		p /= sum;
		q /= sum;
		tmp1 /= sum * sum;
		tmp2 /= sum * sum * sum;
		tmp3 = 1.0 - p;
		tmp4 = 1.0 - q;
		fprintf(dap_lst, "Statistic          Value   ASE\n");
		fprintf(dap_lst, "Kappa             %6.3f  %5.3f\n",
				(p - q) / tmp4,
				sqrt((p * tmp3 / (tmp4 * tmp4) +
					  2.0 * tmp3 * (2.0 * p * q - tmp1) / (tmp4 * tmp4 * tmp4) +
					  tmp3 * tmp3 * (tmp2 - 4.0 * q * q) / (tmp4 * tmp4 * tmp4 * tmp4)) /
					 sum));
	}
	if (statv[FREQNOM])
	{
		for (hx = 0.0, r = 0; r < nlevels[0]; r++)
			hx -= rowsum[r] * log(rowsum[r] / sum);
		hx /= sum;
		for (hy = 0.0, c = 0; c < nlevels[1]; c++)
			hy -= colsum[c] * log(colsum[c] / sum);
		hy /= sum;
		for (hxy = 0.0, r = 0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
				hxy -= tab[r][c] * log(tab[r][c] / sum);
		hxy /= sum;
		uv = hx + hy - hxy;
		fprintf(dap_lst, "Statistic              Value   ASE\n");
		for (var = 0.0, r = 0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				tmp1 = hy * log(tab[r][c] / rowsum[r]) +
					   (hx - hxy) * log(colsum[c] / sum);
				var += tab[r][c] * tmp1 * tmp1;
			}
		var = sqrt(var) / (sum * hy * hy);
		fprintf(dap_lst, "Uncertainty C|R       %6.3f  %5.3f\n",
				uv / hy, var);
		for (var = 0.0, r = 0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				tmp1 = hx * log(tab[r][c] / colsum[c]) +
					   (hy - hxy) * log(rowsum[r] / sum);
				var += tab[r][c] * tmp1 * tmp1;
			}
		var = sqrt(var) / (sum * hx * hx);
		fprintf(dap_lst, "Uncertainty R|C       %6.3f  %5.3f\n",
				uv / hx, var);
		for (var = 0.0, r = 0; r < nlevels[0]; r++)
			for (c = 0; c < nlevels[1]; c++)
			{
				tmp1 = hxy * log(rowsum[r] * colsum[c] / (sum * sum)) -
					   (hx + hy) * log(tab[r][c] / sum);
				var += tab[r][c] * tmp1 * tmp1;
			}
		tmp2 = hx + hy;
		var = 2.0 * sqrt(var) / (sum * tmp2 * tmp2);
		fprintf(dap_lst, "Uncertainty Symmetric %6.3f  %5.3f\n",
				2.0 * uv / (hx + hy), var);
	}
	dap_swap();
	dap_free(expmem, (char*) "");
	dap_free(expect, (char*) "");
	dap_free(rowsum, (char*) "");
	dap_free(colsum, (char*) "");
	dap_free(amem, (char*) "");
	dap_free(a, (char*) "");
	dap_free(dmem, (char*) "");
	dap_free(d, (char*) "");
}

static int freqparse(char *varlist, int *varv, int *wt)
{
	int nvars;
	int m;
	int i;
	char *mname;
	int wtvar;

	wt[0] = -1;
	if (!varlist)
		return 0;
	mname = dap_malloc(dap_namelen + 1, (char*) "");
	for (m = 0; varlist[m] == ' '; m++)
		;
	for (nvars = 0, wtvar = 0; varlist[m];)
	{
		if (varlist[m] == '*')
		{
			if (wtvar)
			{
				fprintf(dap_err,
						"(freqparse) Only one weight variable allowed: %s\n",
						varlist);
				exit(1);
			}
			wtvar = 1;
			for (m++; varlist[m] == ' '; m++)
				;
		}
		for (i = 0; varlist[m + i] && varlist[m + i] != ' ' && varlist[m + i] != '*'; i++)
		{
			if (i < dap_namelen)
				mname[i] = varlist[m + i];
			else
			{
				mname[i] = '\0';
				fprintf(dap_err, "(dap_list) Variable name too long: %s\n",
						mname);
				exit(1);
			}
		}
		mname[i] = '\0';
		if (wtvar)
		{
			if ((wt[0] = dap_varnum(mname)) < 0)
			{
				fprintf(dap_err, "(dap_list) Weight variable unknown: %s\n", mname);
				exit(1);
			}
		}
		else if ((varv[nvars++] = dap_varnum(mname)) < 0)
		{
			fprintf(dap_err, "(dap_list) Variable unknown: %s\n", mname);
			exit(1);
		}
		m += i;
		while (varlist[m] == ' ')
			m++;
	}
	dap_free(mname, (char*) "");
	return nvars;
}



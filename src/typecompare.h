#include <cstdio>
#include <cstring>

static int dblcmp(const void *d1, const void *d2)
{
  if (*(double *)d1 < *(double *)d2)
    return -1;
  else if (*(double *)d1 > *(double *)d2)
    return 1;
  return 0;
}

static int intcmp(const void *i1, const void *i2)
{
  if (*(int *)i1 < *(int *)i2)
    return -1;
  else if (*(int *)i1 > *(int *)i2)
    return 1;
  return 0;
}

static int stcmp(const void *s1, const void *s2)
{
  return strcmp(*(char **)s1, *(char **)s2);
}

static int ddblcmp(const void *x, const void *y)
{
  if (*(double **)x < *(double **)y)
    return -1;
  if (*(double **)x > *(double **)y)
    return 1;
  return 0;
}

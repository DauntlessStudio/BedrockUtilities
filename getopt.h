#pragma once
#include <string.h>
#include <stdio.h>

int     bed_opterr = 1,             /* if error message should be printed */
  bed_optind = 1,             /* index into parent argv vector */
  bed_optopt,                 /* character checked for validity */
  bed_optreset;               /* reset getopt */
char    *bed_optarg;                /* argument associated with option */

#define BADCH   (int)'?'
#define BADARG  (int)':'
#define EMSG    ""

/*
* getopt --
*      Parse argc/argv argument vector.
*/
int
  bed_getopt(int nargc, char * const nargv[], const char *ostr)
{
   char conversion[] = EMSG;
  static char *place = conversion;              /* option letter processing */
  const char *oli;                        /* option letter list index */

  if (bed_optreset || !*place) {              /* update scanning pointer */
    bed_optreset = 0;
    if (bed_optind >= nargc || *(place = nargv[bed_optind]) != '-') {
      place = conversion;
      return (-1);
    }
    if (place[1] && *++place == '-') {      /* found "--" */
      ++bed_optind;
      place = conversion;
      return (-1);
    }
  }                                       /* option letter okay? */
  if ((bed_optopt = (int)*place++) == (int)':' ||
    !(oli = strchr(ostr, bed_optopt))) {
      /*
      * if the user didn't specify '-' as an option,
      * assume it means -1.
      */
      if (bed_optopt == (int)'-')
        return (-1);
      if (!*place)
        ++bed_optind;
      if (bed_opterr && *ostr != ':')
        (void)printf("illegal option -- %c\n", bed_optopt);
      return (BADCH);
  }
  if (*++oli != ':') {                    /* don't need argument */
    bed_optarg = NULL;
    if (!*place)
      ++bed_optind;
  }
  else {                                  /* need an argument */
    if (*place)                     /* no white space */
      bed_optarg = place;
    else if (nargc <= ++bed_optind) {   /* no arg */
      place = conversion;
      if (*ostr == ':')
        return (BADARG);
      if (bed_opterr)
        (void)printf("option requires an argument -- %c\n", bed_optopt);
      return (BADCH);
    }
    else                            /* white space */
      bed_optarg = nargv[bed_optind];
    place = conversion;
    ++bed_optind;
  }
  return (bed_optopt);                        /* dump back option letter */
}
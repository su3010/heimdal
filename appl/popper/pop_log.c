/*
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef lint
static char copyright[] = "Copyright (c) 1990 Regents of the University of California.\nAll rights reserved.\n";
static char SccsId[] = "@(#)@(#)pop_log.c	2.1  2.1 3/18/91";
#endif not lint

#include <stdio.h>
#include <sys/types.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "popper.h"

/* 
 *  log:    Make a log entry
 */

static char msgbuf[MAXLINELEN];

int
#ifdef __STDC__
pop_log(POP *p, int stat, char *format, ...)
#else
pop_log(va_alist)
va_dcl
#endif
{
    va_list     ap;
#ifdef __STDC__
    va_start(ap, format);
#else
    POP     *   p;
    int         stat;
    char    *   format;

    va_start(ap);
    p = va_arg(ap,POP *);
    stat = va_arg(ap,int);
    format = va_arg(ap,char *);
#endif

#ifdef HAVE_VSPRINTF
        vsprintf(msgbuf,format,ap);
#else
        {
	    int a0 = va_arg(ap, int);
	    int a1 = va_arg(ap, int);
	    int a2 = va_arg(ap, int);
	    int a3 = va_arg(ap, int);
	    int a4 = va_arg(ap, int);
	    int a5 = va_arg(ap, int);
	    (void)sprintf(msgbuf, format, a0, a1, a2, a3, a4, a5, 0, 4711);
	}
#endif /* HAVE_VSPRINTF */

    if (p->debug && p->trace) {
        (void)fprintf(p->trace,"%s\n",msgbuf);
        (void)fflush(p->trace);
    }
    else {
        syslog (stat,"%s",msgbuf);
    }
    va_end(ap);

    return(stat);
}

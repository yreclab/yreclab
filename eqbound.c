/* eqbound.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal xz[215600]	/* was [5][10][56][77] */, t6list[4312]	/* 
	    was [77][56] */, rho[77], t6a[56], esk[4312]	/* was [56][
	    77] */, esk2[4312]	/* was [56][77] */, dfsx[5], dfs[56], dfsr[77]
	    , xa[5];
    integer m, mf;
} a_;

#define a_1 a_

struct {
    doublereal rmx[56];
    integer kra[56], kt;
} rmpopeos_;

#define rmpopeos_1 rmpopeos_

/* Table of constant values */

static integer c__1 = 1;

/* MHP 8/98 SUBROUTINE TO CHECK IF POINT IS WITHIN */
/* OPAL EOS TABLE. */
/* Subroutine */ int eqbound_(doublereal *t, doublereal *dl, doublereal *dl0, 
	doublereal *fac, logical *ltab, logical *lramp)
{
    /* Format strings */
    static char fmt_5[] = "(\002 ERROR IN OPAL EOS: OUTSIDE TABLE IN T6\002,"
	    "2f10.6,i5)";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    double d_lg10(doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal t6, ft, tt, dlim, dlim2;

    /* Fortran I/O blocks */
    static cilist io___4 = { 0, 6, 0, fmt_5, 0 };
    static cilist io___5 = { 0, 6, 0, fmt_5, 0 };


    t6 = *t * 1e-6;
/* EXIT IF OUTSIDE TABLE IN RHO */
    if (*dl < -14. || *dl > 5.) {
	goto L9999;
/* Out of Table in density. Go to Error exit */
    }
/* FIND NEAREST TABLE ELEMENT IN T. */
    if (t6 < a_1.t6a[rmpopeos_1.kt - 1]) {
	for (i__ = rmpopeos_1.kt + 1; i__ <= 56; ++i__) {
	    if (t6 >= a_1.t6a[i__ - 1]) {
		rmpopeos_1.kt = i__ - 1;
		goto L10;
	    }
	}
	tt = a_1.t6a[55];
/* SR CALL SHOULD HAVE BEEN STOPPED OUTSIDE TABLE BOUNDS; STOP CODE */
	s_wsfe(&io___4);
	do_fio(&c__1, (char *)&t6, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tt, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rmpopeos_1.kt, (ftnlen)sizeof(integer));
	e_wsfe();
	s_stop("", (ftnlen)0);
L10:
	;
    } else {
	for (i__ = rmpopeos_1.kt; i__ >= 1; --i__) {
	    if (t6 <= a_1.t6a[i__ - 1]) {
		rmpopeos_1.kt = i__;
		goto L20;
	    }
	}
	tt = a_1.t6a[0];
/* SR CALL SHOULD HAVE BEEN STOPPED OUTSIDE TABLE BOUNDS; STOP CODE */
	s_wsfe(&io___5);
	do_fio(&c__1, (char *)&t6, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tt, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rmpopeos_1.kt, (ftnlen)sizeof(integer));
	e_wsfe();
	s_stop("", (ftnlen)0);
L20:
	;
    }
    ft = (t6 - a_1.t6a[rmpopeos_1.kt]) / (a_1.t6a[rmpopeos_1.kt - 1] - 
	    a_1.t6a[rmpopeos_1.kt]);
/* DEFINE TABLE EDGE IN RHO BY LINEAR INTERPOLATION. */
    dlim = rmpopeos_1.rmx[rmpopeos_1.kt];
/*      DLIM = RMX(KT+1)+FT*(RMX(KT)-RMX(KT+1)) */
    dlim = d_lg10(&dlim);
/* DEFINE BEGINNING OF RAMP IN THE SAME FASHION - */
/* RAMP IS DEFINED AS ONE TABLE ELEMENT WIDE. */
/*      DLIM2 = RHO(KRA(KT+1)-1)+FT*(RHO(KRA(KT)-1)- */
/*     *        RHO(KRA(KT+1)-1)) */
    dlim2 = a_1.rho[rmpopeos_1.kra[rmpopeos_1.kt] - 2];
    dlim2 = d_lg10(&dlim2);
/* CHECK IF WITHIN TABLE BOUNDS IN RHO */
    if (*dl > dlim) {
/*         WRITE(*,*)T6,DL,DLIM */
	goto L9999;
/* Out of table in density. Go to error exit */
    }
/*  If we get here, the point is in the table. */
    *ltab = TRUE_;
/*  Now we check if ramping is needed. */
/*  First we check if ramping in temperature is needed. */
/*      WRITE(*,911)DL,DLIM,DLIM2 */
/* 911  FORMAT(3F11.4) */
    if (t6 <= a_1.t6a[54]) {
	*lramp = TRUE_;
	*fac = (t6 - a_1.t6a[55]) / (a_1.t6a[54] - a_1.t6a[55]);
    } else if (t6 >= a_1.t6a[1]) {
	*lramp = TRUE_;
	*fac = (a_1.t6a[0] - t6) / (a_1.t6a[0] - a_1.t6a[1]);
    } else if (*dl >= dlim2) {
/*  If we get here, ramping in density is needed. */
	*lramp = TRUE_;
	*fac = (dlim - *dl) / (dlim - dlim2);
/*         WRITE(*,912)DL,DL0,DLIM,DLIM2,FAC */
/* 912     format(' high rho ramp',5f9.6) */
    } else {
/*        If we get here, we are in the middel of the table and */
/*        no ramping is needed. */
	*lramp = FALSE_;
    }
    return 0;
/* Error Exit. */
L9999:
    *ltab = FALSE_;
/* Not in table */
    *lramp = TRUE_;
/* Turn on ramping */
    *fac = 0.;
/*                            This way, out of table results are ramped to zero. */
/* Set ramping factor to zero */
    return 0;
} /* eqbound_ */


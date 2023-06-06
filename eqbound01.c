/* eqbound01.f -- translated by f2c (version 20100827).
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
    doublereal xz[1613950]	/* was [5][10][191][169] */, t6list[32279]	
	    /* was [169][191] */, rho[169], t6a[191], esk[32279]	/* 
	    was [191][169] */, esk2[32279]	/* was [191][169] */, dfsx[5],
	     dfs[191], dfsr[169];
    integer m, mf;
    doublereal xa[5];
} aeos_;

#define aeos_1 aeos_

struct {
    doublereal rmx[191];
    integer kra[191], kt;
} rmpopeos01_;

#define rmpopeos01_1 rmpopeos01_

/* Table of constant values */

static integer c__1 = 1;

/* MHP 7/2003 SUBROUTINE TO CHECK IF POINT IS WITHIN */
/* OPAL EOS TABLE. */
/* Subroutine */ int eqbound01_(doublereal *t, doublereal *dl, doublereal *
	dl0, doublereal *fac, logical *ltab, logical *lramp)
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


/*      COMMON/A/  XZ(MX,MV,NT,NR), */
/*     *T6LIST(NR,NT),RHO(NR),T6A(NT),ESK(NT,NR),ESK2(NT,NR),DFSX(MX), */
/*     * DFS(NT),DFSR(NR),XA(MX),M,MF */
/*      COMMON/RMPOPEOS/RMX(NT),KRA(NT),KT */
    t6 = *t * 1e-6;
/* EXIT IF OUTSIDE TABLE IN RHO */
    if (*dl < -14. || *dl > 7.) {
	goto L9999;
/* Out of Table in density. Go to Error exit */
    }
/* FIND NEAREST TABLE ELEMENT IN T. */
    if (t6 < aeos_1.t6a[rmpopeos01_1.kt - 1]) {
	for (i__ = rmpopeos01_1.kt + 1; i__ <= 191; ++i__) {
	    if (t6 >= aeos_1.t6a[i__ - 1]) {
		rmpopeos01_1.kt = i__ - 1;
		goto L10;
	    }
	}
	tt = aeos_1.t6a[190];
/* SR CALL SHOULD HAVE BEEN STOPPED OUTSIDE TABLE BOUNDS; STOP CODE */
	s_wsfe(&io___4);
	do_fio(&c__1, (char *)&t6, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tt, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rmpopeos01_1.kt, (ftnlen)sizeof(integer));
	e_wsfe();
	s_stop("", (ftnlen)0);
L10:
	;
    } else {
	for (i__ = rmpopeos01_1.kt; i__ >= 1; --i__) {
	    if (t6 <= aeos_1.t6a[i__ - 1]) {
		rmpopeos01_1.kt = i__;
		goto L20;
	    }
	}
	tt = aeos_1.t6a[0];
/* SR CALL SHOULD HAVE BEEN STOPPED OUTSIDE TABLE BOUNDS; STOP CODE */
	s_wsfe(&io___5);
	do_fio(&c__1, (char *)&t6, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tt, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rmpopeos01_1.kt, (ftnlen)sizeof(integer));
	e_wsfe();
	s_stop("", (ftnlen)0);
L20:
	;
    }
    ft = (t6 - aeos_1.t6a[rmpopeos01_1.kt]) / (aeos_1.t6a[rmpopeos01_1.kt - 1]
	     - aeos_1.t6a[rmpopeos01_1.kt]);
/* DEFINE TABLE EDGE IN RHO BY LINEAR INTERPOLATION. */
    dlim = rmpopeos01_1.rmx[rmpopeos01_1.kt];
/*      DLIM = RMX(KT+1)+FT*(RMX(KT)-RMX(KT+1)) */
    dlim = d_lg10(&dlim);
/* DEFINE BEGINNING OF RAMP IN THE SAME FASHION - */
/* RAMP IS DEFINED AS ONE TABLE ELEMENT WIDE. */
/*      DLIM2 = RHO(KRA(KT+1)-1)+FT*(RHO(KRA(KT)-1)- */
/*     *        RHO(KRA(KT+1)-1)) */
    dlim2 = aeos_1.rho[rmpopeos01_1.kra[rmpopeos01_1.kt] - 2];
    dlim2 = d_lg10(&dlim2);
/* CHECK IF WITHIN TABLE BOUNDS IN RHO */
    if (*dl > dlim) {
/*         WRITE(*,*)T6,DL,DLIM */
	goto L9999;
/* Out of Table in density. Go to Error exit */
    }
/*  If we get here, the point is in the table. */
    *ltab = TRUE_;
/*      WRITE(*,911)DL,DLIM,DLIM2 */
/* 911  FORMAT(3F11.4) */
/*  Now we check if ramping is needed. */
/*  First we check if ramping in temperature is needed. */
    if (t6 <= aeos_1.t6a[189]) {
	*lramp = TRUE_;
	*fac = (t6 - aeos_1.t6a[190]) / (aeos_1.t6a[189] - aeos_1.t6a[190]);
    } else if (t6 >= aeos_1.t6a[1]) {
	*lramp = TRUE_;
	*fac = (aeos_1.t6a[0] - t6) / (aeos_1.t6a[0] - aeos_1.t6a[1]);
    } else if (*dl >= dlim2) {
/*  If we get here, ramping in density is needed. */
	*lramp = TRUE_;
	*fac = (dlim - *dl) / (dlim - dlim2);
/*         WRITE(*,912)DL,DL0,DLIM,DLIM2,FAC */
/* 912     format(' high rho ramp',5f9.6) */
    } else {
	*lramp = FALSE_;
    }
    return 0;
/* Error Exit. */
/* Normal exit */
L9999:
    *ltab = FALSE_;
/* Not in table */
    *lramp = TRUE_;
/* Turn on ramping */
    *fac = 0.;
/*                            This way, out of table results are ramped to zero. */
/* Set ramping factor to zero */
    return 0;
/* Error exit */
} /* eqbound01_ */


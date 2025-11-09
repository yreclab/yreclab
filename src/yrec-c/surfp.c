/* surfp.f -- translated by f2c (version 20061008).
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
    doublereal tau, ap, at, ad, ao, afxion[3];
} atmprt_;

#define atmprt_1 atmprt_

struct {
    doublereal atmpl[627]	/* was [57][11] */, atmtl[57], atmgl[11], 
	    atmz;
    integer ioatm;
} atmos2_;

#define atmos2_1 atmos2_

struct {
    integer imin[57], iminmax[57], jp, kp[4], imin2[76], iminmax2[76];
} fac_;

#define fac_1 fac_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int surfp_(doublereal *teffl, doublereal *gl, logical *lprt)
{
    /* Format strings */
    static char fmt_911[] = "(1x,\002DESIRED ATMOSPHERE OUTSIDE TABLE RANG"
	    "E\002/\002 LOG TEFF\002,f10.6,\002 LOG G\002,f10.6/\002 RUN STOP"
	    "PED\002)";
    static char fmt_70[] = "(\002********PRESSURE AT T=TEFF INTERPOLATED FRO"
	    "M TABULATED\002,\002 VALUES********\002)";
    static char fmt_71[] = "(\002 \002,20x,\002LOG (Teff) =\002,f10.5,\002 L"
	    "OG P =\002,f10.5)";

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer j, k, n;
    static doublereal y0;
    static integer jj, kk;
    static doublereal qg[4], fx, pp[4], yg[4], qs[3], qt[4], yt[4], qgg[3];
    static integer kkk;
    static doublereal dum[3], ptab[4];
    extern /* Subroutine */ int inter3_(doublereal *, doublereal *, 
	    doublereal *, doublereal *), kspline_(doublereal *, doublereal *, 
	    doublereal *), ksplint_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, fmt_911, 0 };
    static cilist io___2 = { 0, 0, 0, fmt_911, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___21 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_71, 0 };
    static cilist io___23 = { 0, 0, 0, fmt_71, 0 };


/* PARAMETERS NT AND NG FOR TABULATED SURFACE PRESSURES. */
/*      CHARACTER*256 FATM */
/* MHP 8/25 Removed file names from common block */
/*      COMMON/ATMOS2/ATMPL(NT,NG),ATMTL(NT), */
/*     *              ATMGL(NG),ATMZ,IOATM,FATM */
/* SURFPL INTERPOLATES IN TEMPERATURE USING A 4-POINT LAGRANGIAN */
/* INTERPOLATOR, AND INTERPOLATES IN GRAVITY THE SAME WAY IF 4 OR */
/* MORE POINTS ARE AVAILABLE.  IT WILL QUIT IF THE DESIRED DATA POINT */
/* HAS TEFF OR LOG G MORE THAN ONE TABLE POINT FROM THE DATA. */

/* CHECK TO ENSURE THAT DATA IS WITHIN TABLE. */
    if (*teffl < 3.5 || *gl < -.5) {
	io___1.ciunit = luout_1.iowr;
	s_wsfe(&io___1);
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	e_wsfe();
	io___2.ciunit = luout_1.ishort;
	s_wsfe(&io___2);
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
/* TEMPERATURE INTERPOLATION FACTORS. */
    for (j = 1; j <= 57; ++j) {
	if (*teffl <= atmos2_1.atmtl[j - 1]) {
	    goto L10;
	}
    }
    j = 57;
L10:
/* Computing MAX */
    i__1 = 1, i__2 = j - 2;
    jj = max(i__1,i__2);
    jj = min(54,jj);
    for (k = 1; k <= 4; ++k) {
	qt[k - 1] = atmos2_1.atmtl[jj + k - 2];
    }
/*      CALL INTRP2(QR,QT,TEFFL) */
    fac_1.jp = jj;
/* GRAVITY INTERPOLATION FACTORS. */
    i__1 = jj + 3;
    for (j = jj; j <= i__1; ++j) {
	n = j - jj + 1;
/* CHECK IF 4 LOG VALUES AVAILABLE - OTHERWISE, USE 3 POINT LAGRANGIAN */
/* OR LINEAR INTERPOLATION. */
	if (atmos2_1.atmtl[j - 1] > 4.5) {
	    if (atmos2_1.atmtl[j - 1] > 4.55) {
/* LINEAR INTERPOLATION */
		fx = (*gl - atmos2_1.atmgl[9]) / (atmos2_1.atmgl[10] - 
			atmos2_1.atmgl[9]);
		pp[n - 1] = atmos2_1.atmpl[j + 512] + fx * (atmos2_1.atmpl[j 
			+ 569] - atmos2_1.atmpl[j + 512]);
		fac_1.kp[n - 1] = 10;
	    } else {
/* 3-POINT LAGRANGIAN INTERPOLATION. */
		for (k = 1; k <= 3; ++k) {
		    qs[k - 1] = atmos2_1.atmgl[k + 7];
		}
		inter3_(qs, qgg, dum, gl);
		pp[n - 1] = atmos2_1.atmpl[j + 455] * qgg[0] + atmos2_1.atmpl[
			j + 512] * qgg[1] + atmos2_1.atmpl[j + 569] * qgg[2];
		fac_1.kp[n - 1] = 9;
	    }
	    goto L20;
	}
	if (*gl >= atmos2_1.atmgl[9]) {
/* DESIRED LOG G ABOVE SECOND TO TOP TABLE LOG G - USE TOP 4 LOG G VALUES. */
	    for (kk = 1; kk <= 4; ++kk) {
		qg[kk - 1] = atmos2_1.atmgl[kk + 6];
		ptab[kk - 1] = atmos2_1.atmpl[j + (kk + 7) * 57 - 58];
	    }
/*            CALL INTRP2(QR,QG,GL) */
	    kspline_(qg, ptab, yg);
	    ksplint_(qg, ptab, yg, gl, &y0);
/*            PP(N) = ATMPL(J,NG-3)*QG(1)+ATMPL(J,NG-2)*QG(2)+ */
/*     *              ATMPL(J,NG-1)*QG(3)+ATMPL(J,NG)*QG(4) */
	    pp[n - 1] = y0;
	    fac_1.kp[n - 1] = 8;
	    goto L20;
	}
/* GENERAL CASE - FIND 4 NEAREST POINTS IN GRAVITY THAT ARE IN THE TABLE. */
/* G Somers, I changed NG to IMINMAX in the next line. This prevents the */
/* code from using -999 to interpolate in some instances. */
	i__2 = fac_1.imin[j - 1];
	for (k = fac_1.iminmax[j - 1] - 3; k >= i__2; --k) {
	    if (*gl < atmos2_1.atmgl[k + 1] && *gl >= atmos2_1.atmgl[k]) {
/* Computing MAX */
		i__3 = fac_1.imin[j - 1];
		kk = max(i__3,k);
		kk = min(8,kk);
		for (kkk = 1; kkk <= 4; ++kkk) {
		    qg[kkk - 1] = atmos2_1.atmgl[kk + kkk - 2];
		    ptab[kkk - 1] = atmos2_1.atmpl[j + (kk + kkk - 1) * 57 - 
			    58];
		}
		kspline_(qg, ptab, yg);
		ksplint_(qg, ptab, yg, gl, &y0);
		pp[n - 1] = y0;
/*               CALL INTRP2(QR,QG,GL) */
/*               PP(N) = ATMPL(J,KK)*QG(1)+ATMPL(J,KK+1)*QG(2)+ */
/*     *                 ATMPL(J,KK+2)*QG(3)+ATMPL(J,KK+3)*QG(4) */
		fac_1.kp[n - 1] = kk;
		goto L20;
	    }
	}
/* DESIRED LOG G BELOW 2ND TABLE ENTRY -USE FIRST 4 POINTS. */
	for (k = 1; k <= 4; ++k) {
	    qg[k - 1] = atmos2_1.atmgl[k + fac_1.imin[j - 1] - 2];
	    ptab[k - 1] = atmos2_1.atmpl[j + (k + fac_1.imin[j - 1] - 1) * 57 
		    - 58];
	}
	kspline_(qg, ptab, yg);
	ksplint_(qg, ptab, yg, gl, &y0);
	pp[n - 1] = y0;
/*         CALL INTRP2(QR,QG,GL) */
/*         II = IMIN(J) */
/*         PP(N) = ATMPL(J,II)*QG(1)+ATMPL(J,II+1)*QG(2)+ */
/*     *           ATMPL(J,II+2)*QG(3)+ATMPL(J,II+3)*QG(4) */
	fac_1.kp[n - 1] = fac_1.imin[j - 1];
L20:
	;
    }
/* INTERPOLATE IN TEMPERATURE TO FIND CORRECT LOG P. */
    kspline_(qt, pp, yt);
    ksplint_(qt, pp, yt, teffl, &y0);
/*      AP = PP(1)*QT(1)+PP(2)*QT(2)+PP(3)*QT(3)+PP(4)*QT(4) */
    atmprt_1.ap = y0;
    atmprt_1.at = *teffl;
/* WRITE OUT INFORMATION TO THE MODEL FILE. */
    if (*lprt) {
	io___20.ciunit = luout_1.ishort;
	s_wsfe(&io___20);
	e_wsfe();
	io___21.ciunit = luout_1.istor;
	s_wsfe(&io___21);
	e_wsfe();
	io___22.ciunit = luout_1.ishort;
	s_wsfe(&io___22);
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&atmprt_1.ap, (ftnlen)sizeof(doublereal));
	e_wsfe();
	io___23.ciunit = luout_1.istor;
	s_wsfe(&io___23);
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&atmprt_1.ap, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    return 0;
} /* surfp_ */


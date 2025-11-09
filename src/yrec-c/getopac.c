/* getopac.f -- translated by f2c (version 20061008).
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
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
} nwlaol_;

#define nwlaol_1 nwlaol_

struct {
    doublereal optol, zsi;
    integer idt, idd[4];
} optab_;

#define optab_1 optab_

struct {
    integer ikur2, icondopacp;
    logical lcondopacp;
} miscopac_;

#define miscopac_1 miscopac_

/* Table of constant values */

static doublereal c_b3 = 10.;
static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     GETOPAC */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int getopac_(doublereal *dl, doublereal *tl, doublereal *x, 
	doublereal *z__, doublereal *o, doublereal *ol, doublereal *qod, 
	doublereal *qot, doublereal *fxion)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    double d_lg10(doublereal *);

    /* Local variables */
    extern /* Subroutine */ int getalex06_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), getopal95_(doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal o1, oc, so, ox, oz, ol1, so1, ocl, sol, olz, zit, qod1, 
	    sol1, qot1, cond, qodc, sqod, qotc, qodx, qodz, sqot, qotx, qotz;
    extern /* Subroutine */ int condopacpint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *);
    static doublereal sqod1, sqot1, slope, rmpwt;
    extern /* Subroutine */ int yalo3d_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), yllo3d_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static logical lcondo;
    extern /* Subroutine */ int gtlaol_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), yllo3d2_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), kurucz_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), gtpurz_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), gtlaol2_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), kurucz2_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static logical lgotatm;

    /* Fortran I/O blocks */
    static cilist io___11 = { 0, 0, 0, 0, 0 };
    static cilist io___17 = { 0, 0, 0, 0, 0 };
    static cilist io___22 = { 0, 0, 0, 0, 0 };


/* MHP 8/25 Removed unused variables */
/*      CHARACTER*256 FLAOL, FPUREZ, FKUR2, FcondOpacP */
/* OPACITY COMMON BLOCKS - modified 3/09 */
/* MHP 8/25 Removed character file names from common block */
/* MHP 8/25 Removed character file names from common block */

/*     THIS SUBROUTINE CALCULATES THE OPACITY FOR A GIVEN X AND Z. */
/*     IF LDIFZ=T OR LZRAMP=T THEN INTERPOLATE BETWEEN TWO Z TABLES. */
/*     IN A SMALL T RANGE THE ATMOSPHERE AND INTERIOR OPACITY ARE */
/*     RAMPED FROM ONE TO THE OTHER. */


/*     GET ATMOSPHERE OPACITY */

    /* Parameter adjustments */
    --fxion;

    /* Function Body */
    lgotatm = FALSE_;
    if (*tl <= newopac_1.tmolmax) {
	if (newopac_1.lalex06) {
	    getalex06_(dl, tl, x, z__, &so, &sol, &sqod, &sqot);
/*             RR = DL - 3.0D0*(TL-6.0D0) */
/*             WRITE(*,911)X,Z,RR,TL,SOL */
/* 911         FORMAT(2f5.2,3f7.3) */
	    lgotatm = TRUE_;
	} else if (newopac_1.lalex95) {
	    yalo3d_(dl, tl, x, z__, &so, &sol, &sqod, &sqot);
	    lgotatm = TRUE_;
	} else if (newopac_1.lkur90) {
	    switch (kurucz_(dl, tl, &so, &sol, &sqod, &sqot)) {
		case 1:  goto L100;
	    }
	    if (newopac_1.l2z) {
		switch (kurucz2_(dl, tl, &so1, &sol1, &sqod1, &sqot1)) {
		    case 1:  goto L100;
		}
		slope = (sol - sol1) / (newopac_1.zkur1 - newopac_1.zkur2);
		sol = sol1 + (*z__ - newopac_1.zkur2) * slope;
		so = pow_dd(&c_b3, &sol);
		slope = (sqod - sqod1) / (newopac_1.zkur1 - newopac_1.zkur2);
		sqod = sqod1 + (*z__ - newopac_1.zkur2) * slope;
		slope = (sqot - sqot1) / (newopac_1.zkur1 - newopac_1.zkur2);
		sqot = sqot1 + (*z__ - newopac_1.zkur2) * slope;
	    }
	    lgotatm = TRUE_;
	}
    }
L100:
/*     GET INTERIOR OPACITY IF NEEDED */
    if (*tl < newopac_1.tmolmin && lgotatm) {
	goto L1000;
    }
/*     HELIUM BURNING REGION (HB EVOLUTION) USE PURE Z TABLE */
/* mhp 7/12 Altered logic of the opacities in the He burnng */
/* regime.  Switched to exclusive usage of OPAL below 50 million K */
/* and switched the ramp to above Z = 0.1. */
    if (*z__ > .1 && *tl > 7.7) {
/*      IF((Z .GT. 0.15D0) .OR. */
/*     *     ((ABS(Z-ZENV) .GT. OPTOL).AND..NOT.L2Z)) THEN */
	if (! nwlaol_1.lpurez) {
/*            WRITE(ISHORT, *)' ERROR: Z.NE.ZENV. NEED PURE Z', */
/*     *        ' TABLE TO CONTINUE. Z,ZENV=',Z, ZENV */
	    io___11.ciunit = luout_1.ishort;
	    s_wsle(&io___11);
	    do_lio(&c__9, &c__1, " ERROR: Z>0.10 T > 5 X 10^7 K", (ftnlen)29);
	    do_lio(&c__9, &c__1, " NEED PURE Z TABLE TO CONTINUE. Z,LOG T=", (
		    ftnlen)40);
	    do_lio(&c__5, &c__1, (char *)&(*z__), (ftnlen)sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_stop("", (ftnlen)0);
	}
	gtpurz_(dl, tl, &oz, &olz, &qodz, &qotz);
	if (newopac_1.lopal95) {
/* MHP 7/12 INTERPOLATE TO MAXIMUM Z IN TABLE */
	    zit = .1;
	    getopal95_(dl, tl, x, &zit, o, ol, qod, qot);
/*           ZIT=ZOPAL951 */
	} else if (newopac_1.lopal92) {
	    yllo3d_(dl, tl, x, o, ol, qod, qot);
	    zit = newopac_1.zopal1;
	} else if (newopac_1.llaol89) {
	    gtlaol_(dl, tl, x, o, ol, qod, qot);
	    zit = newopac_1.zlaol1;
	}
	slope = (*ol - olz) / (zit - 1.);
	*ol = olz + (*z__ - 1.) * slope;
	*o = pow_dd(&c_b3, ol);
	slope = (*qod - qodz) / (zit - 1.);
	*qod = qodz + (*z__ - 1.) * slope;
	slope = (*qot - qotz) / (zit - 1.);
	*qot = qotz + (*z__ - 1.) * slope;
/*      ELSE */
    } else if (*z__ > .12 || (d__1 = *z__ - comp_1.zenv, abs(d__1)) > 
	    optab_1.optol && ! newopac_1.l2z && ! newopac_1.lopal95) {
	io___17.ciunit = luout_1.ishort;
	s_wsle(&io___17);
	do_lio(&c__9, &c__1, " Z>0.12 T < 5 X 10^7 K", (ftnlen)22);
	do_lio(&c__9, &c__1, " OUTSIDE OPAL OPACITY TABLE RANGE OR Z", (
		ftnlen)38);
	do_lio(&c__9, &c__1, " OUTSIDE SINGLE TABLE USED.Z,ZENV,LOG T=", (
		ftnlen)40);
	do_lio(&c__5, &c__1, (char *)&(*z__), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&comp_1.zenv, (ftnlen)sizeof(doublereal))
		;
	do_lio(&c__5, &c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	e_wsle();
	s_stop("", (ftnlen)0);

/*     NOT HELIUM BURNING REGION (HB EVOLUTION) OR L2Z=T AND */
/*     Z STILL NOT TOO LARGE IN CORE (<.15) SO CAN USE */
/*     SECOND Z TABLE RATHER THAN PURE Z TABLE */

/*      IF (LOPAL95) THEN */
    } else if (newopac_1.lopal95) {
	getopal95_(dl, tl, x, z__, o, ol, qod, qot);
    } else if (newopac_1.lopal92) {
	yllo3d_(dl, tl, x, o, ol, qod, qot);
	if (newopac_1.l2z) {
	    yllo3d2_(dl, tl, x, &o1, &ol1, &qod1, &qot1);
	    slope = (*ol - ol1) / (newopac_1.zopal1 - newopac_1.zopal2);
	    *ol = ol1 + (*z__ - newopac_1.zopal2) * slope;
	    *o = pow_dd(&c_b3, ol);
	    slope = (*qod - qod1) / (newopac_1.zopal1 - newopac_1.zopal2);
	    *qod = qod1 + (*z__ - newopac_1.zopal2) * slope;
	    slope = (*qot - qot1) / (newopac_1.zopal1 - newopac_1.zopal2);
	    *qot = qot1 + (*z__ - newopac_1.zopal2) * slope;
	}
    } else if (newopac_1.llaol89) {
	gtlaol_(dl, tl, x, o, ol, qod, qot);
	if (newopac_1.l2z) {
	    gtlaol2_(dl, tl, x, &o1, &ol1, &qod1, &qot1);
	    slope = (*ol - ol1) / (newopac_1.zlaol1 - newopac_1.zlaol2);
	    *ol = ol1 + (*z__ - newopac_1.zlaol2) * slope;
	    *o = pow_dd(&c_b3, ol);
	    slope = (*qod - qod1) / (newopac_1.zlaol1 - newopac_1.zlaol2);
	    *qod = qod1 + (*z__ - newopac_1.zlaol2) * slope;
	    slope = (*qot - qot1) / (newopac_1.zlaol1 - newopac_1.zlaol2);
	    *qot = qot1 + (*z__ - newopac_1.zlaol2) * slope;
	}
/* MHP 7/12 INSERT FINAL TRAP - NO OPACITY COMPUTED */
/* SHOULD NOT BE ABLE TO GET HERE. */
    } else {
	io___22.ciunit = luout_1.ishort;
	s_wsle(&io___22);
	do_lio(&c__9, &c__1, "NO OPACITY TABLE CHOSEN", (ftnlen)23);
	do_lio(&c__9, &c__1, " RUN STOPPED. X Z TL=", (ftnlen)21);
	do_lio(&c__5, &c__1, (char *)&(*x), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&(*z__), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	e_wsle();
	s_stop("", (ftnlen)0);
    }
/*      END IF */

L1000:
/*     DO A RAMP BETWEEN SURFACE AND INTERIOR OPACITY */
    if (lgotatm && *tl <= newopac_1.tmolmax) {
	if (*tl >= newopac_1.tmolmin) {
/*             RR = DL - 3.0D0*(TL-6.0D0) */
/*             WRITE(*,*)RR,TL,OL,SOL */
	    rmpwt = (*tl - newopac_1.tmolmin) / (newopac_1.tmolmax - 
		    newopac_1.tmolmin);
	    *o = rmpwt * *o + (1. - rmpwt) * so;
	    *ol = d_lg10(o);
	    *qod = rmpwt * *qod + (1. - rmpwt) * sqod;
	    *qot = rmpwt * *qot + (1. - rmpwt) * sqot;
	} else {
	    *o = so;
	    *ol = sol;
	    *qod = sqod;
	    *qot = sqot;
	}
    }
/*     DO CONDUCTIVE OPACITY CORRECTION */
    if (miscopac_1.lcondopacp) {
/* Get Potekhin conductive opacity */
	condopacpint_(dl, tl, x, z__, &oc, &ocl, &qodc, &qotc, &fxion[1], &
		lcondo);
    } else {
	lcondo = FALSE_;
    }
    if (! lcondo) {
/* If we get here we have no Potekhin opacity, so we */
/* try for Hubbard Lampe */
	if (*tl < 4.2) {
	    return 0;
	} else if (*dl < *tl * 2. - 13.) {
	    return 0;
	} else {
/* Do Hubbard Lampe conductive opacity calculation */
	    d__1 = 1. - *x * .6;
	    cond = d_lg10(&d__1) - 14.6196 - (*dl * .1386 + 3.5853) * *dl + (
		    5.1324 - *tl * .3219) * *tl + *dl * .3901 * *tl;
	    oc = pow_dd(&c_b3, &cond);
	    qodc = *tl * .3901 - *dl * .2772 - 3.5853;
	    qotc = *dl * .3901 - *tl * .6438 + 5.1324;
	}
    }
    ox = *o;
/* Save the radiative opacity stuff */
    qodx = *qod;
    qotx = *qot;
/* Add the opacities apppropriately */
    *o = ox * oc / (ox + oc);
/* e.g. 1/O = 1/OX + 1/OC */
    *ol = d_lg10(o);
    *qod = qodx + qodc - (ox * qodx + oc * qodc) / (ox + oc);
    *qot = qotx + qotc - (ox * qotx + oc * qotc) / (ox + oc);
    return 0;
} /* getopac_ */


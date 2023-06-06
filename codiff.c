/* codiff.f -- translated by f2c (version 20100827).
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
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal alm[5000], delami[5000], delmi[5000], dm[5000], epsilm[5000], 
	    hgm[5000], hs3[5000], pm[5000], qdtm[5000], rm[5000], tm[5000];
} intvar_;

#define intvar_1 intvar_

struct {
    doublereal amum[5000], thdifm[5000], viscm[5000], wm[5000];
} intvr2_;

#define intvr2_1 intvr2_

struct {
    doublereal hamu[5000], cp[5000], delm[5000], delam[5000], delrm[5000], 
	    sesum[5000], om[5000], sqdt[5000], thdif[5000], svel[5000], visc[
	    5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    doublereal ves[5000], ves0[5000], vss[5000], vss0[5000], hle[5000], vgsf[
	    5000], vgsf0[5000], vmu[5000];
} temp2_;

#define temp2_1 temp2_

struct {
    doublereal fw, fc, fo, fes, fgsf, fmu, fss, rcrit;
} vmult_;

#define vmult_1 vmult_

struct {
    doublereal fesc, fssc, fgsfc;
    integer ies, igsf, imu;
} vmult2_;

#define vmult2_1 vmult2_

struct {
    doublereal fadv[5000], fadv0[5000];
} advec_;

#define advec_1 advec_

struct {
    doublereal vfc[5000];
    logical lvfc, ldifad;
} varfc_;

#define varfc_1 varfc_

struct {
    logical lnoj;
} notran_;

#define notran_1 notran_

/* $$$$$$ */
/* Subroutine */ int codiff_(doublereal *delts, doublereal *hru, doublereal *
	hv, integer *imin, integer *imax, logical *lc, logical *lcz, integer *
	m, doublereal *rmid, doublereal *cod, doublereal *cod2)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal con1, con2;

/* 2/91 SUBROUTINE ALTERED TO ALLOW DIFFERENT FC'S FOR DIFFERENT */
/*      MECHANISMS (COMMON BLOCK VMULT2) */
/* MHP 9/93 */
/*  THIS SR DETERMINES THE RUN OF CHARACTERISTIC VELOCITY LENGTH */
/*  SCALES FOR THE DIFFUSION EQUATIONS. */

/*  INPUT VARIABLES */

/*       DECLARED: */
/*  HRU : RUN OF RADIUS (UNLOGGED) OF THE MIDPOINTS OF THE SHELLS. */
/*  M : NUMBER OF SHELLS. */
/*  HV : RUN OF CHARACTERISTIC DIFFUSION VELOCITIES. */
/*  LC : FLAG SET T IF ZONE IS CONVECTIVE. */
/*  LCZ : FLAG SET T IF ZONE IS CONVECTIVE FOR ANGULAR MOMENTUM */
/*        TRANSPORT PURPOSES(I.E. INCLUDES OVERSHOOT REGIONS). */
/*  M : NUMBER OF SHELLS. */
/*  FC,FO,FW : USER PARAMETERS.  THE DIFFUSION COEFFICIENTS */
/*  CAN BE MODIFIED BY THESE THREE PARAMETERS. */
/*  SVEL : RUN OF CONVECTIVE VELOCITIES. */

/*  OUTPUT VARIABLES */

/*       DECLARED */
/*  COD : RUN OF DIFFUSION COEFFICENTS FOR ANGULAR MOMENTUM TRANSPORT. */
/*  COD2 : SAME, WITH RESPECT TO COMPOSITION TRANSPORT. */
/*  RMID : RMID(I) IS DEFINED AS THE AVERAGE OF HRU(I) AND HRU(I-1). */
/*       FROM COMMON BLOCKS: */
/*       IN COMMON BLOCKS */
/*  HLE : RUN OF CHARACTERSITIC VELOCITY LENGTH SCALES. */

/*  NOTE ON STORAGE: COD,V, AND HLE ARE CALCULATED AT THE MIDPOINT */
/*  BETWEEN MASS POINTS. ELEMENT I CONTAINS THE INFORMATION FOR THE */
/*  (I,I-1) INTERFACE. */
    /* Parameter adjustments */
    --cod2;
    --cod;
    --rmid;
    --lcz;
    --lc;
    --hv;
    --hru;

    /* Function Body */
    temp2_1.hle[0] = 0.;
    rmid[1] = 0.;
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
	temp2_1.hle[i__ - 1] = 0.;
	rmid[i__] = (hru[i__] + hru[i__ - 1]) * .5;
    }
    if (! varfc_1.lvfc) {
	con1 = const1_1.c4pi * vmult_1.fw;
	con2 = con1 * vmult_1.fc;
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    cod[i__] = con1 * (temp2_1.ves[i__ - 1] + temp2_1.vgsf[i__ - 1] + 
		    temp2_1.vss[i__ - 1]) * rmid[i__];
	    cod2[i__] = con2 * (vmult2_1.fesc * temp2_1.ves[i__ - 1] + 
		    vmult2_1.fgsfc * temp2_1.vgsf[i__ - 1] + vmult2_1.fssc * 
		    temp2_1.vss[i__ - 1]) * rmid[i__];
	    temp2_1.hle[i__ - 1] = rmid[i__];
	}
    } else {
	con1 = const1_1.c4pi * vmult_1.fw;
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    cod[i__] = con1 * (temp2_1.ves[i__ - 1] + temp2_1.vgsf[i__ - 1] + 
		    temp2_1.vss[i__ - 1]) * rmid[i__];
	    cod2[i__] = cod[i__] * varfc_1.vfc[i__ - 1];
	    temp2_1.hle[i__ - 1] = rmid[i__];
	}
    }
    if (notran_1.lnoj) {
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    cod[i__] = 0.;
	}
    }
    return 0;
} /* codiff_ */


/* mdot.f -- translated by f2c (version 20100827).
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
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal drate[5000], drate0[5000], fmassacc, taucz;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal sage, tdisk, pdisk;
    logical ldisk;
} disk_;

#define disk_1 disk_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal dmdt0, fczdmdt, ftotdmdt, compacc[15], creim;
    logical lreimer, lmdot;
} masschg_;

#define masschg_1 masschg_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal sacc, scen, smass0, dlogp, dlogt;
} masschg2_;

#define masschg2_1 masschg2_

/* Table of constant values */

static doublereal c_b3 = 10.;
static integer c__1 = 1;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MASS LOSS ROUTINE */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mdot_(doublereal *delts, doublereal *hcomp, doublereal *
	hd, doublereal *hjm, doublereal *hp, doublereal *hr, doublereal *hs, 
	doublereal *hs1, doublereal *hs2, doublereal *hstot, doublereal *ht, 
	integer *jenv, logical *lnew, integer *m, doublereal *omega, 
	doublereal *rmu, doublereal *rtot, doublereal *smass, doublereal *
	dmdt, doublereal *eacc, doublereal *ethav, doublereal *sumdm, 
	doublereal *senvold)
{
    /* Format strings */
    static char fmt_10[] = "(\002 TIMESTEP REDUCED FOR MASS LOSS - OLD,NE"
	    "W\002,1p2e12.3)";
    static char fmt_20[] = "(\002MASS LOSS APPLIED - NEW M,DEL M\002,1p2e13."
	    "4)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double d_lg10(doublereal *);

    /* Local variables */
    static doublereal d__;
    static integer i__, j;
    static doublereal p, t, rb, fx, fac, beta, facr, delj, delm, dlnm, rate, 
	    dmcz, dtcz, rnew, test, abund;
    static logical ldone;
    static doublereal dtmax, dtenv, dmczt, dlogr, cjtot, rinit, surfi, dttot, 
	    cjnew, ratio, dmsun, wsurf, hstot1, hstot2, dlogen, ethnew;

    /* Fortran I/O blocks */
    static cilist io___8 = { 0, 6, 0, fmt_10, 0 };
    static cilist io___35 = { 0, 6, 0, fmt_20, 0 };


    /* Parameter adjustments */
    --omega;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hjm;
    --hd;
    hcomp -= 16;

    /* Function Body */
    *senvold = hs[*m] - *hstot;
/*      LMDOT = .TRUE. */
/*      DMDT = 4.0D-10 */
/* MAXIMUM FRACTION OF CZ MASS REMOVED PER TIMESTEP */
/*      FRAC = 0.1D0 */
/*      IF(.NOT.LMDOT)GOTO 9999 */
/* CONVERT FROM SOLAR MASSES/YEAR TO GM/SEC */
    rate = abs(*dmdt) * const_1.cmsun / const3_1.csecyr;
/* THE SUM OF THE MASSES OF ALL SHELLS (E.G. TO JENV - 1) */
/* SHOULD BE USED RATHER THAN THE SUM OF THE MASSES DOWN */
/* TO THE MIDPOINT OF THE BOTTOM SHELL */
/*      DMCZT = 10.0D0**HSTOT - HS1(JENV) */
    dmczt = *sumdm;
/* COMPUTE MASS OF SURFACE CONVECTION ZONE BELOW FITTING POINT */
    if (*jenv == *m) {
	s_stop("911", (ftnlen)3);
    }
    if (*jenv > 1) {
	dmcz = hs1[*m] - hs1[*jenv];
    } else {
	dmcz = hs1[*m];
    }
/* COMPUTE MAXIMUM TIMESTEP BASED ON NOT REMOVING TOO MUCH MASS FROM THE */
/* SURFACE CZ (FCZDMDT) OR AS A FRACTION OF THE TOTAL MASS (FTOTDMDT) */
    dttot = masschg_1.ftotdmdt * *smass * const_1.cmsun / rate;
    dtcz = masschg_1.fczdmdt * dmcz / rate;
    dtmax = min(dttot,dtcz);
/* RESTRICT TIMESTEP TO ADD NO MORE THAN 1/2 OF THE CURRENT MASS */
/* BEYOND THE FITTING POINT TO THE STAR. */
    if (rate > 0.) {
	dtenv = (pow_dd(&c_b3, hstot) - pow_dd(&c_b3, &hs[*m])) * .5 / rate;
	dtmax = min(dtmax,dtenv);
    }
    if (dtmax < *delts) {
	s_wsfe(&io___8);
	do_fio(&c__1, (char *)&(*delts), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&dtmax, (ftnlen)sizeof(doublereal));
	e_wsfe();
	*delts = dtmax;
    }
    if (disk_1.ldisk) {
	test = disk_1.sage + *delts * 1e-9 / const3_1.csecyr;
	if (test > disk_1.tdisk) {
	    *delts = (disk_1.tdisk - disk_1.sage) * 1e9 * const3_1.csecyr;
	    ldone = TRUE_;
	} else {
	    ldone = FALSE_;
	}
    } else {
	ldone = FALSE_;
    }
/* FINAL AMOUNT OF MASS LOSS INFERRED IN CGS UNITS. */
    delm = *dmdt * const_1.cmsun * *delts / const3_1.csecyr;
/* COMPUTE THE MEAN THERMAL ENERGY */
/* CONTENT OF THE CONVECTION ZONE FOR MODELS WITH ACCRETION. */
    if (delm > 0.) {
	ethnew = (*eacc * delm + *ethav * *sumdm) / (delm + *sumdm);
	d__1 = ethnew / *ethav;
	fac = d_lg10(&d__1);
/*         WRITE(*,912) JENV,EACC,ETHAV,ETHNEW,FAC,SUMDM,DELM */
/* 912     FORMAT(I5,1P6E12.3) */
/* OVERALL SCALE FACTOR IN R */
	t = pow_dd(&c_b3, &ht[*jenv]);
	p = pow_dd(&c_b3, &hp[*jenv]);
	d__ = pow_dd(&c_b3, &hd[*jenv]);
/* Computing 4th power */
	d__1 = t, d__1 *= d__1;
	beta = 1. - const2_1.ca3 * (d__1 * d__1) / p;
	*rmu = p * beta / (d__ * t);
/*         DLOGEN = (DELM/DMCZ)*(SACC-SCEN)/RMU */
	dlogen = delm / dmcz * masschg2_1.scen / *rmu;
/*         DLNM = LOG(DMCZ+DELM)-LOG(DMCZ) */
	dlnm = 0.;
	dlogr = (const1_1.cc23 * dlogen - const1_1.cc13 * dlnm) / 
		const1_1.cln;
	masschg2_1.dlogt = dlnm / const1_1.cln - dlogr;
	masschg2_1.dlogp = dlnm * 2. / const1_1.cln - dlogr * 4.;
/*         WRITE(*,*)DLOGR,DLOGP,DLOGT */
	if (*jenv == 1) {
	    i__1 = *m;
	    for (j = *jenv; j <= i__1; ++j) {
		hr[j] += dlogr;
		hp[j] += masschg2_1.dlogp;
		ht[j] += masschg2_1.dlogt;
	    }
	} else {
	    hp[*jenv] += masschg2_1.dlogp;
	    ht[*jenv] += masschg2_1.dlogt;
	    rb = pow_dd(&c_b3, &hr[*jenv]);
	    facr = pow_dd(&c_b3, &dlogr);
	    i__1 = *m;
	    for (j = *jenv + 1; j <= i__1; ++j) {
		rinit = pow_dd(&c_b3, &hr[j]);
		rnew = rb + facr * (rinit - rb);
		hr[j] = d_lg10(&rnew);
	    }
	}
/*         DO J = JENV,M */
/*            HT(J) = HT(J) + FAC */
/*         END DO */
/*         WRITE(*,*)HT(15),HT(16),HT(17) */
    }
/* FOR MODELS WITH ROTATION AND MASS LOSS REMOVE ANGULAR MOMENTUM. */
/* IN THIS CASE WE ASSUME A THERMAL WIND WHERE THE SURFACE MATTER */
/* CARRIES AWAY ONLY ITS LOCAL ANGULAR MOMENTUM PER UNIT MASS. */
    if (rot_1.lrot && delm < 0.) {
/* MOMENT OF INERTIA PER UNIT MASS AT THE SURFACE. */
/* Computing 2nd power */
	d__1 = *rtot;
	surfi = d__1 * d__1 * .66666666666666663;
	if (rot_1.walpcz >= 0.) {
/* SOLID BODY CZ ROTATION */
	    delj = omega[*m] * surfi * delm;
	} else if (rot_1.walpcz <= -2.) {
/* CONSTANT J/M */
	    delj = hjm[*m] * delm;
	} else {
	    d__1 = hr[*m] * rot_1.walpcz;
	    wsurf = omega[*m] * pow_dd(&c_b3, &d__1) / pow_dd(rtot, &
		    rot_1.walpcz);
	    delj = wsurf * surfi * delm;
	}
/*  FIND TOTAL STARTING ANGULAR MOMENTUM OF C.Z. */
	cjtot = hjm[*jenv] * hs2[*jenv];
	i__1 = *m;
	for (j = *jenv + 1; j <= i__1; ++j) {
	    cjtot += hjm[j] * hs2[j];
	}
	cjnew = (cjtot + delj) / (dmczt + delm);
	ratio = cjnew / cjtot;
	i__1 = *m;
	for (j = *jenv; j <= i__1; ++j) {
	    hjm[j] *= ratio;
	}
    }
/* REMOVE OR ADD MASS IN THE CONVECTION ZONE. */
/* HS1 IS THE LOCATION OF THE ZONE CENTERS IN GM; */
/* HS IS THE BASE-10 LOG OF HS1 */
    if (delm < 0.) {
	fx = (dmcz + delm) / dmcz;
/*      WRITE(*,*)JENV,M,DMCZ,DELM,FX,HS1(M),HS(M) */
	i__1 = *m;
	for (i__ = *jenv + 1; i__ <= i__1; ++i__) {
	    hs1[i__] = hs1[*jenv] + fx * (hs1[i__] - hs1[*jenv]);
	    hs[i__] = d_lg10(&hs1[i__]);
	}
    }
/*      WRITE(*,*)HS1(M),HS(M) */
/* CORRECT TOTAL MASS IN SOLAR UNITS (SMASS) AND */
/* LOG OF TOTAL MASS IN GRAMS (HSTOT,STOTAL) */
    *smass += delm / const_1.cmsun;
    masschg2_1.smass0 = *smass;
    dmsun = delm / const_1.cmsun;
    s_wsfe(&io___35);
    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&dmsun, (ftnlen)sizeof(doublereal));
    e_wsfe();
    hstot1 = pow_dd(&c_b3, hstot);
    hstot2 = hstot1 + delm;
    *hstot = d_lg10(&hstot2);
    comp_1.stotal = *hstot;
/* CORRECT MASS CONTENTS OF INDIVIDUAL SHELLS (HS2, IN GM) */
    i__1 = *m - 1;
    for (i__ = *jenv; i__ <= i__1; ++i__) {
	hs2[i__] = (hs1[i__ + 1] - hs1[i__ - 1]) * .5;
    }
    hs2[*m] = hstot2 - (hs1[*m] + hs1[*m - 1]) * .5;
/* 07/02RESET SENV */
    comp_1.senv = hs[*m] - *hstot;
/* RECOMPUTE SURFACE BOUNDRY CONDITION */
    *lnew = TRUE_;
/* REMIX THE SURFACE CONVECTION ZONE IF MDOT IS POSITIVE. */
/*      WRITE(*,911)DELM,DMCZT,COMPACC(12),HCOMP(12,M), */
/*     *            COMPACC(4),HCOMP(4,M) */
/* 911  FORMAT(1P6E12.3) */
    if (delm > 0.) {
	for (i__ = 1; i__ <= 11; ++i__) {
	    abund = (hcomp[i__ + *jenv * 15] * dmczt + masschg_1.compacc[i__ 
		    - 1] * delm) / (delm + dmczt);
	    i__1 = *m;
	    for (j = *jenv; j <= i__1; ++j) {
		hcomp[i__ + j * 15] = abund;
	    }
	}
	deuter_1.fmassacc = delm;
    }
/* L9999: */
    if (ldone) {
	masschg_1.lmdot = FALSE_;
    }
/*      WRITE(*,*)M,HS(M),HSTOT */
    return 0;
} /* mdot_ */


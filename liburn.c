/* liburn.f -- translated by f2c (version 20100827).
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal rli6[5000], rli7[5000], rbe9[5000];
} newrat_;

#define newrat_1 newrat_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
} oldmod_;

#define oldmod_1 oldmod_

struct {
    doublereal rli60[5000], rli70[5000], rbe90[5000];
} oldrat_;

#define oldrat_1 oldrat_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal dpenv, alphac, alphae, alpham;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    doublereal pscal0, pscal1;
} liov_;

#define liov_1 liov_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal amum[5000], cpm[5000], delm[5000], delam[5000], delrm[5000], 
	    esumm[5000], om[5000], qdtm[5000], thdifm[5000], velm[5000], 
	    viscm[5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    doublereal rbase0, bli6old, bli7old, bbe9old;
    integer jenvos;
} prevcz_;

#define prevcz_1 prevcz_

struct {
    doublereal drate[5000], drate0[5000], fmassacc, taucz;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal dmdt0, fczdmdt, ftotdmdt, compacc[15], creim;
    logical lreimer, lmdot;
} masschg_;

#define masschg_1 masschg_

/* Table of constant values */

static integer c__3 = 3;
static integer c__7 = 7;
static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* LIBURN */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* 11/91 HR ADDED TO CALL. */
/* Subroutine */ int liburn_(doublereal *delts, doublereal *hcomp, doublereal 
	*hd, doublereal *hr, doublereal *hs1, doublereal *hs2, doublereal *ht,
	 integer *jnenv, integer *jnenv0, integer *m)
{
    /* Initialized data */

    static integer nstepe[11] = { 2,4,6,8,12,16,24,32,48,64,96 };
    static doublereal ytol[3] = { 1e-6,1e-6,1e-6 };

    /* Format strings */
    static char fmt_911[] = "(1x,\002***LIBURN CONVERGENCE FAILURE IN SHELL"
	    " \002,i4,\002ERRORS \002/1p3e10.3)";
    static char fmt_913[] = "(1p7e12.3)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal), log(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j, k;
    static doublereal r__;
    static integer k2;
    static doublereal fm, dr, dt, fx, fm0, ddj, ros, bbe9, dbe9, fbe9, bli6, 
	    bli7, dli6, fli6, fli7, tbe9, dli7, tli6, tli7, bbe90, fbe90, 
	    frac, bli60, bli70, frad, fli60, fli70;
    static integer minj;
    static doublereal hsav[15000]	/* was [3][5000] */;
    static integer jenv, maxj;
    static doublereal yerr[3], yest[3], xest, fbe9a, yext[3], ddjm1, fli6a, 
	    fli7a, czbe9;
    static integer jenv0;
    static doublereal czli6, czli7, hsbeg, rbase;
    static logical ldone;
    static doublereal hsend, dmass, ratbe9[5000], ratli6[5000], ratli7[5000], 
	    hs2sav;
    static logical ldoacc;
    static doublereal fbe9add;
    extern /* Subroutine */ int ratext_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *);
    static doublereal fli6add, fli7add;

    /* Fortran I/O blocks */
    static cilist io___33 = { 0, 0, 0, fmt_911, 0 };
    static cilist io___62 = { 0, 6, 0, fmt_913, 0 };
    static cilist io___63 = { 0, 0, 0, fmt_911, 0 };


/* MHP 10/91 COMMON BLOCK ADDED FOR OVERSHOOT. */
/* MHP 11/91 COMMON BLOCK ADDED FOR OVERSHOOT. */
/* MHP 11/91 COMMON BLOCKS ADDED FOR LITHIUM BURNING IN ROTATING */
/* MODELS WITH LINSTB=T. */
/* 11/91 COMMON BLOCK ADDED FOR THE EXACT LOCATION OF THE BASE OF THE */
/* SURFACE CZ AND THE INTEGRATED BURNING RATES THROUGHOUT IT. USED TO */
/* REMEMBER THE PREVIOUS "END OF TIMESTEP VALUES" FOR THE NEW */
/* "BEGINNING OF TIMESTEP VALUES". */
/* MHP 05/02 INCLUDE MASS ACCRETION AND ITS EFFECT ON ABUNDANCES */
    /* Parameter adjustments */
    --ht;
    --hs2;
    --hs1;
    --hr;
    --hd;
    hcomp -= 16;

    /* Function Body */
/* DETERMINE LITHIUM AND BERYLLIUM BURNING IN A NON-ROTATING MODEL. */
/* THE BURNING RATES DEPEND ON THE LOCAL T AND RHO, THE ABUNDANCE, AND */
/* IN THE CASE OF CONVECTION ZONES THE MIXING. */

/* IN RADIATIVE REGIONS BURNING IS DONE IMPLICITLY, CORRECTING THE RATES FOR THE */
/* CHANGE IN ABUNDANCE AS A FUNCTION OF TIME. */

/* IN CONVECTIVE REGIONS THE PROGRAM ITERATES BETWEEN BURNING AND MIXING */
/* TO CORRECT THE RATES FOR THE CHANGE IN ABUNDANCE AS A FUNCTION OF TIME. */

/* SAVE ORIGINAL ABUNDANCES. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hsav[i__ * 3 - 3] = hcomp[i__ * 15 + 13];
	hsav[i__ * 3 - 2] = hcomp[i__ * 15 + 14];
	hsav[i__ * 3 - 1] = hcomp[i__ * 15 + 15];
/* L10: */
    }
/* THE DEGREE OF LITHIUM BURNING IN A SURFACE CZ DEPENDS SENSITIVELY */
/* ON THE TEMPERATURE AT ITS BASE - SO ACCURATELY LOCATING IS IMPORTANT. */
/* DETERMINE THE TRUE LOCATION (FX) OF THE BASE OF THE CZ AT THE END */
/* OF THE TIMESTEP, AND THE LOCATION OF THE EDGE OF OVERSHOOT REGIONS */
/* IF APPLICABLE. */
    if (*jnenv > 1 && *jnenv < *m) {
	if (rot_1.lrot && rot_1.linstb) {
	    ddj = mdphy_1.delam[*jnenv - 1] - mdphy_1.delrm[*jnenv - 1];
	    ddjm1 = mdphy_1.delam[*jnenv - 2] - mdphy_1.delrm[*jnenv - 2];
	} else {
/* EVALUATE DEL(AD) - DEL(RAD) AT THE LAST CONVECTIVE POINT AND THE ONE */
/* BELOW IT. */
	    ddj = scrtch_1.sdel[*jnenv * 3 - 1] - scrtch_1.sdel[*jnenv * 3 - 
		    3];
	    ddjm1 = scrtch_1.sdel[(*jnenv - 1) * 3 - 1] - scrtch_1.sdel[(*
		    jnenv - 1) * 3 - 3];
	}
/* USE LINEAR INTERPOLATION TO FIND THE DISTANCE OF THE TRUE LOCATION */
/* OF THE BASE FROM THE ZONE MIDPOINT. IF FX IS NEGATIVE,THEN THE TRUE */
/* BASE IS HIGHER; IF IT IS POSITIVE, THE TRUE BASE IS LOWER. */
/* Computing MAX */
	d__1 = -.5, d__2 = .5 - ddjm1 / (ddjm1 - ddj);
	fx = max(d__1,d__2);
	fx = min(.5,fx);
	if (! dpmix_1.lovste) {
	    jenv = *jnenv;
	    jenv0 = *jnenv0;
	} else {
/* STARTING CZ DEPTH */
	    if (prevcz_1.rbase0 == 0.) {
		prevcz_1.rbase0 = (exp(const1_1.cln * oldmod_1.hro[*jnenv0 - 
			1]) + exp(const1_1.cln * oldmod_1.hro[*jnenv0 - 2])) *
			 .5;
		ros = prevcz_1.rbase0 - liov_1.pscal0;
		for (j = *jnenv0 - 1; j >= 1; --j) {
		    r__ = exp(const1_1.cln * oldmod_1.hro[j - 1]);
		    if (r__ < ros) {
			jenv0 = j + 1;
			goto L11;
		    }
		}
		jenv0 = 1;
L11:
		;
	    } else {
		jenv0 = prevcz_1.jenvos;
	    }
/* ENDING CZ DEPTH : DETERMINE OVERSHOOT FROM TRUE CZ BASE. */
	    dr = exp(const1_1.cln * hr[*jnenv]) - exp(const1_1.cln * hr[*
		    jnenv - 1]);
	    rbase = (exp(const1_1.cln * hr[*jnenv]) + exp(const1_1.cln * hr[*
		    jnenv - 1])) * .5 - fx * dr;
	    prevcz_1.rbase0 = rbase;
	    ros = rbase - liov_1.pscal1;
	    for (j = *jnenv - 1; j >= 1; --j) {
		r__ = exp(const1_1.cln * hr[j]);
		if (r__ < ros) {
		    jenv = j + 1;
		    dr = exp(const1_1.cln * oldmod_1.hro[j]) - r__;
		    fx = .5 - (ros - r__) / dr;
		    fx = max(-.5,fx);
		    fx = min(.5,fx);
		    goto L12;
		}
	    }
	    jenv = 1;
L12:
	    ;
	}
    } else {
	jenv = *jnenv;
	jenv0 = *jnenv0;
    }
    prevcz_1.jenvos = jenv;
/* RADIATIVE INTERIOR. */
    minj = min(jenv,jenv0);
    maxj = max(jenv,jenv0);
    i__1 = minj - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (newrat_1.rbe9[i__ - 1] <= 1e-32 || oldrat_1.rbe90[i__ - 1] <= 
		1e-32) {
	    goto L60;
	}
	if (hcomp[i__ * 15 + 13] < 1e-24 && hcomp[i__ * 15 + 14] < 1e-24 && 
		hcomp[i__ * 15 + 15] < 1e-24) {
	    goto L50;
	}
	if (ht[i__] > 7.) {
	    hcomp[i__ * 15 + 13] = 0.;
	    hcomp[i__ * 15 + 14] = 0.;
	    hcomp[i__ * 15 + 15] = 0.;
	    goto L50;
	}
	for (j = 1; j <= 11; ++j) {
/* PERFORM BURNING IN NSTEPE SMALLER TIMESTEPS. */
/*  DEFINE FRAC - THE FRACTION OF THE TOTAL TIMESTEP IN EACH SMALL ONE - */
/*  AND DELT - THE FRACTIONAL TIMESTEP IN YEARS. */
	    frac = 1. / (doublereal) nstepe[j - 1];
	    dt = frac * *delts;
	    ldone = FALSE_;
/* RESTORE INITIAL ABUNDANCES. */
	    hcomp[i__ * 15 + 13] = hsav[i__ * 3 - 3];
	    hcomp[i__ * 15 + 14] = hsav[i__ * 3 - 2];
	    hcomp[i__ * 15 + 15] = hsav[i__ * 3 - 1];
/* STORE STARTING REACTION RATES. */
	    tli6 = log(oldrat_1.rli60[i__ - 1]) - frac * .5 * (log(
		    newrat_1.rli6[i__ - 1]) - log(oldrat_1.rli60[i__ - 1]));
	    tli7 = log(oldrat_1.rli70[i__ - 1]) - frac * .5 * (log(
		    newrat_1.rli7[i__ - 1]) - log(oldrat_1.rli70[i__ - 1]));
	    tbe9 = log(oldrat_1.rbe90[i__ - 1]) - frac * .5 * (log(
		    newrat_1.rbe9[i__ - 1]) - log(oldrat_1.rbe90[i__ - 1]));
	    i__2 = nstepe[j - 1];
	    for (k = 1; k <= i__2; ++k) {
/* INCREMENT THE REACTION RATES. */
		tli6 += frac * (log(newrat_1.rli6[i__ - 1]) - log(
			oldrat_1.rli60[i__ - 1]));
		tli7 += frac * (log(newrat_1.rli7[i__ - 1]) - log(
			oldrat_1.rli70[i__ - 1]));
		tbe9 += frac * (log(newrat_1.rbe9[i__ - 1]) - log(
			oldrat_1.rbe90[i__ - 1]));
		ratli6[i__ - 1] = dt * exp(tli6);
		ratli7[i__ - 1] = dt * exp(tli7);
		ratbe9[i__ - 1] = dt * exp(tbe9);
/* THE REACTION RATES ARE OF THE FORM */
/*    DLI/DT = F(RHO,T,X)*LI =>DLN LI = DT*F(RHO,T,X) */
/* SOLVE FOR D LN (SPECIES)/DT AND ZERO OUT IF THE DEPLETION IS TOO HIGH. */
		if (ratli6[i__ - 1] < 30.) {
		    hcomp[i__ * 15 + 13] /= exp(ratli6[i__ - 1]);
		} else {
		    hcomp[i__ * 15 + 13] = 0.;
		}
		if (ratli7[i__ - 1] < 30.) {
		    hcomp[i__ * 15 + 14] /= exp(ratli7[i__ - 1]);
		} else {
		    hcomp[i__ * 15 + 14] = 0.;
		}
		if (ratbe9[i__ - 1] < 30.) {
		    hcomp[i__ * 15 + 15] /= exp(ratbe9[i__ - 1]);
		} else {
		    hcomp[i__ * 15 + 15] = 0.;
		}
/* L20: */
	    }
/* STORE ABUNDANCES AS A FUNCTION OF TIMESTEP IN VECTOR YEST. */
	    yest[0] = hcomp[i__ * 15 + 13];
	    yest[1] = hcomp[i__ * 15 + 14];
	    yest[2] = hcomp[i__ * 15 + 15];
/* Computing 2nd power */
	    d__1 = frac;
	    xest = d__1 * d__1;
/* USE A RATIONAL POLYNOMIAL EXTRAPOLATOR TO EXTRAPOLATE TO THE SOLUTION FOR */
/* ZERO TIMESTEP. */
	    ratext_(&j, &xest, yest, yext, yerr, &c__3, &c__7);
/* CHECK IF THE SOLUTION HAS CONVERGED. */
	    if (j > 1) {
		ldone = TRUE_;
		for (k2 = 1; k2 <= 3; ++k2) {
		    if (yest[k2 - 1] < 1e-24) {
			goto L30;
		    }
		    yerr[k2 - 1] = (d__1 = yerr[k2 - 1] / yest[k2 - 1], abs(
			    d__1));
		    if (yerr[k2 - 1] > ytol[k2 - 1]) {
			ldone = FALSE_;
		    }
L30:
		    ;
		}
		if (ldone) {
/*                 WRITE(ISHORT,912)I,J,(YEXT(K2)K2=1,3) */
/* L912: */
		    goto L45;
		}
	    }
/* L40: */
	}
/* IF THE PROGRAM GETS HERE THEN IT FAILED TO CONVERGE TO WITHIN */
/* THE SPECIFIED TOLERANCE IN THE MAXIMUM NUMBER OF ITERATIONS. */
	io___33.ciunit = luout_1.ishort;
	s_wsfe(&io___33);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	for (k2 = 1; k2 <= 3; ++k2) {
	    do_fio(&c__1, (char *)&yerr[k2 - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
L45:
/* WRITE NEW ABUNDANCES AND EXIT. */
	hcomp[i__ * 15 + 13] = yext[0];
	if (hcomp[i__ * 15 + 13] < 1e-24) {
	    hcomp[i__ * 15 + 13] = 0.;
	}
	hcomp[i__ * 15 + 14] = yext[1];
	if (hcomp[i__ * 15 + 14] < 1e-24) {
	    hcomp[i__ * 15 + 14] = 0.;
	}
	hcomp[i__ * 15 + 15] = yext[2];
	if (hcomp[i__ * 15 + 15] < 1e-24) {
	    hcomp[i__ * 15 + 15] = 0.;
	}
L50:
	;
    }
L60:
/* CONVECTION ZONE. */

/* SKIP IF WHOLE CZ IS BELOW THE BURNING THRESHOLD. */
    if (oldrat_1.rbe90[jenv0 - 1] <= 1e-32 || newrat_1.rbe9[jenv - 1] <= 
	    1e-32) {
	goto L200;
    }
/* FIND RATES AT THE BEGINNING OF THE TIMESTEP (USING THE DEPTH AT THE START). */
    fli60 = 0.;
    fli70 = 0.;
    fbe90 = 0.;
    fm0 = 0.;
    i__1 = *m;
    for (i__ = jenv0; i__ <= i__1; ++i__) {
	fli60 += hcomp[i__ * 15 + 13] * hs2[i__];
	fli70 += hcomp[i__ * 15 + 14] * hs2[i__];
	fbe90 += hcomp[i__ * 15 + 15] * hs2[i__];
	fm0 += hs2[i__];
/* L65: */
    }
/* L67: */
    fli60 /= fm0;
    fli70 /= fm0;
    fbe90 /= fm0;
    if (prevcz_1.bli6old <= 0.) {
/* COMPUTE MASS-WEIGHTED AVERAGE RATES AT THE START OF THE STEP. */
	bli60 = 0.;
	bli70 = 0.;
	bbe90 = 0.;
	i__1 = *m;
	for (i__ = jenv0; i__ <= i__1; ++i__) {
	    bli60 += oldrat_1.rli60[i__ - 1] * hs2[i__];
	    bli70 += oldrat_1.rli70[i__ - 1] * hs2[i__];
	    bbe90 += oldrat_1.rbe90[i__ - 1] * hs2[i__];
/* L68: */
	}
	bli60 = log(bli60 / fm0);
	bli70 = log(bli70 / fm0);
	bbe90 = log(bbe90 / fm0);
    } else {
/* USE THE RATE FROM THE END OF THE PREVIOUS TIMESTEP. */
	bli60 = prevcz_1.bli6old;
	bli70 = prevcz_1.bli7old;
	bbe90 = prevcz_1.bbe9old;
    }
/* USE THE LOCATION OF THE TRUE EDGE OF THE CONVECTION ZONE (FX, FOUND AT */
/* BEGINNING OF SR) TO ADJUST THE BURNING RATE AND MASS OF THE BOTTOM POINT */
/* SUCH THAT IT INCLUDES THE ENTIRE C.Z. */
    hs2sav = hs2[jenv];
    if (jenv > 1 && jenv < *m) {
	hs2[jenv] += fx * (hs1[jenv] - hs1[jenv - 1]);
	newrat_1.rli6[jenv - 1] += fx * .5 * (newrat_1.rli6[jenv - 2] - 
		newrat_1.rli6[jenv - 1]);
	newrat_1.rli7[jenv - 1] += fx * .5 * (newrat_1.rli7[jenv - 2] - 
		newrat_1.rli7[jenv - 1]);
	newrat_1.rbe9[jenv - 1] += fx * .5 * (newrat_1.rbe9[jenv - 2] - 
		newrat_1.rbe9[jenv - 1]);
    }
/* FIND RATES AT THE END OF THE TIMESTEP (USING THE DEPTH AT THE END). */
/* ALSO STORE INITIAL ABUNDANCES(FLI60,FLI70,FBE90). */
/* FM IS THE TOTAL MASS IN THE CZ. */
    fli6 = 0.;
    fli7 = 0.;
    fbe9 = 0.;
    fm = 0.;
    bli6 = 0.;
    bli7 = 0.;
    bbe9 = 0.;
    i__1 = *m;
    for (i__ = jenv; i__ <= i__1; ++i__) {
	bli6 += newrat_1.rli6[i__ - 1] * hs2[i__];
	bli7 += newrat_1.rli7[i__ - 1] * hs2[i__];
	bbe9 += newrat_1.rbe9[i__ - 1] * hs2[i__];
	fli6 += hcomp[i__ * 15 + 13] * hs2[i__];
	fli7 += hcomp[i__ * 15 + 14] * hs2[i__];
	fbe9 += hcomp[i__ * 15 + 15] * hs2[i__];
	fm += hs2[i__];
/* L70: */
    }
/* L75: */
    fli6 /= fm;
    fli7 /= fm;
    fbe9 /= fm;
/* MASS-WEIGHTED AVERAGE RATES AT THE END OF THE STEP. */
    bli6 = log(bli6 / fm);
    bli7 = log(bli7 / fm);
    bbe9 = log(bbe9 / fm);
/* RESTORE ORIGINAL MASS TO BASE OF C.Z. */
    hs2[jenv] = hs2sav;
/* FOR THE STARTING ABUNDANCE, USE THE MIXED ABUNDANCE FOR THE */
/* DEEPER CZ. */
    if (jenv < jenv0) {
	fli60 = fli6;
	fli70 = fli7;
	fbe90 = fbe9;
    }
    for (j = 1; j <= 11; ++j) {
/* PERFORM BURNING IN NSTEPE SMALLER TIMESTEPS. */
/*  DEFINE FRAC - THE FRACTION OF THE TOTAL TIMESTEP IN EACH SMALL ONE - */
/*  AND DELT - THE FRACTIONAL TIMESTEP IN YEARS. */
	frac = 1. / (doublereal) nstepe[j - 1];
	dt = frac * *delts;
	ldone = FALSE_;
/* INITIALIZE ABUNDANCES. */
	fli6 = fli60;
	fli7 = fli70;
	fbe9 = fbe90;
/* INITIALIZE RATES. */
	czli6 = bli60 - frac * .5 * (bli6 - bli60);
	czli7 = bli70 - frac * .5 * (bli7 - bli70);
	czbe9 = bbe90 - frac * .5 * (bbe9 - bbe90);
/* BURN IN NSTEPE SMALL TIMESTEPS. */
/* MHP 05/02 ADDED THE IMPACT OF MASS ACCRETION ON LIGHT */
/* ELEMENT ABUNDANCES.  INITIALIZE ARRAYS; SPECIES ARE */
/* ASSUMED TO EXPERIENCE BURNING FOR ON AVERAGE 1/2 OF */
/* THE STEP WHERE THEY ARE INITIALLY ACCRETED AND ARE */
/* THEN FULLY BURNED. */
	if (masschg_1.lmdot && masschg_1.dmdt0 > 0.) {
	    ldoacc = TRUE_;
	    fli6a = 0.;
	    fli7a = 0.;
	    fbe9a = 0.;
	} else {
	    ldoacc = FALSE_;
	}
	i__1 = nstepe[j - 1];
	for (k = 1; k <= i__1; ++k) {
/* INCREMENT RATES BY LINEAR INTERPOLATION IN THE LOG. */
	    czli6 += frac * (bli6 - bli60);
	    czli7 += frac * (bli7 - bli70);
	    czbe9 += frac * (bbe9 - bbe90);
	    dli6 = dt * exp(czli6);
	    dli7 = dt * exp(czli7);
	    dbe9 = dt * exp(czbe9);
	    if (dli6 < 30. && fli6 > 1e-24) {
		fli6 /= exp(dli6);
	    } else {
		fli6 = 0.;
	    }
	    if (fli6 < 1e-24) {
		fli6 = 0.;
	    }
	    if (dli7 < 30. && fli7 > 1e-24) {
		fli7 /= exp(dli7);
	    } else {
		fli7 = 0.;
	    }
	    if (fli7 < 1e-24) {
		fli7 = 0.;
	    }
	    if (dbe9 < 30. && fbe9 > 1e-24) {
		fbe9 /= exp(dbe9);
	    } else {
		fbe9 = 0.;
	    }
	    if (fbe9 < 1e-24) {
		fbe9 = 0.;
	    }
/* MHP 05/02 MASS ACCRETION.  THE NET LITHIUM ADDED IN */
/* A GIVEN STEP IS XXXADD WHILE THE LITHIUM ADDED IN PRIOR */
/* STEPS IS XXXA; THE TWO ARE ADDED AFTER BURNING. */
/* N.B. SINCE THIS IS A HALF-LIFE PROBLEM IT IS OK TO BURN */
/* THE COMPONENTS SEPARATELY. */
	    if (ldoacc) {
		fli6add = masschg_1.compacc[12] * frac / exp(dli6 * .5);
		fli6a = fli6a / exp(dli6) + fli6add;
		fli7add = masschg_1.compacc[13] * frac / exp(dli7 * .5);
		fli7a = fli7a / exp(dli7) + fli7add;
		fbe9add = masschg_1.compacc[14] * frac / exp(dbe9 * .5);
		fbe9a = fbe9a / exp(dbe9) + fbe9add;
	    }
/* L100: */
	}
/* DO A MASS-WEIGHTED AVERAGE OF THE ORIGINAL LIGHT */
/* ELEMENT CONTENT AND THE NET AMOUNT ADDED. */
/* FMASSACC = DMDT*DT/ORIGINAL CZ MASS */
/* NOTE: THIS FORMULATION ASSUMES THAT ALL ACCRETED MATTER */
/* LANDS IN A CZ WITH THE END-OF-TIMESTEP DEPTH. */
/* NOT STRICTLY TRUE, BUT NOT A BAD APPROXIMATION EITHER. */
	if (ldoacc) {
	    s_wsfe(&io___62);
	    do_fio(&c__1, (char *)&fli60, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fli6, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fli6a, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fli70, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fli7, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fli7a, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&deuter_1.fmassacc, (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
	    fli6 = (fli6 * fm + fli6a * deuter_1.fmassacc) / (fm + 
		    deuter_1.fmassacc);
	    fli7 = (fli7 * fm + fli7a * deuter_1.fmassacc) / (fm + 
		    deuter_1.fmassacc);
	    fbe9 = (fbe9 * fm + fbe9a * deuter_1.fmassacc) / (fm + 
		    deuter_1.fmassacc);
	}
/* STORE THE ABUNDANCE AS A FUNCTION OF THE TIME STEP. */
/* STORE ABUNDANCES AS A FUNCTION OF TIMESTEP IN VECTOR YEST. */
	yest[0] = fli6;
	yest[1] = fli7;
	yest[2] = fbe9;
/* Computing 2nd power */
	d__1 = frac;
	xest = d__1 * d__1;
/* USE A RATIONAL POLYNOMIAL EXTRAPOLATOR TO EXTRAPOLATE TO THE SOLUTION FOR */
/* ZERO TIMESTEP. */
	ratext_(&j, &xest, yest, yext, yerr, &c__3, &c__7);
/* CHECK IF THE SOLUTION HAS CONVERGED. */
	if (j > 1) {
	    ldone = TRUE_;
	    for (k2 = 1; k2 <= 3; ++k2) {
		if (yest[k2 - 1] < 1e-24) {
		    goto L110;
		}
		yerr[k2 - 1] = (d__1 = yerr[k2 - 1] / yest[k2 - 1], abs(d__1))
			;
		if (yerr[k2 - 1] > ytol[k2 - 1]) {
		    ldone = FALSE_;
		}
L110:
		;
	    }
	    if (ldone) {
/*              WRITE(ISHORT,912)JENV,J,(YEXT(K2),YERR(K2),K2=1,3) */
		goto L125;
	    }
	}
/* L120: */
    }
/* IF THE PROGRAM GETS HERE THEN IT FAILED TO CONVERGE TO WITHIN */
/* THE SPECIFIED TOLERANCE IN THE MAXIMUM NUMBER OF ITERATIONS. */
    io___63.ciunit = luout_1.ishort;
    s_wsfe(&io___63);
    do_fio(&c__1, (char *)&jenv, (ftnlen)sizeof(integer));
    for (k2 = 1; k2 <= 3; ++k2) {
	do_fio(&c__1, (char *)&yerr[k2 - 1], (ftnlen)sizeof(doublereal));
    }
    e_wsfe();
L125:
/* WRITE NEW ABUNDANCES AND EXIT. */
    fli6 = yext[0];
    if (fli6 < 1e-24) {
	fli6 = 0.;
    }
    fli7 = yext[1];
    if (fli7 < 1e-24) {
	fli7 = 0.;
    }
    fbe9 = yext[2];
    if (fbe9 < 1e-24) {
	fbe9 = 0.;
    }
    i__1 = *m;
    for (i__ = maxj; i__ <= i__1; ++i__) {
	hcomp[i__ * 15 + 13] = fli6;
	hcomp[i__ * 15 + 14] = fli7;
	hcomp[i__ * 15 + 15] = fbe9;
/* L130: */
    }
/* STORE ENDING RATE FOR USE AT THE BEGINNING OF THE NEXT STEP. */
    prevcz_1.bli6old = bli6;
    prevcz_1.bli7old = bli7;
    prevcz_1.bbe9old = bbe9;
/* NOW SOLVE FOR ABUNDANCES IN THE REGION WHICH BEGAN CONVECTIVE AND */
/* ENDED RADIATIVE. */
    if (jenv <= jenv0) {
	goto L200;
    }
/* FIND STARTING AND ENDING LOCATION IN MASS OF THE CZ BASE, AND */
/* ASSUME THAT THE FRACTION OF TIME SPENT IN THE CZ IS PROPORTIONAL TO */
/* THE LOCATION IN MASS (I.E. A POINT 1/3 FROM THE OLD TO THE NEW CZ */
/* BASE IN MASS SPENT 1/3 OF THE TIME IN THE CZ AND 2/3 OUT OF IT). */
    if (jenv0 > 1) {
	hsbeg = (hs1[jenv0] + hs1[jenv0 - 1]) * .5;
    } else {
	hsbeg = 0.;
    }
    hsend = (hs1[jenv] + hs1[jenv - 1]) * .5;
    dmass = hsbeg - hsend;
    i__1 = jenv - 1;
    for (i__ = jenv0; i__ <= i__1; ++i__) {
/* MHP 9/91 CHANGE TO AVOID DIVISION BY ZERO. */
/* SKIP IF SHELL TEMPERATURE DROPS BELOW BURNING THRESHOLD. */
	if (newrat_1.rbe9[i__ - 1] <= 1e-32) {
	    goto L145;
	}
	frad = (hs1[i__] - hsbeg) / dmass;
/* USE FRAD*RADIATIVE RATE AND (1-FRAD)*CONVECTIVE RATE. */
	dli6 = *delts * exp(frad * log(newrat_1.rli6[i__ - 1]) + (1. - frad) *
		 bli60);
	dli7 = *delts * exp(frad * log(newrat_1.rli7[i__ - 1]) + (1. - frad) *
		 bli70);
	dbe9 = *delts * exp(frad * log(newrat_1.rbe9[i__ - 1]) + (1. - frad) *
		 bbe90);
/* ***REMEMBER TO ADD FAILSAFES FOR LARGE DEPLETION*** */
	hcomp[i__ * 15 + 13] /= exp(dli6);
	if (hcomp[i__ * 15 + 13] < 1e-24) {
	    hcomp[i__ * 15 + 13] = 0.;
	}
	hcomp[i__ * 15 + 14] /= exp(dli7);
	if (hcomp[i__ * 15 + 14] < 1e-24) {
	    hcomp[i__ * 15 + 14] = 0.;
	}
	hcomp[i__ * 15 + 15] /= exp(dbe9);
	if (hcomp[i__ * 15 + 15] < 1e-24) {
	    hcomp[i__ * 15 + 15] = 0.;
	}
/* L140: */
    }
L145:
L200:
    return 0;
} /* liburn_ */


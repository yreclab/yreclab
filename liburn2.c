/* liburn2.f -- translated by f2c (version 20100827).
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



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* LIBURN */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* 11/91 HR ADDED TO CALL. */
/* Subroutine */ int liburn2_(doublereal *delts, doublereal *hcomp, 
	doublereal *hd, doublereal *hr, doublereal *hs1, doublereal *hs2, 
	doublereal *ht, integer *jnenv, integer *jnenv0, integer *m)
{

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal), log(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal r__, fm, dr, fx, fm0, ddj, ros, bbe9, dbe9, fbe9, bli6, 
	    bli7, dli6, fli6, fli7, tbe9, dli7, tli6, tli7, bbe90, fbe90, 
	    bli60, bli70, frad, fli60, fli70;
    static integer minj, maxj, jenv;
    static doublereal ddjm1, czbe9;
    static integer jenv0;
    static doublereal czli6, czli7, hsbeg, rbase, hsend, dmass, ratbe9[5000], 
	    ratli6[5000], ratli7[5000], hs2sav;

/* MHP 10/91 COMMON BLOCK ADDED FOR OVERSHOOT. */
/* MHP 11/91 COMMON BLOCK ADDED FOR OVERSHOOT. */
/* MHP 11/91 COMMON BLOCKS ADDED FOR LITHIUM BURNING IN ROTATING */
/* MODELS WITH LINSTB=T. */
/* 11/91 COMMON BLOCK ADDED FOR THE EXACT LOCATION OF THE BASE OF THE */
/* SURFACE CZ AND THE INTEGRATED BURNING RATES THROUGHOUT IT. USED TO */
/* REMEMBER THE PREVIOUS "END OF TIMESTEP VALUES" FOR THE NEW */
/* "BEGINNING OF TIMESTEP VALUES". */
    /* Parameter adjustments */
    --ht;
    --hs2;
    --hs1;
    --hr;
    --hd;
    hcomp -= 16;

    /* Function Body */
/* DETERMINE LITHIUM AND BERYLLIUM BURNING. */
/* THE BURNING RATES DEPEND ON THE LOCAL T AND RHO, THE ABUNDANCE, AND */
/* IN THE CASE OF CONVECTION ZONES THE MIXING. */

/* IN RADIATIVE REGIONS BURNING IS DONE IMPLICITLY. */
/* IN CONVECTIVE REGIONS THE PROGRAM ITERATES BETWEEN BURNING AND MIXING */
/* TO CORRECT THE RATES FOR THE CHANGE IN ABUNDANCE AS A FUNCTION OF TIME. */
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
	    goto L50;
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
	tli6 = (log(newrat_1.rli6[i__ - 1]) + log(oldrat_1.rli60[i__ - 1])) * 
		.5;
	tli7 = (log(newrat_1.rli7[i__ - 1]) + log(oldrat_1.rli70[i__ - 1])) * 
		.5;
	tbe9 = (log(newrat_1.rbe9[i__ - 1]) + log(oldrat_1.rbe90[i__ - 1])) * 
		.5;
	ratli6[i__ - 1] = *delts * exp(tli6);
	ratli7[i__ - 1] = *delts * exp(tli7);
	ratbe9[i__ - 1] = *delts * exp(tbe9);
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
/* WRITE NEW ABUNDANCES AND EXIT. */
	if (hcomp[i__ * 15 + 13] < 1e-24) {
	    hcomp[i__ * 15 + 13] = 0.;
	}
	if (hcomp[i__ * 15 + 14] < 1e-24) {
	    hcomp[i__ * 15 + 14] = 0.;
	}
	if (hcomp[i__ * 15 + 15] < 1e-24) {
	    hcomp[i__ * 15 + 15] = 0.;
	}
L50:
	;
    }
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
/* INITIALIZE ABUNDANCES. */
    fli6 = fli60;
    fli7 = fli70;
    fbe9 = fbe90;
/* TIME-AVERAGED RATES USING LINEAR INTERPOLATION IN THE LOG. */
    czli6 = (bli6 + bli60) * .5;
    czli7 = (bli7 + bli70) * .5;
    czbe9 = (bbe9 + bbe90) * .5;
    dli6 = *delts * exp(czli6);
    dli7 = *delts * exp(czli7);
    dbe9 = *delts * exp(czbe9);
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
    i__1 = *m;
    for (i__ = maxj; i__ <= i__1; ++i__) {
	hcomp[i__ * 15 + 13] = fli6;
	hcomp[i__ * 15 + 14] = fli7;
	hcomp[i__ * 15 + 15] = fbe9;
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
	    goto L200;
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
    }
L200:
    return 0;
} /* liburn2_ */


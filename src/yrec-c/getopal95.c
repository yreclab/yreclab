/* getopal95.f -- translated by f2c (version 20061008).
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
    doublereal tgr[70], xxg[10], r0gr[19], zzg[13], cappa2[167580]	/* 
	    was [126][70][19] */;
    integer numxm[13], nz[13];
} llot95a_;

#define llot95a_1 llot95a_

struct {
    doublereal cappa[13300]	/* was [10][70][19] */, ztab;
} llot95_;

#define llot95_1 llot95_

struct {
    doublereal cappae[1330]	/* was [70][19] */, xtab;
} llot95e_;

#define llot95e_1 llot95e_

struct {
    integer jz, jx[16]	/* was [4][4] */, jt, jd[4];
} op95indx_;

#define op95indx_1 op95indx_

struct {
    doublereal bz[4], bx[16]	/* was [4][4] */, bt[4], btt[4], bd[16]	/* 
	    was [4][4] */, bdd[16]	/* was [4][4] */;
} op95fact_;

#define op95fact_1 op95fact_

struct {
    doublereal rl, rll, rlh[4];
    logical lextl, lexth, lexh[4];
} op95ext_;

#define op95ext_1 op95ext_

struct {
    doublereal tauczn, deladj[5000], tauhe, tnorm, tcz, whe, acatmr[5000], 
	    acatmd[5000], acatmp[5000], acatmt[5000], tatmos, ageout[5];
    logical lclcd;
    integer iclcd, iacat, ijlast;
    logical ljlast, ljwrt, ladon, laoly;
    integer ijvs, ijent, ijdel;
    logical lacout;
} acdpth_;

#define acdpth_1 acdpth_

/* Table of constant values */

static integer c__1 = 1;

/* THIS IS THE INTERPOLATION FACILITY FOR THE LIVERMORE OPACITY TABLES */
/* USING CUBIC SPLINE INTERPLOATION SCHEME.   (FOR OPAL95) */
/* -------------------------------------------------------------- */
/*      SUBROUTINE GETOPAL95(DL,TL,X,Z,O,OL,QOD,QOT) DRIVER- GET CAPPA */
/*      SUBROUTINE OP952D(O,OL,QOD,QOT) 2D INTERPOLATION IN (T,RHO) */
/*      SUBROUTINE OP953D(O,OL,QOD,QOT) 3D INTERPOLATION IN (X,T,RHO) */
/*      SUBROUTINE OP954D(O,OL,QOD,QOT) 4D INTERPOLATION IN (Z,X,T,RHO) */
/*      SUBROUTINE LL95TBL READ IN ALL TABLES */
/*      SUBROUTINE OP95ZTAB(Z) GENERATE TABLE AT FIXED Z */
/*      SUBROUTINE OP95XTAB(X) GENERATE TABLE AT FIXED X,Z */



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     GETOPAL95 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int getopal95_(doublereal *dl, doublereal *tl, doublereal *x,
	 doublereal *z__, doublereal *o, doublereal *ol, doublereal *qod, 
	doublereal *qot)
{
    /* Format strings */
    static char fmt_5[] = "(\002 LOG T OF\002,f11.6,\002OUT OF OPAL 95 TABLE"
	    " RANGE\002)";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal a[4], b[4], c__[4];
    static integer i__, j, k;
    static doublereal rr, zz;
    static integer idd, itt, ixx, jxx;
    static logical lchk;
    extern /* Subroutine */ int op952d_(doublereal *, doublereal *, 
	    doublereal *, doublereal *), op953d_(doublereal *, doublereal *, 
	    doublereal *, doublereal *), op954d_(doublereal *, doublereal *, 
	    doublereal *, doublereal *), intrp2_(doublereal *, doublereal *, 
	    doublereal *);
    static logical lshift;
    extern /* Subroutine */ int interp_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, fmt_5, 0 };


/* 7/98 MHP DRIVER ROUTINE FOR OPACITY GIVEN RHO,T, X, AND Z. */
/* JVS Need this one too: */
/* FULL SET OF TABLES: OPACITY AS A FUNCTION OF Z AND X, T, RHO/T6**3 */
/* TABLES ARE INCREMENTED IN SETS OF NZ*NX.  SO THE TABLES FOR THE */
/* THIRD METAL ABUNDANCE (3 X 10**-4)BEGIN AT TABLE 21 AND END AT TABLE 30. */
/* FOR THE HIGH VALUES OF Z, THE NUMBER OF X TABLES IS NOT THE SAME (I.E. */
/* X<0.9 FOR Z=0.1). */
/* FOR EACH COMPOSITION A FULL GRID IN (T,RHO/T6**3) IS RETAINED. */
/* AS ABOVE FOR THE MODEL Z. */
/* AS ABOVE FOR DESIRED SURFACE VALUE OF X. */
/* INDICES FOR INTERPOLATION IN Z,X,T, AND R */
/* INTERPOLATION FACTORS FOR Z,X,T, AND R, AS WELL AS DERIVATIVE */
/* FACTORS FOR T AND RHO. */
/* JVS Acoustic depth common block */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/ACDPTH/TAUCZN,DELADJ(JSON),TAUHE, TNORM, TCZ, WHE, ICLCD, */
/*      *LCLCD, AGEOUT(5), IACAT, IJLAST, LJLAST, LJWRT, LADON,LAOLY, IJVS, */
/* END JVS */
/* ENSURE THAT WE ARE WITHIN THE OPAL 95 TABLES. */
/* COMPUTE LOG R = RHO/T6**3 */
    op95ext_1.rl = *dl - (*tl - 6.) * 3.;
/*  CHECK T */
    if (*tl < llot95a_1.tgr[0] || *tl > llot95a_1.tgr[69]) {
	s_wsfe(&io___1);
	do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
/* CHECK TO SEE IF EXTRAPOLATION BELOW THE FIRST TABLE ELEMENT */
/* IN DENSITY IS NEEDED. */
    if (op95ext_1.rl < llot95a_1.r0gr[0]) {
	op95ext_1.lextl = TRUE_;
    } else {
	op95ext_1.lextl = FALSE_;
    }
/*  THIS SECTION IS REPLACED BY LINEAR EXTRAPOLATION IN R FROM THE */
/*  LAST TWO OPACITY VALUES. */
/*      IF(RL.LT.(R0GR(1)-4.0D0) .OR. RL.GT.(R0GR(NUMD)+1.0D0))THEN */
/*         WRITE(*,7)RL,TL */
/* 7       FORMAT(' LOG R OF',F11.6,' OUT OF OPAL 95 TABLE RANGE;TL' */
/*     *          ,F11.6) */
/*         STOP */
/*      ENDIF */
/* GET INTERPOLATION FACTORS IN T */
    if (*tl >= llot95a_1.tgr[op95indx_1.jt + 1]) {
	for (i__ = op95indx_1.jt + 3; i__ <= 69; ++i__) {
	    if (*tl < llot95a_1.tgr[i__ - 1]) {
		op95indx_1.jt = i__ - 2;
		goto L10;
	    }
	}
	op95indx_1.jt = 67;
L10:
	;
    } else {
	for (i__ = op95indx_1.jt + 1; i__ >= 2; --i__) {
	    if (*tl > llot95a_1.tgr[i__ - 1]) {
		op95indx_1.jt = i__ - 1;
		goto L20;
	    }
	}
	op95indx_1.jt = 1;
L20:
	;
    }
/* T INTERPOLATION FACTORS */
    for (i__ = 1; i__ <= 4; ++i__) {
	a[i__ - 1] = llot95a_1.tgr[op95indx_1.jt + i__ - 2];
    }
/* GET INTERPOLATION FACTORS IN T */
    interp_(a, b, c__, tl);
    for (i__ = 1; i__ <= 4; ++i__) {
	op95fact_1.bt[i__ - 1] = b[i__ - 1];
	op95fact_1.btt[i__ - 1] = c__[i__ - 1];
    }
/* GET INDICES IN RHO FOR EACH OF THE 4 T VALUES. */
    if (op95ext_1.rl >= llot95a_1.r0gr[op95indx_1.jd[0] + 1]) {
	for (i__ = op95indx_1.jd[0] + 3; i__ <= 18; ++i__) {
	    if (op95ext_1.rl < llot95a_1.r0gr[i__ - 1]) {
		op95indx_1.jd[0] = i__ - 2;
		goto L30;
	    }
	}
	op95indx_1.jd[0] = 16;
L30:
	;
    } else {
	for (i__ = op95indx_1.jd[0] + 1; i__ >= 2; --i__) {
	    if (op95ext_1.rl > llot95a_1.r0gr[i__ - 1]) {
		op95indx_1.jd[0] = i__ - 1;
		goto L40;
	    }
	}
	op95indx_1.jd[0] = 1;
L40:
	;
    }
/* NOW CHECK IF WITHIN PORTION OF TABLE WITH DATA. */
/* NOTE THAT A POINT CAN BE WITHIN THE TABLE AND STILL HAVE THE */
/* 4X4 MATRIX OF T,RHO AROUND IT OUTSIDE THE TABLE. */
/* CHECK LOW RHO, LOW T REGIME; SINCE THE EMPTY REGION DEPENDS ON Z AT */
/* LOW X, POSTPONE UNTIL YOU KNOW IF IT IS A 2D, 3D, OR 4D INTERPOLATION. */
    if (*x < .2 && op95indx_1.jt <= 5) {
	lchk = TRUE_;
	goto L60;
    } else {
	lchk = FALSE_;
    }
/* CHECK HIGH RHO, HIGH T REGIME(BECAUSE OF THE TABLE GEOMETRY, THE */
/* POINT WILL FALL OUTSIDE THE TABLE FIRST AT THE HIGHEST T). */
    lshift = FALSE_;
    op95ext_1.lexth = FALSE_;
    if (llot95_1.cappa[op95indx_1.jx[0] + (op95indx_1.jt + 3 + (op95indx_1.jd[
	    0] + 3) * 70) * 10 - 711] >= 9.9) {
	lshift = TRUE_;
/* NOW THERE ARE TWO POSSIBLE SOLUTIONS: WE CAN USE A DIFFERENT SET */
/* OF DENSITIES FOR EACH TEMPERATURE AND STAY WITHIN THE TABLE, OR */
/* THE DESIRED DENSITY COULD BE OUTSIDE THE TABLE AT ONE OR MORE */
/* TEMPERATURES.  IF THE DESIRED DENSITY IS OUTSIDE THE TABLE, */
/* LINEAR EXTRAPOLATION IN R AT FIXED T IS USED. */
	for (k = 1; k <= 4; ++k) {
	    if (llot95_1.cappa[op95indx_1.jx[0] + (op95indx_1.jt + k - 1 + (
		    op95indx_1.jd[0] + 1) * 70) * 10 - 711] >= 9.9) {
		op95ext_1.lexth = TRUE_;
		op95ext_1.lexh[k - 1] = TRUE_;
	    } else {
		op95ext_1.lexh[k - 1] = FALSE_;
	    }
	}
/* FIND 4 NEAREST ELEMENTS WITHIN THE TABLE AT EACH OF THE 4 TEMPERATURES. */
	ixx = op95indx_1.jx[0];
	idd = op95indx_1.jd[0];
	for (i__ = 1; i__ <= 4; ++i__) {
	    itt = op95indx_1.jt + i__ - 1;
	    if (llot95_1.cappa[ixx + (itt + (idd + 3) * 70) * 10 - 711] > 9.9)
		     {
		for (j = idd + 2; j >= 1; --j) {
		    if (llot95a_1.cappa2[ixx + (itt + j * 70) * 126 - 8947] <=
			     9.9) {
			op95indx_1.jd[i__ - 1] = j - 3;
			idd = j - 3;
			goto L50;
		    }
		}
L50:
		;
	    } else {
		op95indx_1.jd[i__ - 1] = idd;
	    }
	}
    }
L60:
/* GET INTERPOLATION FACTORS IN RHO FOR EACH OF THE 4 T VALUES. */
/* ASSIGN ALL THE SAME VALUES IF GRID IN R IS SAME FOR ALL T. */
    if (! lshift) {
	for (i__ = 1; i__ <= 4; ++i__) {
	    a[i__ - 1] = llot95a_1.r0gr[op95indx_1.jd[0] + i__ - 2];
	}
	if (! op95ext_1.lextl) {
	    interp_(a, b, c__, &op95ext_1.rl);
	} else {
	    op95ext_1.rll = llot95a_1.r0gr[0];
	    interp_(a, b, c__, &op95ext_1.rll);
	}
	for (j = 1; j <= 4; ++j) {
	    op95indx_1.jd[j - 1] = op95indx_1.jd[0];
	    for (i__ = 1; i__ <= 4; ++i__) {
		op95fact_1.bd[j + (i__ << 2) - 5] = b[i__ - 1];
		op95fact_1.bdd[j + (i__ << 2) - 5] = c__[i__ - 1];
	    }
	}
    } else {
	for (j = 1; j <= 4; ++j) {
	    for (i__ = 1; i__ <= 4; ++i__) {
		a[i__ - 1] = llot95a_1.r0gr[op95indx_1.jd[j - 1] + i__ - 2];
	    }
/* IF EXTRAPOLATION IS BEING PERFORMED, ASSIGN R=REDGE */
/* AND EXTRAPOLATE LINEARLY LATER */
	    if (! op95ext_1.lexh[j - 1]) {
		interp_(a, b, c__, &op95ext_1.rl);
	    } else {
		rr = llot95a_1.r0gr[op95indx_1.jd[j - 1] + 2];
		interp_(a, b, c__, &rr);
		op95ext_1.rlh[j - 1] = rr;
	    }
	    for (i__ = 1; i__ <= 4; ++i__) {
		op95fact_1.bd[j + (i__ << 2) - 5] = b[i__ - 1];
		op95fact_1.bdd[j + (i__ << 2) - 5] = c__[i__ - 1];
	    }
	}
    }
/* DETERMINE WHETHER A 2D (RHO,T); 3D (X,RHO,T); OR 4D (Z,X,RHO,T) */
/* INTERPOLATION IS NEEDED TO GET THE OPACITY. */
/* JVS 04/11 force 4d interpolation for acoustic depth calculations */
    if (acdpth_1.ladon && acdpth_1.lacout) {
	goto L153;
    }
/* If we're worrying about the acoustic depth, default to 4d interp */
    if ((d__1 = *z__ - llot95_1.ztab, abs(d__1)) / max(llot95_1.ztab,1e-6) <= 
	    1e-4) {
	if ((d__1 = *x - llot95e_1.xtab, abs(d__1)) <= 1e-4) {
/* 2D INTERPOLATION IN SURFACE TABLE */
	    op952d_(o, ol, qod, qot);
	    goto L9999;
	} else {
/* 3D INTERPOLATION IN FIXED Z TABLE (X,T,RHO) */
/* GET INTERPOLATION FACTORS IN X. */
	    if (*x > llot95a_1.xxg[op95indx_1.jx[0] + 1]) {
		for (i__ = op95indx_1.jx[0] + 3; i__ <= 9; ++i__) {
		    if (*x < llot95a_1.xxg[i__ - 1]) {
			op95indx_1.jx[0] = i__ - 2;
			goto L70;
		    }
		}
		op95indx_1.jx[0] = 7;
L70:
		;
	    } else {
		for (i__ = op95indx_1.jx[0] + 1; i__ >= 2; --i__) {
		    if (*x >= llot95a_1.xxg[i__ - 1]) {
			op95indx_1.jx[0] = i__ - 1;
			goto L80;
		    }
		}
		op95indx_1.jx[0] = 1;
L80:
		;
	    }
/* CHECK FOR ABSENT TABLES AT HIGH X. */
	    if (llot95_1.ztab >= .04) {
		if (*x >= .8) {
		    if (llot95_1.ztab < .1) {
/* NO TABLE 9 (X=0.95) */
			op95indx_1.jx[12] = 10;
			op95indx_1.jx[8] = 8;
			op95indx_1.jx[4] = 7;
			op95indx_1.jx[0] = 6;
		    } else {
/* NO TABLE 9 OR TABLE 10 */
			op95indx_1.jx[12] = 8;
			op95indx_1.jx[8] = 7;
			op95indx_1.jx[4] = 6;
			op95indx_1.jx[0] = 5;
		    }
		} else {
		    jxx = op95indx_1.jx[0] - 1;
		    for (i__ = 1; i__ <= 4; ++i__) {
			op95indx_1.jx[(i__ << 2) - 4] = jxx + i__;
		    }
		}
	    } else {
		jxx = op95indx_1.jx[0] - 1;
		for (i__ = 1; i__ <= 4; ++i__) {
		    op95indx_1.jx[(i__ << 2) - 4] = jxx + i__;
		}
	    }
/* X INTERPOLATION FACTORS */
	    for (i__ = 1; i__ <= 4; ++i__) {
		ixx = op95indx_1.jx[(i__ << 2) - 4];
		a[i__ - 1] = llot95a_1.xxg[ixx - 1];
	    }
	    if (op95indx_1.jx[12] == 10) {
		a[3] = 1. - llot95_1.ztab;
	    }
/* GET INTERPOLATION FACTORS IN X */
	    intrp2_(a, b, x);
	    for (j = 1; j <= 4; ++j) {
		op95fact_1.bx[(j << 2) - 4] = b[j - 1];
	    }
	    op953d_(o, ol, qod, qot);
	    goto L9999;
	}
    }
L153:
/* 4D INTERPOLATION IN Z,X,T,RHO */
/* GET NEAREST TABLES IN Z. */
    if (*z__ > llot95a_1.zzg[op95indx_1.jz + 1]) {
/* mhp 7/12 corrected typo */
/*         DO I = JZ+3,NUMT-1 */
	for (i__ = op95indx_1.jz + 3; i__ <= 12; ++i__) {
	    if (*z__ < llot95a_1.zzg[i__ - 1]) {
		op95indx_1.jz = i__ - 2;
		goto L110;
	    }
	}
	op95indx_1.jz = 10;
L110:
	;
    } else {
	for (i__ = op95indx_1.jz + 1; i__ >= 2; --i__) {
	    if (*z__ >= llot95a_1.zzg[i__ - 1]) {
		op95indx_1.jz = i__ - 1;
		goto L120;
	    }
	}
	op95indx_1.jz = 1;
L120:
	;
    }
/* mhp 7/12 added failsafe */
    op95indx_1.jz = min(op95indx_1.jz,10);
/* Z INTERPOLATION FACTORS */
    for (i__ = 1; i__ <= 4; ++i__) {
	a[i__ - 1] = llot95a_1.zzg[op95indx_1.jz + i__ - 2];
    }
/* INTERPOLATION FACTORS IN Z */
    intrp2_(a, b, z__);
    for (i__ = 1; i__ <= 4; ++i__) {
	op95fact_1.bz[i__ - 1] = b[i__ - 1];
    }
/* GET NEAREST TABLES IN X AT EACH VALUE OF Z */
    for (k = 1; k <= 4; ++k) {
	zz = llot95a_1.zzg[op95indx_1.jz + k - 2];
	ixx = op95indx_1.jx[k - 1];
	if (*x > llot95a_1.xxg[ixx + 1]) {
	    for (i__ = op95indx_1.jx[k - 1] + 3; i__ <= 9; ++i__) {
		if (*x < llot95a_1.xxg[i__ - 1]) {
		    op95indx_1.jx[k - 1] = i__ - 2;
		    goto L75;
		}
	    }
	    op95indx_1.jx[k - 1] = 7;
L75:
	    ;
	} else {
	    for (i__ = op95indx_1.jx[k - 1] + 1; i__ >= 2; --i__) {
		if (*x >= llot95a_1.xxg[i__ - 1]) {
		    op95indx_1.jx[k - 1] = i__ - 1;
		    goto L85;
		}
	    }
	    op95indx_1.jx[k - 1] = 1;
L85:
	    ;
	}
/* CHECK FOR ABSENT TABLES AT HIGH X. */
	if (zz >= .04) {
	    if (*x >= .8) {
		if (zz < .1) {
/* NO TABLE 9 (X=0.95) */
		    op95indx_1.jx[k + 11] = 10;
		    op95indx_1.jx[k + 7] = 8;
		    op95indx_1.jx[k + 3] = 7;
		    op95indx_1.jx[k - 1] = 6;
		} else {
/* NO TABLE 9 OR TABLE 10 */
		    op95indx_1.jx[k + 11] = 8;
		    op95indx_1.jx[k + 7] = 7;
		    op95indx_1.jx[k + 3] = 6;
		    op95indx_1.jx[k - 1] = 5;
		}
	    } else {
		jxx = op95indx_1.jx[k - 1] - 1;
		for (i__ = 1; i__ <= 4; ++i__) {
		    op95indx_1.jx[k + (i__ << 2) - 5] = jxx + i__;
		}
	    }
	} else {
	    jxx = op95indx_1.jx[k - 1] - 1;
	    for (i__ = 1; i__ <= 4; ++i__) {
		op95indx_1.jx[k + (i__ << 2) - 5] = jxx + i__;
	    }
	}
/* X INTERPOLATION FACTORS */
	for (i__ = 1; i__ <= 4; ++i__) {
	    ixx = op95indx_1.jx[k + (i__ << 2) - 5];
	    a[i__ - 1] = llot95a_1.xxg[ixx - 1];
	}
	if (op95indx_1.jx[k + 11] == 10) {
	    a[3] = 1. - zz;
	}
/* GET INTERPOLATION FACTORS IN X */
	intrp2_(a, b, x);
	for (j = 1; j <= 4; ++j) {
	    op95fact_1.bx[k + (j << 2) - 5] = b[j - 1];
	}
    }
    op954d_(o, ol, qod, qot);
L9999:
    return 0;
} /* getopal95_ */


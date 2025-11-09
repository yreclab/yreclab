/* mixcz.f -- translated by f2c (version 20061008).
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
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal amum[5000], cpm[5000], delm[5000], delam[5000], delrm[5000], 
	    esumm[5000], om[5000], qdtm[5000], thdifm[5000], velm[5000], 
	    viscm[5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

/* $$$$$$ */
/*       SUBROUTINE MIXCZ(HCOMP,HS2,HS1,LCZ,HR,HP,HD,HG,M,IFSTCL)  ! KC 2025-05-31 */
/* Subroutine */ int mixcz_(doublereal *hcomp, doublereal *hs2, logical *lcz, 
	integer *m)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Local variables */
    static integer i__, j, i1, i2, jj, mp1;
    static logical lcc;
    static integer iend;
    static doublereal xsum[15], wtsum;
    static integer mxzone[24];

/* JVS 02/12 COMMON BLOCKS ADDED FOR THE CALCULATION OF TAUCZ */
/* END JVS */
/* MHP 02/12 ADDED ROTATION INFORMATION.  HG VECTOR IS NOT DEFINED FOR */
/* SPHERICAL MODELS AND IS USED FOR TAUCZ; ADDED INFORMATION SO THAT */
/* TAUCZ IS PROPERLY COMPUTED FOR SUCH MODELS. */
/*      *     XSUM(15), HR(JSON), HP(JSON), HD(JSON), HG(JSON), HS1(JSON)  ! KC 2025-05-31 */
/* G Somers 6/14, ADDED IFSTCL TO THE ROUTINE CALL, STANDING */
/* FOR 'FIRST CALL'. THIS IS A BOOL THAT IS TRUE IF MIXCZ IS */
/* CALLED BEFORE MIDMOD, OR FALSE IF IT IS CALLED AFTER MIDMOD. */
/* THIS ALLOWS THE CORRECT GRADIENTS TO BE USED WHEN CALCULATING TAUCZ. */
/* THE COMMON BLOCK WITH THE NECESSARY VARIABLES IS IMPORTED HERE. */
/* G Somers END */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/* COMPUTE STANDARD CONVECTION ZONES */
    /* Parameter adjustments */
    --lcz;
    --hs2;
    hcomp -= 16;

    /* Function Body */
    j = 1;
    lcc = FALSE_;
    mp1 = *m + 1;
    lcz[mp1] = FALSE_;
    i__1 = mp1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (! lcz[i__]) {
	    goto L10;
	}
/* CONVECTION ZONE */
	if (lcc) {
	    goto L11;
	}
/* START OF CONVECTION ZONE */
	lcc = TRUE_;
	i1 = i__;
	goto L11;
L10:
	if (! lcc) {
	    goto L11;
	}
/*   END OF CONVECTION ZONE */
	lcc = FALSE_;
	mxzone[j - 1] = i1;
	mxzone[j] = i__ - 1;
	j += 2;
	if (j < 24) {
	    goto L11;
	}
	goto L12;
L11:
	;
    }
    mxzone[j - 1] = 0;
L12:
    iend = 11;
    if (flag_1.lexcom) {
	iend = 15;
    }
/* MIX ALL CONVECTIVE ZONES */
    for (j = 1; j <= 24; j += 2) {
	if (mxzone[j - 1] <= 0) {
	    goto L110;
	}
	i1 = mxzone[j - 1];
/* Computing MIN */
	i__1 = *m, i__2 = mxzone[j];
	i2 = min(i__1,i__2);
/*   903    IF(I1.NE.1 .AND. I1.GE.I2) GOTO 100 */
	if (i1 != 1 && i1 >= i2) {
	    goto L100;
	}
/* INITIALIZE SUMS */
/*   904    WTSUM = 0.0D0 */
	wtsum = 0.;
	i__1 = iend;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xsum[i__ - 1] = 0.;
/* L40: */
	}
	i__1 = i2;
	for (jj = i1; jj <= i__1; ++jj) {
	    wtsum += hs2[jj];
	    i__2 = iend;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		xsum[i__ - 1] += hcomp[i__ + jj * 15] * hs2[jj];
/* L50: */
	    }
/* L60: */
	}
	i__1 = iend;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xsum[i__ - 1] /= wtsum;
/* L70: */
	}
	i__1 = i2;
	for (jj = i1; jj <= i__1; ++jj) {
	    i__2 = iend;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		hcomp[i__ + jj * 15] = xsum[i__ - 1];
/* L80: */
	    }
/* L90: */
	}
L100:
	;
    }
L110:
/* RENORMALIZE COMPOSITION IF NECESSARY */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__1 = hcomp[i__ * 15 + 1];
	hcomp[i__ * 15 + 1] = max(d__1,0.);
/* Computing MIN */
	d__1 = hcomp[i__ * 15 + 3], d__2 = 1. - hcomp[i__ * 15 + 1];
	hcomp[i__ * 15 + 3] = min(d__1,d__2);
/* Computing MAX */
	d__1 = hcomp[i__ * 15 + 9], d__2 = (hcomp[i__ * 15 + 3] - 
		comp_1.zenvm) * 9.9e-4;
	hcomp[i__ * 15 + 9] = max(d__1,d__2);
/* L140: */
    }
/* G Somers 3/17, COMMENTED OUT THIS TAUCZ CALCULATION. IT IS NOW PASSED */
/* IN IN THE OVRTRN COMMON BLOCK */

/* JVS 02/12 CALCULATE THE LOCAL CONVECTIVE OVERTURN TIMESCALE AT THE BASE */
/* OF THE CZ. IN OLDER VERSIONS THIS WAS ONLY DONE FOR ROTATING MODELS; */
/* THIS MAKES IT SO TAUCZ IS CALCULATED FOR ALL MODELS. */
/* THIS CODE SNAGGED FROM MIDMOD */

/* C  DETERMINE EXTENT OF SURFACE CONVECTION ZONE. */
/*      LALLCZ = .FALSE. */
/*      IF(LCZ(M))THEN */
/* C  SURFACE C.Z. EXISTS.  FIND LOWEST SHELL (IMAX), WHICH IS ALSO THE */
/* C  UPPERMOST ZONE CONSIDERED FOR STABILITY AGAINST ROTATIONALLY INDUCED MIXING. */
/*         DO 71 I = M-1,1,-1 */
/*            IF(.NOT.LCZ(I)) GOTO 81 */
/*   71    CONTINUE */
/*         LALLCZ = .TRUE. */
/*         I = 0 */
/*   81    IMAX = I + 1 */
/* C  HSTOP IS THE MASS AT THE TOP OF THE C.Z. */
/* C  HSBOT IS THE MASS AT THE BOTTOM OF THE C.Z. */
/*         HSTOP = EXP(CLN*STOTAL) */
/*         IF(IMAX.GT.1)THEN */
/*            HSBOT = 0.5D0*(HS1(IMAX)+HS1(IMAX-1)) */
/*         ELSE */
/*            HSBOT = 0.0D0 */
/*         ENDIF */
/* C  LCZSUR=T IF A SURFACE C.Z.DEEP ENOUGH FOR ANGULAR MOMENTUM LOSS EXISTS */
/*         IF((HSTOP-HSBOT)/CMSUN.GT.0.0D0)THEN */
/*            LCZSUR = .TRUE. */
/*         ELSE */
/*            LCZSUR= .FALSE. */
/*         ENDIF */
/*      ELSE */
/* C  NO SURFACE C.Z. */
/*         IMAX = M */
/*         LCZSUR = .FALSE. */
/*      ENDIF */

/*      IF(LCZSUR)THEN */
/*         IF(.NOT.LALLCZ)THEN */
/*            IF(.NOT.LROT)THEN */
/*               HG(IMAX)=HS1(IMAX)*EXP(CLN*(CGL-2.0D0*HR(IMAX))) */
/*               HG(IMAX-1)=HS1(IMAX-1)*EXP(CLN*(CGL-2.0D0*HR(IMAX-1))) */
/*            ENDIF */
/* C PINPOINT RCZ */
/* C G Somers 6/14, CHECK WHETHER THIS RUN OF MIXCZ OCCURED BEFORE */
/* C OR AFTER MIDMOD. IF BEFORE, USE SDEL. IF AFTER, USE THE UPDATED */
/* C VARIABLES DELRM AND DELAM. */
/*            IF(IFSTCL.EQ..TRUE.)THEN */
/*               DD2 = SDEL(1,IMAX-1)-SDEL(3,IMAX-1) */
/*               DD1 = SDEL(1,IMAX)-SDEL(3,IMAX) */
/*            ELSE */
/*               DD2 = DELRM(IMAX-1)-DELAM(IMAX-1) */
/*               DD1 = DELRM(IMAX)-DELAM(IMAX) */
/*            ENDIF */
/* C G Somers END */
/*            FX = DD2/(DD2-DD1) */
/* C INFER HP */
/*            ENVRL = HR(IMAX-1)+FX*(HR(IMAX)-HR(IMAX-1)) */
/*            ENVR = EXP(CLN*ENVRL) */
/*            PS2 = EXP(CLN*(HP(IMAX)-HD(IMAX)))/HG(IMAX) */
/*            PS1 = EXP(CLN*(HP(IMAX-1)-HD(IMAX-1)))/HG(IMAX-1) */
/*            PSCA = PS1 + FX*(PS2-PS1) */
/*            RTESTL = DLOG10(ENVR+PSCA) */
/* C FIND V */
/*            DO K = IMAX+1,M */
/*               IF(HR(K).GT.RTESTL)THEN */
/*                  FX = (RTESTL-HR(K-1))/(HR(K)-HR(K-1)) */
/*                  CVEL = SVEL(K-1)+FX*(SVEL(K)-SVEL(K-1)) */
/*                  GOTO 85 */
/*               ENDIF */
/*            END DO */
/*            CVEL = SVEL(M) */
/* 85         CONTINUE */
/* C DEFINE TAUCZ */
/*            TAUCZ = PSCA/CVEL */
/*         ELSE */
/* C INFER HP */
/*            IF(.NOT.LROT)THEN */
/*               HG(1)=HS1(1)*EXP(CLN*(CGL-2.0D0*HR(1))) */
/*            ENDIF */
/*            PSCA2 = EXP(CLN*(HP(1)-HD(1)))/HG(1) */
/*            RTEST2 = EXP(CLN*HR(1)) */
/*            IF(PSCA2.LE.RTEST2)THEN */
/* C HP < R AT THE FIRST POINT.  ASSUME V CONSTANT INSIDE AND HP = K/R FOR */
/* C SLOWLY VARYING DENSITY AND PRESSURE NEAR THE CENTER. */
/*               CVEL = SVEL(1) */
/*               PSCA = (PSCA2*RTEST2)**0.5D0 */
/*               TAUCZ = PSCA/CVEL */
/*            ELSE */
/*               DO K = 2,M */
/*                  PSCA1 = PSCA2 */
/*                  RTEST1 = RTEST2 */
/*                  IF(.NOT.LROT)THEN */
/*                     HG(K)=HS1(K)*EXP(CLN*(CGL-2.0D0*HR(K))) */
/*                  ENDIF */
/*                  PSCA2 = EXP(CLN*(HP(K)-HD(K)))/HG(K) */
/*                  RTEST2 = EXP(CLN*HR(K)) */
/* C FIND LOCATION WHERE HP = R */
/*                  IF(PSCA2.LE.RTEST2)THEN */
/*                     FX = (RTEST1-PSCA1)/((PSCA2-RTEST2)-(PSCA1-RTEST1)) */
/* C FIND V */
/*                     CVEL = SVEL(K-1)+FX*(SVEL(K)-SVEL(K-1)) */
/*                     PSCA = PSCA1+FX*(PSCA2-PSCA1) */
/* C DEFINE TAUCZ */
/*                     TAUCZ = PSCA/CVEL */
/*                     GOTO 95 */
/*                  ENDIF */
/*               END DO */
/*               K = M */
/*               CVEL = SVEL(M) */
/*               PSCA = PSCA2 */
/*               TAUCZ = PSCA/CVEL */
/* 95            CONTINUE */
/*            ENDIF */
/*         ENDIF */
/*      ELSE */
/*         TAUCZ = 0.0D0 */
/*      ENDIF */
/* END JVS */
    return 0;
} /* mixcz_ */


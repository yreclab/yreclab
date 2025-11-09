/* seculr.f -- translated by f2c (version 20061008).
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
    logical lstore, lstatm, lstenv, lstmod, lstphys, lstrot, lscrib, lstch, 
	    lphhd;
} ccout_;

#define ccout_1 ccout_

struct {
    integer npenv, nprtmod, nprtpt, npoint;
} ccout1_;

#define ccout1_1 ccout1_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal wmax, exmd, exw, extau, exr, exm, exl, expr, constfactor, 
	    structfactor, excen, c_2__;
    logical ljdot0;
} cwind_;

#define cwind_1 cwind_

struct {
    doublereal dtdif, djok;
    integer itdif1, itdif2;
} difus_;

#define difus_1 difus_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal alm[5000], delami[5000], delmi[5000], dm[5000], epsilm[5000], 
	    hgm[5000], hs3[5000], pm[5000], qdtmi[5000], rm[5000], tm[5000];
} intvar_;

#define intvar_1 intvar_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_;

#define oldmod_1 oldmod_

struct {
    doublereal ves[5000], ves0[5000], vss[5000], vss0[5000], hle[5000], vgsf[
	    5000], vgsf0[5000], vmu[5000];
} temp2_;

#define temp2_1 temp2_

struct {
    doublereal hcomps[75000]	/* was [15][5000] */;
} oldab_;

#define oldab_1 oldab_

struct {
    doublereal vfc[5000];
    logical lvfc, ldifad;
} varfc_;

#define varfc_1 varfc_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    logical lprt0;
} rotprt_;

#define rotprt_1 rotprt_

struct {
    logical lnoj;
} notran_;

#define notran_1 notran_

struct {
    doublereal sage, tdisk, pdisk;
    logical ldisk;
} disk_;

#define disk_1 disk_

struct {
    doublereal chi[5000], echi[5000], eqs1[5000], dchi;
    integer ntot;
} egrid_;

#define egrid_1 egrid_

struct {
    doublereal tho[5000], thn[5000], thm[5000], ddelm[5000], festime[5000], 
	    thp[5000], qwrst[5000], wmst[5000], qwrmst[5000];
} oldrot2_;

#define oldrot2_1 oldrot2_

struct {
    logical lsolid;
    integer impjmod;
} sbrot_;

#define sbrot_1 sbrot_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$ */
/*       SUBROUTINE SECULR(DELTS,DT,HD,HG,HI,HL,HP,HR,HS,HS1,HS2,HT, */
/*      *                  HJMSAV,LCZ,LC,M,MODEL,OMEGA, */
/*      *                  HJM,ETA2,QIW,R0,HCOMP,LFIRST,IMIN,IMAX, */
/*      *                  BL,HSTOT,SJTOT,SMASS,TEFFL,LREDO,IREDO,  ! KC 2025-05-31 */
/* Subroutine */ int seculr_(doublereal *dt, doublereal *hd, doublereal *hg, 
	doublereal *hi, doublereal *hl, doublereal *hp, doublereal *hr, 
	doublereal *hs, doublereal *hs1, doublereal *hs2, doublereal *ht, 
	doublereal *hjmsav, logical *lcz, integer *m, doublereal *omega, 
	doublereal *hjm, doublereal *eta2, doublereal *qiw, doublereal *r0, 
	doublereal *hcomp, integer *imin, integer *imax, doublereal *bl, 
	doublereal *hstot, doublereal *smass, doublereal *teffl, logical *
	lredo, integer *iredo, doublereal *hicz, doublereal *hsbot, 
	doublereal *hstop, doublereal *omegas, logical *lczsur, doublereal *
	cod2, doublereal *hv, logical *lok)
{
    /* Format strings */
    static char fmt_198[] = "(\002COMPOSITION CHANGE FROM ROTATIONAL MIXIN"
	    "G\002/5x,\002H\002,8x,\002HE3\002,7x,\002C12\002,7x,\002C13\002,"
	    "7x,\002N14\002,7x,\002LI7\002,7x,\002BE9\002)";
    static char fmt_199[] = "(i5,1p7e10.3)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double d_lg10(doublereal *), exp(doublereal);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int dadcoeft_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, logical *, logical *);
    static integer i__, j, id[5000];
    static doublereal ei[5000], em[5000], ej[5000], dj[5000], dr, ew[5000];
    static integer it;
    static doublereal dx, dr1, dc12, dc13, cod[5000], dn14;
    static logical ldo;
    static integer idm;
    static doublereal hru[5000], dhe3, dbe9, dli7;
    static logical lcz1;
    static integer ibeg, jbeg;
    static doublereal ecod[5000];
    static integer jend, iend;
    static doublereal codm, wbeg;
    static logical lock;
    static doublereal rmid[5000], hjmp[5000], rlnc;
    static logical ldum, lfix, lczm;
    static doublereal wsav[5000];
    static logical lprt;
    static doublereal ecod2[5000], wind1;
    static logical ldum2;
    static doublereal wind2;
    extern /* Subroutine */ int getfc_(doublereal *, doublereal *, doublereal 
	    *, integer *, integer *, doublereal *);
    static logical lokad, lcodm;
    extern /* Subroutine */ int vcirc_(doublereal *, doublereal *, integer *, 
	    integer *, integer *, logical *, integer *, doublereal *, logical 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer imaxj;
    extern /* Subroutine */ int solid_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, integer *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    );
    static logical ljdot, limix;
    extern /* Subroutine */ int mwind_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, integer *, integer *, logical *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal cltot;
    extern /* Subroutine */ int mixcz_(doublereal *, doublereal *, logical *, 
	    integer *);
    static logical ltest;
    static doublereal sumdj, qwlnr[5000];
    extern /* Subroutine */ int eq2mod_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, logical *, integer *, 
	    doublereal *, doublereal *), checkc_(doublereal *, integer *, 
	    logical *, integer *, doublereal *, integer *, logical *, logical 
	    *), checkj_(doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, logical *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, logical *, logical *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, logical *), codiff_(doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *), dcoeft_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, logical *), 
	    tridia_(integer *, doublereal *, doublereal *, doublereal *), 
	    getqua_(doublereal *, doublereal *, doublereal *, doublereal *, 
	    integer *);
    static doublereal hsbotj, hstopj;
    static integer jstart, istart;
    static doublereal qwrmax[5000];
    extern /* Subroutine */ int setupv_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *), ndifcom_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, logical *, logical *, integer *, doublereal *, integer 
	    *, integer *), mcowind_(doublereal *, doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *), rotgrid_(doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    logical *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *);

    /* Fortran I/O blocks */
    static cilist io___51 = { 0, 0, 0, fmt_198, 0 };
    static cilist io___59 = { 0, 0, 0, fmt_199, 0 };


/*      *                  MRZONE,MXZONE,NRZONE,NZONE,  ! KC 2025-05-31 */
/* MHP 6/00 ADDED MRZONE,MXZONE,NRZONE,NZONE FOR BS MIX PLUS BURN */
/* MHP 8/17 ADDED EXCEN, C_2 TO COMMON BLOCK FOR MATT ET AL. 2012 CENT. TERM */
/*      COMMON/CWIND/WMAX,EXMD,EXW,EXTAU,EXR,EXM,CONSTFACTOR,STRUCTFACTOR,LJDOT0 */
/* MHP 6/00 ADDED FLAG FOR CALL TO NDIFCOM */
/* 3/92 COMMON BLOCK ADDED FOR CENTERED DW/DLNR. */
/* ADD OPTION FOR VARIABLE FC. */
/* MHP 9/94 ADDED DISK LOCKING OPTION - FLAG, TIME OVER WHICH LOCKING */
/* IS ENFORCED, AND PERIOD AT WHICH LOCKING IS SET ARE OPTIONS. */
/* Time change of theta */
/* MHP 3/99 ADDED FLAG TO TREAT THE ENTIRE STAR AS 'CONVECTIVE' */
/* FOR ANGULAR MOMENTUM PURPOSES. */
/* JNT 09/25 FOR 05/15 ADD IMPJMOD */
/*      * HR(JSON),LC(JSON),OMEGA(JSON),HL(JSON),ETA2(JSON),QIW(JSON),  ! KC 2025-05-31 */
/*      *     MRZONE(13,2),MXZONE(12,2) */
/* MHP 6/00 ADDED MRZONE,MXZONE FOR BS MIXING PLUS BURNING */
/*   SECULR CALCULATES THE TRANSFER OF ANGULAR MOMENTUM(AND THE ASSOCIATED */
/*   TRANSPORT OF COMPOSITION) DUE TO SECULAR ROTATIONAL INSTABILITIES. */
/*  PRINT OUT DETAILS OF THE DIFFUSION EVERY TIME SHORT OR LONG */
/*  OUTPUT OF THE MODEL IS GENERATED. */

/* G Somers 11/14, EXCLUDE THE IO TO THE FULL FILE. THE CODE */
/* WILL NO LONGER REPORT THE CHANGES TO J AT EACH POINT, BECAUSE */
/* THIS CAN BE EASILY INFERRED FROM THE EXTENDED SHORT FILE. IF */
/* DESIRED, THIS OUTPUT CAN BE RETURNED. */
/*      IF(.NOT.LPRT0)THEN */
/*         LPRT = MOD(MODEL+1,NPRTMOD).EQ.0 */
/*      ELSE */
/*         LPRT = .TRUE. */
/*      ENDIF */
/*      IF(.NOT.LSCRIB.OR..NOT.LPRTIN) LPRT = .FALSE. */
    /* Parameter adjustments */
    --hv;
    --cod2;
    hcomp -= 16;
    --r0;
    --qiw;
    --eta2;
    --hjm;
    --omega;
    --lcz;
    --hjmsav;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hi;
    --hg;
    --hd;

    /* Function Body */
    lprt = FALSE_;
/* MHP 9/94 */
/* DISK LOCKING CHECKED */
    lock = FALSE_;
    if (disk_1.ldisk && disk_1.sage <= disk_1.tdisk) {
	lock = TRUE_;
    }
/*  FIRST AND LAST SHELL BOUNDARY CONDITIONS REQUIRE THAT THESE SHELLS BE */
/*  TREATED AS 'CONVECTIVE' FOR DIFFUSION PURPOSES. FIX THIS. */
    lcz1 = lcz[1];
    lczm = lcz[*m];
/*  SET UP FACTORS USED TO COMPUTE DIFFUSION VELOCITIES. */
/*       CALL SETUPV(HD,HG,HL,HP,HR,HS1,HT,IMIN,IMAX,LCZ,M,HRU,QWRMAX)  ! KC 2025-05-31 */
    setupv_(&hd[1], &hg[1], &hl[1], &hp[1], &hr[1], &hs1[1], &ht[1], imin, 
	    imax, m, hru, qwrmax);
    cltot = const_1.clsun * hl[*m];
/*  COMPUTE ANGULAR VELOCITY GRADIENTS */
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
/* CENTER LOGARITHMIC DERIVATIVE. */
	rlnc = d_lg10(&intvar_1.rm[i__ - 1]);
	dr1 = 1. / const1_1.cln / (hr[i__] - rlnc) + 1. / const1_1.cln / (
		rlnc - hr[i__ - 1]);
	qwlnr[i__ - 1] = (omega[i__] - omega[i__ - 1]) * .25 * dr1;
/*        QWLNR(I) = (OMEGA(I)-OMEGA(I-1))/CLN/(HR(I)-HR(I-1)) */
/* L10: */
    }
    getqua_(&hd[1], &hg[1], hru, &omega[1], m);
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	varfc_1.vfc[i__ - 1] = 0.;
    }
/*  CHECK STABILITY OF THE MODEL AND COMPUTE CIRCULATION VELOCITIES. */
/*  MECHANISMS CONSIDERED:SECULAR AND DYNAMICAL SHEAR,EDDINGTON CIRCULATION, */
/*  AND THE GSF INSTABILITY. */
    it = 1;
/* MHP 06/02 added timestep to call */
/*       CALL VCIRC(HJM,HR,HRU,IMIN,IMAX,IT,LCZ,M,OMEGA,LDO,QWLNR,  ! KC 2025-05-31 */
    vcirc_(&hr[1], hru, imin, imax, &it, &lcz[1], m, &omega[1], &ldo, qwlnr, 
	    qwrmax, &hv[1], &cltot, dt, &hp[1]);
    if (varfc_1.lvfc) {
	getfc_(&hd[1], hru, &hv[1], imin, imax, &omega[1]);
    }
/*  STORE INITIAL ANGULAR MOMENTUM DISTRIBUTION. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hjmp[i__ - 1] = hjmsav[i__];
	wsav[i__ - 1] = omega[i__];
/* L20: */
    }
/*  STORE INITIAL SURFACE ANGULAR VELOCITY FOR USE IN ANGULAR MOMENTUM */
/*  LOSS CALCULATIONS. */
/*      WBEG = OMEGA(M) */
    wbeg = oldrot2_1.wmst[*m - 1];
    *lok = FALSE_;
/*  ON THE FIRST LEVEL OF ITERATION, THE UNPERTURBED MODEL IS USED TO */
/*  CALCULATE THE DIFFUSION VELOCITIES. ON THE SECOND AND SUBSEQUENT */
/*  ITERATIONS, THE ANGULAR MOMENTUM DISTRIBUTION FROM THE PREVIOUS */
/*  ITERATION IS USED TO GET THE VELOCITIES.  THIS 'NEW' VELOCITY IS THEN */
/*  AVERAGED WITH THE VELOCITY FOUND IN THE PREVIOUS ITERATION TO GET A */
/*  CORRECTED V AND THUS A MORE ACCURATE RUN OF DIFFUSION COEFFICIENTS. */
    i__1 = difus_1.itdif2;
    for (it = 1; it <= i__1; ++it) {
	*omegas = omega[*m];
	if (it > 1) {
/*  COMPUTE NEW RUN OF ANGULAR VELOCITIES (AVERAGE OF INITIAL AND */
/*  LATEST VALUES). */
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		omega[i__] = (omega[i__] + wsav[i__ - 1]) * .5;
	    }
/*  COMPUTE NEW RUN OF ANGULAR VELOCITY GRADIENTS. */
	    i__2 = *imax;
	    for (i__ = *imin; i__ <= i__2; ++i__) {
/* CENTER LOGARITHMIC DERIVATIVE. */
		rlnc = d_lg10(&intvar_1.rm[i__ - 1]);
		dr1 = 1. / const1_1.cln / (hr[i__] - rlnc) + 1. / 
			const1_1.cln / (rlnc - hr[i__ - 1]);
		qwlnr[i__ - 1] = (omega[i__] - omega[i__ - 1]) * .25 * dr1;
/*              QWLNR(I) = (OMEGA(I)-OMEGA(I-1))/CLN/(HR(I)-HR(I-1)) */
/* L30: */
	    }
/*  ON 2ND AND SUBSEQUENT ITERATIONS,COMPUTE CHARACTERISTIC VELOCITIES */
/*  FOR THE NEW RUN OF OMEGA AND COMPOSITION FOUND IN THE PREVIOUS */
/*  ITERATION. */
/* MHP 06/02 added pressure and timestep to call */
/*             CALL VCIRC(HJM,HR,HRU,IMIN,IMAX,IT,LCZ,M,OMEGA,LDO,QWLNR,  ! KC 2025-05-31 */
	    vcirc_(&hr[1], hru, imin, imax, &it, &lcz[1], m, &omega[1], &ldo, 
		    qwlnr, qwrmax, &hv[1], &cltot, dt, &hp[1]);
	    if (varfc_1.lvfc) {
		getfc_(&hd[1], hru, &hv[1], imin, imax, &omega[1]);
	    }
/*  NOW THAT THE NEW DIFFUSION VELOCITIES HAVE BEEN COMPUTED, RESET THE */
/*  ANGULAR MOMENTUM AND COMPOSITION ARRAYS TO THEIR ORIGINAL VALUES. */
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		hjm[i__] = hjmsav[i__];
		for (j = 1; j <= 4; ++j) {
		    hcomp[j + i__ * 15] = oldab_1.hcomps[j + i__ * 15 - 16];
/* L40: */
		}
/* L50: */
	    }
/* MHP 10/91 CHANGED TO REMIX CZ'S TO THEIR PROPER DEPTH! */
/* OTHERWISE, DRASTIC ERRORS OCCUR IN THE PRESENCE OF A DEEPENING CZ */
/* (THE LOCAL ABUNDANCE AT THE CZ BASE PRIOR TO THE DEEPENING OF THE */
/*  CZ IS ASSIGNED TO THE WHOLE CZ - X AND HE3 ONLY, AND ONLY FOR A */
/*  CZ WHICH IS BECOMING DEEPER.) */
/*  ENSURE THAT CONVECTIVE REGIONS ARE FULLY MIXED. */
/*  JVS 0212 CALL MIXCZ(HCOMP,HS2,LCZ,M) */
/* KC 2025-05-30 addressed warning messages from Makefile.legacy */
/* C G Somers 6/14, SET IMIX = .FALSE. SO THE CORRECT GRADS ARE USED. */
/*          IMIX = .FALSE. */
/*          CALL MIXCZ(HCOMP,HS2,HS1,LCZ,HR,HP,HD,HG,M,IMIX) */
/* G Somers 6/14, SET LIMIX = .FALSE. SO THE CORRECT GRADS ARE USED. */
	    limix = FALSE_;
/*          CALL MIXCZ(HCOMP,HS2,HS1,LCZ,HR,HP,HD,HG,M,LIMIX)  ! KC 2025-05-31 */
	    mixcz_(&hcomp[16], &hs2[1], &lcz[1], m);
/* G Somers END */
	}
/*  CALCULATE LOSS OF ANGULAR MOMENTUM DUE TO WIND FOR AN */
/*  ISOLATED SURFACE C.Z.(NO COUPLING WITH INTERIOR VIA DIFFUSION). */
	if (*lczsur && hv[*imax] == 0. && ! lock) {
/*  FIND MOMENT OF INERTIA OF THE SURFACE C.Z. */
	    *hicz = 0.;
	    i__2 = *m;
	    for (i__ = *imax; i__ <= i__2; ++i__) {
		*hicz += hi[i__];
/* L55: */
	    }
	    ljdot = cwind_1.ljdot0;
/* MHP 10/02 UNUSED LFIRST REMOVED FROM CALL */
	    mwind_(bl, dt, hsbot, hstop, imax, m, &ljdot, omegas, smass, 
		    teffl, hicz, &hjm[1]);
/*      *                SJTOT,SMASS,TEFFL,HICZ,HJM,LFIRST)  ! KC 2025-05-31 */
/* REMOVE TORQUE FROM ENTIRE STAR */
/* JNT 09/25 FOR 05/15 IMPJMOD=1 SAME AS LSOLID */
	} else if (*lczsur && (sbrot_1.lsolid || sbrot_1.impjmod == 1)) {
	    ljdot = cwind_1.ljdot0;
	    hsbotj = 0.;
	    hstopj = exp(const1_1.cln * *hstot);
	    imaxj = 1;
	    mwind_(bl, dt, &hsbotj, &hstopj, &imaxj, m, &ljdot, omegas, smass,
		     teffl, hicz, &hjm[1]);
/*      *                SJTOT,SMASS,TEFFL,HICZ,HJM)  ! KC 2025-05-31 */
/*            WRITE(*,*)HJM(1),HJM(M) */
	    jstart = 1;
	    jend = *m;
	    solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &jstart, &jend, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
/*            WRITE(*,*)OMEGA(1),OMEGA(M) */
	}
/*  IF LDO=F,NO INSTABILITIES OCCUR (STABLE AGAINST ALL MECHANISMS). */
	if (! ldo) {
	    goto L9999;
	}
/*  TREAT CENTRAL AND SURFACE ZONES AS ALWAYS CONVECTIVE */
/*  (SHOULD BE FIXED TO GIVE BETTER CENTRAL/SURFACE B.C.) */
	lcz[1] = TRUE_;
	lcz[*m] = TRUE_;
/*  UNSTABLE REGION EXISTS. */
/*  FIND DIFFUSION COEFFICIENTS(COD) FOR ALL UNSTABLE REGIONS. */
/*          CALL CODIFF(DELTS,HRU,HV,IMIN,IMAX,LC,LCZ,M,RMID,COD,COD2)  ! KC 2025-05-31 */
	codiff_(hru, m, rmid, cod, &cod2[1]);
/*  EACH UNSTABLE REGION IS SOLVED SEPARATELY STARTING HERE. */
/*  LTEST IS SET T IF A NON-ZERO VELOCITY IS ENCOUNTERED. */
/*  IBEG IS THE ZONE BELOW THE FIRST NON-ZERO V;IEND IS THE ZONE ABOVE */
/*  THE LAST NON-ZERO V. */
	ldum = FALSE_;
	istart = *imin;
L60:
	ltest = FALSE_;
/* MHP 8/13 TREAT ENTIRE DOMAIN AS UNSTABLE IF A CONSTANT DIFFUSION */
/* COEFFICIENT IS BEING ADDED */
	if (lcodm && codm > 0.) {
	    ltest = TRUE_;
	    ibeg = *imin - 1;
	    iend = *imax;
	    istart = *imax + 1;
	    goto L80;
	}
	i__2 = *imax;
	for (j = istart; j <= i__2; ++j) {
	    if (hv[j] > 0.) {
		ltest = TRUE_;
		if (! ldum) {
/*  START OF UNSTABLE REGION */
		    ldum = TRUE_;
		    ibeg = j - 1;
		}
	    } else if (ldum) {
/*  END OF UNSTABLE REGION */
		iend = j - 1;
		ldum = FALSE_;
		istart = j + 1;
		goto L80;
	    }
/* L70: */
	}
/*  IF THE LAST INTERFACE IS UNSTABLE (NON-ZERO V) ENSURE THAT IEND IS SET */
/*  PROPERLY. */
	if (ldum) {
	    iend = *imax;
	}
	istart = *imax + 1;
L80:
/*  IF NO NON-ZERO V'S ENCOUNTERED, EXIT. */
	if (! ltest) {
	    goto L90;
	}
/* MHP 08/03 REMOVED OBSOLETE EQUAL ROUTINE */
/*         IF(M.GT.1)THEN */
/*  TRANSFORM TO EQUAL GRID SPACING IN CHI FOR THE REGION. */
/* CHI IS A NORMALIZED SUM OF THE VARIABLES USED TO PLACE POINTS */
/* IN THE HENYEY SCHEME, CHOSEN SUCH THAT THE GRID USED IN THE */
/* ANGULAR MOMENTUM EVOLUTION IS CLOSE TO THE GRID STORED FOR */
/* THE STRUCTURAL EVOLUTION. */
	rotgrid_(cod, &cod2[1], &hd[1], &hi[1], &hjmsav[1], &hl[1], &hp[1], &
		hr[1], hru, &hs[1], &hs1[1], &hs2[1], hstot, &ibeg, &iend, &
		lcz[1], m, wsav, &dr, ecod, ecod2, ei, ej, em, ew, &ldum2);
/*         ELSE */
/*         CALL EQUAL(BL,COD,COD2,HD,HI,HJMSAV,HRU,HS,HS1,HS2,HSTOT, */
/*     *              IBEG,IEND,LCZ,M,TEFFL,DR,ECOD,ECOD2,EI,EJ, */
/*     *              EM,ES1,EW,WSAV,LDUM2,NTOT) */
/*         ENDIF */
/*  LDUM2=T IF TWO C.Z.'S ARE SEPARATED BY ONE RADIATIVE ZONE; */
/*  SKIP IF THIS OCCURS. */
	if (ldum2) {
	    if (istart <= *imax) {
		goto L60;
	    } else {
		goto L90;
	    }
	}
/* MHP 3/09 SKIP ANGULAR MOMENTUM EVOLUTION FOR SOLID BODY MODELS */
/* JNT 09/25 FOR 05/15 IMPJMOD=1 IS THE SAME AS LSOLID */
	if (! sbrot_1.lsolid && sbrot_1.impjmod != 1) {
/*  CHECK IF SURFACE C.Z. IS PART OF THE UNSTABLE REGION. */
/*  IF SO,CALCULATE TERMS FOR DIFFUSION. */
	    if (*lczsur && iend == *imax) {
		if (lock) {
		    wind1 = 0.;
		    wind2 = 0.;
		    lfix = TRUE_;
		} else {
		    lfix = FALSE_;
		    if (cwind_1.ljdot0) {
			*hicz = ei[egrid_1.ntot - 1];
			*omegas = omega[*m];
			mcowind_(bl, dt, hicz, &it, omegas, smass, teffl, &
				wbeg, &wind1, &wind2);
		    } else {
			wind1 = 0.;
			wind2 = 0.;
		    }
		}
	    } else {
		lfix = FALSE_;
		wind1 = 0.;
		wind2 = 0.;
	    }
	    lokad = FALSE_;
	    if (! varfc_1.ldifad) {
/*  SET UP DIFFUSION EQUATION ARRAYS TO SOLVE FOR OMEGA AT END OF TSTEP */
		dcoeft_(ecod, &dr, dt, ei, ej, ew, &egrid_1.ntot, &wind1, &
			wind2, &lfix);
/*  SOLVE MATRIX FOR THE RUN OF OMEGA AT THE END OF THE TIMESTEP AT THE */
/*  EQUALLY SPACED GRID POINTS. */
/*             CALL TRIDIA(NTOT,EI,EJ,DJ,SUMDJ)  ! KC 2025-05-31 */
		tridia_(&egrid_1.ntot, ei, dj, &sumdj);
/*  TRANSFORM THE NEW ANGULAR MOMENTUM DISTRIBUTION BACK TO THE ORIGINAL GRID */
/*  POINTS IN THE UNSTABLE REGION. */
	    } else {
/* SOLVE FOR OMEGA AND ITS DERIVATIVES IN A BAND MATRIX */
/*             CALL DADCOEFT(DR,DT,EI,EJ,EW,NTOT,WIND1,WIND2,DJ,  ! KC 2025-05-31 */
		dadcoeft_(&dr, dt, ei, ew, &egrid_1.ntot, &wind1, &wind2, dj, 
			ecod2, &sumdj, &lfix, &lokad);
	    }
/* MHP 08/03 REMOVED OBSOLETE EQUAL2 ROUTINE */
/*         IF(M.GT.1)THEN */
/* TRANSFORM BACK TO THE ORIGINAL GRID */
	    eq2mod_(dj, ej, &hs2[1], &ibeg, &iend, &lcz[1], m, &sumdj, &hjm[1]
		    );
/*         ELSE */
/*         CALL EQUAL2(DJ,EJ,EM,ES1,HS1,IBEG,IEND,LCZ,M,NTOT,HJM) */
/*         ENDIF */
/*  PERFORM COMPOSITION DIFFUSION. */
/*  UNTIL THE FINAL ITERATION, ONLY COMPOSITION DIFFUSION OF SPECIES WHICH */
/*  AFFECT GRADIENTS IN MEAN MOLECULAR WEIGHT IS COMPUTED (H,HE3,HE4). */
/*  ON THE FINAL ITERATION, DIFFUSION OF ALL SPECIES IS PERFORMED. */
/* MHP 08/03 REMOVED OBSOLETE DIFCOM ROUTINE */
/*         IF(M.GT.1)THEN */
	}
	jbeg = 1;
	jend = 4;
	ndifcom_(dt, &cod2[1], ecod2, em, &hd[1], &hl[1], &hp[1], &hr[1], &hs[
		1], &hs1[1], &hs2[1], hstot, &hv[1], &ibeg, &iend, imax, imin,
		 &lcz[1], lok, m, &hcomp[16], &jbeg, &jend);
/*      *                HSTOT,HV,IBEG,IEND,IMAX,IMIN,LCZ,LOK,M,NTOT,  ! KC 2025-05-31 */
/*         ELSE */
/*         CALL DIFCOM(DR,DT,COD2,ECOD2,EM,ES1,HRU,HS,HS1,HS2,HV, */
/*     *               IBEG,IEND,IMIN,LCZ,LOK,M,NTOT,HCOMP) */
/*         ENDIF */
/*  RETURN FOR NEXT REGION IF APPLICABLE */
	if (istart <= *imax) {
	    goto L60;
	}
L90:
/* CHECK SOLUTION,UPDATE OMEGA,AND SEE IF ANOTHER ITERATION IS NEEDED. */
	lcz[1] = lcz1;
	lcz[*m] = lczm;
/* mhp 10/02 unused ecod, ecod2 no longer passed */
/*         WRITE(*,*)LSOLID,OMEGA(1),OMEGA(M) */
	checkj_(&hd[1], hjmp, &hjmsav[1], &hr[1], &hs[1], &hs2[1], &hv[1], 
		imin, imax, &it, &lcz[1], m, dt, &eta2[1], &hi[1], &hjm[1], 
		iredo, lok, lredo, &omega[1], &qiw[1], &r0[1], wsav, id, &idm,
		 &lokad);
/*      *         LPRT,M,DT,ETA2,HI,HJM,IREDO,LOK,LREDO,OMEGA,QIW,R0,  ! KC 2025-05-31 */
/*     *         WSAV,ID,IDM,ECOD,ECOD2,LOKAD) */
/*         WRITE(*,*)OMEGA(1),OMEGA(M) */
/* CHECK COMPOSITION DIFFUSION AND RECOMPUTE MEAN MOLECULAR WEIGHT. */
	if (! (*lredo)) {
	    checkc_(&hcomp[16], &it, &lprt, m, dt, iredo, lok, lredo);
	}
/* MHP 9/93 */
	if (notran_1.lnoj) {
	    *lok = TRUE_;
	}
/* IF LOK=T,CONVERGED. */
	if (*lok) {
	    goto L200;
	}
/* IF LREDO=T, A PROBLEM REQUIRES TIMESTEP CUTTING. */
	if (*lredo) {
	    goto L9999;
	}
/* L100: */
    }
    *lok = TRUE_;
L200:
/* PERFORM COMPOSITION DIFFUSION OF REMAINING SPECIES. */
    lcz[1] = TRUE_;
    lcz[*m] = TRUE_;
/* MHP 6/00 ADDED OPTION OF BS EXTRAPOLATION FOR HE3, CNO */
/*      LBSMIX=.TRUE. */
/*      IF(LBSMIX)THEN */
/*         CALL BSCOMP(DR,DT,COD2,ECOD2,EM,ES1,HRU,HS,HS1,HS2, */
/*     *               IBEG,IEND,IMIN,LCZ,LOK,M,NTOT,HCOMP,HV, */
/*     *           HD,HP,HR,HT,MRZONE,MXZONE,NRZONE,NZONE,HSTOT) */
/*      ELSE */
/* MHP 08/03 REMOVED OBSOLETE DIFCOM ROUTINE */
/*      IF(M.GT.1)THEN */
    jbeg = 5;
    if (flag_1.lexcom) {
	jend = 15;
    } else {
	jend = 11;
    }
    ndifcom_(dt, &cod2[1], ecod2, em, &hd[1], &hl[1], &hp[1], &hr[1], &hs[1], 
	    &hs1[1], &hs2[1], hstot, &hv[1], &ibeg, &iend, imax, imin, &lcz[1]
	    , lok, m, &hcomp[16], &jbeg, &jend);
/*      *             HSTOT,HV,IBEG,IEND,IMAX,IMIN,LCZ,LOK,M,NTOT,  ! KC 2025-05-31 */
/*      ELSE */
/*      CALL DIFCOM(DR,DT,COD2,ECOD2,EM,ES1,HRU,HS,HS1,HS2,HV, */
/*     *            IBEG,IEND,IMIN,LCZ,LOK,M,NTOT,HCOMP) */
/*      ENDIF */
/* MHP 6/00 */
    lcz[1] = lcz1;
    lcz[*m] = lczm;
/* ADD I/O FOR MIXING. */
    if (lprt) {
/* MHP 8/03 ADDED HEADER LINE. */
	io___51.ciunit = luout_1.imodpt;
	s_wsfe(&io___51);
	e_wsfe();
	i__1 = idm;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dx = hcomp[id[i__ - 1] * 15 + 1] - oldab_1.hcomps[id[i__ - 1] * 
		    15 - 15];
	    dhe3 = hcomp[id[i__ - 1] * 15 + 4] - oldab_1.hcomps[id[i__ - 1] * 
		    15 - 12];
	    dc12 = hcomp[id[i__ - 1] * 15 + 5] - oldab_1.hcomps[id[i__ - 1] * 
		    15 - 11];
	    dc13 = hcomp[id[i__ - 1] * 15 + 6] - oldab_1.hcomps[id[i__ - 1] * 
		    15 - 10];
	    dn14 = hcomp[id[i__ - 1] * 15 + 7] - oldab_1.hcomps[id[i__ - 1] * 
		    15 - 9];
	    dli7 = hcomp[id[i__ - 1] * 15 + 14] - oldab_1.hcomps[id[i__ - 1] *
		     15 - 2];
	    dbe9 = hcomp[id[i__ - 1] * 15 + 15] - oldab_1.hcomps[id[i__ - 1] *
		     15 - 1];
	    io___59.ciunit = luout_1.imodpt;
	    s_wsfe(&io___59);
	    do_fio(&c__1, (char *)&id[i__ - 1], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&dx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dhe3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dc12, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dc13, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dn14, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dli7, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dbe9, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
L9999:
/* MHP 8/03 - OMITTED I/O, COULD REINTRODUCE IN ANOTHER FILE */
/*  DETERMINE COUPLING FACTOR (I.E. THE FRACTION OF THE TOTAL ANGULAR */
/*  MOMENTUM LOST FROM THE CORE RELATIVE TO ITS FRACTION OF THE TOTAL */
/*  MOMENT OF INERTIA). */
/*      DJCORE = 0.0D0 */
/*      HICORE = 0.0D0 */
/*      HJTOT = 0.0D0 */
/*      DO I = 1,IMAX-1 */
/*         DJCORE = DJCORE + (HJM(I)-HJMSAV(I))*HS2(I) */
/*         HICORE = HICORE + HI(I) */
/*         HJTOT = HJTOT + HJM(I)*HS2(I) */
/*      END DO */
/*      HIENV = 0.0D0 */
/*      DJENV = 0.0D0 */
/*      DO I = IMAX,M */
/*         DJENV = DJENV + (HJM(I)-HJMSAV(I))*HS2(I) */
/*         HIENV = HIENV + HI(I) */
/*         HJTOT = HJTOT + HJM(I)*HS2(I) */
/*      END DO */
/*      FI = HICORE/(HICORE+HIENV) */
/*      IF(ABS(DJCORE+DJENV).GT.1.0D-32)THEN */
/*         FJ = DJCORE/(DJCORE+DJENV) */
/*      ELSE */
/*         FJ = 1.0D0 */
/*      ENDIF */
/*      WRITE(88,709)SAGE,HJTOT,OMEGA(M),FJ,FJ/FI, */
/*     *               HCOMP(14,M),HCOMP(15,M) */
/*  709 FORMAT(1P7E11.3) */
    return 0;
} /* seculr_ */


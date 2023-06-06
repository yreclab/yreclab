/* getw.f -- translated by f2c (version 20100827).
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
    doublereal cdelrl, cmixz, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

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
    doublereal dtwind;
} ct2_;

#define ct2_1 ct2_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal wmax, exmd, exw, exr, exm, factor;
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal amum[5000], cpm[5000], delm[5000], delam[5000], delrm[5000], 
	    esumm[5000], om[5000], qdtm[5000], thdifm[5000], velm[5000], 
	    viscm[5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    doublereal delo[5000], delao[5000], amuo[5000], oo[5000], cpo[5000], qdto[
	    5000], velo[5000], visco[5000], thdifo[5000], esumo[5000], delro[
	    5000], epso[5000];
} oldphy_;

#define oldphy_1 oldphy_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
} oldmod_;

#define oldmod_1 oldmod_

struct {
    doublereal wold[5000], hjx[5000], hio[5000], hgo[5000], r0x[5000], eta2x[
	    5000];
} oldrot_;

#define oldrot_1 oldrot_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal cp[5000], hamu[5000], sqdt[5000], thdif[5000], visc[5000];
} temp_;

#define temp_1 temp_

struct {
    doublereal rli6[5000], rli7[5000], rbe9[5000];
} newrat_;

#define newrat_1 newrat_

struct {
    doublereal rli60[5000], rli70[5000], rbe90[5000];
} oldrat_;

#define oldrat_1 oldrat_

struct {
    doublereal hcomps[75000]	/* was [15][5000] */;
} oldab_;

#define oldab_1 oldab_

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
    doublereal quad[5000], gg[5000];
} quadru_;

#define quadru_1 quadru_

struct {
    logical lprt0;
} rotprt_;

#define rotprt_1 rotprt_

struct {
    doublereal sage, tdisk, pdisk;
    logical ldisk;
} disk_;

#define disk_1 disk_

struct {
    logical lsolid;
} sbrot_;

#define sbrot_1 sbrot_

struct {
    doublereal tho[5000], thn[5000], thm[5000], ddelm[5000], festime[5000], 
	    thp[5000], qwrst[5000], wmst[5000], qwrmst[5000];
} oldrot2_;

#define oldrot2_1 oldrot2_

/* Table of constant values */

static doublereal c_b5 = 10.;
static integer c__2 = 2;
static integer c__1 = 1;

/* $$$$$$ */
/* 11/91 MHP REVISED SUBROUTINE (REPLACES OLD FINDW). */
/* GETW EVOLVES THE ANGULAR MOMENTUM DISTRIBUTION IN TIME. */
/* IT ENFORCES LOCAL CONSERVATION OF ANGULAR MOMENTUM IN RADIATIVE REGIONS, */
/* AND ENFORCES THE USER-SPECIFIED ROTATION LAW IN CONVECTIVE REGIONS. */
/* BOTH MERIDIONAL CIRCULATION AND DIFFERENTIAL ROTATION WITH DEPTH CAN */
/* CAUSE THE RADIAL TRANSPORT OF ANGULAR MOMENTUM AND MATERIAL. */
/* GETW SOLVES FOR THE TRANSPORT OF ANGULAR MOMENTUM AND THE ASSOCIATED MIXING */
/* IF DESIRED (LINSTB=T), AND ACCOUNTS FOR ANGULAR MOMENTUM LOSS CAUSED BY A */
/* MAGNETIC STELLAR WIND IF DESIRED (LJDOT0=T). */
/* IF INSTABILITIES ARE BEING TREATED, THE BURNING OF THE LIGHT ELEMENTS */
/* LITHIUM AND BERYLLIUM ARE CONSIDERED HERE IF DESIRED (LEXCOM=T). */
/* FOR A DISCUSSION OF THE OVERALL TECHNIQUE USED SEE PINSONNEAULT, KAWALER, */
/* SOFIA, AND DEMARQUE (1989), AP.J. VOL. 338, P.424. */
/* 11/91 JENV0 ADDED TO CALL. */
/* Subroutine */ int getw_(doublereal *bl, doublereal *delts, doublereal *
	dwmax, doublereal *fp, doublereal *ft, doublereal *hcomp, doublereal *
	hd, doublereal *hjm, doublereal *hl, doublereal *hp, doublereal *hr, 
	doublereal *hs, doublereal *hs1, doublereal *hs2, doublereal *hstot, 
	doublereal *ht, logical *lc, logical *ljdot, integer *m, integer *
	model, doublereal *sjtot, doublereal *smass, doublereal *teffl, 
	doublereal *eta2, doublereal *hg, doublereal *hi, doublereal *omega, 
	doublereal *qiw, doublereal *r0, integer *jenv0)
{
    /* Format strings */
    static char fmt_9911[] = "(1x,\002QUAD \002,1pe12.3,\002 PHIS \002,e12"
	    ".3,\002 3/2 QUAD/G \002,e12.3)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), d_mod(doublereal *, doublereal *), pow_dd(
	    doublereal *, doublereal *), d_lg10(doublereal *);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j, ii;
    static doublereal dt, hv[5000], dr, fx, rl, qw, r0m[5000], hdm[5000], hgm[
	    5000];
    static logical lcm[5000];
    static doublereal him[5000], hlm[5000], hpm[5000], hrm[5000];
    static logical lcz[5000];
    static doublereal htm[5000];
    extern /* Subroutine */ int wcz_(doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    ;
    static logical lok;
    static doublereal cod2[5000];
    static integer iend;
    static logical lock;
    static doublereal hicz;
    static integer imax;
    static logical lczm[5000];
    static doublereal qiwm[5000];
    extern /* Subroutine */ int wind_(doublereal *, doublereal *, doublereal *
	    , doublereal *, integer *, integer *, logical *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal test, wmid;
    static integer imin;
    static doublereal eta2m[5000];
    static integer jenv1;
    static logical lburs;
    static integer nspec, nzone;
    static doublereal hstop, hsbot;
    static logical lskip;
    extern /* Subroutine */ int ovrot_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, logical *, integer *,
	     logical *, integer *, integer *, integer *, integer *);
    static integer nstep;
    static doublereal sumdt;
    static integer iredo;
    extern /* Subroutine */ int mixcz_(doublereal *, doublereal *, logical *, 
	    integer *);
    static logical lredo;
    static doublereal qsurf;
    static integer jcore1;
    static doublereal psurf;
    static integer nzone0, nstep2, mxzon0[24]	/* was [12][2] */;
    static doublereal omegam[5000];
    extern /* Subroutine */ int midmod_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, logical *, logical *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    logical *, logical *, logical *, logical *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *);
    static doublereal omegas;
    static logical lallcz;
    extern /* Subroutine */ int convec_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     integer *, integer *, integer *);
    static doublereal hjmsav[5000];
    extern /* Subroutine */ int physic_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *), getrot_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static logical lfirst;
    extern /* Subroutine */ int seculr_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, logical *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, logical *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, logical *), 
	    liburn_(doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *);
    static integer mrzone[26]	/* was [13][2] */, nrzone, mxzone[24]	/* 
	    was [12][2] */;
    static logical lczsur;
    extern /* Subroutine */ int liburn2_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *), lirate88_(
	    doublereal *, doublereal *, doublereal *, integer *, integer *), 
	    bursmix_(doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, logical 
	    *, logical *, integer *, integer *, integer *, integer *, integer 
	    *);

    /* Fortran I/O blocks */
    static cilist io___58 = { 0, 6, 0, fmt_9911, 0 };


/* MHP 6/00 ADDED COD2, HV TO ALLOW BUR-ST MIXING PLUS BURNING. */
/* 11/91 COMMON BLOCKS ADDED FOR PRESSURE SCALE HEIGHT CALC. FOR LIBURN */
/* 7/91 NEW LITHIUM BURNING COMMON BLOCKS ADDED. */
/* 8/92 COMMON BLOCK FOR COMPUTATION OF BEGINNING OF STEP MU */
/* BARRIER. */
/* MHP 3/99 ADDED FLAG TO TREAT THE ENTIRE STAR AS 'CONVECTIVE' */
/* FOR ANGULAR MOMENTUM PURPOSES. */
/* MHP 06/02 */
/* Time change of theta */
    /* Parameter adjustments */
    --r0;
    --qiw;
    --omega;
    --hi;
    --hg;
    --eta2;
    --lc;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hjm;
    --hd;
    hcomp -= 16;
    --ft;
    --fp;

    /* Function Body */
    lburs = FALSE_;
/* DETERMINE THE NUMBER OF DIFFERENT ELEMENTS AND ISOTOPES BEING TRACKED */
/* BY THE CODE (NSPEC). */
    nspec = 11;
    if (flag_1.lexcom) {
	nspec = 15;
    }
/*  CONVECTIVE AND RADIATIVE REGIONS ARE TREATED DIFFERENTLY FOR ANGULAR */
/*  MOMENTUM PURPOSES; IF CONVECTIVE OVERSHOOT IS BEING INCLUDED THE */
/*  OVERSHOOT REGION IS TREATED AS CONVECTIVE FOR ANGULAR MOMENTUM PURPOSES. */
/*  ***NOTE : IF LINSTB=T THERE MUST BE AT LEAST ONE SHELL IN THE OVERSHOOT */
/*  REGION, TO COUPLE THE RADIATIVE AND CONVECTIVE REGIONS AND TO AVOID */
/*  NUMERICAL PROBLEMS IN SOME OF THE TERMS WHICH ARISE IN THE SOLUTION OF */
/*  THE DIFFUSION EQUATIONS. */

/*  OVROT CALCULATES CONVECTIVE OVERSHOOT BY ARBITRARILY MIXING TO A */
/*  USER-SPECIFIED FRACTION OF A PRESSURE SCALE HEIGHT ABOVE OR BELOW A */
/*  CONVECTIVE REGION.  IT RETURNS A VECTOR LCZ, WHICH IS TRUE IF A SHELL IS */
/*  CONVECTIVE FOR ANGULAR MOMENTUM PURPOSES. */
/* 7/91 CHANGED CALL TO OVROT. */
    ovrot_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], &lc[1], m, lcz,
	     mrzone, mxzone, &nrzone, &nzone);
/* MHP 9/94 ADDED DISK LOCKING OPTION. */
    lock = FALSE_;
    if (disk_1.ldisk && disk_1.sage <= disk_1.tdisk) {
	lock = TRUE_;
    }
    if (! rot_1.linstb) {
/*  STORE THE SURFACE ANGULAR VELOCITY FROM THE BEGINNING OF THE TIMESTEP. */
	omegas = omega[*m];
/*  ENFORCE SB ROTATION (OR UNIFORM ROTATION LAW IN ENTIRE STAR) IF DESIRED. */
	if (sbrot_1.lsolid) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		lcz[i__ - 1] = TRUE_;
	    }
	}
/*  GETROT TAKES THE ANGULAR MOMENTUM DISTRIBUTION AND FINDS THE */
/*  ROTATION CURVE THAT CORRESPONDS TO IT.  CONVECTIVE REGIONS HAVE */
/*  SOLID BODY ROTATION ENFORCED ON THEM. */
	getrot_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], lcz, m, &eta2[1], &
		hi[1], &omega[1], &qiw[1], &r0[1]);
/*  ANGULAR MOMENTUM LOSS WITHOUT INTERNAL ANGULAR MOMENTUM TRANSPORT. */
/*         DO I = 1,M */
/*            WOLD(I) = OMEGA(I) */
/*         END DO */
	if (! lock && cwind_1.ljdot0 && lc[*m]) {
/*  FIND MOMENT OF INERTIA OF THE SURFACE C.Z. */
	    hicz = 0.;
/*  ENFORCE SB ROTATION (OR UNIFORM ROTATION LAW IN ENTIRE STAR) IF DESIRED. */
	    if (sbrot_1.lsolid) {
		ii = 1;
	    } else {
		ii = mxzone[nzone - 1];
	    }
	    i__1 = *m;
	    for (i__ = ii; i__ <= i__1; ++i__) {
		hicz += hi[i__];
	    }
/*  FIND LOWEST SHELL IN SURFACE CZ (IMAX) */
	    imax = mxzone[nzone - 1];
/*  HSTOP IS THE MASS AT THE TOP OF THE C.Z. */
/*  HSBOT IS THE MASS AT THE BOTTOM OF THE C.Z. */
	    hstop = exp(const1_1.cln * *hstot);
	    if (imax > 1) {
		hsbot = (hs1[imax] + hs1[imax - 1]) * .5;
	    } else {
		hsbot = 0.;
	    }
	    *ljdot = cwind_1.ljdot0;
/* MHP 10/02 UNUSED LFIRST REMOVED FROM CALL */
	    wind_(bl, delts, &hsbot, &hstop, &imax, m, ljdot, &omegas, sjtot, 
		    smass, teffl, &hicz, &hjm[1]);
/*     *                SJTOT,SMASS,TEFFL,HICZ,HJM,LFIRST) */
/*  FIND THE NEW RUN OF OMEGA IN THE CONVECTION ZONE AFTER THE WIND. */
/* MHP 10/02 REPLACED IEND WITH M IN CALL, DEFINED IEND=M */
	    iend = *m;
	    wcz_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &imax, &iend, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
	}
	goto L9999;
    }
/*  GETROT TAKES THE ANGULAR MOMENTUM DISTRIBUTION AND FINDS THE */
/*  ROTATION CURVE THAT CORRESPONDS TO IT.  CONVECTIVE REGIONS HAVE */
/*  SOLID BODY ROTATION ENFORCED ON THEM. */
    getrot_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], lcz, m, &eta2[1], &hi[1]
	    , &omega[1], &qiw[1], &r0[1]);
    lskip = ! rot_1.linstb && ! (*ljdot);
    if (lskip || *delts <= 0.) {
	goto L9999;
    }
/*  NOW LIMIT THE DIFFUSION TIMESTEP TO A MAXIMUM CHANGE IN OMEGA */
/*  FROM THE PREVIOUS MODEL. */
    if (*dwmax == 0.) {
	*dwmax = ct2_1.dtwind;
    }
    nstep = (integer) (*dwmax / difus_1.dtdif);
    if (d_mod(dwmax, &difus_1.dtdif) != 0.) {
	++nstep;
    }
    nstep2 = (integer) (ct2_1.dtwind / difus_1.dtdif);
    if (d_mod(&ct2_1.dtwind, &difus_1.dtdif) != 0.) {
	++nstep2;
    }
/*     NSTEP = MAX(NSTEP,NSTEP2/2) */
    nstep = min(nstep,nstep2);
    dt = *delts / (doublereal) nstep;
/*  FIND BASIC PHYSICAL QUANTITIES NEEDED FOR BOTH SECULAR AND DYNAMICAL */
/*  INSTABILITES: ADIABATIC AND ACTUAL TEMPERATURE GRADIENTS,OPACITIES, */
/*  KINEMATIC VISCOSITIES,THERMOMETRIC DIFFUSIVITY, AND HEAT CAPACITY. */
    physic_(&fp[1], &ft[1], &hcomp[16], &hd[1], &hg[1], &hl[1], &hp[1], &hr[1]
	    , &hs[1], &ht[1], &lc[1], lcz, m);
/* IF DT IS LESS THAN DELTS, THEN THE MODEL TIMESTEP IS TOO LONG FOR THE */
/* DIFFUSION CALCULATIONS.  IF THIS OCCURS, */
/* USE A SERIES OF SMALLER TIMESTEPS THAT DON'T VIOLATE THIS CONDITION. */
/* INTERPOLATE THE MODEL STRUCTURE BETWEEN THE OLD MODEL AND THE NEW ONE */
/* TO CALCULATE DIFFUSION AND WIND BETWEEN MODELS. */
    sumdt = 0.;
    lfirst = TRUE_;
/*      DO 20 I = 1,M */
/*         WOLD(I) = OMEGA(I) */
/*   20 CONTINUE */
/*  ENTRY FOR SERIES OF DIFFUSION TIMESTEPS. */
L30:
    iredo = 0;
/*  ENTRY FOR DIFFUSION TIMESTEP CUTTING. */
L40:
/* MHP 06/02 CHANGED TO ELIMINATE OCCASIONAL */
/* ALMOST ZERO TIMESTEP FROM ROUNDOFF ERROR */
    test = *delts - *delts * 1e-6;
    if (sumdt + dt >= test) {
	dt = *delts - sumdt;
	sumdt = *delts;
    } else {
	sumdt += dt;
    }
/* COPY OVER PRIOR THETA(TIME) TERM TO TEMPORARY SLOT */
/* FOR USE IN THE ADVECTION/DIFFUSION TREATMENT OF MAEDER&ZAHN 1998 */
    if (lfirst) {
	oldrot2_1.thp[0] = oldrot2_1.tho[0];
	oldrot2_1.wmst[0] = oldrot_1.wold[0];
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    oldrot2_1.qwrmst[i__ - 1] = oldrot2_1.qwrst[i__ - 1];
	    oldrot2_1.thp[i__ - 1] = oldrot2_1.tho[i__ - 1];
	    oldrot2_1.wmst[i__ - 1] = oldrot_1.wold[i__ - 1];
	}
/* RECOMPUTE THETA */
    } else {
	oldrot2_1.wmst[0] = omega[1];
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    wmid = (omega[i__] + omega[i__ - 1]) * .5;
	    dr = pow_dd(&c_b5, &hrm[i__ - 1]) - pow_dd(&c_b5, &hrm[i__ - 2]);
	    qw = (omega[i__] - omega[i__ - 1]) / dr;
	    oldrot2_1.thp[i__ - 1] = oldrot2_1.thm[i__ - 1] * wmid * qw;
	    oldrot2_1.qwrmst[i__ - 1] = qw;
	    oldrot2_1.wmst[i__ - 1] = omega[i__];
	}
    }
    fx = sumdt / *delts;
/* INTERPOLATE LINEARLY IN TIME FOR THE MODEL STRUCTURE BETWEEN THE */
/* START AND END OF THE TIMESTEP. */
    midmod_(delts, &dt, &fx, &hcomp[16], &hd[1], &hg[1], &hjm[1], &hl[1], &hp[
	    1], &hr[1], &hs[1], &hs1[1], &hs2[1], hstot, &ht[1], &lc[1], lcz, 
	    &lfirst, m, eta2m, hdm, hgm, &hicz, him, hlm, hpm, hrm, &hsbot, &
	    hstop, htm, &imin, &imax, &lallcz, lcm, lczm, &lczsur, omegam, 
	    r0m, qiwm, mrzone, mxzone, &nrzone, &nzone);
/* IF DESIRED, REMOVE ANGULAR MOMENTUM FROM OUTER CONVECTION ZONE */
/* USING A WEBER-DAVIS MAGNETIC WIND MODEL */
    if (! lock && *ljdot && lczsur) {
	omegas = omegam[*m - 1];
/*  WIND CALCULATION WITHOUT INSTABILITIES */
	if (lallcz || ! rot_1.linstb) {
/* MHP 10/02 UNUSED LFIRST REMOVED FROM CALL */
	    wind_(bl, &dt, &hsbot, &hstop, &imax, m, ljdot, &omegas, sjtot, 
		    smass, teffl, &hicz, &hjm[1]);
/*     *                SJTOT,SMASS,TEFFL,HICZ,HJM,LFIRST) */
/*  FIND THE NEW OMEGA OF THE CONVECTION ZONE AFTER THE WIND. */
/* MHP 10/02 REPLACED IEND WITH M IN CALL, DEFINED IEND=M */
	    iend = *m;
	    wcz_(hdm, &hjm[1], hrm, &hs[1], &hs2[1], &imax, &iend, eta2m, him,
		     omegam, qiwm, r0m, m);
	}
    }
/*  NOW CHECK FOR INSTABILITIES IN RADIATIVE REGIONS */
    if (rot_1.linstb && ! lallcz) {
/*  ENSURE THAT CONVECTIVE REGIONS ARE FULLY MIXED. */
	mixcz_(&hcomp[16], &hs2[1], lczm, m);
/*  NOW SOLVE FOR LONG-TIMESCALE(SECULAR) INSTABILITIES. */
/*  THESE ARE TREATED USING DIFFUSION EQUATIONS. */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    hjmsav[i__ - 1] = hjm[i__];
/* L60: */
	}
/* MHP 6/00 ADDED COD2,HV TO LIST RETURNED FROM SECULR */
/* FOR THE BUR-ST MIXING ROUTINES */
	seculr_(delts, &dt, hdm, hgm, him, hlm, hpm, hrm, &hs[1], &hs1[1], &
		hs2[1], htm, hjmsav, lczm, lcm, m, model, omegam, &hjm[1], 
		eta2m, qiwm, r0m, &hcomp[16], &lfirst, &imin, &imax, bl, 
		hstot, sjtot, smass, teffl, &lredo, &iredo, &hicz, &hsbot, &
		hstop, &omegas, &lczsur, mrzone, mxzone, &nrzone, &nzone, 
		cod2, hv, &lok);
/*  DIFFUSION TIMESTEP CUTTING REQUIRED IF LREDO IS TRUE. */
/*  RESET MEAN MOLECULAR WEIGHT,COMPOSITION,AND SPECIFIC ANGULAR MOMENTUM */
/*  TO THE VALUES THEY HAD PRIOR TO THE START OF THE STEP. */
	if (lredo) {
	    fx = dt * 2. / *delts;
	    sumdt -= dt * 2.;
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		hjm[i__] = hjmsav[i__ - 1];
		mdphy_1.amum[i__ - 1] -= fx * (temp_1.hamu[i__ - 1] - 
			oldphy_1.amuo[i__ - 1]);
		i__2 = nspec;
		for (j = 1; j <= i__2; ++j) {
		    hcomp[j + i__ * 15] = oldmod_1.hcompp[j + i__ * 15 - 16];
/* L70: */
		}
/* L80: */
	    }
	    goto L40;
	}
    }
/* MHP 05/02 TAKEN OUT OF LOOP SO THAT NUCLEAR BURNING */
/* IS ACCOUNTED FOR IN MODELS THAT ARE FULLY CONVECTIVE */
/* OR WITHOUT INSTABILITIES */
/* ADDED CHANGE FOR BURLICH-STORER TREATMENT OF MIXING PLUS */
/* BURNING - ONLY UPDATED IF NOT USED */
    if (! lburs) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    for (j = 1; j <= 11; ++j) {
		oldmod_1.hcompp[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
	    }
	}
    }
    lfirst = FALSE_;
/*  CLEAN UP EXTENDED COMP ARRAYS; ZERO VALUES THROUGHOUT MOST OF THE */
/*  INTERIOR CAN LEAD TO SMALL NEGATIVE VALUES DUE TO ROUNDOFF ERROR IN */
/*  THE DIFFUSION CALCULATIONS. */
    if (flag_1.lexcom) {
/*  PERFORM LIGHT ELEMENT BURNING. */
/* FIND SURFACE C.Z. DEPTH AT THE END OF THE TIME STEP. */
	convec_(&hcomp[16], hdm, hpm, hrm, &hs[1], htm, lcm, m, mrzone, 
		mxzone, mxzon0, &jcore1, &jenv1, &nrzone, &nzone, &nzone0);
/* 11/91 CHANGED FOR LITHIUM BURNING WITH OVERSHOOT. */
	if (dpmix_1.lovste && lcm[*m - 1]) {
	    liov_1.pscal1 = dpmix_1.alphae * exp(const3_1.clndp * (hpm[jenv1 
		    - 1] + hrm[jenv1 - 1] * 2. - hdm[jenv1 - 1] - 
		    const2_1.cgl - hs[jenv1]));
	} else {
	    liov_1.pscal1 = 0.;
	}
/* FIND LIGHT ELEMENT BURNING RATES AT THE END OF THE TIME STEP. */
	lirate88_(&hcomp[16], hdm, htm, m, &c__2);
/* STORE CURRENT "END OF STEP" QUANTITIES AS "BEGINNING" ONES FOR */
/* THE NEXT STEP. */
/* ADDED CHANGE FOR BURLICH-STORER TREATMENT OF MIXING PLUS */
/* BURNING - ONLY UPDATED IF NOT USED */
	if (! rot_1.linstb || ! lburs || lallcz) {
/* COMPUTE BURNING. */
	    liburn_(&dt, &hcomp[16], hdm, hrm, &hs1[1], &hs2[1], htm, &jenv1, 
		    jenv0, m);
	    *jenv0 = jenv1;
	    liov_1.pscal0 = liov_1.pscal1;
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		oldrat_1.rli60[i__ - 1] = newrat_1.rli6[i__ - 1];
		oldrat_1.rli70[i__ - 1] = newrat_1.rli7[i__ - 1];
		oldrat_1.rbe90[i__ - 1] = newrat_1.rbe9[i__ - 1];
/* L155: */
	    }
	} else {
/* COMPUTE BURNING. */
	    liburn2_(&dt, &hcomp[16], hdm, hrm, &hs1[1], &hs2[1], htm, &jenv1,
		     jenv0, m);
	}
/*  ENSURE THAT CONVECTIVE REGIONS ARE FULLY MIXED. */
	mixcz_(&hcomp[16], &hs2[1], lczm, m);
/*  ZERO OUT LOW ABUNDANCES. */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    for (j = 12; j <= 15; ++j) {
		if (hcomp[j + i__ * 15] < 1e-24) {
		    hcomp[j + i__ * 15] = 0.;
		}
/* L90: */
	    }
/* L100: */
	}
/* MHP 6/00 ADDED OVERWRITE OF HCOMPP FOR LIGHT ELEMENTS */
/* ADDED CHANGE FOR BURLICH-STORER TREATMENT OF MIXING PLUS */
/* BURNING - ONLY UPDATED IF NOT USED */
	if (! rot_1.linstb || lallcz) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		for (j = 12; j <= 15; ++j) {
		    oldmod_1.hcompp[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
		}
	    }
	} else if (! lburs) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		for (j = 12; j <= 15; ++j) {
		    oldmod_1.hcompp[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
		}
	    }
	}
    }
/* MHP 6/00 NOW ADDED THE OPTION OF PERFORMING A BUR-ST EXTRAPOLATION */
/* TO ZERO TIMESTEP FOR THE COMBINATION OF MIXING AND NUCLEAR BURNING. */
    if (rot_1.linstb && ! lallcz) {
	if (lburs) {
	    bursmix_(cod2, &dt, &hcomp[16], hdm, hlm, hpm, hrm, &hs[1], &hs1[
		    1], &hs2[1], hstot, htm, hv, &imax, &imin, jenv0, &jenv1, 
		    &lok, lczm, m, mrzone, mxzone, &nrzone, &nzone);
	}
    }
/*  RETURN FOR NEXT SMALL DIFFUSION TIMESTEP IF NEEDED. */
    if (sumdt < *delts) {
	goto L30;
    }
/*  UPDATE OMEGA ARRAY TO REFLECT NEW ANGULAR MOMENTUM DISTRIBUTION. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	omega[i__] = omegam[i__ - 1];
/* L110: */
    }
/* MHP 3/96 ADDED CALL TO RECOMPUTE SELF-CONSISTENT SET OF OMEGAS */
    getrot_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], lcz, m, &eta2[1], &hi[1]
	    , &omega[1], &qiw[1], &r0[1]);
L9999:
    if (rotprt_1.lprt0) {
	*bl = d_lg10(&hl[*m]);
	rl = (*bl + const_1.clsunl - *teffl * 4. - const1_1.c4pil - 
		const2_1.csigl) * .5;
	fx = exp(const1_1.cln * 3. * (hr[*m] - rl));
	qsurf = fx * quadru_1.quad[*m - 1];
	psurf = exp(const1_1.cln * (const2_1.cgl + *hstot - rl));
	s_wsfe(&io___58);
	do_fio(&c__1, (char *)&qsurf, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&psurf, (ftnlen)sizeof(doublereal));
	d__1 = qsurf * -1.5 / psurf;
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    return 0;
} /* getw_ */


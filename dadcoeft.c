/* dadcoeft.f -- translated by f2c (version 20100827).
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
    doublereal drate[5000], drate0[5000], fmassacc, taucz;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal ecod3[5000], ecod4[5000];
} difad_;

#define difad_1 difad_

struct {
    doublereal facd2[5000], facd3[5000], vesd2[5000], vesd3[5000], ecod5[5000]
	    , ecod6[5000], fgeom[5000], fv0[5000], fv1a[5000], fv1b[5000], 
	    fv2a[5000], fv2b[5000], ev0[5000], ev1a[5000], ev1b[5000], ev2a[
	    5000], ev2b[5000], dss[5000], dgsf[5000], ess[5000], egsf[5000];
} difad3_;

#define difad3_1 difad3_

struct {
    doublereal ethvn[5000], ethvp[5000], ewst[5000], eqwrst[5000];
} difaddt_;

#define difaddt_1 difaddt_

struct {
    doublereal dtdif, djok;
    integer itdif1, itdif2;
} difus_;

#define difus_1 difus_

struct {
    doublereal qchire[5000], qchirc[5000];
} egridchi_;

#define egridchi_1 egridchi_

struct {
    doublereal eqqcod[5000], eqqqcod[5000], qqcod[5000], qqqcod[5000];
} egridder_;

#define egridder_1 egridder_

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
    doublereal fgeomix[5000], vesn[5000], req[5000];
} difad4_;

#define difad4_1 difad4_

struct {
    doublereal wmax, exmd, exw, exr, exm, factor;
    logical ljdot0;
} cwind_;

#define cwind_1 cwind_

/* Table of constant values */

static integer c__1 = 1;
static integer c__3 = 3;
static integer c__9 = 9;
static integer c__5 = 5;

/* $$$$$$ */
/* MHP 06/02 */
/* Subroutine */ int dadcoeft_(doublereal *dr, doublereal *dt, doublereal *ei,
	 doublereal *ej, doublereal *ew, integer *ntot, doublereal *wind1, 
	doublereal *wind2, doublereal *dj, doublereal *ecod2, doublereal *
	sumdj, logical *lfix, logical *lokad)
{
    /* Format strings */
    static char fmt_912[] = "(\002ERROR IN WIND - TAUCZ NOT DEFINED \002,1p2"
	    "e12.3,\002STOPPED\002)";
    static char fmt_100[] = "(\002 MAX D(OMEGA)/OMEGA\002,1pe12.3,\002 AT "
	    "PT.\002,i5,\002 BY ITERATION\002/5(1x,e11.3,i4))";
    static char fmt_914[] = "(1p5e12.3)";
    static char fmt_911[] = "(1p10e12.3)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal a[80000]	/* was [8000][10] */, b[8000], c__[8000], d__[
	    8000];
    static integer i__, j, k, m1, m2;
    static doublereal v0, v1, v2, v3, aa[80000]	/* was [8000][10] */;
    static integer ii, nm, nn;
    static doublereal dw, fx, wm[5000], wn, wp, dt0, dw2, v1e, fx1[5000], wm0[
	    5000], w2m, dwi, ewt[5000];
    static integer nnn;
    static doublereal wmi, dww, wmp[5000], fxx;
    static integer iww, iwi;
    static doublereal wmm, qwr[5000], dwi2, qwr2, fact, delj, corr, dwit[50], 
	    ewit[5000];
    static integer ncut, iwit[50];
    static doublereal sumj;
    static integer nnnn;
    static doublereal tiny, wsat, qwri, vthn, vthp, qwrp[5000], fact0, vtot, 
	    delj0, ewit2[5000], sumj2, facta, vtot2;
    extern /* Subroutine */ int bandw_(doublereal *, integer *, integer *, 
	    integer *, doublereal *);
    static doublereal wind20, dcmix, qqwcc[5000], dwmax;
    static integer iwmax, nstep;
    static doublereal sumdt, sumdj2, wminit[5000], ewprev[5000], qwrinit[5000]
	    ;

    /* Fortran I/O blocks */
    static cilist io___22 = { 0, 6, 0, fmt_912, 0 };
    static cilist io___61 = { 0, 6, 0, 0, 0 };
    static cilist io___62 = { 0, 6, 0, 0, 0 };
    static cilist io___66 = { 0, 6, 0, 0, 0 };
    static cilist io___67 = { 0, 6, 0, 0, 0 };
    static cilist io___70 = { 0, 6, 0, 0, 0 };
    static cilist io___71 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___73 = { 0, 6, 0, 0, 0 };
    static cilist io___74 = { 0, 6, 0, 0, 0 };
    static cilist io___75 = { 0, 6, 0, fmt_914, 0 };
    static cilist io___83 = { 0, 6, 0, fmt_911, 0 };
    static cilist io___86 = { 0, 6, 0, 0, 0 };


/* MHP 3/09 ADDED OPTION TO SCALE THE SATURATION RATE BY THE OVERTURN TIMESCALE */
/* DIFFUSION COEFFICIENTS FOR THE TERMS INVOLVING D/DR (OMEGA) */
/* (ECOD3) AND D/DR (D OMEGA/DR) (ECOD4). */
/* time change of theta */
/* CONVERGENCE CRITERION */
/* VALUES OF D CHI/DR AT THE ZONE EDGES AND ZONE CENTERS */
/* DEFINITION TERMS FOR THE SECOND AND THIRD DERIVATIVE */
/* TERMS */
/*  DCOEFT SETS UP THE COEFFICIENTS FOR THE DIFFUSION DIFFERENCE EQUATION. */

/*  INPUT VARIABLES: */
/*  ECOD : DIFFUSION COEFFICIENTS AT THE EQUALLY SPACED GRID POINTS. */
/*  DR : GRID SPACING. */
/*  DT : TIMESTEP. */
/*  EI : RUN OF MOMENTS OF INERTIA OF EQUALLY SPACED GRID POINTS. */
/*  EW : RUN OF ANGULAR VELOCITY OF EQUALLY SPACED GRID POINTS. */
/*  NTOT : NUMBER OF EQUALLY SPACED GRID POINTS. */
/*  WIND1 : THE ANGULAR MOMENTUM LOSS FROM A SURFACE C.Z. COMPUTED */
/*     EXPLICITILY. */
/*  WIND2 : AS WIND1, BUT COMPUTED IMPLICITLY. */
/*  *NOTE: IF NOT APPLICABLE, WIND1 AND WIND2 ARE ZEROED OUT. */

/*  OUTPUT VARIABLES : */
/*  THE ANGULAR VELOCITY OF SHELL I AT TIME N+1 (W(I,N+1)) IS A FUNCTION OF */
/*  W(I-1),W(I),AND W(I+1) AS DISCUSSED BELOW.  THIS CAN BE EXPRESSED */
/*  AS A TRIDIAGONAL MATRIX. */
/*  A(I) : CONTAINS ALL TERMS INVOLVING OMEGA(I-1). */
/*  B(I) : CONTAINS ALL TERMS INVOLVING OMEGA(I). */
/*  C(I) : CONTAINS ALL TERMS INVOLVING OMEGA(I+1) */
/*  D(I) : THE ANGULAR VELOCITY TERMS AT THE BEGINNING OF THE TIMESTEP. */
/*  *NOTE: ANGULAR MOMENTUM LOSS FROM A SURFACE C.Z. IS SUBTRACTED FROM */
/*     THE LAST ELEMENT OF ARRAY D IF APPLICABLE. */

/*  THE DIFFUSION EQUATION WE ARE SOLVING IS */
/*  dW/dT = 1/(4pi*RHO*R**2) 1/(I/M) d/dR(D*dW/dR) */
/*  WHERE D IS OUR DIFFUSION COEFFICIENT,W IS THE ANGULAR VELOCITY, */
/*  I IS THE MOMENT OF INERTIA,M IS MASS,T IS TIME,R IS RADIUS, */
/*  AND RHO IS DENSITY. */
/*  USING M = 4pi*RHO*R**2*DR THIS IS DIFFERENCED FOR SHELL I AS */
/*  W(I,N+1)-W(I,N)=(DT/DR)*(1/I)*(D(I+1/2)*(W(I+1,N+1)-W(I,N+1)) - */
/*  D(I-1/2)*(W(I,N+1)-W(I-1,N+1))) */
/*  WHERE INDEX N+1 REFERS TO VALUES AT THE END OF THE TIMESTEP,AND */
/*  INDEX N REFERS TO VALUES AT THE BEGINNING OF THE TIMESTEP. */
/*  THIS SYSTEM IS SUPPLEMENTED WITH APPROPRIATE BOUNDARY CONDITIONS. */

/* WE ARE SOLVING A 4XN SYSTEM OF EQUATIONS. */
/* INITIAL DEFINITIONS: */
/* OMEGA IS STORED IN THE FIRST ENTRY */
/* D^2 OMEGA/DR^2 TERM IS STORED IN THE SECOND */
/* D OMEGA/DR TERM IS STORED IN THE THIRD */
/* D^3 OMEGA/DR^3 TERM IS STORED IN THE FOURTH */
/* NOTE THAT SINCE THE DERIVATIVES ARE DEFINED IN */
/* TERMS OF LOWER ORDER QUANTITIES WE DON'T NEED THE */
/* START OF TIMESTEP VALUES FOR THEM. */
    /* Parameter adjustments */
    --ecod2;
    --dj;
    --ew;
    --ej;
    --ei;

    /* Function Body */
    ncut = 0;
    nstep = 1;
    dt0 = *dt;
    wind20 = *wind2;
    tiny = 1e-30;
/* STORE START OF TIMESTEP GRADIENTS AND */
/* AVERAGED OMEGAS. */
    i__1 = *ntot;
    for (i__ = 2; i__ <= i__1; ++i__) {
	qwr[i__ - 1] = egridchi_1.qchire[i__ - 1] * (ew[i__] - ew[i__ - 1]) / 
		*dr;
	wm0[i__ - 1] = (ew[i__] + ew[i__ - 1]) * .5;
    }
    nm = (*ntot << 2) - 2;
/* LOOP FOR TIMESTEP CUTTING */
L5:
    sumdt = 0.;
/* STORE START OF TIMESTEP OMEGA VALUES */
    *wind2 = wind20;
    sumj = 0.;
    i__1 = *ntot;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ewprev[i__ - 1] = ew[i__];
	ewit[i__ - 1] = ew[i__];
	ewit2[i__ - 1] = ew[i__];
	ewt[i__ - 1] = ew[i__];
	sumj += ew[i__] * ei[i__];
    }
    i__1 = *ntot;
    for (i__ = 2; i__ <= i__1; ++i__) {
	wmp[i__ - 1] = wm0[i__ - 1];
	qwrp[i__ - 1] = qwr[i__ - 1];
    }
    i__1 = nstep;
    for (nnnn = 1; nnnn <= i__1; ++nnnn) {
	*dt = dt0 / (doublereal) nstep;
	sumdt += *dt;
	fxx = *dt / dt0;
/* LOOP FOR ITERATION ON THE D THETA/DT TERM; */
/* COEFFICIENTS UPDATED ONCE PER NNN */
	i__2 = difus_1.itdif2;
	for (nnn = 1; nnn <= i__2; ++nnn) {
/* LOOP FOR ITERATION ON THE OTHER COEFFICIENTS */
/* THAT ARE FUNCTIONS OF OMEGA; UPDATED ONCE PER */
/* NN. */
	    *lokad = FALSE_;
/* UPDATE JDOT TERM */
	    if (nnn > 1 && *wind2 > 0.) {
/* MHP 3/09 IF WMAX > 1 THEN ASSUME THAT THE PARAMETER WMAX IS DEFINED BY */
/* WMAX = WMAX(SUN)*TAUCZ(SUN) AND THE SATURATION THRESHOLD WSAT = WMAX/TAUCZ(STAR) */
		if (cwind_1.wmax > 1.) {
		    if (deuter_1.taucz > 1.) {
			wsat = cwind_1.wmax / deuter_1.taucz;
		    } else {
			s_wsfe(&io___22);
			do_fio(&c__1, (char *)&cwind_1.wmax, (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&deuter_1.taucz, (ftnlen)sizeof(
				doublereal));
			e_wsfe();
			s_stop("", (ftnlen)0);
		    }
		} else {
		    wsat = cwind_1.wmax;
		}
/* Computing MIN */
		d__1 = ew[*ntot];
		wp = min(d__1,wsat);
/* Computing MIN */
		d__1 = ewprev[*ntot - 1];
		wn = min(d__1,wsat);
		d__1 = wn / wp;
		d__2 = cwind_1.exw - 1.;
		*wind2 = wind20 * pow_dd(&d__1, &d__2) * (ewprev[*ntot - 1] / 
			ew[*ntot]);
	    }
	    i__3 = difus_1.itdif2;
	    for (nn = 1; nn <= i__3; ++nn) {
/* COMPUTE THE DIFFUSION COEFFICIENTS FOR */
/* THE FIRST AND SECOND ORDER TERMS. */
		if (nnnn == 1) {
		    i__4 = *ntot;
		    for (i__ = 2; i__ <= i__4; ++i__) {
			wminit[i__ - 1] = (difaddt_1.ewst[i__ - 1] + 
				difaddt_1.ewst[i__ - 2]) * .5;
			qwrinit[i__ - 1] = difaddt_1.eqwrst[i__ - 1];
		    }
		} else {
		    i__4 = *ntot;
		    for (i__ = 2; i__ <= i__4; ++i__) {
			wminit[i__ - 1] = wmp[i__ - 1];
			qwrinit[i__ - 1] = qwrp[i__ - 1];
		    }
		}
		qqwcc[0] = 0.;
		i__4 = *ntot - 1;
		for (i__ = 2; i__ <= i__4; ++i__) {
		    qqwcc[i__ - 1] = ewprev[i__] - ewprev[i__ - 1] * 2. + 
			    ewprev[i__ - 2];
		}
		qqwcc[*ntot - 1] = 0.;
		i__4 = *ntot;
		for (i__ = 2; i__ <= i__4; ++i__) {
		    wm[i__ - 1] = (ewprev[i__ - 1] + ewprev[i__ - 2]) * .5 - (
			    qqwcc[i__ - 1] - qqwcc[i__ - 2]) * .125;
/*         WM(I) = 0.5D0*(WM(I)+WMINIT(I)) */
		    wmi = (ewit2[i__ - 1] + ewit2[i__ - 2]) * .5;
		    qwr2 = egridchi_1.qchire[i__ - 1] * (ewprev[i__ - 1] - 
			    ewprev[i__ - 2]) / *dr;
/*         QWR2 = 0.5D0*(QWR2+QWRINIT(I)) */
		    qwri = egridchi_1.qchire[i__ - 1] * (ewit2[i__ - 1] - 
			    ewit2[i__ - 2]) / *dr;
		    if ((d__1 = qwr[i__ - 1], abs(d__1)) > tiny) {
/* Computing 2nd power */
			d__1 = qwr2 / qwr[i__ - 1];
			difad3_1.ess[i__ - 1] *= d__1 * d__1;
/* Computing 2nd power */
			d__1 = qwr2 / qwr[i__ - 1];
			difad3_1.egsf[i__ - 1] *= d__1 * d__1;
		    }
/* Computing 2nd power */
		    d__1 = wm[i__ - 1];
/* Computing 2nd power */
		    d__2 = wm[i__ - 1];
		    v1 = vmult_1.fw * difad3_1.ev0[i__ - 1] * (d__1 * d__1) * 
			    (difad3_1.ev1a[i__ - 1] + d__2 * d__2 * 
			    difad3_1.ev1b[i__ - 1]);
/*         VTH = FW*(ETHVN(I)*WM(I)*QWR2-ETHVP(I))/DT */
		    vthn = 0.;
/*         VTHN = FW*ETHVN(I)*WM(I)**2/DT */
/*         VTHP = -FW*ETHVP(I)/DT */
/*          VTHP = FW/DT0*(ETHVN(I)*WMI*QWRI-ETHVP(I)) */
/* C          VTHP0 = FW/DT0*(ETHVN(I)*WM0(I)*QWR(I)-ETHVP(I)) */
/* C          VTHP1 = FW/DT*ETHVN(I)*(WMI*QWRI-WMP(I)*QWRP(I)) */
/* C          IF(NSTEP.LE.2)THEN */
/* C             VTHP = VTHP0+VTHP1 */
/* C          ELSE */
		    vthp = 0.;
/* C          ENDIF */
/*         VTHN = FW*WM(I)*(ETHVN(I)*WM(I)-ETHVP(I)/QWR2)/DT */
/*         VTHN = MAX(0.0D0,VTHN) */
/* SET D THETA/DT TERM TO ZERO ON THE FIRST ITERATION */
		    if (nnn == 1) {
/*         IF(NTOT.GT.1)THEN */
			vthn = 0.;
			vthp = 0.;
		    }
/* Computing 2nd power */
		    d__1 = wm[i__ - 1];
		    v2 = vmult_1.fw * difad3_1.ev0[i__ - 1] * (d__1 * d__1) * 
			    (difad3_1.ev2a[i__ - 1] + difad3_1.ev2b[i__ - 1]) 
			    + vthn;
		    v1 += vthp;
/*         ECOD3(I) = 0.2D0*(V1+VTH)*FGEOM(I) */
		    difad_1.ecod3[i__ - 1] = v1 * .2 * difad3_1.fgeom[i__ - 1]
			    ;
		    difad_1.ecod4[i__ - 1] = (v2 * .2 + difad3_1.ess[i__ - 1] 
			    + difad3_1.egsf[i__ - 1]) * difad3_1.fgeom[i__ - 
			    1];
/* Computing MAX */
		    d__1 = 0., d__2 = difad_1.ecod4[i__ - 1];
		    difad_1.ecod4[i__ - 1] = max(d__1,d__2);
		}
/* USE THE PRIOR RUN TO CORRECT THE */
/* DIFFUSION COEFFICIENTS FOR CHANGES IN OMEGA; */
/* FX1 IS USED FOR THE THIRD AND FOURTH ORDER TERMS. */
		i__4 = *ntot;
		for (i__ = 2; i__ <= i__4; ++i__) {
		    fx1[i__ - 1] = wm[i__ - 1] * 2. / (ew[i__] + ew[i__ - 1]);
		}
/* RIGHT HAND SIDE - STARTING OMEGA RUN */
		i__4 = *ntot;
		for (i__ = 1; i__ <= i__4; ++i__) {
		    ii = (i__ - 1 << 2) + 1;
		    b[ii - 1] = ewt[i__ - 1];
		    b[ii] = 0.;
		    b[ii + 1] = 0.;
		    b[ii + 2] = 0.;
		    d__[ii - 1] = ewt[i__ - 1];
		    d__[ii] = 0.;
		    d__[ii + 1] = 0.;
		    d__[ii + 2] = 0.;
		}
/* INCLUDE ANGULAR MOMENTUM LOSS */
		delj = (*wind1 + *wind2) * -.5 * ei[*ntot] * fxx;
		b[(*ntot << 2) - 4] *= delj / ei[*ntot] / ewt[*ntot - 1] + 1.;
		d__[(*ntot << 2) - 4] = b[(*ntot << 2) - 4];
/* GLOBAL FACTOR FOR THE DIFFUSION COEFFICIENTS */
		fact0 = *dt / *dr;
/* IF LDIFAD=T, WE ARE SOLVING A COMBINED DIFFUSION/ADVECTION EQUATION. */
/* THIS ADDS A TERM D/DR(RHO*R**4*V*W) TO THE ORIGINAL D/DR(RHO*R**4* */
/* V*R*DW/DR) EQUATION.  SINCE V DEPENDS ON OMEGA AND ITS FIRST THROUGH */
/* THIRD DERIVATIVES, WE CAN EFFECTIVELY RECAST THIS AS A SET OF 4 FIRST */
/* ORDER EQUATIONS. */
/*  FIRST SHELL BOUNDARY CONDITIONS: NO FLOW BELOW THE BOUNDARY */
/*  I.E. THE ANGULAR MOMENTUM TRANSPORT AT THE FIRST SHELL DOES NOT */
/*  DEPEND ON THE SHELLS BELOW IT. */
		fact = fact0 / ei[1];
		facta = *dt * .5 / ei[1] / *dr;
/* ZERO OUT INITIAL COEFFICIENT MATRIX */
		i__4 = nm;
		for (i__ = 1; i__ <= i__4; ++i__) {
		    for (j = 1; j <= 10; ++j) {
			a[i__ + j * 8000 - 8001] = 0.;
		    }
		}
/* OMEGA TERMS - ADVECTIVE */
		a[32000] = 1. - facta * difad_1.ecod3[1];
		a[64000] = -facta * difad_1.ecod3[1];
/* OMEGA TERMS - DW/DR */
		a[48000] = -fact * egridchi_1.qchire[1] * difad_1.ecod4[1];
/* OMEGA TERMS - D2W/DR2 */
/*      A(1,6) = -FACTA*ECOD5(2)*FX1(2) */
/*      FPL = EQQCOD(2)*QCHIRE(2)*FX1(2) */
		a[72000] = -facta * egridchi_1.qchire[1] * difad3_1.ecod5[1] *
			 fx1[1];
/*     *          +0.125D0*ECOD3(2)*DR**2/FPL */
/* OMEGA TERMS - D3W/DR3 */
		a[56000] = fact * egridchi_1.qchire[1] * difad3_1.ecod6[1] * 
			fx1[1];
/* D^2W/DR^2 - SET TO ZERO AT THE LOWER BOUNDARY. */
		a[32001] = 1.;
/*      A(2,6) = -EQQCOD(2)*QCHIRE(2)/DR*FX1(2) */
/* D OMEGA/DR TERMS */
		a[16002] = 1. / *dr;
		a[32002] = 1.;
		a[48002] = -1. / *dr;
/* D^3W/DR^3 */
/* APPLY B.C. TO THE HIGHEST ORDER TERM */
/*      A(4,3) = EQQQCOD(1)*QCHIRE(2)/DR */
		a[32003] = 1.;
/*      A(4,7) = -EQQQCOD(2)*QCHIRE(2)/DR */
		a[64003] = -.33333333333333331;
		i__4 = *ntot - 1;
		for (ii = 2; ii <= i__4; ++ii) {
		    fact = fact0 / ei[ii];
		    facta = *dt * .5 / ei[ii] / *dr;
		    i__ = (ii - 1 << 2) + 1;
/* OMEGA TERMS - ADVECTIVE */
		    a[i__ - 1] = facta * difad_1.ecod3[ii - 1];
		    a[i__ + 31999] = facta * (difad_1.ecod3[ii - 1] - 
			    difad_1.ecod3[ii]) + 1.;
		    a[i__ + 63999] = -facta * difad_1.ecod3[ii];
/* OMEGA TERMS - DW/DR */
		    a[i__ + 15999] = fact * egridchi_1.qchire[ii - 1] * 
			    difad_1.ecod4[ii - 1];
		    a[i__ + 47999] = -fact * egridchi_1.qchire[ii] * 
			    difad_1.ecod4[ii];
/* OMEGA TERMS - D2W/DR2 */
/*         FMI = EQQCOD(II)*QCHIRE(II)*FX1(II) */
/*         FPL = EQQCOD(II+1)*QCHIRE(II+1)*FX1(II+1) */
		    a[i__ + 7999] = facta * egridchi_1.qchire[ii - 1] * 
			    difad3_1.ecod5[ii - 1] * fx1[ii - 1];
/*     *           -0.125D0*ECOD3(II)*DR**2/FMI */
		    a[i__ + 39999] = facta * (difad3_1.ecod5[ii - 1] * 
			    egridchi_1.qchire[ii - 1] * fx1[ii - 1] - 
			    difad3_1.ecod5[ii] * egridchi_1.qchire[ii] * fx1[
			    ii]);
/*     *          +0.125D0*DR**2*(ECOD3(II)/FMI - ECOD3(II+1)/FPL) */
		    a[i__ + 71999] = -facta * difad3_1.ecod5[ii] * 
			    egridchi_1.qchire[ii] * fx1[ii];
/*     *           +0.125D0*ECOD3(II+1)*DR**2/FPL */
/* OMEGA TERMS - D3W/DR3 */
		    a[i__ + 23999] = fact * difad3_1.ecod6[ii - 1] * 
			    egridchi_1.qchire[ii - 1] * fx1[ii - 1];
		    a[i__ + 55999] = -fact * difad3_1.ecod6[ii] * 
			    egridchi_1.qchire[ii] * fx1[ii];
/* D^2W/DR^2 COEFFICIENTS */
		    a[i__ + 8000] = egridder_1.eqqcod[ii - 1] * 
			    egridchi_1.qchire[ii - 1] / *dr * fx1[ii - 1];
		    a[i__ + 32000] = 1.;
		    a[i__ + 40000] = -egridder_1.eqqcod[ii] * 
			    egridchi_1.qchire[ii] / *dr * fx1[ii];
/* D W/DR COEFFICIENTS */
		    a[i__ + 16001] = 1. / *dr;
		    a[i__ + 32001] = 1.;
		    a[i__ + 48001] = -1. / *dr;
/* D^3 W/DR^3 COEFFICIENTS */
		    a[i__ + 16002] = egridchi_1.qchire[ii - 1] * 
			    egridder_1.eqqqcod[ii - 1] / *dr;
		    a[i__ + 32002] = 1.;
		    a[i__ + 48002] = -egridchi_1.qchire[ii - 1] * 
			    egridder_1.eqqqcod[ii] / *dr;
		}
/*  LAST SHELL B.C. : SAME AS FIRST SHELL B.C. */
		fact = fact0 / ei[*ntot];
		facta = *dt * .5 / ei[*ntot] / *dr;
		i__ = (*ntot << 2) - 3;
/*      A(I-1,3) = 0.0D0 */
/*      A(I-1,7) = 0.0D0 */
/*      A(I-1,1) = -1.0D0/3.0D0 */
/* ZERO OUT TERMS RELATED TO D2W/DR2 AT THE EDGES */
		a[i__ + 71995] = 0.;
		a[8004] = 0.;
		if (! (*lfix)) {
/* OMEGA TERMS - ADVECTIVE */
		    a[i__ - 1] = facta * difad_1.ecod3[*ntot - 1];
		    a[i__ + 31999] = facta * difad_1.ecod3[*ntot - 1] + 1.;
/* OMEGA TERMS - DW/DR */
		    a[i__ + 15999] = fact * egridchi_1.qchire[*ntot - 1] * 
			    difad_1.ecod4[*ntot - 1];
/* OMEGA TERMS - D2W/DR2 */
/*         FMI = EQQCOD(NTOT)*QCHIRE(NTOT)*FX1(NTOT) */
		    a[i__ + 7999] = facta * egridchi_1.qchire[*ntot - 1] * 
			    difad3_1.ecod5[*ntot - 1] * fx1[*ntot - 1];
/*     *            -0.125D0*ECOD3(NTOT)*DR**2/FMI */
/*         A(I,6) = FACTA*QCHIRE(NTOT)*ECOD5(NTOT)*FX1(NTOT) */
/* OMEGA TERMS - D3W/DR3 */
		    a[i__ + 23999] = fact * egridchi_1.qchire[*ntot - 1] * 
			    difad3_1.ecod6[*ntot - 1];
		} else {
/* HOLD OMEGA FIXED */
		    a[i__ + 31999] = 1.;
		}
/* D^2W/DR^2 COEFFICIENTS: ASSUME DW/DR = 0 ABOVE BOUNDARY */
/*      A(I+1,2) = EQQCOD(NTOT)*QCHIRC(NTOT)/DR*FX1(NTOT) */
		a[i__ + 32000] = 1.;
/* D W/DR COEFFICIENTS AND D^3 W/DR^3 COEFFICIENTS NOT USED, */
/* SINCE THEY ARE TREATED AS ZERO ABOVE THE UNSTABLE REGION */
/* STORE COEFFICIENT MATRIX TO CHECK ON THE MATRIX INVERSION */
		for (i__ = 1; i__ <= 10; ++i__) {
		    i__4 = nm;
		    for (j = 1; j <= i__4; ++j) {
			aa[j + i__ * 8000 - 8001] = a[j + i__ * 8000 - 8001];
		    }
		}
/* NOW DECOMPOSE THE BAND MATRIX.  SRS. ARE FROM NUMERICAL */
/* RECIPES. */
/* SUBDIAGONAL ROWS */
		m1 = 4;
/* SUPERDIAGONAL ROWS */
		m2 = 5;
/* NM = TOTAL NUMBER OF ELEMENTS, 4 PER SHELL */
/*      WRITE(*,909)(ECOD3(I),ECOD4(I),ECOD5(I),ECOD6(I), */
/*     *             EV0(I),EV1A(I),EV1B(I),EV2A(I), */
/*     *             EV2B(I),I=1,NTOT) */
/* 909  FORMAT(1P9E12.3) */
/*      WRITE(*,910)((A(J,I),I=1,10),J=1,NM) */
/* L910: */
		bandw_(a, &nm, &m1, &m2, b);
/* CHECK ON MATRIX INVERSION */
		i__4 = nm;
		for (i__ = 1; i__ <= i__4; ++i__) {
		    c__[i__ - 1] = 0.;
		}
		for (i__ = 5; i__ <= 10; ++i__) {
		    c__[0] += aa[i__ * 8000 - 8000] * b[i__ - 5];
		}
		for (i__ = 4; i__ <= 10; ++i__) {
		    c__[1] += aa[i__ * 8000 - 7999] * b[i__ - 4];
		}
		for (i__ = 3; i__ <= 10; ++i__) {
		    c__[2] += aa[i__ * 8000 - 7998] * b[i__ - 3];
		}
		for (i__ = 2; i__ <= 10; ++i__) {
		    c__[3] += aa[i__ * 8000 - 7997] * b[i__ - 2];
		}
		i__4 = nm - 5;
		for (j = 5; j <= i__4; ++j) {
		    for (i__ = 1; i__ <= 10; ++i__) {
			c__[j - 1] += aa[j + i__ * 8000 - 8001] * b[i__ - 5 + 
				j - 1];
		    }
		}
		for (i__ = 1; i__ <= 9; ++i__) {
		    c__[nm - 5] += aa[nm - 4 + i__ * 8000 - 8001] * b[i__ + 
			    nm - 10];
		}
		for (i__ = 1; i__ <= 8; ++i__) {
		    c__[nm - 4] += aa[nm - 3 + i__ * 8000 - 8001] * b[i__ + 
			    nm - 9];
		}
		for (i__ = 1; i__ <= 7; ++i__) {
		    c__[nm - 3] += aa[nm - 2 + i__ * 8000 - 8001] * b[i__ + 
			    nm - 8];
		}
		for (i__ = 1; i__ <= 6; ++i__) {
		    c__[nm - 2] += aa[nm - 1 + i__ * 8000 - 8001] * b[i__ + 
			    nm - 7];
		}
		for (i__ = 1; i__ <= 5; ++i__) {
		    c__[nm - 1] += aa[nm + i__ * 8000 - 8001] * b[i__ + nm - 
			    6];
		}
/* CONVERT RUN OF OMEGA TO DELTA OMEGA */
		*sumdj = 0.;
		sumdj2 = 0.;
/* DWMAX - CHANGE FROM THE PREVIOUS LOW-LEVEL ITERATION */
/* (NN). */
		dwmax = (b[0] - ewprev[0]) / ewprev[0];
		iwmax = 1;
/* DWW - ABSOLUTE CHANGE FROM THE INITIAL VECTOR OF OMEGA */
		dww = (b[0] - ew[1]) / ew[1];
		iww = 1;
/* DWI - CHANGE FROM THE RESULT OF THE PRIOR MEDIUM */
/* LEVEL ITERATION (NNN). */
		dwi = (b[0] - ewit[0]) / ewit[0];
		iwi = 1;
		i__4 = *ntot;
		for (i__ = 1; i__ <= i__4; ++i__) {
		    ii = (i__ - 1 << 2) + 1;
		    dj[i__] = (b[ii - 1] - ew[i__]) * ei[i__];
		    sumdj2 += (b[ii - 1] - ewt[i__ - 1]) * ei[i__];
		    *sumdj += dj[i__];
		    dw = (b[ii - 1] - ewprev[i__ - 1]) / ewprev[i__ - 1];
		    dw2 = (b[ii - 1] - ew[i__]) / ew[i__];
		    dwi2 = (b[ii - 1] - ewit[i__ - 1]) / ewit[i__ - 1];
		    if (abs(dw) > abs(dwmax)) {
			iwmax = i__;
			dwmax = dw;
		    }
		    if (abs(dw2) > abs(dww)) {
			iww = i__;
			dww = dw2;
		    }
		    if (abs(dwi2) > abs(dwi)) {
			iwi = i__;
			dwi = dwi2;
		    }
		}
/* DAMP OUT LARGE (SPURIOUS) CHANGES IN OMEGA */
		if (abs(dwmax) > .1) {
		    s_wsle(&io___61);
		    do_lio(&c__3, &c__1, (char *)&nnnn, (ftnlen)sizeof(
			    integer));
		    do_lio(&c__3, &c__1, (char *)&nnn, (ftnlen)sizeof(integer)
			    );
		    do_lio(&c__3, &c__1, (char *)&nn, (ftnlen)sizeof(integer))
			    ;
		    e_wsle();
		    s_wsle(&io___62);
		    do_lio(&c__9, &c__1, "CORRECTIONS TOO LARGE ", (ftnlen)22)
			    ;
		    do_lio(&c__5, &c__1, (char *)&dwmax, (ftnlen)sizeof(
			    doublereal));
		    do_lio(&c__3, &c__1, (char *)&iwmax, (ftnlen)sizeof(
			    integer));
		    e_wsle();
		    *lokad = FALSE_;
/*      WRITE(*,920)((AA(I,J),J=1,10),B(I),C(I),D(I),I=1,NM) */
/* L920: */
		    goto L950;
		} else if (abs(dwmax) < .01) {
		    fx = 1.;
		} else {
/*         FX = 0.01D0/ABS(DWMAX) */
		    fx = 1.;
		}
		sumj2 = 0.;
		i__4 = *ntot;
		for (i__ = 1; i__ <= i__4; ++i__) {
		    ii = (i__ - 1 << 2) + 1;
		    ewprev[i__ - 1] += fx * (b[ii - 1] - ewprev[i__ - 1]);
		    dj[i__] *= fx;
		    sumj2 += ewprev[i__ - 1] * ei[i__];
		}
/* ANGULAR MOMENTUM CONSERVATION ENFORCED */
		corr = (sumj + delj) / sumj2;
		s_wsle(&io___66);
		do_lio(&c__5, &c__1, (char *)&sumj, (ftnlen)sizeof(doublereal)
			);
		do_lio(&c__5, &c__1, (char *)&delj, (ftnlen)sizeof(doublereal)
			);
		do_lio(&c__5, &c__1, (char *)&sumj2, (ftnlen)sizeof(
			doublereal));
		do_lio(&c__5, &c__1, (char *)&corr, (ftnlen)sizeof(doublereal)
			);
		e_wsle();
		*sumdj = 0.;
		i__4 = *ntot;
		for (i__ = 1; i__ <= i__4; ++i__) {
		    ewprev[i__ - 1] *= corr;
		    dj[i__] = (ewprev[i__ - 1] - ew[i__]) * ei[i__];
		    *sumdj += dj[i__];
		}
		s_wsle(&io___67);
		do_lio(&c__5, &c__1, (char *)&(*sumdj), (ftnlen)sizeof(
			doublereal));
		do_lio(&c__5, &c__1, (char *)&delj, (ftnlen)sizeof(doublereal)
			);
		e_wsle();
/*      WRITE(*,912)FX,DWMAX,SUMDJ */
/* 912  FORMAT(1P2E12.3) */
/*      WRITE(*,913)(EW(I),EWPREV(I),DJ(I),I=1,NTOT) */
/* 913  FORMAT(1P6E12.3) */
		dwit[nn - 1] = dwmax;
		iwit[nn - 1] = iwmax;
/* DETERMINE IF RUN HAS CONVERGED */
		if (abs(dwmax) < difus_1.djok) {
		    *lokad = TRUE_;
		    goto L900;
		}
	    }
L900:
	    s_wsle(&io___70);
	    do_lio(&c__3, &c__1, (char *)&nnnn, (ftnlen)sizeof(integer));
	    do_lio(&c__3, &c__1, (char *)&nnn, (ftnlen)sizeof(integer));
	    do_lio(&c__3, &c__1, (char *)&nn, (ftnlen)sizeof(integer));
	    e_wsle();
	    s_wsfe(&io___71);
	    do_fio(&c__1, (char *)&dww, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&iww, (ftnlen)sizeof(integer));
	    i__3 = nn;
	    for (j = 1; j <= i__3; ++j) {
		do_fio(&c__1, (char *)&dwit[j - 1], (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&iwit[j - 1], (ftnlen)sizeof(integer));
	    }
	    e_wsfe();
	    if (nnn <= 2) {
		i__3 = *ntot;
		for (k = 1; k <= i__3; ++k) {
		    ewit[k - 1] = ewprev[k - 1];
		    ewit2[k - 1] = ewprev[k - 1];
		}
	    } else {
		i__3 = *ntot;
		for (k = 1; k <= i__3; ++k) {
		    ewit[k - 1] = ewprev[k - 1];
		    ewit2[k - 1] = ewit[k - 1] * .5 + ewprev[k - 1] * .5;
		}
	    }
	    if (abs(dwi) <= difus_1.djok && nnn >= 2) {
		goto L9999;
	    } else {
		*lokad = FALSE_;
	    }
	}
L9999:
	i__2 = *ntot;
	for (k = 1; k <= i__2; ++k) {
	    ewt[k - 1] = ewprev[k - 1];
	}
	sumj += delj;
	i__2 = *ntot;
	for (k = 2; k <= i__2; ++k) {
	    wmp[k - 1] = (ewprev[k - 1] + ewprev[k - 2]) * .5;
	    qwrp[k - 1] = egridchi_1.qchire[k - 1] * (ewprev[k - 1] - ewprev[
		    k - 2]) / *dr;
	}
    }
L950:
    if (! (*lokad)) {
	++ncut;
	nstep <<= 1;
	if (ncut > 5) {
	    s_wsle(&io___73);
	    do_lio(&c__9, &c__1, "TIMESTEP CUT MORE THAN 5 TIMES - RUN STOPP"
		    "ED", (ftnlen)44);
	    e_wsle();
	    s_stop("111", (ftnlen)3);
	} else {
	    s_wsle(&io___74);
	    do_lio(&c__9, &c__1, "TIMESTEP CUT #", (ftnlen)14);
	    do_lio(&c__3, &c__1, (char *)&ncut, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " IN DADCOEFT", (ftnlen)12);
	    e_wsle();
	}
	goto L5;
    }
    s_wsfe(&io___75);
    do_fio(&c__1, (char *)&b[0], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ew[1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&b[1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&b[2], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&b[3], (ftnlen)sizeof(doublereal));
    e_wsfe();
    i__1 = *ntot;
    for (i__ = 2; i__ <= i__1; ++i__) {
	ii = (i__ - 1 << 2) + 1;
	wmm = (b[ii - 1] + b[ii - 5]) * .5;
	w2m = (b[ii] + b[ii - 4]) * .5;
	v0 = difad_1.ecod3[i__ - 1] / difad3_1.fgeom[i__ - 1];
	v1 = difad_1.ecod4[i__ - 1] / difad3_1.fgeom[i__ - 1] * b[ii - 3] * 
		egridchi_1.qchire[i__ - 1] / wmm;
	v1e = vmult_1.fw * .2 * difad3_1.ev0[i__ - 1] * wmm * 
		egridchi_1.qchire[i__ - 1] * (difad3_1.ev2a[i__ - 1] + 
		difad3_1.ev2b[i__ - 1]) * b[ii - 3];
	if (difad_1.ecod4[i__ - 1] <= 0.) {
	    v1e = 0.;
	}
	v2 = difad3_1.ecod5[i__ - 1] / difad3_1.fgeom[i__ - 1] * 
		egridchi_1.qchire[i__ - 1] * w2m / wmm;
	v3 = difad3_1.ecod6[i__ - 1] / difad3_1.fgeom[i__ - 1] * b[ii - 2] * 
		egridchi_1.qchire[i__ - 1] / wmm;
	vtot = v0 + v1 + v2 + v3;
	vtot2 = v0 + v1e + v2 + v3;
	if (i__ <= 10 || *ntot - i__ <= 10) {
	    s_wsfe(&io___83);
	    do_fio(&c__1, (char *)&b[ii - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ew[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&v0, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&v1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&v2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&v3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&vtot, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&b[ii], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&b[ii + 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&b[ii + 2], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	difad4_1.vesn[i__ - 1] = (d__1 = vmult_1.fc * vmult2_1.fesc * vtot2 * 
		difad4_1.req[i__ - 1], abs(d__1)) * 5.;
	dcmix = difad4_1.vesn[i__ - 1] + vmult_1.fc * vmult2_1.fssc * 
		difad3_1.ess[i__ - 1] + vmult_1.fc * vmult2_1.fgsfc * 
		difad3_1.egsf[i__ - 1];
	ecod2[i__] = dcmix * difad4_1.fgeomix[i__ - 1];
/*         WRITE(*,1111)I,VESN(I),DCMIX,ECOD2(I),REQ(I) */
/* L1111: */
    }
    *dt = dt0;
    delj0 = delj / fxx;
    s_wsle(&io___86);
    do_lio(&c__5, &c__1, (char *)&(*sumdj), (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&delj0, (ftnlen)sizeof(doublereal));
    e_wsle();
/*      IF(.NOT.LOKAD)THEN */
/*         SUMDJ = 0.0D0 */
/*         DO I = 1,NTOT */
/*            DJ(I) = (EWPREV(I)-EW(I))*EI(I) */
/*            SUMDJ = SUMDJ + DJ(I) */
/*         END DO */
/*      ENDIF */
/*      LOKAD = .TRUE. */
    return 0;
} /* dadcoeft_ */


/* checkj.f -- translated by f2c (version 20061008).
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
    integer npenv, nprtmod, nprtpt, npoint;
} ccout1_;

#define ccout1_1 ccout1_

struct {
    doublereal dtdif, djok;
    integer itdif1, itdif2;
} difus_;

#define difus_1 difus_

struct {
    doublereal toleri;
} errmom_;

#define errmom_1 errmom_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

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
    doublereal ves[5000], ves0[5000], vss[5000], vss0[5000], hle[5000], vgsf[
	    5000], vgsf0[5000], vmu[5000];
} temp2_;

#define temp2_1 temp2_

struct {
    doublereal vfc[5000];
    logical lvfc, ldifad;
} varfc_;

#define varfc_1 varfc_

struct {
    doublereal phisp[5000], phirot[5000], phidis[5000], rat[5000];
} quadd_;

#define quadd_1 quadd_

struct {
    doublereal chi[5000], echi[5000], es1[5000], dchi;
    integer ntot;
} egrid_;

#define egrid_1 egrid_

struct {
    doublereal ecod3[5000], ecod4[5000];
} difad_;

#define difad_1 difad_

struct {
    doublereal vesa[5000], vesa0[5000], vesd[5000], vesd0[5000];
} difad2_;

#define difad2_1 difad2_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$ */
/* MHP 10/02 ECOD, ECOD2 NO LONGER USED; OMITTED FROM CALL */
/* Subroutine */ int checkj_(doublereal *hd, doublereal *hjmp, doublereal *
	hjmsav, doublereal *hr, doublereal *hs, doublereal *hs2, doublereal *
	hv, integer *imin, integer *imax, integer *it, logical *lcz, integer *
	m, doublereal *dt, doublereal *eta2, doublereal *hi, doublereal *hjm, 
	integer *iredo, logical *lok, logical *lredo, doublereal *omega, 
	doublereal *qiw, doublereal *r0, doublereal *wsav, integer *id, 
	integer *idm, logical *lokad)
{
    /* Format strings */
    static char fmt_1000[] = "(1x,39(\002>\002),39(\002<\002)/5x,\002ERROR I"
	    "N SR CHECKJ\002/5x,\002NEGATIVE J/M ENCOUNTERED IN ZONE\002,i5"
	    ",\002 AND 3 ATTEMPTS AT CUTTING TIMESTEP FAILED\002/\002RUN STOP"
	    "PED\002)";
    static char fmt_1005[] = "(5x,\002ERROR IN SR CHECKJ\002/5x,\002TIMESTEP"
	    " CUT,\002,1x,\002NUMBER\002,i5,\002 DUE TO NEGATIVE J/M IN ZON"
	    "E\002,i5)";
    static char fmt_120[] = "(5x,\002OMEGA GRADIENT REVERSAL BETWEEN ZONES"
	    " \002,i5,\002 AND \002,i5,\002 ITERATION \002,i5)";
    static char fmt_160[] = "(\002 MAX D(J/M)/(J/M)\002,1pe12.3,\002 AT PT"
	    ".\002,i5,\002 BY ITERATION\002/5(1x,e11.3,i4))";
    static char fmt_170[] = "(\002 SHELL\002,3x,\002OMEGA\002,5x,\002DEL OME"
	    "GA\002,6x,\002J/M\002,7x,\002DEL J/M\002)";
    static char fmt_190[] = "(1x,i5,1p4e12.3)";
    static char fmt_210[] = "(1x,\002SHELL\002,4x,\002VES0\002,9x,\002VES"
	    "\002,7x,\002VGSF0\002,8x,\002VGSF\002,9x,\002VSS\002,9x,\002RA"
	    "T\002,8x,\002VTOT\002,7x,\002LENGTH\002,8x,\002VMU\002)";
    static char fmt_220[] = "(1x,i5,1p10e12.3)";
    static char fmt_221[] = "(1x,i5,1p7e12.3)";
    static char fmt_222[] = "(1x,i5,48x,1p3e12.3)";
    static char fmt_223[] = "(1x,i5,1p4e12.3)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j;
    static doublereal dj;
    static integer ii;
    static doublereal acc;
    static integer ibeg;
    static doublereal delj;
    static integer iend, ibot, itop;
    static doublereal delji[16];
    static integer imaxi[16], ijmax;
    extern /* Subroutine */ int solid_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, integer *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    );
    static doublereal toler0;
    extern /* Subroutine */ int getrot_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_1000, 0 };
    static cilist io___4 = { 0, 6, 0, fmt_1005, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_1005, 0 };
    static cilist io___14 = { 0, 6, 0, fmt_120, 0 };
    static cilist io___18 = { 0, 6, 0, fmt_160, 0 };
    static cilist io___19 = { 0, 0, 0, fmt_170, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_190, 0 };
    static cilist io___23 = { 0, 0, 0, fmt_210, 0 };
    static cilist io___24 = { 0, 0, 0, fmt_220, 0 };
    static cilist io___25 = { 0, 0, 0, fmt_221, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_221, 0 };
    static cilist io___27 = { 0, 0, 0, fmt_222, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_221, 0 };
    static cilist io___29 = { 0, 0, 0, fmt_223, 0 };


/*      *                  LPRT,M,DT,ETA2,HI,HJM,IREDO,LOK,LREDO,OMEGA,  ! KC 2025-05-31 */
/*     *                  QIW,R0,WSAV,ID,IDM,ECOD,ECOD2,LOKAD) */
/* MHP 7/93 */
/* MHP 3/93 */
/* MHP 11/94 */
/*     *   ECOD(JSON),ECOD2(JSON) */
/*  SR CHECKJ PERFORMS SEVERAL FUNCTIONS. */
/*  FIRST, IT CHECKS FOR NEGATIVE SPECIFIC ANGULAR MOMENTA. */
/*  IF THEY ARE ENCOUNTERED, THE TIMESTEP IS CUT. */
/*  SECOND, IT GUARDS AGAINST REVERSAL OF ANGULAR VELOCITY GRADIENTS. */
/*  THIRD, IT COMPARES THE RUN OF OMEGA TO THAT FOR THE PREVIOUS ITERATION. */
/*  IF THE RUN HAS CHANGED BY LITTLE ENOUGH THEN THE DIFFUSION EQUATIONS */
/*  ARE CONSIDERED CONVERGED.  LOK=T IF THE RUN HAS CONVERGED. */
/*  FOURTH, IT CORRECTS THE MOMENT OF INERTIA FOR CHANGES IN OMEGA. */
/*  INPUT VARIABLES: */
/*  FIFTH, IT WRITES OUT DETAILS OF THE DIFFUSION IF REQUESTED. */

/*  HD : RUN OF LOG DENSITY. */
/*  HJM : RUN OF SPECIFIC ANGULAR MOMENTUM AFTER THE CURRENT ITERATION. */
/*  HJMP : RUN OF SPECIFIC ANGULAR MOMENTUM AFTER THE LAST ITERATION */
/*     FOR THE DIFFUSION COEFFICIENTS. */
/*  HJMSAV : RUN OF SPECIFIC ANGULAR MOMENTUM AT THE BEGINNING OF THE */
/*     TIMESTEP. */
/*  HR : RUN OF LOG RADIUS. */
/*  HS : RUN OF LOG MASS. */
/*  HS2 : MASS (UNLOGGED) CONTAINED IN EACH OF THE MODEL POINTS. */
/*  HV : RUN OF CHARACTERISTIC DIFFUSION VELOCITIES.  IF HV(I)>0 THEN ZONE */
/*     I IS UNSTABLE WITH RESPECT TO ZONE I-1. */
/*  IMIN,IMAX : THE FIRST AND LAST ZONES AT WHICH HV IS COMPUTED. */
/*   *NOTE: IMIN = 2 AND IMAX = NUMBER OF MODEL POINTS UNLESS A SURFACE */
/*     OR CENTRAL CONVECTION ZONE EXISTS. */
/*  IT : ITERATION NUMBER. */
/*  ITDIF2 : MAXIMUM NUMBER OF ITERATIONS ALLOWED IN A GIVEN DIFFUSION */
/*     TIMESTEP. */
/*  LCZ : ARRAY SET T IF A ZONE IS CONVECTIVE FOR ANGULAR MOMENTUM */
/*     REDISTRIBUTION PURPOSES (I.E. INCLUDES OVERSHOOT REGION.) */
/*  LPRT : FLAG SET T IF MODEL I/O DESIRED. */
/*  M : NUMBER OF MODEL POINTS. */

/*  OUTPUT VARIABLES: */

/*  DT : DIFFUSION TIMESTEP, WHICH CAN BE CUT IF ERRORS IN THE DIFFUSION */
/*     ARE DETECTED. */
/*  ETA2,R0 : AUXILLARY QUANTITIES USED TO FIND OMEGA GIVEN J/M. */
/*  HI,QIW : RUN OF MOMENTS OF INERTIA AND THEIR DERIVATIVES WITH RESPECT */
/*  TO OMEGA. */
/*  HJMP : ARRAY HJMP IS SET EQUAL TO HJM AFTER CONVERGENCE IS CHECKED. */
/*  IREDO : NUMBER OF TIMES DIFFUSION TIMESTEP HAS BEEN CUT. */
/*  LOK : FLAG SET T IF DIFFUSION CEOFFICIENTS HAVE CONVERGED. */
/*  LREDO : FLAG SET T IF A PROBLEM REQUIRES CUTTING THE DIFFUSION TIMESTEP. */
/*  OMEGA : RUN OF ANGULAR VELOCITY. */

/*  CHECK FOR NEGATIVE J/M. */
    /* Parameter adjustments */
    --id;
    --wsav;
    --r0;
    --qiw;
    --omega;
    --hjm;
    --hi;
    --eta2;
    --lcz;
    --hv;
    --hs2;
    --hs;
    --hr;
    --hjmsav;
    --hjmp;
    --hd;

    /* Function Body */
    *lok = FALSE_;
    *lredo = FALSE_;
    if (*lokad) {
	*lok = TRUE_;
	*lredo = FALSE_;
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (hjm[i__] <= 0.) {
	    ++(*iredo);
/*  STOP IF TIMESTEP CUT MORE THAN 3 TIMES. */
/*            IF(IREDO.GT.3)THEN */
	    if (*iredo > 0) {
		s_wsfe(&io___2);
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		e_wsfe();
		io___3.ciunit = luout_1.ishort;
		s_wsfe(&io___3);
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    } else {
		*lredo = TRUE_;
		*dt *= .5;
		s_wsfe(&io___4);
		do_fio(&c__1, (char *)&(*iredo), (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		e_wsfe();
		io___5.ciunit = luout_1.ishort;
		s_wsfe(&io___5);
		do_fio(&c__1, (char *)&(*iredo), (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		e_wsfe();
		goto L240;
	    }
	}
/* L10: */
    }
/*  CHECK IF THE FRACTIONAL CHANGE IN OMEGA RELATIVE TO THE PREVIOUS */
/*  ITERATION IS SMALL ENOUGH TO BE CONSIDERED CONVERGED. */
/*  ALSO LOCATE THE ZONE WHERE THE MAXIMUM CHANGE OCCURS FOR I/O. */
    delji[*it - 1] = (hjm[1] - hjmp[1]) / hjmp[1];
    hjmp[1] = hjm[1];
    imaxi[*it - 1] = 1;
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
	dj = (hjm[i__] - hjmp[i__]) / hjmp[i__];
	if (abs(dj) > (d__1 = delji[*it - 1], abs(d__1))) {
	    delji[*it - 1] = dj;
	    imaxi[*it - 1] = i__;
	}
	hjmp[i__] = hjm[i__];
/* L140: */
    }
    if ((d__1 = delji[*it - 1], abs(d__1)) <= difus_1.djok) {
/*         LOK = .FALSE. */
/*      ELSE */
	*lok = TRUE_;
    }
/*  FIND THE RUN OF OMEGA THAT CORRESPONDS TO THE NEW RUN OF J/M. */
/*  THE MOMENT OF INERTIA IS A FUNCTION OF OMEGA WHICH IS SOLVED */
/*  ITERATIVELY.  BECAUSE THE ERROR IN THE DIFFUSION IS OF ORDER DJOK, */
/*  RELAX TOLERANCE FOR MOMENT OF INERTIA ITERATION EXCEPT FOR THE */
/*  FINAL STEP. */
    toler0 = errmom_1.toleri;
    acc = rot_1.acfpft;
    if (*it < difus_1.itdif2 && ! (*lok)) {
/* Computing MAX */
	d__1 = difus_1.djok * .01;
	errmom_1.toleri = max(d__1,toler0);
/* Computing MAX */
	d__1 = difus_1.djok * .01;
	rot_1.acfpft = max(d__1,acc);
    }
    getrot_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &lcz[1], m, &eta2[1], &
	    hi[1], &omega[1], &qiw[1], &r0[1]);
    errmom_1.toleri = toler0;
    rot_1.acfpft = acc;
/*  SEARCH FOR REVERSAL OF OMEGA GRADIENTS.  IF ONE EXISTS, ENFORCE */
/*  SOLID-BODY ROTATION IN THE OFFENDING PAIR OF ZONES. */
    i__ = *m;
    ibot = *m;
L20:
/*  POSITIVE OMEGA GRADIENT ENCOUNTERED. */
    if (omega[i__] - omega[i__ - 1] > 1.) {
/*  IF PREVIOUS GRADIENT WAS POSITIVE, LEAVE ALONE. */
	if (oldrot_1.wold[i__ - 1] - oldrot_1.wold[i__ - 2] > 1e-15) {
	    i__ = ibot - 1;
	    ibot = i__;
	    if (i__ > 1) {
		goto L20;
	    } else {
		goto L130;
	    }
	}
/*  SIGN OF D OMEGA/DR HAS CHANGED,INDICATING AN ERROR IN DIFFUSION. */
/*  MIX THE OFFENDING ZONES TO SOLID BODY ROTATION. */
/*  ITOP IS THE UPPERMOST UNSTABLE SHELL. */
	itop = i__;
/*  IF ADJACENT TO A CONVECTION ZONE, MIX THE CONVECTION ZONE AS WELL. */
	if (lcz[itop] && itop < *m) {
	    i__1 = *m;
	    for (j = itop + 1; j <= i__1; ++j) {
		if (! lcz[j]) {
		    goto L40;
		}
/* L30: */
	    }
L40:
	    itop = j - 1;
	}
/*  IBOT IS THE BOTTOM UNSTABLE ZONE. CHECK FOR ADJACENT CZ AS ABOVE. */
	ibot = i__ - 1;
	if (lcz[ibot] && ibot > 1) {
	    for (j = ibot - 1; j >= 1; --j) {
		if (! lcz[j]) {
		    goto L60;
		}
/* L50: */
	    }
L60:
	    ibot = j + 1;
	}
/*  ENFORCE A SOLID BODY ROTATION CURVE FROM IBOT TO ITOP. */
	solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &ibot, &itop, &eta2[
		1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
/*  NOW CHECK TO SEE IF THE REDISTRIBUTION HAS GENERATED ANY NEW REVERSALS. */
L70:
	*lredo = FALSE_;
/*  CHECK FOR GRADIENT REVERSALS BELOW ZONE IBOT. */
	if (ibot > 1) {
	    if (omega[ibot] - omega[ibot - 1] > 1e-15) {
		if (oldrot_1.wold[ibot - 1] - oldrot_1.wold[ibot - 2] < 1e-15)
			 {
		    *lredo = TRUE_;
		    --ibot;
		    if (lcz[ibot] && ibot > 1) {
			for (j = ibot - 1; j >= 1; --j) {
			    if (! lcz[j]) {
				goto L90;
			    }
/* L80: */
			}
L90:
			ibot = j + 1;
		    }
		}
	    }
	}
/*  CHECK FOR GRADIENT REVERSALS ABOVE ZONE ITOP. */
	if (itop < *m) {
	    if (omega[itop + 1] - omega[itop] > 1e-15) {
		if (oldrot_1.wold[itop] - oldrot_1.wold[itop - 1] < 1e-15) {
		    *lredo = TRUE_;
		    ++itop;
		    if (lcz[itop] && itop < *m) {
			i__1 = *m;
			for (j = itop + 1; j <= i__1; ++j) {
			    if (! lcz[j]) {
				goto L110;
			    }
/* L100: */
			}
L110:
			itop = j - 1;
		    }
		}
	    }
	}
/*  IF LREDO=T THEN THE REDISTRIBUTION OF ANGULAR MOMENTUM IN A REVERSED */
/*  REGION HAS EFFECTED A CHANGE IN OMEGA AT ONE OF BOTH OF THE BOUNDARIES */
/*  THAT HAS CAUSED A NEW GRADIENT REVERSAL AT THE BOUNDARY. */
	if (*lredo) {
	    solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &ibot, &itop, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
	    goto L70;
	}
	if (*it == difus_1.itdif2 || *lok) {
	    s_wsfe(&io___14);
	    do_fio(&c__1, (char *)&ibot, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&itop, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*it), (ftnlen)sizeof(integer));
	    e_wsfe();
	}
    }
L130:
/*  RETURN FOR NEXT ZONE. */
    i__ = ibot - 1;
    ibot = i__;
    if (i__ > 1) {
	goto L20;
    }
/*  I/O FOR END OF DIFFUSION STEP. */
    if (*it == difus_1.itdif2 || *lok) {
/*  FIND MAXIMUM FRACTIONAL CHANGE IN J/M OVER TIMESTEP. */
	delj = 0.;
	ijmax = 0;
/* MHP 10/02 ICRIT REMOVED */
/*         IF(ICRIT.EQ.0)THEN */
	ii = 1;
/*         ELSE */
/*           II = ICRIT */
/*         ENDIF */
	i__1 = *m;
	for (i__ = ii; i__ <= i__1; ++i__) {
	    dj = (hjm[i__] - hjmsav[i__]) / hjmsav[i__];
	    if (abs(dj) > abs(delj)) {
		delj = dj;
		ijmax = i__;
	    }
/* L150: */
	}
	if (! (*lokad)) {
	    s_wsfe(&io___18);
	    do_fio(&c__1, (char *)&delj, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ijmax, (ftnlen)sizeof(integer));
	    i__1 = *it;
	    for (j = 1; j <= i__1; ++j) {
		do_fio(&c__1, (char *)&delji[j - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&imaxi[j - 1], (ftnlen)sizeof(integer));
	    }
	    e_wsfe();
	}

/* G Somers 11/14, I AM TURNING OFF THE OUTPUT TO THE .FULL FILE. */
/* THE AM CHANGES WILL NOT BE RECORDED, BUT THIS CAN BE TRIVIALLY */
/* EXTRACTED FROM THE EXTENDED .STORE FILE. */

/* SKIP OUTPUT IF NOT DESIRED. */
/*         IF(.NOT.LPRT)GOTO 240 */
	if (TRUE_) {
	    goto L240;
	}
/* G Somers END */

/*  IF NPRTPT IS SET TO A LARGE NUMBER, SKIP DETAILED OUTPUT. */
	if (ccout1_1.nprtpt > *m) {
	    goto L240;
	}
	io___19.ciunit = luout_1.imodpt;
	s_wsfe(&io___19);
	e_wsfe();
/*  DETERMINE WHICH SHELLS TO PRINT. */
/*  FIRST POINT ALWAYS PRINTED OUT. */
	id[1] = 1;
	*idm = 2;
	ibeg = max(*imin,ccout1_1.nprtpt);
/* Computing MIN */
	i__1 = *imax, i__2 = *imax / ccout1_1.nprtpt * ccout1_1.nprtpt;
	iend = min(i__1,i__2);
/* PRINT OUT EVERY NPRTPT POINTS. WHEN V=0, SKIP POINTS. */
	i__1 = iend;
	i__2 = ccout1_1.nprtpt;
	for (j = ibeg; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
/*            IF(HV(J).EQ.0.0D0)GOTO 180 */
	    id[*idm] = j;
	    ++(*idm);
/* L180: */
	}
/* OUTERMOST MODEL POINT (OR POINT AT BASE OF SURFACE C.Z.)ALWAYS PRINTED. */
	if (id[*idm - 1] != *imax) {
	    id[*idm] = *imax;
	} else {
	    --(*idm);
	}
/*  I/O CONCERNING ANGULAR MOMENTUM TRANSPORT. */
	i__2 = *idm;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    io___22.ciunit = luout_1.imodpt;
	    s_wsfe(&io___22);
	    do_fio(&c__1, (char *)&id[i__], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&omega[id[i__]], (ftnlen)sizeof(doublereal))
		    ;
	    d__1 = omega[id[i__]] - wsav[id[i__]];
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hjm[id[i__]], (ftnlen)sizeof(doublereal));
	    d__2 = hjm[id[i__]] - hjmsav[id[i__]];
	    do_fio(&c__1, (char *)&d__2, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* L200: */
	}
/*  I/O CONCERNING DIFFUSION VELOCITIES AND SCALE LENGTHS. */
	io___23.ciunit = luout_1.imodpt;
	s_wsfe(&io___23);
	e_wsfe();
	i__2 = *idm;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    io___24.ciunit = luout_1.imodpt;
	    s_wsfe(&io___24);
	    do_fio(&c__1, (char *)&id[i__], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&temp2_1.ves0[id[i__] - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temp2_1.ves[id[i__] - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temp2_1.vgsf0[id[i__] - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temp2_1.vgsf[id[i__] - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temp2_1.vss[id[i__] - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&quadd_1.rat[id[i__] - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&hv[id[i__]], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&temp2_1.hle[id[i__] - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temp2_1.vmu[id[i__] - 1], (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
/* L230: */
	}
	if (varfc_1.ldifad) {
/*            DO I = 1,IDM */
/*               WRITE(IMODPT,221)ID(I),VES(ID(I)),VESA(ID(I)), */
/*     *         VESD(ID(I)), */
/*     *         ECOD(ID(I)),ECOD2(ID(I)),ECOD3(ID(I)),ECOD4(ID(I)) */
/* 221           FORMAT(1X,I5,1P7E12.3) */
/*            END DO */
	    if (*idm == egrid_1.ntot) {
		i__2 = *idm;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    io___25.ciunit = luout_1.imodpt;
		    s_wsfe(&io___25);
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&egrid_1.chi[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&temp2_1.ves[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad2_1.vesa[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad2_1.vesd[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&egrid_1.echi[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad_1.ecod3[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad_1.ecod4[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		}
	    } else if (*idm < egrid_1.ntot) {
		i__2 = *idm;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    io___26.ciunit = luout_1.imodpt;
		    s_wsfe(&io___26);
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&egrid_1.chi[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&temp2_1.ves[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad2_1.vesa[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad2_1.vesd[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&egrid_1.echi[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad_1.ecod3[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad_1.ecod4[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		}
		i__2 = egrid_1.ntot;
		for (i__ = *idm + 1; i__ <= i__2; ++i__) {
		    io___27.ciunit = luout_1.imodpt;
		    s_wsfe(&io___27);
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&egrid_1.echi[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad_1.ecod3[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad_1.ecod4[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		}
	    } else {
		i__2 = egrid_1.ntot;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    io___28.ciunit = luout_1.imodpt;
		    s_wsfe(&io___28);
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&egrid_1.chi[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&temp2_1.ves[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad2_1.vesa[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad2_1.vesd[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&egrid_1.echi[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad_1.ecod3[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad_1.ecod4[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		}
		i__2 = *idm;
		for (i__ = egrid_1.ntot + 1; i__ <= i__2; ++i__) {
		    io___29.ciunit = luout_1.imodpt;
		    s_wsfe(&io___29);
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&egrid_1.chi[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&temp2_1.ves[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad2_1.vesa[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&difad2_1.vesd[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		}
	    }
	}
    }
L240:
    return 0;
} /* checkj_ */


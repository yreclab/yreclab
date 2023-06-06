/* hpoint.f -- translated by f2c (version 20100827).
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
    doublereal hcompm[75000]	/* was [15][5000] */;
} burn_;

#define burn_1 burn_

struct {
    integer npenv, nprt1, nprt2, nprtpt, npoint;
} ccout1_;

#define ccout1_1 ccout1_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal htoler[10]	/* was [5][2] */, fcorr0, fcorri, fcorr, 
	    hpttol[12];
    integer niter1, niter2, niter3;
} ctol_;

#define ctol_1 ctol_

struct {
    doublereal dpenv, alphac, alphae, alpham;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    doublereal qwrmax[5000], qwrmx0[5000];
} dwmax_;

#define dwmax_1 dwmax_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

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
    doublereal delo[5000], delao[5000], amuo[5000], oo[5000], cpo[5000], qdto[
	    5000], velo[5000], visco[5000], thdifo[5000], esumo[5000], delro[
	    5000], epso[5000];
} oldphy_;

#define oldphy_1 oldphy_

struct {
    doublereal tho[5000], thn[5000], thm[5000], ddelm[5000], festime[5000], 
	    thp[5000], qwrst[5000], wmst[5000], qwrmst[5000];
} oldrot2_;

#define oldrot2_1 oldrot2_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal optol, zsi;
    integer idt, idd[4];
} optab_;

#define optab_1 optab_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal cp[5000], hamu[5000], sqdt[5000], thdif[5000], visc[5000];
} temp_;

#define temp_1 temp_

struct {
    doublereal htt0[5000], hpp0[5000], hll0[5000], hrr0[5000];
} entrop_;

#define entrop_1 entrop_

struct {
    doublereal drate[5000], drate0[5000], fmassacc, taucz;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

/* Table of constant values */

static integer c__1 = 1;
static integer c__5000 = 5000;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* HPOINT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int hpoint_(integer *m, doublereal *hstot, doublereal *hs, 
	doublereal *hs1, doublereal *hs2, doublereal *ht, doublereal *hp, 
	doublereal *hr, logical *lc, doublereal *hl, doublereal *hd, 
	doublereal *hcomp, doublereal *ps, doublereal *rs, doublereal *estore,
	 integer *istore, logical *lreset, integer *jxbeg, integer *model, 
	logical *lshell, integer *jcore, integer *jenv, doublereal *omega, 
	doublereal *eta2, doublereal *r0, doublereal *hi, doublereal *hjm, 
	doublereal *hkerot, doublereal *sjtot, doublereal *skerot, doublereal 
	*bl, doublereal *delts, doublereal *fp, doublereal *ft, doublereal *
	hg, doublereal *qiw, doublereal *smass, doublereal *teffl)
{
    /* Initialized data */

    static integer id[7] = { 1,2,4,5,6,7,9 };

    /* Format strings */
    static char fmt_10[] = "(\002 OUTER POINTS DELETED OLD M =\002,i5,\002  "
	    "NEW M =\002,i5)";
    static char fmt_30[] = "(1x,39(\002>\002),40(\002<\002)/1x,\002ERROR IN "
	    "HPOINT\002/1x,\002MAX. STAR T LESS THAN MINIMUM ENVELOPE T.RUN S"
	    "TOPPED\002)";
    static char fmt_60[] = "(\002 OUTER POINT ADDED\002,i5,f15.10,\002  PT"
	    "R\002,3f10.6)";
    static char fmt_110[] = "(1x,\002MORE THAN 100 FLAG POINTS-FIRST 100 RET"
	    "AINED\002)";
    static char fmt_185[] = "(1x,\002FLAG-POINTS\002,20i4)";
    static char fmt_101[] = "(\002 DESIRED NUMBER OF POINTS \002,i6,\002EXCE"
	    "EEDS JSON \002,i6/\002 RUN STOPPED\002)";
    static char fmt_910[] = "(\0021\002,20x,\002OLD POINTS\002,54x,\002NEW P"
	    "OINTS\002/2(3x,\002N\002,5x,\002S\002,8x,\002P\002,7x,\002T\002,"
	    "7x,\002R\002,8x,\002L\002,7x,\002X\002,4x,\002Z\002,3x,\002O1"
	    "6\002,1x))";
    static char fmt_920[] = "(2(1x,i3,f11.7,f8.4,f8.5,f8.4,1pe9.2,0pf6.3,2f5"
	    ".3))";
    static char fmt_930[] = "(1x,i3,f11.7,f8.4,f8.5,f8.4,1pe9.2,0pf6.3,2f5.3)"
	    ;
    static char fmt_940[] = "(65x,i3,f11.7,f8.4,f8.5,f8.4,1pe9.2,0pf6.3,2f5."
	    "3)";
    static char fmt_1020[] = "(\002 POINTS  OLD\002,i5,\002   NEW\002,i5)";
    static char fmt_1120[] = "(1x,\002TOTAL J OF STAR - PREVIOUS \002,1pe21."
	    "13,\002 NEW \002,1pe21.13/\002 TOTAL ROTATIONAL K.E. OF STAR-PRE"
	    "VIOUS \002,1pe21.13,\002 NEW \002,1pe21.13)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    double d_lg10(doublereal *), d_mod(doublereal *, doublereal *), exp(
	    doublereal);

    /* Local variables */
    extern /* Subroutine */ int splintd2_(doublereal *, doublereal *, integer 
	    *, doublereal *, doublereal *, doublereal *, integer *, integer *)
	    , surfopac_(doublereal *);
    static integer i__, j, k;
    static doublereal x, y;
    static integer i0;
    static doublereal y2[5000], dm, dl, dp;
    static integer jj, np, mm;
    static doublereal dx;
    static integer nn;
    static doublereal dz;
    static integer im;
    static doublereal hj, dr, dw, ds1, ds2, ds3, fac, chi[5000], hfo[5000];
    static logical lcz[5000];
    static doublereal fpx[5000], ftx[5000], hko[5000];
    static integer jos, npt, klo, khi, ixx;
    static doublereal dss, dchi;
    static integer jbeg, iend, jend;
    static doublereal delp;
    static integer ntab;
    static doublereal xtab[5000], ytab[5000];
    extern /* Subroutine */ int fpft_(doublereal *, doublereal *, doublereal *
	    , integer *, doublereal *, doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *);
    static integer mnew, ntot;
    extern /* Subroutine */ int momi_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *);
    static doublereal sumj, wmid, pmax1, pmax2, pmax3, pmax4, pmax5;
    static integer iflag, nflag[100], iiflg, jfine;
    static doublereal hpmax[4], wltop, wlbot;
    static logical ldone;
    static integer ntemp;
    static doublereal hlmax, testp;
    static integer jprev;
    extern /* Subroutine */ int ovrot_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, logical *, integer *,
	     logical *, integer *, integer *, integer *, integer *);
    static integer nzone;
    static doublereal sumke, delchi, omegal[5000];
    static integer ixflag[5000];
    extern /* Subroutine */ int splinc_(doublereal *, doublereal *, 
	    doublereal *, integer *);
    static integer minmin, mrzone[26]	/* was [13][2] */, mxzone[24]	/* 
	    was [12][2] */;
    extern /* Subroutine */ int osplin_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *);
    static integer nrzone;
    extern /* Subroutine */ int getrot_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), physic_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, logical *, 
	    integer *);
    static doublereal chiprev;

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_60, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_110, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_185, 0 };
    static cilist io___48 = { 0, 6, 0, fmt_101, 0 };
    static cilist io___69 = { 0, 0, 0, fmt_910, 0 };
    static cilist io___70 = { 0, 0, 0, fmt_920, 0 };
    static cilist io___71 = { 0, 0, 0, fmt_930, 0 };
    static cilist io___72 = { 0, 0, 0, fmt_940, 0 };
    static cilist io___74 = { 0, 0, 0, fmt_1020, 0 };
    static cilist io___86 = { 0, 0, 0, fmt_1120, 0 };


/* MHP 10/02 ADDED MRZONE,MXZONE TO DIMENSION STATEMENTS */
/* MHP 06/02 */
/* Time change of theta */
/* 7/91 ENTROPY TERM COMMON BLOCK ADDED. */
/* MHP 05/02 DEUTERIUM BURNING RATE ADDED */
/* MHP 6/00 ADDED DUMMY VECTOR */
/* MHP 7/02 ADDED CHI VECTOR - A RUNNING TOTAL OF THE NORMALIZED */
/* DIFFERENCES IN M, L, P BETWEEN SHELLS THAT IS USED TO SET THE */
/* POINT SPACING. */
    /* Parameter adjustments */
    --qiw;
    --hg;
    --ft;
    --fp;
    --hkerot;
    --hjm;
    --hi;
    --r0;
    --eta2;
    --omega;
    --estore;
    --rs;
    --ps;
    hcomp -= 16;
    --hd;
    --hl;
    --lc;
    --hr;
    --hp;
    --ht;
    --hs2;
    --hs1;
    --hs;

    /* Function Body */
/*  THIS SUBROUTINE REZONES THE MODEL, SPACING THE SHELLS SUCH THAT */
/*  THE MAXIMUM DISTANCE BETWEEN 2 SUCCESSIVE POINTS IN P,L,X, AND Z */
/*  SPECIFIED BY THE USER IS NOT EXCEEDED.  IT ALSO FLAGS REAL */
/*  DISCONTINUITIES TO PREVENT ARTIFICIAL SMOOTHING. */
    *lreset = FALSE_;
/*  IEND IS THE NUMBER OF SPECIES THE PROGRAM IS KEEPING TRACK OF */
    iend = 11;
    if (flag_1.lexcom) {
	iend = 15;
    }
/* CHECK IF TEMPERATURE OF OUTERMOST HENYEY POINT > MIMIMUM ENVELOPE T */
    if (ht[*m] < ctlim_1.tenv0) {
	for (i__ = *m - 1; i__ >= 1; --i__) {
	    if (ht[i__] > ctlim_1.tenv0) {
		io___5.ciunit = luout_1.ishort;
		s_wsfe(&io___5);
		do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		e_wsfe();
		*m = i__;
		comp_1.senv = hs[*m] - *hstot;
		*lreset = TRUE_;
		goto L40;
	    }
/* L20: */
	}
/*  ENTIRE MODEL HAS T<TENV0 - UNLIKELY - BUT STOP IF TRUE */
	io___6.ciunit = luout_1.ishort;
	s_wsfe(&io___6);
	e_wsfe();
	io___7.ciunit = luout_1.iowr;
	s_wsfe(&io___7);
	e_wsfe();
	s_stop("", (ftnlen)0);
L40:
/*  CHECK IF OUTER POINT T < MAXIMUM ENVELOPE T */
	;
    } else if (ht[*m] > ctlim_1.tenv1 && *istore != 0) {
	++(*m);
	comp_1.senv = estore[4];
	hs[*m] = *hstot + comp_1.senv;
	hp[*m] = hp[*m - 1] + (estore[1] - ps[*istore]);
	ht[*m] = ht[*m - 1] + (estore[1] - ps[*istore]) * .25;
	hr[*m] = hr[*m - 1] + (estore[3] - rs[*istore]);
	hl[*m] = hl[*m - 1];
	i__1 = iend;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    hcomp[i__ + *m * 15] = hcomp[i__ + (*m - 1) * 15];
/* L50: */
	}
	hd[*m] = hp[*m] - ht[*m] - 8.;
	j = *m - 1;
	io___9.ciunit = luout_1.ishort;
	s_wsfe(&io___9);
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hs[j], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hp[j], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ht[j], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hr[j], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hp[*m], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ht[*m], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hr[*m], (ftnlen)sizeof(doublereal));
	e_wsfe();
	*lreset = TRUE_;
    }
/* SET UP FLAGGED POINTS - PROGRAM WILL NOT REZONE ACROSS FLAGGED POINTS */
    iflag = 1;
/* FLAG EDGES OF CENTRAL AND SURFACE CONVECTION ZONES */
    if (*jcore > 1) {
	nflag[iflag - 1] = *jcore;
	++iflag;
    }
    if (*jenv < *m && *jenv > 1) {
	nflag[iflag - 1] = *jenv;
	++iflag;
    }
/* FLAG EDGE OF H SHELL */
    if (*lshell && *jxbeg > 1) {
	nflag[iflag - 1] = *jxbeg - 1;
	++iflag;
    }
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
/*  TEST FOR FLAGGING DUE TO X GRADIENT */
	if ((d__1 = hcomp[i__ * 15 + 1] - hcomp[(i__ - 1) * 15 + 1], abs(d__1)
		) > ctol_1.hpttol[2]) {
	    nflag[iflag - 1] = i__;
	    ++iflag;
/*  TEST FOR FLAGGING DUE TO Z GRADIENT */
	} else if ((d__1 = hcomp[i__ * 15 + 3] - hcomp[(i__ - 1) * 15 + 3], 
		abs(d__1)) > ctol_1.hpttol[3]) {
	    nflag[iflag - 1] = i__;
	    ++iflag;
/*  TEST FOR FLAGGING DUE TO GRADIENT IN LOG OMEGA. */
	} else if (rot_1.lrot) {
	    wltop = d_lg10(&omega[i__]);
	    wlbot = d_lg10(&omega[i__ - 1]);
	    if ((d__1 = wltop - wlbot, abs(d__1)) > ctol_1.hpttol[11]) {
		nflag[iflag - 1] = i__;
		++iflag;
	    }
	}
	if (iflag >= 100) {
	    io___14.ciunit = luout_1.ishort;
	    s_wsfe(&io___14);
	    e_wsfe();
	    goto L130;
	}
/* L120: */
    }
/*  PMAX1 = MAX DEL LOG P BELOW SURFACE C.Z. AND BELOW FINELY ZONED */
/*  REGION AROUND IT. */
/*  PMAX2 = MAX DEL LOG P BETWEEN LOWER EDGE OF FINELY ZONED REGION */
/*  AROUND SURFACE C.Z. AND BASE OF OVERSHOOT REGION. */
/*  PMAX3 = SAME FOR OVERSHOOT REGION. */
/*  PMAX4 = MAX DEL LOG P ABOVE BASE OF SURFACE C.Z. IN FINELY ZONED */
/*  REGION AROUND IT. */
/*  PMAX5 = SAME FOR THE OUTER POINTS IN THE STAR. */
    pmax1 = ctol_1.hpttol[10];
    pmax4 = ctol_1.hpttol[9];
    pmax5 = ctol_1.hpttol[7];
    if (! lc[*m]) {
	jos = *m;
	jfine = *m;
    } else if (*jenv == 1) {
	jos = 1;
	jfine = 1;
    } else {
/*  LOCATE BASE OF OVERSHOOT REGION IF APPLICABLE. */
	if (! dpmix_1.lovste) {
	    i__ = *jenv;
	    jos = *jenv;
	} else {
	    for (jos = *jenv - 1; jos >= 1; --jos) {
		if (hp[jos] - hp[*jenv] > dpmix_1.alphae) {
		    goto L193;
		}
/* L191: */
	    }
L193:
	    ++jos;
	    delp = hp[jos] - hp[*jenv];
	    if (delp > 0.) {
		np = (integer) (delp / ctol_1.hpttol[9]);
		if (d_mod(&delp, &ctol_1.hpttol[9]) != 0.) {
		    ++np;
		}
		pmax3 = delp / (doublereal) np;
	    } else {
		pmax3 = ctol_1.hpttol[9];
	    }
	    if (jos > 1) {
		nflag[iflag - 1] = jos;
		++iflag;
	    }
	}
	if (ctol_1.hpttol[6] == 0.) {
	    jfine = jos;
	} else {
/*  NOW LOCATE BASE OF FINELY ZONED REGION. */
	    if (jos == 1) {
		jfine = 1;
		goto L198;
	    }
	    for (jfine = jos - 1; jfine >= 1; --jfine) {
		if (hp[jfine] - hp[*jenv] > ctol_1.hpttol[6]) {
		    goto L197;
		}
/* L195: */
	    }
L197:
	    ++jfine;
	    if (jfine == jos) {
		goto L198;
	    }
	    delp = hp[jfine] - hp[jos];
	    np = (integer) (delp / ctol_1.hpttol[9]);
	    if (d_mod(&delp, &ctol_1.hpttol[9]) != 0.) {
		++np;
	    }
	    pmax2 = delp / (doublereal) np;
	    if (pmax2 == 0.) {
		pmax2 = ctol_1.hpttol[9];
	    }
	    if (jfine > 1) {
		nflag[iflag - 1] = jfine;
		++iflag;
	    }
L198:
	    ;
	}
    }
L130:
    nflag[iflag - 1] = *m;
/* ARRANGE THE FLAG POINTS IN ASCENDING ORDER */
    if (iflag == 1) {
	goto L180;
    }
L140:
    ldone = TRUE_;
    i__1 = iflag - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (nflag[i__] < nflag[i__ - 1]) {
	    ntemp = nflag[i__ - 1];
	    nflag[i__ - 1] = nflag[i__];
	    nflag[i__] = ntemp;
	    ldone = FALSE_;
	}
/* L150: */
    }
    if (! ldone) {
	goto L140;
    }
/* ENSURE THAT POINTS ARENT FLAGGED MORE THAN ONCE. */
    i__ = 2;
L160:
    if (nflag[i__ - 1] == nflag[i__ - 2]) {
	if (i__ < iflag) {
	    i__1 = iflag - 1;
	    for (j = i__; j <= i__1; ++j) {
		nflag[j - 1] = nflag[j];
/* L170: */
	    }
	}
	--iflag;
    }
    ++i__;
    if (i__ <= iflag) {
	goto L160;
    }
L180:
    io___26.ciunit = luout_1.ishort;
    s_wsfe(&io___26);
    i__1 = iflag;
    for (j = 1; j <= i__1; ++j) {
	do_fio(&c__1, (char *)&nflag[j - 1], (ftnlen)sizeof(integer));
    }
    e_wsfe();
/* BEGIN REFLOATING OF POINTS */
    if (rot_1.lrot) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (omega[i__] > 0.) {
		omegal[i__ - 1] = d_lg10(&omega[i__]);
	    } else {
		omegal[i__ - 1] = 0.;
	    }
/* L190: */
	}
    }
    oldmod_1.hss[0] = hs[1];
    oldmod_1.hpo[0] = hp[1];
    oldmod_1.hlo[0] = hl[1];
    hko[0] = hcomp[16];
    hfo[0] = hcomp[18];
    hlmax = hl[*m];
    for (i__ = *m - 1; i__ >= 1; --i__) {
	if (hl[i__] > hlmax) {
	    hlmax = hl[i__];
	}
    }
    hpmax[0] = ctol_1.hpttol[7];
    hpmax[1] = ctol_1.hpttol[8] * hlmax;
    hpmax[2] = ctol_1.hpttol[4];
    hpmax[3] = ctol_1.hpttol[5];
/*      KFACT = 0 */
/*  200 CONTINUE */
    iiflg = 1;
    j = 2;
    i0 = 2;
/* CHI IS THE NORMALIZED VECTOR OF DIFFERENCES IN M,L,P: */
/* CHI = HS/DELTA M + HL/DELTA L - HP/DELTA P */
    dm = ctol_1.hpttol[1];
    dl = hpmax[1];
    chi[0] = 1.;
    i__1 = *m;
    for (j = 2; j <= i__1; ++j) {
	testp = hp[j] - hp[*jenv];
	if (abs(testp) < ctol_1.hpttol[6]) {
/* FINELY ZONED REGION */
	    dp = ctol_1.hpttol[9];
	} else if (testp > ctol_1.hpttol[6]) {
/* BELOW SURFACE CZ */
	    dp = ctol_1.hpttol[10];
	} else {
/* IN SURFACE CZ */
	    dp = ctol_1.hpttol[7];
	}
	if (hl[j] > hl[j - 1]) {
	    dchi = (hs[j] - hs[j - 1]) / dm + (hl[j] - hl[j - 1]) / dl - (hp[
		    j] - hp[j - 1]) / dp;
	} else {
	    dchi = (hs[j] - hs[j - 1]) / dm - (hp[j] - hp[j - 1]) / dp;
	}
	chi[j - 1] = chi[j - 2] + dchi;
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	xtab[j - 1] = chi[j - 1];
	ytab[j - 1] = hs[j];
    }
/* GET SPLINE COEFFICIENTS */
    splinc_(xtab, ytab, y2, m);
    chiprev = chi[0];
    jprev = 1;
    mnew = 1;
    i__1 = iflag;
    for (i__ = 1; i__ <= i__1; ++i__) {
	delchi = chi[nflag[i__ - 1] - 1] - chiprev;
	npt = (integer) delchi + 1;
	if (mnew + npt > 5000) {
/* EXCEEDED ARRAY DIMENSIONS; COMPLAIN AND STOP */
	    s_wsfe(&io___48);
	    i__2 = mnew + npt;
	    do_fio(&c__1, (char *)&i__2, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&c__5000, (ftnlen)sizeof(integer));
	    e_wsfe();
	    s_stop("9999", (ftnlen)4);
	}
	dchi = delchi / (doublereal) npt;
/* ASSIGN NEW POINTS */
	i__2 = jprev + npt;
	for (j = jprev + 1; j <= i__2; ++j) {
	    x = chiprev + dchi;
	    splintd2_(xtab, ytab, m, y2, &x, &y, &klo, &khi);
	    oldmod_1.hss[j - 1] = y;
	    chiprev = x;

	}
	mnew += npt;
	jprev = mnew;

    }
/* TEST FOR ASSIGNING POINTS BASED ON THE GRADIENT IN X. */
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	xtab[j - 1] = hs[j];
	ytab[j - 1] = hcomp[j * 15 + 1];
    }
/* GET SPLINE COEFFICIENTS */
    splinc_(xtab, ytab, y2, m);
/* ASSIGN INTERPOLATED VECTOR OF X VALUES TO HIO */
    i__1 = mnew;
    for (i__ = 2; i__ <= i__1; ++i__) {
	x = oldmod_1.hss[i__ - 1];
	splintd2_(xtab, ytab, m, y2, &x, &y, &klo, &khi);
	hko[i__ - 1] = y;
    }
/* SKIP IF HPMAX(3) IS ZEROED OUT */
    if (hpmax[2] <= 1e-15) {
	goto L102;
    }
/* TEST ON X-CHANGE (ONLY FOR INCREASING X) USING HIO AS DUMMY ARRAY */
    ixx = 0;
    for (j = mnew; j >= 2; --j) {
	if (hko[j - 1] - hko[j - 2] > hpmax[2]) {
	    ++ixx;
	    ixflag[ixx - 1] = j;
	}
    }
    if (ixx == 0) {
	goto L102;
    }
    mm = mnew;
    i__1 = ixx;
    for (i__ = 1; i__ <= i__1; ++i__) {
	j = ixflag[i__ - 1];
	dx = (hko[j - 1] - hko[j - 2]) / hpmax[2];
/* NUMBER OF NEW POINTS NEEDED */
	nn = (integer) dx;

	dss = (oldmod_1.hss[j - 1] - oldmod_1.hss[j - 2]) / (doublereal) (nn 
		+ 1);
	i__2 = j + nn;
	for (k = mm + nn; k >= i__2; --k) {
	    oldmod_1.hss[k - 1] = oldmod_1.hss[k - nn - 1];

	}
	i__2 = j - 1;
	for (k = j + nn - 1; k >= i__2; --k) {
	    oldmod_1.hss[k - 1] = oldmod_1.hss[k] - dss;
	}
	mm += nn;
    }
    mnew = mm;

L102:
/* TEST FOR ASSIGNING POINTS BASED ON THE GRADIENT IN Z. */
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	xtab[j - 1] = hs[j];
	ytab[j - 1] = hcomp[j * 15 + 3];
    }
/* GET SPLINE COEFFICIENTS */
    splinc_(xtab, ytab, y2, m);
/* ASSIGN INTERPOLATED VECTOR OF Z VALUES TO HGO */
    i__1 = mnew;
    for (i__ = 2; i__ <= i__1; ++i__) {
	x = oldmod_1.hss[i__ - 1];
	splintd2_(xtab, ytab, m, y2, &x, &y, &klo, &khi);
	hfo[i__ - 1] = y;

    }
/* TEST ON Z-CHANGE (ONLY FOR DECREASING Z) USING HIO AS DUMMY ARRAY */
/* SKIP IF HPMAX(4) IS ZEROED OUT */

    if (hpmax[3] <= 1e-15) {
	goto L103;
    }
    ixx = 0;
    for (j = mnew; j >= 2; --j) {
	if (hfo[j - 2] - hfo[j - 1] > hpmax[3]) {
	    ++ixx;
	    ixflag[ixx - 1] = j;
	}
    }

    if (ixx == 0) {
	goto L103;
    }
    mm = mnew;

    i__1 = ixx;
    for (i__ = 1; i__ <= i__1; ++i__) {
	j = ixflag[i__ - 1];
	dz = (hfo[j - 2] - hfo[j - 1]) / hpmax[3];
/* NUMBER OF NEW POINTS NEEDED */
	nn = (integer) dz;
	dss = (oldmod_1.hss[j - 1] - oldmod_1.hss[j - 2]) / (doublereal) (nn 
		+ 1);
	i__2 = j + nn;
	for (k = mm + nn; k >= i__2; --k) {
	    oldmod_1.hss[k - 1] = oldmod_1.hss[k - nn - 1];
	}
	i__2 = j - 1;
	for (k = j + nn - 1; k >= i__2; --k) {
	    oldmod_1.hss[k - 1] = oldmod_1.hss[k] - dss;
	}
	mm += nn;
    }
    mnew = mm;

L103:
/* DELETE NEW POINTS THAT ARE TOO CLOSE TOGETHER. */
/* (NOTE HDO IS BEING USED AS A DUMMY ARRAY HERE). */
    j = 1;
    oldmod_1.hdo[j - 1] = oldmod_1.hss[j - 1];
    i__1 = mnew - 1;
    for (jj = 2; jj <= i__1; ++jj) {

	if (oldmod_1.hss[jj - 1] - oldmod_1.hdo[j - 1] > ctol_1.hpttol[0]) {
	    ++j;
	    oldmod_1.hdo[j - 1] = oldmod_1.hss[jj - 1];
	}
/* L810: */
    }
    ++j;
    oldmod_1.hdo[j - 1] = oldmod_1.hss[mnew - 1];
    mnew = j;
    i__1 = mnew;
    for (j = 2; j <= i__1; ++j) {
	oldmod_1.hss[j - 1] = oldmod_1.hdo[j - 1];
/* L820: */
    }

/*  NOW LOCATE OUTER EDGE OF CONVECTIVE CORE AND INNER EDGE OF CONVECTIVE */
/*  ENVELOPE IN THE NEW POINT DISTRIBUTION. */
    if (*jcore > 1) {
	i__1 = mnew;
	for (j = 2; j <= i__1; ++j) {
	    if (oldmod_1.hss[j - 1] > hs[*jcore]) {
		goto L824;
	    }
/* L823: */
	}
L824:
	*jcore = j - 1;
    } else {
	*jcore = 1;
    }
    if (*jenv < *m) {
	for (j = mnew - 1; j >= 1; --j) {
	    if (oldmod_1.hss[j - 1] < hs[*jenv]) {
		goto L826;
	    }
/* L825: */
	}
L826:
	*jenv = j + 1;
    } else {
	*jenv = mnew;
    }
    if (*jcore > 1) {
	i__1 = *jcore;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    lc[i__] = TRUE_;
/* L827: */
	}
	jbeg = *jcore + 1;
    } else {
	jbeg = 1;
    }
    if (*jenv < mnew) {
	i__1 = mnew;
	for (i__ = *jenv; i__ <= i__1; ++i__) {
	    lc[i__] = TRUE_;
/* L828: */
	}
	jend = *jenv - 1;
    } else {
	jend = mnew;
    }
    if (jend < 1 || jbeg > mnew) {
	goto L830;
    }
    i__1 = jend;
    for (j = jbeg; j <= i__1; ++j) {
	lc[j] = FALSE_;
/* L829: */
    }
L830:
/*  NOW USE AN OSCILLATORY SPLINE TO FIT THE OLD RUN OF PHYSICAL VARIABLES */
/*  AT THE NEW RUN OF MASS POINTS. */
    ntab = *m;
    ntot = mnew;
/*  XVAL=RUN OF NEW MODEL MASS COORDINATES(HSS) */
/*  XTAB = RUN OF OLD MODEL MASS CO-ORDINATES(HS) */
/*  YTAB = RUN OF VARIABLE WHOSE VALUE AT THE NEW MASS POINTS */
/*         IS DESIRED(HP,HT,HL,HR,HD,ETC.) */
/*  NTAB = NUMBER OF DATA POINTS(M) */
/*  NTOT=NUMBER OF POINTS AT WHICH SPLINE IS TO BE EVALUTED(MNEW) */
/*  YVAL = OUTPUT RUN OF VARIABLE VALUES AT THE NEW RUN OF MASS POINTS. */
/*  FORM OF CALL IS CALL OSPLIN(XVAL,YVAL,XTAB,YTAB,NTAB,NTOT) */
/*  DO EACH COMPOSITION IN ORDER USING HPO AND HTO AS DUMMY ARRAYS. */
/* 7/91 ADD ENTROPY TERM INTERPOLATION. */
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	oldmod_1.hpo[j - 1] = entrop_1.htt0[j - 1];
/* L904: */
    }
    osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], oldmod_1.hpo, &ntab, &ntot);
    i__1 = mnew;
    for (j = 1; j <= i__1; ++j) {
	entrop_1.htt0[j - 1] = oldmod_1.hto[j - 1];
/* L905: */
    }

    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	oldmod_1.hpo[j - 1] = entrop_1.hpp0[j - 1];
/* L906: */
    }
    osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], oldmod_1.hpo, &ntab, &ntot);
    i__1 = mnew;
    for (j = 1; j <= i__1; ++j) {
	entrop_1.hpp0[j - 1] = oldmod_1.hto[j - 1];
/* L907: */
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	oldmod_1.hpo[j - 1] = entrop_1.hll0[j - 1];
/* L911: */
    }
    osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], oldmod_1.hpo, &ntab, &ntot);
    i__1 = mnew;
    for (j = 1; j <= i__1; ++j) {
	entrop_1.hll0[j - 1] = oldmod_1.hto[j - 1];
/* L912: */
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	oldmod_1.hpo[j - 1] = entrop_1.hrr0[j - 1];
/* L913: */
    }
    osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], oldmod_1.hpo, &ntab, &ntot);
    i__1 = mnew;
    for (j = 1; j <= i__1; ++j) {
	entrop_1.hrr0[j - 1] = oldmod_1.hto[j - 1];
/* L914: */
    }
    i__1 = iend;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    oldmod_1.hpo[j - 1] = hcomp[i__ + j * 15];
/* L833: */
	}
	osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], oldmod_1.hpo, &ntab, &
		ntot);
	i__2 = mnew;
	for (j = 1; j <= i__2; ++j) {
	    hcomp[i__ + j * 15] = oldmod_1.hto[j - 1];
/* L835: */
	}
/*  HCOMPP IS THE ARRAY OF COMPOSITION AT THE BEGINNING OF THE TIMESTEP. */
/*  THIS IS NEEDED FOR COMPOSITION DIFFUSION IN ROTATING MODELS. */
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    oldmod_1.hpo[j - 1] = oldmod_1.hcompp[i__ + j * 15 - 16];
/* L840: */
	}
	osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], oldmod_1.hpo, &ntab, &
		ntot);
	i__2 = mnew;
	for (j = 1; j <= i__2; ++j) {
	    oldmod_1.hcompp[i__ + j * 15 - 16] = oldmod_1.hto[j - 1];
/* L845: */
	}
/* L850: */
    }
/*  HCOMPM IS THE ARRAY OF CHANGES IN COMPOSITION DUE TO NUCLEAR BURNING. */
/*  THIS IS NEEDED FOR COMPOSITION DIFFUSION IN ROTATING MODELS. */
    for (i__ = 1; i__ <= 7; ++i__) {
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    oldmod_1.hpo[j - 1] = burn_1.hcompm[id[i__ - 1] + j * 15 - 16];
/* L847: */
	}
	osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], oldmod_1.hpo, &ntab, &
		ntot);
	i__1 = mnew;
	for (j = 1; j <= i__1; ++j) {
	    burn_1.hcompm[id[i__ - 1] + j * 15 - 16] = oldmod_1.hto[j - 1];
/* L848: */
	}
/* L849: */
    }
/* MHP 05/02 IF THE SURFACE DEUTERIUM IS ABOVE */
/* THRESHOLD (1.0D-14) FIND THE NEW RUN OF */
/* DEUTERIUM BURNING RATES */
    if (flag_1.lexcom && hcomp[*m * 15 + 12] >= 1e-14) {
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    oldmod_1.hpo[j - 1] = deuter_1.drate0[j - 1];
	}
	osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], oldmod_1.hpo, &ntab, &
		ntot);
	i__1 = mnew;
	for (j = 1; j <= i__1; ++j) {
	    deuter_1.drate0[j - 1] = oldmod_1.hto[j - 1];
	}
    }
/* NOW FIND RUN OF P,R,L,T,AND RHO IN THAT ORDER FOR THE NEW POINTS. */
    osplin_(oldmod_1.hss, oldmod_1.hpo, &hs[1], &hp[1], &ntab, &ntot);
    osplin_(oldmod_1.hss, oldmod_1.hro, &hs[1], &hr[1], &ntab, &ntot);
    osplin_(oldmod_1.hss, oldmod_1.hlo, &hs[1], &hl[1], &ntab, &ntot);
    osplin_(oldmod_1.hss, oldmod_1.hto, &hs[1], &ht[1], &ntab, &ntot);
    osplin_(oldmod_1.hss, oldmod_1.hdo, &hs[1], &hd[1], &ntab, &ntot);
/* FOR ROTATING MODELS FIND THE NEW RUN OF OMEGA,J/M,FP,FT,R0,AND ETA2. */
    if (rot_1.lrot) {
	osplin_(oldmod_1.hss, oldrot_1.wold, &hs[1], &omega[1], &ntab, &ntot);
	osplin_(oldmod_1.hss, oldrot_1.hjx, &hs[1], &hjm[1], &ntab, &ntot);
	osplin_(oldmod_1.hss, fpx, &hs[1], &fp[1], &ntab, &ntot);
	osplin_(oldmod_1.hss, ftx, &hs[1], &ft[1], &ntab, &ntot);
	osplin_(oldmod_1.hss, oldrot_1.r0x, &hs[1], &r0[1], &ntab, &ntot);
	osplin_(oldmod_1.hss, oldrot_1.eta2x, &hs[1], &eta2[1], &ntab, &ntot);
    }

/*     SPIT OUT POINT DISTRIBUTION DETAILS IF REQUESTED */
    if (ccout2_1.ldebug && ccout1_1.npoint < 9999) {
	if (*model % ccout1_1.npoint == 0) {
	    minmin = min(*m,mnew);

	    io___69.ciunit = luout_1.idebug;
	    s_wsfe(&io___69);
	    e_wsfe();
	    io___70.ciunit = luout_1.idebug;
	    s_wsfe(&io___70);
	    i__1 = minmin;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hko[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hfo[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hcomp[i__ * 15 + 9], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&oldmod_1.hss[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&oldmod_1.hpo[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&oldmod_1.hto[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&oldmod_1.hro[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&oldmod_1.hlo[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hcomp[i__ * 15 + 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hcomp[i__ * 15 + 3], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hcomp[i__ * 15 + 9], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	    if (*m > minmin) {
		++minmin;
		io___71.ciunit = luout_1.idebug;
		s_wsfe(&io___71);
		i__1 = *m;
		for (i__ = minmin; i__ <= i__1; ++i__) {
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&hko[i__ - 1], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&hfo[i__ - 1], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&hcomp[i__ * 15 + 9], (ftnlen)
			    sizeof(doublereal));
		}
		e_wsfe();
	    } else if (mnew > minmin) {
		++minmin;
		io___72.ciunit = luout_1.idebug;
		s_wsfe(&io___72);
		i__1 = mnew;
		for (i__ = minmin; i__ <= i__1; ++i__) {
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&oldmod_1.hss[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&oldmod_1.hpo[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&oldmod_1.hto[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&oldmod_1.hro[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&oldmod_1.hlo[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&hcomp[i__ * 15 + 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&hcomp[i__ * 15 + 3], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&hcomp[i__ * 15 + 9], (ftnlen)
			    sizeof(doublereal));
		}
		e_wsfe();
	    }
	}
    }
/* TRANSFER NEW POINTS. */
    i__1 = mnew;
    for (j = 1; j <= i__1; ++j) {
	hs[j] = oldmod_1.hss[j - 1];
	hp[j] = oldmod_1.hpo[j - 1];
	ht[j] = oldmod_1.hto[j - 1];
	hr[j] = oldmod_1.hro[j - 1];
	hl[j] = oldmod_1.hlo[j - 1];
	hd[j] = oldmod_1.hdo[j - 1];
/* L1000: */
    }
    if (rot_1.lrot) {
	i__1 = mnew;
	for (j = 1; j <= i__1; ++j) {
	    hjm[j] = oldrot_1.hjx[j - 1];
	    omega[j] = oldrot_1.wold[j - 1];
	    fp[j] = fpx[j - 1];
	    ft[j] = ftx[j - 1];
	    eta2[j] = oldrot_1.eta2x[j - 1];
	    r0[j] = oldrot_1.r0x[j - 1];
/* L1005: */
	}
    }
/* MHP 6/00 INTERPOLATED IN ENERGY GENERATION AT START OF TIMESTEP */
    if (rot_1.lrot || flag_1.lexcom && dpmix_1.lovste) {
	osplin_(oldmod_1.hss, oldphy_1.esumo, &hs[1], scrtch_1.sesum, &ntab, &
		ntot);
	i__1 = *m;
	for (im = 1; im <= i__1; ++im) {
	    ytab[im - 1] = scrtch_1.sesum[im - 1] + scrtch_1.seg[im * 7 - 2] 
		    + scrtch_1.seg[im * 7 - 1];
	}
	osplin_(oldmod_1.hss, oldphy_1.epso, &hs[1], ytab, &ntab, &ntot);
    }
    io___74.ciunit = luout_1.ishort;
    s_wsfe(&io___74);
    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&mnew, (ftnlen)sizeof(integer));
    e_wsfe();
    *m = mnew;
/* SET UP WEIGHTS AND MASSES */
    ds3 = exp(const3_1.clndp * hs[1]);
    ds2 = -ds3;
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
	ds1 = ds2;
	ds2 = ds3;
	ds3 = exp(const3_1.clndp * hs[i__]);
	hs1[i__ - 1] = ds2;
	hs2[i__ - 1] = (ds3 - ds1) * .5;
/* L1030: */
    }
    hs1[*m] = ds3;
    hs2[*m] = exp(const1_1.cln * *hstot) - (ds2 + ds3) * .5;
    if (rot_1.lrot) {
/*  FIRST GUESS AT MOMENT OF INERTIA(HI) */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    hi[i__] = const1_1.cc23 * hs2[i__] * exp(const1_1.cln * 2. * hr[
		    i__]);
/* L1070: */
	}
/*   CALCULATE OVERSHOOT */
	ovrot_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], &lc[1], m, 
		lcz, mrzone, mxzone, &nrzone, &nzone);
/*   FIND THE ANGULAR VELOCITY OMEGA THAT CORRESPONDS TO THE GIVEN */
/*   SPECIFIC ANGULAR MOMENTUM HJM. */
	getrot_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], lcz, m, &eta2[1], &
		hi[1], &omega[1], &qiw[1], &r0[1]);
/*  CALCULATE FP,FT,R0 AND ETA2 GIVEN OMEGA */
	fpft_(&hd[1], &hr[1], &hs[1], m, &omega[1], &eta2[1], &fp[1], &ft[1], 
		&hg[1], &r0[1]);
/*  FIND CORRECT MOMENT OF INERTIA(HI) */
	momi_(&eta2[1], &hd[1], &hr[1], &hs[1], &hs2[1], &c__1, m, &omega[1], 
		&r0[1], &hi[1], &qiw[1], m);
/*  FIND NEW TOTAL ANGULAR MOMENTUM */
	sumj = 0.;
	sumke = 0.;
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    hj = hjm[i__] * hs2[i__];
	    hkerot[i__] = omega[i__] * .5 * hj;
	    sumj += hj;
	    sumke += hkerot[i__];
/* L1110: */
	}
	io___86.ciunit = luout_1.ishort;
	s_wsfe(&io___86);
	do_fio(&c__1, (char *)&(*sjtot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sumj, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*skerot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sumke, (ftnlen)sizeof(doublereal));
	e_wsfe();
	*sjtot = sumj;
	*skerot = sumke;
/*  STORE THE OLD MODEL STRUCTURE FOR USE IN DIFFUSION. */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    oldrot_1.wold[i__ - 1] = omega[i__];
	    oldrot_1.hgo[i__ - 1] = hg[i__];
	    oldrot_1.hio[i__ - 1] = hi[i__];
	    oldrot_1.eta2x[i__ - 1] = eta2[i__];
	    oldrot_1.r0x[i__ - 1] = r0[i__];
	    oldmod_1.lco[i__ - 1] = lc[i__];
	    oldmod_1.lczo[i__ - 1] = lcz[i__ - 1];
/* MHP 10/91 J/M STORED IN HJX FOR I/O USE. */
	    oldrot_1.hjx[i__ - 1] = hjm[i__];
/* L1130: */
	}
/* MHP 9/91 CHANGE : T GRADIENTS STORED IF LEXCOM=T AND LOVSTE=T; OR FOR */
/* ROTATION; THIS IS NEEDED SO THAT THE BASE OF THE OVERSHOOT REGION FOR */
/* PRE-MS MODELS CAN BE ACCURATELY LOCATED. */
    }
    if (rot_1.lrot || flag_1.lexcom && dpmix_1.lovste) {
/* END OF 9/91 CHANGE */
/*   FIND THE NEW RUN OF PHYSICAL VARIABLES AT THE NEW SET OF POINTS; */
/*   THIS IS NEEDED EVEN IN THE ABSENCE OF DIFFUSION TO ACCURATELY LOCATE */
/*   THE EDGES OF CONVECTION ZONES. */
	physic_(&fp[1], &ft[1], &hcomp[16], &hd[1], &hg[1], &hl[1], &hp[1], &
		hr[1], &hs[1], &ht[1], &lc[1], lcz, m);
/*   FOR DIFFUSION STORE THE AUXILLARY QUANTITIES NEEDED TO CALCULATE */
/*   VELOCITIES AT THE START OF THE TIMESTEP WITH THE NEW POINT DISTRIBUTION */
/*   SO THAT A SERIES OF SMALL DIFFUSION TIMESTEPS CAN BE TAKEN WITHIN */
/*   ONE LARGE EVOLUTIONARY TIMESTEP. */
	i__1 = *m;
	for (im = 1; im <= i__1; ++im) {
	    oldphy_1.delro[im - 1] = scrtch_1.sdel[im * 3 - 3];
	    oldphy_1.delo[im - 1] = scrtch_1.sdel[im * 3 - 2];
	    oldphy_1.delao[im - 1] = scrtch_1.sdel[im * 3 - 1];
	    oldphy_1.amuo[im - 1] = temp_1.hamu[im - 1];
	    oldphy_1.oo[im - 1] = scrtch_1.so[im - 1];
	    oldphy_1.cpo[im - 1] = temp_1.cp[im - 1];
	    oldphy_1.qdto[im - 1] = temp_1.sqdt[im - 1];
	    oldphy_1.velo[im - 1] = scrtch_1.svel[im - 1];
	    oldphy_1.visco[im - 1] = temp_1.visc[im - 1];
	    oldphy_1.thdifo[im - 1] = temp_1.thdif[im - 1];
/* MHP 06/02 */
	    oldrot2_1.ddelm[im - 1] = oldphy_1.delao[im - 1] - oldphy_1.delo[
		    im - 1];
/* MHP 6/00 CALCULATED EARLIER */
/*            ESUMO(IM) = SESUM(IM) */
	    dwmax_1.qwrmx0[im - 1] = dwmax_1.qwrmax[im - 1];
/* L1040: */
	}
/* MHP 06/02 ADDED TERM FOR THE TIME EVOLUTION */
/* OF THE ANGULAR VELOCITY DISTRIBUTION */
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    dr = exp(const1_1.cln * hr[i__]) - exp(const1_1.cln * hr[i__ - 1])
		    ;
	    dw = omega[i__] - omega[i__ - 1];
	    wmid = (omega[i__] + omega[i__ - 1]) * .5;
	    fac = (hr[i__] + hr[i__ - 1]) * 2. - (hs[i__] + hs[i__ - 1]) * .5 
		    - const2_1.cgl;
	    oldrot2_1.tho[i__ - 1] = exp(const1_1.cln * fac) * wmid * dw / dr;
	    oldrot2_1.qwrst[i__ - 1] = dw / dr;
	}
    }
/*  CALCULATE NEW SURFACE OPACITY TABLE IF NEEDED. */
    if ((d__1 = comp_1.xnew - hcomp[*m * 15 + 1], abs(d__1)) > 1e-8) {
	comp_1.xnew = hcomp[*m * 15 + 1];
	comp_1.znew = hcomp[*m * 15 + 3];
	surfopac_(&comp_1.xnew);
    }
    return 0;
} /* hpoint_ */


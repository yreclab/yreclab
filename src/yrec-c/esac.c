/* esac.f -- translated by f2c (version 20061008).
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
    integer itime;
} lreadco_;

#define lreadco_1 lreadco_

struct {
    doublereal epl[21560]	/* was [5][56][77] */, xx[5];
} ee_;

#define ee_1 ee_

struct {
    doublereal q[4], h__[4], xxh;
} aa_;

#define aa_1 aa_

struct {
    doublereal xz[215600]	/* was [5][10][56][77] */, t6list[4312]	/* 
	    was [77][56] */, rho[77], t6a[56], esk[4312]	/* was [56][
	    77] */, esk2[4312]	/* was [56][77] */, dfsx[5], dfs[56], dfsr[77]
	    , xa[5];
    integer m, mf;
} a_;

#define a_1 a_

struct {
    doublereal zz[5];
    integer iri[10], index[10], nta[77];
} b_;

#define b_1 b_

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bb_;

#define bb_1 bb_

struct {
    doublereal esact, eos[10];
} e_;

#define e_1 e_

/* Table of constant values */

static integer c__1 = 1;
static integer c__5 = 5;

/* ************************************************************************* */
/*       SUBROUTINE ESAC (XH,ZTAB,T6,R,IORDER,IRAD,*)  ! KC 2025-05-31 */
/* Subroutine */ int esac_(doublereal *xh, doublereal *t6, doublereal *r__, 
	integer *iorder, integer *irad)
{
    /* Initialized data */

    static doublereal aprop = 83.1446304;

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    integer do_fio(integer *, char *, ftnlen), s_wsle(cilist *), do_lio(
	    integer *, integer *, char *, ftnlen), e_wsle(void);

    /* Local variables */
    static integer i__, j;
    static doublereal z__;
    extern /* Subroutine */ int t6rinterp_(doublereal *, doublereal *);
    static doublereal p0;
    static integer mg, mh, mi;
    static doublereal ri;
    static integer ir, it, iv, is, iw, ms, mf2, ihi, imd, ilo;
    static doublereal slr, slt, xxi, sum1, sum2, frac[7];
    extern doublereal quad_(integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal dixr, sum23, sum33;
    static char blank[1];
    static doublereal fracz;
    extern doublereal gmass_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal moles, tmass;
    extern /* Subroutine */ int readco_(void), radsub_(doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal eground;

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 0, 0, "(\" IORDER CANNOT EXCEED 10\")", 0 };
    static cilist io___4 = { 0, 0, 0, "(\" IRAD MUST BE 0 OR 1\")", 0 };
    static cilist io___19 = { 0, 0, 0, "(\" IHI,ILO,IMD\",3I5)", 0 };
    static cilist io___28 = { 0, 0, 0, "(\"Z DOES NOT MATCH Z IN EOSDATA FIL"
	    "ES YOU ARE\" ,\" USING\")", 0 };
    static cilist io___30 = { 0, 0, 0, "(\" PROBLEM IT IR,L3,K3,IQ,IP=\", 6I"
	    "5)", 0 };
    static cilist io___31 = { 0, 0, 0, "(3E12.4)", 0 };
    static cilist io___34 = { 0, 0, 0, "(\" PROBLEM IT IR,L3,K3,IQ,IP=\", 6I"
	    "5)", 0 };
    static cilist io___35 = { 0, 0, 0, "(3E12.4)", 0 };
    static cilist io___42 = { 0, 0, 0, "(\" MASS FRACTIONS EXCEED UNITY (61"
	    ")\")", 0 };
    static cilist io___43 = { 0, 0, 0, 0, 0 };
    static cilist io___44 = { 0, 0, 0, "(\" T6/LOGR OUTSIDE OF TABLE RANGE ("
	    "62)\")", 0 };
    static cilist io___45 = { 0, 0, 0, 0, 0 };
    static cilist io___46 = { 0, 0, 0, 0, 0 };
    static cilist io___47 = { 0, 0, 0, "(\"T6/LOG RHO IN EMPTY REGION OF TAB"
	    "LE (65)\")", 0 };
    static cilist io___48 = { 0, 0, 0, "(\"XH,T6,R=\", 3E12.4)", 0 };
    static cilist io___49 = { 0, 0, 0, "(\" Z DOES NOT MATCH Z IN EOSDATA* F"
	    "ILES YOU ARE\", \" USING (66)\")", 0 };
    static cilist io___50 = { 0, 0, 0, "(\"MF,ZZ(MF)=\",I5,E12.4)", 0 };
    static cilist io___51 = { 0, 0, 0, "(\"  IQ,IP,K3,L3,XH,T6,R,Z= \",4I5,4"
	    "E12.4)", 0 };


/* ..... THE PURPOSE OF THIS SUBROUTINE IS TO INTERPOLATE */
/*      THE EQUATION OF STATE AND ITS DERIVATIVES IN X, T6, DENSITY */
/*        IZI=0 RECALULATE TABLE INDICES TO USE; =1 KEEP PREVIOUS */
/*        XH=HYDROGEN MASS FRACTION */
/*        ZTAB IS METAL FRACTION OF THE EOSDATA TABLES YOU ARE USING. */
/*           INCLUDED ONLY FOR PURPOSE OF PREVENTING MISMATCH */
/*        T6=T6=TEMPERATURE IN MILLIONS OF DEGREES KELVIN */
/*        R=RHO=RHO=DENSITY(G/CM**3) */
/* ..... TO USE ESAC INSERT COMMON/E/ ESACT,EOS(10) IN THE CALLING ROUTINE. */
/*      THIS COMMON CONTAINS THE INTERPOLATED EOS VALUES FOR THE EOS */

/* ..... EOS(I) ARE OBTAINED FROM A QUADRADIC INTERPOLATION AT */
/*      FIXED T6 AT THREE VALUES OF RHO; FOLLOWED BY QUADRATIC */
/*      INTERPOLATION ALONG T6. RESULTS SMOOTHED BY MIXING */
/*      OVERLAPPING QUADRATICS. */
/*         DEFINITIONS: */

/*            T6 IS THE TEMPERATURE IN UNITS OF 10**6 K */

/*            RHO IS THE DENSITY IN GRAMS/CC */
/*            R=RHO/T6**3 */
/*            EOS(1) IS THE PRESSURE IN MEGABARS (10**12DYNE/CM**2) */
/* YCK NO USE EOS(2) IS ENERGY IN 10**12 ERGS/GM. ZERO IS ZERO T6 */
/* YCK NO USE EOS(3) IS THE ENTROPY IN UNITS OF ENERGY/T6 */
/* YCK NO USE EOS(4) IS DE/DRHO AT CONSTANT T6 */
/*            EOS(5) IS THE SPECIFIC HEAT, DE/DT6 AT CONSTANT V. */
/*            EOS(6) IS DLOGP/DLOGRHO AT CONSTANT T6. */
/*                   COX AND GUIL1 EQ 9.82 */
/*            EOS(7) IS DLOGP/DLOGT6 AT CONXTANT RHO. */
/*                   COX AND GUIL1 EQ 9.81 */
/*            EOS(8) IS GAMMA1. EQS. 9.88 COX AND GUILI. */
/*            EOS(9) IS GAMMA2/(GAAMMA2-1). EQS. 9.88 COX AND GUILI */
/*            EOS(10) IS GAMMA3-1. EQS 9.88 COX AND GUILI */
/*            IORDER SETS MAXIMUM INDEX FOR EOS(I);I.E., IORDER=1 */
/*                   GIVES JUST THE PRESSURE */

/*            IRAD  IF =0 NO RADIATION CORRECTION; IF =1 ADDS RADIATION */
/*            INDEX(I),I=1,10  SETS ORDER IN WHICH THE EQUATION OF STATE */
/*            VARIABLES ARE STORED IN EOS(I).  ABOVE ORDER CORRESPONDS */
/*            TO BLOCK DATA STATEMENT: */
/*                 DATA (INDEX(I),I=1,10)/1,2,3,4,5,6,7,8,9,10/. */
/*            IF YOU, FOR EXAMPLE, ONLY WANT TO RETURN GAMMA1: SET IORDER=1 */
/*            AND SET: DATA (INDEX(I),I=1,10)/8,2,3,4,5,6,7,1,9,10/ */


    *(unsigned char *)blank = ' ';
    if (*iorder > 10) {
	io___3.ciunit = luout_1.ishort;
	s_wsfe(&io___3);
	e_wsfe();
    }
    if (*irad != 0 && *irad != 1) {
	io___4.ciunit = luout_1.ishort;
	s_wsfe(&io___4);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    xxi = *xh;
    ri = *r__;
    slt = *t6;
    slr = *r__;
    if (lreadco_1.itime != 12345678) {
	lreadco_1.itime = 12345678;
	for (i__ = 1; i__ <= 10; ++i__) {
	    for (j = 1; j <= 10; ++j) {
		if (b_1.index[i__ - 1] == j) {
		    b_1.iri[i__ - 1] = j;
		}
	    }
	}
	for (i__ = 1; i__ <= 5; ++i__) {
	    ee_1.xx[i__ - 1] = a_1.xa[i__ - 1];
	}

/* ..... READ THE DATA FILES */
	readco_();
	z__ = b_1.zz[0];
	if (z__ + *xh - 1e-6 > 1.) {
	    goto L61;
	}
    }


/* ..... DETERMINE T6,RHO GRID POINTS TO USE IN THE */
/*      INTERPOLATION. */
    if (slt > a_1.t6a[0] || slt < a_1.t6a[55]) {
	goto L62;
    }
    if (slr < a_1.rho[0] || slr > a_1.rho[76]) {
	goto L62;
    }



    ilo = 2;
    ihi = 5;
L8:
    if (ihi - ilo > 1) {
	imd = (ihi + ilo) / 2;
	if (*xh <= a_1.xa[imd - 1] + 1e-7) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L8;
    }
    i__ = ihi;
    a_1.mf = i__ - 2;
    mg = i__ - 1;
    mh = i__;
    mi = i__ + 1;
    mf2 = mi;
    if (*xh < 1e-6) {
	mh = 1;
	mh = 1;
	mg = 1;
	mi = 2;
	mf2 = 1;
    }
    if (*xh <= a_1.xa[1] + 1e-7 || *xh >= a_1.xa[2] - 1e-7) {
	mf2 = mh;
    }

    ilo = 2;
    ihi = 77;
L12:
    if (ihi - ilo > 1) {
	imd = (ihi + ilo) / 2;
	if (slr == a_1.rho[imd - 1]) {
	    ihi = imd;
	    goto L13;
	}
	if (slr <= a_1.rho[imd - 1]) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L12;
    }
L13:
    i__ = ihi;
    bb_1.l1 = i__ - 2;
    bb_1.l2 = i__ - 1;
    bb_1.l3 = i__;
    bb_1.l4 = bb_1.l3 + 1;

    ilo = 56;
    ihi = 2;
L11:
    if (ilo - ihi > 1) {
	imd = (ihi + ilo) / 2;
	if (*t6 == a_1.t6list[imd * 77 - 77]) {
	    ilo = imd;
	    goto L14;
	}
	if (*t6 <= a_1.t6list[imd * 77 - 77]) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L11;
    }
L14:
    i__ = ilo;
    bb_1.k1 = i__ - 2;
    bb_1.k2 = i__ - 1;
    bb_1.k3 = i__;
    bb_1.k4 = bb_1.k3 + 1;
    if (bb_1.k3 == 0) {
	io___19.ciunit = luout_1.ishort;
	s_wsfe(&io___19);
	e_wsfe();
    }
/*     CHECK TO DETERMINE IF INTERPOLATION INDICES FALL WITHIN */
/*     TABLE BOUNDARIES.  CHOOSE LARGEST ALLOWED SIZE. */
    sum1 = 0.;
    sum2 = 0.;
    sum23 = 0.;
    sum33 = 0.;
    i__1 = a_1.mf + 3;
    for (a_1.m = a_1.mf; a_1.m <= i__1; ++a_1.m) {
	i__2 = bb_1.l1 + 1;
	for (ir = bb_1.l1; ir <= i__2; ++ir) {
	    i__3 = bb_1.k1 + 1;
	    for (it = bb_1.k1; it <= i__3; ++it) {
		sum1 += a_1.xz[a_1.m + ((it + ir * 56) * 10 + 1) * 5 - 2856];
	    }
	}
	i__2 = bb_1.l1 + 2;
	for (ir = bb_1.l1; ir <= i__2; ++ir) {
	    i__3 = bb_1.k1 + 2;
	    for (it = bb_1.k1; it <= i__3; ++it) {
		sum2 += a_1.xz[a_1.m + ((it + ir * 56) * 10 + 1) * 5 - 2856];
	    }
	}
	i__2 = bb_1.l1 + 2;
	for (ir = bb_1.l1; ir <= i__2; ++ir) {
	    i__3 = bb_1.k1 + 3;
	    for (it = bb_1.k1; it <= i__3; ++it) {
		sum23 += a_1.xz[a_1.m + ((it + ir * 56) * 10 + 1) * 5 - 2856];
	    }
	}
	i__2 = bb_1.l1 + 3;
	for (ir = bb_1.l1; ir <= i__2; ++ir) {
	    i__3 = bb_1.k1 + 3;
	    for (it = bb_1.k1; it <= i__3; ++it) {
		sum33 += a_1.xz[a_1.m + ((it + ir * 56) * 10 + 1) * 5 - 2856];
	    }
	}
    }
    bb_1.iq = 2;
    bb_1.ip = 2;
    if (sum2 > 1e30) {
	if (sum1 < 1e25) {
	    bb_1.k1 = bb_1.k3 - 3;
	    bb_1.k2 = bb_1.k1 + 1;
	    bb_1.k3 = bb_1.k2 + 1;
	    bb_1.l1 = bb_1.l3 - 3;
	    bb_1.l2 = bb_1.l1 + 1;
	    bb_1.l3 = bb_1.l2 + 1;
	    goto L15;
	} else {
	    goto L65;
	}
    }
    if (sum23 < 1e30) {
	bb_1.ip = 3;
    }
    if (sum33 < 1e30) {
	bb_1.iq = 3;
    }
    if (*t6 >= a_1.t6list[77] + 1e-7) {
	bb_1.ip = 2;
    }
    if (slr <= a_1.rho[1] + 1e-15) {
	bb_1.iq = 2;
    }
    if (bb_1.l3 == 77) {
	bb_1.iq = 2;
    }
L15:
    i__1 = *iorder;
    for (iv = 1; iv <= i__1; ++iv) {
	i__2 = mf2;
	for (a_1.m = a_1.mf; a_1.m <= i__2; ++a_1.m) {
	    is = 0;
/* __________ */
	    i__3 = bb_1.l1 + bb_1.iq;
	    for (ir = bb_1.l1; ir <= i__3; ++ir) {
		i__4 = bb_1.k1 + bb_1.ip;
		for (it = bb_1.k1; it <= i__4; ++it) {
		    ee_1.epl[a_1.m + (it + ir * 56) * 5 - 286] = a_1.xz[a_1.m 
			    + (iv + (it + ir * 56) * 10) * 5 - 2856];
		    is = 1;
		}
	    }
/* L123: */
	}
	if (b_1.zz[mg - 1] != b_1.zz[a_1.mf - 1] || b_1.zz[mh - 1] != b_1.zz[
		a_1.mf - 1]) {
	    io___28.ciunit = luout_1.ishort;
	    s_wsfe(&io___28);
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
	if (z__ != b_1.zz[a_1.mf - 1]) {
	    goto L66;
	}
	is = 0;
	iw = 1;
	i__2 = bb_1.l1 + bb_1.iq;
	for (ir = bb_1.l1; ir <= i__2; ++ir) {
	    i__3 = bb_1.k1 + bb_1.ip;
	    for (it = bb_1.k1; it <= i__3; ++it) {
		if (mf2 == 1) {
		    a_1.esk[it + ir * 56 - 57] = ee_1.epl[a_1.mf + (it + ir * 
			    56) * 5 - 286];
		    goto L46;
		}
		a_1.esk[it + ir * 56 - 57] = quad_(&is, &iw, xh, &ee_1.epl[
			a_1.mf + (it + ir * 56) * 5 - 286], &ee_1.epl[mg + (
			it + ir * 56) * 5 - 286], &ee_1.epl[mh + (it + ir * 
			56) * 5 - 286], &ee_1.xx[a_1.mf - 1], &ee_1.xx[mg - 1]
			, &ee_1.xx[mh - 1]);
		if (a_1.esk[it + ir * 56 - 57] > 1e20) {
		    io___30.ciunit = luout_1.ishort;
		    s_wsfe(&io___30);
		    do_fio(&c__1, (char *)&it, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&ir, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&bb_1.l3, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&bb_1.k3, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&bb_1.iq, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&bb_1.ip, (ftnlen)sizeof(integer));
		    e_wsfe();
		    io___31.ciunit = luout_1.ishort;
		    s_wsfe(&io___31);
		    i__4 = a_1.mf + 2;
		    for (ms = a_1.mf; ms <= i__4; ++ms) {
			do_fio(&c__1, (char *)&ee_1.epl[ms + (it + ir * 56) * 
				5 - 286], (ftnlen)sizeof(doublereal));
		    }
		    e_wsfe();
		}
		is = 1;
L46:
		;
	    }
/* L45: */
	}
	if (mi == mf2) {
/* INTERPOLATE BETWEEN QUADRATICS */
	    is = 0;
	    iw = 1;
	    dixr = (ee_1.xx[mh - 1] - *xh) * a_1.dfsx[mh - 1];
	    i__2 = bb_1.l1 + bb_1.iq;
	    for (ir = bb_1.l1; ir <= i__2; ++ir) {
		i__3 = bb_1.k1 + bb_1.ip;
		for (it = bb_1.k1; it <= i__3; ++it) {
		    a_1.esk2[it + ir * 56 - 57] = quad_(&is, &iw, xh, &
			    ee_1.epl[mg + (it + ir * 56) * 5 - 286], &
			    ee_1.epl[mh + (it + ir * 56) * 5 - 286], &
			    ee_1.epl[mi + (it + ir * 56) * 5 - 286], &ee_1.xx[
			    mg - 1], &ee_1.xx[mh - 1], &ee_1.xx[mi - 1]);
		    if (a_1.esk[it + ir * 56 - 57] > 1e20) {
			io___34.ciunit = luout_1.ishort;
			s_wsfe(&io___34);
			do_fio(&c__1, (char *)&it, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&ir, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&bb_1.l3, (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&bb_1.k3, (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&bb_1.iq, (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&bb_1.ip, (ftnlen)sizeof(
				integer));
			e_wsfe();
			io___35.ciunit = luout_1.ishort;
			s_wsfe(&io___35);
			i__4 = mg + 2;
			for (ms = mg; ms <= i__4; ++ms) {
			    do_fio(&c__1, (char *)&ee_1.epl[ms + (it + ir * 
				    56) * 5 - 286], (ftnlen)sizeof(doublereal)
				    );
			}
			e_wsfe();
		    }
		    a_1.esk[it + ir * 56 - 57] = a_1.esk[it + ir * 56 - 57] * 
			    dixr + a_1.esk2[it + ir * 56 - 57] * (1. - dixr);
		    is = 1;
		}
/* L47: */
	    }
	}
	is = 0;

/* ..... COMPLETED X INTERPOLATION. NOW INTERPOLATE T6 AND RHO ON A */
/*      4X4 GRID. (T6A(I),I=I1,I1+3),RHO(J),J=J1,J1+3)).PROCEDURE */
/*      MIXES OVERLAPPING QUADRATICS TO OBTAIN SMOOTHED DERIVATIVES. */


	t6rinterp_(&slr, &slt);
	e_1.eos[iv - 1] = e_1.esact;
/* L124: */
    }
    p0 = *t6 * *r__;
    e_1.eos[b_1.iri[0] - 1] *= p0;
/* INTERPOLATED IN P/PO */
    e_1.eos[b_1.iri[1] - 1] *= *t6;
/* YCK >    EOS(IRI(4))=EOS(IRI(4))/SQRT(R*T6) ! INTERP DE/DR/SQRT(R/T6) */
/* INTERPOLATED IN E/T6 */
    tmass = gmass_(xh, &z__, &moles, &eground, &fracz, frac);
    if (*irad == 1) {
	radsub_(t6, r__, &moles, &tmass);
    } else {
	e_1.eos[b_1.iri[4] - 1] = e_1.eos[b_1.iri[4] - 1] * moles * aprop / 
		tmass;
    }
    return 0;
L61:
    io___42.ciunit = luout_1.ishort;
    s_wsfe(&io___42);
    e_wsfe();
    io___43.ciunit = luout_1.ishort;
    s_wsle(&io___43);
    do_lio(&c__5, &c__1, (char *)&z__, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&(*xh), (ftnlen)sizeof(doublereal));
    e_wsle();
    s_stop("", (ftnlen)0);
L62:
    io___44.ciunit = luout_1.ishort;
    s_wsfe(&io___44);
    e_wsfe();
    io___45.ciunit = luout_1.ishort;
    s_wsle(&io___45);
    do_lio(&c__5, &c__1, (char *)&a_1.t6a[0], (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&slt, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&a_1.t6a[55], (ftnlen)sizeof(doublereal));
    e_wsle();
    io___46.ciunit = luout_1.ishort;
    s_wsle(&io___46);
    do_lio(&c__5, &c__1, (char *)&a_1.rho[0], (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&slr, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&a_1.rho[76], (ftnlen)sizeof(doublereal));
    e_wsle();
    return 1;
L65:
    io___47.ciunit = luout_1.ishort;
    s_wsfe(&io___47);
    e_wsfe();
    io___48.ciunit = luout_1.ishort;
    s_wsfe(&io___48);
    do_fio(&c__1, (char *)&(*xh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*t6), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*r__), (ftnlen)sizeof(doublereal));
    e_wsfe();
    return 1;
L66:
    io___49.ciunit = luout_1.ishort;
    s_wsfe(&io___49);
    e_wsfe();
    io___50.ciunit = luout_1.ishort;
    s_wsfe(&io___50);
    do_fio(&c__1, (char *)&a_1.mf, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&b_1.zz[a_1.mf - 1], (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___51.ciunit = luout_1.ishort;
    s_wsfe(&io___51);
    do_fio(&c__1, (char *)&bb_1.ip, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bb_1.iq, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bb_1.k3, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bb_1.l3, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*xh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*t6), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*r__), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&z__, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_stop("", (ftnlen)0);
    return 0;
} /* esac_ */


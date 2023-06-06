/* esac01.f -- translated by f2c (version 20100827).
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
    integer itime;
} lreadco_;

#define lreadco_1 lreadco_

struct {
    doublereal epl[161395]	/* was [5][191][169] */, xx[5];
} eeeos_;

#define eeeos_1 eeeos_

struct {
    doublereal q[4], h__[4], xxh;
} aaeos_;

#define aaeos_1 aaeos_

struct aeos_1_ {
    doublereal xz[1613950]	/* was [5][10][191][169] */, t6list[32279]	
	    /* was [169][191] */, rho[169], t6a[191], esk[32279]	/* 
	    was [191][169] */, esk2[32279]	/* was [191][169] */, dfsx[5],
	     dfs[191], dfsr[169];
    integer m, mf;
    doublereal xa[5];
};

#define aeos_1 (*(struct aeos_1_ *) &aeos_)

struct beos_1_ {
    integer iri[10], index[10], nta[169];
    doublereal zz[5];
};

#define beos_1 (*(struct beos_1_ *) &beos_)

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bbeos_;

#define bbeos_1 bbeos_

struct {
    doublereal esact, eos[10];
} eeos_;

#define eeos_1 eeos_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Initialized data */

struct {
    doublereal fill_1[1711513];
    doublereal e_2[5];
    } aeos_ = { {0}, 0., .2, .4, .6, .8 };

struct {
    doublereal fill_1[5];
    integer e_2[179];
    integer fill_3[10];
    } beos_ = { {0}, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 191, 191, 191, 191, 191, 
	    191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 
	    191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 
	    191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 
	    191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 
	    191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 
	    191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 
	    191, 191, 191, 191, 191, 191, 191, 191, 191, 190, 189, 188, 187, 
	    186, 185, 184, 174, 134, 134, 134, 134, 133, 133, 133, 132, 132, 
	    98, 92, 85, 85, 77, 77, 71, 63, 63, 63, 59, 59, 53, 51, 46, 46, 
	    44, 44, 44, 44, 44, 44, 44, 44, 44, 38, 38, 38, 33, 33, 33, 33, 
	    33, 33, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
	    29, 29, 27, 26, 25, 23, 22, 20, 19, 18, 17, 16 };


/* Table of constant values */

static integer c__1 = 1;
static integer c__9 = 9;
static integer c__5 = 5;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     ESAC01 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int esac01_(doublereal *xh, doublereal *ztab, doublereal *t6,
	 doublereal *r__, integer *iorder, integer *irad)
{
    /* Initialized data */

    static doublereal aprop = 83.14511;
    static char id[15] = "OPALEOS/ESAC01:";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern doublereal quadeos01_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer i__, j;
    static doublereal z__, p0;
    static integer mg, mh, mi;
    static doublereal ri;
    static integer ir, it, iv, is, iw, ms;
    extern /* Subroutine */ int t6rinteos01_(doublereal *, doublereal *), 
	    readcoeos01_(void);
    static integer mf2, ihi, imd, ilo, ipu, iqu;
    static doublereal slr, slt, xxi, sum1, sum2, frac[7], dixr, sum23, sum33;
    static char blank[1];
    static doublereal fracz, moles, tmass;
    extern doublereal gmass01_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    extern /* Subroutine */ int radsub01_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal eground;

    /* Fortran I/O blocks */
    static cilist io___4 = { 0, 0, 0, "(A, \" iorder cannot exceed 9\")", 0 };
    static cilist io___5 = { 0, 0, 0, "(A, \" Irad must be 0 or 1\")", 0 };
    static cilist io___22 = { 0, 0, 0, "(A, \" ihi,ilo,imd\",3i5)", 0 };
    static cilist io___31 = { 0, 0, 0, "(A,\"Z does not match Z in OEOS01 fi"
	    "les you are\" ,\" using\")", 0 };
    static cilist io___33 = { 0, 0, 0, "(A,\" problem it ir,l3,k3,iq,ip=\", "
	    "6i5)", 0 };
    static cilist io___34 = { 0, 0, 0, "(3e12.4)", 0 };
    static cilist io___37 = { 0, 0, 0, "(A,\" problem it ir,l3,k3,iq,ip=\", "
	    "6i5)", 0 };
    static cilist io___38 = { 0, 0, 0, "(3e12.4)", 0 };
    static cilist io___45 = { 0, 0, 0, 0, 0 };
    static cilist io___46 = { 0, 0, 0, 0, 0 };
    static cilist io___47 = { 0, 0, 0, 0, 0 };
    static cilist io___48 = { 0, 0, 0, 0, 0 };
    static cilist io___49 = { 0, 0, 0, 0, 0 };
    static cilist io___50 = { 0, 0, 0, 0, 0 };
    static cilist io___51 = { 0, 0, 0, "(\"xh,t6,r=\", 3e12.4)", 0 };
    static cilist io___52 = { 0, 0, 0, 0, 0 };
    static cilist io___53 = { 0, 0, 0, "(\"mf,zz(mf)=\",i5,e12.4)", 0 };
    static cilist io___54 = { 0, 0, 0, "(\"  iq,ip,k3,l3,xh,t6,r,z= \",4i5,4"
	    "e12.4)", 0 };


/*      The purpose of this subroutine is to interpolate */
/*      the equation of state and its derivatives in X, T6, density */
/*        izi=0 recalulate table indices to use; =1 keep previous */
/*        xh=hydrogen mass fraction */
/*        ztab is metal fraction of the EOSdata tables you are using. */
/*           included only for purpose of preventing mismatch */
/*        t6=T6=temperature in millions of degrees kelvin */
/*        r=rho=Rho=density(g/cm**3) */
/* ..... to use esac01 insert common/eeos/ esact,eos(10) in the calling routine. */
/*      This common contains the interpolated EOS values for the EOS */

/* ..... eos(i) are obtained from a quadradic interpolation at */
/*      fixed T6 at three values of Rho; followed by quadratic */
/*      interpolation along T6. Results smoothed by mixing */
/*      overlapping quadratics. */
/*         definitions: */

/*            T6 is the temperature in units of 10**6 K */

/*            rho is the density in grams/cc */
/*            R=Rho/T6**3 */
/*            eos(1) is the pressure in megabars (10**12dyne/cm**2) */
/*            eos(2) is energy in 10**12 ergs/gm. Zero is zero T6 */
/*            eos(3) is the entropy in units of energy/T6 */
/*            eos(4) is the specific heat, dE/dT6 at constant V. */
/*            eos(5) is dlogP/dlogRho at constant T6. */
/*                   Cox and Guil1 eq 9.82 */
/*            eos(6) is dlogP/dlogT6 at conxtant Rho. */
/*                   Cox and Guil1 eq 9.81 */
/*            eos(7) is gamma1. Eqs. 9.88 Cox and Guili. */
/*            eos(8) is gamma2/(gaamma2-1). Eqs. 9.88 Cox and Guili */
/*            eos(9) is gamma3-1. Eqs 9.88 Cox and Guili */
/*            iorder sets maximum index for eos(i);i.e., iorder=1 */
/*                   gives just the pressure */

/*            irad  if =0 no radiation correction; if =1 adds radiation */
/*            index(i),i=1,10  sets order in which the equation of state */
/*            variables are stored in eos(i).  Above order corresponds */
/*            to block data statement: */
/*                 data (index(i),i=1,10)/1,2,3,4,5,6,7,8,9,10/. */
/*            If you, for example, only want to return gamma1: set iorder=1 */
/*            and set: data (index(i),i=1,10)/8,2,3,4,5,6,7,1,9,10/ */


/* *************************************************************************** */

/*    parameters: */
/* 	mx is the number of x's in the 2001 Opal EOS table */
/* 	mv is the maximum number of thermmodynamic variables in the 2001 */
/* 		Opal EOS table.  Note that the input tables only contain 9. */
/* 	nr is the number of densities in the table. */
/* 	nt is the max number of t6's associated with an x/density.  See */
/* 		below for more details about the table. */

/* *************************************************************************** */
/* *************************************************************************** */

/*    common lreadco definitions: */
/* 	itime is the first time switch.  It is initially true. After the */
/* 	first pass it is set to false.  When it is true, the tables are */
/* 	read and associated variables are initialized. */
/*    common eeeos definitions */
/* 	xx is an auxilliary array containing the same values of x as array xa. */

/* *************************************************************************** */
/* *************************************************************************** */

/*  common aeos definitions: */

/*    xz is the array of thermodynamic variables, as a funtion of four arguments: */
/* 	arg 1: 	identifies the value of x in the corresponding array xa, ie, */
/* 		xz(1,*,*,*) refers to values at x=xa(1)=0.00, xz(2,*,*,*) */
/* 		refers to values at x=xa(2)=0.20, etc. */
/* 	arg 2:	identifies which thermodynamic variable.  xz(*,1,*,*) refers to */
/* 		the thermodynamic variable specified for eos(1) - by default the */
/* 		pressure, xz(*,2,*,*) refers to the thermodynamic variable */
/* 		specified for eos(2), etc. */
/* 	arg 3:	identifies the value of t6 in the corresponding array t6a */
/* 		(and t6list).  e.g., xz(*,*,1,*) refers to values at */
/* 		t6=t6a(1)=100, xz(*,*,2,*) refers to values at t6=t6a(2), etc. */
/* 	arg 4:	identifies the vaue of d, the density, in the corresponding */
/* 		array rho. eg, xz(*,*,*,1) refers to values at d=rho(1)=10**-14, */
/* 		xz(*,*,*,2) refers to values at d-rho(2), etc. */
/* 	Therefore, in the default eos case, xz(1,1,1,1) would be the pressure */
/* 	at x=0.00, t6=100, density=10**-14. */

/*    t6listis the array of t6 (temperature in units of 10**6 degrees Kelvin) */
/* 	The arguments match the first and fourth arguments in array xz above, */
/* 	with the first argument being associated with a temperature and the */
/* 	second with a density. */

/* 	In the first column, associated with the density of 10**-14, */
/* 	temperatures range from t6=100 in t6list(1,1) to t6=.002 in */
/* 	t6list(1,191).  In the last column, associated with a density */
/* 	of 10**7, temperatures range from t6=100 in t6list(169,1) to */
/* 	t6=22.5 in t6list(169,16).  About 10% of the table in vicinity */
/* 	of the lower right hand corner is empty.  The table is homogeneous */
/* 	in t6, in that for each row in the table, all non-empty elements */
/* 	have the same value of t6.  In row 1, all t6's are 100. In row */
/* 	191, all t6's in the non-empty part of the table are .002, etc. */

/*    rho is to array of density in units of grams per cc.  This array has */
/* 	one argument, matching the fourth argument in array xz.  The */
/* 	first density in the table is for density 10**-14, and the last */
/* 	(169th) is for density 10**7. */

/*    t6a is an auxiliary array of temperatures.  It has the full range of */
/* 	temmperatures, from t6a(1)=100 to t6a(191)=.002.  (It exactly */
/* 	matches the first column of t6list) */

/*    xa is the array of the tabulated values of x, eg, xa(1)=0.00, xa(2)=0.20, */
/* 	through xa(5)=0.80. */

/*    dsfx is the first of three auxilliary arrays used in interpolation. */
/* 	dfsx(2)=1/(xa(2)-xa(1)), dfsx(3)=1/(xa(3)-x1(2), ..., */
/* 	dsfx(5)=1/(xa(5)-xa(4)). */

/*    dfs is the second auxilliary array used in interpolation. */
/* 	dfs(2)=1/(t6a(2)-t6a(1), ..., dfs(191)=1/(t6a(191)-t6a(190)). */

/*    dfsr is the third auxilliary array used in interpolaltion. */
/* 	dfsr(2)=1/(rho(2)-rho(1)), ..., dfsr(169)=1/(rho(169)-rho(168)). */

/* *************************************************************************** */
/* *************************************************************************** */

/*    common beos definitions */

/*    array index defines the order in which thermodynamic variables are */
/* 	returned in array eos and stored in array xz.  By default, */
/* 	index(1)=1, index(2)=2 ,  ..., index(10)=10.  For our purposes, */
/* 	I see no reason to change index. */

/*    array iri provides the inverse mapping to array index. */
/* 	index(iri(i))=iri(index(1)=i, for i = 1, 2 ..., 10. */
/* 	in the default case, iri(1)=1, iri(2)=2, ..., iri(10)=10. */

/*    array nta provides the index in array t6a of the lower limits of */
/* 	temperature in the xz array as a function of density.  For */
/* 	example, nta(1)=191, and t6a(nta(1))=t6a(191)=.002, the */
/* 	lowest temperature associated with the first density, */
/* 	rho(1)=10**-14.  At the highest density, in column 169, */
/* 	rho(169)=10**7. The associated nta(169)=16, identifies */
/* 	the lowest temperature for this density, and */
/* 	t6a(nta(169))=t6a(16)=22.5. */

/*    array zz contains the values of z read in from the 2001 Opal EOS table. */
/* 	It can be used for checking purposes. */

/* *************************************************************************** */
/*    common eeos definitions: */

/*    array eos is an output array containing the values of the thermodynamic */
/* 	variables obtained by interpolation.  These interplated values */
/* 	are for the specified x, t6 and density. */

    *(unsigned char *)blank = ' ';
    if (*iorder > 9) {
	io___4.ciunit = luout_1.ishort;
	s_wsfe(&io___4);
	do_fio(&c__1, id, (ftnlen)15);
	e_wsfe();
    }
    if (*irad != 0 && *irad != 1) {
	io___5.ciunit = luout_1.ishort;
	s_wsfe(&io___5);
	do_fio(&c__1, id, (ftnlen)15);
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
		if (beos_1.index[i__ - 1] == j) {
		    beos_1.iri[i__ - 1] = j;
		}
	    }
	}
	for (i__ = 1; i__ <= 5; ++i__) {
	    eeeos_1.xx[i__ - 1] = aeos_1.xa[i__ - 1];
	}

/* ..... read the data files */
	readcoeos01_();
	z__ = beos_1.zz[0];
	if (z__ + *xh - 1e-6 > 1.) {
	    goto L61;
	}
    }


/* ..... Determine T6,rho grid points to use in the */
/*      interpolation. */
    if (slt > aeos_1.t6a[0] || slt < aeos_1.t6a[190]) {
	goto L62;
    }
    if (slr < aeos_1.rho[0] || slr > aeos_1.rho[168]) {
	goto L62;
    }



    ilo = 2;
    ihi = 5;
L8:
    if (ihi - ilo > 1) {
	imd = (ihi + ilo) / 2;
	if (*xh <= aeos_1.xa[imd - 1] + 1e-7) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L8;
    }
    i__ = ihi;
    aeos_1.mf = i__ - 2;
    mg = i__ - 1;
    mh = i__;
    mi = i__ + 1;
    mf2 = mi;
    if (*xh < 1e-6) {
	aeos_1.mf = 1;
	mg = 1;
	mh = 1;
	mi = 2;
	mf2 = 1;
    }
    if (*xh <= aeos_1.xa[1] + 1e-7 || *xh >= aeos_1.xa[2] - 1e-7) {
	mf2 = mh;
    }

    ilo = 2;
    ihi = 169;
L12:
    if (ihi - ilo > 1) {
	imd = (ihi + ilo) / 2;
	if (slr == aeos_1.rho[imd - 1]) {
	    ihi = imd;
	    goto L13;
	}
	if (slr <= aeos_1.rho[imd - 1]) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L12;
    }
L13:
    i__ = ihi;
    bbeos_1.l1 = i__ - 2;
    bbeos_1.l2 = i__ - 1;
    bbeos_1.l3 = i__;
    bbeos_1.l4 = bbeos_1.l3 + 1;
    iqu = 3;
    if (bbeos_1.l4 > 169) {
	iqu = 2;
    }

    ilo = 191;
    ihi = 2;
L11:
    if (ilo - ihi > 1) {
	imd = (ihi + ilo) / 2;
	if (*t6 == aeos_1.t6list[imd * 169 - 169]) {
	    ilo = imd;
	    goto L14;
	}
	if (*t6 <= aeos_1.t6list[imd * 169 - 169]) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L11;
    }
L14:
    i__ = ilo;
    bbeos_1.k1 = i__ - 2;
    bbeos_1.k2 = i__ - 1;
    bbeos_1.k3 = i__;
    bbeos_1.k4 = bbeos_1.k3 + 1;
    ipu = 3;
    if (bbeos_1.k4 > 191) {
	ipu = 2;
    }
    if (bbeos_1.k3 == 0) {
	io___22.ciunit = luout_1.ishort;
	s_wsfe(&io___22);
	do_fio(&c__1, id, (ftnlen)15);
	e_wsfe();
    }
/*     check to determine if interpolation indices fall within */
/*     table boundaries.  choose largest allowed size. */
    sum1 = 0.;
    sum2 = 0.;
    sum23 = 0.;
    sum33 = 0.;
    i__1 = mf2;
    for (aeos_1.m = aeos_1.mf; aeos_1.m <= i__1; ++aeos_1.m) {
	i__2 = bbeos_1.l1 + 1;
	for (ir = bbeos_1.l1; ir <= i__2; ++ir) {
	    i__3 = bbeos_1.k1 + 1;
	    for (it = bbeos_1.k1; it <= i__3; ++it) {
		sum1 += aeos_1.xz[aeos_1.m + ((it + ir * 191) * 10 + 1) * 5 - 
			9606];
	    }
	}
	i__2 = bbeos_1.l1 + 2;
	for (ir = bbeos_1.l1; ir <= i__2; ++ir) {
	    i__3 = bbeos_1.k1 + 2;
	    for (it = bbeos_1.k1; it <= i__3; ++it) {
		sum2 += aeos_1.xz[aeos_1.m + ((it + ir * 191) * 10 + 1) * 5 - 
			9606];
	    }
	}
	if (ipu == 3) {
	    i__2 = bbeos_1.l1 + 2;
	    for (ir = bbeos_1.l1; ir <= i__2; ++ir) {
		i__3 = bbeos_1.k1 + ipu;
		for (it = bbeos_1.k1; it <= i__3; ++it) {
		    sum23 += aeos_1.xz[aeos_1.m + ((it + ir * 191) * 10 + 1) *
			     5 - 9606];
		}
	    }
	} else {
	    sum23 = 2e30;
	}
	if (iqu == 3) {
	    i__2 = bbeos_1.l1 + 3;
	    for (ir = bbeos_1.l1; ir <= i__2; ++ir) {
		i__3 = bbeos_1.k1 + ipu;
		for (it = bbeos_1.k1; it <= i__3; ++it) {
		    sum33 += aeos_1.xz[aeos_1.m + ((it + ir * 191) * 10 + 1) *
			     5 - 9606];
		}
	    }
	} else {
	    sum33 = 2e30;
	}
    }
    bbeos_1.iq = 2;
    bbeos_1.ip = 2;
    if (sum2 > 1e30) {
	if (sum1 < 1e25) {
	    bbeos_1.k1 = bbeos_1.k3 - 3;
	    bbeos_1.k2 = bbeos_1.k1 + 1;
	    bbeos_1.k3 = bbeos_1.k2 + 1;
	    bbeos_1.l1 = bbeos_1.l3 - 3;
	    bbeos_1.l2 = bbeos_1.l1 + 1;
	    bbeos_1.l3 = bbeos_1.l2 + 1;
	    goto L15;
	} else {
	    goto L65;
	}
    }
    if (sum23 < 1e30) {
	bbeos_1.ip = 3;
    }
    if (sum33 < 1e30) {
	bbeos_1.iq = 3;
    }
    if (*t6 >= aeos_1.t6list[169] + 1e-7) {
	bbeos_1.ip = 2;
    }
    if (slr <= aeos_1.rho[1] + 1e-15) {
	bbeos_1.iq = 2;
    }
    if (bbeos_1.l3 == 169 || bbeos_1.k3 == 191) {
	bbeos_1.iq = 2;
	bbeos_1.ip = 2;
    }
L15:
    i__1 = *iorder;
    for (iv = 1; iv <= i__1; ++iv) {
	i__2 = mf2;
	for (aeos_1.m = aeos_1.mf; aeos_1.m <= i__2; ++aeos_1.m) {
	    is = 0;
/* __________ */
	    i__3 = bbeos_1.l1 + bbeos_1.iq;
	    for (ir = bbeos_1.l1; ir <= i__3; ++ir) {
		i__4 = bbeos_1.k1 + bbeos_1.ip;
		for (it = bbeos_1.k1; it <= i__4; ++it) {
		    eeeos_1.epl[aeos_1.m + (it + ir * 191) * 5 - 961] = 
			    aeos_1.xz[aeos_1.m + (iv + (it + ir * 191) * 10) *
			     5 - 9606];
		    is = 1;
		}
	    }
/* L123: */
	}
	if (beos_1.zz[mg - 1] != beos_1.zz[aeos_1.mf - 1] || beos_1.zz[mh - 1]
		 != beos_1.zz[aeos_1.mf - 1]) {
	    io___31.ciunit = luout_1.ishort;
	    s_wsfe(&io___31);
	    do_fio(&c__1, id, (ftnlen)15);
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
	if (z__ != beos_1.zz[aeos_1.mf - 1]) {
	    goto L66;
	}
	is = 0;
	iw = 1;
	i__2 = bbeos_1.l1 + bbeos_1.iq;
	for (ir = bbeos_1.l1; ir <= i__2; ++ir) {
	    i__3 = bbeos_1.k1 + bbeos_1.ip;
	    for (it = bbeos_1.k1; it <= i__3; ++it) {
		if (mf2 == 1) {
		    aeos_1.esk[it + ir * 191 - 192] = eeeos_1.epl[aeos_1.mf + 
			    (it + ir * 191) * 5 - 961];
		    goto L46;
		}
		aeos_1.esk[it + ir * 191 - 192] = quadeos01_(&is, &iw, xh, &
			eeeos_1.epl[aeos_1.mf + (it + ir * 191) * 5 - 961], &
			eeeos_1.epl[mg + (it + ir * 191) * 5 - 961], &
			eeeos_1.epl[mh + (it + ir * 191) * 5 - 961], &
			eeeos_1.xx[aeos_1.mf - 1], &eeeos_1.xx[mg - 1], &
			eeeos_1.xx[mh - 1]);
		if (aeos_1.esk[it + ir * 191 - 192] > 1e20) {
		    io___33.ciunit = luout_1.ishort;
		    s_wsfe(&io___33);
		    do_fio(&c__1, id, (ftnlen)15);
		    do_fio(&c__1, (char *)&it, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&ir, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&bbeos_1.l3, (ftnlen)sizeof(integer)
			    );
		    do_fio(&c__1, (char *)&bbeos_1.k3, (ftnlen)sizeof(integer)
			    );
		    do_fio(&c__1, (char *)&bbeos_1.iq, (ftnlen)sizeof(integer)
			    );
		    do_fio(&c__1, (char *)&bbeos_1.ip, (ftnlen)sizeof(integer)
			    );
		    e_wsfe();
		    io___34.ciunit = luout_1.ishort;
		    s_wsfe(&io___34);
		    i__4 = aeos_1.mf + 2;
		    for (ms = aeos_1.mf; ms <= i__4; ++ms) {
			do_fio(&c__1, (char *)&eeeos_1.epl[ms + (it + ir * 
				191) * 5 - 961], (ftnlen)sizeof(doublereal));
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
/* interpolate between quadratics */
	    is = 0;
	    iw = 1;
	    dixr = (eeeos_1.xx[mh - 1] - *xh) * aeos_1.dfsx[mh - 1];
	    i__2 = bbeos_1.l1 + bbeos_1.iq;
	    for (ir = bbeos_1.l1; ir <= i__2; ++ir) {
		i__3 = bbeos_1.k1 + bbeos_1.ip;
		for (it = bbeos_1.k1; it <= i__3; ++it) {
		    aeos_1.esk2[it + ir * 191 - 192] = quadeos01_(&is, &iw, 
			    xh, &eeeos_1.epl[mg + (it + ir * 191) * 5 - 961], 
			    &eeeos_1.epl[mh + (it + ir * 191) * 5 - 961], &
			    eeeos_1.epl[mi + (it + ir * 191) * 5 - 961], &
			    eeeos_1.xx[mg - 1], &eeeos_1.xx[mh - 1], &
			    eeeos_1.xx[mi - 1]);
		    if (aeos_1.esk[it + ir * 191 - 192] > 1e20) {
			io___37.ciunit = luout_1.ishort;
			s_wsfe(&io___37);
			do_fio(&c__1, id, (ftnlen)15);
			do_fio(&c__1, (char *)&it, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&ir, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&bbeos_1.l3, (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&bbeos_1.k3, (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&bbeos_1.iq, (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&bbeos_1.ip, (ftnlen)sizeof(
				integer));
			e_wsfe();
			io___38.ciunit = luout_1.ishort;
			s_wsfe(&io___38);
			i__4 = mg + 2;
			for (ms = mg; ms <= i__4; ++ms) {
			    do_fio(&c__1, (char *)&eeeos_1.epl[ms + (it + ir *
				     191) * 5 - 961], (ftnlen)sizeof(
				    doublereal));
			}
			e_wsfe();
		    }
		    aeos_1.esk[it + ir * 191 - 192] = aeos_1.esk[it + ir * 
			    191 - 192] * dixr + aeos_1.esk2[it + ir * 191 - 
			    192] * (1. - dixr);
		    is = 1;
		}
/* L47: */
	    }
	}
	is = 0;

/* ..... completed X interpolation. Now interpolate T6 and rho on a */
/*      4x4 grid. (t6a(i),i=i1,i1+3),rho(j),j=j1,j1+3)).Procedure */
/*      mixes overlapping quadratics to obtain smoothed derivatives. */


	t6rinteos01_(&slr, &slt);
	eeos_1.eos[iv - 1] = eeos_1.esact;
/* L124: */
    }
    p0 = *t6 * *r__;
    eeos_1.eos[beos_1.iri[0] - 1] *= p0;
/* interpolated in p/po */
    eeos_1.eos[beos_1.iri[1] - 1] *= *t6;
/* interpolated in E/T6 */
    tmass = gmass01_(xh, &z__, &moles, &eground, &fracz, frac);
    if (*irad == 1) {
	radsub01_(t6, r__, &moles, &tmass);
    } else {
	eeos_1.eos[beos_1.iri[3] - 1] = eeos_1.eos[beos_1.iri[3] - 1] * moles 
		* aprop / tmass;
    }
    return 0;
L61:
    io___45.ciunit = luout_1.ishort;
    s_wsle(&io___45);
    do_lio(&c__9, &c__1, id, (ftnlen)15);
    do_lio(&c__9, &c__1, "Mass fractions exceed unity (61)", (ftnlen)32);
    e_wsle();
    io___46.ciunit = luout_1.ishort;
    s_wsle(&io___46);
    do_lio(&c__9, &c__1, "Z, XH", (ftnlen)5);
    do_lio(&c__5, &c__1, (char *)&z__, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&(*xh), (ftnlen)sizeof(doublereal));
    e_wsle();
    s_stop("", (ftnlen)0);
L62:
    io___47.ciunit = luout_1.ishort;
    s_wsle(&io___47);
    do_lio(&c__9, &c__1, id, (ftnlen)15);
    do_lio(&c__9, &c__1, " T6 or rho outside of table range (62)", (ftnlen)38)
	    ;
    e_wsle();
    io___48.ciunit = luout_1.ishort;
    s_wsle(&io___48);
    do_lio(&c__9, &c__1, "t6, t6a(1),t6a(nt):", (ftnlen)19);
    do_lio(&c__5, &c__1, (char *)&slt, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&aeos_1.t6a[0], (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&aeos_1.t6a[190], (ftnlen)sizeof(doublereal))
	    ;
    e_wsle();
    io___49.ciunit = luout_1.ishort;
    s_wsle(&io___49);
    do_lio(&c__9, &c__1, "slr,r,rho(1),rho(nr):", (ftnlen)21);
    do_lio(&c__5, &c__1, (char *)&slr, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&(*r__), (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&aeos_1.rho[0], (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&aeos_1.rho[168], (ftnlen)sizeof(doublereal))
	    ;
    e_wsle();
    return 1;
L65:
    io___50.ciunit = luout_1.ishort;
    s_wsle(&io___50);
    do_lio(&c__9, &c__1, id, (ftnlen)15);
    do_lio(&c__9, &c__1, "T6/rho in empty region of OPAL 2001 EOS", (ftnlen)
	    39);
    do_lio(&c__9, &c__1, " table (65)", (ftnlen)11);
    e_wsle();
    io___51.ciunit = luout_1.ishort;
    s_wsfe(&io___51);
    do_fio(&c__1, (char *)&(*xh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*t6), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*r__), (ftnlen)sizeof(doublereal));
    e_wsfe();
    return 1;
L66:
    io___52.ciunit = luout_1.ishort;
    s_wsle(&io___52);
    do_lio(&c__9, &c__1, id, (ftnlen)15);
    do_lio(&c__9, &c__1, " Z does not match Z in OPAL 2001 EOS files", (
	    ftnlen)42);
    do_lio(&c__9, &c__1, " you are using (66)", (ftnlen)19);
    e_wsle();
    io___53.ciunit = luout_1.ishort;
    s_wsfe(&io___53);
    do_fio(&c__1, (char *)&aeos_1.mf, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&beos_1.zz[aeos_1.mf - 1], (ftnlen)sizeof(
	    doublereal));
    e_wsfe();
    io___54.ciunit = luout_1.ishort;
    s_wsfe(&io___54);
    do_fio(&c__1, (char *)&bbeos_1.ip, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bbeos_1.iq, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bbeos_1.k3, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bbeos_1.l3, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*xh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*t6), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*r__), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&z__, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_stop("", (ftnlen)0);
    return 0;
} /* esac01_ */


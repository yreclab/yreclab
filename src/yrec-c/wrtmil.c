/* wrtmil.f -- translated by f2c (version 20061008).
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
    integer npenv, nprtmod, nprtpt, npoint;
} ccout1_;

#define ccout1_1 ccout1_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

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
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

/* Table of constant values */

static integer c__1 = 1;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* WRTMIL */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int wrtmil_(doublereal *hcomp, doublereal *hd, doublereal *
	hl, doublereal *hp, doublereal *hr, doublereal *hs1, integer *m, 
	integer *model)
{
    /* Format strings */
    static char fmt_5[] = "(10x,\002MODEL\002,i5,\002  XENV =\002,1pd10.3"
	    ",\002  ZENV =\002,d10.3,\002  MASS(SOLAR UNITS) =\002,d10.3)";
    static char fmt_10[] = "(1x,i4,10(1pe11.3))";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;
    cllist cl__1;

    /* Builtin functions */
    double exp(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void),
	     f_clos(cllist *);

    /* Local variables */
    static doublereal d__;
    static integer i__;
    static doublereal p, r__, u, v, w, np1;
    static integer ibeg, iend;
    static doublereal smtot;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, fmt_5, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_10, 0 };


/* MHP 8/25 Milne output file is now opened in parmin,unused variables removed */
/*  FIND THE MILNE INVARIANTS U AND V, ALONG WITH THE INDEX N+1. */
/*  WRITE THEM OUT TO LOGICAL UNIT IMILNE. */
/*  HEADER */
    /* Parameter adjustments */
    --hs1;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;

    /* Function Body */
    smtot = exp(const1_1.cln * comp_1.stotal) / const_1.cmsun;
    io___2.ciunit = luout_1.imilne;
    s_wsfe(&io___2);
    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&comp_1.xenv, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&comp_1.zenv, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&smtot, (ftnlen)sizeof(doublereal));
    e_wsfe();
/*  CALCULATE FOR FIRST POINT(ALWAYS DONE) */
    d__ = exp(const1_1.cln * hd[1]);
    p = exp(const1_1.cln * hp[1]);
    r__ = exp(const1_1.cln * hr[1]);
/* Computing 3rd power */
    d__1 = r__;
    u = const1_1.c4pi * d__ * (d__1 * (d__1 * d__1)) / hs1[1];
    v = exp(const1_1.cln * const2_1.cgl) * hs1[1] * d__ / (p * r__);
    w = u * hs1[1] * (scrtch_1.sesum[0] + scrtch_1.seg[6]) / (hl[1] * 
	    const_1.clsun);
    np1 = 1. / scrtch_1.sdel[1];
    io___10.ciunit = luout_1.imilne;
    s_wsfe(&io___10);
    do_fio(&c__1, (char *)&c__1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&hs1[1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&r__, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&d__, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hcomp[16], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hl[1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&u, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&w, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&np1, (ftnlen)sizeof(doublereal));
    e_wsfe();
/*  PRINT OUT EVERY NPRTPT POINTS;LAST POINT ALWAYS PRINTED. */
    iend = 1;
    if (ccout1_1.nprtpt <= *m) {
	ibeg = max(2,ccout1_1.nprtpt);
	iend = *m - *m % ccout1_1.nprtpt;
	i__1 = iend;
	i__2 = ccout1_1.nprtpt;
	for (i__ = ibeg; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	    d__ = exp(const1_1.cln * hd[i__]);
	    p = exp(const1_1.cln * hp[i__]);
	    r__ = exp(const1_1.cln * hr[i__]);
/* Computing 3rd power */
	    d__1 = r__;
	    u = const1_1.c4pi * d__ * (d__1 * (d__1 * d__1)) / hs1[i__];
	    v = exp(const1_1.cln * const2_1.cgl) * hs1[i__] * d__ / (p * r__);
	    w = u * hs1[i__] * (scrtch_1.sesum[i__ - 1] + scrtch_1.seg[i__ * 
		    7 - 1]) / (hl[i__] * const_1.clsun);
	    np1 = 1. / scrtch_1.sdel[i__ * 3 - 2];
	    io___14.ciunit = luout_1.imilne;
	    s_wsfe(&io___14);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&hs1[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&r__, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&d__, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[i__ * 15 + 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&u, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&v, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&w, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&np1, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* L20: */
	}
    }
    if (iend < *m) {
/*  PRINT OUT LAST POINT IF NPRTPT DOESNT DIVIDE EVENLY INTO M. */
	d__ = exp(const1_1.cln * hd[*m]);
	p = exp(const1_1.cln * hp[*m]);
	r__ = exp(const1_1.cln * hr[*m]);
/* Computing 3rd power */
	d__1 = r__;
	u = const1_1.c4pi * d__ * (d__1 * (d__1 * d__1)) / hs1[*m];
	v = exp(const1_1.cln * const2_1.cgl) * hs1[*m] * d__ / (p * r__);
	w = u * hs1[*m] * (scrtch_1.sesum[*m - 1] + scrtch_1.seg[*m * 7 - 1]) 
		/ (hl[*m] * const_1.clsun);
	np1 = 1. / scrtch_1.sdel[*m * 3 - 2];
	io___15.ciunit = luout_1.imilne;
	s_wsfe(&io___15);
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hs1[*m], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&r__, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&p, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&d__, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hcomp[*m * 15 + 1], (ftnlen)sizeof(doublereal))
		;
	do_fio(&c__1, (char *)&hl[*m], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&u, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&w, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&np1, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    cl__1.cerr = 0;
    cl__1.cunit = luout_1.imilne;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* wrtmil_ */


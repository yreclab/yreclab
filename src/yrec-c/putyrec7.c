/* putyrec7.f -- translated by f2c (version 20061008).
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

/* Table of constant values */

static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* PUTYREC7 - Write out a stallar model in YREC7 format */

/* llp  4/16/03 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int putyrec7_(doublereal *bl, doublereal *cfenv, doublereal *
	cmixl, doublereal *dage, doublereal *ddage, doublereal *ftri, 
	doublereal *hcomp, doublereal *hd, doublereal *hl, doublereal *hp, 
	doublereal *hr, doublereal *hs, doublereal *hstot, doublereal *ht, 
	integer *iwrite, integer *jcore, integer *jenv, logical *lc, logical *
	lexcom, logical *lrot, integer *m, integer *model, doublereal *omega, 
	doublereal *ps, doublereal *rs, doublereal *smass, doublereal *teffl, 
	doublereal *tlumx, doublereal *tril, doublereal *trit, doublereal *ts)
{
    /* Format strings */
    static char fmt_10[] = "(\002NMOD \002,2i5,3f8.5,1x,f14.10,f13.9,f13.0)";
    static char fmt_20[] = "(\002NMOD \002,2i5,3f8.5,1x,f14.10,f13.9,1pe13.6)"
	    ;
    static char fmt_30[] = "(2(l1,1x),\002F F \002,2i4,f7.3)";
    static char fmt_40[] = "(\002TLUMX\002,5x,1p7e10.3)";
    static char fmt_50[] = "(\002ENV\002,i2,f7.5,4f8.5,1p3e12.5)";
    static char fmt_100[] = "(0pf13.10,f10.7,1pe14.7,0pf10.7,2f10.7,l1,2i6)";
    static char fmt_200[] = "(8(1pe9.3,1x))";
    static char fmt_220[] = "(4(1pe9.3,1x))";
    static char fmt_310[] = "(0p8f10.7)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double d_lg10(doublereal *);

    /* Local variables */
    static integer i__, j, k, i0, j1, n1, n2, ix, iz, ktest;
    static doublereal cccmax, omegal[5000];

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___2 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___13 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___16 = { 0, 0, 0, fmt_220, 0 };
    static cilist io___18 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_220, 0 };
    static cilist io___25 = { 0, 0, 0, fmt_310, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_310, 0 };


/*      * HP,HR,HS,HSTOT,HT,IWRITE,ISHORT,JCORE,JENV,LC,LEXCOM,LROT,M, */
/*      * MODEL,OMEGA,PS,RS,SMASS,TEFFL,TLUMX,TRIL,TRIT,TS,  ! KC 2025-05-31 */
/*      & ATM,EOS,HIK,LDIFY,LDIFZ,LDISK,LINSTB,LJDOT0,ALOK, */
/*      & LOVSTC,LOVSTE,LOVSTM,LPUREZ,LSEMIC,COMPMIX,PDISK,TDISK,WMAX)  ! KC 2025-05-31 */
/* First three lines above are YREC7 inputs */
/* Last two lines are MODEL2 add-ons */
/*     WRITE MODEL OUT IN ASCII FORMAT */
/*     CHARACTER*4 ATM, LOK, HIK, COMPMIX */
/* MHP 4/25 changed LOK name to make it unique, used elsewhere */
/*       CHARACTER*4 ATM,HIK,ALOK,COMPMIX */
/*       CHARACTER*6 EOS */
/* PUTYREC7 writes the model provided to it out to the LU IWRITE file. */
/* Any error messages go to LU ISHORT. */
/*  THE 6 HEADER RECORDS WRITTEN FIRST */
    /* Parameter adjustments */
    --ts;
    --trit;
    --tril;
    --tlumx;
    --rs;
    --ps;
    --omega;
    --lc;
    --ht;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;
    --cfenv;

    /* Function Body */
    if (*ddage >= 1e6) {
	io___1.ciunit = *iwrite;
	s_wsfe(&io___1);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	io___2.ciunit = *iwrite;
	s_wsfe(&io___2);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
/* write PHYSICS FLAGS- ROTATION,EXTENDED COMP,CENTRAL AND SURFACE CZ'S */
    io___3.ciunit = *iwrite;
    s_wsfe(&io___3);
    do_fio(&c__1, (char *)&(*lrot), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lexcom), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*jcore), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*cmixl), (ftnlen)sizeof(doublereal));
    e_wsfe();
/* write LUMINOSITIES */
/* If TLUMX are in solar units, convert to ergs.  Decide by */
/* comparing to 10**20.  If smaller, multiply by CLSUN. */
/* Computing MAX */
    d__1 = max(tlumx[1],tlumx[2]), d__1 = max(d__1,tlumx[3]), d__1 = max(d__1,
	    tlumx[4]), d__1 = max(d__1,tlumx[5]), d__2 = abs(tlumx[6]), d__1 =
	     max(d__1,d__2);
    cccmax = max(d__1,tlumx[7]);
    if (cccmax <= 1e20) {
	for (j = 1; j <= 7; ++j) {
	    tlumx[j] *= const_1.clsun;
	}
    }
    io___6.ciunit = *iwrite;
    s_wsfe(&io___6);
    for (j = 1; j <= 7; ++j) {
	do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
    }
    e_wsfe();
/* write ENVELOPE DATA */
    for (i__ = 1; i__ <= 3; ++i__) {
	i0 = i__;
	if (*ftri < 0.) {
	    i0 = -i__;
	}
	io___9.ciunit = *iwrite;
	s_wsfe(&io___9);
	do_fio(&c__1, (char *)&i0, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&trit[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tril[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ps[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ts[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rs[i__], (ftnlen)sizeof(doublereal));
	for (j = 1; j <= 3; ++j) {
	    do_fio(&c__1, (char *)&cfenv[i__ * 3 - 3 + j], (ftnlen)sizeof(
		    doublereal));
	}
	e_wsfe();
/* L60: */
    }
/* write HENYEY POINTS, one line per shell */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ix = (integer) (hcomp[i__ * 15 + 1] * 1e6 + .5);
	iz = (integer) (hcomp[i__ * 15 + 3] * 1e6 + .5);
	io___12.ciunit = *iwrite;
	s_wsfe(&io___12);
	do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&ix, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&iz, (ftnlen)sizeof(integer));
	e_wsfe();
/* L110: */
    }
/* WRITE OUT COMPOSITION ARRAY - CENTRAL AND SURFACE */
/* CONVECTION ZONES HAVE ONLY 1 COMPOSITION STORED PER ZONE */
/* IF STAR IS FULLY CONVECTIVE, WRITE OUT 1 COMP. */
    if (*jenv <= *jcore) {
	io___13.ciunit = *iwrite;
	s_wsfe(&io___13);
	for (i__ = 4; i__ <= 11; ++i__) {
	    do_fio(&c__1, (char *)&hcomp[i__ + *jcore * 15], (ftnlen)sizeof(
		    doublereal));
	}
	e_wsfe();
	io___14.ciunit = *iwrite;
	s_wsfe(&io___14);
	for (i__ = 4; i__ <= 11; ++i__) {
	    do_fio(&c__1, (char *)&hcomp[i__ + *jenv * 15], (ftnlen)sizeof(
		    doublereal));
	}
	e_wsfe();
    } else {
	i__1 = *jenv;
	for (j = *jcore; j <= i__1; ++j) {
	    io___15.ciunit = *iwrite;
	    s_wsfe(&io___15);
	    for (i__ = 4; i__ <= 11; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + j * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
/* L210: */
	}
    }
/* EXTENDED COMP - WRITE OUT 1 ABUND IF FULLY CONVECTIVE, */
/* OTHERWISE WRITE OUT 2 POINTS PER LINE. */
    if (*lexcom) {
	if (*jenv <= *jcore) {
	    io___16.ciunit = *iwrite;
	    s_wsfe(&io___16);
	    for (i__ = 12; i__ <= 15; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + *jenv * 15], (ftnlen)
			sizeof(doublereal));
	    }
	    e_wsfe();
	} else {
	    i__1 = *jenv - 1;
	    for (k = *jcore; k <= i__1; k += 2) {
		io___18.ciunit = *iwrite;
		s_wsfe(&io___18);
		i__2 = k + 1;
		for (j = k; j <= i__2; ++j) {
		    for (i__ = 12; i__ <= 15; ++i__) {
			do_fio(&c__1, (char *)&hcomp[i__ + j * 15], (ftnlen)
				sizeof(doublereal));
		    }
		}
		e_wsfe();
/* L230: */
	    }
/*   IF AN ODD NUMBER OF ABUNDANCES EXISTS, WRITE IN LAST VALUE */
	    ktest = *jenv - 1 - *jcore;
	    if (ktest % 2 != 0) {
		io___20.ciunit = *iwrite;
		s_wsfe(&io___20);
		for (i__ = 12; i__ <= 15; ++i__) {
		    do_fio(&c__1, (char *)&hcomp[i__ + k * 15], (ftnlen)
			    sizeof(doublereal));
		}
		e_wsfe();
	    }
	}
    }
/* WRITE OUT RUN OF OMEGA,STORED 8 ELEMENTS PER LINE */
/* (- THE LOG OF OMEGA IS STORED) */
    if (*lrot) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (omega[i__] <= 1e-59) {
		omega[i__] = 1e-59;
	    }
	    omegal[i__ - 1] = (d__1 = d_lg10(&omega[i__]), abs(d__1));
/* L300: */
	}
	n1 = *m / 8;
	n2 = *m - (n1 << 3);
	j1 = 1;
	i__1 = n1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    io___25.ciunit = *iwrite;
	    s_wsfe(&io___25);
	    i__2 = j1 + 7;
	    for (j = j1; j <= i__2; ++j) {
		do_fio(&c__1, (char *)&omegal[j - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	    j1 += 8;
/* L320: */
	}
	if (n2 > 0) {
	    io___26.ciunit = *iwrite;
	    s_wsfe(&io___26);
	    i__1 = j1 + n2 - 1;
	    for (j = j1; j <= i__1; ++j) {
		do_fio(&c__1, (char *)&omegal[j - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	}
    }
    return 0;
} /* putyrec7_ */


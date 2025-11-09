/* putmodel2.f -- translated by f2c (version 20061008).
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
/* PUTMMODEL2 - Write out a stallar model in MODEL2 format */

/* llp  4/16/03 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int putmodel2_(doublereal *bl, doublereal *cfenv, doublereal 
	*cmixl, doublereal *dage, doublereal *ddage, doublereal *ftri, 
	doublereal *hcomp, doublereal *hd, doublereal *hl, doublereal *hp, 
	doublereal *hr, doublereal *hs, doublereal *hstot, doublereal *ht, 
	integer *iwrite, integer *ishort, integer *jcore, integer *jenv, 
	logical *lc, logical *lexcom, logical *lrot, integer *m, integer *
	model, doublereal *omega, doublereal *ps, doublereal *rs, doublereal *
	smass, doublereal *teffl, doublereal *tlumx, doublereal *tril, 
	doublereal *trit, doublereal *ts, char *atm, char *eos, char *hik, 
	logical *ldify, logical *ldifz, logical *ldisk, logical *linstb, 
	logical *ljdot0, char *alok, logical *lovstc, logical *lovste, 
	logical *lovstm, logical *lpurez, logical *lsemic, char *compmix, 
	doublereal *pdisk, doublereal *tdisk, doublereal *wmax, ftnlen 
	atm_len, ftnlen eos_len, ftnlen hik_len, ftnlen alok_len, ftnlen 
	compmix_len)
{
    /* Format strings */
    static char fmt_7[] = "(\002*** YREC7 input file, flags, etc., have be"
	    "en \002,\002defaulted.  ***\002)";
    static char fmt_10[] = "(a5,2i8,5f16.11,1pe18.10,0p2f16.12)";
    static char fmt_11[] = "(a5,2i8,4f16.12,f16.10,1pe18.10,0p2f16.12)";
    static char fmt_12[] = "(a5,2i8,4f16.12,f16.9,1pe18.10,0p2f16.12)";
    static char fmt_13[] = "(a5,2i8,4f16.12,f16.8,1pe18.10,0p2f16.12)";
    static char fmt_30[] = "(2i8,f16.10,1x,a6,1x,3(a4,1x),l1,1x,a4,1x,11(l1,"
	    "1x),3(1pe18.10))";
    static char fmt_40[] = "(\002TLUMX\002,5x,1p7e17.9)";
    static char fmt_50[] = "(\002ENV\002,i2,5f16.12,1p3e20.12)";
    static char fmt_55[] = "(a6,2a18,a24,3a18,a24,a2,3a12,12a16)";
    static char fmt_60[] = "(i6,0p2f18.14,1pe24.16,0p3f18.14,1pe24.16,1x,l1,"
	    "3(0pf12.9),12(0pe16.8))";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_cmp(char *, char *, ftnlen, ftnlen), s_wsfe(cilist *), e_wsfe(
	    void), do_fio(integer *, char *, ftnlen), s_wsle(cilist *), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, i0;
    static doublereal cccmax;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, fmt_7, 0 };
    static cilist io___2 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_11, 0 };
    static cilist io___4 = { 0, 0, 0, fmt_12, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_13, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___13 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_55, 0 };
    static cilist io___15 = { 0, 0, 0, 0, 0 };
    static cilist io___16 = { 0, 0, 0, fmt_60, 0 };


/* First three lines above are YREC7 inputs */
/* Last two lines are MODEL2 add-ons */
/*  Write output model in MODEL2 format */
/*     CHARACTER*4 ATM, LOK, HIK, COMPMIX */
/* MHP 4/25 changed LOK name to make it unique, used elsewhere */
/* PUTYMODEL2 writes the model provided to it out to the LU IWRITE file. */
/* Any error messages go to LU ISHORT. */
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
    if (s_cmp(atm, " ? ", (ftnlen)4, (ftnlen)3) == 0) {
	io___1.ciunit = *ishort;
	s_wsfe(&io___1);
	e_wsfe();
    }
/* write header records */
    if (*dage < 1e3) {
	io___2.ciunit = *iwrite;
	s_wsfe(&io___2);
	do_fio(&c__1, "MOD2 ", (ftnlen)5);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else if (*dage < 1e4) {
	io___3.ciunit = *iwrite;
	s_wsfe(&io___3);
	do_fio(&c__1, "MOD2 ", (ftnlen)5);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else if (*dage < 1e5) {
	io___4.ciunit = *iwrite;
	s_wsfe(&io___4);
	do_fio(&c__1, "MOD2 ", (ftnlen)5);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	io___5.ciunit = *iwrite;
	s_wsfe(&io___5);
	do_fio(&c__1, "MOD2 ", (ftnlen)5);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
/* write physics flags: */
    io___6.ciunit = *iwrite;
    s_wsfe(&io___6);
    do_fio(&c__1, (char *)&(*jcore), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*cmixl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, eos, (ftnlen)6);
    do_fio(&c__1, atm, (ftnlen)4);
    do_fio(&c__1, alok, (ftnlen)4);
    do_fio(&c__1, hik, (ftnlen)4);
    do_fio(&c__1, (char *)&(*lpurez), (ftnlen)sizeof(logical));
    do_fio(&c__1, compmix, (ftnlen)4);
    do_fio(&c__1, (char *)&(*lexcom), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*ldify), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*ldifz), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lsemic), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lovstc), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lovste), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lovstm), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lrot), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*linstb), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*ljdot0), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*ldisk), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*tdisk), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pdisk), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*wmax), (ftnlen)sizeof(doublereal));
    e_wsfe();
/* write luminosities */
/* If TLUMX are in solar units, convert to ergs.  Decide by */
/* comparing to 10**20, if smaller, multiply by CLSUN */
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
    io___9.ciunit = *iwrite;
    s_wsfe(&io___9);
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
	io___12.ciunit = *iwrite;
	s_wsfe(&io___12);
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
    }
/* write column headings for all per shell information */
    io___13.ciunit = *iwrite;
    s_wsle(&io___13);
    e_wsle();
    io___14.ciunit = *iwrite;
    s_wsfe(&io___14);
    do_fio(&c__1, " SHELL", (ftnlen)6);
    do_fio(&c__1, "MASS       ", (ftnlen)11);
    do_fio(&c__1, "RADIUS      ", (ftnlen)12);
    do_fio(&c__1, "LUMINOSITY       ", (ftnlen)17);
    do_fio(&c__1, "PRESSURE     ", (ftnlen)13);
    do_fio(&c__1, "TEMPERATURE   ", (ftnlen)14);
    do_fio(&c__1, "DENSITY     ", (ftnlen)12);
    do_fio(&c__1, "OMEGA         ", (ftnlen)14);
    do_fio(&c__1, " C", (ftnlen)2);
    do_fio(&c__1, "  H1     ", (ftnlen)9);
    do_fio(&c__1, "   He4    ", (ftnlen)10);
    do_fio(&c__1, "   METALS  ", (ftnlen)11);
    do_fio(&c__1, "He3      ", (ftnlen)9);
    do_fio(&c__1, "C12      ", (ftnlen)9);
    do_fio(&c__1, "C13      ", (ftnlen)9);
    do_fio(&c__1, "N14      ", (ftnlen)9);
    do_fio(&c__1, "N15      ", (ftnlen)9);
    do_fio(&c__1, "O16      ", (ftnlen)9);
    do_fio(&c__1, "O17      ", (ftnlen)9);
    do_fio(&c__1, "O18      ", (ftnlen)9);
    do_fio(&c__1, "H2       ", (ftnlen)9);
    do_fio(&c__1, "Li6      ", (ftnlen)9);
    do_fio(&c__1, "Li7      ", (ftnlen)9);
    do_fio(&c__1, "Be9      ", (ftnlen)9);
    e_wsfe();
    io___15.ciunit = *iwrite;
    s_wsle(&io___15);
    e_wsle();
/* LLP 4/16/03  Output OMEGA rather Log10(OMEGA), a change from YREC7 files */
/* write per shell information, one line per shell */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___16.ciunit = *iwrite;
	s_wsfe(&io___16);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(logical));
	for (j = 1; j <= 15; ++j) {
	    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (ftnlen)sizeof(
		    doublereal));
	}
	e_wsfe();
    }
    return 0;
} /* putmodel2_ */


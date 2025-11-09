/* pdist.f -- translated by f2c (version 20061008).
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
    doublereal dage;
} theage_;

#define theage_1 theage_

struct {
    doublereal poa, pob, poc, pomax;
    logical lpout;
} po_;

#define po_1 po_

struct {
    doublereal xmsol;
    logical lpulse;
    integer ipver;
} pulse_;

#define pulse_1 pulse_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk;
    logical lzramp;
} zramp_;

#define zramp_1 zramp_

struct {
    integer ifirst, irun, istand, ifermi, iopmod, iopenv, iopatm, idyn, 
	    illdat, isnu, iscomp, ikur;
} lunum_;

#define lunum_1 lunum_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* PDIST */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* calculates the distance the star has travelled in the HR diagram */
/* if far enough, output pulsation model */
/* MHP 8/25 passed file names directly and removed common block with file names */
/* Subroutine */ int pdist_(doublereal *pol1, doublereal *pot1, doublereal *
	poa1, doublereal *polen, doublereal *bl, doublereal *teffl, integer *
	modeln, char *fpatm, char *fpenv, char *fpmod, ftnlen fpatm_len, 
	ftnlen fpenv_len, ftnlen fpmod_len)
{
    /* Format strings */
    static char fmt_276[] = "(5x,\002 LEN SQ=\002,1pe10.3,\002  D L=\002,1pe"
	    "10.3,\002  D Te=\002,1pe10.3,\002  D AGE=\002,1pe10.3)";

    /* System generated locals */
    address a__1[2];
    integer i__1[2];
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer i_indx(char *, char *, ftnlen, ftnlen), s_wsfi(icilist *), do_fio(
	    integer *, char *, ftnlen), e_wsfi(void);
    /* Subroutine */ void s_cat(char *, char **, integer *, integer *, ftnlen);
    integer f_open(olist *), f_clos(cllist *), s_wsfe(cilist *), e_wsfe(void);

    /* Local variables */
    static doublereal tm1, tm2, tm3, tmp1, tmp2, tmp3;
    static char cout[256], ctemp[256];
    static integer ioccol;

    /* Fortran I/O blocks */
    static icilist io___9 = { 0, ctemp, 0, "(I2.2,'_',I4.4)", 256, 1 };
    static icilist io___11 = { 0, ctemp, 0, "(I2.2,'_',I5.5)", 256, 1 };
    static icilist io___12 = { 0, ctemp, 0, "(I2.2,'_',I4.4)", 256, 1 };
    static icilist io___13 = { 0, ctemp, 0, "(I2.2,'_',I5.5)", 256, 1 };
    static icilist io___14 = { 0, ctemp, 0, "(I2.2,'_',I4.4)", 256, 1 };
    static icilist io___15 = { 0, ctemp, 0, "(I2.2,'_',I5.5)", 256, 1 };
    static cilist io___16 = { 0, 0, 0, fmt_276, 0 };
    static cilist io___17 = { 0, 0, 0, fmt_276, 0 };


/* Removed variables not used in the routine */
/* MHP 10/02 added proper dimensions to last 2 variables */
/* MHP 8/25 Removed character file names from common block */
/* MHP 8/25 Removed common block with file names */
/*      COMMON/LUFNM/ FLAST, FFIRST, FRUN, FSTAND, FFERMI, */
/*     1    FDEBUG, FTRACK, FSHORT, FMILNE, FMODPT, */
/*     2    FSTOR, FPMOD, FPENV, FPATM, FDYN, */
/*     3    FLLDAT, FSNU, FSCOMP, FKUR, */
/*     4    FMHD1, FMHD2, FMHD3, FMHD4, FMHD5, FMHD6, FMHD7, FMHD8 */
    tm1 = *bl - *pol1;
    tm2 = *teffl - *pot1;
    tm3 = theage_1.dage - *poa1;
    tmp1 = po_1.poa * tm1 * po_1.poa * tm1;
    tmp2 = po_1.pob * tm2 * po_1.pob * tm2;
    tmp3 = po_1.poc * tm3 * po_1.poc * tm3;
    *polen = *polen + tmp1 + tmp2 + tmp3;
    *pol1 = *bl;
    *pot1 = *teffl;
    *poa1 = theage_1.dage;
    if (*polen >= po_1.pomax) {
	pulse_1.lpulse = TRUE_;
	*polen = 0.;
	ioccol = i_indx(fpmod, " ", (ftnlen)256, (ftnlen)1) - 1;
	if (*modeln < 10000) {
	    s_wsfi(&io___9);
	    do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*modeln), (ftnlen)sizeof(integer));
	    e_wsfi();
/* Writing concatenation */
	    i__1[0] = ioccol, a__1[0] = fpmod;
	    i__1[1] = 7, a__1[1] = ctemp;
	    s_cat(cout, a__1, i__1, &c__2, (ftnlen)256);
	} else {
	    s_wsfi(&io___11);
	    do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*modeln), (ftnlen)sizeof(integer));
	    e_wsfi();
/* Writing concatenation */
	    i__1[0] = ioccol, a__1[0] = fpmod;
	    i__1[1] = 8, a__1[1] = ctemp;
	    s_cat(cout, a__1, i__1, &c__2, (ftnlen)256);
	}
	o__1.oerr = 0;
	o__1.ounit = lunum_1.iopmod;
	o__1.ofnmlen = 256;
	o__1.ofnm = cout;
	o__1.orl = 0;
	o__1.osta = "NEW";
	o__1.oacc = 0;
	o__1.ofm = "FORMATTED";
	o__1.oblnk = 0;
	f_open(&o__1);
	ioccol = i_indx(fpenv, " ", (ftnlen)256, (ftnlen)1) - 1;
	if (*modeln < 10000) {
	    s_wsfi(&io___12);
	    do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*modeln), (ftnlen)sizeof(integer));
	    e_wsfi();
/* Writing concatenation */
	    i__1[0] = ioccol, a__1[0] = fpenv;
	    i__1[1] = 7, a__1[1] = ctemp;
	    s_cat(cout, a__1, i__1, &c__2, (ftnlen)256);
	} else {
	    s_wsfi(&io___13);
	    do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*modeln), (ftnlen)sizeof(integer));
	    e_wsfi();
/* Writing concatenation */
	    i__1[0] = ioccol, a__1[0] = fpenv;
	    i__1[1] = 8, a__1[1] = ctemp;
	    s_cat(cout, a__1, i__1, &c__2, (ftnlen)256);
	}
	o__1.oerr = 0;
	o__1.ounit = lunum_1.iopenv;
	o__1.ofnmlen = 256;
	o__1.ofnm = cout;
	o__1.orl = 0;
	o__1.osta = "NEW";
	o__1.oacc = 0;
	o__1.ofm = "FORMATTED";
	o__1.oblnk = 0;
	f_open(&o__1);
	ioccol = i_indx(fpatm, " ", (ftnlen)256, (ftnlen)1) - 1;
	if (*modeln < 10000) {
	    s_wsfi(&io___14);
	    do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*modeln), (ftnlen)sizeof(integer));
	    e_wsfi();
/* Writing concatenation */
	    i__1[0] = ioccol, a__1[0] = fpatm;
	    i__1[1] = 7, a__1[1] = ctemp;
	    s_cat(cout, a__1, i__1, &c__2, (ftnlen)256);
	} else {
	    s_wsfi(&io___15);
	    do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*modeln), (ftnlen)sizeof(integer));
	    e_wsfi();
/* Writing concatenation */
	    i__1[0] = ioccol, a__1[0] = fpatm;
	    i__1[1] = 8, a__1[1] = ctemp;
	    s_cat(cout, a__1, i__1, &c__2, (ftnlen)256);
	}
	o__1.oerr = 0;
	o__1.ounit = lunum_1.iopatm;
	o__1.ofnmlen = 256;
	o__1.ofnm = cout;
	o__1.orl = 0;
	o__1.osta = "NEW";
	o__1.oacc = 0;
	o__1.ofm = "FORMATTED";
	o__1.oblnk = 0;
	f_open(&o__1);
    } else {
	cl__1.cerr = 0;
	cl__1.cunit = lunum_1.iopmod;
	cl__1.csta = 0;
	f_clos(&cl__1);
	cl__1.cerr = 0;
	cl__1.cunit = lunum_1.iopenv;
	cl__1.csta = 0;
	f_clos(&cl__1);
	cl__1.cerr = 0;
	cl__1.cunit = lunum_1.iopatm;
	cl__1.csta = 0;
	f_clos(&cl__1);
	pulse_1.lpulse = FALSE_;
    }
    io___16.ciunit = luout_1.iowr;
    s_wsfe(&io___16);
    do_fio(&c__1, (char *)&(*polen), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tm1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tm2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tm3, (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___17.ciunit = luout_1.ishort;
    s_wsfe(&io___17);
    do_fio(&c__1, (char *)&(*polen), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tmp1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tmp2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tmp3, (ftnlen)sizeof(doublereal));
    e_wsfe();
    return 0;
} /* pdist_ */


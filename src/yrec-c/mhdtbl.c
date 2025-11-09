/* mhdtbl.f -- translated by f2c (version 20061008).
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
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MHDTBL */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mhdtbl_(char *fmhd1, char *fmhd2, char *fmhd3, char *
	fmhd4, char *fmhd5, char *fmhd6, char *fmhd7, char *fmhd8, ftnlen 
	fmhd1_len, ftnlen fmhd2_len, ftnlen fmhd3_len, ftnlen fmhd4_len, 
	ftnlen fmhd5_len, ftnlen fmhd6_len, ftnlen fmhd7_len, ftnlen 
	fmhd8_len)
{
    /* System generated locals */
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), f_clos(cllist *);

    /* Local variables */
    extern /* Subroutine */ int mhdst_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *);

/*     FOR SET TABLES */
/* MHP 8/25 Removed un-used file names and file names from common blocks */
/*      COMMON/LUFNM/ FLAST, FFIRST, FRUN, FSTAND, FFERMI, */
/*     1    FDEBUG, FTRACK, FSHORT, FMILNE, FMODPT, */
/*     2    FSTOR, FPMOD, FPENV, FPATM, FDYN, */
/*     3    FLLDAT, FSNU, FSCOMP, FKUR, */
/*     4    FMHD1, FMHD2, FMHD3, FMHD4, FMHD5, FMHD6, FMHD7, FMHD8 */
/*       DATA UMOD /2.302585092994046 D0/ */
/*     SET MHD EQUATION OF STATE */
/*     USES 3 ZAMS-TYPE TABLES AND OPTIONALLY 5 CENTER-TYPE TABLES. */

    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd1;
    o__1.ofnmlen = 256;
    o__1.ofnm = fmhd1;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd2;
    o__1.ofnmlen = 256;
    o__1.ofnm = fmhd2;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd3;
    o__1.ofnmlen = 256;
    o__1.ofnm = fmhd3;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd4;
    o__1.ofnmlen = 256;
    o__1.ofnm = fmhd4;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd5;
    o__1.ofnmlen = 256;
    o__1.ofnm = fmhd5;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd6;
    o__1.ofnmlen = 256;
    o__1.ofnm = fmhd6;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd7;
    o__1.ofnmlen = 256;
    o__1.ofnm = fmhd7;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd8;
    o__1.ofnmlen = 256;
    o__1.ofnm = fmhd8;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    mhdst_(&mhd_1.iomhd1, &mhd_1.iomhd2, &mhd_1.iomhd3, &mhd_1.iomhd4, &
	    mhd_1.iomhd5, &mhd_1.iomhd6, &mhd_1.iomhd7, &mhd_1.iomhd8);
/*     END MHD TABLE SETTING */
    cl__1.cerr = 0;
    cl__1.cunit = mhd_1.iomhd1;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = mhd_1.iomhd2;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = mhd_1.iomhd3;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = mhd_1.iomhd4;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = mhd_1.iomhd5;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = mhd_1.iomhd6;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = mhd_1.iomhd7;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = mhd_1.iomhd8;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* mhdtbl_ */


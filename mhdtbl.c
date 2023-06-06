/* mhdtbl.f -- translated by f2c (version 20100827).
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
    char flast[256], ffirst[256], frun[256], fstand[256], ffermi[256], fdebug[
	    256], ftrack[256], fshort[256], fmilne[256], fmodpt[256], fstor[
	    256], fpmod[256], fpenv[256], fpatm[256], fdyn[256], flldat[256], 
	    fsnu[256], fscomp[256], fkur[256], fmhd1[256], fmhd2[256], fmhd3[
	    256], fmhd4[256], fmhd5[256], fmhd6[256], fmhd7[256], fmhd8[256];
} lufnm_;

#define lufnm_1 lufnm_

struct {
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
} ccout2_;

#define ccout2_1 ccout2_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MHDTBL */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mhdtbl_(void)
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
/*     SET MHD EQUATION OF STATE */
/*     USES 3 ZAMS-TYPE TABLES AND OPTIONALLY 5 CENTER-TYPE TABLES. */

    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd1;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fmhd1;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd2;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fmhd2;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd3;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fmhd3;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd4;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fmhd4;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd5;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fmhd5;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd6;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fmhd6;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd7;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fmhd7;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = mhd_1.iomhd8;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fmhd8;
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


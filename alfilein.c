/* alfilein.f -- translated by f2c (version 20100827).
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
    doublereal teffls[250], gls[25], fehs[25], alphas[25], pls[6250]	/* 
	    was [250][25] */, p100ls[6250]	/* was [250][25] */, t100ls[
	    6250]	/* was [250][25] */;
    logical loldnextgen;
    integer nteff, ngl, nfeh, nalpha;
} alatm01_;

#define alatm01_1 alatm01_

struct {
    doublereal alatm_feh__, alatm_alpha__;
    logical laltptau100;
    integer ioatma;
} alatm03_;

#define alatm03_1 alatm03_

struct {
    doublereal dummy1, dummy2;
    char fallard[256];
    doublereal dummy3, dummy4xternalsort_shell__;
} alatm04_;

#define alatm04_1 alatm04_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;
static integer c__5 = 5;

/* 	Subroutine ALFILEIN */
/* PURPOSE */
/* To read Allard atmosphere information files into the appropriate input arrays */
/* and calculate associated auxilliary information. These files contain the */
/* desired properties of stellar and substellar atmospheres from atmospheric */
/* tables developed by France Allard, et al. These properties include Log(P) */
/* at Teff and GL, as well as Log(P) and Log(T) at Tau = 100 for this Teff and */
/* GL. Currently supported input formats include the old Allard, et al, circa */
/* 1999 NextGen format, to which we are adding the newer 2007 NextGen format. */
/* As other formats become available, weanticipate being able to handle those also. */
/* Input files may be in Old NextGen file format or in the new Allard Atmosphere */
/* file format. This format, is of a conceptually different style from the old. */
/* The data part of the new file format has one record for each Teff, GL, FE/h, */
/* Alpha. The rest of that record contains the associated PL @ T=Teff, */
/* PL @ Tau=100 and TL @ Tau100. In other words the new format has one data record */
/* for each item in the table. The old format had one record for each GL in the */
/* table. This new format is more flexible in supporting future needs. */
/* The contents of these files are put into the arrays and elements used by the */
/* Allard Atmosphere table lookup routine, ALSURFP. In addition, we fill any vacant */
/* entries in the table with -999.0. A value of -999. in the table identifies the */
/* entry as "invalid." In addition, key auxililiary arrays, as described below, are */
/* created. */
/* Subroutine */ int alfilein_(void)
{
    /* Format strings */
    static char fmt_901[] = "(a)";
    static char fmt_905[] = "(5f7.2/)";
    static char fmt_907[] = "(10(1p5e16.8,/),1p4e16.8,/)";
    static char fmt_909[] = "(1p5e16.8)";
    static char fmt_911[] = "(i2,x,a)";
    static char fmt_912[] = "(2a)";
    static char fmt_915[] = "(f6.0,3f6.2)";
    static char fmt_920[] = "(f6.0,3f6.2,1p4d16.8)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;
    olist o__1;
    cllist cl__1;
    alist al__1;

    /* Builtin functions */
    integer f_open(olist *), s_wsle(cilist *), e_wsle(void), do_lio(integer *,
	     integer *, char *, ftnlen), s_rsfe(cilist *), do_fio(integer *, 
	    char *, ftnlen), e_rsfe(void), f_rew(alist *), s_cmp(char *, char 
	    *, ftnlen, ftnlen), f_clos(cllist *), s_wsfe(cilist *), e_wsfe(
	    void), s_rsle(cilist *), e_rsle(void);
    double d_lg10(doublereal *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j;
    extern /* Subroutine */ int altabinit_(void);
    static integer i1, j1;
    static doublereal gl, pl, t100;
    extern /* Subroutine */ int sort_shell__(integer *, doublereal *);
    static doublereal feh;
    static logical latmtptau100;
    static doublereal p100l, teff;
    static integer nhdr;
    static doublereal alpha;
    static char inrec[35];
    static doublereal teffs[250];
    static char inrec2[256];
    static integer irecno;

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 6, 0, 0, 0 };
    static cilist io___4 = { 0, 6, 0, 0, 0 };
    static cilist io___5 = { 0, 6, 0, 0, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_901, 0 };
    static cilist io___8 = { 0, 0, 0, 0, 0 };
    static cilist io___9 = { 0, 0, 0, 0, 0 };
    static cilist io___10 = { 0, 6, 0, 0, 0 };
    static cilist io___11 = { 0, 6, 0, 0, 0 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 6, 0, 0, 0 };
    static cilist io___15 = { 0, 6, 0, 0, 0 };
    static cilist io___16 = { 0, 0, 0, 0, 0 };
    static cilist io___17 = { 0, 0, 0, 0, 0 };
    static cilist io___18 = { 0, 0, 0, fmt_905, 0 };
    static cilist io___19 = { 0, 0, 0, fmt_907, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_909, 0 };
    static cilist io___21 = { 0, 0, 0, fmt_911, 0 };
    static cilist io___24 = { 0, 0, 0, fmt_912, 0 };
    static cilist io___25 = { 0, 0, 0, 0, 0 };
    static cilist io___27 = { 1, 0, 1, fmt_915, 0 };
    static cilist io___33 = { 1, 0, 1, fmt_915, 0 };
    static cilist io___34 = { 0, 6, 0, 0, 0 };
    static cilist io___35 = { 0, 6, 0, 0, 0 };
    static cilist io___36 = { 0, 6, 0, 0, 0 };
    static cilist io___37 = { 0, 0, 0, 0, 0 };
    static cilist io___38 = { 1, 0, 1, fmt_920, 0 };
    static cilist io___43 = { 0, 6, 0, 0, 0 };
    static cilist io___44 = { 0, 6, 0, 0, 0 };
    static cilist io___46 = { 0, 6, 0, 0, 0 };
    static cilist io___47 = { 0, 6, 0, 0, 0 };
    static cilist io___48 = { 0, 6, 0, 0, 0 };
    static cilist io___49 = { 0, 6, 0, 0, 0 };
    static cilist io___50 = { 0, 6, 0, 0, 0 };
    static cilist io___51 = { 0, 6, 0, 0, 0 };
    static cilist io___52 = { 0, 6, 0, 0, 0 };
    static cilist io___53 = { 0, 6, 0, 0, 0 };
    static cilist io___54 = { 0, 6, 0, 0, 0 };
    static cilist io___55 = { 0, 6, 0, 0, 0 };
    static cilist io___56 = { 0, 6, 0, 0, 0 };
    static cilist io___57 = { 0, 0, 0, 0, 0 };
    static cilist io___58 = { 0, 0, 0, 0, 0 };
    static cilist io___59 = { 0, 0, 0, 0, 0 };
    static cilist io___60 = { 0, 0, 0, 0, 0 };



/* Parameters NTA and NGA are respectively the maximum expected numbers */
/* of Teff's and GL's we expect to encounter, even in future tables */
/* The maximum nuber of Teff's in the current table is nTeff, and the */
/* associated max number of GL's is nGL. */
/* Shared: ALFILEIN, ALTABINIT and ALSURFP */
/* Shared: ALFILEIN, */
/* ALSURFP and PARMIN */
/* set output arrays to invalid values */
    for (i__ = 1; i__ <= 250; ++i__) {
	alatm01_1.teffls[i__ - 1] = -999.;
	for (j = 1; j <= 25; ++j) {
	    alatm01_1.gls[j - 1] = -999.;
	    alatm01_1.pls[i__ + j * 250 - 251] = -999.;
	    alatm01_1.p100ls[i__ + j * 250 - 251] = -999.;
	    alatm01_1.t100ls[i__ + j * 250 - 251] = -999.;
	}
    }
/* the input file name is in FALLARD and its unit number is IOATMA */
    o__1.oerr = 1;
    o__1.ounit = alatm03_1.ioatma;
    o__1.ofnmlen = 256;
    o__1.ofnm = alatm04_1.fallard;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    i__1 = f_open(&o__1);
    if (i__1 != 0) {
	goto L899;
    }
    goto L900;
L899:
    s_wsle(&io___3);
    e_wsle();
    s_wsle(&io___4);
    do_lio(&c__9, &c__1, "ALFILEIN: Allard File OPEN Failure", (ftnlen)34);
    e_wsle();
    s_wsle(&io___5);
    do_lio(&c__9, &c__1, "     Unit-Number, FIle-Name are: ", (ftnlen)33);
    do_lio(&c__3, &c__1, (char *)&alatm03_1.ioatma, (ftnlen)sizeof(integer));
    do_lio(&c__9, &c__1, alatm04_1.fallard, (ftnlen)256);
    e_wsle();
    goto L9999;
/* Error exit */
L900:
/* Decide what kind of input file */
    io___6.ciunit = alatm03_1.ioatma;
    s_rsfe(&io___6);
    do_fio(&c__1, inrec, (ftnlen)35);
    e_rsfe();
    al__1.aerr = 0;
    al__1.aunit = alatm03_1.ioatma;
    f_rew(&al__1);
    if (s_cmp(inrec + 3, "3.50", (ftnlen)4, (ftnlen)4) == 0) {
	goto L100;
    }
/* Old NextGen file type */
    if (s_cmp(inrec + 3, "ALLARD", (ftnlen)6, (ftnlen)6) == 0) {
	goto L200;
    }
/* If we get here, the input file is invalid */
/* Allard file type */
    io___8.ciunit = luout_1.ishort;
    s_wsle(&io___8);
    do_lio(&c__9, &c__1, "*** Invalid Allard Atmosphere input file ***", (
	    ftnlen)44);
    e_wsle();
    io___9.ciunit = luout_1.ishort;
    s_wsle(&io___9);
    do_lio(&c__9, &c__1, "First record was '", (ftnlen)18);
    do_lio(&c__9, &c__1, inrec, (ftnlen)35);
    do_lio(&c__9, &c__1, "'", (ftnlen)1);
    e_wsle();
    s_wsle(&io___10);
    do_lio(&c__9, &c__1, "*** Invalid Allard Atmosphere input file ***", (
	    ftnlen)44);
    e_wsle();
    s_wsle(&io___11);
    do_lio(&c__9, &c__1, "First record was '", (ftnlen)18);
    do_lio(&c__9, &c__1, inrec, (ftnlen)35);
    do_lio(&c__9, &c__1, "'", (ftnlen)1);
    e_wsle();
    goto L9999;
/* Process old-stype nextgen input file. */
/* The error exit */
L100:
    alatm01_1.loldnextgen = TRUE_;
    io___12.ciunit = luout_1.ishort;
    s_wsle(&io___12);
    do_lio(&c__9, &c__1, "ALFileIn: File Description: 1999 NEXTGEN", (ftnlen)
	    40);
    do_lio(&c__9, &c__1, " (Old NEXTGEN)", (ftnlen)14);
    e_wsle();
/* Ensure that we are not requesting PL,TL at Tau-100. These are not */
/* present in the old Nextgen 1 files. If requested, fail */
    if (latmtptau100) {
	s_wsle(&io___14);
	e_wsle();
	s_wsle(&io___15);
	do_lio(&c__9, &c__1, "ALFileIN: Invalid old Allard input file ", (
		ftnlen)40);
	do_lio(&c__9, &c__1, "for requested PT,TL at Tau=100", (ftnlen)30);
	e_wsle();
	io___16.ciunit = luout_1.ishort;
	s_wsle(&io___16);
	e_wsle();
	io___17.ciunit = luout_1.ishort;
	s_wsle(&io___17);
	do_lio(&c__9, &c__1, "ALFileIN: Invalid old Allard input file ", (
		ftnlen)40);
	do_lio(&c__9, &c__1, "for requested PT,TL at Tau=100", (ftnlen)30);
	e_wsle();
	goto L9999;
/* The ERROR EXIT */
    }
/* READ RANGE OF GRAVITIES */
    alatm01_1.nteff = 54;
    alatm01_1.ngl = 5;
    io___18.ciunit = alatm03_1.ioatma;
    s_rsfe(&io___18);
    i__1 = alatm01_1.ngl;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&alatm01_1.gls[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsfe();
/* 	read(ioatma,*) */
/* READ RANGE OF TEMPERATURES */
    io___19.ciunit = alatm03_1.ioatma;
    s_rsfe(&io___19);
    i__1 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&alatm01_1.teffls[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsfe();
/* 	read(ioatma,*) */
    io___20.ciunit = alatm03_1.ioatma;
    s_rsfe(&io___20);
    i__1 = alatm01_1.nteff;
    for (j = 1; j <= i__1; ++j) {
	i__2 = alatm01_1.ngl;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    do_fio(&c__1, (char *)&alatm01_1.pls[j + i__ * 250 - 251], (
		    ftnlen)sizeof(doublereal));
	}
    }
    e_rsfe();
    cl__1.cerr = 0;
    cl__1.cunit = alatm03_1.ioatma;
    cl__1.csta = 0;
    f_clos(&cl__1);
    goto L500;
/* Old Nextgen input file has been read an put into the proper arrays */
/* Process new-style Allard Atmosphere file */
/* NORMAL EXIT */
L200:
    alatm01_1.loldnextgen = FALSE_;
    io___21.ciunit = alatm03_1.ioatma;
    s_rsfe(&io___21);
    do_fio(&c__1, (char *)&nhdr, (ftnlen)sizeof(integer));
    do_fio(&c__1, inrec2, (ftnlen)256);
    e_rsfe();
/* nhdr is number of header recoreds to skip over */
    io___24.ciunit = luout_1.ishort;
    s_wsfe(&io___24);
    do_fio(&c__1, "ALFilein: New Allard Atm: File Description: ", (ftnlen)44);
    do_fio(&c__1, inrec2, (ftnlen)47);
    e_wsfe();
/* Skip over rest of header, if any */
    if (nhdr > 1) {
	i__2 = nhdr;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    io___25.ciunit = alatm03_1.ioatma;
	    s_rsle(&io___25);
	    e_rsle();
	}
    }
    alatm01_1.ngl = 0;
    alatm01_1.nteff = 0;
    alatm01_1.nfeh = 0;
    alatm01_1.nalpha = 0;
    irecno = 0;
/* First we read the file to count the # of Teff,GL,Fe/H and Alpha's */
L299:
    io___27.ciunit = alatm03_1.ioatma;
    i__2 = s_rsfe(&io___27);
    if (i__2 != 0) {
	goto L100001;
    }
    i__2 = do_fio(&c__1, (char *)&teff, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100001;
    }
    i__2 = do_fio(&c__1, (char *)&gl, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100001;
    }
    i__2 = do_fio(&c__1, (char *)&feh, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100001;
    }
    i__2 = do_fio(&c__1, (char *)&alpha, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100001;
    }
    i__2 = e_rsfe();
L100001:
    if (i__2 < 0) {
	goto L400;
    }
    if (i__2 > 0) {
	goto L399;
    }
/* Process first record(s) */
    ++irecno;
/* If the record does not have the correct FeH and Alpha, we skip it */
    if ((d__1 = feh - alatm03_1.alatm_feh__, abs(d__1)) > 1e-5 || (d__2 = 
	    alpha - alatm03_1.alatm_alpha__, abs(d__2)) > 0.) {
	goto L299;
/* On to next record. Stay in this part until we get an acceptable record */
    }
    alatm01_1.nteff = 1;
/* Initialize counters and variables after reading first record */
    alatm01_1.ngl = 1;
    alatm01_1.nfeh = 1;
    alatm01_1.nalpha = 1;
    teffs[alatm01_1.nteff - 1] = teff;
    alatm01_1.gls[alatm01_1.ngl - 1] = gl;
    alatm01_1.fehs[alatm01_1.nfeh - 1] = feh;
    alatm01_1.alphas[alatm01_1.nalpha - 1] = alpha;
L300:
    io___33.ciunit = alatm03_1.ioatma;
    i__2 = s_rsfe(&io___33);
    if (i__2 != 0) {
	goto L100002;
    }
    i__2 = do_fio(&c__1, (char *)&teff, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100002;
    }
    i__2 = do_fio(&c__1, (char *)&gl, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100002;
    }
    i__2 = do_fio(&c__1, (char *)&feh, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100002;
    }
    i__2 = do_fio(&c__1, (char *)&alpha, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100002;
    }
    i__2 = e_rsfe();
L100002:
    if (i__2 < 0) {
	goto L400;
    }
    if (i__2 > 0) {
	goto L399;
    }
    ++irecno;
/* If the record does not have the correct FeH and Alpha, we skip it */
    if ((d__1 = feh - alatm03_1.alatm_feh__, abs(d__1)) > 1e-5 || (d__2 = 
	    alpha - alatm03_1.alatm_alpha__, abs(d__2)) > 0.) {
	goto L316;
/* On to next record */
    }
/*  Now check Teffs, increase counter if needed */
    i__2 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__2; ++i__) {
/* Skip out if any old Teff is a match */
	if ((d__1 = teff - teffs[i__ - 1], abs(d__1)) < 1e-6) {
	    goto L310;
	}
    }
    ++alatm01_1.nteff;
/* count the nextTeff's */
    teffs[alatm01_1.nteff - 1] = teff;
/* save the new Teff in array Teffs */
L310:
/* Now check GLs, increase counter if needed */
    i__2 = alatm01_1.ngl;
    for (i__ = 1; i__ <= i__2; ++i__) {
/* Skip out if any old GL is a match */
	if ((d__1 = gl - alatm01_1.gls[i__ - 1], abs(d__1)) < 1e-6) {
	    goto L312;
	}
    }
    ++alatm01_1.ngl;
/* count the next GL */
    alatm01_1.gls[alatm01_1.ngl - 1] = gl;
/* save the new GL in array GLs */
L312:
/* Now check FeHs, increase counter if needed */
    i__2 = alatm01_1.ngl;
    for (i__ = 1; i__ <= i__2; ++i__) {
/* Skip out if any old FeH is a match */
	if ((d__1 = feh - alatm01_1.fehs[i__ - 1], abs(d__1)) < 1e-6) {
	    goto L314;
	}
    }
    ++alatm01_1.nfeh;
/* count the next FeH */
    alatm01_1.fehs[alatm01_1.nfeh - 1] = feh;
/* save the new FeH in array FeHs */
L314:
/* Now check ALPHAs, increase counter if needed */
    i__2 = alatm01_1.ngl;
    for (i__ = 1; i__ <= i__2; ++i__) {
/* Skip out if any old ALPHA is a match */
	if ((d__1 = alpha - alatm01_1.alphas[i__ - 1], abs(d__1)) < 1e-6) {
	    goto L316;
	}
    }
    ++alatm01_1.nalpha;
/* count the next ALPHA */
    alatm01_1.alphas[alatm01_1.nalpha - 1] = alpha;
/* save the new ALPHA in array ALPHAs */
L316:
    goto L300;
/* File Read error exit */
/* go on to next record */
L399:
    s_wsle(&io___34);
    e_wsle();
    s_wsle(&io___35);
    do_lio(&c__9, &c__1, "AtTabInit Pass 1 File Error ", (ftnlen)28);
    e_wsle();
    s_wsle(&io___36);
    e_wsle();
    goto L9999;
L400:
/* 	write(*,*) 'nTeff,nGL,nFeH,nALPHA: ',nTeff,nGL,nFeH,nALPHA */
/*  Now we have unsorted Teff,GL,Fe/H and Alpha's. */
/* The next step is to sort them */
    sort_shell__(&alatm01_1.nteff, teffs);
    sort_shell__(&alatm01_1.ngl, alatm01_1.gls);
    sort_shell__(&alatm01_1.nfeh, alatm01_1.fehs);
    sort_shell__(&alatm01_1.nalpha, alatm01_1.alphas);
/* Now we can rewind the input file and start over for real */
    al__1.aerr = 0;
    al__1.aunit = alatm03_1.ioatma;
    f_rew(&al__1);
/*  Skip over header */
/* go back to the beginning of the file */
    i__2 = nhdr;
    for (i__ = 1; i__ <= i__2; ++i__) {
	io___37.ciunit = alatm03_1.ioatma;
	s_rsle(&io___37);
	e_rsle();
    }
L410:
    io___38.ciunit = alatm03_1.ioatma;
    i__2 = s_rsfe(&io___38);
    if (i__2 != 0) {
	goto L100003;
    }
    i__2 = do_fio(&c__1, (char *)&teff, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100003;
    }
    i__2 = do_fio(&c__1, (char *)&gl, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100003;
    }
    i__2 = do_fio(&c__1, (char *)&feh, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100003;
    }
    i__2 = do_fio(&c__1, (char *)&alpha, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100003;
    }
    i__2 = do_fio(&c__1, (char *)&pl, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100003;
    }
    i__2 = do_fio(&c__1, (char *)&p100l, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100003;
    }
    i__2 = do_fio(&c__1, (char *)&t100, (ftnlen)sizeof(doublereal));
    if (i__2 != 0) {
	goto L100003;
    }
    i__2 = e_rsfe();
L100003:
    if (i__2 < 0) {
	goto L500;
    }
    if (i__2 > 0) {
	goto L499;
    }
/* If the record does not have the correct FeH and Alpha, we skip it */
    if ((d__1 = feh - alatm03_1.alatm_feh__, abs(d__1)) > 1e-5 || (d__2 = 
	    alpha - alatm03_1.alatm_alpha__, abs(d__2)) > 0.) {
	goto L440;
/* On to next record */
    }
    i__2 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__2; ++i__) {
/* Skip out when we find the matching Teff */
	if ((d__1 = teff - teffs[i__ - 1], abs(d__1)) < 1e-6) {
	    i1 = i__;
	    goto L420;
	}
    }
    s_wsle(&io___43);
    do_lio(&c__9, &c__1, "ALFilein: Impossible failure #1", (ftnlen)31);
    e_wsle();
    s_wsle(&io___44);
    do_lio(&c__9, &c__1, "Teff of ", (ftnlen)8);
    do_lio(&c__5, &c__1, (char *)&teff, (ftnlen)sizeof(doublereal));
    do_lio(&c__9, &c__1, " not in Teff table.", (ftnlen)19);
    e_wsle();
    goto L9999;
/* The error exit */
L420:
    i__2 = alatm01_1.ngl;
    for (j = 1; j <= i__2; ++j) {
/* Skip out when we find the a matching GL */
	if ((d__1 = gl - alatm01_1.gls[j - 1], abs(d__1)) < 1e-6) {
	    j1 = j;
	    goto L430;
	}
    }
    s_wsle(&io___46);
    do_lio(&c__9, &c__1, "ALFilein: Impossible failure #2", (ftnlen)31);
    e_wsle();
    s_wsle(&io___47);
    do_lio(&c__9, &c__1, "GL of ", (ftnlen)6);
    do_lio(&c__5, &c__1, (char *)&gl, (ftnlen)sizeof(doublereal));
    do_lio(&c__9, &c__1, " not in GL table.", (ftnlen)17);
    e_wsle();
    goto L9999;
/* The error exit */
L430:
/* we now verify that we have the correct FeH and Alpha */
    if ((d__1 = feh - alatm03_1.alatm_feh__, abs(d__1)) >= 1e-6) {
	goto L440;
    }
/* Wrong FeH, bypass item */
    if ((d__1 = alpha - alatm03_1.alatm_alpha__, abs(d__1)) >= 1e-6) {
	goto L440;
    }
/* We now have the correct indices for our tables, i1 for the Teff-direction */
/* and j1 for the GL direction */
/* Wrong Alpha, bypass item */
    alatm01_1.teffls[i1 - 1] = d_lg10(&teff);
/* We need log(teff), but up to now we've been using Teff */
    alatm01_1.gls[j1 - 1] = gl;
    alatm01_1.pls[i1 + j1 * 250 - 251] = pl;
    alatm01_1.p100ls[i1 + j1 * 250 - 251] = p100l;
    alatm01_1.t100ls[i1 + j1 * 250 - 251] = t100;
L440:
    goto L410;
/* Back to process the next record */
L499:
    s_wsle(&io___48);
    e_wsle();
    s_wsle(&io___49);
    do_lio(&c__9, &c__1, "AtTabInit File Read error", (ftnlen)25);
    e_wsle();
    s_wsle(&io___50);
    e_wsle();
    goto L9999;
L500:
/* We heve finished with the input file and entered all inputs */
    altabinit_();
/* Initialize Allard tables */
    return 0;
L9999:
/* THE ERROR EXIT */
    s_wsle(&io___51);
    e_wsle();
    s_wsle(&io___52);
    e_wsle();
    s_wsle(&io___53);
    do_lio(&c__9, &c__1, "**************** PROGRAM ALFilein TERMINATED ", (
	    ftnlen)45);
    do_lio(&c__9, &c__1, "@ 9999 **************", (ftnlen)21);
    e_wsle();
    s_wsle(&io___54);
    e_wsle();
    s_wsle(&io___55);
    e_wsle();
    s_wsle(&io___56);
    e_wsle();
    io___57.ciunit = luout_1.ishort;
    s_wsle(&io___57);
    e_wsle();
    io___58.ciunit = luout_1.ishort;
    s_wsle(&io___58);
    do_lio(&c__9, &c__1, "**************** PROGRAM ALFilein TERMINATED ", (
	    ftnlen)45);
    do_lio(&c__9, &c__1, "@ 9999 *************", (ftnlen)20);
    e_wsle();
    io___59.ciunit = luout_1.ishort;
    s_wsle(&io___59);
    e_wsle();
    io___60.ciunit = luout_1.ishort;
    s_wsle(&io___60);
    e_wsle();
    s_stop("9999", (ftnlen)4);
    return 0;
} /* alfilein_ */

/* ************* End of ALFilein ************************* */
/* Numerical Recipes Shell sort */
/* END OF ALINITTAB */
/* Subroutine */ int sort_shell__(integer *nn, doublereal *a)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, j, n;
    static doublereal v;
    static integer inc;

/* Sorts an array A(1:nn) into ascending numerical order by Shell's method (diminishing */
/* incremental sort) nn is input. A is replaced on output by its sorted arrangement */
    /* Parameter adjustments */
    --a;

    /* Function Body */
    if (*nn == 1) {
	return 0;
    }
/* Exit if only one element */
    n = *nn;
    inc = 1;
L1:
    inc = inc * 3 + 1;
/* Determin starting increment */
    if (inc <= n) {
	goto L1;
    }
L2:
    inc /= 3;
/* Loop over the partial sorts */
    i__1 = n;
    for (i__ = inc + 1; i__ <= i__1; ++i__) {
	v = a[i__];
/* Outer loop of straight insertion */
	j = i__;
L3:
	if (a[j - inc] > v) {
/* Inner loop of straight insertion */
	    a[j] = a[j - inc];
	    j -= inc;
	    if (j <= inc) {
		goto L4;
	    }
	    goto L3;
	}
L4:
	a[j] = v;
    }
    if (inc > 1) {
	goto L2;
    }
    return 0;
} /* sort_shell__ */


/* alsurfp.f -- translated by f2c (version 20100827).
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
    doublereal tau, ap, at, ad, ao, afxion[3];
} atmprt_;

#define atmprt_1 atmprt_

struct {
    doublereal teffls[250], gls[25], fehs[25], alphas[25], pls[6250]	/* 
	    was [250][25] */, p100ls[6250]	/* was [250][25] */, t100ls[
	    6250]	/* was [250][25] */;
    logical loldnextgen;
    integer nteff, ngl, nfeh, nalpha;
} alatm01_;

#define alatm01_1 alatm01_

struct {
    doublereal glmin[250], glmax[250];
    integer iglmin[250], iglmax[250];
    doublereal tefflmin, tefflmax, glxmin, glxmax;
} alatm02_;

#define alatm02_1 alatm02_

struct {
    doublereal alatm_feh__, alatm_alpha__;
    logical laltptau100;
    integer ioatma;
} alatm03_;

#define alatm03_1 alatm03_

struct {
    doublereal dummy1, dummy2;
    char fallard[256];
    doublereal dummy3, dummy4;
} alatm04_;

#define alatm04_1 alatm04_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;
static integer c__4 = 4;

/* 	Subroutine ALSURFP */
/* PURPOSE */
/* To obtain the desired properties of stellar and sub-stellar atmospheres from atmospheric */
/* tables developed by France Allard, et al. Given Log(Teff) and GL, ASURFP returns Log(P) at */
/* this Teff and GL, as well as Log(P) and Log(T) at Tau = 100 for this Teff and GL. */
/* Currently supported input formats include the old Allard, et al, circa 1999 NextGen format, */
/* to which we are adding the newer 2007 NextGen format. As other formats become available, we */
/* anticipate being able to handle those also. */
/* Results are obtained by doing 4-point Lagrange interpolation in two dimensions, in TeffL and */
/* GL. This means we will be interpolating (or extrapolating) over sixteen points in four rows */
/* of four. We require that the desired Teff and GL are within the limits of the extended range */
/* of the table. The extended range for GL is from one column's width past the lowest GL on the */
/* left to one column's width past the highest GL on the right for the current row. The extended */
/* range for TeffL is defined in the same manner as for the columns. Note that the limits are on */
/* a row by row and column by column basis. If the request TeffL, GL point is outside the table, */
/* the progam is terminated with a definitive error message. */
/* ARGUMENTS OF TABLE LOOKUP SUBROUTINE */
/* TeffL	- Input argument. Value of TL at which the results are desired. */
/* GL		- Input argument. Value of GL at which the results are desired. */
/* AP		- Output argument to COMMON /ATMPRT/. Value of Log(Pressure) for the */
/* 		  associated input TeffL and GL If LATMTPTau100 is .FALSE. it is PL */
/* 		  at TEFFL,GL. If .TRUE. it is PL at TAU=100 for the starting TEFFL,GL. */
/* AT		- Output argument to COMMON /ATMPRT/. Value of Log(Temperature) for the */
/* 		  associated input TeffL and GL If LATMTPTau100 is .FALSE. it is TEFFL. */
/* 		  If .TRUE. it is TL at TAU=100 for the starting TEFFL,GL. */
/* LPRT	  Input argument: If .TRUE. print Log(P) at the associated Log(Teff)  to ISHORT and IMODPT. */
/* LAlFail   Output argument. If .TRUE. the specified TeffL/GL is outside the Allard tables. The */
/*           calling routine should set KTTAU to 0 to change to a gray atmosphere, or KTTAU to 3 for */
/*           aKurucz atmosphere. */

/* Internal Arrays */
/* TEFFLs	1-D Array of T=TeffL table elements - one for each TeffL. (Columns) */
/* GLs		1-D Array of G = GL table elements - one for each GL. (Rows) */
/* PLs		2-D array of assoiated PL's for the matching T in TEFFLs and the matching G in GLA. */
/* 		- One for each TeffL by One for each GL */
/* P100Ls	2-D array of assoiated P100L's for the matching T in TEFFLs and  the matching G in GLA. */
/* 		 - One for each TeffL by One for each GL */
/* T100Ls	2-D array of assoiated T100L's for the matching T in TEFFLs and  the matching G in GLA. */
/* 		 - One for each TeffL by One for each GL */
/* In addition, we define the following auxiliarry arrays */
/* For each row (or GL): */
/* GLmin	Minimum acceptable GL (including extrapolation) for this row.   - One for each TeffL */
/* GLmax	Maximum acceptable GL (including extrapolation) for this row.   - One for each TeffL */
/* IGLmin	Row index of first acceptable GL in table (excludes extrapolation) - One for each TeffL */
/* IGLmax	Row index of first acceptable GL in table (excludes extrapolation) - One for each TeffL */
/* For teh Table */
/* TEFFLmin		Minimum acceptable TeffL (Including extrapolation) for the table */
/* TEFFLmax		Maximum acceptable TeffL (including extrapolation) for the table. */
/* OVERALL LOGIC */
/* I	Determine if TeffL and GL are within overall limits of the table. If TEFFL is greater than the */
/*     max of all table TL's or less than the minimum, or GL is of the same nature, the program has */
/*     failed.  To fail, write diagnostic message and go to error exit. */
/* II	Locate TL and GL in table. This gives us a column index, iGL, and a row index, iTL. The subtable */
/*     used for Lagrange interpolation will  	have four rows of four elements. Find indices such that */
/*     each row is in the table.  Start with TeffL. If it is out of the table, adjust the TeffL index */
/*     such that all four rows are in the table. Then for each row asjust the GL index such that the */
/*     row is in the table. If this is not possible, the program has failed. To fail, write diagnostic */
/*     message and go to error exit. */
/* III	Next we do four-point-Lagrange-interpolation in GL in the first row, then the second, then the */
/*     third, then the fourth rows. We obtain, for each row, the associated Log(P), Log(P100) and */
/*     Log(T100) for each row's specific TL. */
/*  IV	To get our desired results, we interpolate the results from III. PL is the result of 4-point */
/*     Lagrange interpolation in TL using the four Log(P)'s obtained in III above. Likewist P100L and */
/*     T100L. */
/* 	If LPRT  is .TRUE. print Log(P) at the associated Log(Teff) to ISHORT and IMODPT. */
/* Subroutine */ int alsurfp_(doublereal *teffl, doublereal *gl, logical *
	lprt, logical *lalfail)
{
    /* Format strings */
    static char fmt_70[] = "(\002********PL,TL at Tau=100 INTERPOLATED\002"
	    ",\002 FROM ALLARD TABULATED VALUES********\002)";
    static char fmt_71[] = "(\002********PL,TL at T=TEFF,GL INTERPOLATED "
	    "\002,\002FROM ALLARD TABULATED VALUES********\002)";
    static char fmt_72[] = "(\002 \002,20x,\002LOG(Teffl) =\002,f10.5,\002 ,"
	    "LOG(G) =\002,f10.5,\002, LOG(T) =\002,f10.5,\002, Log(P) =\002,f"
	    "10.5)";
    static char fmt_73[] = "(\002ALSURFP:  PL,TL at Tau=100 INTERPOLATE"
	    "D\002,\002 FROM ALLARD TABULATED VALUES:\002)";
    static char fmt_74[] = "(\002ALSURFP: PL,TL at T=TEFF,GL INTERPOLATED"
	    " \002,\002FROM ALLARD TABULATED VALUES:\002)";
    static char fmt_75[] = "(\002 \002,10x,\002LOG(Teffl) =\002,f10.5,\002, "
	    "LOG(G) =\002,f10.5,\002, LOG(T) =\002,f10.5,\002, Log(P) =\002,f"
	    "10.5)";

    /* Builtin functions */
    integer s_wsle(cilist *), e_wsle(void), do_lio(integer *, integer *, char 
	    *, ftnlen), s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, 
	    char *, ftnlen);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, n, i1;
    static logical lbadpoint;
    static integer j1, j2, j3;
    static doublereal dy, pl1[4], pl2[4];
    static integer igl[4];
    static doublereal p100l1[4], p100l2[4], t100l1[4], t100l2[4];
    extern /* Subroutine */ int locate_(doublereal *, integer *, doublereal *,
	     integer *);
    static integer iteffl;
    extern /* Subroutine */ int polint_(doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, 0, 0 };
    static cilist io___3 = { 0, 0, 0, 0, 0 };
    static cilist io___4 = { 0, 0, 0, 0, 0 };
    static cilist io___5 = { 0, 6, 0, 0, 0 };
    static cilist io___6 = { 0, 6, 0, 0, 0 };
    static cilist io___7 = { 0, 6, 0, 0, 0 };
    static cilist io___8 = { 0, 0, 0, 0, 0 };
    static cilist io___9 = { 0, 6, 0, 0, 0 };
    static cilist io___10 = { 0, 0, 0, 0, 0 };
    static cilist io___11 = { 0, 0, 0, 0, 0 };
    static cilist io___12 = { 0, 6, 0, 0, 0 };
    static cilist io___13 = { 0, 6, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, 0, 0 };
    static cilist io___15 = { 0, 0, 0, 0, 0 };
    static cilist io___16 = { 0, 0, 0, 0, 0 };
    static cilist io___17 = { 0, 6, 0, 0, 0 };
    static cilist io___18 = { 0, 6, 0, 0, 0 };
    static cilist io___19 = { 0, 6, 0, 0, 0 };
    static cilist io___28 = { 0, 0, 0, 0, 0 };
    static cilist io___29 = { 0, 0, 0, 0, 0 };
    static cilist io___30 = { 0, 0, 0, 0, 0 };
    static cilist io___31 = { 0, 6, 0, 0, 0 };
    static cilist io___32 = { 0, 6, 0, 0, 0 };
    static cilist io___33 = { 0, 6, 0, 0, 0 };
    static cilist io___42 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___44 = { 0, 0, 0, fmt_71, 0 };
    static cilist io___45 = { 0, 0, 0, fmt_71, 0 };
    static cilist io___46 = { 0, 0, 0, fmt_72, 0 };
    static cilist io___47 = { 0, 0, 0, fmt_72, 0 };
    static cilist io___48 = { 0, 0, 0, fmt_73, 0 };
    static cilist io___49 = { 0, 0, 0, fmt_74, 0 };
    static cilist io___50 = { 0, 0, 0, fmt_75, 0 };
    static cilist io___51 = { 0, 6, 0, 0, 0 };
    static cilist io___52 = { 0, 6, 0, 0, 0 };
    static cilist io___53 = { 0, 6, 0, 0, 0 };
    static cilist io___54 = { 0, 0, 0, 0, 0 };
    static cilist io___55 = { 0, 0, 0, 0, 0 };
    static cilist io___56 = { 0, 0, 0, 0, 0 };


/* Shared: ALFILEIN, ALTABINIT and ALSURFP */
/* Shared: ALTABINIT and ALSURFP */
/* Shared: ALFILEIN, */
/* ALSURFP and PARMIN */
/* 	Determine if TeffL and GL are within overall limits of the table. If TEFFL is greater than the */
/*    max of all table TL's or GL is greater than the max or less than the min. Under these */
/*    circumstances we want to switch to another kind of atmosphere by changing KTTAU. Most likely */
/*    the calling routine should set KTTAU to 0, to specify a gray atmosphere. */
    lbadpoint = FALSE_;
/* presume we have started at a good point */
    if (*teffl >= alatm02_1.tefflmax) {
	lbadpoint = TRUE_;
	io___2.ciunit = luout_1.ishort;
	s_wsle(&io___2);
	e_wsle();
	io___3.ciunit = luout_1.ishort;
	s_wsle(&io___3);
	do_lio(&c__9, &c__1, "ALSURFP: TEFFL greater than TeffLmax: ", (
		ftnlen)38);
	e_wsle();
	io___4.ciunit = luout_1.ishort;
	s_wsle(&io___4);
	do_lio(&c__9, &c__1, "    TEFFLmin,TEFFL,TEFFLmax; ", (ftnlen)29);
	do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmin, (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmax, (ftnlen)sizeof(
		doublereal));
	e_wsle();
	s_wsle(&io___5);
	e_wsle();
	s_wsle(&io___6);
	do_lio(&c__9, &c__1, "ALSURFP: TEFFL greater than TeffLmax: ", (
		ftnlen)38);
	e_wsle();
	s_wsle(&io___7);
	do_lio(&c__9, &c__1, "    TEFFLmin,TEFFL,TEFFLmax; ", (ftnlen)29);
	do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmin, (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmax, (ftnlen)sizeof(
		doublereal));
	e_wsle();
    }
    if (*gl >= alatm02_1.glxmax || *gl <= alatm02_1.glxmin) {
	lbadpoint = TRUE_;
	io___8.ciunit = luout_1.ishort;
	s_wsle(&io___8);
	e_wsle();
	s_wsle(&io___9);
	e_wsle();
	io___10.ciunit = luout_1.ishort;
	s_wsle(&io___10);
	do_lio(&c__9, &c__1, "ALSURFP: GL out of max range: ", (ftnlen)30);
	e_wsle();
	io___11.ciunit = luout_1.ishort;
	s_wsle(&io___11);
	do_lio(&c__9, &c__1, "    GLXmin,GL,GLXmax; ", (ftnlen)22);
	do_lio(&c__5, &c__1, (char *)&alatm02_1.glxmin, (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&alatm02_1.glxmax, (ftnlen)sizeof(
		doublereal));
	e_wsle();
	s_wsle(&io___12);
	do_lio(&c__9, &c__1, "ALSURFP: GL out of max range: ", (ftnlen)30);
	e_wsle();
	s_wsle(&io___13);
	do_lio(&c__9, &c__1, "    GLXmin,GL,GLXmax; ", (ftnlen)22);
	do_lio(&c__5, &c__1, (char *)&alatm02_1.glxmin, (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&alatm02_1.glxmax, (ftnlen)sizeof(
		doublereal));
	e_wsle();
    }
    if (lbadpoint) {
	*lalfail = TRUE_;
/* Set LAlFail so calling routine can take appropiate action */
/* We are above the table in Teffl, or outside the table in GL */
	return 0;
    } else {
	*lalfail = FALSE_;
/* We are not above the table in Teffl, and inside the table in GL */
    }
/*    If TeffL is less than TeffLmin, the program has failed.  We write a diagnostic message and go */
/*    to the error exit. */
    if (*teffl <= alatm02_1.tefflmin) {
	io___14.ciunit = luout_1.ishort;
	s_wsle(&io___14);
	e_wsle();
	io___15.ciunit = luout_1.ishort;
	s_wsle(&io___15);
	do_lio(&c__9, &c__1, "ALSURFP: TEFFL less than TEFFLmin: ", (ftnlen)
		35);
	e_wsle();
	io___16.ciunit = luout_1.ishort;
	s_wsle(&io___16);
	do_lio(&c__9, &c__1, "    TEFFLmin,TEFFL,TEFFLmax; ", (ftnlen)29);
	do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmin, (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmax, (ftnlen)sizeof(
		doublereal));
	e_wsle();
	s_wsle(&io___17);
	e_wsle();
	s_wsle(&io___18);
	do_lio(&c__9, &c__1, "ALSURFP: TEFFL less than TEFFLmin: ", (ftnlen)
		35);
	e_wsle();
	s_wsle(&io___19);
	do_lio(&c__9, &c__1, "    TEFFLmin,TEFFL,TEFFLmax; ", (ftnlen)29);
	do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmin, (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmax, (ftnlen)sizeof(
		doublereal));
	e_wsle();
	goto L9999;
/* End program at Error Exit */
    }
/* II	Locate TEFFL and GL in table. This gives us a column index, iGL, and a row index, iTEFFL. The */
/*     subtable used for Lagrange interpolation will have four rows of four elements. Find indices such */
/*     that each row is in the table.  Start with TeffL. If it is out of the table, adjust the TeffL */
/*     index such that all four rows are in the table. Then for each row asjust the GL index such that the */
/*     row is in the table. If this is not possible, the program has failed. To fail, write diagnostic */
/*     message and go to error exit. */
/* First locate TEFFL */
    locate_(alatm01_1.teffls, &alatm01_1.nteff, teffl, &iteffl);
/* returns row 2 in Teffs for 4x4 Lagrange */
    --iteffl;
/* Change to row 1 of 4x4 square in TEFFLs */
    if (iteffl < 1) {
	iteffl = 1;
    }
/* Be sure it is safe to do 4-point Lagrange interpolation */
    if (iteffl > alatm01_1.nteff - 3) {
	iteffl = alatm01_1.nteff - 3;
    }
/* Now find the right index for each row. */
    for (i__ = 1; i__ <= 4; ++i__) {
/* Start with iTEFFL and go up to iTEFFL=3 */
	i1 = iteffl + i__ - 1;
/* current row pointer - index in TEFFLs aray (0 to 3) */
	j1 = alatm02_1.iglmin[i1 - 1];
/* lowest valid entry in this row */
	j2 = alatm02_1.iglmax[i1 - 1];
/* higest valid entry in this row */
	n = j2 - j1 + 1;
/* number of OK columns */
	locate_(&alatm01_1.gls[j1 - 1], &n, gl, &j3);
/* and GL,GLs(JL1+j3) */
/* Returns offset in GLs such that GL is >= GLs(jl1+j3-1) */
	igl[i__ - 1] = j1 + j3 - 1;
/* Save the offset */
	--igl[i__ - 1];
/* FIrst make sure it is safe to do 4-point Lagrange interpolaltion */
/* Change from col 2 to column 1 in GLs direction of 4x4 square */
	if (igl[i__ - 1] < j1) {
	    igl[i__ - 1] = j1;
	}
	if (igl[i__ - 1] > j2 - 3) {
	    igl[i__ - 1] = j2 - 3;
	}
/* Next, make sue that GL is in range in the current row.  If not, set out of table flag */
	if (*gl < alatm02_1.glmin[i1 - 1] || *gl > alatm02_1.glmax[i1 - 1]) {
/* and exit */
	    lbadpoint = TRUE_;
	    io___28.ciunit = luout_1.ishort;
	    s_wsle(&io___28);
	    e_wsle();
	    io___29.ciunit = luout_1.ishort;
	    s_wsle(&io___29);
	    do_lio(&c__9, &c__1, "ALSURFP: GL out of extended range: ", (
		    ftnlen)35);
	    e_wsle();
	    io___30.ciunit = luout_1.ishort;
	    s_wsle(&io___30);
	    do_lio(&c__9, &c__1, "    GLmin,GL,GLmax; ", (ftnlen)20);
	    do_lio(&c__5, &c__1, (char *)&alatm02_1.glmin[i1 - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&alatm02_1.glmax[i1 - 1], (ftnlen)
		    sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___31);
	    e_wsle();
	    s_wsle(&io___32);
	    do_lio(&c__9, &c__1, "ALSURFP: GL out of extended range: ", (
		    ftnlen)35);
	    e_wsle();
	    s_wsle(&io___33);
	    do_lio(&c__9, &c__1, "    GLmin,GL,GLmax; ", (ftnlen)20);
	    do_lio(&c__5, &c__1, (char *)&alatm02_1.glmin[i1 - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&alatm02_1.glmax[i1 - 1], (ftnlen)
		    sizeof(doublereal));
	    e_wsle();
	    *lalfail = TRUE_;
	    return 0;
	}
    }
/* III	Next we do four-point-Lagrange-interpolation in GL in the first row, then the second, then the */
/*     third, then the fourth rows. We obtain, for each row, the associated Log(P), Log(P100) and */
/*     Log(T100) for each row's specific TL. */
/* Do the Lagrange interpolation in GL */
    for (i__ = 1; i__ <= 4; ++i__) {
/* Start with iTEFFL and go up to iTEFFL=3, a row at a time */
	i1 = iteffl + i__ - 1;
/* Index in TEFFL array (0 to 3) */
	for (j = 1; j <= 4; ++j) {
	    j1 = igl[i__ - 1] + j - 1;
/* Index in GL array - from iGL(i) to iGL(i)+3 */
	    pl1[j - 1] = alatm01_1.pls[i1 + j1 * 250 - 251];
/* Get this row's four working PL's */
	    p100l1[j - 1] = alatm01_1.p100ls[i1 + j1 * 250 - 251];
/* Get this row's four working P100L's */
	    t100l1[j - 1] = alatm01_1.t100ls[i1 + j1 * 250 - 251];
/* Get this row's four working T100L's */
	}
	j1 = igl[i__ - 1];
	polint_(&alatm01_1.gls[j1 - 1], pl1, &c__4, gl, &pl2[i__ - 1], &dy);
	polint_(&alatm01_1.gls[j1 - 1], p100l1, &c__4, gl, &p100l2[i__ - 1], &
		dy);
	polint_(&alatm01_1.gls[j1 - 1], t100l1, &c__4, gl, &t100l2[i__ - 1], &
		dy);
    }
/* Now do final 4-point Lagrange inerpolations in TEFFL */
    if (! alatm03_1.laltptau100) {
/*   Current standard alternative. PL for TEFFL,GL, TL=TEFFL */
	polint_(&alatm01_1.teffls[iteffl - 1], pl2, &c__4, teffl, &
		atmprt_1.ap, &dy);
	atmprt_1.at = *teffl;
    } else {
	polint_(&alatm01_1.teffls[iteffl - 1], p100l2, &c__4, teffl, &
		atmprt_1.ap, &dy);
	polint_(&alatm01_1.teffls[iteffl - 1], t100l2, &c__4, teffl, &
		atmprt_1.at, &dy);
    }
/* We now have obtained the needed temparatures and pressures */
/* If requested, WRITE OUT INFORMATION TO THE MODEL FILE. */
    if (*lprt) {
	if (alatm03_1.laltptau100) {
	    io___42.ciunit = luout_1.ishort;
	    s_wsfe(&io___42);
	    e_wsfe();
	    io___43.ciunit = luout_1.imodpt;
	    s_wsfe(&io___43);
	    e_wsfe();
	} else {
	    io___44.ciunit = luout_1.ishort;
	    s_wsfe(&io___44);
	    e_wsfe();
	    io___45.ciunit = luout_1.imodpt;
	    s_wsfe(&io___45);
	    e_wsfe();
	}
	io___46.ciunit = luout_1.ishort;
	s_wsfe(&io___46);
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&atmprt_1.at, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&atmprt_1.ap, (ftnlen)sizeof(doublereal));
	e_wsfe();
	io___47.ciunit = luout_1.imodpt;
	s_wsfe(&io___47);
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&atmprt_1.at, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&atmprt_1.ap, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
/* If not requested via LPRT, WRITE OUT INFORMATION TO THE SHORT FILE. */
    if (! (*lprt)) {
	if (alatm03_1.laltptau100) {
	    io___48.ciunit = luout_1.ishort;
	    s_wsfe(&io___48);
	    e_wsfe();
	} else {
	    io___49.ciunit = luout_1.ishort;
	    s_wsfe(&io___49);
	    e_wsfe();
	}
	io___50.ciunit = luout_1.ishort;
	s_wsfe(&io___50);
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&atmprt_1.at, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&atmprt_1.ap, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    return 0;
L9999:
    s_wsle(&io___51);
    e_wsle();
    s_wsle(&io___52);
    do_lio(&c__9, &c__1, "******** ALSURFP: Program Terminated ********", (
	    ftnlen)45);
    e_wsle();
    s_wsle(&io___53);
    e_wsle();
    io___54.ciunit = luout_1.ishort;
    s_wsle(&io___54);
    e_wsle();
    io___55.ciunit = luout_1.ishort;
    s_wsle(&io___55);
    do_lio(&c__9, &c__1, "******** ALSURF: Program Terminated ********", (
	    ftnlen)44);
    e_wsle();
    io___56.ciunit = luout_1.ishort;
    s_wsle(&io___56);
    e_wsle();
    s_stop("", (ftnlen)0);
/* eliminate for testing */
    return 0;
} /* alsurfp_ */


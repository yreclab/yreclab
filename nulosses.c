/* nulosses.f -- translated by f2c (version 20100827).
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

/* Table of constant values */

static integer c__4 = 4;

/* .. */
/* .. */
/* .. neutrino loss subroutine modified by G. Newsham */
/* .. from codes of N. Itoh & F. Timmes */
/* .. (9/06) */
/* .. */
/* .. */
/* .. Currently uses just the carbon coefficients for the bremsstrahlung */
/* .. neutrino losses (the differences for other elements is slight.) */
/* .. We also currently set the fermi temperature cuttoff at 0.01 Tfermi. */
/* .. This is applicable for helium but will need to be amended for */
/* .. carbon and oxygen white dwarfs and cores of AGB stars. */
/* .. */
/* .. */
/* Subroutine */ int nulosses_(doublereal *temp, doublereal *den, doublereal *
	snu, doublereal *xmass, doublereal *ymass, doublereal *aion, 
	doublereal *zion, doublereal *dsnudt, doublereal *dsnudd)
{
    static doublereal abar, zbar;
    extern /* Subroutine */ int azbar_(doublereal *, doublereal *, doublereal 
	    *, integer *, doublereal *, doublereal *, doublereal *), sneut_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal dsnuda, dsnudz;

/* ..tests the neutrino loss rate routine */
/* ..ionmax  = number of isotopes in the network */
/* ..xmass   = mass fractions */
/* ..ymass   = molar fractions */
/* ..aion    = number of nucleons */
/* ..zion    = number of protons */
/* ..get abar and zbar */
    /* Parameter adjustments */
    --zion;
    --aion;
    --ymass;
    --xmass;

    /* Function Body */
    azbar_(&xmass[1], &aion[1], &zion[1], &c__4, &ymass[1], &abar, &zbar);
/* ..get the neutrino losses */
    sneut_(temp, den, &abar, &zbar, snu, dsnudt, dsnudd, &dsnuda, &dsnudz);
    return 0;
} /* nulosses_ */

/* Subroutine */ int azbar_(doublereal *xmass, doublereal *aion, doublereal *
	zion, integer *ionmax, doublereal *ymass, doublereal *abar, 
	doublereal *zbar)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal ytot1, zbarxx;

/* ..input */
/* ..mass fractions     = xmass(1:ionmax) */
/* ..number of nucleons = aion(1:ionmax) */
/* ..charge of nucleus  = zion(1:ionmax) */
/* ..number of isotopes = ionmax */
/* ..output: */
/* ..molar abundances        = ymass(1:ionmax), */
/* ..mean number of nucleons = abar */
/* ..mean nucleon charge     = zbar */
/* ..declare */
    /* Parameter adjustments */
    --ymass;
    --zion;
    --aion;
    --xmass;

    /* Function Body */
    zbarxx = 0.;
    ytot1 = 0.;
    i__1 = *ionmax;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ymass[i__] = xmass[i__] / aion[i__];
	ytot1 += ymass[i__];
	zbarxx += zion[i__] * ymass[i__];
    }
    *abar = 1. / ytot1;
    *zbar = zbarxx * *abar;
    return 0;
} /* azbar_ */


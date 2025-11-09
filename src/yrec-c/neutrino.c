/* neutrino.f -- translated by f2c (version 20061008).
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

/* ********* Added by Grant Newsham 9/06 */

/* Currently sets up just hydrogen, helium, carbon and oxygen for */
/* use in neutrino loss calculations */

/* Returns not only neutrino loss (snu)  but the derivatives of the loss */
/* with respect to the temperature and density (dsnudt and dsnudd.) */

/* Subroutine */ int neutrino_(doublereal *temp, doublereal *den, doublereal *
	x, doublereal *y, doublereal *zc, doublereal *zo, doublereal *snu, 
	doublereal *dsnudt, doublereal *dsnudd)
{
    extern /* Subroutine */ int nulosses_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal aion[4], zion[4], xmass[4], ymass[4];


/* ..set the mass fractions, z's and a's of the composition */
/* ..hydrogen */
    aion[0] = 1.;
    zion[0] = 1.;
/* ..helium */
    aion[1] = 4.;
    zion[1] = 2.;
/* ..carbon 12 */
    aion[2] = 12.;
    zion[2] = 6.;
/* ..oxygen 16 */
    aion[3] = 16.;
    zion[3] = 8.;
    xmass[0] = *x;
    xmass[1] = *y;
    xmass[2] = *zc;
    xmass[3] = *zo;
    nulosses_(temp, den, snu, xmass, ymass, aion, zion, dsnudt, dsnudd);
    return 0;
} /* neutrino_ */


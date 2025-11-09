/* sneut.f -- translated by f2c (version 20061008).
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

static doublereal c_b2 = .33333333333333331;
static doublereal c_b3 = -.3;
static doublereal c_b4 = .66666666666666663;
static doublereal c_b5 = -2.066;
static doublereal c_b7 = 3.85;
static doublereal c_b8 = 2.85;
static doublereal c_b9 = 1.4;
static doublereal c_b10 = .4;
static doublereal c_b11 = -.11;
static doublereal c_b12 = -1.11;
static doublereal c_b13 = .656;
static doublereal c_b14 = -.454;
static doublereal c_b17 = -2.25;
static doublereal c_b18 = -4.55;

/* Subroutine */ int sneut_(doublereal *temp, doublereal *den, doublereal *
	abar, doublereal *zbar, doublereal *snu, doublereal *dsnudt, 
	doublereal *dsnudd, doublereal *dsnuda, doublereal *dsnudz)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *), exp(
	    doublereal), d_lg10(doublereal *), sin(doublereal), cos(
	    doublereal);

    /* Local variables */
    extern doublereal zfermim12_(doublereal *);
    static doublereal b, c__, d__, u, v, w, z__, a0, a1, a2, a3, b1, b2, f0, 
	    f1, f2, f3, t8, t9, c00, c01, c02, cc, c03, c04, c05, c06, c10, 
	    c11, c12, c13, c14, c15, c16, c20, c21, c22, c23, c24, c25, c26, 
	    gl, ft, fl, fb, gt, ye, rm, t82, t83, t85, t86, xl, gb, nu, gl2, 
	    gm1, gm2, gl6, t812, t832, nu2, xl2, xl3, xl4, xl5, xl6, xl7, xl8,
	     xl9, nu3, dd00, dd01, dd02, dd03, dd04, dd05, dd11, dd12, dd13, 
	    dd14, dd15, dd21, dd22, dd23, dd24, dd25, gl12, gl32, eta, gl72, 
	    gm13, gm23, gm43, gm53, dum, rmi, gum, tau, t8m1, t8m2, t8m3, 
	    t8m5, t8m6, fxy, den6, cos1, cos2, cos3, cos4, cos5, sin1, sin2, 
	    sin3, sin4, sin5, xlm1, xlm2, xlm3, xlm4, xlp5, flda, fldd, bigj, 
	    ftda, deni, ftdd, rmda, rmdd, nuda, fldt, gldt, fliq, gliq, nudd, 
	    xden, fldz, ftdt, zeta, last, ftdz, nudt, xldt, rmdz, xmue, xast, 
	    nudz, xlnt, xnum, gl2da, gl2dd, etam1, etam2, etam3, gl2dt, gl2dz,
	     zeta2, zeta3, xlmp5, abari, etada, etadd, dumda, fbrem, gbrem, 
	    dumdd, gumda, gumdd, fpair, etadt, zbari, sbrem, etadz, sreco, 
	    qpair, dumdt, spair, tempi, gumdt, fxydd, splas, dumdz, fxyda, 
	    taudt, gumdz, fphot, qphot, sphot, fxydt, fxydz, bigjda, bigjdd, 
	    fliqda, gliqda, xdenda, fliqdd, gliqdd, xdendd, bigjdt, zetada, 
	    bigjdz, zetadd, fliqdt, gliqdt, tfermi, xdendt, fliqdz, gliqdz, 
	    zetadt, xnumda, xdendz, xnumdd, zetadz, xnumdt, xnumdz, fbremda, 
	    gbremda, fbremdd, gbremdd, fpairda, fpairdd, sbremda;
    extern doublereal ifermi12_(doublereal *);
    static doublereal sbremdd, srecoda, qpairda, spairda, srecodd, qpairdd, 
	    spairdd, splasda, fphotdd, fpairdt, splasdd, fphotda, fbremdt, 
	    fbremdz, gbremdt, fpairdz, sbremdt, qphotda, sphotda, srecodt, 
	    qpairdt, sphotdd, spairdt, sbremdz, fphotdt, srecodz, splasdt, 
	    qpairdz, spairdz, qphotdd, fphotdz, gbremdz, splasdz, qphotdt, 
	    sphotdt, qphotdz, sphotdz;

/* ..this routine computes neutrino losses from the analytic fits of */
/* ..itoh et al. apjs 102, 411, 1996, and also returns their derivatives. */
/* ..input: */
/* ..temp = temperature */
/* ..den  = density */
/* ..abar = mean atomic weight */
/* ..zbar = mean charge */
/* ..output: */
/* ..snu    = total neutrino loss rate in erg/g/sec */
/* ..dsnudt = derivative of snu with temperature */
/* ..dsnudd = derivative of snu with density */
/* ..dsnuda = derivative of snu with abar */
/* ..dsnudz = derivative of snu with zbar */
/* ..declare the pass */
/* ..local variables */
/*       integer          i */
/* ..pair production */
/* b3 */
/* rp1,rn1 */
/* ..plasma */
/* ..photo */
/* ..brem */
/* ..recomb */
/* ..numerical constants */
/* ..theta is sin**2(theta_weinberg) = 0.2319 plus/minus 0.00005 (1996) */
/* ..xnufam is the number of neutrino flavors = 3.02 plus/minus 0.005 (1998) */
/* ..change theta and xnufam if need be, and the changes will automatically */
/* ..propagate through the routine. cv and ca are the vector and axial currents. */
/* ..initialize */
    spair = 0.;
    spairdt = 0.;
    spairdd = 0.;
    spairda = 0.;
    spairdz = 0.;
    splas = 0.;
    splasdt = 0.;
    splasdd = 0.;
    splasda = 0.;
    splasdz = 0.;
    sphot = 0.;
    sphotdt = 0.;
    sphotdd = 0.;
    sphotda = 0.;
    sphotdz = 0.;
    sbrem = 0.;
    sbremdt = 0.;
    sbremdd = 0.;
    sbremda = 0.;
    sbremdz = 0.;
    sreco = 0.;
    srecodt = 0.;
    srecodd = 0.;
    srecoda = 0.;
    srecodz = 0.;
    *snu = 0.;
    *dsnudt = 0.;
    *dsnudd = 0.;
    *dsnuda = 0.;
    *dsnudz = 0.;
    if (*temp < 1e7f) {
	return 0;
    }
/* ..to avoid lots of divisions */
    deni = 1. / *den;
    tempi = 1. / *temp;
    abari = 1. / *abar;
    zbari = 1. / *zbar;
/* ..some composition variables */
    ye = *zbar * abari;
    xmue = *abar * zbari;
/* ..some frequent factors */
    t9 = *temp * 1e-9;
    xl = t9 * .16862837678324508;
    xldt = 1.6862837678324508e-10;
    xlp5 = sqrt(xl);
    xl2 = xl * xl;
    xl3 = xl2 * xl;
    xl4 = xl3 * xl;
    xl5 = xl4 * xl;
    xl6 = xl5 * xl;
    xl7 = xl6 * xl;
    xl8 = xl7 * xl;
    xl9 = xl8 * xl;
    xlmp5 = 1. / xlp5;
    xlm1 = 1. / xl;
    xlm2 = xlm1 * xlm1;
    xlm3 = xlm1 * xlm2;
    xlm4 = xlm1 * xlm3;
    rm = *den * ye;
    rmdd = ye;
    rmda = -rm * abari;
    rmdz = *den * abari;
    rmi = 1. / rm;
    a0 = rm * 1e-9;
    a1 = pow_dd(&a0, &c_b2);
    zeta = a1 * xlm1;
    zetadt = -a1 * xlm2 * xldt;
    a2 = a1 * .33333333333333331 * rmi * xlm1;
    zetadd = a2 * rmdd;
    zetada = a2 * rmda;
    zetadz = a2 * rmdz;
    zeta2 = zeta * zeta;
    zeta3 = zeta2 * zeta;
/* ..pair neutrino section */
/* ..for reactions like e+ + e- => nu_e + nubar_e */
/* ..equation 2.8 */
    gl = 1. - xl2 * 13.04 + xl4 * 133.5 + xl6 * 1534. + xl8 * 918.6;
    gldt = xldt * (xl * -26.08 + xl3 * 534. + xl5 * 9204. + xl7 * 7348.8);
/* ..equation 2.7 */
    a1 = zeta * 2.084e20 + 6.002e19 + zeta2 * 1.872e21;
    a2 = zeta * 3.744e21 + 2.084e20;
    if (t9 < 10.f) {
	b1 = exp(zeta * -5.5924);
	b2 = -b1 * 5.5924;
    } else {
	b1 = exp(zeta * -4.9924);
	b2 = -b1 * 4.9924;
    }
    xnum = a1 * b1;
    c__ = a2 * b1 + a1 * b2;
    xnumdt = c__ * zetadt;
    xnumdd = c__ * zetadd;
    xnumda = c__ * zetada;
    xnumdz = c__ * zetadz;
    if (t9 < 10.f) {
	a1 = xlm1 * .9383 - xlm2 * .4141 + xlm3 * .05829;
	a2 = xlm2 * -.9383 + xlm3 * .82820000000000005 - xlm4 * .17487;
    } else {
	a1 = xlm1 * 1.2383 - xlm2 * .8141;
	a2 = xlm2 * -1.2383 + xlm3 * 1.6282000000000001;
    }
    b1 = zeta2 * 3.;
    xden = zeta3 + a1;
    xdendt = b1 * zetadt + a2 * xldt;
    xdendd = b1 * zetadd;
    xdenda = b1 * zetada;
    xdendz = b1 * zetadz;
    a1 = 1. / xden;
    fpair = xnum * a1;
    fpairdt = (xnumdt - fpair * xdendt) * a1;
    fpairdd = (xnumdd - fpair * xdendd) * a1;
    fpairda = (xnumda - fpair * xdenda) * a1;
    fpairdz = (xnumdz - fpair * xdendz) * a1;
/* ..equation 2.6 */
    a1 = xl2 * 10.748 + xlp5 * .3967 + 1.005;
    a2 = xldt * (xl * 21.495999999999999 + xlmp5 * .19835);
    xnum = 1. / a1;
    xnumdt = -xnum * xnum * a2;
    a1 = xl3 * 7.692e7 + xlp5 * 9.715e6;
    a2 = xldt * (xl2 * 2.3076e8 + xlmp5 * 4857500.);
    c__ = 1. / a1;
    b1 = rm * c__ + 1.;
    xden = pow_dd(&b1, &c_b3);
    d__ = xden * -.3 / b1;
    xdendt = -d__ * rm * c__ * c__ * a2;
    xdendd = d__ * rmdd * c__;
    xdenda = d__ * rmda * c__;
    xdendz = d__ * rmdz * c__;
    qpair = xnum * xden;
    qpairdt = xnumdt * xden + xnum * xdendt;
    qpairdd = xnum * xdendd;
    qpairda = xnum * xdenda;
    qpairdz = xnum * xdendz;
/* ..equation 2.5 */
    a1 = exp(xlm1 * -2.);
    a2 = a1 * 2. * xlm2 * xldt;
    spair = a1 * fpair;
    spairdt = a2 * fpair + a1 * fpairdt;
    spairdd = a1 * fpairdd;
    spairda = a1 * fpairda;
    spairdz = a1 * fpairdz;
    a1 = spair;
    spair = gl * a1;
    spairdt = gl * spairdt + gldt * a1;
    spairdd = gl * spairdd;
    spairda = gl * spairda;
    spairdz = gl * spairdz;
    a1 = (qpair * -.78408808942077868 + 1.) * .84076566000000008;
    a2 = -.65923434000000003;
    a3 = spair;
    spair = a1 * a3;
    spairdt = a1 * spairdt + a2 * qpairdt * a3;
    spairdd = a1 * spairdd + a2 * qpairdd * a3;
    spairda = a1 * spairda + a2 * qpairda * a3;
    spairdz = a1 * spairdz + a2 * qpairdz * a3;
/* ..plasma neutrino section */
/* ..for collective reactions like gamma_plasmon => nu_e + nubar_e */
/* ..equation 4.6 */
    a1 = rm * 1.019e-6;
    a2 = pow_dd(&a1, &c_b4);
    a3 = a2 * .66666666666666663 / a1;
    b1 = sqrt(a2 + 1.);
    b2 = 1. / b1;
    c00 = 1. / (*temp * *temp * b1);
    gl2 = rm * 1.1095e11 * c00;
    gl2dt = gl2 * -2. * tempi;
    d__ = rm * c00 * b2 * .5 * b2 * a3 * 1.019e-6;
    gl2dd = (rmdd * c00 - d__ * rmdd) * 1.1095e11;
    gl2da = (rmda * c00 - d__ * rmda) * 1.1095e11;
    gl2dz = (rmdz * c00 - d__ * rmdz) * 1.1095e11;
    gl = sqrt(gl2);
    gl12 = sqrt(gl);
    gl32 = gl * gl12;
    gl72 = gl2 * gl32;
    gl6 = gl2 * gl2 * gl2;
/* ..equation 4.7 */
    ft = gl12 * .6 + 2.4 + gl * .51 + gl32 * 1.25;
    gum = 1. / gl2;
    a1 = (gl12 * .14999999999999999 + gl * .255 + gl32 * .9375) * gum;
    ftdt = a1 * gl2dt;
    ftdd = a1 * gl2dd;
    ftda = a1 * gl2da;
    ftdz = a1 * gl2dz;
/* ..equation 4.8 */
    a1 = gl2 * 8.6 + gl72 * 1.35;
    a2 = gl72 * 2.3625000000000003 * gum + 8.6;
    b1 = 225. - gl * 17. + gl2;
    b2 = gl * -8.5 * gum + 1.;
    c__ = 1. / b1;
    fl = a1 * c__;
    d__ = (a2 - fl * b2) * c__;
    fldt = d__ * gl2dt;
    fldd = d__ * gl2dd;
    flda = d__ * gl2da;
    fldz = d__ * gl2dz;
/* ..equation 4.9 and 4.10 */
    d__1 = rm * 2.;
    cc = d_lg10(&d__1);
    xlnt = d_lg10(temp);
    xnum = (cc + 17.5 - xlnt * 3.) * .16666666666666666;
    xnumdt = tempi * -.21714724095162591;
    a2 = rmi * .07238241365054196;
    xnumdd = a2 * rmdd;
    xnumda = a2 * rmda;
    xnumdz = a2 * rmdz;
    xden = (cc - 24.5 + xlnt * 3.) * .16666666666666666;
    xdendt = tempi * .21714724095162591;
    xdendd = a2 * rmdd;
    xdenda = a2 * rmda;
    xdendz = a2 * rmdz;
/* ..equation 4.11 */
    if (abs(xnum) > .7 || xden < 0.) {
	fxy = 1.;
	fxydt = 0.;
	fxydd = 0.;
	fxydz = 0.;
	fxyda = 0.;
    } else {
	a1 = .39 - xnum * 1.25 - sin(xnum * 4.5) * .35;
	a2 = -1.25 - cos(xnum * 4.5) * 1.575;
/* Computing 2nd power */
	d__1 = xnum * 4.5 + .9;
	b1 = exp(d__1 * d__1 * -1.) * .3;
	b2 = -b1 * 2. * (xnum * 4.5 + .9) * 4.5;
/* Computing MIN */
	d__1 = 0., d__2 = xden - 1.6 + xnum * 1.25;
	c__ = min(d__1,d__2);
	if (c__ == 0.f) {
	    dumdt = 0.;
	    dumdd = 0.;
	    dumda = 0.;
	    dumdz = 0.;
	} else {
	    dumdt = xdendt + xnumdt * 1.25;
	    dumdd = xdendd + xnumdd * 1.25;
	    dumda = xdenda + xnumda * 1.25;
	    dumdz = xdendz + xnumdz * 1.25;
	}
	d__ = .57 - xnum * .25;
	a3 = c__ / d__;
/* Computing 2nd power */
	d__1 = a3;
	c00 = exp(d__1 * d__1 * -1.);
	f1 = -c00 * 2. * a3 / d__;
	c01 = f1 * (dumdt + a3 * .25 * xnumdt);
	c02 = f1 * (dumdd + a3 * .25 * xnumdd);
	c03 = f1 * (dumda + a3 * .25 * xnumda);
	c04 = f1 * (dumdz + a3 * .25 * xnumdz);
	fxy = (a1 - b1) * c00 + 1.05;
	fxydt = (a2 * xnumdt - b2 * xnumdt) * c00 + (a1 - b1) * c01;
	fxydd = (a2 * xnumdd - b2 * xnumdd) * c00 + (a1 - b1) * c02;
	fxyda = (a2 * xnumda - b2 * xnumda) * c00 + (a1 - b1) * c03;
	fxydz = (a2 * xnumdz - b2 * xnumdz) * c00 + (a1 - b1) * c04;
    }
/* ..equation 4.1 and 4.5 */
    splas = (ft + fl) * fxy;
    splasdt = (ftdt + fldt) * fxy + (ft + fl) * fxydt;
    splasdd = (ftdd + fldd) * fxy + (ft + fl) * fxydd;
    splasda = (ftda + flda) * fxy + (ft + fl) * fxyda;
    splasdz = (ftdz + fldz) * fxy + (ft + fl) * fxydz;
    a2 = exp(-gl);
    a3 = a2 * -.5 * gl * gum;
    a1 = splas;
    splas = a2 * a1;
    splasdt = a2 * splasdt + a3 * gl2dt * a1;
    splasdd = a2 * splasdd + a3 * gl2dd * a1;
    splasda = a2 * splasda + a3 * gl2da * a1;
    splasdz = a2 * splasdz + a3 * gl2dz * a1;
    a2 = gl6;
    a3 = gl6 * 3. * gum;
    a1 = splas;
    splas = a2 * a1;
    splasdt = a2 * splasdt + a3 * gl2dt * a1;
    splasdd = a2 * splasdd + a3 * gl2dd * a1;
    splasda = a2 * splasda + a3 * gl2da * a1;
    splasdz = a2 * splasdz + a3 * gl2dz * a1;
    a2 = xl9 * 2.7945899999999998e21;
    a3 = xl8 * 2.515131e22 * xldt;
    a1 = splas;
    splas = a2 * a1;
    splasdt = a2 * splasdt + a3 * a1;
    splasdd = a2 * splasdd;
    splasda = a2 * splasda;
    splasdz = a2 * splasdz;
/* ..photoneutrino process section */
/* ..for reactions like e- + gamma => e- + nu_e + nubar_e */
/* ..                   e+ + gamma => e+ + nu_e + nubar_e */
/* ..equation 3.8 for tau, equation 3.6 for cc, */
/* ..and table 2 written out for speed */
    if (*temp >= 1e7 && *temp < 1e8) {
	d__1 = *temp * 1e-7;
	tau = d_lg10(&d__1);
	cc = tau + .5654;
	c00 = 1.008e11;
	c01 = 0.;
	c02 = 0.;
	c03 = 0.;
	c04 = 0.;
	c05 = 0.;
	c06 = 0.;
	c10 = 8.156e10;
	c11 = 9.728e8;
	c12 = -3.806e9;
	c13 = -4.384e9;
	c14 = -5.774e9;
	c15 = -5.249e9;
	c16 = -5.153e9;
	c20 = 1.067e11;
	c21 = -9.782e9;
	c22 = -7.193e9;
	c23 = -6.936e9;
	c24 = -6.893e9;
	c25 = -7.041e9;
	c26 = -7.193e9;
	dd01 = 0.;
	dd02 = 0.;
	dd03 = 0.;
	dd04 = 0.;
	dd05 = 0.;
	dd11 = -1.879e10;
	dd12 = -9.667e9;
	dd13 = -5.602e9;
	dd14 = -3.37e9;
	dd15 = -1.825e9;
	dd21 = -2.919e10;
	dd22 = -1.185e10;
	dd23 = -7.27e9;
	dd24 = -4.222e9;
	dd25 = -1.56e9;
    } else if (*temp >= 1e8 && *temp < 1e9) {
	d__1 = *temp * 1e-8;
	tau = d_lg10(&d__1);
	cc = 1.5654;
	c00 = 9.889e10;
	c01 = -4.524e8;
	c02 = -6.088e6;
	c03 = 4.269e7;
	c04 = 5.172e7;
	c05 = 4.91e7;
	c06 = 4.388e7;
	c10 = 1.813e11;
	c11 = -7.556e9;
	c12 = -3.304e9;
	c13 = -1.031e9;
	c14 = -1.764e9;
	c15 = -1.851e9;
	c16 = -1.928e9;
	c20 = 9.75e10;
	c21 = 3.484e10;
	c22 = 5.199e9;
	c23 = -1.695e9;
	c24 = -2.865e9;
	c25 = -3.395e9;
	c26 = -3.418e9;
	dd01 = -1.135e8;
	dd02 = 1.256e8;
	dd03 = 5.149e7;
	dd04 = 3.436e7;
	dd05 = 1.005e7;
	dd11 = 1.652e9;
	dd12 = -3.119e9;
	dd13 = -1.839e9;
	dd14 = -1.458e9;
	dd15 = -8.956e8;
	dd21 = -1.549e10;
	dd22 = -9.338e9;
	dd23 = -5.899e9;
	dd24 = -3.035e9;
	dd25 = -1.598e9;
    } else if (*temp >= 1e9) {
	tau = d_lg10(&t9);
	cc = 1.5654;
	c00 = 9.581e10;
	c01 = 4.107e8;
	c02 = 2.305e8;
	c03 = 2.236e8;
	c04 = 1.58e8;
	c05 = 2.165e8;
	c06 = 1.721e8;
	c10 = 1.459e12;
	c11 = 1.314e11;
	c12 = -1.169e11;
	c13 = -1.765e11;
	c14 = -1.867e11;
	c15 = -1.983e11;
	c16 = -1.896e11;
	c20 = 2.424e11;
	c21 = -3.669e9;
	c22 = -8.691e9;
	c23 = -7.967e9;
	c24 = -7.932e9;
	c25 = -7.987e9;
	c26 = -8.333e9;
	dd01 = 4.724e8;
	dd02 = 2.976e8;
	dd03 = 2.242e8;
	dd04 = 7.937e7;
	dd05 = 4.859e7;
	dd11 = -7.094e11;
	dd12 = -3.697e11;
	dd13 = -2.189e11;
	dd14 = -1.273e11;
	dd15 = -5.705e10;
	dd21 = -2.254e10;
	dd22 = -1.551e10;
	dd23 = -7.793e9;
	dd24 = -4.489e9;
	dd25 = -2.185e9;
    }
    taudt = tempi * .4342944819032518;
/* ..equation 3.7, compute the expensive trig functions only one time */
    cos1 = cos(tau * 5.2359877559829888);
    cos2 = cos(tau * 10.471975511965978);
    cos3 = cos(tau * 15.707963267948966);
    cos4 = cos(tau * 20.943951023931955);
    cos5 = cos(tau * 26.179938779914945);
    last = cos(tau * 31.415926535897931);
    sin1 = sin(tau * 5.2359877559829888);
    sin2 = sin(tau * 10.471975511965978);
    sin3 = sin(tau * 15.707963267948966);
    sin4 = sin(tau * 20.943951023931955);
    sin5 = sin(tau * 26.179938779914945);
    xast = sin(tau * 31.415926535897931);
    a0 = c00 * .5 + c01 * cos1 + dd01 * sin1 + c02 * cos2 + dd02 * sin2 + c03 
	    * cos3 + dd03 * sin3 + c04 * cos4 + dd04 * sin4 + c05 * cos5 + 
	    dd05 * sin5 + c06 * .5 * last;
    f0 = taudt * 5.2359877559829888 * (-c01 * sin1 + dd01 * cos1 - c02 * sin2 
	    * 2. + dd02 * cos2 * 2. - c03 * sin3 * 3. + dd03 * cos3 * 3. - 
	    c04 * sin4 * 4. + dd04 * cos4 * 4. - c05 * sin5 * 5. + dd05 * 
	    cos5 * 5.) - c06 * .5 * xast * 31.415926535897931 * taudt;
    a1 = c10 * .5 + c11 * cos1 + dd11 * sin1 + c12 * cos2 + dd12 * sin2 + c13 
	    * cos3 + dd13 * sin3 + c14 * cos4 + dd14 * sin4 + c15 * cos5 + 
	    dd15 * sin5 + c16 * .5 * last;
    f1 = taudt * 5.2359877559829888 * (-c11 * sin1 + dd11 * cos1 - c12 * sin2 
	    * 2. + dd12 * cos2 * 2. - c13 * sin3 * 3. + dd13 * cos3 * 3. - 
	    c14 * sin4 * 4. + dd14 * cos4 * 4. - c15 * sin5 * 5. + dd15 * 
	    cos5 * 5.) - c16 * .5 * xast * 31.415926535897931 * taudt;
    a2 = c20 * .5 + c21 * cos1 + dd21 * sin1 + c22 * cos2 + dd22 * sin2 + c23 
	    * cos3 + dd23 * sin3 + c24 * cos4 + dd24 * sin4 + c25 * cos5 + 
	    dd25 * sin5 + c26 * .5 * last;
    f2 = taudt * 5.2359877559829888 * (-c21 * sin1 + dd21 * cos1 - c22 * sin2 
	    * 2. + dd22 * cos2 * 2. - c23 * sin3 * 3. + dd23 * cos3 * 3. - 
	    c24 * sin4 * 4. + dd24 * cos4 * 4. - c25 * sin5 * 5. + dd25 * 
	    cos5 * 5.) - c26 * .5 * xast * 31.415926535897931 * taudt;
/* ..equation 3.4 */
    dum = a0 + a1 * zeta + a2 * zeta2;
    dumdt = f0 + f1 * zeta + a1 * zetadt + f2 * zeta2 + a2 * 2. * zeta * 
	    zetadt;
    dumdd = a1 * zetadd + a2 * 2. * zeta * zetadd;
    dumda = a1 * zetada + a2 * 2. * zeta * zetada;
    dumdz = a1 * zetadz + a2 * 2. * zeta * zetadz;
    z__ = exp(-cc * zeta);
    xnum = dum * z__;
    xnumdt = dumdt * z__ - dum * z__ * cc * zetadt;
    xnumdd = dumdd * z__ - dum * z__ * cc * zetadd;
    xnumda = dumda * z__ - dum * z__ * cc * zetada;
    xnumdz = dumdz * z__ - dum * z__ * cc * zetadz;
    xden = zeta3 + xlm1 * .00629 + xlm2 * .007483 + xlm3 * 3.061e-4;
    dum = zeta2 * 3.;
    xdendt = dum * zetadt - xldt * (xlm2 * .00629 + xlm3 * .014966 + xlm4 * 
	    9.1830000000000004e-4);
    xdendd = dum * zetadd;
    xdenda = dum * zetada;
    xdendz = dum * zetadz;
    dum = 1. / xden;
    fphot = xnum * dum;
    fphotdt = (xnumdt - fphot * xdendt) * dum;
    fphotdd = (xnumdd - fphot * xdendd) * dum;
    fphotda = (xnumda - fphot * xdenda) * dum;
    fphotdz = (xnumdz - fphot * xdendz) * dum;
/* ..equation 3.3 */
    a0 = xl * 2.045 + 1.;
    xnum = pow_dd(&a0, &c_b5) * .666;
    xnumdt = xnum * -2.066 / a0 * 2.045 * xldt;
    dum = xl * 1.875e8 + xl2 * 1.653e8 + xl3 * 8.449e8 - xl4 * 1.604e8;
    dumdt = xldt * (xl * 3.306e8 + 1.875e8 + xl2 * 2.5347e9 - xl3 * 6.416e8);
    z__ = 1. / dum;
    xden = rm * z__ + 1.;
    xdendt = -rm * z__ * z__ * dumdt;
    xdendd = rmdd * z__;
    xdenda = rmda * z__;
    xdendz = rmdz * z__;
    z__ = 1. / xden;
    qphot = xnum * z__;
    qphotdt = (xnumdt - qphot * xdendt) * z__;
    dum = -qphot * z__;
    qphotdd = dum * xdendd;
    qphotda = dum * xdenda;
    qphotdz = dum * xdendz;
/* ..equation 3.2 */
    sphot = xl5 * fphot;
    sphotdt = xl4 * 5. * xldt * fphot + xl5 * fphotdt;
    sphotdd = xl5 * fphotdd;
    sphotda = xl5 * fphotda;
    sphotdz = xl5 * fphotdz;
    a1 = sphot;
    sphot = rm * a1;
    sphotdt = rm * sphotdt;
    sphotdd = rm * sphotdd + rmdd * a1;
    sphotda = rm * sphotda + rmda * a1;
    sphotdz = rm * sphotdz + rmdz * a1;
    a1 = (1. - qphot * -.78408808942077868) * .84076566000000008;
    a2 = .65923434000000003;
    a3 = sphot;
    sphot = a1 * a3;
    sphotdt = a1 * sphotdt + a2 * qphotdt * a3;
    sphotdd = a1 * sphotdd + a2 * qphotdd * a3;
    sphotda = a1 * sphotda + a2 * qphotda * a3;
    sphotdz = a1 * sphotdz + a2 * qphotdz * a3;
    if (sphot <= 0.f) {
	sphot = 0.;
	sphotdt = 0.;
	sphotdd = 0.;
	sphotda = 0.;
	sphotdz = 0.;
    }
/* ..bremsstrahlung neutrino section */
/* ..for reactions like e- + (z,a) => e- + (z,a) + nu + nubar */
/* ..                   n  + n     => n + n + nu + nubar */
/* ..                   n  + p     => n + p + nu + nubar */
/* ..equation 4.3 */
    den6 = *den * 1e-6;
    t8 = *temp * 1e-8;
    t812 = sqrt(t8);
    t832 = t8 * t812;
    t82 = t8 * t8;
    t83 = t82 * t8;
    t85 = t82 * t83;
    t86 = t85 * t8;
    t8m1 = 1. / t8;
    t8m2 = t8m1 * t8m1;
    t8m3 = t8m2 * t8m1;
    t8m5 = t8m3 * t8m2;
    t8m6 = t8m5 * t8m1;
    d__1 = den6 * ye;
    tfermi = (sqrt(pow_dd(&d__1, &c_b4) * 1.018 + 1.) - 1.) * 5.9302e9;
/* .."weak" degenerate electrons only */
    if (*temp > tfermi * .01) {
/* ..equation 5.3 */
	dum = t832 * 7.05e6 + t83 * 51200.;
	dumdt = (t812 * 1.0575e7 + t82 * 153600.) * 1e-8;
	z__ = 1. / dum;
	eta = rm * z__;
	etadt = -rm * z__ * z__ * dumdt;
	etadd = rmdd * z__;
	etada = rmda * z__;
	etadz = rmdz * z__;
	etam1 = 1. / eta;
	etam2 = etam1 * etam1;
	etam3 = etam2 * etam1;
/* ..equation 5.2 */
	a0 = t8m2 * 68300. + 23.5 + t8m5 * 7.81e8;
	f0 = (t8m3 * -136600. - t8m6 * 3.905e9) * 1e-8;
	xnum = 1. / a0;
	dum = etam1 * 1.47 + 1. + etam2 * .0329;
	z__ = etam2 * -1.47 - etam3 * .065799999999999997;
	dumdt = z__ * etadt;
	dumdd = z__ * etadd;
	dumda = z__ * etada;
	dumdz = z__ * etadz;
	c00 = (etam1 + 1.) * 1.26;
	z__ = etam2 * -1.26;
	c01 = z__ * etadt;
	c02 = z__ * etadd;
	c03 = z__ * etada;
	c04 = z__ * etadz;
	z__ = 1. / dum;
	xden = c00 * z__;
	xdendt = (c01 - xden * dumdt) * z__;
	xdendd = (c02 - xden * dumdd) * z__;
	xdenda = (c03 - xden * dumda) * z__;
	xdendz = (c04 - xden * dumdz) * z__;
	fbrem = xnum + xden;
	fbremdt = -xnum * xnum * f0 + xdendt;
	fbremdd = xdendd;
	fbremda = xdenda;
	fbremdz = xdendz;
/* ..equation 5.9 */
	a0 = t8m2 * 6.7e5 + 230. + t8m5 * 7.66e9;
	f0 = (t8m3 * -1.34e6 - t8m6 * 3.83e10) * 1e-8;
	z__ = rm * 1e-9 + 1.;
	dum = a0 * z__;
	dumdt = f0 * z__;
	z__ = a0 * 1e-9;
	dumdd = z__ * rmdd;
	dumda = z__ * rmda;
	dumdz = z__ * rmdz;
	xnum = 1. / dum;
	z__ = -xnum * xnum;
	xnumdt = z__ * dumdt;
	xnumdd = z__ * dumdd;
	xnumda = z__ * dumda;
	xnumdz = z__ * dumdz;
	c00 = t832 * 7.75e5 + pow_dd(&t8, &c_b7) * 247.;
	dd00 = (t812 * 1162500. + pow_dd(&t8, &c_b8) * 950.95000000000005) * 
		1e-8;
	c01 = pow_dd(&t8, &c_b9) * .024 + 4.07;
	dd01 = pow_dd(&t8, &c_b10) * .033599999999999998 * 1e-8;
	c02 = pow_dd(&t8, &c_b11) * 4.59e-5;
	dd02 = pow_dd(&t8, &c_b12) * -5.0489999999999994e-6 * 1e-8;
	z__ = pow_dd(den, &c_b13);
	dum = c00 * rmi + c01 + c02 * z__;
	dumdt = dd00 * rmi + dd01 + dd02 * z__;
	z__ = -c00 * rmi * rmi;
	dumdd = z__ * rmdd + c02 * .656 * pow_dd(den, &c_b14);
	dumda = z__ * rmda;
	dumdz = z__ * rmdz;
	xden = 1. / dum;
	z__ = -xden * xden;
	xdendt = z__ * dumdt;
	xdendd = z__ * dumdd;
	xdenda = z__ * dumda;
	xdendz = z__ * dumdz;
	gbrem = xnum + xden;
	gbremdt = xnumdt + xdendt;
	gbremdd = xnumdd + xdendd;
	gbremda = xnumda + xdenda;
	gbremdz = xnumdz + xdendz;
/* ..equation 5.1 */
	dum = *zbar * .5738 * ye * t86 * *den;
	dumdt = *zbar * .5738 * ye * 6. * t85 * *den * 1e-8;
	dumdd = *zbar * .5738 * ye * t86;
	dumda = -dum * abari;
	dumdz = ye * 1.1476 * t86 * *den;
	z__ = fbrem * .84076566000000008 - gbrem * -.65923434000000003;
	sbrem = dum * z__;
	sbremdt = dumdt * z__ + dum * (fbremdt * .84076566000000008 - gbremdt 
		* -.65923434000000003);
	sbremdd = dumdd * z__ + dum * (fbremdd * .84076566000000008 - gbremdd 
		* -.65923434000000003);
	sbremda = dumda * z__ + dum * (fbremda * .84076566000000008 - gbremda 
		* -.65923434000000003);
	sbremdz = dumdz * z__ + dum * (fbremdz * .84076566000000008 - gbremdz 
		* -.65923434000000003);
/* ..liquid metal with c12 parameters (not too different for other elements) */
/* ..equation 5.18 and 5.16 */
    } else {
	u = (d_lg10(den) - 3.) * .62831853071795862;
	a0 = deni * .27287527076836826;
/* ..compute the expensive trig functions of equation 5.21 only once */
	cos1 = cos(u);
	cos2 = cos(u * 2.);
	cos3 = cos(u * 3.);
	cos4 = cos(u * 4.);
	cos5 = cos(u * 5.);
	sin1 = sin(u);
	sin2 = sin(u * 2.);
	sin3 = sin(u * 3.);
	sin4 = sin(u * 4.);
	sin5 = sin(u * 5.);
/* ..equation 5.21 */
	fb = u * .00945 + .089730000000000004 + .34529 - cos1 * .05821 - sin1 
		* .04969 - cos2 * .01089 - sin2 * .01584 - cos3 * .01147 - 
		sin3 * .00504 - cos4 * .00656 - sin4 * .00281 - cos5 * .00519;
	c00 = a0 * (sin1 * .05821 + .00945 - cos1 * .04969 + sin2 * .01089 * 
		2. - cos2 * .01584 * 2. + sin3 * .01147 * 3. - cos3 * .00504 *
		 3. + sin4 * .00656 * 4. - cos4 * .00281 * 4. + sin5 * .00519 
		* 5.);
/* ..equation 5.22 */
	ft = .033904999999999998 - u * .02342 + .24819 - cos1 * .00944 - sin1 
		* .02213 - cos2 * .01289 - sin2 * .01136 - cos3 * .00589 - 
		sin3 * .00467 - cos4 * .00404 - sin4 * .00131 - cos5 * .0033;
	c01 = a0 * (sin1 * .00944 - .02342 - cos1 * .02213 + sin2 * .01289 * 
		2. - cos2 * .01136 * 2. + sin3 * .00589 * 3. - cos3 * .00467 *
		 3. + sin4 * .00404 * 4. - cos4 * .00131 * 4. + sin5 * .0033 *
		 5.);
/* ..equation 5.23 */
	gb = .0038300000000000001 - u * .01259 + .07917 - cos1 * .0071 + sin1 
		* .023 - cos2 * 2.8e-4 - sin2 * .01078 + cos3 * .00232 + sin3 
		* .00118 + cos4 * 4.4e-4 - sin4 * 8.9e-4 + cos5 * .00158;
	c02 = a0 * (sin1 * .0071 - .01259 + cos1 * .023 + sin2 * 2.8e-4 * 2. 
		- cos2 * .01078 * 2. - sin3 * .00232 * 3. + cos3 * .00118 * 
		3. - sin4 * 4.4e-4 * 4. - cos4 * 8.9e-4 * 4. - sin5 * .00158 *
		 5.);
/* ..equation 5.24 */
	gt = -.0038449999999999999 - u * .00829 + .05211 + cos1 * .00356 + 
		sin1 * .01052 - cos2 * .00184 - sin2 * .00354 + cos3 * .00146 
		- sin3 * 1.4e-4 + cos4 * 3.1e-4 - sin4 * 1.8e-4 + cos5 * 
		6.9e-4;
	c03 = a0 * (-.00829 - sin1 * .00356 + cos1 * .01052 + sin2 * .00184 * 
		2. - cos2 * .00354 * 2. - sin3 * .00146 * 3. - cos3 * 1.4e-4 *
		 3. - sin4 * 3.1e-4 * 4. - cos4 * 1.8e-4 * 4. - sin5 * 6.9e-4 
		* 5.);
	d__1 = den6 * abari;
	dum = *zbar * .2275 * *zbar * t8m1 * pow_dd(&d__1, &c_b2);
	dumdt = -dum * tempi;
	dumdd = dum * .33333333333333331 * deni;
	dumda = dum * -.33333333333333331 * abari;
	dumdz = dum * 2. * zbari;
	gm1 = 1. / dum;
	gm2 = gm1 * gm1;
	gm13 = pow_dd(&gm1, &c_b2);
	gm23 = gm13 * gm13;
	gm43 = gm13 * gm1;
	gm53 = gm23 * gm1;
/* ..equation 5.25 and 5.26 */
	v = -.05483 - gm13 * .01946 + gm23 * 1.8631 - gm1 * .78873;
	a0 = gm43 * .0064866666666666666 - gm53 * 1.2420666666666667 + gm2 * 
		.78873;
	w = gm13 * .06859 - .06711 + gm23 * 1.7436 - gm1 * .74498;
	a1 = gm43 * -.022863333333333333 - gm53 * 1.1623999999999999 + gm2 * 
		.74498;
/* ..equation 5.19 and 5.20 */
	fliq = v * fb + (1. - v) * ft;
	fliqdt = a0 * dumdt * (fb - ft);
	fliqdd = a0 * dumdd * (fb - ft) + v * c00 + (1. - v) * c01;
	fliqda = a0 * dumda * (fb - ft);
	fliqdz = a0 * dumdz * (fb - ft);
	gliq = w * gb + (1. - w) * gt;
	gliqdt = a1 * dumdt * (gb - gt);
	gliqdd = a1 * dumdd * (gb - gt) + w * c02 + (1. - w) * c03;
	gliqda = a1 * dumda * (gb - gt);
	gliqdz = a1 * dumdz * (gb - gt);
/* ..equation 5.17 */
	dum = *zbar * .5738 * ye * t86 * *den;
	dumdt = *zbar * .5738 * ye * 6. * t85 * *den * 1e-8;
	dumdd = *zbar * .5738 * ye * t86;
	dumda = -dum * abari;
	dumdz = ye * 1.1476 * t86 * *den;
	z__ = fliq * .84076566000000008 - gliq * -.65923434000000003;
	sbrem = dum * z__;
	sbremdt = dumdt * z__ + dum * (fliqdt * .84076566000000008 - gliqdt * 
		-.65923434000000003);
	sbremdd = dumdd * z__ + dum * (fliqdd * .84076566000000008 - gliqdd * 
		-.65923434000000003);
	sbremda = dumda * z__ + dum * (fliqda * .84076566000000008 - gliqda * 
		-.65923434000000003);
	sbremdz = dumdz * z__ + dum * (fliqdz * .84076566000000008 - gliqdz * 
		-.65923434000000003);
    }
/* ..recombination neutrino section */
/* ..for reactions like e- (continuum) => e- (bound) + nu_e + nubar_e */
/* ..equation 6.11 solved for nu */
    xnum = *den * 1.1052e8 * ye / (*temp * sqrt(*temp));
    xnumdt = xnum * -1.5 * tempi;
    xnumdd = xnum * deni;
    xnumda = -xnum * abari;
    xnumdz = xnum * zbari;
/* ..the chemical potential */
    nu = ifermi12_(&xnum);
/* ..a0 is d(nu)/d(xnum) */
    a0 = 1. / (zfermim12_(&nu) * .5);
    nudt = a0 * xnumdt;
    nudd = a0 * xnumdd;
    nuda = a0 * xnumda;
    nudz = a0 * xnumdz;
    nu2 = nu * nu;
    nu3 = nu2 * nu;
/* ..table 12 */
    if (nu >= -20.f && nu < 0.f) {
	a1 = .0151;
	a2 = .242;
	a3 = 1.21;
	b = .0371;
	c__ = .906f;
	d__ = .928;
	f1 = 0.;
	f2 = 0.;
	f3 = 0.;
    } else if (nu >= 0.f && nu <= 10.f) {
	a1 = .0123;
	a2 = .266;
	a3 = 1.3;
	b = .117;
	c__ = .897f;
	d__ = .177;
	f1 = -.012;
	f2 = .0229;
	f3 = -.00104;
    }
/* ..equation 6.7, 6.13 and 6.14 */
    if (nu >= -20.f && nu <= 10.f) {
	zeta = *zbar * 157900. * *zbar * tempi;
	zetadt = -zeta * tempi;
	zetadd = 0.;
	zetada = 0.;
	zetadz = zeta * 2. * zbari;
	c00 = 1. / (f1 * nu + 1. + f2 * nu2 + f3 * nu3);
	c01 = f1 + f2 * 2. * nu + f3 * 3. * nu2;
	dum = zeta * c00;
	dumdt = zetadt * c00 + zeta * c01 * nudt;
	dumdd = zeta * c01 * nudd;
	dumda = zeta * c01 * nuda;
	dumdz = zetadz * c00 + zeta * c01 * nudz;
	z__ = 1. / dum;
	dd00 = pow_dd(&dum, &c_b17);
	dd01 = pow_dd(&dum, &c_b18);
	c00 = a1 * z__ + a2 * dd00 + a3 * dd01;
	c01 = -(a1 * z__ + a2 * 2.25f * dd00 + a3 * 4.55f * dd01) * z__;
	z__ = exp(c__ * nu);
	dd00 = b * z__ * (d__ * dum + 1.);
	gum = dd00 + 1.;
	gumdt = dd00 * c__ * nudt + b * z__ * d__ * dumdt;
	gumdd = dd00 * c__ * nudd + b * z__ * d__ * dumdd;
	gumda = dd00 * c__ * nuda + b * z__ * d__ * dumda;
	gumdz = dd00 * c__ * nudz + b * z__ * d__ * dumdz;
	z__ = exp(nu);
	a1 = 1. / gum;
	bigj = c00 * z__ * a1;
	bigjdt = c01 * dumdt * z__ * a1 + c00 * z__ * nudt * a1 - c00 * z__ * 
		a1 * a1 * gumdt;
	bigjdd = c01 * dumdd * z__ * a1 + c00 * z__ * nudd * a1 - c00 * z__ * 
		a1 * a1 * gumdd;
	bigjda = c01 * dumda * z__ * a1 + c00 * z__ * nuda * a1 - c00 * z__ * 
		a1 * a1 * gumda;
	bigjdz = c01 * dumdz * z__ * a1 + c00 * z__ * nudz * a1 - c00 * z__ * 
		a1 * a1 * gumdz;
/* ..equation 6.5 */
	z__ = exp(zeta + nu);
	dum = z__ + 1.;
	a1 = 1. / dum;
	a2 = 1. / bigj;
/* Computing 13th power */
	d__1 = *zbar, d__2 = d__1, d__1 *= d__1, d__1 *= d__1, d__2 *= d__1;
	sreco = ye * 5.4477514666800008e-18 * (d__2 * (d__1 * d__1)) * *den * 
		bigj * a1;
	srecodt = sreco * (bigjdt * a2 - z__ * (zetadt + nudt) * a1);
	srecodd = sreco * (deni * 1. + bigjdd * a2 - z__ * (zetadd + nudd) * 
		a1);
	srecoda = sreco * (abari * -1. + bigjda * a2 - z__ * (zetada + nuda) *
		 a1);
	srecodz = sreco * (zbari * 14. + bigjdz * a2 - z__ * (zetadz + nudz) *
		 a1);
    }
/* ..convert from erg/cm^3/s to erg/g/s */
/* ..comment these out to duplicate the itoh et al plots */
    spair *= deni;
    spairdt *= deni;
    spairdd = spairdd * deni - spair * deni;
    spairda *= deni;
    spairdz *= deni;
    splas *= deni;
    splasdt *= deni;
    splasdd = splasdd * deni - splas * deni;
    splasda *= deni;
    splasdz *= deni;
    sphot *= deni;
    sphotdt *= deni;
    sphotdd = sphotdd * deni - sphot * deni;
    sphotda *= deni;
    sphotdz *= deni;
    sbrem *= deni;
    sbremdt *= deni;
    sbremdd = sbremdd * deni - sbrem * deni;
    sbremda *= deni;
    sbremdz *= deni;
    sreco *= deni;
    srecodt *= deni;
    srecodd = srecodd * deni - sreco * deni;
    srecoda *= deni;
    srecodz *= deni;
/* ..the total neutrino loss rate */
    *snu = splas + spair + sphot + sbrem + sreco;
    *dsnudt = splasdt + spairdt + sphotdt + sbremdt + srecodt;
    *dsnudd = splasdd + spairdd + sphotdd + sbremdd + srecodd;
    *dsnuda = splasda + spairda + sphotda + sbremda + srecoda;
    *dsnudz = splasdz + spairdz + sphotdz + sbremdz + srecodz;
    return 0;
} /* sneut_ */


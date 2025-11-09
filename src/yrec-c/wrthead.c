/* wrthead.f -- translated by f2c (version 20061008).
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
    doublereal rescal[200]	/* was [4][50] */;
    integer nmodls[50], iresca[50];
    logical lfirst[50];
    integer numrun;
} ckind_;

#define ckind_1 ckind_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk;
    logical lzramp;
} zramp_;

#define zramp_1 zramp_

struct {
    integer itrver;
} track_;

#define track_1 track_

struct {
    doublereal xenv0, zenv0;
} label_;

#define label_1 label_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    integer ifirst, irun, istand, ifermi, iopmod, iopenv, iopatm, idyn, 
	    illdat, isnu, iscomp, ikur;
} lunum_;

#define lunum_1 lunum_

struct {
    logical lrwsh, liso;
    integer iiso;
} chrone_;

#define chrone_1 chrone_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_

/* Table of constant values */

static integer c__1 = 1;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* WRTHEAD */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* write the headers for all the appropriate output files */
/* Subroutine */ int wrthead_(doublereal *smass)
{
    /* Format strings */
    static char fmt_47[] = "(/,\002 RUN=\002,i2,\002 EVOLVE  \002,\002 X="
	    "\002,f8.6,\002 Z=\002,f8.6,\002 CMIXL=\002,f8.6,\002 NO.MODS="
	    "\002,i5)";
    static char fmt_48[] = "(/,\002 RUN=\002,i2,\002 RESCALE \002,\002 X="
	    "\002,f8.6,\002 Z=\002,f8.6,\002 CMIXL=\002,f8.6,\002 NO.MODS="
	    "\002,i5)";
    static char fmt_49[] = "(/,\002 RUN=\002,i2,\002 RESCALE&EVOLVE \002,"
	    "\002 X=\002,f8.6,\002 Z=\002,f8.6,\002 CMIXL=\002,f8.6,\002 NO.M"
	    "ODS=\002,i5)";
    static char fmt_1495[] = "(7x,1p5e16.8)";
    static char fmt_1500[] = "(\002#Version=\002,i3,\002  Mtot/Msun =\002,1p"
	    "e16.8,\002  Initial: X =\002,1pe16.8,\002 Z =\002,1pe16.8,\002  "
	    "Mix. length =\002,1pe16.8)";
    static char fmt_1504[] = "(\002# \002,/,\002     Step    Shls         Ag"
	    "e_gyr       LogL_lsun       LogR_rsun           Log_g\002,\002  "
	    "      log_Teff        Mco_core         Mco_env     Rco_env     T"
	    "co_env     Dco_env\002,\002     Pco_env     Oco_env        LogT_"
	    "cen        LogD_cen        logP_cen        Beta_cen\002,\002    "
	    "     Eta_cen           X_cen           Y_cen           Z_cen    "
	    "    ppI_lsun\002,\002       ppII_lsun      ppIII_lsun        CNO"
	    "_lsun         3a_lsun        HeC_lsun\002,\002      Egrav_lsun  "
	    "     Neut_lsun    Cl_snu    Ga_snu   pp_neut  pep_neut  hep_neu"
	    "t\002,\002  Be7_neut   B8_neut  N13_neut  O15_neut  F17_neut    "
	    " diag1     diag2         He3_cen\002,\002         C12_cen       "
	    "  C13_cen         N14_cen         N15_cen         O16_cen\002"
	    ",\002         O17_cen         O18_cen         He3_sur         C1"
	    "2_sur         C13_sur\002,\002         N14_sur         N15_sur  "
	    "       O16_sur         O17_sur         O18_sur\002,\002         "
	    " H2_sur         Li6_sur         Li7_sur         Be9_sur         "
	    "  X_sur\002,\002           Y_sur           Z_sur         Z_X_sur"
	    "            Jtot      KE_rot_tot\002,\002           I_tot       "
	    "     I_cz       Omega_sur       Omega_cen      Prot_sur_d\002"
	    ",\002        Vrot_kms         TauCZ_s    MHshell_base     MHshel"
	    "l_mid     MHshell_top\002,\002    RHshell_base     RHShell_mid  "
	    "   RHshell_top       logP_phot       Mass_msun\002,/,\002# \002)";
    static char fmt_1505[] = "(\002# Model #, shells, AGE, log(L/Lsun), log("
	    "R/Rsun), log(g),\002,\002 log(Teff), Mconv. core, Mconv. env."
	    ")\002,/,\002# Central: log(T), log(RHO), log(P), BETA, ETA, X, Y"
	    ", Z\002,/,\002# Luminosity: ppI, ppII, ppIII, CNO, triple-alpha"
	    ",\002,\002 He-C, gravity, neutrinos (old)\002,/,\002 Neutrinos ("
	    "1E10 erg/CM^2 at earth): pp, pep, hep, Be7,\002,\002 B8, N13, O1"
	    "5, F17\002,/,\002# Central Abundances: He3, C12, C13, N14, N15, "
	    "O16,\002,\002 O17, O18\002,/,\002# Surface Abundances: He3, C12,"
	    " C13, N14, N15, O16,\002,\002 O17,O18\002,/,\002    \"        \""
	    " cont: H2, Li6, Li7, Be9\002,/,\002# H shell loc: mass frac-base"
	    ", midpoint, top; radius frac-\002,\002base, midpoint, top\002)";
    static char fmt_1510[] = "(\002 Jtot, K.E. Rotation, OMEGAsurf, OMEGAcen"
	    "ter\002)";
    static char fmt_1515[] = "(\002#Model #, shells, AGE, log(L/Lsun), log(R"
	    "/Rsun), log(g),\002,\002 log(Teff), Mconv. core, Mconv. env., % "
	    "Grav Energy, X env\002)";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal gmmass;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, fmt_47, 0 };
    static cilist io___2 = { 0, 0, 0, fmt_48, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_49, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_1495, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_1500, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_1504, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_1505, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_1505, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_1510, 0 };
    static cilist io___11 = { 0, 0, 0, fmt_1515, 0 };


/* MHP 8/25 Removed character file names from common block */
/* MHP 10/02 added proper dimensions for flaol2, fopal2 */
/*      CHARACTER*256 FISO,FLAOL2, FOPAL2 */
/* MHP 8/25 Removed character file names from common block */
/* MHP 8/25 Removed character file names from common block */
    if (ckind_1.iresca[zramp_1.nk - 1] == 1) {
	io___1.ciunit = luout_1.iowr;
	s_wsfe(&io___1);
	do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&label_1.xenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.zenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ckind_1.nmodls[zramp_1.nk - 1], (ftnlen)sizeof(
		integer));
	e_wsfe();
    } else if (ckind_1.iresca[zramp_1.nk - 1] == 2) {
	io___2.ciunit = luout_1.iowr;
	s_wsfe(&io___2);
	do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&label_1.xenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.zenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ckind_1.nmodls[zramp_1.nk - 1], (ftnlen)sizeof(
		integer));
	e_wsfe();
    } else if (ckind_1.iresca[zramp_1.nk - 1] == 3) {
	io___3.ciunit = luout_1.iowr;
	s_wsfe(&io___3);
	do_fio(&c__1, (char *)&zramp_1.nk, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&label_1.xenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.zenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ckind_1.nmodls[zramp_1.nk - 1], (ftnlen)sizeof(
		integer));
	e_wsfe();
    }
    if (chrone_1.liso) {
/* header stuff for isochrone output */
	gmmass = *smass * const_1.cmsun;
	io___5.ciunit = chrone_1.iiso;
	s_wsfe(&io___5);
	do_fio(&c__1, (char *)&gmmass, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.xenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.zenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&const_1.cmbol, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (ccout2_1.ltrack && ckind_1.lfirst[zramp_1.nk - 1]) {
/* ITRVER identifies version of track out file.  If you change */
/* the track out file then change this version number. */
	io___6.ciunit = luout_1.itrack;
	s_wsfe(&io___6);
	do_fio(&c__1, (char *)&track_1.itrver, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.xenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.zenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal));
	e_wsfe();
	if (track_1.itrver == 0) {
/*            WRITE(ITRACK, 1503) */
/* 1503       FORMAT( */
/*     1'# Model #, shells, AGE(Gyr), log(L/Lsun), log(R/Rsun), log(g),', */
/*     1' log(Teff), Mconv. core (Msun), Mconv. env, R,T,Rho,P,cappa env',/, */
/*     2'# Central: log(T), log(RHO), log(P), BETA, ETA, X, Y, Z',/, */
/*     3'# Luminosity: ppI, ppII, ppIII, CNO, triple-alpha,', */
/*     3' He-C, gravity, neutrinos (old)',/, */
/*     3'# Cl SNU, Ga SNU, Neutrinos (1E10 erg/CM^2 at earth): pp, pep, hep, Be7,', */
/*     3' B8, N13, O15, F17 2xdiagnostic',/, */
/*     4'# Central Abundances: He3, C12, C13, N14, N15, O16,', */
/*     4' O17, O18',/, */
/*     5'# Surface Abundances: He3, C12, C13, N14, N15, O16,', */
/*     5' O17,O18 H2, Li6, Li7, Be9 X Y Z Z/X',/, */
/*     6'# Jtot, KE rot tot, total I, CZ I, Omega center, surface, Prot (day), Vrot (km/s), TauCZ (sec) ',/, 
*/
/*     7'# H shell loc: mass frac-base, midpoint, top; radius frac-', */
/*     7'base, midpoint, top, Pphot, mass (msun)') */
/* G Somers 11/14; Added option to create .track file header. Uncomment the following */
/* block if desired. */
	    io___7.ciunit = luout_1.itrack;
	    s_wsfe(&io___7);
	    e_wsfe();
/* 1504       FORMAT( */
/*     1'# ',/, */
/*     2'#    Step    Shls     Age (Gyr)      log(L/Lsun)    log(R/Rsun)        log(g)        log(Teff)', */
/*     2'       Mconv.core      Mconv.env     Rcore     Tcore      Rho_core     P_core     kappa_env   ', */
/*     2' log(T)_cen     log(Rho)_cen     log(P)_cen        BETA             ETA            X_cen      ', */
/*     2'     Y_cen           Z_cen          ppI_lum         ppII_lum       ppIII_lum        CNO_lum   ', */
/*     2'    3-alpha_lum       He-C_lum        gravity       OLD NUTRINOS   Cl SNU    Ga SNU    **pp** ', */
/*     2'   **pep**   **hep**   **Be7**   **B8**    **N13**   **O15**   **F17**  **diag1** **diag2**   ', */
/*     2'   He3_cen        C12_cen         C13_cen         N14_cen         B10_cen         O16_cen     ', */
/*     2'    B11_cen         O18_cen         He3_surf        C12_surf        C13_surf        N14_surf  ', */
/*     2'      B10_surf        O16_surf        B11_surf        O18_surf        H2_surf         Li6_surf', */
/*     2'        Li7_surf        Be9_surf         X_surf          Y_surf          Z_surf         Z/X_su', */
/*     2'rf          Jtot         KE_rot_tot       total I           CZ I         Omega_surf      Omega', */
/*     2'_cen       Prot (days)     Vrot (km/s)     TauCZ (s)       Mfrac_base      Mfrac_midp      Mfr', */
/*     2'ac_top       Rfrac_base      Rfrac_midp      Rfrac_top         P_phot           Mass     ',/, */
/*     2'# ') */
/* G Somers END. */
	} else if (track_1.itrver == 1) {
	    io___8.ciunit = luout_1.itrack;
	    s_wsfe(&io___8);
	    e_wsfe();
	} else if (track_1.itrver == 2) {
	    io___9.ciunit = luout_1.itrack;
	    s_wsfe(&io___9);
	    e_wsfe();
	    io___10.ciunit = luout_1.itrack;
	    s_wsfe(&io___10);
	    e_wsfe();
	} else if (track_1.itrver == 3) {
	    io___11.ciunit = luout_1.itrack;
	    s_wsfe(&io___11);
	    e_wsfe();
	}
    }
    return 0;
} /* wrthead_ */


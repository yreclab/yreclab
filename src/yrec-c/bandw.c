/* bandw.f -- translated by f2c (version 20061008).
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

static integer c__1 = 1;

/* $$$$$$ */
/*       SUBROUTINE BANDW(A,NM,M1,M2,B)  ! KC 2025-05-31 */
/* Subroutine */ int bandw_(doublereal *a, integer *nm, doublereal *b)
{
    /* Format strings */
    static char fmt_911[] = "(i5,1p10e12.3)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, ii, jj, imj, imj5;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, fmt_911, 0 };
    static cilist io___8 = { 0, 6, 0, fmt_911, 0 };


/*       INTEGER*4 M1,M2,NM  ! KC 2025-05-31 */
/* INITIAL STEP: DIAGONALIZE TERMS INVOLVING OMEGA(1) */
/* AND THEN STEP THROUGH ITS FIRST THROUGH THIRD */
/* DERIVATIVES.  THEN PROCEED TO THE SECOND SHELL AND */
/* REPEAT, GOING TO THE BOTTOM.  THE REMAINDER OF THE */
/* TERMS CAN THEN BE REMOVED THROUGH BACKSUBSTITUTION. */
/*      DO I = 1,NM-5,4 */
/* INITIAL STEP: DIAGONALIZE OMEGA(II) TERM. */
/*         I1 = I+1 */
/*         I2 = I+2 */
/*         I3 = I+3 */
/*         I4 = I+4 */
/*         PIVOT = A(I,5) */
    /* Parameter adjustments */
    --b;
    a -= 8001;

    /* Function Body */
    i__1 = *nm - 5;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if ((d__1 = a[i__ + 40000], abs(d__1)) < 1e-20) {
	    s_wsfe(&io___2);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    for (j = 1; j <= 10; ++j) {
		do_fio(&c__1, (char *)&a[i__ + j * 8000], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	    s_stop("999", (ftnlen)3);
	}
	b[i__] /= a[i__ + 40000];
	for (j = 6; j <= 10; ++j) {
/*         DO J = 5,10 */
	    a[i__ + j * 8000] /= a[i__ + 40000];
	}
	i__2 = i__ + 4;
	for (j = i__ + 1; j <= i__2; ++j) {
	    imj = i__ - j;
	    imj5 = imj + 5;
/*            WRITE(*,*)I,J,IMJ5 */
	    b[j] -= a[j + imj5 * 8000] * b[i__];
	    i__3 = imj + 10;
	    for (k = imj5 + 1; k <= i__3; ++k) {
/*               WRITE(*,*)I,J,K,IMJ5,K+J-I */
		a[j + k * 8000] -= a[j + imj5 * 8000] * a[i__ + (k + j - i__) 
			* 8000];
	    }
	}
    }
    i__1 = *nm - 1;
    for (i__ = *nm - 4; i__ <= i__1; ++i__) {
	ii = *nm - i__;
	if ((d__1 = a[i__ + 40000], abs(d__1)) < 1e-20) {
	    s_wsfe(&io___8);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    for (j = 1; j <= 10; ++j) {
		do_fio(&c__1, (char *)&a[i__ + j * 8000], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	    s_stop("999", (ftnlen)3);
	}
	b[i__] /= a[i__ + 40000];
/*         WRITE(*,*)I,B(I),A(I,5) */
/*         DO J = 5,5+II */
	i__2 = ii + 5;
	for (j = 6; j <= i__2; ++j) {
	    a[i__ + j * 8000] /= a[i__ + 40000];
	}
/*         WRITE(*,*)I,(J,A(I,J),J=6,5+II) */
	i__2 = *nm;
	for (j = i__ + 1; j <= i__2; ++j) {
	    imj = i__ - j;
	    imj5 = imj + 5;
	    b[j] -= a[j + imj5 * 8000] * b[i__];
/*            WRITE(*,*)I,J,B(I),B(J),IMJ5,A(J,IMJ5) */
	    i__3 = imj5 + ii;
	    for (k = imj5 + 1; k <= i__3; ++k) {
		a[j + k * 8000] -= a[j + imj5 * 8000] * a[i__ + (k + j - i__) 
			* 8000];
/*               WRITE(*,*)I,J,K,A(J,K),IMJ5,A(J,IMJ5), */
/*     *                   K+J-I,A(I,K+J-I) */
	    }
	}
    }
    if ((d__1 = a[*nm + 40000], abs(d__1)) < 1e-20) {
	s_stop("999", (ftnlen)3);
    }
    b[*nm] /= a[*nm + 40000];
/*      WRITE(*,*)NM,B(NM),A(NM,5) */
/*      WRITE(*,912)((A(I,JJ),JJ=1,10),B(I),I=1,NM) */
/* 912  FORMAT(1P11E12.3) */
/* D2W/DR2 TERM */
/*         PIVOT = A(I+2,3) */
/*         B(I1) = B(I1) - A(I1,4)*B(I) */
/*         DO J = 5,9 */
/*         DO J = 4,9 */
/*            A(I1,J) = A(I1,J)-A(I1,4)*A(I,J+1) */
/*         END DO */
/* DW/DR (II) TERM */
/*         PIVOT = A(I+2,3) */
/*         B(I2) = B(I2)-A(I2,3)*B(I) */
/*         DO J = 4,8 */
/*         DO J = 3,8 */
/*            A(I2,J) = A(I2,J)-A(I2,3)*A(I,J+2) */
/*         END DO */
/* OMEGA(II+1) TERM */
/*         PIVOT = A(I+4,1) */
/*         B(I4) = B(I4)-A(I4,1)*B(I) */
/*         DO J = 1,6 */
/*         DO J = 2,6 */
/*            A(I4,J)= A(I4,J)-A(I4,1)*A(I,J+4) */
/*         END DO */
/* 3 NONZERO ENTRIES ABOVE I FOR THE NEXT TWO */
/* COLUMNS */
/*         DO J = I1,I2 */
/* DIAGONALIZE ROW */
/*         IF(ABS(A(J,5)).LT.TINY)THEN */
/*            WRITE(*,911)J,(A(J,K),K=1,10) */
/*            STOP999 */
/*         ENDIF */
/*            B(J)= B(J)/A(J,5) */
/*            K1 = 10 - J + I */
/*            DO K = 6,K1 */
/*            DO K = 5,K1 */
/*               A(J,K) = A(J,K)/A(J,5) */
/*            END DO */
/* CORRECT RHS */
/*            DO K = J+1,J+3 */
/*               K2 = 5 - K + J */
/*               B(K) = B(K) - A(K,K2)*B(J) */
/* CORRECT LHS */
/*               K3 = K2 + 1 */
/*               K4 = K3 + K1 - 6 */
/*               DO JJ = K3,K4 */
/*               DO JJ = K3-1,K4 */
/*                  A(K,JJ) = A(K,JJ)-A(K,K2)*A(J,JJ+K-J) */
/*                  A(K,JJ) = A(K,JJ)-A(K,K2)*A(J,6+JJ-K3) */
/*               END DO */
/*            END DO */
/*         END DO */
/* D3W/DR3 TERM */
/*         K1 = 7 */
/* CORRECT RHS */
/*         DO J = I3+1,I3+2 */
/*            K2 = 5 - J + I3 */
/*            B(J) = B(J) - A(J,K2)*B(I3) */
/* CORRECT LHS */
/*            K3 = K2 + 1 */
/*            DO JJ = K3,K3+1 */
/*            DO JJ = K3-1,K3+1 */
/*               A(J,JJ) = A(J,JJ) - A(J,K2)*A(I3,JJ+J-I3) */
/*            END DO */
/*         END DO */
/*      END DO */
/* FINAL 2 ENTRIES ARE A BIT SIMPLER. */
/*      NM1 = NM - 1 */
/*      IF(ABS(A(NM1,5)).LT.TINY)STOP999 */
/*      B(NM1) = B(NM1)/A(NM1,5) */
/*      A(NM1,6) = A(NM1,6)/A(NM1,5) */
/*      IF(ABS(A(NM,5)).LT.TINY)STOP999 */
/*      B(NM) = B(NM)/A(NM,5) */
/*      WRITE(*,912)((A(I,JJ),JJ=1,10),B(I),I=1,NM) */
/* 912  FORMAT(1P11E12.3) */
/* BACKSUBSTITUTION */
/*      DO I = NM,6,-4 */
    for (i__ = *nm; i__ >= 6; --i__) {
/* REMOVE ENTRIES IN LAST COLUMN */
/*         DO J = I-1,I-5,-1 */
/*            B(J) = B(J) - B(I)*A(J,5+I-J) */
	for (j = -1; j >= -5; --j) {
	    b[i__ + j] -= b[i__] * a[i__ + j + (5 - j) * 8000];
	}
/*         DO J = I-2,I-5,-1 */
/*            B(J) = B(J) - B(I-1)*A(J,4+I-J) */
/*         END DO */
/*         DO J = I-3,I-5,-1 */
/*            B(J) = B(J) - B(I-2)*A(J,3+I-J) */
/*         END DO */
/*         DO J = I-4,I-5,-1 */
/*            B(J) = B(J) - B(I-3)*A(J,2+I-J) */
/*         END DO */
/*         DO J = I,I-3,-1 */
/*            DO K = J-1,I-5,-1 */
/*               KK = 5 + I - K */
/*               B(K) = B(K)-B(J)*A(K,KK) */
/*            END DO */
/*         END DO */
    }
    for (i__ = 5; i__ >= 2; --i__) {
	jj = -(i__ - 1);
	i__1 = jj;
	for (j = -1; j >= i__1; --j) {
	    b[i__ + j] -= b[i__] * a[i__ + j + (5 - j) * 8000];
	}
    }
/*      B(1) = B(1) - B(2)*A(1,6) */
    return 0;
} /* bandw_ */


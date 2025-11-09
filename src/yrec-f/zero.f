C
C
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
C ZERO
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
      SUBROUTINE  ZERO(A,NN)
      IMPLICIT REAL*8 (A-H,O-Z)
C     SETS A(N)=0., N=1,NN
      DIMENSION A(NN)
      save

      DO 1 N=1,NN
C KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE"
C     1 A(N)=0.D0
         A(N)=0.D0
    1 CONTINUE
      RETURN
      END

NAME = model4.1.gfort

FFILES = \
alex06tab.c	alfilein.c     alprint.c	 alsurfp.c \
altabinit.c	alx8th.c       alxtbl.c		 alxztab.c \
bandw.c		blkdta000.c    bsrotmix.c	 bsstep.c \
bursmix.c	cases.c        ccoeft.c		 checkc.c \
checkj.c	chkcal.c       chkscal.c	 choose.c \
codiff.c	coefft.c       condopacp.c	 condopacpint.c \
convec.c	cowind.c       crrect.c		 cspline.c \
ctridi.c	dadcoeft.c     dburn.c		 dburnm.c \
dcoeft.c	deutrate.c     engeb.c		 envint.c \
eq2mod.c	eqbound01.c    eqbound06.c	 eqbound.c \
eqburn.c	eqrelv.c       eqsaha.c		 eqscve.c \
eqscvg.c	eqstat2.c      eqstat.c		 equal_to_model.c \
esac01.c	esac06.c       esac.c		 findex.c \
findsh.c	fpft.c	       func.c		 getalex06.c \
getfc.c		getgrid.c      get_imp_diffco.c  getmodel2.c \
getnewenv.c	getopac.c      getopal95.c	 getqua.c \
getrot.c	getw.c	       getyrec7.c	 gmass01.c \
gmass06.c	gmass.c        grsett.c		 gtlaol2.c \
gtlaol.c	gtpurz.c       hpoint.c		 hra.c \
hsolve.c	hsubp.c        htimer.c		 ifermi12.c \
inter3.c	interp.c       intmom.c		 intpol.c \
intpt.c		intrp2.c       kemcom.c		 kspline.c \
ksplint.c	kurucz2.c      kurucz.c		 lax_wendrof1.c \
lax_wendrof2.c	liburn2.c      liburn.c		 lirate88.c \
lir.c		ll4th.c        ll95tbl.c	 locate.c \
lubksb.c	ludcmp.c       main.c		 massloss.c \
mdot.c		meqos.c        meval.c		 mhdpx1.c \
mhdpx2.c	mhdpx.c        mhdst1.c		 mhdst.c \
mhdtbl.c	midmod.c       mixcom.c		 mixcz.c \
mix.c		mixgrid.c      mmid.c		 model_to_equal.c \
momi.c		mu.c	       ndifcom.c	 neutrino.c \
nulosses.c	oeqos01.c      oeqos06.c	 oeqos.c \
op952d.c	op953d.c       op954d.c		 op95xtab.c \
op95ztab.c	osplin.c       oversh.c		 ovrot.c \
parmin.c	pdist.c        physic.c		 pindex.c \
polint.c	ptime.c        putmodel2.c	 putyrec7.c \
qatm.c		qenv.c	       qgauss.c		 quadeos01.c \
quadeos06.c	quad.c	       quint.c		 rabu.c \
radsub01.c	radsub06.c     radsub.c		 rates.c \
ratext.c	rdlaol.c       rdzlaol.c	 readalex06.c \
readcoeos01.c	readcoeos06.c  readco.c		 reduce.c \
rhoofp01.c	rhoofp06.c     rhoofp.c		 rotgrid.c \
rotmix.c	rscale.c       rtab.c		 sconvec.c \
search.c	seculr.c       setcal.c		 setkrz.c \
setllo.c	setscal.c      setscv.c		 setup_grsett.c \
setupopac.c	setups.c       setupv.c		 shape.c \
simeqc.c	slopes.c       sneut.c		 solid.c \
splinc.c	spline.c       splintd2.c	 splint.c \
starin.c	sulaol.c       surfbc.c		 surfopac.c \
surfp.c		t6rinteos01.c  t6rinteos06.c	 t6rinterp.c \
thdiff.c	tpgrad.c       trapzd.c		 tridia.c \
tridiag_gs.c	vcirc.c        viscos.c		 wcz.c \
wind.c		wrthead.c      wrtlst.c		 wrtmil.c \
wrtmod.c	wrtmonte.c     wrtout.c		 wtime.c \
xrng4.c		xtime.c        yalo3d.c		 ykoeff.c \
yllo2d2.c	yllo2d.c       yllo3d2.c	 yllo3d.c \
ylloc.c		ysplin.c       ytime.c		 zero.c \
zfermim12.c	zsulaol.c

libf2cFiles = \
c_abs c_div c_sqrt cabs \
close ctype d_cnjg d_imag \
d_lg10 d_sign endfile err exit_ f77_aloc \
fmt fmtlib i_dnnt i_nint open \
pow_ci pow_dd pow_di pow_ii pow_ri pow_zi \
r_cnjg r_imag r_lg10 r_sign \
s_cat s_cmp s_copy \
sfe sig_die util wsfe wref wrtfmt \
z_abs z_div z_sqrt \

lapackFiles = \
chla_transtype dgbtf2 dgebd2 \
dgehd2 dgelq2 dgeql2 dgeqr2 dgerq2 \
dgesc2 dgetc2 dgetf2 dgsvj0 dgsvj1 \
dgtts2 disnan dlabad dlabrd dlacn2 \
dlacpy dladiv dlae2 dlaebz dlaed0 \
dlaed1 dlaed2 dlaed3 dlaed5 dlaed6 \
dlaed4 dlaed7 dlaed8 dlaed9 dlaeda \
dlaein dlaev2 dlaexc dlag2 dlags2 \
dlagtf dlagtm dlagts dlagv2 dlahqr \
dlahr2 dlaic1 dlaisnan dlaln2 dlals0 \
dlalsa dlalsd dlamrg dlaneg dlangb \
dlange dlangt dlanhs dlansb dlansp \
dlanst dlansy dlantb dlantp dlantr \
dlanv2 dlapll dlapmt dlapy2 dlapy3 \
dlaqgb dlaqge dlaqp2 dlaqps dlaqr0 \
dlaqr1 dlaqr2 dlaqr3 dlaqr4 dlaqr5 \
dlaqsb dlaqsp dlaqsy dlaqtr dlar1v \
dlar2v dlarf dlarfb dlarfg dlarfp \
dlarft dlarfx dlargv dlarnv dlarra \
dlarrb dlarrc dlarrd dlarre dlarrf \
dlarrj dlarrk dlarrr dlarrv dlartg \
dlartv dlaruv dlarz dlarzb dlarzt \
dlas2 dlascl dlascl2 dlasd0 dlasd1 \
dlasd2 dlasd3 dlasd4 dlasd5 dlasd6 \
dlasd7 dlasd8 dlasda dlasdq dlasdt \
dlaset dlasq1 dlasq2 dlasq3 dlasq4 \
dlasq5 dlasq6 dlasr dlasrt dlassq \
dlasv2 dlaswp dlasy2 dlasyf dlatbs \
dlatdf dlatps dlatrd dlatrs dlatrz \
dlauu2 dlauum dorg2l dorg2r dorgl2 \
dorgr2 dorm2l dorm2r dorml2 dormr2 \
dormr3 dpbtf2 dpotf2 dpstf2 dptts2 \
drscl dsygs2 dsytd2 dsytf2 dtgex2 \
dtgsy2 dtrti2 ieeeck iladlc iladlr \
ilaenv ilaprec ilaslc ilaslr ilatrans \
ilauplo iparmq maxloc sgbtf2 sgebd2 \
sgehd2 sgelq2 sgeql2 sgeqr2 sgerq2 \
sgesc2 sgesc2 sgetc2 sgetf2 sgsvj0 \
sgsvj1 sgtts2 sisnan slabad slabrd \
slacn2 slacpy sladiv slae2 slaebz \
slaed0 slaed1 slaed2 slaed3 slaed4 \
slaed5 slaed6 slaed7 slaed8 slaed9 \
slaeda slaein slaev2 slaexc slag2 \
slags2 slagtf slagtm slagts slagv2 \
slahqr slahr2 slaic1 slaisnan slaln2 \
slals0 slalsa slalsd slamrg slaneg \
slangb slange slangt slanhs slansb \
slansp slanst slansy slantb slantp \
slantr slanv2 slapll slapmt slapy2 \
slapy3 slaqgb slaqge slaqp2 slaqps \
slaqr0 slaqr1 slaqr2 slaqr3 slaqr4 \
slaqr5 slaqsb slaqsp slaqsy slaqtr \
slar1v slar2v slarf slarfb slarfg \
slarfp slarft slarfx slargv slarnv \
slarra slarrb slarrc slarrd slarre \
slarrf slarrj slarrk slarrr slarrv \
slartg slartv slaruv slarz slarzb \
slarzt slas2 slascl slasd0 slasd1 \
slasd2 slasd3 slasd4 slasd5 slasd6 \
slasd7 slasd8 slasda slasdq slasdt \
slaset slasq1 slasq2 slasq3 slasq4 \
slasq5 slasq6 slasr slasrt slassq \
slasv2 slaswp slasy2 slasyf slatbs \
slatdf slatps slatrd slatrs slatrz \
slauu2 slauum sorg2l sorg2r sorgl2 \
sorgr2 sorm2l sorm2r sorml2 sormr2 \
sormr3 spbtf2 spotf2 spstf2 sptts2 \
srscl ssygs2 ssytd2 ssytf2 stgex2 \
stgsy2 strti2 sbdsdc sbdsqr sdisna \
sgbbrd sgbcon sgbequ sgbequb sgbrfs \
sgbsv sgbsvx sgbtrf sgbtrs sgebak \
sgebal sgebrd sgecon sgeequ sgeequb \
sgees sgeesx sgeev sgeevx sgehrd \
sgejsv sgelqf sgels sgelsd sgelss \
sgelsy sgeqlf sgeqp3 sgeqpf sgeqrf \
sgerfs sgerqf sgesdd sgesv sgesvd \
sgesvj sgesvx sgetrf sgetri sgetrs \
sggbak sggbal sgges sggesx sggev \
sggevx sggglm sgghrd sgglse sggqrf \
sggrqf sggsvd sggsvp sgtcon sgtrfs \
sgtsv sgtsvx sgttrf sgttrs shgeqz \
shsein shseqr sopgtr sopmtr sorgbr \
sorghr sorglq sorgql sorgqr sorgrq \
sorgtr sormbr sormhr sormlq sormql \
sormqr sormrq sormrz sormtr spbcon \
spbequ spbrfs spbstf spbsv spbsvx \
spbtrf spbtrs spftrf spftri spftrs \
spocon spoequ spoequb sporfs sposv \
sposvx spotrf spotri spotrs sppcon \
sppequ spprfs sppsv sppsvx spptrf \
spptri spptrs spstrf sptcon spteqr \
sptrfs sptsv sptsvx spttrf spttrs \
ssbev ssbevd ssbevx ssbgst ssbgv \
ssbgvd ssbgvx ssbtrd ssfrk sspcon \
sspev sspevd sspevx sspgst sspgv \
sspgvd sspgvx ssprfs sspsv sspsvx \
ssptrd ssptrf ssptri ssptrs sstebz \
sstedc sstegr sstein sstemr ssteqr \
ssterf sstev sstevd sstevr sstevx \
ssycon ssyequb ssyev ssyevd ssyevr \
ssyevx ssygst ssygv ssygvd ssygvx \
ssyrfs ssysv ssysvx ssytrd ssytrf \
ssytri ssytrs stbcon stbrfs stbtrs \
stfsm stftri stfttp stfttr stgevc \
stgexc stgsen stgsja stgsna stgsyl \
stpcon stprfs stptri stptrs stpttf \
stpttr strcon strevc strexc strrfs \
strsen strsna strsyl strtri strtrs \
strttf strttp stzrzf dbdsdc dbdsqr \
ddisna dgbbrd dgbcon dgbequ dgbequb \
dgbrfs dgbsv dgbsvx dgbtrf dgbtrs \
dgebak dgebal dgebrd dgecon dgeequ \
dgeequb dgees dgeesx dgeev dgeevx \
dgehrd dgejsv dgelqf dgels dgelsd \
dgelss dgelsy dgeqlf dgeqp3 dgeqpf \
dgeqrf dgerfs dgerqf dgesdd dgesv \
dgesvd dgesvj dgesvx dgetrf dgetri \
dgetrs dggbak dggbal dgges dggesx \
dggev dggevx dggglm dgghrd dgglse \
dggqrf dggrqf dggsvd dggsvp dgtcon \
dgtrfs dgtsv dgtsvx dgttrf dgttrs \
dhgeqz dhsein dhseqr dopgtr dopmtr \
dorgbr dorghr dorglq dorgql dorgqr \
dorgrq dorgtr dormbr dormhr dormlq \
dormql dormqr dormrq dormrz dormtr \
dpbcon dpbequ dpbrfs dpbstf dpbsv \
dpbsvx dpbtrf dpbtrs dpftrf dpftri \
dpftrs dpocon dpoequ dpoequb dporfs \
dposv dposvx dpotrf dpotri dpotrs \
dppcon dppequ dpprfs dppsv dppsvx \
dpptrf dpptri dpptrs dpstrf dptcon \
dpteqr dptrfs dptsv dptsvx dpttrf \
dpttrs dsbev dsbevd dsbevx dsbgst \
dsbgv dsbgvd dsbgvx dsbtrd dsfrk dspcon \
dspev dspevd dspevx dspgst dspgv dspgvd \
dspgvx dsprfs dspsv dspsvx dsptrd \
dsptrf dsptri dsptrs dstebz dstedc \
dstegr dstein dstemr dsteqr dsterf \
dstev dstevd dstevr dstevx dsycon \
dsyequb dsyev dsyevd dsyevr dsyevx \
dsygst dsygv dsygvd dsygvx dsyrfs \
dsysv dsysvx dsytrd dsytrf dsytri \
dsytrs dtbcon dtbrfs dtbtrs dtfsm \
dtftri dtfttp dtfttr dtgevc dtgexc \
dtgsen dtgsja dtgsna dtgsyl dtpcon \
dtprfs dtptri dtptrs dtpttf dtpttr \
dtrcon dtrevc dtrexc dtrrfs dtrsen \
dtrsna dtrsyl dtrtri dtrtrs dtrttf \
dtrttp dtzrzf cbdsqr cgbbrd cgbcon \
cgbequ cgbrfs cgbsv cgbsvx cgbtf2 \
cgbtrf cgbtrs cgebak cgebal cgebd2 \
cgebrd cgecon cgeequ cgees cgeesx \
cgeev cgeevx cgegs cgegv cgehd2 \
cgehrd cgelq2 cgelqf cgels cgelsd \
cgelss cgelsx cgelsy cgeql2 cgeqlf \
cgeqp3 cgeqpf cgeqr2 cgeqrf cgerfs\
cgerq2 cgerqf cgesc2 cgesdd cgesv\
cgesvd cgesvx cgetc2 cgetf2 cgetrf\
cgetri cgetrs cggbak cggbal cgges\
cggesx cggev cggevx cggglm cgghrd\
cgglse cggqrf cggrqf cggsvd cggsvp\
cgtcon cgtrfs cgtsv cgtsvx cgttrf\
cgttrs cgtts2 chbev chbevd chbevx\
chbgst chbgv chbgvd chbgvx chbtrd\
checon cheev cheevd cheevr cheevx\
chegs2 chegst chegv chegvd chegvx\
cherfs chesv chesvx chetd2 chetf2\
chetrd chetrf chetri chetrs chgeqz\
chpcon chpev chpevd chpevx chpgst\
chpgv chpgvd chpgvx chprfs chpsv\
chpsvx chptrd chptrf chptri chptrs\
chsein chseqr clabrd clacgv clacon\
clacn2 clacp2 clacpy clacrm clacrt\
cladiv claed0 claed7 claed8 claein\
claesy claev2 clags2 clagtm clahef\
clahqr clahrd clahr2 claic1 clals0\
clalsa clalsd clangb clange clangt\
clanhb clanhe clanhp clanhs clanht\
clansb clansp clansy clantb clantp\
clantr clapll clapmt clarcm claqgb\
claqge claqhb claqhe claqhp claqp2\
claqps claqsb claqr0 claqr1 claqr2\
claqr3 claqr4 claqr5 claqsp claqsy\
clar1v clar2v ilaclr ilaclc clarf\
clarfb clarfg clarft clarfp clarfx\
clargv clarnv clarrv clartg clartv\
clarz clarzb clarzt clascl claset\
clasr classq claswp clasyf clatbs\
clatdf clatps clatrd clatrs clatrz\
clatzm clauu2 clauum cpbcon cpbequ\
cpbrfs cpbstf cpbsv cpbsvx cpbtf2\
cpbtrf cpbtrs cpocon cpoequ cporfs\
cposv cposvx cpotf2 cpotrf cpotri\
cpotrs cpstrf cpstf2 cppcon cppequ\
cpprfs cppsv cppsvx cpptrf cpptri\
cpptrs cptcon cpteqr cptrfs cptsv\
cptsvx cpttrf cpttrs cptts2 crot\
cspcon cspmv cspr csprfs cspsv\
cspsvx csptrf csptri csptrs csrscl\
cstedc cstegr cstein csteqr csycon\
csymv csyr csyrfs csysv csysvx\
csytf2 csytrf csytri csytrs ctbcon\
ctbrfs ctbtrs ctgevc ctgex2 ctgexc\
ctgsen ctgsja ctgsna ctgsy2 ctgsyl\
ctpcon ctprfs ctptri ctptrs ctrcon\
ctrevc ctrexc ctrrfs ctrsen ctrsna\
ctrsyl ctrti2 ctrtri ctrtrs ctzrqf\
ctzrzf cung2l cung2r cungbr cunghr\
cungl2 cunglq cungql cungqr cungr2\
cungrq cungtr cunm2l cunm2r cunmbr\
cunmhr cunml2 cunmlq cunmql cunmqr\
cunmr2 cunmr3 cunmrq cunmrz cunmtr\
cupgtr cupmtr icmax1 scsum1 cstemr\
chfrk ctfttp clanhf cpftrf cpftri\
cpftrs ctfsm ctftri ctfttr ctpttf\
ctpttr ctrttf ctrttp cgeequb cgbequb\
csyequb cpoequb cheequb zbdsqr zgbbrd\
zgbcon zgbequ zgbrfs zgbsv zgbsvx\
zgbtf2 zgbtrf zgbtrs zgebak zgebal\
zgebd2 zgebrd zgecon zgeequ zgees\
zgeesx zgeev zgeevx zgegs zgegv\
zgehd2 zgehrd zgelq2 zgelqf zgels\
zgelsd zgelss zgelsx zgelsy zgeql2\
zgeqlf zgeqp3 zgeqpf zgeqr2 zgeqrf\
zgerfs zgerq2 zgerqf zgesc2 zgesdd\
zgesv zgesvd zgesvx zgetc2 zgetf2\
zgetrf zgetri zgetrs zggbak zggbal\
zgges zggesx zggev zggevx zggglm\
zgghrd zgglse zggqrf zggrqf zggsvd\
zggsvp zgtcon zgtrfs zgtsv zgtsvx\
zgttrf zgttrs zgtts2 zhbev zhbevd\
zhbevx zhbgst zhbgv zhbgvd zhbgvx\
zhbtrd zhecon zheev zheevd zheevr\
zheevx zhegs2 zhegst zhegv zhegvd\
zhegvx zherfs zhesv zhesvx zhetd2\
zhetf2 zhetrd zhetrf zhetri zhetrs\
zhgeqz zhpcon zhpev zhpevd zhpevx\
zhpgst zhpgv zhpgvd zhpgvx zhprfs\
zhpsv zhpsvx zhptrd zhptrf zhptri\
zhptrs zhsein zhseqr zlabrd zlacgv\
zlacon zlacn2 zlacp2 zlacpy zlacrm\
zlacrt zladiv zlaed0 zlaed7 zlaed8\
zlaein zlaesy zlaev2 zlags2 zlagtm\
zlahef zlahqr zlahrd zlahr2 zlaic1\
zlals0 zlalsa zlalsd zlangb zlange\
zlangt zlanhb zlanhe zlanhp zlanhs\
zlanht zlansb zlansp zlansy zlantb\
zlantp zlantr zlapll zlapmt zlaqgb\
zlaqge zlaqhb zlaqhe zlaqhp zlaqp2\
zlaqps zlaqsb zlaqr0 zlaqr1 zlaqr2\
zlaqr3 zlaqr4 zlaqr5 zlaqsp zlaqsy\
zlar1v zlar2v ilazlr ilazlc zlarcm\
zlarf zlarfb zlarfg zlarft zlarfp\
zlarfx zlargv zlarnv zlarrv zlartg\
zlartv zlarz zlarzb zlarzt zlascl\
zlaset zlasr zlassq zlaswp zlasyf\
zlatbs zlatdf zlatps zlatrd zlatrs\
zlatrz zlatzm zlauu2 zlauum zpbcon\
zpbequ zpbrfs zpbstf zpbsv zpbsvx\
zpbtf2 zpbtrf zpbtrs zpocon zpoequ\
zporfs zposv zposvx zpotf2 zpotrf\
zpotri zpotrs zpstrf zpstf2 zppcon\
zppequ zpprfs zppsv zppsvx zpptrf\
zpptri zpptrs zptcon zpteqr zptrfs\
zptsv zptsvx zpttrf zpttrs zptts2\
zrot zspcon zspmv zspr zsprfs\
zspsv zspsvx zsptrf zsptri zsptrs\
zdrscl zstedc zstegr zstein zsteqr\
zsycon zsymv zsyr zsyrfs zsysv\
zsysvx zsytf2 zsytrf zsytri zsytrs\
ztbcon ztbrfs ztbtrs ztgevc ztgex2\
ztgexc ztgsen ztgsja ztgsna ztgsy2\
ztgsyl ztpcon ztprfs ztptri ztptrs\
ztrcon ztrevc ztrexc ztrrfs ztrsen\
ztrsna ztrsyl ztrti2 ztrtri ztrtrs\
ztzrqf ztzrzf zung2l zung2r zungbr\
zunghr zungl2 zunglq zungql zungqr\
zungr2 zungrq zungtr zunm2l zunm2r\
zunmbr zunmhr zunml2 zunmlq zunmql\
zunmqr zunmr2 zunmr3 zunmrq zunmrz\
zunmtr zupgtr zupmtr izmax1 dzsum1\
zstemr zcgesv zcposv zlag2c clag2z\
zlat2c zhfrk ztfttp zlanhf zpftrf\
zpftri zpftrs ztfsm ztftri ztfttr\
ztpttf ztpttr ztrttf ztrttp zgeequb

FFLAGS =  -c -W -O3 -fno-automatic -ffixed-line-length-132

SRSFILES = $(FFILES)

OBJFILES = $(FFILES:.c=.o)

%.o: %.c
	emcc CLAPACK-3.2.1/SRC/$@.c -O2 -ICLAPACK-3.2.1/INCLUDE -o build/$<.bc

$(NAME): build/$(laPackFiles:.c=.bc)
	echo build/$(laPackFiles:.c=.bc)

#$(laPackFiles):
#	emcc CLAPACK-3.2.1/SRC/$@.c -O2 -ICLAPACK-3.2.1/INCLUDE -o build/$<.bc

# lapack: $(lapackFiles)
# 	%: %.c
# 		emcc CLAPACK-3.2.1/SRC/$@.c -O2 -ICLAPACK-3.2.1/INCLUDE -o build/$<.bc
#
# f2c:
# 	%: %.c
# 		emcc CLAPACK-3.2.1/F2CLIBS/libf2c/$@.c -O2 -ICLAPACK-3.2.1/INCLUDE -o build/$<.bc

#$(NAME):	$(OBJFILES)
#	gcc -o $(NAME) *.o
#	gfortran -o $(NAME) *.o
#	mv $(NAME) /home/llp/bin
#.c.o:
#	gfortran $(FFLAGS)  $*.c

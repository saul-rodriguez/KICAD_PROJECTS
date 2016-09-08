* Path, Component, Release: cmos7base/rel/HSPICE/models/p5pfet50.inc, tech7_models, mod_cmos7base
* CMVC Revision: 1.3 11/08/23 14:47:26
*
*  IBM 7RF/7WL  p5pfet50       5.0V PFET with Lmin=0.5um subcircuit
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) p5pfet50 l=nnn w=nnn
*
*  REQUIRED:
*            +        w = nnn  <- Design width of RX (meters)
*            +        l = nnn  <- Design length of PC (meters)
*  OPTIONAL:
*            +       as = 0    <- Source diffusion area (meters^2)
*            +       ad = 0    <- Drain diffusion area (meters^2)
*            +       ps = 0    <- Source diffusion perimeter in (meters)
*            +       pd = 0    <- Drain diffusion perimeter in (meters)
*            +      nrd = 0    <- Number of squares of drain diffusion
*            +      nrs = 0    <- Number of squares of source diffusion
*            +    dtemp = 0    <- Device temp rise from ambient (deg C)
*            +       nf = 1    <- number of gate stripes or "fingers" in device
*            +  m (par) = 1    <- number of parallel instances (multiplicity)
*            +     gcon = 1    <- Gate connection switch (1->single-ended,
*                                                         2->double-ended)
*            +      rsx = 50   <- Body resistance
*            +       rf = 0    <- RF device flag (0-> nfet pcell
*                                                 1-> nfet_rf pcell)
*            +      gns = 0    <- ESD hierarchical cell layout option
*                                 (0-> silicided gate, 1-> non-silicided gate)
*
*  NOTES:
*
*  1. If nrd or nrs are not passed to the model they will default to 0.
*     This will result in 0 ohms of silicided S/D resistance being placed
*     in series with the device model.
*
*  2. Intrinsic FET model includes PC bounded perimeter only.
*
* SUBCIRCUIT SCHEMATIC:
*
*                cwgd
*                 | |             drain
*        o--------| |---------------o----------------------------------o
*        |        | |               |                                  |
*        |                          |     Ddb (Includes internal       |
*        |                          /     FET drain area and STI       |
*        |                   rdext  \     bounded perimeter)           |
*        |                          /                                  |
*        |                          |______|\|__________             ----- cwds
*        |                      d1  |      |/|          |            -----
*        |                          |------\/\/\/-------o              |
*        |                          |        rddb       |              |
*        |                    |_____|                   |              |
*        |              g1  | |         b1              |     bulk     |
*   gate o-----\/\/\/---o---| |  |------o----\/\/\/-----o-------o      |
*        |      rgate       | |_____          rsx       |              |
*        |                    |     |                   |              |
*        |                          |------\/\/\/-------o              |
*        |                          |         rdsb      |              |
*        |                      s1  |______|\|__________|              |
*        |                          |      |/|                         |
*        |                          \                                  |
*        |                   rsext  /     Dsb (Includes internal       |
*        |                          \     FET source area and STI      |
*        |                          |     bounded perimeter)           |
*        |        | |               |                                  |
*        o--------| |---------------o----------------------------------o
*                 | |             source
*                cwgs
*
* IBM CONFIDENTIAL
* (C) 2011 IBM Corporation
*
***************************************************************************
*
.subckt p5pfet50  d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                          gcon=1 dtemp=0 rf=0 par=1 rsx=50 gns=0
.param
+  zad=ad zas=as znrd=nrd znrs=nrs zpd=pd zps=ps
*
* Gate bounded perimeter (identical for source and drain)
+  pgate = '(w+ndelrx)'
*
* STI S/D bounded perimeter (subtract gate bounded from total passed in)
+  pstis = 'max(0,(zps-pgate))'
+  pstid = 'max(0,(zpd-pgate))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=1.2812e-8  kvtw=-0.25u    kvtl=0.35u
+  kmb=3.6075e-10 kmbw=-0.958u    kmbl=0.09u
+  sigvth='kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta='kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0=agauss(0,sigvth,3)        $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)       $ beta mis-match
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale = '(noistd_p5p50-min(log(sqrt(w*l*nf*par/noideva_p5p50)),0))'
+  noi_mul   = '(exp(dnoip50*noi_scale))'
*
* Thermal noise scaling equation
+  tnoitanha = -0.1
+  tnoitanhb = 3.55e6
+  tnoitanhc = 7e11
+  ntnoi_p5p50 = '1/tanh(tnoitanha + tnoitanhb*l + tnoitanhc*l*l)'
*
* Gate Resistance Calculation
+  rnqsl='0.5*((l-2*lint_p5p50)*1e6)'
+  rnqsw='2.4225*(0.043*((w-2*wint_p5p50)*1e6))'
+  rnqsnf = '1.1*(32/nf)**1.1'
+  rnqs = '0.2*(rnqsl/rnqsw)*rnqsnf'
+  rpoly='((pcrsi*(1-gns)+oppcrsf*gns)/nf)*((1.96u+w+ndelrx)/(l+lwbpc))*(1/(3*gcon*gcon))'
*
* Substrate Resistance Calculation
+ rsubl='1/(l-2*lint_p5p50)**0.1'
+ rsubw='0.01/((w-2*wint_p5p50)**0.1)'
+ rsubn='1/(0.01*nf)**0.1'
+ rx='1.121*4.4281*rsubl*rsubw*rsubn'
*
* Drain/Source Resistance Calculation
+  rd='1 + (nf-2)*(0.05 + l*1e6*0.9+ w*1e6*0.005)'
+  rs='1 + (nf)*(0.05 + l*1e6*0.9 + w*1e6*0.005)'
*
* Gate to drain capacitance calculation (function of l and nf)
+  cgd='230e-18 + (nf-2)*(280e-18 + (l*1e6)*20e-18 + (w*1e6)*25e-18)'
*
* Gate to source capacitance calculation (function of l and nf)
+  cgs='1e-15 + (nf)*(600e-18 + (w*1e6)*25e-18)'
*
* Drain to source capacitance calculation (function of l and nf)
+  cds= '(nf-2)*(500e-18 + (l*1e6)*500e-18 + (w*1e6)*170e-18)'
*
m0 d1 g1 s1 b1 pch50    w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                       mult=nf 
rdext  d1  d  r='(znrd*rsh_p50/nf) + rf*rd'
rsext  s1  s  r='(znrs*rsh_p50/nf) + rf*rs'
rgate  g1  g  r='rpoly+rnqs'
rsx    b  b1  r='((1-rf)*rsx+rf*rx)'
cwgd   g   d  c='(1e-18 + rf*cgd)'
cwgs   g   s  c='(1e-18 + rf*cgs)'
cwds   d   s  c='(1e-18 + rf*cds)'
ddb    d1 b1 pdio area=zad pj=pstid m=nf dtemp=dtemp
dsb    s1 b1 pdio area=zas pj=pstis m=nf dtemp=dtemp
rdb    d1 b1 r='222222/(zad*nf)'
rsb    s1 b1 r='222222/(zas*nf)'
*
***************************************************************************
* PFET PSP model
***************************************************************************
.model pch50 pmos (
+ level  = 69
+ version = 102.3
+ tr  = 25.00 
***************************************************************************
* Switch Settings
***************************************************************************
+ swgidl  = 0.000 
+ swigate  = 0.000 
+ swimpact  = 1.000 
+ swjuncap  = 3.000 
***************************************************************************
* Parameters With Process Variation
***************************************************************************
+ lap  = lint_p5p50
+ lov  = lov_p5p50
+ novo  = 4.100e+23 
+ nsubo  = 1.260e+23 
+ rsw1  = rsw_p5p50 
+ thesatl  = thesatl_p5p50
+ toxo  = tox_p5p50
+ toxovo  = tox_p5p50
+ uo  = 'uo_p5p50+mmbeta'
+ vfbl  = vfbl_p5p50
+ vfblw  = vfblw_p5p50
+ vfbo  = 'vfb_p5p50+mmvth0'
+ wot  = wint_p5p50
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l  = 81.90m
+ a1o  = 52.00 
+ a1w  = 120.0m
+ a2o  = 51.38 
+ a3l  = -79.78m
+ a3o  = 1.204 
+ a3w  = -300.0m
+ a4l  = -350.0m
+ a4o  = 38.00m
+ a4w  = 0.000 
+ agidlw  = 0.000 
+ alp1l1  = 5.500m
+ alp1l2  = 0.000 
+ alp1lexp  = 990.0m
+ alp1w  = 335.5m
+ alp2l1  = 0.000 
+ alp2l2  = 0.000 
+ alp2lexp  = 1.000 
+ alp2w  = 90.00m
+ alpl  = 28.95m
+ alplexp  = 899.0m
+ alpw  = -1.334m
+ axl  = 1.000 
+ axo  = 10.67 
+ betw1  = 1.000u
+ betw2  = 0.000 
+ bgidlo  = 41.00 
+ cfbo  = 300.3m
+ cfl  = 98.4u
+ cflexp  = 4.732 
+ cfrw  = 0.000 
+ cfw  = -100.0m
+ cgbovl  = 0.000 
+ cgidlo  = 0.000 
+ chibo  = 3.100 
+ csl  = 23.95u
+ cslexp  = 1.000 
+ cslw  = -4.642 
+ cso  = 1.000m
+ csw  = 0.000 
+ ctl  = 55.5000m
+ ctlexp  = 579.1m
+ ctlw  = 0.000 
+ cto  = 40.00m
+ ctw  = 0.000
+ dlq  = -150.0n
+ dnsubo  = 21.48m
+ dphibl  = 97.76m
+ dphiblexp  = 416.1m
+ dphiblw  = 0.000 
+ dphibo  = -15.00m
+ dphibw  = -5.000m
+ dta = dtemp
+ dwq  = -36.00n
+ fbet1  = 990.0m
+ fbet1w  = 990.0m
+ fbet2  = 0.000 
+ fetao  = 1.250 
+ fol1  = fol1_p5p50
+ fol2  = fol2_p5p50
+ gc2o  = 375.0m
+ gc3o  = 63.00m
+ gcoo  = 0.000 
+ iginvlw  = 0.000 
+ igovw  = 0.000 
+ kuo  = 0.000 
+ kvsat  = 0.000 
+ kvtho  = 0.000 
+ lkuo  = 0.000 
+ lkvtho  = 0.000 
+ llodkuo  = 0.000 
+ llodvth  = 0.000 
+ lodetao  = 1.000 
+ lp1  = 20.00n
+ lp1w  = 100.0m
+ lp2  = 1e-10 
+ lpck  = 10.00n
+ lpckw  = 0.000 
+ lvarl  = 0.000 
+ lvaro  = 0.000 
+ lvarw  = 0.000 
+ mueo  = 2.200 
+ muew  = -125.0m
+ npck  = 1.000f
+ npckw  = 0.000 
+ npl  = -150.0m
+ npo  = 4.910e+25 
+ nslpo  = 1.001m
+ nsubw  = -19.00m
+ pkuo  = 0.000 
+ pkvtho  = 0.000 
+ qmc  = 395.4m
+ rsbo  = 0.000 
+ rsgo  = 100.0u
+ rsw2  = -444.1p
+ saref  = 1.000u
+ sbref  = 1.000u
+ sta2o  = 0.000 
+ stbetl  = 44.65m
+ stbetlw  = 0.000 
+ stbeto  = 995.0m
+ stbetw  = -48.10m
+ stbgidlo  = 0.000 
+ stcso  = 835.6u
+ stetao  = 0.000 
+ stigo  = 2.000 
+ stmueo  = 444.1p
+ strso  = 274.3m
+ stthemuo  = 509.9m
+ stthesatl  = 540.0m
+ stthesatlw  = -12.40m
+ stthesato  = 707.9m
+ stthesatw  = 444.1p
+ stvfbl  = -64.82m
+ stvfblw  = -94.95m
+ stvfbo  = 0.5000m
+ stvfbw  = 894.0m
+ stxcoro  = -100.0m
+ themuo  = 1.000 
+ thesatbo  = -1.000m
+ thesatgo  = 100.7m
+ thesatlexp  = 1.140 
+ thesatlw  = 140.0m
+ thesato  = 441.0p
+ thesatw  = -290.0m
+ tkuo  = 0.000 
+ vfbw  = -5.500m
+ vnsubo  = 0.000 
+ vpo  = 400.0m
+ wbet  = 31.90n
+ wkuo  = 0.000 
+ wkvtho  = 0.000 
+ wlod  = 0.000 
+ wlodkuo  = 0.000 
+ wlodvth  = 0.000 
+ wseg  = 10.00n
+ wsegp  = 100.0p
+ wvarl  = 0.000 
+ wvaro  = 0.000 
+ wvarw  = 0.000 
+ xcorl  = 0.000 
+ xcorlw  = 0.000 
+ xcoro  = 1.000f
+ xcorw  = 0.000 
***************************************************************************
* Junction Diode Parameters
***************************************************************************
+ trj  = 25.00 
+ imax  = 1.000k
***************************************************************************
*    Capacitance Parameters
***************************************************************************
+ cjorbot  = 1e-12
+ cjorgat  = cjsg_p5p50
+ cjorsti  = 1e-18
+ vbirgat  = pbsg_p5p50
+ pbot  = 0.05
+ pgat  = mjsg_p5p50
+ psti  = 0.05
***************************************************************************
*    Ideal Current Parameters
***************************************************************************
+ phigbot  = 1.000 
+ phiggat  = 1.000 
+ phigsti  = 1.000 
+ xjungat  = 100.0n
+ xjunsti  = 100.0n
+ idsatrbot  = 1.000f
+ idsatrgat  = 1.300f
+ idsatrsti  = 1.300f
+ csrhbot  = 0.000 
+ csrhgat  = 0.000 
+ csrhsti  = 0.000
***************************************************************************
*    Trap-Assisted Tunneling Parameters
***************************************************************************
+ ctatbot  = 0.000 
+ ctatgat  = 0.000 
+ ctatsti  = 0.000 
+ mefftatbot  = 250.0m
+ mefftatgat  = 250.0m
+ mefftatsti  = 250.0m
***************************************************************************
*    Band-to-Band Tunneling Parameters
***************************************************************************
+ cbbtbot=0
+ cbbtsti=0
+ cbbtgat=0
+ fbbtrbot=1e+09
+ fbbtrsti=1e+09
+ fbbtrgat=1e+09
+ stfbbtbot=0
+ stfbbtsti=0
+ stfbbtgat=0
***************************************************************************
*    Avalanche and Breakdown Parameters
***************************************************************************
+ vbrbot=1001
+ vbrsti=1001
+ vbrgat=1001
+ pbrbot=4
+ pbrsti=4
+ pbrgat=4
***************************************************************************
* Noise Parameters
***************************************************************************
+ nfalw  = '9e+22*noi_mul'
+ nfblw  = '3.9e+09*noi_mul'
+ nfclw  = '0.9e-08*noi_mul'
+ efo    = 1.3
+ fnto   = ntnoi_p5p50  )
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model pdio  d (
+ level  = 1.000 
+ tref  = 25.00 
+ xti  = 3.000 
+ tlev  = 0.000 
+ tlevc  = 1.000 
+ eg  = 1.170 
+ gap1  = 473.0u
+ gap2  = 636.0 
+ rs = 0
+ js  = js_p5p50
+ jsw  = jsw_p5p50
+ n  = n_p5p50
+ cj  = cj_p5p50
+ pb  = pb_p5p50
+ mj  = mj_p5p50
+ cjsw  = cjsw_p5p50
+ php  = pbsw_p5p50
+ mjsw  = mjsw_p5p50
+ ibv = 10u
+ cta  = cta_p5p50 
+ ctp  = ctp_p5p50
+ tpb  = pta_p5p50
+ tphp  = ptp_p5p50
+ bv  = 9.530 )
***************************************************************************
.ends p5pfet50

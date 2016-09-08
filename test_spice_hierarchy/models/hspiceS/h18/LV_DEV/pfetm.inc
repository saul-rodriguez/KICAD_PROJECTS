* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfetm.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  pfetm     5.0V PFET subcircuit
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) pfetm l=nnn w=nnn
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
*            +       nf = 1    <- Number of gate stripes or "fingers" in device
*            +  m (par) = 1    <- Number of parallel instances (multiplicity)
*            +     gcon = 1    <- Gate connection switch (1->single-ended,
*                                                         2->double-ended)
*            +      rsx = 50   <- Body resistance
*            +      gns = 0    <- ESD hierarchical cell layout option
*                                 (0-> silicided gate, 1-> non-silicided gate)
*
*  NOTES:
*
*  1. If nrd or nrs are not passed to the model they will default to 0.
*     This will result in 0 ohms of silicided S/D resistance being placed
*     in series with the device model.
*
*  2. Calculations assume input design width represents width of each
*     finger.
*
*  3. Calculations based on PCELL scaling rules and assume that for a device
*     with an even number of fingers, the source is the outer diffusion.
*
* SUBCIRCUIT SCHEMATIC:
*
*                                 drain
*                                   o
*                                   |
*                                   |   Ddb (Includes internal
*                                   |   FET drain area and STI
*                                   |   bounded perimeter)
*                                   |
*                                   |______|\|__________
*                             d     |      |/|          |
*                                   |------\/\/\/-------o
*                                   |     rddb          |
*                             |_____|                   |
*                     g1    | |                      b1 |             bulk
*   gate o-----\/\/\/---o---| |  |----------------------o---\/\/\/-----o
*              rgate        | |_____                    |    rsb
*                             |     |                   |
*                                   |------\/\/\/-------o
*                                   |        rdsb       |
*                            s      |______|\|__________|
*                                   |      |/|
*                                   |
*                                   |   Dsb (Includes internal
*                                   |   FET source area and STI
*                                   |    bounded perimeter)
*                                   |
*                                   o
*                                source
*
*
***************************************************************************
.subckt pfetm  d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                       gcon=1 rsx=50 dtemp=0 par=1 gns=0
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
+  kvt=1.6012e-8   kvtw=-0.15u    kvtl=0.38u
+  kmb=4.1075e-10  kmbw=-0.258u   kmbl=-0.89u
+  sigvth = 'kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta= 'kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0=agauss(0,sigvth,3)        $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)       $ beta mis-match
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale = '(noistd_p5m-min(log(sqrt(w*l*nf*par/noideva_p5m)),0))'
+  noia_mul  = '(exp(dnoip5m*noi_scale))'
+  noib_mul  = '(exp(dnoip5m*noi_scale))'
+  noic_mul  = '(exp(dnoip5m*noi_scale/3))'
*
* Gate Resistance Calculation
+  rnqsl  = '0.5*((l-2*lint_p5m)*1e6)'
+  rnqsw  = '2.4225*(0.043*((w-2*wint_p5m)*1e6))'
+  rnqsnf = '1.1*(32/nf)**1.1'
+  rnqs   = '0.2*(rnqsl/rnqsw)*rnqsnf'
+  rpoly  = '((pcrsi*(1-gns)+oppcrsf*gns)/(nf*gcon))*(1.96u+w/(3*gcon))/(l+lwbpc)'
*
m0 d g1 s b1 pchm   w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
rgate  g1  g  r='(rpoly+rnqs)'
rsb    b   b1 r=rsx
ddb    d   b1 pdio area=zad pj=pstid m=nf dtemp=dtemp
dsb    s   b1 pdio area=zas pj=pstis m=nf dtemp=dtemp
rddb   d   b1 r='109553/(zad*nf)'
rdsb   s   b1 r='109553/(zas*nf)'
*
***************************************************************************
* 5V PFET PSP model
***************************************************************************
.model pchm pmos (
+ level  = 69
+ version = 102.3
+ tr  = 25.00 
***************************************************************************
* Switch Settings
***************************************************************************
+ swgidl  = 1.000 
+ swigate  = 0.000 
+ swimpact  = 1.000 
+ swjuncap  = 3.000 
***************************************************************************
* Parameters With Process Variation
***************************************************************************
+ fol1 = fol1_p5m
+ fol2 = fol2_p5m
+ lap  = lint_p5m
+ lov  = lov_p5m
+ novo  = 5.065e+23 
+ nsubo  = 1.453e+23
+ rsw1  = rsw_p5m
+ thesatl  = thesatl_p5m
+ toxo  = tox_p5m
+ toxovo  = tox_p5m
+ uo  = 'uo_p5m+mmbeta'
+ vfbl  = vfbl_p5m
+ vfblw  = vfblw_p5m
+ vfbo  = 'vfb_p5m+mmvth0'
+ wot  = wint_p5m
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l  = 55.90m
+ a1o  = 52
+ a1w  = 20m
+ a2o  = 51.38
+ a3l  = -75.78m
+ a3o  = 1.204 
+ a3w  = -9m
+ a4l  = -350.0m
+ a4o  = 38.00m
+ a4w  = 0.000 
+ agidlw  = 3.409m
+ alp1l1  = 4.168u
+ alp1l2  = 1.604m
+ alp1lexp  = 6.864
+ alp1w  = -500m
+ alp2l1  = -12.27m
+ alp2l2  = 0
+ alp2lexp  = 1.0
+ alp2w  = -12.00m
+ alpl  = 32.70m
+ alplexp  = 940.7m
+ alpw  = 2.726m
+ axl  = 647.9m
+ axo  = 11.85
+ betw1  = 67.36m
+ betw2  = -143.3m
+ bgidlo  = 9.210
+ cfbo  = 950m
+ cfl  = 999u
+ cflexp  = 2.550
+ cfrw  = -3.6u 
+ cfw  = 10m
+ cgbovl  = 0.000 
+ cgidlo  = 0.000 
+ chibo  = 3.100
+ csl  = 104.9m
+ cslexp  = 10m
+ cslw = -10.5m
+ cso  = 1.000m
+ csw  = -10m
+ ctl  = 20.26m
+ ctlexp  = 520.9m
+ ctlw  = 882m
+ cto  = 49.74m
+ ctw  = -397.6m 
+ dlq  = -122.7n
+ dnsubo  = 444.1p
+ dphibl  = 2.120m
+ dphiblexp  = 379.2m
+ dphiblw  = 250m
+ dphibo  = 19.39m
+ dphibw  = 243.7m
+ dta = dtemp
+ dwq  = -36.00n
+ fbet1  = 100m
+ fbet1w  = -900m
+ fbet2  = 100m 
+ fetao  = 1.120
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
+ lp1  = 100n
+ lp1w  = 1n
+ lp2  = 13.41n
+ lpck  = 1.00n
+ lpckw  = 0.000 
+ lvarl  = 0.000 
+ lvaro  = 0.000 
+ lvarw  = 0.000 
+ mueo  = 1.975
+ muew  = -217.8m
+ npck  = 994.8k
+ npckw  = 0.000 
+ npl  = 100m
+ npo  = 1.922e+25 
+ nslpo  = 1.001m
+ nsubw  = -800m
+ pkuo  = 0.000 
+ pkvtho  = 0.000 
+ qmc  = 444.1p
+ rsbo  = 57.70m 
+ rsgo  = 100.0u
+ rsw2  = 14m
+ saref  = 1.00u
+ sbref  = 1.00u
+ sta2o  = 56.45m 
+ stbetl  = 136.6m
+ stbetlw  = 0.000 
+ stbeto  = 1
+ stbetw  = -43.33m
+ stbgidlo  = 0.000 
+ stcso  = 835.6u
+ stetao  = 0.000 
+ stigo  = 2.000 
+ stmueo  = 32.45m
+ strso  = 592.4m
+ stthemuo  = 347.5m
+ stthesatl  = 11.96m
+ stthesatlw  = 138.7m
+ stthesato  = 1.643
+ stthesatw  = -206.5m
+ stvfbl  = -22.32m
+ stvfblw  = -1.00f
+ stvfbo  = 869.9u
+ stvfbw  = -50m
+ stxcoro  = 155.6m
+ themuo  = 1.090
+ thesatbo  = 42.40m
+ thesatgo  = 1.7m
+ thesatlexp  = 1.202 
+ thesatlw  = 48.34m
+ thesato  = 4p
+ thesatw  = -126.4m
+ tkuo  = 0.000 
+ vfbw  = 1.887m
+ vnsubo  = 0.000 
+ vpo  = 1u
+ wbet  = 170n
+ wkuo  = 0.000 
+ wkvtho  = 0.000 
+ wlod  = 0.000 
+ wlodkuo  = 0.000 
+ wlodvth  = 0.000 
+ wseg  = 40u
+ wsegp  = 1e-10
+ wvarl  = 0.000 
+ wvaro  = 0.000 
+ wvarw  = 0.000 
+ xcorl  = 0.000 
+ xcorlw  = -500m 
+ xcoro  = 8.00m
+ xcorw  = -700m 
***************************************************************************
* Junction Diode Parameters
***************************************************************************
+ trj  = 25.00 
+ imax  = 1.000k
***************************************************************************
*    Capacitance Parameters
***************************************************************************
+ cjorbot  = 1e-12
+ cjorgat  = cjsg_p5m
+ cjorsti  = 1e-18
+ vbirgat  = pbsg_p5m
+ pbot  = 0.05
+ pgat  = mjsg_p5m
+ psti  = 0.05
***************************************************************************
*    Ideal Current Parameters
***************************************************************************
+ csrhbot  = 0.000 
+ csrhgat  = 0.010 
+ csrhsti  = 0.000
+ idsatrbot  = 1.000u
+ idsatrgat  = 0.300f
+ idsatrsti  = 1.300p
+ phigbot  = 1.000 
+ phiggat  = 1.000 
+ phigsti  = 1.000 
+ xjungat  = 100.0n
+ xjunsti  = 100.0n
***************************************************************************
*    Trap-Assisted Tunneling Parameters
***************************************************************************
+ ctatbot  = 0.000 
+ ctatgat  = 0.001
+ ctatsti  = 0.000 
+ mefftatbot  = 250.0m
+ mefftatgat  = 350.0m
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
+ stfbbtsti=-0.500
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
+ nfalw = '9e+22*noia_mul'
+ nfblw = '1.7e+09*noib_mul'
+ nfclw = '0.2e-08*noic_mul'
+ efo   = 1.2
+ fnto  = 1.0 )
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
+ rs = 100n
+ js  = js_p5m
+ jsw  = jsw_p5m
+ n  = n_p5m
+ cj  = cj_p5m
+ pb  = pb_p5m
+ mj  = mj_p5m
+ cjsw  = cjsw_p5m
+ php  = pbsw_p5m
+ mjsw  = mjsw_p5m
+ ibv  = 10u
+ cta  = cta_p5m 
+ ctp  = ctp_p5m
+ tpb  = pta_p5m
+ tphp  = ptp_p5m
+ bv  = 9.530 )
***************************************************************************
.ends pfetm

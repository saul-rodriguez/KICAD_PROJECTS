* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfetim4.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  pfetim4     5.0V PFET in HV well subcircuit (4 node)
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b  pfetim4 l=nnn w=nnn
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
*            +    vdnsx = 50   <- DN/SX max voltage option (50V or 120V)
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
*                                   |______|\|________
*                                   |      |/|        |
*                                   |------\/\/\/-----o
*                                   |     rddb        |
*                             |_____|                 |
*                      g1   | |                    b1 |             b
*   gate o-----\/\/\/---o---| |  |--------------------o---\/\/\/----o
*              rgate        | |_____                  |    rsb
*                             |     |                 |
*                                   |------\/\/\/-----o
*                                   |        rdsb     |
*                                   |______|\|________|
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
***********************************************************************
.subckt pfetim4 d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                        gcon=1 rsx=50 dtemp=0 par=1 gns=0 vdnsx=50
*
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
+  kvt=1.6012e-8   kvtw=-0.15u    kvtl=0.31u
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
+  rnqsl  = '0.5*((l-2*lint_p5im)*1e6)'
+  rnqsw  = '2.4225*(0.043*((w-2*wint_p5im)*1e6))'
+  rnqsnf = '1.1*(32/nf)**1.1'
+  rnqs   = '0.2*(rnqsl/rnqsw)*rnqsnf'
+  rpoly  = '((pcrsi*(1-gns)+oppcrsf*gns)/(nf*gcon))*(1.96u+w/(3*gcon))/(l+lwbpc)'
*
m0 d g1 s b1 pchim  w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
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
.model pchim pmos (
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
+ fol1 = fol1_p5im
+ fol2 = fol2_p5im
+ lap  = lint_p5im
+ lov  = lov_p5im
+ novo  = 3.379e+23 
+ nsubo  = 1.353e+23
+ rsw1  = rsw_p5im
+ thesatl  = thesatl_p5im
+ toxo  = tox_p5im
+ toxovo  = tox_p5im
+ uo  = 'uo_p5im+mmbeta'
+ vfbl  = vfbl_p5im
+ vfblw  = vfblw_p5im
+ vfbo  = 'vfb_p5im+mmvth0'
+ wot  = wint_p5im
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l  = 27.78m
+ a1o  = 35.94
+ a1w  = -205.1m
+ a2o  = 51.49
+ a3l  = -126.6m
+ a3o  = 1.191
+ a3w  = 43.58m
+ a4l  = -350.0m
+ a4o  = 38.00m
+ a4w  = 0.000 
+ agidlw  = 3.409m 
+ alp1l1  = 491.1u
+ alp1l2  = 1m 
+ alp1lexp  = 2.336
+ alp1w  =  502.5m
+ alp2l1  = -12.27m
+ alp2l2  = 0
+ alp2lexp  = 1.0
+ alp2w  = -12.00m
+ alpl  = 33.72m
+ alplexp  = 826.4m
+ alpw  = -444.1p
+ axl  = 686.5m
+ axo  = 12.62 
+ betw1  = 105.6m
+ betw2  = -180.1m
+ bgidlo  = 9.210 
+ cfbo  = 950m
+ cfl  = 789u
+ cflexp  = 2.738
+ cfrw  = -3.6u 
+ cfw  = -200m
+ cgbovl  = 0.000 
+ cgidlo  = 0.000 
+ chibo  = 3.100 
+ csl  = 104.9m
+ cslexp  = 10m
+ cslw  = -198.7m 
+ cso  = 1.000m
+ csw  = -949.2m 
+ ctl  = 35.26m
+ ctlexp  = 520.9m
+ ctlw  = 882m
+ cto  = 49.74m
+ ctw  = -347.4m 
+ dlq  = -158.2n
+ dnsubo  = 1f
+ dphibl  = 15.15m
+ dphiblexp  = 2
+ dphiblw  = -15m
+ dphibo  = 10.65m
+ dphibw  = -10m
+ dta = dtemp
+ dwq  = -36.00n
+ fbet1  = 444.1m
+ fbet1w  = 10m
+ fbet2  = 200m 
+ fetao  = 1.220 
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
+ lp1  = 1e-10
+ lp1w  = 25n
+ lp2  = 1e-10
+ lpck  = 1.00n
+ lpckw  = 0.000 
+ lvarl  = 0.000 
+ lvaro  = 0.000 
+ lvarw  = 0.000 
+ mueo  = 2.129
+ muew  = -205.5m
+ npck  = 994.8k
+ npckw  = 0.000 
+ npl  = -100m
+ npo  = 8.143e+25 
+ nslpo  = 1.001m
+ nsubw  = 394.4m
+ pkuo  = 0.000 
+ pkvtho  = 0.000 
+ qmc  = 50m
+ rsbo  = 10.50m 
+ rsgo  = 100.0u
+ rsw2  = 14m
+ saref  = 1.00u
+ sbref  = 1.00u
+ sta2o  = 99.02m
+ stbetl  = 89.68m
+ stbetlw  = 0.000 
+ stbeto  = 1.6
+ stbetw  = -72.50m
+ stbgidlo  = 0.000 
+ stcso  = 444.1p
+ stetao  = 0.000 
+ stigo  = 2.000 
+ stmueo  = 1.194
+ strso  = 992.6m
+ stthemuo  = 5.749m
+ stthesatl  = 122.4m
+ stthesatlw  = 63.01m
+ stthesato  = 1.9
+ stthesatw  = -155.2m
+ stvfbl  = -51.54m
+ stvfblw  = -20.42m
+ stvfbo  = 880.2u
+ stvfbw  = 2m
+ stxcoro  = 900m
+ themuo  = 1.1
+ thesatbo  = 100m
+ thesatgo  = 100.7m
+ thesatlexp  = 1.2
+ thesatlw  = 55.82m
+ thesato  = 9.170m
+ thesatw  = -147m
+ tkuo  = 0.000 
+ vfbw  = 15m
+ vnsubo  = 0.000 
+ vpo  = 1u
+ wbet  = 157.4n
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
+ xcorl  = -200m 
+ xcorlw  = 0 
+ xcoro  = 5.00m
+ xcorw  = -400m 
***************************************************************************
* Junction Diode Parameters
***************************************************************************
+ trj  = 25.00 
+ imax  = 1.000k
***************************************************************************
*    Capacitance Parameters
***************************************************************************
+ cjorbot  = 1e-12
+ cjorgat  = cjsg_p5im
+ cjorsti  = 1e-18
+ vbirgat  = pbsg_p5im
+ pbot  = 0.05
+ pgat  = mjsg_p5im
+ psti  = 0.05
***************************************************************************
*    Ideal Current Parameters
***************************************************************************
+ csrhbot  = 0.000 
+ csrhgat  = 0.000 
+ csrhsti  = 0.000
+ idsatrbot  = 1.000u
+ idsatrgat  = 1.300p
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
+ rs = 130n
+ js  = js_p5im
+ jsw  = jsw_p5im
+ n  = n_p5im
+ cj  = cj_p5im
+ pb  = pb_p5im
+ mj  = mj_p5im
+ cjsw  = cjsw_p5im
+ php  = pbsw_p5im
+ mjsw  = mjsw_p5im
+ ibv  = 10u
+ cta  = cta_p5im 
+ ctp  = ctp_p5im
+ tpb  = pta_p5im
+ tphp  = ptp_p5im
+ bv  = 9.530 )
***************************************************************************
.ends pfetim4

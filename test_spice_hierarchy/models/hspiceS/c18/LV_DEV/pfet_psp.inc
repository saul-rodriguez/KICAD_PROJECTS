* Path, Component, Release: cmos7base/rel/HSPICE/models/pfet_psp.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*  7RF/7WL  pfetpsp       1.8V PFET subcircuit
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) pfetpsp l=nnn w=nnn
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
*            +      rsx = 50   <- body resistance
*            +       rf = 0    <- RF device flag (0-> pfet pcell
*                                                 1-> pfet_rf pcell)
*            +      gns = 0    <- ESD hierarchical cell layout option
*                                 (0-> silicided gate, 1-> non-silicided gate)
*
*  NOTES:
*
*  1. Source/Drain parasitic calculations contained in this file will
*     override any values passed in the instance call for the following
*     parameters: nrs, nrd, as, ad, ps, pd.
*
*  2. Calculations assume input design width represents width of each
*     finger.
*
*  3. Calculations based on PCELL scaling rules and assume that for a device
*     with an even number of fingers, the source is the outer diffusion.
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
*        |                          |                   |              |
*        |                          |                   |              |
*        |                    |_____|                   |              |
*        |              g1  | |         b1              |     bulk     |
*   gate o-----\/\/\/---o---| |  |------o----\/\/\/-----o-------o      |
*        |      rgate       | |_____          rsb       |              |
*        |                    |     |                   |              |
*        |                          |                   |              |
*        |                          |                   |              |
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
*
***************************************************************************
.subckt pfetpsp (d g s b)
+  l=0.18u w=2u nf=1 par=1 gns=0
+  as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+  gcon=1 rsx=50 dtemp=0 rf=0
*
.param
+  zad=ad zas=as znrd=nrd znrs=nrs zpd=pd zps=ps
*
* Gate bounded perimeter (identical for source and drain)
+  pgate='(w+ndelrx)'
*
* STI S/D bounded perimeter (subtract gate bounded from total passed in)
+  pstis='max(0,(zps-pgate))'
+  pstid='max(0,(zpd-pgate))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=0.7835e-8  kvtw=0.02u   kvtl=0.135u
+  kmb=4.8072e-10 kmbw=0.08u   kmbl=-0.125u
+  sigvth='kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta='kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0=agauss(0,sigvth,3)      $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)     $ beta mis-match
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale='(noistdp-min(log(sqrt(w*l*nf*par/noidevap)),0))'
+  noi_mul='(exp(dnoip*noi_scale))'
*
* Gate resistance calculation for all cases (function of w, l and nf)
+  rge1='((pcrsi*(1-gns)+oppcrsf*gns)/(nf*gcon))*((0.42u+w/(3*gcon))/(l+lwbpc))'
+  rgw1='(27.227*(((w-2*wint_p)*nf*1e6)**(-0.55)))'
+  rgl1='((10e6*(l-2*lint_p)+0.1324)/1.665)'
*
* Gate capacitance calculation for rf=1 case (function of w, l and nf)
+  cgw1='(1.2*(85.5e-12*w*nf+0.4135e-15))'
+  cgl1='((23426e-12*l+12.428e-15)/14.09e-15)'
*
* Drain-Source Capacitance Calculation for rf=1 case (function of w, l and nf)
+  cdsw1='(0.2*(6e-12*w*nf + 0.03e-15))'
+  cdsl1='(0.1029e-12/(l**2)-0.1228e-6/l+15.011)'
*
* Substrate resistance calculation for rf=1 case (function of w, l and nf)
+  rsw1='(0.3*1062.3*(((w-2*wint_p)*nf*1e6)**(-0.7)))'
+  rsl1='((11e6*(l-2*lint_p)+28.42)/30.307)'
*
* External resistance term calculation for rf=1 case (function of w, l and nf)
+  rxw1='(27.132*((w*nf*1e6)**(-0.6064)))'
+  rxl1='((3.078e6*l+0.8425)/1.25)'
*
* NP clamping compatibility PSP102.1 vs PSP102.3
+ leff = '(l-2*lint_p)'
+ np0 = '7.1e25*max(1e-6,1-0.1*1e-6/leff)'
+ np1 = 'max(np0,8e7/(tox_p*tox_p))'
+ np_clamped = 'max(np1,3e25)'
*
m0 d1 g1 s1 b1 pch l=l w=w as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
rdext  d1   d r='(znrd*rsh_p/nf)+ rf*(rxw1*rxl1)'
rsext  s1   s r='(znrs*rsh_p/nf)+ rf*(rxw1*rxl1)'
rgate  g1   g r='(rge1+rgw1*rgl1)'
rsb     b  b1 r='((1-rf)*rsx + rf*rsl1*rsw1)'
cwgd    g   d c='(1e-18+rf*(cgw1*cgl1))'
cwgs    g   s c='(1e-18+rf*(cgw1*cgl1))'
cwds    d   s c='(1e-18+rf*(cdsw1*cdsl1))'
ddb    d1  b1 pdio area=zad pj=pstid m=nf dtemp=dtemp
dsb    s1  b1 pdio area=zas pj=pstis m=nf dtemp=dtemp
*
***************************************************************************
* PFET PSP Model
***************************************************************************
.model pch pmos(
+ level=69
+ version=102.3
+ tr=25
***************************************************************************
* Switch Settings
***************************************************************************
+ swgidl=1
+ swigate=0
+ swimpact=1
+ swjuncap=3
***************************************************************************
* Parameters With Process Variation
***************************************************************************
+ lap=lint_psp_p
+ lov=lov_psp_p
+ novo=1.0e+25
+ nsubo=7.029e+23
+ rsw1=rsw_psp_p
+ toxo=tox_psp_p
+ toxovo=tox_psp_p
+ uo='uo_psp_p+mmbeta'
+ vfbo='vfb_psp_p+mmvth0'
+ wot=wint_psp_p
+ fol1=fol1_psp_p
+ fol2=fol2_psp_p
+ cjorbot=cj_psp_p
+ cjorsti=cjsg_psp_p
+ cjorgat=cjsg_psp_p
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l=8.000e-3
+ a1o=3.880 
+ a1w=0.000 
+ a2o=22.22 
+ a3l=-49.00e-3
+ a3o=1.380 
+ a3w=0.000 
+ a4l=-100.0e-3
+ a4o=123.0e-3
+ a4w=0.000 
+ agidlw=0.082 
+ alp1l1=5.212e-3
+ alp1l2=1.243 
+ alp1lexp=1.284 
+ alp1w=186.1e-3
+ alp2l1=0.000 
+ alp2l2=100.0e-3
+ alp2lexp=1.000 
+ alp2w=0.000 
+ alpl=16.98e-3
+ alplexp=800.6e-3
+ alpw=64.25e-3
+ axl=300.0e-3
+ axo=14.64 
+ betw1=128.3e-3
+ betw2=-72.27e-3
+ bgidlo=21.66 
+ cfbo=400.0e-3
+ cfl=1.000e-3
+ cflexp=1.600 
+ cfrw=0.000 
+ cfw=-50.00e-3
+ cgbovl=0.000 
+ cgidlo=0.000 
+ chibo=3.100 
+ csl=251.4e-3
+ cslexp=309.5e-3
+ cslw=28.99e-3
+ cso=426.0e-3
+ csw=138.0e-3
+ ctl=16.19e-3
+ ctlexp=1.000 
+ ctlw=-1.000e-3
+ cto=96.57e-3
+ ctw=-100.0e-3
+ dlq=-61.50e-9
+ dnsubo=12.00e-3
+ dphibl=49.00e-6
+ dphiblexp=2.627 
+ dphiblw=0.000 
+ dphibo=72.53e-3
+ dphibw=0.000 
+ dta=dtemp 
+ dwq=0.000 
+ fbet1=789.7e-3
+ fbet1w=-726.3e-3
+ fbet2=-348.3e-3
+ fetao=1.250 
+ gc2o=375.0e-3
+ gc3o=63.00e-3
+ gcoo=0.000 
+ iginvlw=0.000 
+ igovw=0.000 
+ kuo=0.000 
+ kvsat=0.000 
+ kvtho=0.000 
+ lkuo=0.000 
+ lkvtho=0.000 
+ llodkuo=0.000 
+ llodvth=0.000 
+ lodetao=1.000 
+ lp1=5.969e-9
+ lp1w=791.0e-3
+ lp2=784.2e-12
+ lpck=450.7e-12
+ lpckw=0.000 
+ lvarl=0.000 
+ lvaro=0.000 
+ lvarw=0.000 
+ mueo=2.264 
+ muew=-180.3e-3
+ npck=1.739e+24 
+ npckw=0.000 
+ npl=0
+ npo=np_clamped
+ nslpo=50.00e-3
+ nsubw=-37.00e-3
+ pkuo=0.000 
+ pkvtho=0.000 
+ qmc=790.0e-3
+ rsbo=300.3e-3
+ rsgo=-105.1e-3
+ rsw2=900.0e-3
+ saref=1.000e-6
+ sbref=1.000e-6
+ sta2o=0.000 
+ stbetl=-10.00e-3
+ stbetlw=10.00e-3
+ stbeto=1.107 
+ stbetw=-60.00e-3
+ stbgidlo=0.000 
+ stcso=1.100 
+ stetao=0.000 
+ stigo=2.000 
+ stmueo=-119.0e-3
+ strso=0.000 
+ stthemuo=578.0e-3
+ stthesatl=-15.34e-3
+ stthesatlw=250.0e-3
+ stthesato=1.739 
+ stthesatw=-235.6e-3
+ stvfbl=15.00e-3
+ stvfblw=2.000e-3
+ stvfbo=811.5e-6
+ stvfbw=20.00e-3
+ stxcoro=2.500 
+ themuo=1.167 
+ thesatbo=0.000 
+ thesatgo=463.0e-3
+ thesatl=0.594
+ thesatlexp=861.7e-3
+ thesatlw=-14.00e-3
+ thesato=0.000 
+ thesatw=300.0e-3
+ tkuo=0.000 
+ vfbl=vfbl_psp_p
+ vfblw=vfblw_psp_p
+ vfbw=-28.95e-3
+ vnsubo=0.000 
+ vpo=10.00e-3
+ wbet=5.604e-9
+ wkuo=0.000 
+ wkvtho=0.000 
+ wlod=0.000 
+ wlodkuo=0.000 
+ wlodvth=0.000 
+ wseg=7.000e-9
+ wsegp=10.00e-9
+ wvarl=0.000 
+ wvaro=0.000 
+ wvarw=0.000 
+ xcorl=351.0e-3
+ xcorlw=-100.0e-3
+ xcoro=44.32e-3
+ xcorw=-500.0e-3
***************************************************************************
* Junction Diode Parameters
***************************************************************************
+ trj=25
+ imax=1000
***************************************************************************
*    Capacitance Parameters
***************************************************************************
+ vbirbot=pb_p
+ vbirsti=pbsg_p
+ vbirgat=pbsg_p
+ pbot=mj_p
+ psti=mjsg_p
+ pgat=mjsg_p
***************************************************************************
*    Ideal Current Parameters
***************************************************************************
+ phigbot=1.14775
+ phigsti=1.14775
+ phiggat=1.14775
+ idsatrbot=js_p
+ idsatrsti=jsw_p
+ idsatrgat=jsw_p
+ xjunsti=1e-07
+ xjungat=1e-07
+ csrhbot=0
+ csrhsti=0
+ csrhgat=0
***************************************************************************
*    Trap-Assisted Tunneling Parameters
***************************************************************************
+ ctatbot=0
+ ctatsti=0
+ ctatgat=0
+ mefftatbot=0.25
+ mefftatsti=0.25
+ mefftatgat=0.25
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
+ nfalw='3.62e25*noi_mul'
+ nfblw='8.38e9*noi_mul'
+ nfclw='4e-7*noi_mul'
+ efo=1.265
+ fnto=0.8 )
*
*
*
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model pdio  d (
+level   = 1              tref    = 25
+expli   = 1e10
+xti     = 3              tlev    = 0              tlevc   = 1
+eg      = 1.17           gap1    = 4.73e-4        gap2    = 636
+js      = js_p           jsw     = jsw_p          n       = n_p
+cjo     = cj_p           vj      = pb_p           m       = mj_p
+cjsw    = cjsw_p         php     = pbsw_p         mjsw    = mjsw_p
+rs      = 120p           cta     = cta_p          ctp     = ctp_p
+tpb     = pta_p          tphp    = ptp_p )
*
***************************************************************************
.ends pfetpsp

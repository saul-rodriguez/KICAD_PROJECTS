* Path, Component, Release: cmos7base/rel/HSPICE/models/nfet_psp.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*  7RF/7WL  nfetpsp       1.8V NFET subcircuit
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) nfetpsp l=nnn w=nnn
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
*            +      rsx = 50   <- Body resistance for gcon=1 case
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
*  2. Calculations assume input design width represents width of each
*     finger.
*
*  3. Calculations based on PCELL scaling rules and assume that for a device
*     with an even number of fingers, the source is the outer diffusion.
*
*  4. STI stress calculations are on by default, scale with number of
*     fingers (nf), and assume sa=sb=0.46um and sd=0.52um based on the
*     supported layout PCell.
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
*        |                          |______|/|__________             ----- cwds
*        |                      d1  |      |\|          |            -----
*        |                          |                   |              |
*        |                          |                   |              |
*        |                    |_____|                   |              |
*        |              g1  | |         b1              |     bulk     |
*   gate o-----\/\/\/---o---| |  |------o----\/\/\/-----o-------o      |
*        |      rgate       | |_____          rsb       |              |
*        |                    |     |                   |              |
*        |                          |                   |              |
*        |                          |                   |              |
*        |                      s1  |______|/|__________|              |
*        |                          |      |\|                         |
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
.subckt nfetpsp (d g s b) 
+  l=0.18u w=2u nf=1 par=1 gns=0
+  as=0 ad=0 ps=0 pd=0 nrs=0 nrd=0
+  gcon=1 rsx=50 dtemp=0 rf=0
+  stis=2 sa=0 sb=0
*
.param
+  zad=ad zas=as znrd=nrd znrs=nrs zpd=pd zps=ps zsa=sa zsb=sb
*
* Gate bounded perimeter (identical for source and drain)
+  pgate = '(w+ndelrx)'
*
* STI S/D bounded perimeter (subtract gate bounded from total passed in)
+  pstis = 'max(0,(zps-pgate))'
+  pstid = 'max(0,(zpd-pgate))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=1.3041e-8    kvtw=-0.4509u  kvtl=0.0733u
+  kmb=1.4813e-9    kmbw=0.1193u   kmbl=-1.322u
+  sigvth = '(kvt/sqrt((w-kvtw)*nf*par*(l-kvtl)))'
+  sigbeta= '(kmb/sqrt((w-kmbw)*nf*par*(l-kmbl)))'
+  mmvth0 = agauss(0,sigvth,3)          $ vth0 mis-match
+  mmbeta = agauss(0,sigbeta,3)         $ beta mis-match
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale='(noistdn-min(log(sqrt(w*l*nf*par/noidevan)),0))'
+  noi_mul='(exp(dnoin*noi_scale))'
*
* Gate resistance calculation for all cases (function of w, l and nf)
+  rge1='((pcrsi*(1-gns)+opnpcrsf*gns)/(nf*gcon))*((0.4u+w/(3*gcon))/(l+lwbpc))'
+  rgw1='(10.291*(((w-2*wint_n)*nf*1e6)**(-0.4607)))'
+  rgl1='(3.6232e6*(l-2*lint_n)+0.5159)'
*
* Gate capacitance calculation for rf=1 case (function of w, l and nf)
+  cgw1='(1.36*(85.3e-12*w*nf+0.6e-15))'
+  cgl1='(47233e-12*l+5.9772e-15)/14.048e-15'
*
* Drain-Source capacitance calculation for rf=1 case (function of w, l and nf)
+  cdsw1='(0.5*((9.0e-5*(1e+6*w*nf)**2 + 8.87e-2*(1e+6*w*nf) + 0.4703)*1.0e-15))'
+  cdsl1='(1.6432e-6/l+8.4)/17.53'
*
* Substrate resistance calculation for rf=1 case (function of w, l and nf)
+  rsw1='(1.5*4400*(((w-2*wint_n)*nf*1e6)**(-0.899)))'
+  rsl1='(38.462e6*(l-2*lint_n)+24.423)/46.08'
*
* External resistance term calculation for rf=1 case (function of w, l and nf)
+  rxw1='(0.6*23.642*((w*nf*1e6)**(-0.6235)))'
+  rxl1='(0.3113*((l*1e6)**(-0.6684)))/0.9987'
*
* STI switch to turn on or turn off the stress effect
+  stise = '((gsti==2)*2+(gsti<2)*stis)'
+  ngsti = '((gsti==0))'
*
* RX length calculation
+  rxl = 'max(0.46u,((zas+zad)/w/2))'
*
* STI stress effect calculation based on RX length
+  stist     = '(1-ngsti)*(stise*2.5*exp(-2e6*rxl))'
+  stivsat   = '(72.0m*stist/(nf*2))'
+  sticfl    = '(0.097m*stist/(nf*2))'
+  stivfbl   = '(-0.93m*stist/(nf*2))'
*
m0 d1 g1 s1 b1 nch l=l w=w as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
rdext  d1  d r='(znrd*rsh_n/nf)+ rf*(rxw1*rxl1)'
rsext  s1  s r='(znrs*rsh_n/nf)+ rf*(rxw1*rxl1)'
rgate  g1  g r='(rge1+rgw1*rgl1)'
rsb    b  b1 r='((1-rf)*rsx + rf*rsl1*rsw1)'
cwgd   g   d c='(1e-18+rf*(cgw1*cgl1))'
cwgs   g   s c='(1e-18+rf*(cgw1*cgl1))'
cwds   d   s c='(1e-18+rf*(cdsw1*cdsl1))'
ddb    b1 d1 ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb    b1 s1 ndio area=zas pj=pstis m=nf dtemp=dtemp
*
***************************************************************************
* NFET PSP Model
***************************************************************************
.model nch nmos(
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
+ lap=lint_psp_n
+ lov=lov_psp_n
+ novo=1.35e+25
+ nsubo=3.477e+23
+ rsw1=rsw_psp_n
+ toxo=tox_psp_n
+ toxovo=tox_psp_n
+ uo='uo_psp_n+mmbeta'
+ vfbo='vfb_psp_n+mmvth0'
+ wot=wint_psp_n
+ fol1=fol1_psp_n
+ fol2=fol2_psp_n
+ cjorbot=cj_psp_n
+ cjorsti=cjsw_psp_n
+ cjorgat=cjsg_psp_n
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l =-5.000e-3
+ a1o = 17.22 
+ a1w = 0.000 
+ a2o = 18.90 
+ a3l =-73.00e-3
+ a3o = 1.016 
+ a3w = 0.000 
+ a4l = 3.000 
+ a4o = 1.500e-3
+ a4w = 0.000 
+ agidlw = 3.07
+ alp1l1 = 22.08e-3
+ alp1l2 = 1.127 
+ alp1lexp = 659.2e-3
+ alp1w =-5e-3
+ alp2l1 = 87.89e-3
+ alp2l2 = 179.2e-3
+ alp2lexp = 1.000 
+ alp2w =-5.000 
+ alpl = 18.17e-3
+ alplexp = 934.1e-3
+ alpw = 54.48e-3
+ axl = 450.2e-3
+ axo = 22.12 
+ betw1 = 150.0e-3
+ betw2 =-75.62e-3
+ bgidlo = 26.28
+ cfbo = 775.9e-3
+ cfl = '2.0e-3-sticfl'
+ cflexp = 1.546 
+ cfrw = 0.000 
+ cfw = -130e-3 
+ cgbovl = 0.000 
+ cgidlo = 0.1
+ chibo = 3.100 
+ csl = 15.00e-3
+ cslexp = 1.568 
+ cslw =-26.02e-3
+ cso = 89.41e-3
+ csw = 2.500 
+ ctl = 91.41e-3
+ ctlexp = 67.54e-3
+ ctlw = 5.880e-3
+ cto = 89.90e-3
+ ctw = 45.27e-3
+ dlq =-60.00e-9
+ dnsubo = 0.000 
+ dphibl = 18.68e-3
+ dphiblexp = 735.7e-3
+ dphiblw =-139.4e-6
+ dphibo = 253.7e-3
+ dphibw =-125.7e-3
+ dta = dtemp 
+ dwq = 0.000 
+ fbet1 =-900.0e-3
+ fbet1w =-223.9e-3
+ fbet2 = 1.325 
+ fetao = 1.250 
+ gc2o = 375.0e-3
+ gc3o = 63.00e-3
+ gcoo = 0.000 
+ iginvlw = 0.000 
+ igovw = 0.000 
+ kuo = 0.000 
+ kvsat = 0.000 
+ kvtho = 0.000 
+ lkuo = 0.000 
+ lkvtho = 0.000 
+ llodkuo = 0.000 
+ llodvth = 0.000 
+ lodetao = 1.000 
+ lp1 = 10.00e-9
+ lp1w = 0.000 
+ lp2 = 17.26e-9
+ lpck = 1.355e-9
+ lpckw = 75.37e-3
+ lvarl = 0.000 
+ lvaro = 5.000e-9
+ lvarw = 0.000 
+ mueo = 771.1e-3
+ muew =-1.390e-3
+ npck = 1.152e+24 
+ npckw =-18.59e-3
+ npl = 0.000 
+ npo = 6.000e+25 
+ nslpo = 50.00e-3
+ nsubw =-89.65e-3
+ pkuo = 0.000 
+ pkvtho = 0.000 
+ qmc = 600.0e-3
+ rsbo = 335.9e-3
+ rsgo =-490.3e-3
+ rsw2 =-500.0e-3
+ saref = 3.000e-6
+ sbref = 3.000e-6
+ sta2o = 0.000 
+ stbetl =-20.00e-3
+ stbetlw =-5.000e-3
+ stbeto = 1.400 
+ stbetw =-40.00e-3
+ stbgidlo = 0.000 
+ stcso = 2.500 
+ stetao = 0.000 
+ stigo = 2.000 
+ stmueo =-250.0e-3
+ strso =-100.0e-3
+ stthemuo = 1.200 
+ stthesatl = 97e-3
+ stthesatlw = -5e-3
+ stthesato = 561.8e-3
+ stthesatw =-50e-3
+ stvfbl = 10.00e-3
+ stvfblw = 0
+ stvfbo = 872.8e-6
+ stvfbw = 61.41e-3
+ stxcoro = 2.000 
+ themuo = 1.687 
+ thesatbo = 196.9e-3
+ thesatgo = 212.6e-3
+ thesatl = '0.835+stivsat'
+ thesatlexp = 843.4e-3
+ thesatlw =-0.340e-3
+ thesato = 124.9e-3
+ thesatw =-23.05e-3
+ tkuo = 0.000 
+ vfbl ='vfbl_psp_n+stivfbl'
+ vfblw = vfblw_psp_n
+ vfbw =-47.20e-3
+ vnsubo = 0.000 
+ vpo = 99.54e-3
+ wbet = 22.81e-9
+ wkuo = 0.000 
+ wkvtho = 0.000 
+ wlod = 0.000 
+ wlodkuo = 0.000 
+ wlodvth = 0.000 
+ wseg = 57.42e-9
+ wsegp = 114.0e-12
+ wvarl = 0.000 
+ wvaro = 1.000e-9
+ wvarw = 0.000 
+ xcorl = 680.5e-3
+ xcorlw =-24.00e-3
+ xcoro = 25.70e-3
+ xcorw = 1.222e-15
***************************************************************************
* Junction Diode Parameters
***************************************************************************
+ trj=25
+ imax=1000
***************************************************************************
*    Capacitance Parameters
***************************************************************************
+ vbirbot=pb_n
+ vbirsti=pbsg_n
+ vbirgat=pbsg_n
+ pbot=mj_n
+ psti=mjsg_n
+ pgat=mjsg_n
***************************************************************************
*    Ideal Current Parameters
***************************************************************************
+ phigbot=1.135744
+ phigsti=1.135744
+ phiggat=1.135744
+ idsatrbot=js_n
+ idsatrsti=jsw_n
+ idsatrgat=jsw_n
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
+ nfalw='3.50e25*noi_mul'
+ nfblw='5.00e7*noi_mul'
+ nfclw='-4.00e-9*noi_mul'
+ efo=0.95
+ fnto=1 )
*
*
*
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model ndio  d (
+level   = 1              tref    = 25
+expli   = 1e10
+xti     = 3              tlev    = 0              tlevc   = 1
+eg      = 1.17           gap1    = 4.73e-4        gap2    = 636
+js      = js_n           jsw     = jsw_n          n       = n_n
+cjo     = cj_n           vj      = pb_n           m       = mj_n
+cjsw    = cjsw_n         php     = pbsw_n         mjsw    = mjsw_n
+rs      = 120p           cta     = cta_n          ctp     = ctp_n
+tpb     = pta_n          tphp    = ptp_n )
*
***************************************************************************
.ends nfetpsp

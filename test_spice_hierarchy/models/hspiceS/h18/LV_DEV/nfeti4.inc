* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfeti4.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  nfeti4     1.8V NFET in HV well subcircuit (4 node)
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b  nfeti4 l=nnn w=nnn
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
*            +    lstis = 1    <- Instance flag to control STI stress effects
*                                 on a local level in conjunction with gstis
*                                 global flag (0-> no STI stress effects,
*                                              1-> w/ STI stress effects)
*            +       sa = 0    <- Distance from PC to RX (STI) edge (meters)
*            +       sb = 0    <- Distance from PC to RX (STI) edge (meters)
*            +       sd = 0    <- Finger to finger spacing for NF>1 (meters)
*            +      rsx = 50   <- Body resistance
*            +       rf = 0    <- RF device flag (0-> nfeti4 pcell
*                                                 1-> nfeti4_rf pcell)
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
*                                   |______|/|________
*                                   |      |\|        |
*                                   |------\/\/\/-----o
*                                   |     rddb        |
*                             |_____|                 |
*                      g1   | |                    b1 |             b
*   gate o-----\/\/\/---o---| |  |--------------------o---\/\/\/----o
*              rgate        | |_____                  |    rsb
*                             |     |                 | 	      
*                                   |------\/\/\/-----o
*                                   |        rdsb     |
*                                   |______|/|________|
*                                   |      |\|
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
.subckt nfeti4 d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0 dtemp=0
+                       gcon=1 rsx=50 rf=0 par=1 lstis=1 sa=0 sb=0 sd=0 gns=0 vdnsx=50
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
* Switch to turn ON or OFF the STI stress effects
+  isti = '((gstis==1)&&(lstis==1))||(gstis==2)'
*
* Multi-finger STI scaling equation
+  sa1 = 'max(0.46u,sa)'
+  sa_eff1 = '(sa1+0.5*l*(nf>1)+((nf-1)/3.0)*(sd+l))'
+  sa_eff = 'min(3.0u, max(0.46u,sa_eff1))*(sa != 0)'
+  sb1 = 'max(0.46u,sb)'
+  sb_eff1 = '(sb1+0.5*l*(nf>1)+((nf-1)/3.0)*(sd+l))'
+  sb_eff = 'min(3.0u, max(0.46u,sb_eff1))*(sb != 0)'
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale = '(noistd_n-min(log(sqrt(w*l*nf*par/noideva_n)),0))'
+  noia_mul  = '(exp(dnoin*noi_scale))'
+  noib_mul  = '(exp(dnoin*noi_scale/2))'
+  noic_mul  = '(exp(dnoin*noi_scale/4))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=9e-9    kvtw=0.12u   kvtl=0.075u
+  kmb=0.5e-9  kmbw=0.03u   kmbl=0.05u
+  sigvth  = 'kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta = 'kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0  = agauss(0,sigvth,3)          $ vth0 mis-match
+  mmbeta  = agauss(0,sigbeta,3)         $ beta mis-match
*
* Gate resistance calculation (function of w, l and nf)
+  rge1 = '((pcrsi*(1-gns)+opnpcrsf*gns)/(nf*gcon))*(0.4u+w/(3*gcon))/(l+lwbpc)'
+  rgw1 = '(0.0208*(((w-2*wint_n)*nf)**(-0.5311)))/2.163'
+  rgl1 = '(4.07e6*(l-2*lint_n)+1.564)'
*
* Substrate resistance (turn "off" for RF PCELL)
+  rsx1 = 'rsx*(rf==0) + 0.1*(rf>0)'
*
m0 d g1 s b1  nchi  w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                   mult=nf sa='isti*sa_eff' sb='isti*sb_eff'
rgate  g1  g  r='rge1+rgw1*rgl1'
rsb    b  b1  r=rsx1
ddb    b1  d  ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb    b1  s  ndio area=zas pj=pstis m=nf dtemp=dtemp
rddb   d  b1  r='2e+3/(nf*zad)'
rdsb   s  b1  r='2e+3/(nf*zas)'
*
***************************************************************************
* 1.8V NFET PSP model
***************************************************************************
.model nchi nmos (
+ level = 69
+ version = 102.3
+ tr = 25.00 
********************************************************************
* Switch Settings
********************************************************************
+ swgidl = 1 
+ swigate = 0.000 
+ swimpact = 1.000 
+ swjuncap = 3.000 
*********************************************************
* Process Parameters
**********************************************************
+ lap = lint_ni
+ lov = lov_ni
+ novo = 1.127E+25
+ nsubo = 5.6E+23
+ rsw1 = rsw_ni
+ toxo = tox_ni
+ toxovo = tox_ni
+ uo = 'uo_ni + mmbeta'
+ vfbo = 'vfb_ni + mmvth0'
+ wot = wint_ni
+ vfbl = vfbl_ni
+ vfblw = vfblw_ni
+ fol1 = fol1_ni
+ fol2 = fol2_ni
+ ctl = 170m
+ cfl = 122u
+ thesatl = thesatl_ni
*********************************************************************
* Core Parameters
*********************************************************************
+ a1l =-20.00m
+ a1o = 22.22 
+ a1w = 0.000 
+ a2o = 18.90 
+ a3l =-85.00m
+ a3o = 1.016 
+ a3w = 0.000 
+ a4l = 5.000m
+ a4o = 15.50m
+ a4w =-1.000 
+ agidlw = 23.77m
+ alp1l1 = 22.08m
+ alp1l2 = 1.127 
+ alp1lexp = 659.2m
+ alp1w =-5.000m
+ alp2l1 = 87.89m
+ alp2l2 = 179.2m
+ alp2lexp = 1.000 
+ alp2w =-5.000 
+ alpl = 18.17m
+ alplexp = 934.1m
+ alpw = 54.48m
+ axl = 450.2m
+ axo = 22.12 
+ betw1 = 142.4m
+ betw2 =-79.29m
+ bgidlo = 18.51 
+ cfbo = 775.9m
+ cflexp = 2.775 
+ cfrw = 0.000 
+ cfw =-80.00m
+ cgbovl = 0.000 
+ cgidlo = 0.000 
+ chibo = 3.100 
+ csl = 10.86m
+ cslexp = 1.580 
+ cslw =-30.18m
+ cso = 89.41m
+ csw = 3.287 
+ ctlexp = 67.54m
+ ctlw = 5.880m
+ cto =-52.67m
+ ctw = 45.27m
+ dlq =-60.00n
+ dnsubo =-5.159m
+ dphibl = 19.00m
+ dphiblexp  = 676.5m
+ dphiblw =-8.000m
+ dphibo = 253.7m
+ dphibw =-200.0m
+ dta = dtemp 
+ dwq = 0.000 
+ fbet1 =-1.000 
+ fbet1w =-50.00m
+ fbet2 = 187.6m
+ fetao = 1.066 
+ gc2o = 375.0m
+ gc3o = 63.00m
+ gcoo = 0.000 
+ iginvlw = 0.000 
+ igovw = 0.000 
+ kuo = -28n 
+ kvsat = 600m 
+ kvtho = 6n 
+ lkuo = 0.000 
+ lkvtho = 0.000 
+ llodkuo = 0.000 
+ llodvth = 0.000 
+ lodetao = 1.000 
+ lp1 = 15.54n
+ lp1w = 0.000 
+ lp2 = 10.00n
+ lpck = 2.000n
+ lpckw = 85.40m
+ lvarl = 0.000 
+ lvaro = 0
+ lvarw = 0.000 
+ mueo = 710.0m
+ muew =-2.336m
+ npck = 5.468E+23 
+ npckw =-1.000m
+ npl =-100.0m
+ npo = 6.000E+25 
+ nslpo = 50.00m
+ nsubw =-50.65m
+ pkuo = 0.000 
+ pkvtho = 0.000 
+ qmc = 600.0m
+ rsbo = 266.4m
+ rsgo =-480.1m
+ rsw2 =-500.0m
+ saref = 3.000u
+ sbref = 3.000u
+ sta2o = 0.000 
+ stbetl =-5.295m
+ stbetlw =-7.000m
+ stbeto = 1.463 
+ stbetw =-50.00m
+ stbgidlo = 0.000 
+ stcso = 2.500 
+ stetao = 0.000 
+ stigo = 2.000 
+ stmueo = 154.6m
+ strso = 260.8m
+ stthemuo = 1.013 
+ stthesatl =-9.498m
+ stthesatlw =-5.640m
+ stthesato =  1.231 
+ stthesatw = -133.1m
+ stvfbl = 15.00m
+ stvfblw =-2.000m
+ stvfbo = 872.8u
+ stvfbw = 41.41m
+ stxcoro = 2.000 
+ themuo = 2.400 
+ thesatbo = 10.00m
+ thesatgo = 212.6m
+ thesatlexp = 832.4m
+ thesatlw =-4.100m
+ thesato = 101.8m
+ thesatw =-23.05m
+ tkuo = 0.000 
+ vfbw =-46.36m
+ vnsubo = 0.000 
+ vpo = 99.54m
+ wbet = 20.39n
+ wkuo = 0.000 
+ wkvtho = 0.000 
+ wlod = 0.000 
+ wlodkuo = 0.000 
+ wlodvth = 0.000 
+ wseg = 57.42n
+ wsegp = 1.000n
+ wvarl = 0.000 
+ wvaro = 0
+ wvarw = 0.000 
+ xcorl = 180.5m
+ xcorlw =-24.00m
+ xcoro = 76.97m
+ xcorw = 1.222f
**********************************************************************************
* Junction diode Parameters
**********************************************************************************
+ trj = 25.00 
+ imax = 1.00k
***********************************************************************************
* Capacitance Parameters
***********************************************************************************
+ cjorbot = 1e-12
+ cjorsti = 1e-18
+ cjorgat = cjsg_ni
+ vbirgat = pbsg_ni 
+ pbot = 430.0m
+ psti = 630.0m
+ pgat = mjsg_ni
***********************************************************************************
* Ideal Current Parameters
***********************************************************************************
+ phigbot = 1.136 
+ phigsti = 1.136 
+ phiggat = 1.136 
+ idsatrbot = 80.00n
+ idsatrsti = 50.00f
+ idsatrgat = 50.00f
+ xjunsti = 100.0n
+ xjungat = 100.0n
+ csrhbot = 0.000 
+ csrhsti = 0.000 
+ csrhgat = 0.1m
**************************************************************************************
* Trap Assisted Tunneling Parameters
***************************************************************************************
+ ctatbot = 0.000 
+ ctatsti = 0.000 
+ ctatgat = 1u 
+ mefftatbot = 250.0m
+ mefftatsti = 250.0m
+ mefftatgat = 100m
**************************************************************************************
* Band To Band Tunneling Parameters
**************************************************************************************
+ cbbtbot = 0.000 
+ cbbtsti = 0.000 
+ cbbtgat = 0.000
+ fbbtrbot = 1.0E+9
+ fbbtrsti = 1.0E+9
+ fbbtrgat = 1.0E+9
+ stfbbtbot = 0.000 
+ stfbbtsti = 0.000 
+ stfbbtgat = -0.5m 
*************************************************************************************
* Avalanche Breakdown Parameters
*************************************************************************************
+ vbrbot = 1.001k
+ vbrsti = 1.001k
+ vbrgat = 1.001k
+ pbrbot = 4.000 
+ pbrsti = 4.000 
+ pbrgat = 4.000 
************************************************************************************
* Noise Parameters
*************************************************************************************
+ nfalw = '2.500E+25*noia_mul'
+ nfblw = '800.0E+6*noib_mul'
+ nfclw =  '0*noic_mul'
+ efo = 0.9
+ fnto = 1.000  )
***********************************************************************************
* Extrinsic Source/Drain Diode Model
***********************************************************************************
.model ndio   d (        
+level   = 1              
+tref    = 25
+xti     = 3              
+tlev    = 0              
+tlevc   = 1
+eg      = 1.17           
+gap1    = 4.73e-4        
+gap2    = 636
+js      = js_ni         
+jsw     = jsw_ni        
+n       = n_ni
+cj      = cj_ni         
+pb      = pb_ni         
+mj      = mj_ni
+cjsw    = cjsw_ni       
+php     = pbsw_ni       
+mjsw    = mjsw_ni
+rs      = 120p
+cta     = cta_ni          
+ctp     = ctp_ni          
+tpb     = pta_ni
+tphp    = ptp_ni )
***************************************************************************************
.ends nfeti4

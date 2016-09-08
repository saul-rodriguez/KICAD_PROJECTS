* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfetihvt4.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  nfetihvt4     1.8V HVTNFET in HV well subcircuit (4 node)
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b  nfetihvt4 l=nnn w=nnn
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
.subckt nfetihvt4 d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0 dtemp=0
+                          gcon=1 rsx=50 par=1 lstis=1 sa=0 sb=0 sd=0 vdnsx=50
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
+  noi_scale = '(noistd_nhv-min(log(sqrt(w*l*nf*par/noideva_nhv)),0))'
+  noia_mul  = '(exp(dnoinhv*noi_scale))'
+  noib_mul  = '(exp(dnoinhv*noi_scale/2))'
+  noic_mul  = '(exp(dnoinhv*noi_scale/4))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=12e-9   kvtw=-0.020u   kvtl=0.075u
+  kmb=1e-9    kmbw=-0.030u   kmbl=0.05u
+  sigvth  = 'kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta = 'kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0  = agauss(0,sigvth,3)          $ vth0 mis-match
+  mmbeta  = agauss(0,sigbeta,3)         $ beta mis-match
*
* Gate resistance calculation (function of w, l and nf)
+  rge1 = '(pcrsi/(nf*gcon))*(0.4u+w/(3*gcon))/(l+lwbpc)'
+  rgw1 = '(0.0462*(((w-2*wint_nhvi)*nf)**(-0.4498)))'
+  rgl1 = '((3e6*(l-2*lint_nhvi)+1.2147)/1.64)'

m0 d g1 s b1  nchihvt  w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                      mult=nf sa='isti*sa_eff' sb='isti*sb_eff'
rgate  g1  g  r='rge1+rgw1*rgl1'
rsb    b  b1  r=rsx
ddb    b1  d  ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb    b1  s  ndio area=zas pj=pstis m=nf dtemp=dtemp
rddb   d  b1  r='3.33e+3/(nf*zad)'
rdsb   s  b1  r='3.33e+3/(nf*zas)'

********************************************************************
* 1.8V HVT NFET PSP Model
********************************************************************
.model nchihvt nmos (
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
********************************************************************
* Process Parameters
********************************************************************
+ lap = lint_nhvi
+ lov = lov_nhvi
+ novo = 1.350E+25 
+ nsubo = 7.882E+23 
+ rsw1 = rsw_nhvi 
+ toxo = tox_nhvi
+ toxovo = tox_nhvi
+ uo = 'uo_nhvi + mmbeta'
+ vfbo = 'vfb_nhvi + mmvth0'
+ wot = wint_nhvi
+ vfbl = vfbl_nhvi
+ vfblw = vfblw_nhvi
+ fol1 = fol1_nhvi
+ fol2 = fol2_nhvi
+ thesatl = thesatl_nhvi
*********************************************************************
* Core Parameters
*********************************************************************
+ a1l = 15.00m
+ a1o = 20.22 
+ a1w = 90.99m
+ a2o = 18.90 
+ a3l =-71.00m
+ a3o = 1.016 
+ a3w = 2.000m
+ a4l =-40.00m
+ a4o = 15.00m
+ a4w = 0.000 
+ agidlw = 480.1u 
+ alp1l1 = 8.990m
+ alp1l2 = 560.6m
+ alp1lexp = 501.9m
+ alp1w = 200.0m
+ alp2l1 = 23.16m
+ alp2l2 = 11.59m
+ alp2lexp = 2.750 
+ alp2w =-5.000m
+ alpl = 16.90m
+ alplexp = 1.000 
+ alpw = 100.0m
+ axl = 450.2m
+ axo = 22.12 
+ betw1 = 130.9m
+ betw2 =-90.00m
+ bgidlo = 13.55 
+ cfbo = 600.0m
+ cfl = 1.194u
+ cflexp = 5.000 
+ cfrw = 0.000 
+ cfw =-130.0m
+ cgbovl = 0.000 
+ cgidlo = 0.000 
+ chibo = 3.100 
+ csl = 95.50m
+ cslexp = 835.5m
+ cslw =-1.660m
+ cso = 267.3m
+ csw = 30.00m
+ ctl = 95.35m
+ ctlexp = 100.0m
+ ctlw = 5.880m
+ cto = 5.000m
+ ctw = 45.27m
+ dlq =-60.00n
+ dnsubo = 0.000 
+ dphibl = 10.00m
+ dphiblexp = 939.8m
+ dphiblw = 3.436m
+ dphibo =-71.71m
+ dphibw = 20.00m
+ dta = dtemp
+ dwq = 0.000 
+ fbet1 =-758.6m
+ fbet1w = 250.0m
+ fbet2 =-549.5m
+ fetao = 1.557 
+ gc2o = 375.0m
+ gc3o = 63.00m
+ gcoo = 0.000 
+ iginvlw = 0.000 
+ igovw = 0.000 
+ kuo = -33n 
+ kvsat = 800m
+ kvtho = 5n
+ lkuo = 0.000 
+ lkvtho = 0.000 
+ llodkuo = 0.000 
+ llodvth = 0.000 
+ lodetao = 1.000 
+ lp1 = 25.00n
+ lp1w = 0.000 
+ lp2 = 12.30n
+ lpck = 1.268n
+ lpckw = 75.37m
+ lvarl = 0.000 
+ lvaro = 0
+ lvarw = 0.000 
+ mueo = 620.9m
+ muew =-25.00m
+ npck = 1.000E+24 
+ npckw =-1.680m
+ npl =-100.0m
+ npo = 6.000E+25 
+ nslpo = 50.00m
+ nsubw =-26.48m
+ pkuo = 0.000 
+ pkvtho = 0.000 
+ qmc = 600.0m
+ rsbo = 335.9m
+ rsgo =-490.3m
+ rsw2 = 0.1
+ saref = 3.000u
+ sbref = 3.000u
+ sta2o = 0.000 
+ stbetl =-20.00m
+ stbetlw =-4.000m
+ stbeto = 1.400 
+ stbetw =-87.00m
+ stbgidlo = 0.000 
+ stcso = 2.500 
+ stetao = 0.000 
+ stigo = 2.000 
+ stmueo =-250.0m
+ strso =-100.0m
+ stthemuo = 1.200 
+ stthesatl = 125.0m
+ stthesatlw =-20.00m
+ stthesato = 561.8m
+ stthesatw =-90.00m
+ stvfbl = 20.00m
+ stvfblw = 3.000m
+ stvfbo = 925.0u
+ stvfbw = 10.00m
+ stxcoro = 2.000 
+ themuo = 1.997 
+ thesatbo = 196.9m
+ thesatgo = 212.6m
+ thesatlexp = 803.4m
+ thesatlw =-5.495m
+ thesato = 171.8m
+ thesatw =-10.05m
+ tkuo = 0.000 
+ vfbw = 1.500m
+ vnsubo = 0.000 
+ vpo = 99.54m
+ wbet = 22.81n
+ wkuo = 0.000 
+ wkvtho = 0.000 
+ wlod = 0.000 
+ wlodkuo = 0.000 
+ wlodvth = 0.000 
+ wseg = 100.0n
+ wsegp = 114.0p
+ wvarl = 0.000 
+ wvaro = 0
+ wvarw = 0.000 
+ xcorl = 680.5m
+ xcorlw =-10.82m
+ xcoro = 30.70m
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
+ cjorgat = cjsg_nhvi
+ vbirgat = pbsg_nhvi 
+ pbot = 430.0m
+ psti = 630.0m
+ pgat = mjsg_nhvi
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
+ ctatgat = 0.1m 
+ mefftatbot = 250.0m
+ mefftatsti = 250.0m
+ mefftatgat = 250.0m
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
+ nfalw = '3.6500E+25*noia_mul'
+ nfblw = '950.0E+6*noib_mul'
+ nfclw = '0*noic_mul'
+ efo = 0.9
+ fnto = 1.0 )
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
+js      = js_nhvi         
+jsw     = jsw_nhvi        
+n       = n_nhvi
+cj      = cj_nhvi         
+pb      = pb_nhvi         
+mj      = mj_nhvi
+cjsw    = cjsw_nhvi       
+php     = pbsw_nhvi      
+mjsw    = mjsw_nhvi
+rs      = 120p
+cta     = cta_nhvi         
+ctp     = ctp_nhvi          
+tpb     = pta_nhvi
+tphp    = ptp_nhvi )
***************************************************************************************
.ends nfetihvt4

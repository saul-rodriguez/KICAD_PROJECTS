* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfetshvt.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 1.0
*
*  nfetshvt      1.8V SHVTNFET in SX subcircuit w/diodes
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) nfetshvt l=nnn w=nnn
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
*                                   |	Ddb (Includes internal
*                                   |   FET drain area and STI
*       			    |	bounded perimeter)
*       			    |
*       			    |______|/|__________
*       		      d     |	   |\|	        |
*       			    |------\/\/\/-------o
*       			    |	  rddb          |
*                             |_____|                   |
*                     g1    | |                      b1 |             bulk
*   gate o-----\/\/\/---o---| |  |----------------------o---\/\/\/-----o
*              rgate        | |_____                    |    rsb
*                             |     |                   |
*        			    |------\/\/\/-------o
*        			    |	     rdsb       |
*        		     s      |______|/|__________|
*        			    |	   |\|
*        			    |
*        		            |   Dsb (Includes internal
*        			    |   FET source area and STI
*        			    |	 bounded perimeter) 
*        			    |
*               	            o
*               	         source
*
*
***************************************************************************
.subckt nfetshvt d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                         gcon=1 rsx=50 par=1 lstis=1 sa=0 sb=0 sd=0 dtemp=0
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
+  noi_scale = '(noistd_nshv-min(log(sqrt(w*l*nf*par/noideva_nshv)),0))'
+  noia_mul  = '(exp(dnoinshv*noi_scale))'
+  noib_mul  = '(exp(dnoinshv*noi_scale/3))'
+  noic_mul  = '(exp(dnoinshv*noi_scale/4))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=34e-9   kvtw=0         kvtl=-0.3u
+  kmb=1e-9    kmbw=-0.030u   kmbl=0.05u
+  sigvth  = 'kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta = 'kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0  = agauss(0,sigvth,3)          $ vth0 mis-match
+  mmbeta  = agauss(0,sigbeta,3)         $ beta mis-match
*
* Gate resistance calculation (function of w, l and nf)
+  rge1 = '(pcrsi/(nf*gcon))*(0.4u+w/(3*gcon))/(l+lwbpc)'
+  rgw1 = '(0.0462*(((w-2*wint_nshv)*nf)**(-0.4498)))'
+  rgl1 = '((3e6*(l-2*lint_nshv)+1.2147)/1.64)'

m0 (d g1 s b1) nchshvt  w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                       mult=nf sa='isti*sa_eff' sb='isti*sb_eff'
rgate  g1  g  r='rge1+rgw1*rgl1'
rsb    b  b1  r=rsx
ddb    b1  d  ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb    b1  s  ndio area=zas pj=pstis m=nf dtemp=dtemp
rddb   d  b1  r='2e+3/(nf*zad)'
rdsb   s  b1  r='2e+3/(nf*zas)'

********************************************************************
* 1.8V SHVT NFET PSP Model
********************************************************************
.model nchshvt nmos (
+ level = 69
+ version = 102.3
+ tr = 25.00 
********************************************************************
* Switch Settings
********************************************************************
+ swgidl = 1.000
+ swigate = 0.000
+ swimpact = 1.000
+ swjuncap = 3.000
********************************************************************
* Process Parameters
********************************************************************
+ lap = lint_nshv
+ lov = lov_nshv
+ novo = 1.000E+25 
+ nsubo = 4.35E+23 
+ rsw1 = rsw_nshv 
+ toxo = tox_nshv
+ toxovo = tox_nshv
+ uo = 'uo_nshv + mmbeta'
+ vfbo = 'vfb_nshv + mmvth0' 
+ wot = wint_nshv
+ vfbl = vfbl_nshv
+ vfblw = vfblw_nshv
+ fol1 = fol1_nshv
+ fol2 = fol2_nshv
+ thesatl = thesatl_nshv
*********************************************************************
* Core Parameters
*********************************************************************
+ a1l = -5.000m
+ a1o = 13.93
+ a1w = 2.000m
+ a2o = 19.30
+ a3l = -70.85m
+ a3o = 1.015
+ a3w = 1.000m
+ a4l = 10.00m
+ a4o = 15.00m
+ a4w = 0.000
+ agidlw = 207.7u
+ alp1l1 = 20.20m
+ alp1l2 = 130.1m
+ alp1lexp = 200.9m
+ alp1w = 50.00m
+ alp2l1 = 23.16m
+ alp2l2 = 7.943m
+ alp2lexp = 2.092
+ alp2w = -5.000m
+ alpl = 60.35u
+ alplexp = 3.118
+ alpw = 50.00m
+ axl = 650.0m
+ axo = 20.00
+ betw1 = 28.00m
+ betw2 = -30.00m
+ bgidlo = 15.86
+ cfbo = 426.6m
+ cfl = 8.8u
+ cflexp = 4.228
+ cfrw = 0.000
+ cfw = -50.00m
+ cgbovl = 0.000
+ cgidlo = 0.000
+ chibo = 3.100
+ csl = 145.5m
+ cslexp = 835.5m
+ cslw = 30.00m
+ cso = 0.000
+ csw = 0.000
+ ctl = 6.7m
+ ctlexp = 1.989
+ ctlw = 1.000m
+ cto = 5.000m
+ ctw = 45.27m
+ dlq = -50.00n
+ dnsubo = 0.000
+ dphibl = 9.250m
+ dphiblexp = 2.010
+ dphiblw = 2.750m
+ dphibo = 0.000
+ dphibw = 10.00m
+ dta = dtemp
+ dwq = 0.000
+ fbet1 = 800.0m
+ fbet1w = -250.0m
+ fbet2 = 849.5m
+ fetao = 1.050
+ gc2o = 375.0m
+ gc3o = 63.00m
+ gcoo = 0.000
+ iginvlw = 0.000
+ igovw = 0.000
+ kuo = -33n
+ kvsat = 700m
+ kvtho = 12n
+ lkuo = 0.000
+ lkvtho = 0.000
+ llodkuo = 0.000
+ llodvth = 0.000
+ lodetao = 1.000
+ lp1 = 40.00n
+ lp1w = 250.0m
+ lp2 = 25.00n
+ lpck = 163.0n
+ lpckw = 28.25m
+ lvarl = 0.000
+ lvaro = 0.000
+ lvarw = 0.000
+ mueo = 1.216
+ muew = -30.00m
+ npck = 8.000E+23
+ npckw = -1.576m
+ npl = 0.000
+ npo = 6.000E+25
+ nslpo = 50.00m
+ nsubw = -9.050m
+ pkuo = 0.000
+ pkvtho = 0.000
+ qmc = 600.0m
+ rsbo = 15.90m
+ rsgo = -500.0m
+ rsw2 = 0.000
+ saref = 3.000u
+ sbref = 3.000u
+ sta2o = 0.000
+ stbetl = -15.00m
+ stbetlw = 5.000m
+ stbeto = 1.650
+ stbetw = -27.00m
+ stbgidlo = -0.0015
+ stcso = 3.000
+ stetao = 0.000
+ stigo = 2.000
+ stmueo = -110.0m
+ strso = 10.00m
+ stthemuo = 1.000
+ stthesatl = -50.00m
+ stthesatlw = 7.000m
+ stthesato = 1.500
+ stthesatw = -10.00m
+ stvfbl = 95.00m
+ stvfblw = 3.200m
+ stvfbo = 570.0u
+ stvfbw = -15.00m
+ stxcoro = 2.000
+ themuo = 1.644
+ thesatbo = -1.000
+ thesatgo = 212.6m
+ thesatlexp = 1.297
+ thesatlw = -14.00m
+ thesato = 400.8m
+ thesatw = 100.0m
+ tkuo = 0.000
+ vfbw = -12.90m
+ vnsubo = 0.000
+ vpo = 50.00m
+ wbet = 15.00n
+ wkuo = 0.000
+ wkvtho = 0.000
+ wlod = 0.000
+ wlodkuo = 0.000
+ wlodvth = 0.000
+ wseg = 5.000n
+ wsegp = 114.0p
+ wvarl = 0.000
+ wvaro = 0.000
+ wvarw = 0.000
+ xcorl = -50.00m
+ xcorlw = -10.82m
+ xcoro = 100.0m
+ xcorw = 0.000
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
+ cjorgat = cjsg_nshv
+ vbirgat = pbsg_nshv 
+ pbot = 430.0m
+ psti = 630.0m
+ pgat = mjsg_nshv
***********************************************************************************
*Ideal Current Parameters
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
+ csrhgat = 10m
**************************************************************************************
* Trap Assisted Tunneling Parameters
***************************************************************************************
+ ctatbot = 0.000 
+ ctatsti = 0.000 
+ ctatgat = 0.5m
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
+ stfbbtgat = 0.000 
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
+ nfalw = '9.00E+25*noia_mul' 
+ nfblw = '700E+6*noib_mul'
+ nfclw = '0*noic_mul'
+ efo = 1.0
+ fnto = 1.000 )
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
+js      = js_nshv         
+jsw     = jsw_nshv        
+n       = n_nshv
+cj      = cj_nshv         
+pb      = pb_nshv         
+mj      = mj_nshv
+cjsw    = cjsw_nshv       
+php     = pbsw_nshv      
+mjsw    = mjsw_nshv
+rs      = 120p
+cta     = cta_nshv         
+ctp     = ctp_nshv          
+tpb     = pta_nshv
+tphp    = ptp_nshv )
***********************************************************************************
.ends nfetshvt

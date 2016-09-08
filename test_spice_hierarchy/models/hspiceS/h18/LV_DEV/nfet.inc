* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfet.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*  nfet       1.8V NFET in SX subcircuit w/diodes
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) nfet l=nnn w=nnn
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
.subckt nfet d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0 dtemp=0
+                     gcon=1 rsx=50 rf=0 par=1 lstis=1 sa=0 sb=0 sd=0 gns=0
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
+  kvt=10e-9     kvtw=0.06u    kvtl=0.075u
+  kmb=0.1e-9    kmbw=0.01u    kmbl=0.05u
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
m0 (d g1 s b1) nch  w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                   mult=nf sa='isti*sa_eff' sb='isti*sb_eff'
rgate  g1  g  r='rge1+rgw1*rgl1'
rsb    b  b1  r=rsx1
ddb    b1  d  ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb    b1  s  ndio area=zas pj=pstis m=nf dtemp=dtemp
rddb   d  b1  r='2e+3/(nf*zad)'
rdsb   s  b1  r='2e+3/(nf*zas)'

********************************************************************
* 1.8V NFET PSP Model
********************************************************************
.model nch nmos (
+ level = 69
+ version = 102.3
+ tr = 25
********************************************************************
* Switch Settings
********************************************************************
+ swgidl = 1
+ swigate = 0
+ swimpact = 1
+ swjuncap = 3
********************************************************************
* Process Parameters
********************************************************************
+ lap = lint_n
+ lov = lov_n
+ novo = 1.127E+25
+ nsubo = 5E+23
+ rsw1 = rsw_n
+ toxo = tox_n
+ toxovo = tox_n
+ uo = 'uo_n + mmbeta'
+ vfbo = 'vfb_n + mmvth0' 
+ wot = wint_n
+ vfbl = vfbl_n
+ vfblw = vfblw_n
+ fol1 = fol1_n
+ fol2 = fol2_n
+ ctl = 170m
+ cfl = 22.5u
+ thesatl = thesatl_n
*********************************************************************
* Core Parameters
*********************************************************************
+ a1l = -0.028
+ a1o = 22.22
+ a1w = 0.1
+ a2o = 18.9
+ a3l = -0.085
+ a3o = 1.016
+ a3w = 0.01
+ a4l = 0.005
+ a4o = 0.0155
+ a4w = -1
+ agidlw = 0.01847
+ alp1l1 = 0.02208
+ alp1l2 = 1.127
+ alp1lexp = 0.6592
+ alp1w = -0.005
+ alp2l1 = 0.08789
+ alp2l2 = 0.1792
+ alp2lexp = 1
+ alp2w = -5
+ alpl = 0.01817
+ alplexp = 0.9341
+ alpw = -0.0255
+ axl = 0.4502
+ axo = 22.12
+ betw1 = 0.1597
+ betw2 = -0.08715
+ bgidlo = 18.38
+ cfbo = 0.7759
+ cflexp = 3.682
+ cfrw = 0
+ cfw = -0.08
+ cgbovl = 0
+ cgidlo = 0
+ chibo = 3.1
+ csl = 0.00186
+ cslexp = 1.58
+ cslw = -0.0222
+ cso = 0.08941
+ csw = 3.46
+ ctlexp = 0.06754
+ ctlw = 0.00588
+ cto = -0.05267
+ ctw = 0.04527
+ dlq = -6.5E-08
+ dnsubo = -0.005159
+ dphibl = 0.019
+ dphiblexp = 0.6765
+ dphiblw = -0.01961
+ dphibo = 0.2407
+ dphibw = -0.02271
+ dta = dtemp
+ dwq = 0
+ fbet1 = -1
+ fbet1w = 0.05
+ fbet2 = 0.1876
+ fetao = 1.066
+ gc2o = 0.375
+ gc3o = 0.063
+ gcoo = 0
+ iginvlw = 0
+ igovw = 0
+ kuo = -28n
+ kvsat = 600m
+ kvtho = 6n
+ lkuo = 0
+ lkvtho = 0
+ llodkuo = 0
+ llodvth = 0
+ lodetao = 1
+ lp1 = 2.054E-08
+ lp1w = 1E-08
+ lp2 = 1E-08
+ lpck = 2E-09
+ lpckw = 0.1
+ lvarl = 0
+ lvaro = 0
+ lvarw = 0
+ mueo = 0.71
+ muew = -1.072E-06
+ npck = 5.468E+23
+ npckw = 0.03228
+ npl = -0.1
+ npo = 8E+25
+ nslpo = 0.05
+ nsubw = -0.02269
+ pkuo = 0
+ pkvtho = 0
+ qmc = 0.6
+ rsbo = 0.2664
+ rsgo = -0.4801
+ rsw2 = -0.5
+ saref = 3E-06
+ sbref = 3E-06
+ sta2o = 0
+ stbetl = -0.005
+ stbetlw = -0.0085
+ stbeto = 1.463
+ stbetw = -0.027
+ stbgidlo = 0
+ stcso = 2.5
+ stetao = 0
+ stigo = 2
+ stmueo = 0.1546
+ strso = 0.2008
+ stthemuo = 1.013
+ stthesatl = -0.0135
+ stthesatlw = 0.00564
+ stthesato = 1.231
+ stthesatw = -0.1331
+ stvfbl = 0.01
+ stvfblw = 0.001
+ stvfbo = 0.0008728
+ stvfbw = 0.0254
+ stxcoro = 2
+ themuo = 2.4
+ thesatbo = 0.1
+ thesatgo = 0.2126
+ thesatlexp = 0.8524
+ thesatlw = 0.00566
+ thesato = 0.0108
+ thesatw = -0.08
+ tkuo = 0
+ vfbw = -0.011
+ vnsubo = 0
+ vpo = 0.09954
+ wbet = 2.039E-08
+ wkuo = 0
+ wkvtho = 0
+ wlod = 0
+ wlodkuo = 0
+ wlodvth = 0
+ wseg = 1E-08
+ wsegp = 5.444E-09
+ wvarl = 0
+ wvaro = 0
+ wvarw = 0
+ xcorl = 0.1805
+ xcorlw = -0.024
+ xcoro = 0.07697
+ xcorw = 1.222E-15
**********************************************************************************
* Junction diode Parameters
**********************************************************************************
+ trj = 25
+ imax = 1000
***********************************************************************************
* Capacitance Parameters
***********************************************************************************
+ cjorbot = 1e-12
+ cjorsti = 1e-18
+ cjorgat = cjsg_n
+ vbirgat = pbsg_n 
+ pbot = 430.0m
+ psti = 630.0m
+ pgat = mjsg_n
***********************************************************************************
* Ideal Current Parameters
***********************************************************************************
+ phigbot = 1.136
+ phigsti = 1.136
+ phiggat = 1.136
+ idsatrbot = 8E-08
+ idsatrsti = 5E-14
+ idsatrgat = 5E-14
+ xjunsti = 1E-07
+ xjungat = 1E-07
+ csrhbot = 0
+ csrhsti = 0
+ csrhgat = 0.1m
**************************************************************************************
* Trap Assisted Tunneling Parameters
***************************************************************************************
+ ctatbot = 0
+ ctatsti = 0
+ ctatgat = 1u
+ mefftatbot = 0.25
+ mefftatsti = 0.25
+ mefftatgat = 100m
**************************************************************************************
* Band To Band Tunneling Parameters
**************************************************************************************
+ cbbtbot = 0
+ cbbtsti = 0
+ cbbtgat = 0
+ fbbtrbot = 1E+09
+ fbbtrsti = 1E+09
+ fbbtrgat = 1E+09
+ stfbbtbot = 0
+ stfbbtsti = 0
+ stfbbtgat = -0.5m
*************************************************************************************
* Avalanche Breakdown Parameters
*************************************************************************************
+ vbrbot = 1001
+ vbrsti = 1001
+ vbrgat = 1001
+ pbrbot = 4
+ pbrsti = 4
+ pbrgat = 4
************************************************************************************
* Noise Parameters
*************************************************************************************
+ nfalw = '1.500E+25*noia_mul'
+ nfblw = '100.0E+6*noib_mul'
+ nfclw =  '0*noic_mul'
+ efo = 0.9
+ fnto = 1 )
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
+js      = js_n         
+jsw     = jsw_n        
+n       = n_n
+cj      = cj_n         
+pb      = pb_n         
+mj      = mj_n
+cjsw    = cjsw_n       
+php     = pbsw_n       
+mjsw    = mjsw_n
+rs      = 120p
+cta     = cta_n          
+ctp     = ctp_n          
+tpb     = pta_n
+tphp    = ptp_n )
***********************************************************************************
.ends nfet

* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfet.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*  pfet       1.8V PFET in SX subcircuit w/diodes
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) pfet l=nnn w=nnn
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
*            +       rf = 0    <- RF device flag (0-> pfet pcell
*                                                 1-> pfet_rf pcell)
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
*       			    |______|\|__________
*       		      d     |	   |/|	        |
*       			    |------\/\/\/-------o
*       			    |	  rddb          |
*                             |_____|                   |
*                     g1    | |                      b1 |             bulk
*   gate o-----\/\/\/---o---| |  |----------------------o---\/\/\/-----o
*              rgate        | |_____                    |    rsb
*                             |     |                   |
*        			    |------\/\/\/-------o
*        			    |	     rdsb       |
*        		     s      |______|\|__________|
*        			    |	   |/|
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
.subckt pfet d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrs=0 nrd=0
+                     gcon=1 rsx=50 rf=0 par=1 dtemp=0 gns=0
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
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale = '(noistd_p-min(log(sqrt(w*l*nf*par/noideva_p)),0))'
+  noia_mul  = '(exp(dnoip*noi_scale))'
+  noib_mul  = '(exp(dnoip*noi_scale/2))'
+  noic_mul  = '(exp(dnoip*noi_scale/4))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=0.65e-8     kvtw=0.13u    kvtl=0.14u
+  kmb=4.8072e-10  kmbw=-0.15u   kmbl=0
+  sigvth  = 'kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta = 'kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0  = agauss(0,sigvth,3)          $ vth0 mis-match
+  mmbeta  = agauss(0,sigbeta,3)         $ beta mis-match
*
* Gate resistance calculation (function of w, l and nf)
+  rge1 = '((pcrsi*(1-gns)+oppcrsf*gns)/(nf*gcon))*(0.42u+w/(3*gcon))/(l+lwbpc)'
+  rgw1 = '(28.827*(((w-2*wint_p)*nf*1e6)**(-0.50)))'
+  rgl1 = '(13*1e6*(l-2*lint_p)+0.1324)/1.665'
*
* Substrate resistance (turn "off" for RF PCELL)
+  rsx1 = 'rsx*(rf==0) + 0.1*(rf>0)'

m0 (d g1 s b1) pch  w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
rgate  g1  g  r='rge1+rgw1+rgl1'
rsb    b  b1  r=rsx1
ddb    d  b1  pdio area=zad pj=pstid m=nf dtemp=dtemp
dsb    s  b1  pdio area=zas pj=pstis m=nf dtemp=dtemp
rddb   d  b1  r='1e+3/(zad*nf)'
rdsb   s  b1  r='1e+3/(zas*nf)'
*
***************************************************************************
* 1.8V PFET PSP Model
***************************************************************************
.model pch pmos (
+ level = 69
+ version = 102.3
+ tr = 25
***************************************************************************
* Switch Settings
***************************************************************************
+ swgidl = 1.000 
+ swigate = 0.000 
+ swimpact = 1.000 
+ swjuncap = 3.000 
***************************************************************************
* Process Parameters
***************************************************************************
+ lap = lint_p
+ lov = lov_p
+ novo = 1E+25
+ nsubo = 5.45E+23
+ rsw1 = rsw_p
+ toxo = tox_p
+ toxovo = tox_p
+ uo = uo_p
+ vfbo = vfb_p 
+ wot = wint_p
+ vfbl = vfbl_p
+ vfblw = vfblw_p
+ fol1 = fol1_p
+ fol2 = fol2_p
+ ctl = 2m
+ cfl = 1.125m
+ thesatl = thesatl_p
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l =-34.18m
+ a1o = 400.0m
+ a1w = 30.00m
+ a2o = 17.17 
+ a3l =-53.57m
+ a3o = 1.654 
+ a3w =-10.83m
+ a4l =-150.0m
+ a4o = 123.0m
+ a4w =-2.500 
+ agidlw = 613.3u
+ alp1l1 = 6.116m
+ alp1l2 = 1.243 
+ alp1lexp = 654.4m
+ alp1w = 186.1m
+ alp2l1 = 0.000 
+ alp2l2 = 100.0m
+ alp2lexp = 1.000 
+ alp2w = 0.000 
+ alpl = 16.56m
+ alplexp = 904.6m
+ alpw = 64.25m
+ axl = 880.6m
+ axo = 20.00 
+ betw1 = 1.444f
+ betw2 =-384.0m
+ bgidlo = 14.31 
+ cfbo = 600.0m
+ cflexp = 1.730 
+ cfrw = 0.000 
+ cfw =-50.00m
+ cgbovl = 0.000 
+ cgidlo = 0.000 
+ chibo = 3.100 
+ csl = 251.4m
+ cslexp = 309.5m
+ cslw = 28.99m
+ cso = 426.0m
+ csw = 138.0m
+ ctlexp = 1.000 
+ ctlw = 0.000 
+ cto = 96.57m
+ ctw =-50.00m
+ dlq =-61.50n
+ dnsubo = 12.00m
+ dphibl = 47.23u
+ dphiblexp = 3.499 
+ dphiblw = 0.000 
+ dphibo = 72.53m
+ dphibw = 0.000 
+ dta = dtemp
+ dwq = 0.000 
+ fbet1 =-12.98 
+ fbet1w = 443.7m
+ fbet2 = 186.6m
+ fetao = 1.250 
+ gc2o = 375.0m
+ gc3o = 63.00m
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
+ lp1 = 570.4p
+ lp1w = 100.0m
+ lp2 = 535.2n
+ lpck = 462.4p
+ lpckw = 722.9m
+ lvarl = 0.000 
+ lvaro = 0.000 
+ lvarw = 0.000 
+ mueo = 2.458 
+ muew =-68.61m
+ npck = 1.470E+24 
+ npckw =-12.70m
+ npl =-10.00m
+ npo = 1.000E+26 
+ nslpo = 50.00m
+ nsubw =-17.00m
+ pkuo = 0.000 
+ pkvtho = 0.000 
+ qmc = 790.0m
+ rsbo = 554.3m
+ rsgo =-105.1m
+ rsw2 = 10.00m
+ saref = 1.000u
+ sbref = 1.000u
+ sta2o = 0.000 
+ stbetl =-10.00m
+ stbetlw = 3.000m
+ stbeto = 1.107 
+ stbetw =-5.045m
+ stbgidlo = 0.000 
+ stcso = 1.100 
+ stetao = 0.000 
+ stigo = 2.000 
+ stmueo =-119.0m
+ strso = 0.000 
+ stthemuo = 578.0m
+ stthesatl =-15.34m
+ stthesatlw = 11.29m
+ stthesato = 1.739 
+ stthesatw = 0.000 
+ stvfbl = 15.00m
+ stvfblw =-1.000m
+ stvfbo = 811.5u
+ stvfbw = 20.00m
+ stxcoro = 1.000 
+ themuo = 1.162 
+ thesatbo = 0.000 
+ thesatgo = 510.4m
+ thesatlexp = 1.061 
+ thesatlw =-19.75m
+ thesato = 0.000 
+ thesatw = 522.2m
+ tkuo = 0.000 
+ vfbw =-7.874m
+ vnsubo = 0.000 
+ vpo = 10.00m
+ wbet = 1.082u
+ wkuo = 0.000 
+ wkvtho = 0.000 
+ wlod = 0.000 
+ wlodkuo = 0.000 
+ wlodvth = 0.000 
+ wseg = 7.000n
+ wsegp = 10.00n
+ wvarl = 0.000 
+ wvaro = 0.000 
+ wvarw = 0.000 
+ xcorl = 351.0m
+ xcorlw = 0.000 
+ xcoro = 44.32m
+ xcorw = 0.000 
***************************************************************************
* Junction diode Parameters
***************************************************************************
+ trj = 25.00 
+ imax = 1.00k
***************************************************************************
* Capacitance Parameters
***************************************************************************
+ cjorbot = 1.150m
+ cjorsti = 100.0p
+ cjorgat = cjsg_p
+ vbirbot = 1.000 
+ vbirsti = 1.000 
+ vbirgat = pbsg_p
+ pbot = 500.0m
+ psti = 500.0m
+ pgat = mjsg_p
***************************************************************************
* Ideal Current Parameters
***************************************************************************
+ phigbot = 1.148 
+ phigsti = 1.148 
+ phiggat = 1.148 
+ idsatrbot = 1n
+ idsatrsti = 1a
+ idsatrgat = 1a
+ xjunsti = 100.0n
+ xjungat = 100.0n
+ csrhbot = 0.000 
+ csrhsti = 0.000 
+ csrhgat = 0.000 
***************************************************************************
* Trap Assisted Tunneling Parameters
***************************************************************************
+ ctatbot = 0.000 
+ ctatsti = 0.000 
+ ctatgat = 60u 
+ mefftatbot = 250.0m
+ mefftatsti = 250.0m
+ mefftatgat = 250.0m
***************************************************************************
* Band To Band Tunneling Parameters
***************************************************************************
+ cbbtbot = 0.000 
+ cbbtsti = 0.000 
+ cbbtgat = 0.000
+ fbbtrbot = 1.0E+9
+ fbbtrsti = 1.0E+9
+ fbbtrgat = 1.0E+9
+ stfbbtbot = 0.000 
+ stfbbtsti = 0.000 
+ stfbbtgat = 0.000 
***************************************************************************
* Avalanche Breakdown Parameters
***************************************************************************
+ vbrbot = 1.001k
+ vbrsti = 1.001k
+ vbrgat = 1.001k
+ pbrbot = 4.000 
+ pbrsti = 4.000 
+ pbrgat = 4.000 
***************************************************************************
* Noise Parameters
***************************************************************************
+ nfalw = '2.00E+25*noia_mul'
+ nfblw = '800.0E+6*noib_mul'
+ nfclw = '50n*noic_mul'
+ fnto = 800.0m
+ efo = 1.1 )
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model pdio  d  (
+level   = 1              
+tref    = 25
+xti     = 3              
+tlev    = 0              
+tlevc   = 1
+eg      = 1.17           
+gap1    = 4.73e-4        
+gap2    = 636
+js      = js_p         
+jsw     = jsw_p        
+n       = n_p
+cj      = cj_p         
+pb      = pb_p         
+mj      = mj_p
+cjsw    = cjsw_p       
+php     = pbsw_p       
+mjsw    = mjsw_p
+rs      = 200n
+cta     = cta_p          
+ctp     = ctp_p          
+tpb     = pta_p
+tphp    = ptp_p )
***************************************************************************
.ends pfet

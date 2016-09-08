* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfethvt.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*  pfethvt       1.8V HVTPFET in SX subcircuit w/diodes
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) pfethvt l=nnn w=nnn
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
.subckt pfethvt d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrs=0 nrd=0
+                        gcon=1 rsx=50 par=1 dtemp=0
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
+  noi_scale = '(noistd_phv-min(log(sqrt(w*l*nf*par/noideva_phv)),0))'
+  noia_mul  = '(exp(dnoiphv*noi_scale))'
+  noib_mul  = '(exp(dnoiphv*noi_scale/2))'
+  noic_mul  = '(exp(dnoiphv*noi_scale/4))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=0.7835e-8   kvtw=0.13u    kvtl=0.12u
+  kmb=4.8072e-10  kmbw=-0.15u   kmbl=0
+  sigvth  = 'kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta = 'kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0  = agauss(0,sigvth,3)          $ vth0 mis-match
+  mmbeta  = agauss(0,sigbeta,3)         $ beta mis-match
*
* Gate resistance calculation (function of w, l and nf)
+  rge1 = '(pcrsi/(nf*gcon))*(0.42u+w/(3*gcon))/(l+lwbpc)'
+  rgw1 = '(27.227*(((w-2*wint_phv)*nf*1e6)**(-0.55)))'
+  rgl1 = '((10e6*(l-2*lint_phv)+0.1324)/1.665)'

m0 (d g1 s b1) pchhvt w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
rgate  g1  g  r='rge1+rgw1+rgl1'
rsb    b  b1  r=rsx
ddb    d  b1  pdio area=zad pj=pstid m=nf dtemp=dtemp
dsb    s  b1  pdio area=zas pj=pstis m=nf dtemp=dtemp
rddb   d  b1  r='50e+3/(zad*nf)'
rdsb   s  b1  r='50e+3/(zas*nf)'

***************************************************************************
* 1.8V HVT PFET PSP Model
***************************************************************************
.model pchhvt pmos (
+ level = 69
+ version = 102.3
+ tr = 25
***************************************************************************
* Switch Settings
***************************************************************************
+ swgidl = 1 
+ swigate = 0.000 
+ swimpact = 1.000 
+ swjuncap = 3.000 
***************************************************************************
* Process Parameters
***************************************************************************
+ ctl = 19m 
+ fol1 = fol1_phv
+ fol2 = fol2_phv
+ lap = lint_phv
+ lov = lov_phv
+ rsw1 = rsw_phv 
+ toxo = tox_phv 
+ toxovo = tox_phv
+ uo = 'uo_phv + mmbeta'
+ vfbo = 'vfb_phv + mmvth0' 
+ vfbl = vfbl_phv
+ vfblw = vfblw_phv
+ thesatl = thesatl_phv
+ wot = wint_phv
*********************************************************************
* Core Parameters
*********************************************************************
+ a1l =-46.84m
+ a1o = 8.486 
+ a1w = 75.77m
+ a2o = 22.93 
+ a3l =-53.75m
+ a3o = 1.231 
+ a3w =-5.218m
+ a4l =-100.0m
+ a4o = 75.00m
+ a4w = 100.0m
+ agidlw = 1.567m 
+ alp1l1 = 5.212m
+ alp1l2 = 1.243 
+ alp1lexp = 1.284 
+ alp1w = 0.000 
+ alp2l1 = 0.000 
+ alp2l2 = 100.0m
+ alp2lexp = 1.000 
+ alp2w = 0.000 
+ alpl = 16.98m
+ alplexp = 800.6m
+ alpw = 0.000 
+ axl = 300.0m
+ axo = 14.64 
+ betw1 = 54.00m
+ betw2 =-140.0m
+ bgidlo = 13.67 
+ cfbo = 500.0m
+ cfl = 268.3u
+ cflexp = 2.314 
+ cfrw = 0.000 
+ cfw = 0.000 
+ cgbovl = 0.000 
+ cgidlo = 0.000 
+ chibo = 3.100 
+ csl = 0.000 
+ cslexp = 309.5m
+ cslw = 28.99m
+ cso = 426.0m
+ csw = 138.0m
+ ctlexp = 1.000 
+ ctlw = 0.000 
+ cto = 0.000 
+ ctw = 0.000 
+ dlq =-61.50n
+ dnsubo = 12.00m
+ dphibl = 105.7u
+ dphiblexp = 3.004 
+ dphiblw =-3.634m
+ dphibo = 72.53m
+ dphibw = 57.52m
+ dta = dtemp
+ dwq = 0.000 
+ fbet1 =-2.869 
+ fbet1w = 120.0m
+ fbet2 = 432.4m
+ fetao = 1.000 
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
+ lp1 = 12.81n
+ lp1w = 71.97m
+ lp2 = 223.7n
+ lpck = 1.815n
+ lpckw = 2.685 
+ lvarl = 0.000 
+ lvaro = 0.000 
+ lvarw = 0.000 
+ mueo = 1.755 
+ muew =-100.0m
+ novo = 7.632E+24 
+ npck = 1.328E+24 
+ npckw =-150.5m
+ npl =-10.00m
+ npo = 1.000E+26 
+ nslpo = 50.00m
+ nsubo = 1.189E+24 
+ nsubw =-7.655m
+ pkuo = 0.000 
+ pkvtho = 0.000 
+ qmc = 400.0m
+ rsbo = 0.000 
+ rsgo =-105.1m
+ rsw2 = 38.74m
+ saref = 1.000u
+ sbref = 1.000u
+ sta2o = 0.000 
+ stbetl =-15.00m
+ stbetlw = 9.583m
+ stbeto = 1.041 
+ stbetw =-55.98m
+ stbgidlo = 0.000 
+ stcso = 1.100 
+ stetao = 0.000 
+ stigo = 2.000 
+ stmueo =-119.0m
+ strso = 0.000 
+ stthemuo = 500.0m
+ stthesatl = 51.29m
+ stthesatlw = 85.49m
+ stthesato = 1.000 
+ stthesatw =-162.3m
+ stvfbl = 15.91m
+ stvfblw = 656.7u
+ stvfbo = 675.6u
+ stvfbw = 11.47m
+ stxcoro = 1.000 
+ themuo = 1.559 
+ thesatbo = 0.000 
+ thesatgo = 463.0m
+ thesatlexp = 1.506 
+ thesatlw = 75.73m
+ thesato = 0.000 
+ thesatw =-146.8m
+ tkuo = 0.000 
+ vfbw =-1.000u
+ vnsubo = 0.000 
+ vpo = 10.00m
+ wbet = 93.50n
+ wkuo = 0.000 
+ wkvtho = 0.000 
+ wlod = 0.000 
+ wlodkuo = 0.000 
+ wlodvth = 0.000 
+ wseg = 7.000n
+ wsegp = 591.6n
+ wvarl = 0.000 
+ wvaro = 0.000 
+ wvarw = 0.000 
+ xcorl = 100.0m
+ xcorlw = 19.76m
+ xcoro = 70.00m
+ xcorw =-194.8m
*********************************************************************
* Junction diode Parameters
*********************************************************************
+ trj = 25.00 
+ imax = 1.00k
*********************************************************************
* Capacitance Parameters
*********************************************************************
+ cjorbot = 1e-12
+ cjorsti = 1e-18
+ cjorgat = cjsg_phv
+ vbirbot = 1.000
+ vbirsti = 1.000
+ vbirgat = pbsg_phv 
+ pbot = 430.0m
+ psti = 630.0m
+ pgat = mjsg_phv
*********************************************************************
* Ideal Current Parameters
*********************************************************************
+ phigbot = 1.16 
+ phigsti = 1.16
+ phiggat = 1.16 
+ idsatrbot = 1.000p
+ idsatrsti = 1.000a
+ idsatrgat = 1.000a
+ xjunsti = 100.0n
+ xjungat = 100.0n
+ csrhbot = 0.000 
+ csrhsti = 0.000 
+ csrhgat = 0.000 
*********************************************************************
* Trap Assisted Tunneling Parameters
*********************************************************************
+ ctatbot = 0.000 
+ ctatsti = 0.000 
+ ctatgat = 100.0u 
+ mefftatbot = 250.0m
+ mefftatsti = 250.0m
+ mefftatgat = 250.0m
*********************************************************************
* Band To Band Tunneling Parameters
*********************************************************************
+ cbbtbot = 0.000 
+ cbbtsti = 0.000 
+ cbbtgat = 1.000a 
+ fbbtrbot = 1.0E+9
+ fbbtrsti = 1.0E+9
+ fbbtrgat = 1.0E+9
+ stfbbtbot = 0.000 
+ stfbbtsti = 0.000 
+ stfbbtgat = -2.672m 
*********************************************************************
* Avalanche Breakdown Parameters
*********************************************************************
+ vbrbot = 1.001k
+ vbrsti = 1.001k
+ vbrgat = 1.001k
+ pbrbot = 4.000 
+ pbrsti = 4.000 
+ pbrgat = 4.000
*********************************************************************
* Noise Parameters
*********************************************************************
+ nfalw = '3.500E+25*noia_mul'
+ nfblw = '800.0E+6*noib_mul'
+ nfclw = '50e-9*noic_mul' 
+ efo = 1.1
+ fnto = 800.0m )
*********************************************************************
* Extrinsic Source/Drain Diode Model
*********************************************************************
.model pdio  d  (
+level  = 1              
+tref   = 25
+xti    = 3              
+tlev   = 0              
+tlevc  = 1
+eg     = 1.17           
+gap1   = 4.73e-4        
+gap2   = 636
+js     = js_phv         
+jsw    = jsw_phv        
+n      = n_phv
+cj     = cj_phv         
+pb     = pb_phv         
+mj     = mj_phv
+cjsw   = cjsw_phv       
+php    = pbsw_phv       
+mjsw   = mjsw_phv
+rs     = 200n
+cta    = cta_phv          
+ctp    = ctp_phv          
+tpb    = pta_phv
+tphp   = ptp_phv )
*********************************************************************
.ends pfethvt

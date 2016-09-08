* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfetshvt.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 1.0
*
*  pfetshvt      1.8V SHVTPFET in SX subcircuit w/diodes
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) pfetshvt l=nnn w=nnn
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
.subckt pfetshvt d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrs=0 nrd=0
+                         gcon=1 rsx=50 par=1 dtemp=0
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
+  noi_scale = '(noistd_pshv-min(log(sqrt(w*l*nf*par/noideva_pshv)),0))'
+  noia_mul  = '(exp(dnoipshv*noi_scale))'
+  noib_mul  = '(exp(dnoipshv*noi_scale/2))'
+  noic_mul  = '(exp(dnoipshv*noi_scale/4))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=2.535e-08   kvtw=-0.10u   kvtl=-0.16u
+  kmb=5.401e-10   kmbw=0.0u     kmbl=-0.7u
+  sigvth  = 'kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta = 'kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0  = agauss(0,sigvth,3)          $ vth0 mis-match
+  mmbeta  = agauss(0,sigbeta,3)         $ beta mis-match
*
* Gate resistance calculation (function of w, l and nf)
+  rge1 = '(pcrsi/(nf*gcon))*(0.42u+w/(3*gcon))/(l+lwbpc)'
+  rgw1 = '(27.227*(((w-2*wint_pshv)*nf*1e6)**(-0.55)))'
+  rgl1 = '((10e6*(l-2*lint_pshv)+0.1324)/1.665)'

m0 (d g1 s b1) pchshvt w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
rgate  g1  g  r='rge1+rgw1+rgl1'
rsb    b  b1  r=rsx
ddb    d  b1  pdio area=zad pj=pstid m=nf dtemp=dtemp
dsb    s  b1  pdio area=zas pj=pstis m=nf dtemp=dtemp
rddb   d  b1  r='50e+3/(zad*nf)'
rdsb   s  b1  r='50e+3/(zas*nf)'

***************************************************************************
* 1.8V SHVT PFET PSP Model
***************************************************************************
.model pchshvt pmos (
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
+ fol1 = fol1_pshv
+ fol2 = fol2_pshv
+ lap = lint_pshv
+ lov = lov_pshv
+ rsw1 = rsw_pshv 
+ toxo = tox_pshv 
+ toxovo = tox_pshv
+ uo = 'uo_pshv + mmbeta'
+ vfbo = 'vfb_pshv + mmvth0' 
+ vfbl = vfbl_pshv
+ vfblw = vfblw_pshv
+ thesatl = thesatl_pshv
+ wot = wint_pshv
*********************************************************************
* Core Parameters
*********************************************************************
+ a1l =-0.0935
+ a1o = 5.851
+ a1w = 0
+ a2o = 21.11 
+ a3l = -0.05239
+ a3o = 1.372
+ a3w =-12.02m
+ a4l = -0.1358
+ a4o = 0.04606
+ a4w = 1.0
+ agidlw = 0.00003
+ alp1l1 = 0.0203
+ alp1l2 = 0.00912
+ alp1lexp = 0.1 
+ alp1w = -0.1 
+ alp2l1 = 0.07079
+ alp2l2 = 0.08298
+ alp2lexp = 3.707 
+ alp2w = 0
+ alpl = 0.002986
+ alplexp = 1.475
+ alpw = 0
+ axl = 0.6252
+ axo = 17.9
+ betw1 = 0.06295
+ betw2 = 1.82e-07
+ bgidlo = 11.5
+ cfbo = 1
+ cfl = 558n
+ cflexp = 5 
+ cfrw = 0.000 
+ cfw = 0.1 
+ cgbovl = 0.000 
+ cgidlo = 0.06 
+ chibo = 3.100 
+ csl = 1 
+ cslexp = 0.6254
+ cslw = 0.01259
+ cso = 0
+ csw = 0.00955
+ ctl =  0.05108
+ ctlexp = 0.2101
+ ctlw = 0.003162 
+ cto = 0.0547
+ ctw = 0.00955
+ dlq = -4.895e-08
+ dnsubo = 0.02067
+ dphibl =  0.0282
+ dphiblexp = 0.2819 
+ dphiblw = 0.1
+ dphibo = -0.1008
+ dphibw = -0.1496
+ dta = dtemp
+ dwq = 0.000 
+ fbet1 =  -0.1738 
+ fbet1w = 6.607e-11
+ fbet2 = -0.5495
+ fetao = 1.982 
+ gc2o = 0.375
+ gc3o = 0.063
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
+ lp1 = 1e-08
+ lp1w = 2.188e-10
+ lp2 = 1e-08
+ lpck = 5.835e-09
+ lpckw = -0.04925 
+ lvarl = 0.000 
+ lvaro = 0.000 
+ lvarw = 0.000 
+ mueo = 2.944
+ muew = 0.03162
+ novo = 1.094e+25 
+ npck = 7.345e+23 
+ npckw = 0.05086
+ npl = -0.0845
+ npo = 5.828e+25
+ nslpo = 50.00m
+ nsubo = 4.786e+23 
+ nsubw = 0.000912
+ pkuo = 0.000 
+ pkvtho = 0.000 
+ qmc = 0.763
+ rsbo = -0.5
+ rsgo = 0.1752
+ rsw2 = 0
+ saref = 1.000u
+ sbref = 1.000u
+ sta2o = -0.2324
+ stbetl = 0.0065
+ stbetlw = 0
+ stbeto = 2.081 
+ stbetw = 0.1
+ stbgidlo = -0.0012
+ stcso = 3 
+ stetao = 0.000 
+ stigo = 2.000 
+ stmueo = 1.79
+ strso = 0.4775
+ stthemuo = 0.1573
+ stthesatl = -0.05
+ stthesatlw = -0.0082
+ stthesato = 1.076 
+ stthesatw = 0.352
+ stvfbl = 0.05095
+ stvfblw = -0.01459
+ stvfbo = 0.0006596
+ stvfbw = 0.03476
+ stxcoro = 0 
+ themuo = 0.9098 
+ thesatbo = -5
+ thesatgo = -0.5
+ thesatlexp = 0.1704 
+ thesatlw = -0.01
+ thesato = 0.7413 
+ thesatw = -0.1
+ tkuo = 0.000 
+ vfbw = 0.00615
+ vnsubo = 0.000 
+ vpo = 0.03651
+ wbet = 2.653e-07
+ wkuo = 0.000 
+ wkvtho = 0.000 
+ wlod = 0.000 
+ wlodkuo = 0.000 
+ wlodvth = 0.000 
+ wseg = 5e-07
+ wsegp = 1e-09
+ wvarl = 0.000 
+ wvaro = 0.000
+ wvarw = 0.000 
+ xcorl = 0
+ xcorlw = 6.607e-05
+ xcoro = 1.288e-05
+ xcorw = 0
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
+ cjorgat = cjsg_pshv
+ vbirbot = 1.000
+ vbirsti = 1.000
+ vbirgat = pbsg_pshv 
+ pbot = 430.0m
+ psti = 630.0m
+ pgat = mjsg_pshv
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
+ stfbbtgat = 0.172m
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
+ nfalw = '5.900E+25*noia_mul'
+ nfblw = '800.0E+6*noib_mul'
+ nfclw = '10e-8*noic_mul' 
+ efo = 1.1
+ fnto = 1 )
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
+js     = js_pshv         
+jsw    = jsw_pshv        
+n      = n_pshv
+cj     = cj_pshv         
+pb     = pb_pshv         
+mj     = mj_pshv
+cjsw   = cjsw_pshv       
+php    = pbsw_pshv       
+mjsw   = mjsw_pshv
+rs     = 200n
+cta    = cta_pshv          
+ctp    = ctp_pshv          
+tpb    = pta_pshv
+tphp   = ptp_pshv )
*********************************************************************
.ends pfetshvt

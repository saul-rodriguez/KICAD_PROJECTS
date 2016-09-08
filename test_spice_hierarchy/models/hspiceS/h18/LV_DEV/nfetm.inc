* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfetm.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  nfetm     5.0V NFET subcircuit
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) nfetm l=nnn w=nnn
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
.subckt nfetm  d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                       gcon=1 rsx=50 dtemp=0 par=1 gns=0
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
+  kvt=2.0e-8      kvtw=0.22u    kvtl=0.53u
+  kmb=5.5e-10     kmbw=-0.9u    kmbl=0.3u
+  sigvth = 'kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta= 'kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0=agauss(0,sigvth,3)        $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)       $ beta mis-match
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale = '(noistd_n5m-min(log(sqrt(w*l*nf*par/noideva_n5m)),0))'
+  noia_mul  = '(exp(dnoin5m*noi_scale))'
+  noib_mul  = '(exp(dnoin5m*noi_scale/2))'
+  noic_mul  = '(exp(dnoin5m*noi_scale/4))'
*
* Gate resistance calculation (function of w, l and nf)
+  rnqsl = '20*((l-2*lint_n5m)*1e6)**1'
+  rnqsn = '(8/nf)'
+  rnqsw = '4/((w-2*wint_n5m)*1e6)**0.9'
+  rnqs  = 'rnqsl*rnqsn*rnqsw'
+  rpoly = '((pcrsi*(1-gns)+opnpcrsf*gns)/(nf*gcon))*(1.44u+w/(3*gcon))/(l+lwbpc)'
*
m0 d g1 s b1 nchm   w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
rgate  g1  g  r='rnqs+rpoly'
rsb    b   b1 r=rsx
ddb    b1  d  ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb    b1  s  ndio area=zas pj=pstis m=nf dtemp=dtemp
rddb   b1  d  r='1/(zad*nf*4m)'
rdsb   b1  s  r='1/(zas*nf*4m)'
*
***************************************************************************
* 5V NFET PSP model
***************************************************************************
.model nchm nmos(  
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
+ fol1  = fol1_n5m
+ fol2  = fol2_n5m
+ lap  = lint_n5m
+ lov  = lov_n5m
+ rsw1  = rsw_n5m 
+ thesatl  = thesatl_n5m
+ toxo  = tox_n5m
+ toxovo  = tox_n5m
+ uo  = 'uo_n5m + mmbeta'
+ vfbl  = vfbl_n5m
+ vfblw  = vfblw_n5m
+ vfbo  = 'vfb_n5m + mmvth0' 
+ wot  = wint_n5m
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l = 260.0m
+ a1o = 1.100 
+ a1w = 0.000 
+ a2o = 26.70 
+ a3l =-58.57m
+ a3o = 1.150 
+ a3w = 0.000 
+ a4l =-500.0m
+ a4o = 100.0m
+ a4w = 0.000 
+ agidlw = 7.000 
+ alp1l1 = 5.729m
+ alp1l2 = 0.000 
+ alp1lexp = 508.4m
+ alp1w =-363.3m
+ alp2l1 =-12.83m
+ alp2l2 = 0.000 
+ alp2lexp = 869.6m
+ alp2w = 0.000 
+ alpl = 792.5u
+ alplexp = 444.1p
+ alpw = 1.591 
+ axl = 1.1 
+ axo = 12.44 
+ betw1 =-40.00m
+ betw2 =-6.000m
+ bgidlo = 13.74 
+ cfbo = 950.0m
+ cfl = 1.300m
+ cflexp = 2.600 
+ cfrw = 0.000 
+ cfw = 100.0m
+ cgbovl = 0.000 
+ cgidlo = 8.530m
+ chibo = 3.100 
+ csl =-117.8m
+ cslexp = 540.7m
+ cslw = 1.000p
+ cso =-122.4m
+ csw = 0.000 
+ ctl = 112.00m
+ ctlexp = 1.000 
+ ctlw = 0.000 
+ cto =-100.0m
+ ctw = 100.0m
+ dlq =-185.0n
+ dnsubo =-55.00m
+ dphibl = 72.00m
+ dphiblexp = 1.000 
+ dphiblw = 75.34m
+ dphibo =-75.00m
+ dphibw =-300.0m
+ dta = dtemp
+ dwq = 0.000 
+ fbet1 =-150.0m
+ fbet1w = 100.0m
+ fbet2 =-900.0m
+ fetao = 1.280 
+ fjunq = 0.000 
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
+ lp1 = 140.0n
+ lp1w = 100.0m
+ lp2 = 40.00n
+ lpck = 100.0n
+ lpckw = 107.2m
+ lvarl = 0.000 
+ lvaro = 0.000 
+ lvarw = 0.000 
+ mueo = 744.5m
+ muew =-40.00m
+ npck = 3.000e+22 
+ npckw =-48.16m
+ npl =-100.0m
+ npo = 6.000e+25 
+ novo= 4.692e+23
+ nsubo =1.47e+23
+ nslpo = 1.001m
+ nsubw =-8.372m
+ pkuo = 0.000 
+ pkvtho = 0.000 
+ qmc = 500.0m
+ rsbo = 10.00m
+ rsgo = 0.000 
+ rsw2 = 0.000 
+ saref = 1.000u
+ sbref = 1.000u
+ sta2o = 105.0m
+ stbetl = 8.120m
+ stbetlw = 0.000 
+ stbeto = 1.554 
+ stbetw =-100.0m
+ stbgidlo = 0.000 
+ stcso =-794.4m
+ stetao = 0.000 
+ stigo = 2.000 
+ stmueo = 203.5m
+ strso =-508.5m
+ stthemuo = 948.6m
+ stthesatl = 3.214m
+ stthesatlw = 29.86m
+ stthesato = 1.431 
+ stthesatw =-143.4m
+ stvfbl =-57.54m
+ stvfblw = 91.72m
+ stvfbo = 989.1u
+ stvfbw =-70.04m
+ stxcoro = 0.000 
+ themuo = 2.040 
+ thesatbo = 20.00m
+ thesatgo = 70.00m
+ thesatlexp = 1.000 
+ thesatlw =-5.000m
+ thesato = 35.00m
+ thesatw =-59.30m
+ tkuo = 0.000 
+ vfbw =-44.41a
+ vnsubo = 0.000 
+ vpo = 10.00m
+ wbet = 1.000n
+ wkuo = 0.000 
+ wkvtho = 0.000 
+ wlod = 0.000 
+ wlodkuo = 0.000 
+ wlodvth = 0.000 
+ wseg = 1e-10
+ wsegp = 1e-10
+ wvarl = 0.000 
+ wvaro = 0.000 
+ wvarw = 0.000 
+ xcorl = 100.0m
+ xcorlw = 0.000 
+ xcoro = 10.00m
+ xcorw = 0.000 
***************************************************************************
* Junction Diode Parameters
***************************************************************************
+ trj  = 25.00 
+ imax  = 1.000k
***************************************************************************
*    Capacitance Parameters
***************************************************************************
+ cjorbot  = 1p
+ cjorgat  = cjsg_n5m
+ cjorsti  = 1f
+ vbirbot  = 508.0m
+ vbirgat  = pbsg_n5m
+ vbirsti  = 10.00 
+ pbot  = 230.0m
+ pgat  = mjsg_n5m
+ psti  = 50.00m
***************************************************************************
*    Ideal Current Parameters
***************************************************************************
+ csrhbot  = 0.000 
+ csrhgat  = 0.000 
+ csrhsti  = 0.000 
+ idsatrbot  = 0.000
+ idsatrgat  = 300f
+ idsatrsti  = 0.000
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
+ cbbtbot  = 0.000 
+ cbbtgat  = 0.000
+ cbbtsti  = 0.000 
+ fbbtrbot  = 1.0e+09
+ fbbtrgat  = 1.0e+09
+ fbbtrsti  = 1.0e+09
+ stfbbtbot  = 0.000 
+ stfbbtgat  = 0.000 
+ stfbbtsti  = 0.000 
***************************************************************************
*    Avalanche and Breakdown Parameters
***************************************************************************
+ pbrbot  = 4.000 
+ pbrgat  = 4.000 
+ pbrsti  = 4.000 
+ vbrbot  = 1.001k
+ vbrgat  = 1.001k
+ vbrsti  = 1.001k
***************************************************************************
* Noise Parameters
***************************************************************************
+ efo  = 1.0
+ fnto = 1.0
+ nfalw='(2E+25)*noia_mul'
+ nfblw='(3E+7)*noib_mul'
+ nfclw='(5E-10)*noic_mul')
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model ndio d (
+ level  = 1.000 
+ tref  = 25.00 
+ xti  = 3.000 
+ tlev  = 0.000 
+ tlevc  = 1.000 
+ eg  = 1.170 
+ gap1  = 473.0u
+ gap2  = 636.0 
+ rs = 0.000
+ js  = js_n5m
+ jsw  = jsw_n5m
+ n  = n_n5m
+ cj  = cj_n5m
+ pb  = pb_n5m
+ mj  = mj_n5m
+ cjsw  = cjsw_n5m
+ php  = pbsw_n5m
+ mjsw  = mjsw_n5m
+ ibv  = 10.00u
+ cta  = cta_n5m 
+ ctp  = ctp_n5m
+ tpb  = pta_n5m
+ tphp  = ptp_n5m
+ bv  = 9.530 )
***************************************************************************
.ends nfetm

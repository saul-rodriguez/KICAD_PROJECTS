* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfetim4.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  nfetim4        nfetm over HV well subcircuit (4 node)
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b  nfetim4 l=nnn w=nnn
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
.subckt nfetim4 d g s b  w=0 l=0 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                        dtemp=0 nf=1 gcon=1 rsx=50 par=1 gns=0 vdnsx=50
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
+  rnqsl = '20*((l-2*lint_n5im)*1e6)**1'
+  rnqsn = '(8/nf)'
+  rnqsw = '4/((w-2*wint_n5im)*1e6)**0.9'
+  rnqs  = 'rnqsl*rnqsn*rnqsw'
+  rpoly = '((pcrsi*(1-gns)+opnpcrsf*gns)/(nf*gcon))*(1.44u+w/(3*gcon))/(l+lwbpc)'
*
m0 d g1 s b1 nchim  w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate mult=nf
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
.model nchim nmos(  
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
+ fol1  = fol1_n5im
+ fol2  = fol2_n5im
+ lap  = lint_n5im
+ lov  = lov_n5im
+ rsw1  = rsw_n5im 
+ thesatl  = thesatl_n5im
+ toxo  = tox_n5im
+ toxovo  = tox_n5im
+ uo  = 'uo_n5im + mmbeta'
+ vfbl  = vfbl_n5im
+ vfblw  = vfblw_n5im
+ vfbo  = 'vfb_n5im + mmvth0' 
+ wot  = wint_n5im
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l = 0.26 
+ a1o = 1.1 
+ a1w = 0 
+ a2o = 26.7 
+ a3l = -0.05857 
+ a3o = 1.15 
+ a3w = 0 
+ a4l = -0.5 
+ a4o = 0.1 
+ a4w = 0 
+ agidlw = 7 
+ alp1l1 = 0.005729 
+ alp1l2 = 0 
+ alp1lexp = 0.5084 
+ alp1w = -0.1 
+ alp2l1 = -0.01283 
+ alp2l2 = 0 
+ alp2lexp = 0.8696 
+ alp2w = 0 
+ alpl = 0.0007925 
+ alplexp = 4.441e-10 
+ alpw = 0.1 
+ axl = 1.1 
+ axo = 12.44 
+ betw1 = -0.04 
+ betw2 = -0.006 
+ bgidlo = 13.65 
+ cfbo = 0.7 
+ cfl = 0.0013 
+ cflexp = 2.6 
+ cfrw = 0 
+ cfw = 0.1 
+ cgbovl = 0 
+ cgidlo = 3.066e-05 
+ chibo = 3.1 
+ csl = -0.1178 
+ cslexp = 0.5407 
+ cslw = 1e-12 
+ cso = -0.1224 
+ csw = 0 
+ ctl = 0.110 
+ ctlexp = 1 
+ ctlw = 0 
+ cto = -0.1 
+ ctw = 0.1 
+ dlq = -1.85e-07 
+ dnsubo = -0.055 
+ dphibl = 0.072 
+ dphiblexp = 1 
+ dphiblw = 0.07534 
+ dphibo = -0.075 
+ dphibw = -0.3 
+ dta = dtemp 
+ dwq = 0 
+ fbet1 = 0.15 
+ fbet1w = 0.1 
+ fbet2 = -0.9 
+ fetao = 1.254 
+ fjunq = 0 
+ gc2o = 0.375 
+ gc3o = 0.063 
+ gcoo = 0 
+ iginvlw = 0 
+ igovw = 0 
+ kuo = 0 
+ kvsat = 0 
+ kvtho = 0 
+ lkuo = 0 
+ lkvtho = 0 
+ llodkuo = 0 
+ llodvth = 0 
+ lodetao = 1 
+ lp1 = 1.4e-07 
+ lp1w = 0.1 
+ lp2 = 5.9e-08 
+ lpck = 7e-08 
+ lpckw = 0.1072 
+ lvarl = 0 
+ lvaro = 0 
+ lvarw = 0 
+ mueo = 0.7445 
+ muew = -0.04 
+ npck = 1e+22 
+ npckw = -0.04816 
+ npl = -0.1 
+ novo = 4.692e+23 
+ nsubo = 1.43e+23 
+ npo = 6e+25 
+ nslpo = 0.001001 
+ nsubw = -0.008372 
+ pkuo = 0 
+ pkvtho = 0 
+ qmc = 0.5 
+ rsbo = 0.02 
+ rsgo = 0 
+ rsw2 = 0 
+ saref = 1e-06 
+ sbref = 1e-06 
+ sta2o = 0.105 
+ stbetl = 0.03397 
+ stbetlw = 0 
+ stbeto = 1.515 
+ stbetw = -0.1 
+ stbgidlo = 0 
+ stcso = 0 
+ stetao = 0 
+ stigo = 2 
+ stmueo = 0 
+ strso = -0.3 
+ stthemuo = 0.7 
+ stthesatl = -0.05 
+ stthesatlw = -0.01363 
+ stthesato = 1.563 
+ stthesatw = -0.1002 
+ stvfbl = -0.05754 
+ stvfblw = 0.09412 
+ stvfbo = 0.0009891 
+ stvfbw = -0.1366 
+ stxcoro = 0.01 
+ themuo = 2.04 
+ thesatbo = 0.02 
+ thesatgo = 0.07 
+ thesatlexp = 1 
+ thesatlw = -0.005 
+ thesato = 0.01 
+ thesatw = -0.06185 
+ tkuo = 0 
+ vfbw = -4.441e-17 
+ vnsubo = 0 
+ vpo = 0.01 
+ wbet = 1e-09 
+ wkuo = 0 
+ wkvtho = 0 
+ wlod = 0 
+ wlodkuo = 0 
+ wlodvth = 0 
+ wseg = 1e-10 
+ wsegp = 1e-10 
+ wvarl = 0 
+ wvaro = 0 
+ wvarw = 0 
+ xcorl = 0.1 
+ xcorlw = 0 
+ xcoro = 0.01 
+ xcorw = 0 
***************************************************************************
* Junction Diode Parameters
***************************************************************************
+ trj  = 25.00 
+ imax  = 1.000k
***************************************************************************
*    Capacitance Parameters
***************************************************************************
+ cjorbot  = 600u
+ cjorgat  = cjsg_n5im
+ cjorsti  = 76p
+ vbirbot  = 508.0m
+ vbirgat  = pbsg_n5im
+ vbirsti  = 10.00 
+ pbot  = 230.0m
+ pgat  = mjsg_n5im
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
+ js  = js_n5im
+ jsw  = jsw_n5im
+ n  = n_n5im
+ cj  = cj_n5im
+ pb  = pb_n5im
+ mj  = mj_n5im
+ cjsw  = cjsw_n5im
+ php  = pbsw_n5im
+ mjsw  = mjsw_n5im
+ ibv  = 10.00u
+ cta  = cta_n5im 
+ ctp  = ctp_n5im
+ tpb  = pta_n5im
+ tphp  = ptp_n5im
+ bv  = 9.530 )
***************************************************************************
.ends nfetim4

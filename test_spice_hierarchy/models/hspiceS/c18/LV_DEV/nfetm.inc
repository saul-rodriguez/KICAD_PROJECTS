* Path, Component, Release: cmos7base/rel/HSPICE/models/nfetm.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*  7RF/7WL  nfetm       5.0V NFET subcircuit
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
*        |                          |------\/\/\/-------o              |
*        |                          |        rddb       |              |
*        |                    |_____|                   |              |
*        |              g1  | |         b1              |     bulk     |
*   gate o-----\/\/\/---o---| |  |------o----\/\/\/-----o-------o      |
*        |      rgate       | |_____          rsx       |              |
*        |                    |     |                   |              |
*        |                          |------\/\/\/-------o              |
*        |                          |         rdsb      |              |
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
.subckt nfetm (d g s b)
+ w=10u l=10u nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+ gcon=1 rsx=50 dtemp=0 rf=0 par=1 gns=0
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
+  kvt=1.650e-8    kvtw=-0.05u  kvtl=0.45u
+  kmb=12.5e-10    kmbw=-0.9u  kmbl=0.5u
+  sigvth = '(kvt/sqrt((w-kvtw)*nf*par*(l-kvtl)))'
+  sigbeta= '(kmb/sqrt((w-kmbw)*nf*par*(l-kmbl)))' 
+  mmvth0=agauss(0,sigvth,3)        $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)       $ beta mis-match
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale = '(noistd_n50-min(log(sqrt(w*l*nf*par/noideva_n50)),0))'
+  noia_mul   = '(exp(dnoin50*noi_scale))'
+  noib_mul   = '(exp(dnoin50*noi_scale/2))'
+  noic_mul   = '(exp(dnoin50*noi_scale/4))'
*
* Thermal noise scaling equation
+  tnoitanha = 0.1
+  tnoitanhb = 1e3
+  tnoitanhc = 1.9e12
+  ntnoi_nfetm = '1/tanh(tnoitanha + tnoitanhb*l + tnoitanhc*l*l)'
*
* Gate resistance calculation (function of w, l and nf)
+  rnqsl = '20*((l-2*lint_n50)*1e6)**1'
+  rnqsn = '(8/nf)'
+  rnqsw = '4/((w-2*wint_n50)*1e6)**0.9'
+  rnqs  = 'rnqsl*rnqsn*rnqsw'
+  rpoly = '((pcrsi*(1-gns)+opnpcrsf*gns)/(nf*gcon))*((1.44u+w/(3*gcon))/(l+lwbpc))'
*
* Drain resistance calculation (function of l and nf)
+  rd='0.5 + (nf-2)*(7m)'
*
* Source resistance calculation (function of l and nf)
+  rs='0.5 + (nf)*(7m)'
*
* Body resistance calculation (function of l and nf)
+  rsbl = '45/log(1+(l-2*lint_n50)*1e6)'
+  rsbn = '6.2/(nf**0.65)'
+  rsbw = '5/((w-2*wint_n50)*1e6)'
+  rsb = 'rsbl*rsbn*rsbw'
*
* Gate to drain capacitance calculation (function of l and nf)
+  cgd='380a + (nf-2)*(190a + w*40p)'
*
* Gate to source capacitance calculation (function of l and nf)
+  cgs='380a + (nf)*(190a + w*40p)'
*
* Drain to source capacitance calculation (function of l and nf)
+  cds='(nf-2)*((l*1e6)*400a)'
*
m0 d1 g1 s1 b1 nch    w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                     mult=nf 
rdext  d1  d  r='(znrd*rsh_n50/nf) + rf*rd'
rsext  s1  s  r='(znrs*rsh_n50/nf) + rf*rs'
rgate  g1  g  r='rnqs+rpoly'
rsb    b   b1 r='((1-rf)*rsx + rf*rsb)'
cwgd   g   d  c='1e-18+rf*cgd'
cwgs   g   s  c='1e-18+rf*cgs'
cwds   d   s  c='1e-18+rf*cds'
ddb    b1 d1 ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb    b1 s1 ndio area=zas pj=pstis m=nf dtemp=dtemp
rddb    b1 d1  r='1/(zad*nf*230u + pstid*nf*1.5n)' 
rdsb    b1 s1  r='1/(zas*nf*230u + pstis*nf*1.5n)' 
*
***************************************************************************
* NFET PSP model
***************************************************************************
.model nch nmos(  
+ level  = 69
+ version = 102.3
+ tr  = 25.00 
***************************************************************************
* Switch Settings
***************************************************************************
+ swgidl  = 0.000 
+ swigate  = 0.000 
+ swimpact  = 1.000 
+ swjuncap  = 3.000
***************************************************************************
* Parameters With Process Variation
***************************************************************************
+ lap  = lint_n50
+ lov  = lov_n50
+ novo  = 4.692e+23 
+ nsubo  = 1.700e+23 
+ rsw1  = rsw_n50 
+ thesatl  = thesatl_n50
+ toxo  = tox_n50
+ toxovo  = tox_n50
+ uo  = 'uo_n50 + mmbeta'
+ vfbl  = vfbl_n50
+ vfblw  = vfblw_n50
+ vfbo  = 'vfb_n50 + mmvth0' 
+ wot  = wint_n50
***************************************************************************
* Core Parameters
***************************************************************************
+ a1l  = 225.0m
+ a1o  = 3.600 
+ a1w  = 0.000 
+ a2o  = 32.00 
+ a3l  = -100.0m
+ a3o  = 1.200 
+ a3w  = 0.000 
+ a4l  = -500.0m
+ a4o  = 100.0m
+ a4w  = 0.000 
+ agidlw  = 0.000 
+ alp1l1  = 2.667m
+ alp1l2  = 0
+ alp1lexp  = 488.3m
+ alp1w  = 0.000 
+ alp2l1  = -12.83m
+ alp2l2  = 0
+ alp2lexp  = 869.6m
+ alp2w  = 0.000 
+ alpl  = 3.939m
+ alplexp  = 193.5m
+ alpw  = 0.000 
+ axl  = 1.6 
+ axo  = 12.44 
+ betw1  = -74.05m
+ betw2  = 0.000 
+ bgidlo  = 41.00 
+ cfbo  = 350.0m
+ cfl  = 1.7m
+ cflexp  = 2.400 
+ cfrw  = 0.000 
+ cfw  = 100.0m
+ cgbovl  = 0.000 
+ cgidlo  = 0.000 
+ chibo  = 3.100 
+ csl  = 492.0u
+ cslexp  = 7.302 
+ cslw  = 0.000 
+ cso  = -122.4m
+ csw  = 0.000 
+ ctl  = 63.5m
+ ctlexp  = 1.000 
+ ctlw  = 0.000 
+ cto  = 0.000 
+ ctw  = 100.0m
+ dlq  = -183.0n
+ dnsubo  = 0.000 
+ dphibl  = 90.00m
+ dphiblexp  = 1.150 
+ dphiblw  = 0.000 
+ dphibo  = 0.000 
+ dphibw  = -110.0m
+ dta = dtemp
+ dwq  = 0.000 
+ fbet1  = 0.000 
+ fbet1w  = 0.000 
+ fbet2  = 0.000 
+ fetao  = 1.403 
+ fol1  = fol1_n50
+ fol2  = fol2_n50
+ gc2o  = 375.0m
+ gc3o  = 63.00m
+ gcoo  = 0.000 
+ iginvlw  = 0.000 
+ igovw  = 0.000 
+ kuo  = 0.000 
+ kvsat  = 0.000 
+ kvtho  = 0.000 
+ lkuo  = 0.000 
+ lkvtho  = 0.000 
+ llodkuo  = 0.000 
+ llodvth  = 0.000 
+ lodetao  = 1.000 
+ lp1  = 989.8p
+ lp1w  = 0.000 
+ lp2  = 100.0p
+ lpck  = 8.000n
+ lpckw  = 3.183m
+ lvarl  = 0.000 
+ lvaro  = 0.000 
+ lvarw  = 0.000 
+ mueo  = 744.5m
+ muew  = -83.76m
+ npck  = 4.500e+23 
+ npckw  = -12.32m
+ npl  = -100.0m
+ npo  = 6.000e+25 
+ nslpo  = 1.001m
+ nsubw  = -4.500m
+ pkuo  = 0.000 
+ pkvtho  = 0.000 
+ qmc  = 500.0m
+ rsbo  = 0.000 
+ rsgo  = 0.000 
+ rsw2  = 0.000 
+ saref  = 1.000u
+ sbref  = 1.000u
+ sta2o  = 0.000 
+ stbetl  = 30.00m
+ stbetlw  = 0.000 
+ stbeto  = 1.400 
+ stbetw  = -100.0m
+ stbgidlo  = 0.000 
+ stcso  = 0.000 
+ stetao  = 0.000 
+ stigo  = 2.000 
+ stmueo  = 0.000 
+ strso  = -166.2m
+ stthemuo  = 985.0m
+ stthesatl  = -50.00m
+ stthesatlw  = 0.000 
+ stthesato  = 1.347 
+ stthesatw  = -100.0m
+ stvfbl  = -29.46m
+ stvfblw  = 70.00m
+ stvfbo  = 905.4u
+ stvfbw  = -50.00m
+ stxcoro  = 0.000 
+ themuo  = 1.577 
+ thesatbo  = 444.1p
+ thesatgo  = 115.0m
+ thesatlexp  = 863.2m
+ thesatlw  = -5.000m
+ thesato  = 2.221n
+ thesatw  = -70.00m
+ tkuo  = 0.000 
+ vfbw  = 22.00m
+ vnsubo  = 0.000 
+ vpo  = 10.00m
+ wbet  = 1e-10
+ wkuo  = 0.000 
+ wkvtho  = 0.000 
+ wlod  = 0.000 
+ wlodkuo  = 0.000 
+ wlodvth  = 0.000 
+ wseg  = 125.2p
+ wsegp  = 1e-10
+ wvarl  = 0.000 
+ wvaro  = 0.000 
+ wvarw  = 0.000 
+ xcorl  = 454.3m
+ xcorlw  = 0.000 
+ xcoro  = -918.3u
+ xcorw  = 0.000 
***************************************************************************
* Junction Diode Parameters
***************************************************************************
+ trj  = 25.00 
+ imax  = 1.000k
***************************************************************************
*    Capacitance Parameters
***************************************************************************
+ cjorbot  = 1p
+ cjorgat  = cjsg_n50
+ cjorsti  = 1f
+ vbirbot  = 508.0m
+ vbirgat  = pbsg_n50
+ vbirsti  = 10.00 
+ pbot  = 230.0m
+ pgat  = mjsg_n50
+ psti  = 50.00m
***************************************************************************
*    Ideal Current Parameters
***************************************************************************
+ csrhbot  = 0.000 
+ csrhgat  = 0.000 
+ csrhsti  = 0.000 
+ idsatrbot  = 1.000u
+ idsatrgat  = 26.95f
+ idsatrsti  = 1.300p
+ phigbot  = 1.000 
+ phiggat  = 1.000 
+ phigsti  = 1.000 
+ xjungat  = 100.0n
+ xjunsti  = 100.0n
***************************************************************************
*    Trap-Assisted Tunneling Parameters
***************************************************************************
+ ctatbot  = 0.000 
+ ctatgat  = 100.0u 
+ ctatsti  = 0.000 
+ mefftatbot  = 250.0m
+ mefftatgat  = 250.0m
+ mefftatsti  = 250.0m
***************************************************************************
*    Band-to-Band Tunneling Parameters
***************************************************************************
+ cbbtbot  = 0.000 
+ cbbtgat  = 20.00a 
+ cbbtsti  = 0.000 
+ fbbtrbot  = 1.000G
+ fbbtrgat  = 1.000G
+ fbbtrsti  = 1.000G
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
+ efo    = 1.0
+ nfalw='(2E+25)*noia_mul'
+ nfblw='(3E+7)*noib_mul'
+ nfclw='(5E-10)*noic_mul'
+ fnto=ntnoi_nfetm)
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
+ js  = js_n50
+ jsw  = jsw_n50
+ n  = n_n50
+ cj  = cj_n50
+ pb  = pb_n50
+ mj  = mj_n50
+ cjsw  = cjsw_n50
+ php  = pbsw_n50
+ mjsw  = mjsw_n50
+ ibv  = 10.00u
+ cta  = cta_n50 
+ ctp  = ctp_n50
+ tpb  = pta_n50
+ tphp  = ptp_n50
+ bv  = 9.530 
)
***************************************************************************
.ends nfetm

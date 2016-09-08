* Path, Component, Release: cmos7base/rel/HSPICE/models/nfet.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  nfet     1.8V NFET subcircuit
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
*            +      rsx = 50   <- Body resistance for gcon=1 case
*            +       rf = 0    <- RF device flag (0-> nfet pcell
*                                                 1-> nfet_rf pcell)
*            +     stis = 2    <- STI stress flag (0-> nfet without STI stress
*                                                  1-> STI stress on one side
*                                                  2-> STI stress on both sides)
*            +      gns = 0    <- ESD hierarchical cell layout option
*                                 (0-> silicided gate, 1-> non-silicided gate)
*
*  NOTES:
*
*  1. If nrd or nrs are not passed to the model they will default to 0.
*     This will result in 0 ohms of silicided S/D resistance being placed
*     in series with the device model.
*
* SUBCIRCUIT SCHEMATIC:
*                                drain
*         ________| |______________O___
*        |        | |              |   |
*        |       cwgd              |   |
*        |                         /   |
*        |                  rdext  \   |  Ddb (Includes internal FET drain area
*        |                         /   |       and STI bounded perimeter)
*        |                     d1  |___|___|/|_________
*        |                         |   |   |\|         |
*        |Internal FET includes PC |   |               |
*        |bounded perimeter only   |   |               |
*        |                     ____|   |               |
*    gate|              g1  | |      __|__        |  b1|          bulk
*        O-------\/\/\/-----| |      _____ cwds   |----O--\/\/\/---O
*        |       rgate      | |____    |          |    |    rsb
*        |                         |   |               |
*        |                         |   |               |
*        |                         |   |               |
*        |                     s1  |___|___|/|_________|
*        |                         |   |   |\|
*        |                         \   |
*        |                  rsext  /   |  Dsb (Includes internal FET source area
*        |                         \   |       and STI bounded perimeter)
*        |       cwgs              |   |
*        |________| |______________|___|
*                 | |              O
*                               source
*
*
***************************************************************************
.subckt nfet  d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                      gcon=1 rsx=50 dtemp=0 rf=0 stis=2 par=1 gns=0
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
+  kvt=1.2441e-8    kvtw=-0.5809u  kvtl=0.0583u
+  kmb=1.1313e-5    kmbw=0.0443u   kmbl=0.0822u
+  sigvth='kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta='kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0=agauss(0,sigvth,3)        $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)       $ beta mis-match
+  mmbody=0
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale='noistdn-min(log(sqrt(w*l*nf*par/noidevan)),0)'
+  noi_mul='exp(dnoin*noi_scale)'
*
* Gate resistance calculation for all cases (function of w, l and nf)
+  rge1='((pcrsi*(1-gns)+opnpcrsf*gns)/(nf*gcon))*((0.4u+w/(3*gcon))/(l+lwbpc))'
+  rgw1='(10.291*(((w-2*wint_n)*nf*1e6)**(-0.4607)))'
+  rgl1='(3.6232e6*(l-2*lint_n)+0.5159)'
*
* Gate capacitance calculation for rf=1 case (function of w, l and nf)
+  cgw1='1.36*(85.3e-12*w*nf+0.6e-15)'
+  cgl1='(47233e-12*l+5.9772e-15)/14.048e-15'
*
* Drain-Source capacitance calculation for rf=1 case (function of w, l and nf)
+  cdsw1='0.5*((9.0e-5*(1e+6*w*nf)**2 + 8.87e-2*(1e+6*w*nf) + 0.4703)*1.0e-15)'
+  cdsl1='(1.6432e-6/l+8.4)/17.53'
*
* Substrate resistance calculation for rf=1 case (function of w, l and nf)
+  rsw1='1.5*(4400*(((w-2*wint_n)*nf*1e6)**(-0.899)))'
+  rsl1='(38.462e6*(l-2*lint_n)+24.423)/46.08'
*
* External resistance term calculation for rf=1 case (function of w, l and nf)
+  rxw1='0.6*(23.642*((w*nf*1e6)**(-0.6235)))'
+  rxl1='(0.3113*((l*1e6)**(-0.6684)))/0.9987'
*
* STI switch to turn on or turn off the stress effect
+  stise = '(gsti==2)*2+(gsti<2)*stis'
+  ngsti = '(gsti==0)'
+  fsti  = '(gsti*stise<1)'
*
* RX length calculation
+  rxl = 'min(max(0.46u,((zas+zad)/w/2)),1.4u)'
*
* STI stress effect calculation based on RX length
+  stist      = '(1-ngsti)*(stise*2.5*exp(-2e6*rxl))'
+  stilu0     = '7*stist/(nf*2)'
+  stipclm    = '0.31*stist/(nf*2)*(1.8e-7/l)'
+  stipdiblc1 = '7.151277e-3*exp(-4*stist/(nf*2)*(1.8e-7/l)**6)-fsti*7e-3*(1.8e-7/l)**2'
+  stipdiblc2 = '0.007*exp(-3*stist/(nf*2)*(1.8e-7/l)**4)'
*
m0 d1 g1 s1 b1 nch    w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                     nrd=0 nrs=0 m=nf dtemp=dtemp
rdext  d1  d r='(znrd*rsh_n/nf)+ rf*(rxw1*rxl1)'
rsext  s1  s r='(znrs*rsh_n/nf)+ rf*(rxw1*rxl1)'
rgate  g1  g r='(rge1+rgw1*rgl1)'
rsb    b  b1 r='((1-rf)*rsx + rf*rsl1*rsw1)'
cwgd   g   d c='1e-18+rf*(cgw1*cgl1)'
cwgs   g   s c='1e-18+rf*(cgw1*cgl1)'
cwds   d   s c='1e-18+rf*(cdsw1*cdsl1)'
ddb    b1 d1 ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb    b1 s1 ndio area=zas pj=pstis m=nf dtemp=dtemp
*
***************************************************************************
* NFET BSIM3v3.2.4 Model
***************************************************************************
.model nch    nmos (      level   = 49             version = 3.24
+tnom    = 25             tox     = tox_n          mobmod  = 1
+xj      = 2.5e-7         nch     = 4e17           vth0    = 'vth0_n+mmvth0'
+k1      = 0.4113668      k2      = -4.193665e-3   k3      = 71.7016064
+k3b     = 4.1195251      w0      = 6.894474e-6    nlx     = 2.544e-7
+dvt0w   = -9.47588       dvt1w   = 7.18e6         dvt2w   = -0.122689
+dvt0    = 0.91732        dvt1    = 0.3417608      dvt2    = -0.025578
+wuc     = -4.229e-11     u0      = 'u0_n+mmbeta'  ua      = 2.655969e-13
+ub      = 2.010666e-18   uc      = 8.583045e-11   vsat    = 'vsat_n'
+a0      = 1.7822307      ags     = 0.458          b0      = -1e-5
+b1      = 1.858424e-5    keta    = 0.0367807      a1      = 1.163811e-4
+a2      = 0.4094019      rdsw    = rdsw_n         prwg    = 0.0364393
+prwb    = 0.3070473      wr      = 1              wint    = wint_n
+lint    = lint_n         lketa   = -8.146047e-3   wvsat   = -1.16e4
+dwg     = -1.349276e-8   dwb     = -1.962061e-8   voff    = -0.1196149
+nfactor = 1.2627444      cit     = 0              cdsc    = 6.112059e-4
+cdscd   = 4.866317e-4    cdscb   = 6.588718e-6    eta0    = 0.791184
+etab    = -0.482545      dsub    = 1.20           pclm    = '2.21-stipclm'
+pdiblc1 = stipdiblc1     pdiblc2 = stipdiblc2     pdiblcb = -0.1340178
+drout   = 0.01           pscbe1  = 6.80419e+9     pscbe2  = 1.51129e-4
+pvag    = -0.1734725     delta   = 5.387e-3       ngate   = 1.07e20
+alpha0  = 3e-6           beta0   = 20             paramchk= 0
+alpha1  = 30             wk3     = -48.3014794    binunit = 1
+lua     = -3.38571e-13   lub     = -5.69110e-20   luc     = 1e-11
+lrdsw   = -8.6425836     lu0     = '2-stilu0'     lk1     = 1.600877e-3
+lags    = 0.1553066      wu0     = -54.7975915    wb0     = 3.56386e-7
+wl      = 0              wln     = 0.172078       ww      = -1e-14
+ll      = 0              lw      = 0              lwn     = 2.4e-3
+ wrdsw  = 6.98681        ww0     = -6.027438e-7   wk3b    = 15
*
***************************************************************************
* Source/Drain Diode Parameters
***************************************************************************
+acm     = 2              tlev    = 0              tlevc   = 1
+eg      = 1.17           gap1    = 4.73E-4        gap2    = 636
+cj      = cj_n           pb      = pb_n           mj      = mj_n
+cjsw    = cjsg_n         php     = pbsg_n         mjsw    = mjsg_n
+cjgate  = cjsg_n         xti     = 3              n       = n_n
+js      = js_n           jsw     = jsw_n          hdif    = 0
+rsh     = 0              tcjswg  = tcjsg_n        tpbswg  = tpbsg_n
*
***************************************************************************
* Capacitance-Voltage (CV) Parameters
***************************************************************************
+capmod  = 2              xpart   = 0              dlc     = 'lint_n+2.2E-8'
+dwc     = wint_n         cgdo    = cgdo_n         cgso    = cgso_n
+cgsl    = cgsl_n         cgdl    = cgdl_n         ckappa  = 6.7867
+cf      = 0              cgbo    = 1.706e-11      acde    = 1.2
+llc     = 0              lwc     = 0              lwlc    = 0
+wlc     = 0              wwc     = 0              wwlc    = 0
*
***************************************************************************
* Jds/Vt Temperature Parameters
***************************************************************************
+prt     = 0              ute     = -2             kt1     = -0.2822
+kt1l    = 6.0E-9         kt2     = -0.0546805     ua1     = 1.747122E-9
+ub1     = -4.46008e-18   uc1     = -2.09724e-10   at      = 8.881118E4
+wute    = 0.09
*
***************************************************************************
* Flicker Noise Parameters
***************************************************************************
+noimod  = 2              noia = '0.9e21*noi_mul'  noib    = '0.5e5*noi_mul'
+noic = '-0.4e-12*noi_mul'  em    = 7.0e6          af      = 1
+ef      = 0.95             kf    = 0   )
*
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model ndio  d (          level   = 1              tref    = 25
+xti     = 3              tlev    = 0              tlevc   = 1
+eg      = 1.17           gap1    = 4.73E-4        gap2    = 636
+js      = js_n           jsw     = jsw_n          n       = n_n
+cj      = cj_n           pb      = pb_n           mj      = mj_n
+cjsw    = cjsw_n         php     = pbsw_n         mjsw    = mjsw_n
+rs      = 120p           cta     = cta_n          ctp     = ctp_n
+tpb     = pta_n          tphp    = ptp_n )
*
***************************************************************************
.ends nfet

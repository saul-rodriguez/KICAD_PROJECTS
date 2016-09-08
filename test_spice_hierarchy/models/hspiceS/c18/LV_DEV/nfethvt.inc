* Path, Component, Release: cmos7base/rel/HSPICE/models/nfethvt.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  nfethvt   1.8V NFETHV subcircuit
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) nfethvt l=nnn w=nnn
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
*            +       nf = 1    <- number of gate stripes or "fingers" in device
*            +  m (par) = 1    <- number of parallel instances (multiplicity)
*            +     gcon = 1    <- Gate connection switch (1->single-ended,
*                                                         2->double-ended)
*            +      rsx = 50   <- body resistance
*            +       rf = 0    <- RF device flag (not used)
*            +     stis = 2    <- STI stress flag (0-> nfet without STI stress
*                                                  1-> STI stress on one side
*                                                  2-> STI stress on both sides)
*
*  NOTES:
*
*  1. If nrd or nrs are not passed to the model they will default to 0.
*     This will result in 0 ohms of silicided S/D resistance being placed
*     in series with the device model.
*
*  2. Intrinsic FET model includes PC bounded perimeter only
*
* SUBCIRCUIT SCHEMATIC:
*
*                                 drain
*                                   O
*                                   |
*                                   |
*                                   /     Ddb (Includes internal
*                            rdext  \     FET drain area and STI
*                                   /     bounded perimeter)
*                               d1  |______|/|____
*                                   |      |\|    |
*                                   |             |
*                                   |             |
*                               ____|             |
*   gate               g1   | |      |        b1  |           bulk
*        O-------\/\/\/-----| |      |------------o--\/\/\-----O
*                rgate      | |____  |            |   rsb
*                                   |             |
*                                   |             |
*                                   |             |
*                               s1  |______|/|____|
*                                   |      |\|
*                                   \
*                            rsext  /     Dsb (Includes internal
*                                   \     FET source area and STI
*                                   |     bounded perimeter)
*                                   |
*                                   O
*                                 source
*
*
***************************************************************************
.subckt nfethvt d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                       gcon=1 rsx=50 dtemp=0 rf=0 stis=2 par=1
*
.param
+  zad=ad zas=as znrd=nrd znrs=nrs zpd=pd zps=ps
* Gate bounded perimeter (identical for source and drain)
+  pgate = '(w+ndelrx)'
*
* STI S/D bounded perimeter (subtract gate bounded from total passed in)
+  pstis = 'max(0,(zps-pgate))'
+  pstid = 'max(0,(zpd-pgate))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt=1.00e-8    kvtw=-0.100u   kvtl=0.065u
+  kmb=1.00e-5    kmbw=-0.120u   kmbl=0.100u
+  sigvth='kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta='kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0=agauss(0,sigvth,3)        $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)       $ beta mis-match
+  mmbody=0
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+ noi_scale='noistdn-min(log(sqrt(w*l*nf*par/noidevan)),0)'
+ noi_mul='exp(dnoinhv*noi_scale)'
*
* Gate resistance calculation (function of w, l and nf)
+  rge1='(pcrsi/(nf*gcon))*(0.4u+w/(3*gcon))/(l+lwbpc)'
+  rgw1='(0.0462*(((w-2*wint_n)*nf)**(-0.4498)))'
+  rgl1='((3e6*(l-2*lint_n)+1.2147)/1.64)'
*
* STI switch to turn on or turn off the stress effect
+  stise = '(gsti==2)*2+(gsti<2)*stis'
+  ngsti = '(gsti==0)'
*
* RX length calculation
+  rxl = 'max(0.46u,((zas+zad)/w/2))'
*
* STI stress effect calculation based on RX length
+  stist      = '(1-ngsti)*(stise*2.5*exp(-2e6*rxl))'
+  stilu0     = '22.1*stist/(nf*2)'
*
* DLC adjustment
+  dlc1='0.06*l+lint_nhv+1.62e-8'
*
m0 d1 g1 s1 b1 nchhv  w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                     nrd=0 nrs=0 m=nf dtemp=dtemp
rdext  d1  d r='(znrd*rsh_nhv/nf)'
rsext  s1  s r='(znrs*rsh_nhv/nf)'
rgate  g1  g r='(rge1+rgw1*rgl1)'
rsb     b b1 r='(rsx)'
ddb     b1 d1 ndio area=zad pj=pstid m=nf dtemp=dtemp
dsb     b1 s1 ndio area=zas pj=pstis m=nf dtemp=dtemp
***************************************************************************
* NFETHV BSIM3v3.2.4 Model
***************************************************************************
.model nchhv     nmos (                            level   = 49
+version = 3.24           tnom    = 25             tox     = tox_nhv
+xj      = 2.5e-7         nch     = 1e18           ngate   = 1e20
+k1      = 0.505832       k2      = 0.0300291      vth0    = 'vth0_nhv+mmvth0'
+k3      = 54.5803        k3b     = 10.8356        w0      = 5.3387e-6
+nlx     = 1.67649e-7     dvt0w   = -9.47588       dvt1w   = 1.67988e7
+dvt2w   = -0.122689      dvt0    = 1.72577        dvt1    = 0.274598
+dvt2    = 0.0550841      wuc     = -1.6e-11       u0      = 'u0_nhv+mmbeta'
+ua      = 1.75752e-9     ub      = 1.35041e-19    uc      = 4.27111e-11
+vsat    = vsat_nhv       a0      = 1.37433        ags     = 0.52
+b0      = -3.4e-6        b1      = 1e-4           keta    = 9.68862e-3
+a1      = 0.0327544      a2      = 0.682192       rdsw    = rdsw_nhv
+prwg    = 0.0364393      prwb    = 0.0165541      wr      = 1
+wint    = wint_nhv       lint    = lint_nhv       lketa   = 6e-3
+wvsat   = 1e4            dwg     = -4.49417e-9    dwb     = 5.9063e-9
+voff    = -0.163649      nfactor = 0.350781       cit     = 0
+cdsc    = 1.90852e-3     cdscd   = 2.94472e-4     cdscb   = -1.11764e-3
+eta0    = 0.5            etab    = -1.5           dsub    = 1.270
+pclm    = 1.6833         pdiblc1 = 0.0197408      pdiblc2 = 7.18977e-3
+pdiblcb = 0.5            drout   = 0.105769       pscbe1  = 2.79004e9
+pscbe2  = 2.95441e-6     pvag    = 0.430716       delta   = 5.387e-3
+mobmod  = 1              wk3b    = 12.7           paramchk= 0
+wrdsw   = 0              lvsat   = -920           nqsmod  = 0
+elm     = 5              lua     = 3.85076e-12    pu0     = 1
+pua     = -1.25e-11      pa0     = 0.08           pketa   = 1.7e-3
+lub     = 1.55384e-20    luc     = 2e-11          lrdsw   = 0.789242
+lu0     = '10.8-stilu0' lags    = -0.1            wu0     = -16.8226
+wb0     = -1e-6          wl      = -8.71602e-13   wln     = 0.172078
+ww      = 1.6e-15        ll      = 0              lw      = -8.28732e-20
+lwn     = 2.4e-3         ww0     = -3.65587e-7    wk3     = -29.9481
+alpha0  = 5.0e-8         beta0   = 13.4           alpha1  = 0.56
*
***************************************************************************
* Source/Drain Diode Parameters
***************************************************************************
+acm     = 2              tlev    = 0              tlevc   = 1
+eg      = 1.17           gap1    = 4.73E-4        gap2    = 636
+cj      = cj_nhv         pb      = pb_nhv         mj      = mj_nhv
+cjsw    = cjsg_nhv       php     = pbsg_nhv       mjsw    = mjsg_nhv
+cjgate  = cjsg_nhv       xti     = 3              n       = n_nhv
+js      = js_nhv         jsw     = jsw_nhv        hdif    = 0
+rsh     = 0              tcjswg  = tcjsg_n        tpbswg  = tpbsg_n
*
***************************************************************************
* Capacitance-Voltage (CV) Parameters
***************************************************************************
+capmod  = 2              xpart   = 0              dlc     = dlc1
+dwc     = wint_nhv       cgdo    = cgdo_nhv       cgso    = cgso_nhv
+cgsl    =  cgsl_nhv      cgdl    = cgdl_nhv       ckappa  = 9.4618
+cf      =  1.575E-11     cgbo    = 4.532e-11      acde    = 1.2
+llc     = 0              lwc     = 0              lwlc    = 0
+wlc     = 0              wwc     = 0              wwlc    = 0
*
***************************************************************************
* Jds/Vt Temperature Parameters
***************************************************************************
+prt     = 100            ute     = -1.6           wat     = 0
+kt1     = -0.2123581     kt1l    = -8.527988e-9   kt2     = -0.0454518
+ua1     = 3.558034e-9    ub1     = -4.43341e-18   uc1     = -4.58155e-11
+at      = 3e4            lat     = 0
*
***************************************************************************
* Flicker Noise Parameters
***************************************************************************
+noimod  = 2               noia = '4.0e18*noi_mul'   noib  = '2.3e5*noi_mul'
+noic = '-2.0e-12*noi_mul' em     = 7.0e6              af  = 1
+ef      = 0.97            kf     = 0   )
*
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model ndio  d (          level   = 1              tref    = 25
+xti     = 3              tlev    = 0              tlevc   = 1
+eg      = 1.17           gap1    = 4.73e-4        gap2    = 636
+js      = js_nhv         jsw     = jsw_nhv        n       = n_nhv
+cj      = cj_nhv         pb      = pb_nhv         mj      = mj_nhv
+cjsw    = cjsw_nhv       php     = pbsw_nhv       mjsw    = mjsw_nhv
+rs      = 120p           cta     = cta_n          ctp     = ctp_n
+tpb     = pta_n          tphp    = ptp_n )
*
***************************************************************************
.ends nfethvt

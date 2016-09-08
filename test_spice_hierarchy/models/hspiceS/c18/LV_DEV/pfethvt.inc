* Path, Component, Release: cmos7base/rel/HSPICE/models/pfethvt.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL    pfethvt   1.8V High Vt PFET subcircuit
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
*            +       nf = 1    <- number of gate stripes or "fingers" in device
*            +  m (par) = 1    <- number of parallel instances (multiplicity)
*            +     gcon = 1    <- Gate connection switch (1->single-ended,
*                                                         2->double-ended)
*            +      rsx = 50   <- body resistance
*            +       rf = 0    <- RF device flag (Not Used)
*  NOTES:
*
*  1. If nrd or nrs are not passed to the model they will default to 0.
*     This will result in 0 ohms of silicided S/D resistance being placed
*     in series with the device model.
*
*  2. Intrinsic FET model includes PC bounded perimeter only.
*
* SUBCIRCUIT SCHEMATIC:
*
*                                drain
*                                  O
*                                  |
*                                  |
*                                  /
*                           rdext  \     Ddb (Includes internal FET drain area
*                                  /          and STI bounded perimeter)
*                              d1  |______|\|__________
*                                  |      |/|          |
*                                  |                   |
*                                  |                   |
*                              ____|                   |
*    gate               g1  | |                |  b1   |            bulk
*        O-------\/\/\/-----| |                |-------o---\/\/\/----O
*                 rgate     | |____            |       |     rsb
*                                  |                   |
*                                  |                   |
*                                  |                   |
*                              s1  |______|\|__________|
*                                  |      |/|
*                                  \
*                           rsext  /     Dsb (Includes internal FET source area
*                                  \          and STI bounded perimeter)
*                                  |
*                                  |
*                                  O
*                                source
*
*
***************************************************************************
.subckt pfethvt  d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                        gcon=1 rsx=50 dtemp=0 rf=0 par=1
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
+  kvt = 9.99e-9  kvtw =  0.130u   kvtl = 0.031u
+  kmb = 9.96e-6  kmbw = -0.500u   kmbl = -0.5u
+  sigvth='kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta='kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0=agauss(0,sigvth,3)        $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)       $ beta mis-match
+  mmbody=0
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+ noi_scale='noistdp-min(log(sqrt(w*l*nf*par/noidevap)),0)'
+ noi_mul='exp(dnoiphv*noi_scale)'
*
* Gate resistance calculation for all cases (function of w, l and nf)
+  rge1='(pcrsi/(nf*gcon))*(0.42u+w/(3*gcon))/(l+lwbpc)'
+  rgw1='(27.227*(((w-2*wint_phv)*nf*1e6)**(-0.55)))'
+  rgl1='(10e6*(l-2*lint_phv)+0.1324)/1.665'
*
* DLC adjustment
+  dlc1='0.08*l+lint_phv+0.86e-8'
*
m0 d1 g1 s1 b1 pch     w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+                      nrd=0 nrs=0 m=nf dtemp=dtemp
rdext  d1  d r='(znrd*rsh_phv/nf)'
rsext  s1  s r='(znrs*rsh_phv/nf)'
rgate  g1  g r='(rge1+rgw1*rgl1)'
rsb     b b1 r='rsx'
ddb    d1 b1 pdio area=zad pj=pstid m=nf dtemp=dtemp
dsb    s1 b1 pdio area=zas pj=pstis m=nf dtemp=dtemp
***************************************************************************
* PFETHV BSIM3v3.2.4 Model
***************************************************************************
.model pch pmos (
+level   = 49             version = 3.24           tnom    = 25
+tox     = tox_phv        xj      = 2e-7           nch     = 1e18
+vth0 = 'vth0_phv+mmvth0' k1      = 0.523094       k2      = 0.0739021
+k3      = -2.41762       k3b     = 5.0464         w0      = 0
+nlx     = 3.91809e-8     dvt0w   = -0.0153864     dvt1w   = 0
+dvt2w   = -0.116536      dvt0    = 1.38           dvt1    = 0.39
+dvt2    = -0.246987      u0     = 'u0_phv+mmbeta' ua      = 8.812e-9
+ub      = -5.08767e-18   uc      = -4.71234e-10   vsat    = 2.77e5
+a0      = 1.145          ags     = 0.25           wags    = 0.07
+b0      = 1.88395e-5     b1      = 6.88135e-5     keta    = 0.0375
+a1      = 0.104          a2      = 1.18           rdsw    = rdsw_phv
+prwg    = -3.50105e-4    prwb    = -3.291         wr      = 1
+wint    = wint_phv       lint    = lint_phv       lvsat   = 6e4
+dwg     = 2e-9           dwb     = 1.51077e-8     voff    = -0.108422
+nfactor = 1.2075         cit     = 0              cdsc    = 0
+cdscd   = 2.94472e-4     cdscb   = -1.39821e-4    eta0    = 0.3413
+etab    = -0.089082      dsub    = 1.246          pclm    = 17.4192
+pdiblc1 = 0              pdiblc2 = 0              pdiblcb = -9.37507
+drout   = 0              pscbe1  = 1.83659e10     pscbe2  = -2.29673e-6
+pvag    = 120.146        delta   = 0.02           ngate   = 8e19
+alpha0  = 6.100e-9       alpha1  = 8.340e-3       beta0   = 14
+mobmod  = 1              nqsmod  = 0
+elm     = 5              wl      = 2.33663e-9     wln     = 0.0168336
+ww      = 0              wwn     = 0              wwl     = 0
+ll      = 0              lln     = 0              lw      = -1.94617e-11
+lwn     = 0.465146       lwl     = 0              lua     = -0.3e-10
+la0     = 0.05           paramchk= 0              binunit = 1
*
***************************************************************************
* Source/Drain Diode Parameters
***************************************************************************
+acm     = 2              tlev    = 0              tlevc   = 1
+eg      = 1.17           gap1    = 4.73E-4        gap2    = 636
+cj      = cj_phv         pb      = pb_phv         mj      = mj_phv
+cjsw    = cjsg_phv       php     = pbsg_phv       mjsw    = mjsg_phv
+cjgate  = cjsg_phv       xti     = 3              n       = n_phv
+js      = js_phv         jsw     = jsw_phv        hdif    = 0
+rsh     = 0              tcjswg  = tcjsg_p        tpbswg  = tpbsg_p
*
***************************************************************************
* Capacitance-Voltage (CV) Parameters
***************************************************************************
+capmod = 2               xpart = 0                 acde    = 1.2
+cgso   = cgso_phv        cgdo  = cgdo_phv          cgbo    = 4.062e-11
+cgsl   = cgsl_phv        cgdl  = cgdl_phv          ckappa  = 6.1716
+cf     = 1.625e-11       dlc   = dlc1              dwc     = wint_phv
+llc    = 0               lwc   = 0                 lwlc    = 0
+wlc    = 0               wwc   = 0                 wwlc    = 0
*
***************************************************************************
* Jds/Vt Temperature Parameters
***************************************************************************
+prt     = 0              at      = -1.6e5         ute     = -1.5
+kt1     = -0.316398      kt1l    = 2.833249e-9    kt2     = -0.0484837
+ua1     = -9.0e-10       ub1     = -3.0e-18       uc1     = 1.210193e-10
*
***************************************************************************
* Flicker Noise Parameters
***************************************************************************
+noimod = 2                noia = '3.62e+18*noi_mul' noib   = '1e6*noi_mul'
+noic = '9.86e-12*noi_mul' em     = 4.0e+7           af     = 1
+ef     = 1.2              kf     = 0     )
*
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model pdio    d (        level   = 1              tref    = 25
+xti     = 3              tlev    = 0              tlevc   = 1
+eg      = 1.17           gap1    = 4.73E-4        gap2    = 636
+js      = js_phv         jsw     = jsw_phv        n       = n_phv
+cj      = cj_phv         pb      = pb_phv         mj      = mj_phv
+cjsw    = cjsw_phv       php     = pbsw_phv       mjsw    = mjsw_phv
+rs      = 120p           cta     = cta_p          ctp     = ctp_p
+tpb     = pta_p          tphp    = ptp_p )
*
***************************************************************************
.ends pfethvt

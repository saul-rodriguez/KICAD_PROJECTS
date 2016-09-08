* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfet20hs.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HV MOSFET: PFET20HS
*
*
* *****************************************************************************
.subckt	 pfet20hs d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(3.2525e-06/l+5.2348e-01)'
+ mv_pfet20hs = agauss(0,1,1)
+ mu_pfet20hs = agauss(0,1,1)
+ dvthmat = 'mv_pfet20hs*(1.739e-08/sqrt(l*w*mult))'
+ dumat = 'mu_pfet20hs*(5.233e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 1.8
+  noideva   = 2.4e-10
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dpf20hsnoi*noi_scale)'
+  noib_mul  = 'exp(dpf20hsnoi*noi_scale/2)'
+  noic_mul  = 'exp(dpf20hsnoi*noi_scale/4)'
*
mpfet20hs  d1 g s1 b  mosinsub w=w l=l nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 dtemp=dtemp
rd d1 d r='(rj_pfet20hs/(w+(8.0000e-07)))'  tc1=5.6432e-03  tc2=1.5133e-05  dtemp=dtemp
rs s1 s r='(rj_pfet20hs/(w+(8.0000e-07)))'  tc1=5.6432e-03  tc2=1.5133e-05  dtemp=dtemp
xj1  d gj1 d1  pfet20hsjfet1 w=w dtemp=dtemp
xj2  d gj1 d1  pfet20hsjfet2 w=w dtemp=dtemp
xj3  s gj2 s1  pfet20hsjfet1 w=w dtemp=dtemp
xj4  s gj2 s1  pfet20hsjfet2 w=w dtemp=dtemp
e1  d1 gj1     value='min(v(d1,s1),0)*gv'
e2  s1 gj2     value='min(v(s1,d1),0)*gv'
cgdx g d  c='(cgdx1_pfet20hs*w)'  dtemp=dtemp
cgsx g s  c='(cgdx1_pfet20hs*w)'  dtemp=dtemp
*
xqpnp1 sub b d	pfet20hspnp  area=1  w=w l=l dtemp=dtemp
xdcbx1 sub b	pfet20hsdcbx area=1  w=w dtemp=dtemp
xqpnp2 sub b s	pfet20hspnp  area=1  w=w l=l dtemp=dtemp
xdcbx2 sub b	pfet20hsdcbx area=1  w=w dtemp=dtemp
*
.model mosinsub pmos level=49 version=3.3  capmod=2
+  mobmod=2  nqsmod=0  noimod=3
+  k1=k1_pfet20hs
+  k2=k2_pfet20hs      k3=0.0000e+00
+  k3b=-2.860e-01      nch=1.4267e+16	  vth0='vth0_pfet20hs+dvthmat'
+  voff=-6.163e-02     dvt0=dvt0_pfet20hs dvt1=4.0192e-01
+  dvt2=-3.548e-01     keta=0.0000e+00
+  pscbe1=4.2400e+08   pscbe2=1.0000e-12
+  alpha0=0.0000e+00   beta0=3.0000e+01
+  dvt0w=1.0000e+01    dvt1w=5.3000e+06	  dvt2w=-3.200e-02
+  ua=4.4674e-09       ub=-3.907e-18	  uc=-3.916e-10
+  u0='uo_pfet20hs*(1+dumat)'
+  dsub=1.0000e+00     eta0=-3.468e-01	  etab=-4.734e-01
+  nfactor=8.2499e-01  em=4.1000e+07	  pclm=3.6204e+00
+  drout=5.0000e-01    a0=4.5833e-01	  a1=0.0000e+00
+  a2=1.0000e+00       pvag=0.0000e+00	  vsat=vsat_pfet20hs
+  ags=2.4746e-02      b0=1.0000e-09	  b1=1.0000e-09
+  pdiblcb=-1.000e-06  pdiblc1=0.000e+00  pdiblc2=1.0000e-02
+  delta=1.0000e-01    w0=1.0000e-07	  dlc=dlc_pfet20hs
+  dwc=1.0688e-07      dwb=0.0000e+00	  dwg=0.0000e+00
+  ll=0.0000e+00       lw=0.0000e+00	  lwl=0.0000e+00
+  lln=1.0000e+00      lwn=1.0000e+00	  wl=0.0000e+00
+  ww=0.0000e+00       wwl=0.0000e+00	  wln=1.0000e+00
+  wwn=1.0000e+00      tnom=2.5000e+01	  at=-4.526e+04	     ute=-1.610e+00
+  kt1=-7.230e-01      kt2=-1.000e-01	  kt1l=0.0000e+00
+  ua1=-3.007e-09      ub1=0.0000e+00	  uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_pfet20hs  cgdo=1.00000e-12   cgbo=1.2000e-09
+  cgdl=1.0000e-10     cgsl=1.0000e-10	  ckappa=3.0000e+00
+  cf=0.0000e+00       elm=5.0000e+00
+  xpart=5.0000e-01    clc=1.0000e-15     cle=6.0000e-01
+  rdsw=4.9199e+03
+  cdsc=0.0000e+00     cdscb=-5.953e-05	  cdscd=1.0000e-05
+  prwb=1.0000e-03     prwg=0.0000e+00	  cit=0.0000e+00
+  tox=tox_pfet20hs    ngate=0.0000e+00	  nlx=0.0000e+00
+  xl=xl_pfet20hs      xw=xw_pfet20hs
+  af=1.0322e+00       kf=8.9893e-29	  ef=1.0000e+00
+  noia='3.6184e+19*noia_mul'
+  noib='2.5675e+03*noib_mul'
+  noic='5.0409e-13*noic_mul'
+  rd=0.0000e+00       rs=0.0000e+00	  rsh=0.0000e+00
+  rdc=0.0000e+00      rsc=0.0000e+00	  lint=2.4393e-07
+  wint=1.0688e-07     ldif=0.000e+00	  hdif=8.0000e-07
+  xj=3.0000e-07       js=1.0900e-07	  is=0.0
+  n=1.0000e+00	       tlev=0		  tlevc=1
+  jsw=0.0000e+00      cj=cj_pfet20hs	  cjsw=cjsw_pfet20hs
+  fc=0.000e+00	       xti=1.1880e-01
+  mj=4.4990e-01       mjsw=4.4990e-01
+  pb=8.6950e-01       pbsw=8.6950e-01
.ends pfet20hs
*
* HV-jfet 1
*
.subckt	 pfet20hsjfet1 d b s
.param w=1e-6  dtemp=0
jpfet20hsjfet1 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta1_pfet20hs/(1+(2.8767e-03)*pdelt)*(w+(8.0000e-07))/(1+(5.6432e-03)*pdelt+(1.5133e-05)*pdelt**2)'
+ vto='vth1_pfet20hs*(1+(2.8767e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet20hsjfet1
*
* HV-jfet 2
*
.subckt	 pfet20hsjfet2 d b s
.param w=1e-6  dtemp=0
jpfet20hsjfet2 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta2_pfet20hs/(1+(2.8767e-03)*pdelt)*(w+(8.0000e-07))/(1+(5.6432e-03)*pdelt+(1.5133e-05)*pdelt**2)'
+ vto='vth2_pfet20hs*(1+(2.8767e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet20hsjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 pfet20hspnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qpfet20hspnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='3.903e-06*w*1e-06+1.000e-18*w*l+3.337e-17*exp(-1.000e-18/(l*1e-06))'
+ ise='3.535e-06*w*1e-06+1.000e-18*w*l+1.000e-17*exp(-1.000e-15/(l*1e-06))'
+ ikf='4.500e+06*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.500e+06*w*1e-06'  isc=1.000e-18
+ bf='3.054e+01*exp(8.220e-12/(w*1e-06))+1.259e+02*exp(-3.246e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+6.900e-08/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+1.000e-15/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.290e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=3.315e+00
+ cje='((2.591e-04*((w+4e-06)*(2.1e-06))+5.672e-10*(2*((w+4e-06)+2.1e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+13.5e-06)*(l+5.9e-06))+7.569e-10*(2*((l+5.9e-06)+(w+13.5e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.0322e+00	 kf=0.000e+00	fc=7.500e-01
.ends pfet20hspnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 pfet20hsdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dpfet20hsdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='2.733e-15+4.350e-06*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends pfet20hsdcbx

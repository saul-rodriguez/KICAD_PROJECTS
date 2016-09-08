* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfet50t.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*> HV MOSFET: PFET50T
*
*
* *****************************************************************************
.subckt	 pfet50t d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(2.00e-07/l+4.90e-01)'
+ mv_pfet50t = agauss(0,1,1)
+ mu_pfet50t = agauss(0,1,1)
+ dvthmat = 'mv_pfet50t*(3.995e-09/sqrt(l*w*mult))'
+ dumat = 'mu_pfet50t*(7.778e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.3
+  noideva   = 2.4e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dpf20tnoi*noi_scale)'
+  noib_mul  = 'exp(dpf20tnoi*noi_scale/2)'
+  noic_mul  = 'exp(dpf20tnoi*noi_scale/4)'
*
mpfet50t  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_pfet50t/(w+(6.5697e-07)))'  tc1=4.8236e-03  tc2=7.2840e-06  dtemp=dtemp
xj1  d gj d1  pfet50tjfet1 w=w dtemp=dtemp
xj2  d gj d1  pfet50tjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_pfet50t*w)'  dtemp=dtemp
*
xqpnp  sub b d	pfet50tpnp  area=1  w=w l=l dtemp=dtemp
xdcbx  sub b	pfet50tdcbx area=1  w=w dtemp=dtemp
*
.model mosinsub pmos level=49 version=3.3  capmod=2
+  mobmod=2  nqsmod=0  noimod=3
+  k1=k1_pfet50t
+  k2=k2_pfet50t       k3=0.0000e+00
+  k3b=5.1402e+00      nch=7.9856e+16	  vth0='vth0_pfet50t+dvthmat'
+  voff=-1.479e-01     dvt0=dvt0_pfet50t  dvt1=1.9948e-01
+  dvt2=3.7642e-01     keta=-4.700e-02
+  pscbe1=4.2400e+08   pscbe2=1.0000e-12
+  alpha0=0.0000e+00   beta0=3.0000e+01
+  dvt0w=1.0000e+01    dvt1w=5.3000e+06	  dvt2w=-3.200e-02
+  ua=1.7017e-09       ub=-5.230e-20	  uc=-1.774e-09
+  u0='uo_pfet50t*(1+dumat)'
+  dsub=9.2350e-01     eta0=0.0000e+00	  etab=-2.363e-03
+  nfactor=1.1742e+00  em=4.1000e+07	  pclm=5.0000e-03
+  drout=5.0000e-01    a0=1.0786e+00	  a1=0.0000e+00
+  a2=1.0000e+00       pvag=0.0000e+00	  vsat=vsat_pfet50t
+  ags=3.8804e-01      b0=1.0000e-09	  b1=1.0000e-09
+  pdiblcb=-1.000e-06  pdiblc1=0.000e+00  pdiblc2=5.0000e-06
+  delta=2.9734e-02    w0=0.0000e+00	  dlc=dlc_pfet50t
+  dwc=2.6309e-07      dwb=0.0000e+00	  dwg=0.0000e+00
+  ll=0.0000e+00       lw=0.0000e+00	  lwl=0.0000e+00
+  lln=1.0000e+00      lwn=1.0000e+00	  wl=0.0000e+00
+  ww=0.0000e+00       wwl=0.0000e+00	  wln=1.0000e+00
+  wwn=1.0000e+00      tnom=2.5000e+01	  at=3.3000e+04	     ute=-1.000e+00
+  kt1=-2.429e-01      kt2=0.0000e+00	  kt1l=-1.812e-08
+  ua1=2.8467e-09      ub1=-1.000e-17	  uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_pfet50t   cgdo=1.0000e-12	  cgbo=0.0000e+00
+  cgdl=1.4770e-10     cgsl=3.0000e-10	  ckappa=2.9800e+00
+  elm=5.0000e+00
+  xpart=5.0000e-01
+  rdsw=0.0000e+00
+  cdsc=1.0000e-03     cdscb=0.0000e+00	  cdscd=0.0000e+00
+  prwb=0.0000e+00     prwg=0.0000e+00	  cit=0.0000e+00
+  tox=tox_pfet50t     ngate=0.0000e+00	  nlx=1.7400e-07
+  xl=xl_pfet50t       xw=xw_pfet50t
+  af=1.4235e+00       kf=8.6041e-26	  ef=1.0000e+00
+  noia='3.4447e+18*noia_mul'
+  noib='3.2325e+04*noib_mul'
+  noic='1.6967e-12*noic_mul'
+  rd=0.0000e+00       rs=0.0000e+00	  rsh=0.0000e+00
+  rdc=0.0000e+00      rsc=0.0000e+00	  lint=-1.270e-08
+  wint=2.6309e-07     ldif=0.000e+00	  hdif=8.0000e-07
+  xj=3.0000e-07       js=1.0900e-07	  is=0.0
+  n=1.0000e+00	       tlev=0		  tlevc=1
+  jsw=0.0000e+00      cj=cj_pfet50t	  cjsw=0.0000e+00
+  fc=0.000e+00	       xti=1.1880e-01
+  pb=8.6950e-01       pbsw=8.6850e-01
.ends pfet50t
*
* HV-jfet 1
*
.subckt	 pfet50tjfet1 d b s
.param w=1e-6  dtemp=0
jpfet50tjfet1 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta1_pfet50t/(1+(2.5195e-03)*pdelt)*(w+(6.5697e-07))/(1+(4.8236e-03)*pdelt+(7.2840e-06)*pdelt**2)'
+ vto='vth1_pfet50t*(1+(2.5195e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet50tjfet1
*
* HV-jfet 2
*
.subckt	 pfet50tjfet2 d b s
.param w=1e-6  dtemp=0
jpfet50tjfet2 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta2_pfet50t/(1+(2.5195e-03)*pdelt)*(w+(6.5697e-07))/(1+(4.8236e-03)*pdelt+(7.2840e-06)*pdelt**2)'
+ vto='vth2_pfet50t*(1+(2.5195e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet50tjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 pfet50tpnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qpfet50tpnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='4.004e-06*w*1e-06+1.000e-18*w*l+8.152e-17*exp(-7.045e-15/(l*1e-06))'
+ ise='2.535e-06*w*1e-06+1.000e-16*w*l+5.200e-17*exp(-1.000e-15/(l*1e-06))'
+ ikf='5.922e+05*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.483e+05*w*1e-06'  isc=1.000e-18
+ bf='8.154e+01*exp(4.831e-12/(w*1e-06))+2.871e+01*exp(-3.246e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+1.000e-07/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+6.715e-15/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.250e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=1.315e+00
+ cje='((2.591e-04*((w+7.5e-06)*(l+4e-06))+5.672e-10*(2*((w+7.5e-06)+l+4e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+14.1e-06)*(l+7.1e-06))+7.569e-10*(2*((l+7.1e-06)+(w+14.1e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.4235e+00	 kf=0.000e+00	fc=7.500e-01
.ends pfet50tpnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 pfet50tdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dpfet50tdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='3.733e-15+1.235e-05*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends pfet50tdcbx

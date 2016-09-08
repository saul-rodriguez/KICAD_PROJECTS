* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfet20h.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
* *****************************************************************************
*
*>  HV MOSFET: PFET20H
*
*
* *****************************************************************************
.subckt	 pfet20h d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(4.4758e-07/l+9.0666e-02)'
+ mv_pfet20h = agauss(0,1,1)
+ mu_pfet20h = agauss(0,1,1)
+ dvthmat = 'mv_pfet20h*(2.411e-08/sqrt(l*w*mult))'
+ dumat = 'mu_pfet20h*(4.172e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.2
+  noideva   = 7.2e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dpf20hnoi*noi_scale)'
+  noib_mul  = 'exp(dpf20hnoi*noi_scale/2)'
+  noic_mul  = 'exp(dpf20hnoi*noi_scale/4)'
*
mpfet20h  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_pfet20h/(w+(1.0203e-07)))'  tc1=4.3170e-03  tc2=0.0000e+00  dtemp=dtemp
xj1  d gj d1  pfet20hjfet1 w=w dtemp=dtemp
xj2  d gj d1  pfet20hjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_pfet20h*w)'  dtemp=dtemp
*
xqpnp  sub b d	pfet20hpnp  area=1  w=w l=l dtemp=dtemp
xdcbx  sub b	pfet20hdcbx area=1  w=w dtemp=dtemp
*
.model mosinsub pmos level=49 version=3.3  capmod=2
+  mobmod=2  nqsmod=0  noimod=3
+  k1=k1_pfet20h
+  k2=k2_pfet20h       k3=0.0000e+00
+  k3b=4.2771e+00      nch=2.1275e+16	  vth0='vth0_pfet20h+dvthmat'
+  voff=-1.500e-01     dvt0=dvt0_pfet20h  dvt1=9.1644e-01
+  dvt2=5.2000e-02     keta=-4.700e-02
+  pscbe1=4.2400e+08   pscbe2=1.0000e-12
+  alpha0=0.0000e+00   beta0=3.0000e+01
+  dvt0w=1.0000e+01    dvt1w=5.3000e+06	  dvt2w=-3.200e-02
+  ua=2.7498e-09       ub=-2.833e-19	  uc=-4.415e-10
+  u0='uo_pfet20h*(1+dumat)'
+  dsub=1.0000e+00     eta0=3.0497e-02	  etab=-4.420e-02
+  nfactor=2.4409e+00  em=4.1000e+07	  pclm=8.6204e-01
+  drout=5.0000e-01    a0=1.2071e+00	  a1=0.0000e+00
+  a2=1.0000e+00       pvag=0.0000e+00	  vsat=vsat_pfet20h
+  ags=3.5353e-02      b0=1.0000e-09	  b1=1.0000e-09
+  pdiblcb=-1.000e-06  pdiblc1=0.000e+00  pdiblc2=1.0000e-05
+  delta=1.0000e-01    w0=1.0000e-07	  dlc=dlc_pfet20h
+  dwc=1.4020e-07      dwb=0.0000e+00	  dwg=0.0000e+00
+  ll=0.0000e+00       lw=0.0000e+00	  lwl=0.0000e+00
+  lln=1.0000e+00      lwn=1.0000e+00	  wl=0.0000e+00
+  ww=0.0000e+00       wwl=0.0000e+00	  wln=1.0000e+00
+  wwn=1.0000e+00      tnom=2.5000e+01	  at=3.3000e+04	     ute=-1.429e+00
+  kt1=-1.069e+00      kt2=0.0000e+00	  kt1l=0.0000e+00
+  ua1=1.0000e-18      ub1=-4.660e-18	  uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_pfet20h   cgdo=1.0000e-12	  cgbo=5.0000e-10
+  cgdl=1.0000e-12     cgsl=1.0000e-12	  ckappa=3.0000e+00
+  elm=5.0000e+00
+  xpart=5.0000e-01
+  rdsw=0.0000e+00
+  cdsc=1.0000e-03     cdscb=0.0000e+00	  cdscd=1.1797e-04
+  prwb=0.0000e+00     prwg=0.0000e+00	  cit=0.0000e+00
+  tox=tox_pfet20h     ngate=0.0000e+00	  nlx=1.7400e-07
+  xl=xl_pfet20h       xw=xw_pfet20h
+  af=1.0448e+00       kf=1.9689e-28	  ef=1.0000e+00
+  noia='9.6305e+19*noia_mul'
+  noib='2.0000e+03*noib_mul'
+  noic='1.2597e-12*noic_mul'
+  rd=0.0000e+00       rs=0.0000e+00	  rsh=0.0000e+00
+  rdc=0.0000e+00      rsc=0.0000e+00	  lint=2.9821e-08
+  wint=1.4020e-07     ldif=0.000e+00	  hdif=8.0000e-07
+  xj=3.0000e-07       js=4.4690e-07	  is=0.0
+  n=1.0000e+00	       tlev=0		  tlevc=1
+  jsw=0.0000e+00      cj=cj_pfet20h	  cjsw=0.0000e+00
+  fc=0.000e+00	       xti=3.5650e-01
+  pb=1.0000e+00       pbsw=1.0000e+00
.ends pfet20h
*
* HV-jfet 1
*
.subckt	 pfet20hjfet1 d b s
.param w=1e-6  dtemp=0
jpfet20hjfet1 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta1_pfet20h/(1+(3.7105e-03)*pdelt)*(w+(1.0203e-07))/(1+(4.3170e-03)*pdelt+(0.0000e+00)*pdelt**2)'
+ vto='vth1_pfet20h*(1+(3.7105e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet20hjfet1
*
* HV-jfet 2
*
.subckt	 pfet20hjfet2 d b s
.param w=1e-6  dtemp=0
jpfet20hjfet2 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta2_pfet20h/(1+(3.7105e-03)*pdelt)*(w+(1.0203e-07))/(1+(4.3170e-03)*pdelt+(0.0000e+00)*pdelt**2)'
+ vto='vth2_pfet20h*(1+(3.7105e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet20hjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 pfet20hpnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qpfet20hpnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='2.988e-06*w*1e-06+1.000e-18*w*l+3.644e-17*exp(-4.441e-18/(l*1e-06))'
+ ise='2.563e-06*w*1e-06+1.000e-18*w*l+1.000e-18*exp(-1.000e-15/(l*1e-06))'
+ ikf='9.400e+05*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.500e+06*w*1e-06'  isc=1.000e-18
+ bf='6.516e+01*exp(3.141e-12/(w*1e-06))+1.033e+02*exp(-3.246e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+3.000e-07/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+1.000e-15/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.290e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=3.315e+00
+ cje='((2.591e-04*((w+1.5e-06)*(l+1.2e-06))+5.672e-10*(2*((w+1.5e-06)+l+1.2e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+7e-06)*(l+4.5e-06))+7.569e-10*(2*((l+4.5e-06)+(w+7e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.0448e+00	 kf=0.000e+00	fc=7.500e-01
.ends pfet20hpnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 pfet20hdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dpfet20hdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='2.733e-15+4.350e-06*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends pfet20hdcbx

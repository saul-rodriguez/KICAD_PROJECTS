* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfet50hs.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HV MOSFET: PFET50HS
*
*
* *****************************************************************************
.subckt	 pfet50hs d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(3.8071e-07/l+4.3000e-01)'
+ mv_pfet50hs = agauss(0,1,1)
+ mu_pfet50hs = agauss(0,1,1)
+ dvthmat = 'mv_pfet50hs*(1.782e-08/sqrt(l*w*mult))'
+ dumat = 'mu_pfet50hs*(4.738e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.2
+  noideva   = 3.6e-10
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dpf50hsnoi*noi_scale)'
+  noib_mul  = 'exp(dpf50hsnoi*noi_scale/2)'
+  noic_mul  = 'exp(dpf50hsnoi*noi_scale/4)'
*
mpfet50hs  d1 g s1 b  mosinsub w=w l=l nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 dtemp=dtemp
rd d1 d r='(rj_pfet50hs/(w+(2.1476e-06)))'  tc1=5.0512e-03  tc2=1.0000e-05  dtemp=dtemp
rs s1 s r='(rj_pfet50hs/(w+(2.1476e-06)))'  tc1=5.0512e-03  tc2=1.0000e-05  dtemp=dtemp
xj1  d gj1 d1  pfet50hsjfet1 w=w dtemp=dtemp
xj2  d gj1 d1  pfet50hsjfet2 w=w dtemp=dtemp
xj3  s gj2 s1  pfet50hsjfet1 w=w dtemp=dtemp
xj4  s gj2 s1  pfet50hsjfet2 w=w dtemp=dtemp
e1  d1 gj1     value='min(v(d1,s1),0)*gv'
e2  s1 gj2     value='min(v(s1,d1),0)*gv'
cgdx g d  c='(cgdx1_pfet50hs*w)'  dtemp=dtemp
cgsx g s  c='(cgdx1_pfet50hs*w)'  dtemp=dtemp
*
xqpnp1 sub b d	pfet50hspnp  area=1  w=w l=l dtemp=dtemp
xdcbx1 sub b	pfet50hsdcbx area=1  w=w dtemp=dtemp
xqpnp2 sub b s	pfet50hspnp  area=1  w=w l=l dtemp=dtemp
xdcbx2 sub b	pfet50hsdcbx area=1  w=w dtemp=dtemp
*
.model mosinsub pmos level=49 version=3.3  capmod=2
+  mobmod=2  nqsmod=0  noimod=3
+  k1=k1_pfet50hs
+  k2=k2_pfet50hs      k3=6.3829e-01
+  k3b=-1.369e-02      nch=2.3422e+16	  vth0='vth0_pfet50hs+dvthmat'
+  voff=-3.392e-02     dvt0=dvt0_pfet50hs dvt1=3.4838e-01
+  dvt2=-3.200e-02     keta=-4.700e-02
+  pscbe1=4.2400e+08   pscbe2=1.0000e-12
+  alpha0=0.0000e+00   beta0=3.0000e+01
+  dvt0w=1.0000e+01    dvt1w=5.3000e+06	  dvt2w=-3.200e-02
+  ua=5.9008e-09       ub=-6.179e-18	  uc=-5.147e-10
+  u0='uo_pfet50hs*(1+dumat)'
+  dsub=1.0000e+00     eta0=0.0000e+00	  etab=0.0000e+00
+  nfactor=7.8448e-01  em=4.1000e+07	  pclm=5.0000e+00
+  drout=5.0000e-01    a0=4.5505e-01	  a1=0.0000e+00
+  a2=1.0000e+00       pvag=0.0000e+00	  vsat=vsat_pfet50hs
+  ags=2.4773e-02      b0=1.0000e-09	  b1=1.0000e-09
+  pdiblcb=-1.000e-06  pdiblc1=5.3444e-01 pdiblc2=1.0000e-05
+  delta=1.0000e-01    w0=1.0000e-07	  dlc=dlc_pfet50hs
+  dwc=1.0312e-07      dwb=0.0000e+00	  dwg=0.0000e+00
+  ll=0.0000e+00       lw=0.0000e+00	  lwl=0.0000e+00
+  lln=1.0000e+00      lwn=1.0000e+00	  wl=0.0000e+00
+  ww=0.0000e+00       wwl=0.0000e+00	  wln=1.0000e+00
+  wwn=1.0000e+00      tnom=2.5000e+01	  at=3.3000e+04	     ute=-1.412e+00
+  kt1=-6.000e-01      kt2=0.0000e+00	  kt1l=0.0000e+00
+  ua1=1.1412e-10      ub1=-1.000e-17	  uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_pfet50hs  cgdo=1.00000e-12   cgbo=1.5000e-09
+  cgdl=1.0000e-12     cgsl=1.0000e-12	  ckappa=3.0000e+00
+  elm=5.0000e+00
+  xpart=1.0000e+00
+  rdsw=0.0000e+00
+  cdsc=1.0000e-03     cdscb=0.0000e+00	  cdscd=1.0094e-04
+  prwb=0.0000e+00     prwg=0.0000e+00	  cit=0.0000e+00
+  tox=tox_pfet50hs    ngate=0.0000e+00	  nlx=1.7400e-07
+  xl=xl_pfet50hs      xw=xw_pfet50hs
+  af=1.0876e+00       kf=1.2743e-28	  ef=1.0000e+00
+  noia='3.9923e+19*noia_mul'
+  noib='5.6453e+03*noib_mul'
+  noic='4.4883e-13*noic_mul'
+  rd=0.0000e+00       rs=0.0000e+00	  rsh=0.0000e+00
+  rdc=0.0000e+00      rsc=0.0000e+00	  lint=2.4258e-08
+  wint=1.0312e-07     ldif=0.000e+00	  hdif=8.0000e-07
+  xj=3.0000e-07       js=1.0900e-07	  is=0.0
+  n=1.0000e+00	       tlev=0		  tlevc=1
+  jsw=0.0000e+00      cj=cj_pfet50hs	  cjsw=cjsw_pfet50hs
+  fc=0.000e+00	       xti=8.1180e-01
+  pb=9.8940e-01       pbsw=5.2470e-01
.ends pfet50hs
*
* HV-jfet 1
*
.subckt	 pfet50hsjfet1 d b s
.param w=1e-6  dtemp=0
jpfet50hsjfet1 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta1_pfet50hs/(1+(2.2444e-03)*pdelt)*(w+(2.1476e-06))/(1+(5.0512e-03)*pdelt+(1.0000e-05)*pdelt**2)'
+ vto='vth1_pfet50hs*(1+(2.2444e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet50hsjfet1
*
* HV-jfet 2
*
.subckt	 pfet50hsjfet2 d b s
.param w=1e-6  dtemp=0
jpfet50hsjfet2 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta2_pfet50hs/(1+(2.2444e-03)*pdelt)*(w+(2.1476e-06))/(1+(5.0512e-03)*pdelt+(1.0000e-05)*pdelt**2)'
+ vto='vth2_pfet50hs*(1+(2.2444e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet50hsjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 pfet50hspnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qpfet50hspnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='5.484e-06*w*1e-06+1.000e-18*w*l+1.434e-16*exp(-2.432e-15/(l*1e-06))'
+ ise='7.000e-06*w*1e-06+1.000e-18*w*l+5.200e-17*exp(-1.000e-15/(l*1e-06))'
+ ikf='1.000e+06*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.500e+06*w*1e-06'  isc=1.000e-18
+ bf='2.000e+02*exp(5.831e-12/(w*1e-06))+2.871e+01*exp(-3.246e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+1.500e-07/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+3.076e-10/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.290e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=1.315e+00
+ cje='((2.591e-04*((w+10e-06)*(6.6e-06))+5.672e-10*(2*((w+10e-06)+6.6e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+15e-06)*(l+11.7e-06))+7.569e-10*(2*((l+11.7e-06)+(w+15e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.0876e+00	 kf=0.000e+00	fc=7.500e-01
.ends pfet50hspnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 pfet50hsdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dpfet50hsdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='3.733e-15+1.235e-05*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends pfet50hsdcbx

* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfeti50m.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>   HV MOSFET: NFETI50M
*
*
* *****************************************************************************
.subckt	 nfeti50m d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(1.0397e-07/l+8.1720e-01)'
+ mv_nfeti50m = agauss(0,1,1)
+ mu_nfeti50m = agauss(0,1,1)
+ dvthmat = 'mv_nfeti50m*(8.202e-09/sqrt(l*w*mult))'
+ dumat = 'mu_nfeti50m*(4.667e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.2
+  noideva   = 4.8e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dnfi50mnoi*noi_scale)'
+  noib_mul  = 'exp(dnfi50mnoi*noi_scale/2)'
+  noic_mul  = 'exp(dnfi50mnoi*noi_scale/4)'
*
mnfeti50m  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_nfeti50m/(w+(6.9000e-06)))'  tc1=6.0475e-03  tc2=1.6343e-05  dtemp=dtemp
xj1  d gj d1  nfeti50mjfet1 w=w dtemp=dtemp
xj2  d gj d1  nfeti50mjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_nfeti50m*w)'  dtemp=dtemp
*
xqpnp  sub d b	nfeti50mpnp  area=1 w=w l=l dtemp=dtemp
xdcbx  sub d	nfeti50mdcbx area=1 w=w dtemp=dtemp
*
.model mosinsub nmos level=49 version=3.3  capmod=2
+  mobmod=1  nqsmod=0  noimod=3
+  k1=k1_nfeti50m
+  k2=k2_nfeti50m     k3=6.9544e+00
+  k3b=1.0000e+01     nch=2.8186e+17	 vth0='vth0_nfeti50m+dvthmat'
+  voff=-7.260e-02    dvt0=dvt0_nfeti50m dvt1=2.1602e-01
+  dvt2=1.0000e-01    keta=-1.671e-02
+  pscbe1=4.2400e+08  pscbe2=1.0000e-12
+  alpha0=0.0000e+00  beta0=3.0000e+01
+  dvt0w=0.0000e+00   dvt1w=5.0000e+06	 dvt2w=0.0000e+00
+  ua=2.7837e-10      ub=1.8471e-18	 uc=7.9433e-11
+  u0='uo_nfeti50m*(1+dumat)'
+  dsub=5.0000e-01    eta0=0.0000e+00	 etab=0.0000e+00
+  nfactor=9.4830e-01 em=4.1000e+07	 pclm=5.0000e-01
+  drout=5.0000e-01   a0=1.1187e+00	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_nfeti50m
+  ags=1.4493e-01     b0=0.0000e+00	 b1=0.0000e+00
+  pdiblcb=-5.000e-06 pdiblc1=0.0000e+00 pdiblc2=5.0000e-06
+  delta=1.0000e-02   w0=1.0000e-10	 dlc=dlc_nfeti50m
+  dwc=1.9623e-07     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=3.3000e+04	    ute=-1.820e+00
+  kt1=-4.369e-01     kt2=0.0000e+00	 kt1l=0.0000e+00
+  ua1=4.2512e-21     ub1=-8.282e-19	 uc1=-3.437e-17
+  prt=0.0000e+00
+  cgso=cgso_nfeti50m cgdo=1.0000e-12	 cgbo=1.0000e-09
+  cgdl=5.0000e-10    cgsl=3.2240e-10	 ckappa=4.8940e+00
+  cf=0.0000e+00      elm=5.0000e+00
+  xpart=5.0000e-01   clc=1.0000e-15	 cle=6.0000e-01
+  rdsw=1.2400e+02
+  cdsc=0.0000e+00    cdscb=0.0000e+00	 cdscd=0.0000e+00
+  prwb=0.0000e+00    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_nfeti50m   ngate=0.0000e+00	 nlx=4.4250e-07
+  xl=xl_nfeti50m     xw=xw_nfeti50m
+  af=1.4232e+00      kf=5.6012e-26 	 ef=1.0000e+00
+  noia='2.9350e+20*noia_mul'
+  noib='8.8239e+05*noib_mul'
+  noic='-6.290e-11*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=6.8440e+01
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=-3.000e-07
+  wint=1.9623e-07    ldif=0.000e+00	 hdif=8.0000e-07
+  xj=3.0000e-07      js=5.4920e-08	 is=0.0
+  n=1.0000e+00	      tlev=0		 tlevc=1
+  jsw=0.0000e+00     cj=cj_nfeti50m	 cjsw=0.0000e+00
+  fc=0.0000e+00      xti=3.0130e+00
+  mj=3.6520e-01      mjsw=3.6520e-01
+  pb=4.4630e-01      pbsw=4.4630e-01
.ends nfeti50m
*
* HV-jfet 1
*
.subckt	 nfeti50mjfet1 d b s
.param w=1e-6  dtemp=0
jnfeti50mjfet1 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta1_nfeti50m/(1+(3.8667e-03)*pdelt)*(w+(6.9000e-06))/(1+(6.0475e-03)*pdelt+(1.6343e-05)*pdelt**2)'
+ vto='vth1_nfeti50m*(1+(3.8667e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfeti50mjfet1
*
* HV-jfet 2
*
.subckt	 nfeti50mjfet2 d b s
.param w=1e-6  dtemp=0
jnfeti50mjfet2 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta2_nfeti50m/(1+(3.8667e-03)*pdelt)*(w+(6.9000e-06))/(1+(6.0475e-03)*pdelt+(1.6343e-05)*pdelt**2)'
+ vto='vth2_nfeti50m*(1+(3.8667e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfeti50mjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 nfeti50mpnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qnfeti50mpnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='4.800e-06*w*1e-06+4.426e-07*w*l+2.502e-16*exp(-6.209e-13/(l*1e-06))'
+ ise='3.583e-05*w*1e-06+4.667e-06*w*l+6.427e-16*exp(-5.129e-13/(l*1e-06))'
+ ikf='2.254e+06*w*1e-06+1.000e-15*l*1e-06'
+ ikr='5.012e+05*w*1e-06'  isc=1.000e-18
+ bf='7.600e+01*exp(8.750e-12/(w*1e-06))+2.173e+02*exp(-2.927e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+1.793e-11/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+9.977e-10/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.500e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=1.315e+00
+ cje='((3.446e-04*((w+0.5e-06)*(l+0.5e-06))+5.799e-10*(2*((w+0.5e-06)+l+0.5e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+25e-06)*(l+8e-06))+7.569e-10*(2*((l+8e-06)+(w+25e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.4232e+00	 kf=0.000e+00	fc=7.500e-01
.ends nfeti50mpnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 nfeti50mdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dnfeti50mdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='5.003e-15+1.052e-05*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends nfeti50mdcbx

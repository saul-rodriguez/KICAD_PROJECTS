* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfeti20h.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HV MOSFET: NFETI20H
*
*
* *****************************************************************************
.subckt	 nfeti20h d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(1.0242e-07/l+3.8169e-01)'
+ mv_nfeti20h = agauss(0,1,1)
+ mu_nfeti20h = agauss(0,1,1)
+ dvthmat = 'mv_nfeti20h*(3.019e-08/sqrt(l*w*mult))'
+ dumat = 'mu_nfeti20h*(3.465e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.0
+  noideva   = 6.0e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dnfi20hnoi*noi_scale)'
+  noib_mul  = 'exp(dnfi20hnoi*noi_scale/2)'
+  noic_mul  = 'exp(dnfi20hnoi*noi_scale/4)'
*
mnfeti20h  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_nfeti20h/(w+(2.7000e-06)))'  tc1=5.0837e-03  tc2=1.3158e-05  dtemp=dtemp
xj1  d gj d1  nfeti20hjfet1 w=w dtemp=dtemp
xj2  d gj d1  nfeti20hjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_nfeti20h*w)'  dtemp=dtemp
*
xqpnp  sub d b	nfeti20hpnp  area=1 w=w l=l dtemp=dtemp
xdcbx  sub d	nfeti20hdcbx area=1 w=w dtemp=dtemp
*
.model mosinsub nmos level=49 version=3.3  capmod=2
+  mobmod=1  nqsmod=0  noimod=3
+  k1=k1_nfeti20h
+  k2=k2_nfeti20h     k3=6.9544e+00
+  k3b=0.0000e+00     nch=6.6502e+16	 vth0='vth0_nfeti20h+dvthmat'
+  voff=-1.683e-01    dvt0=dvt0_nfeti20h dvt1=1.5954e+00
+  dvt2=2.1827e-03    keta=0.0000e+00
+  pscbe1=4.2400e+08  pscbe2=1.0000e-12
+  alpha0=0.0000e+00  beta0=3.0000e+01
+  dvt0w=0.0000e+00   dvt1w=5.0000e+06	 dvt2w=0.0000e+00
+  ua=8.2736e-10      ub=1.2441e-18	 uc=1.8965e-11
+  u0='uo_nfeti20h*(1+dumat)'
+  dsub=6.7321e-01    eta0=3.0519e-02	 etab=-5.373e-02
+  nfactor=1.0919e+00 em=4.1000e+07	 pclm=2.5000e+00
+  drout=5.0000e-01   a0=9.5044e-01	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_nfeti20h
+  ags=3.8640e-02     b0=0.0000e+00	 b1=0.0000e+00
+  pdiblcb=-5.000e-06 pdiblc1=0.0000e+00 pdiblc2=5.0000e-06
+  delta=1.0000e-03   w0=1.0000e-10	 dlc=dlc_nfeti20h
+  dwc=1.9623e-07     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=3.5597e+04	     ute=-1.630e+00
+  kt1=-9.410e-01     kt2=0.0000e+00	 kt1l=0.0000e+00
+  ua1=4.2512e-21     ub1=-8.282e-19	 uc1=-3.437e-17
+  prt=0.0000e+00
+  cgso=cgso_nfeti20h cgdo=1.0000e-12	 cgbo=1.0000e-09
+  cgdl=2.0000e-10    cgsl=1.0000e-10	 ckappa=1.8520e+00
+  cf=0.0000e+00      elm=5.0000e+00
+  xpart=5.0000e-01   clc=1.0000e-15	 cle=6.0000e-01
+  rdsw=1.2400e+02
+  cdsc=5.0625e-03    cdscb=0.0000e+00	 cdscd=0.0000e+00
+  prwb=8.0185e-01    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_nfeti20h   ngate=0.0000e+00	 nlx=1.1313e-07
+  xl=xl_nfeti20h     xw=xw_nfeti20h
+  af=1.3225e+00      kf=2.3173e-26 	 ef=0.9000e+00
+  noia='1.2625e+21*0.5*noia_mul'
+  noib='9.8388e+05*0.2*noib_mul'
+  noic='-6.979e-11*0.3*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=6.8440e+01
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=-1.000e-07
+  wint=1.9623e-07    ldif=0.000e+00	 hdif=8.0000e-07
+  xj=3.0000e-07      js=5.4920e-08	 is=0.0
+  n=1.0000e+00	      tlev=0		 tlevc=1
+  jsw=0.0000e+00     cj=cj_nfeti20h	 cjsw=0.0000e+00
+  fc=0.0000e+00      xti=3.0130e+00
+  mj=3.6520e-01      mjsw=3.6520e-01
+  pb=4.4630e-01      pbsw=4.4630e-01
.ends nfeti20h
*
* HV-jfet 1
*
.subckt	 nfeti20hjfet1 d b s
.param w=1e-6  dtemp=0
jnfeti20hjfet1 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta1_nfeti20h/(1+(3.1079e-03)*pdelt)*(w+(2.7000e-06))/(1+(5.0837e-03)*pdelt+(1.3158e-05)*pdelt**2)'
+ vto='vth1_nfeti20h*(1+(3.1079e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfeti20hjfet1
*
* HV-jfet 2
*
.subckt	 nfeti20hjfet2 d b s
.param w=1e-6  dtemp=0
jnfeti20hjfet2 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta2_nfeti20h/(1+(3.1079e-03)*pdelt)*(w+(2.7000e-06))/(1+(5.0837e-03)*pdelt+(1.3158e-05)*pdelt**2)'
+ vto='vth2_nfeti20h*(1+(3.1079e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfeti20hjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 nfeti20hpnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qnfeti20hpnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='1.625e-06*w*1e-06+5.183e-07*w*l+1.094e-16*exp(-9.745e-13/(l*1e-06))'
+ ise='1.563e-06*w*1e-06+2.630e-06*w*l+5.310e-17*exp(-1.000e-18/(l*1e-06))'
+ ikf='2.254e+06*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.000e+06*w*1e-06'  isc=1.000e-18
+ bf='2.111e+01*exp(5.623e-12/(w*1e-06))+1.486e+02*exp(-1.519e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+1.793e-11/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+2.208e-09/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.350e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=1.315e+00
+ cje='((2.591e-04*((w+5e-06)*(l+1.2e-06))+5.672e-10*(2*((w+5e-06)+l+1.2e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+9.8e-06)*(l+6.5e-06))+7.569e-10*(2*((l+6.5e-06)+(w+9.8e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.3225e+00	 kf=0.000e+00	fc=7.500e-01
.ends nfeti20hpnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 nfeti20hdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dnfeti20hdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='3.733e-15+1.235e-05*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends nfeti20hdcbx

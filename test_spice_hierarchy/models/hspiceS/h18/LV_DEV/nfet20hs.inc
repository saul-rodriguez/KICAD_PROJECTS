* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfet20hs.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>   HV MOSFET: NFET20HS
*
*
* *****************************************************************************
.subckt	 nfet20hs d g s b
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(6.8170e-07/l+6.4910e-01)'
+ mv_nfet20hs = agauss(0,1,1)
+ mu_nfet20hs = agauss(0,1,1)
+ dvthmat = 'mv_nfet20hs*(2.192e-08/sqrt(l*w*mult))'
+ dumat = 'mu_nfet20hs*(7.071e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
+ rdsw_eff = 'max(0,(8350*(pdelt/298.0)))'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 1.8
+  noideva   = 8.4e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dnf20hsnoi*noi_scale)'
+  noib_mul  = 'exp(dnf20hsnoi*noi_scale/2)'
+  noic_mul  = 'exp(dnf20hsnoi*noi_scale/4)'
*
mnfet20hs  d1 g s1 b  mosinsub w=w l=l nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 dtemp=dtemp
rd d1 d r='(rj_nfet20hs/(w+(5.1000e-09)))'  tc1=2.0806e-03  tc2=1.0000e-10  dtemp=dtemp
rs s s1 r='(rj_nfet20hs/(w+(5.1000e-09)))'  tc1=2.0806e-03  tc2=1.0000e-10  dtemp=dtemp
xj1  d gj1 d1  nfet20hsjfet1 w=w dtemp=dtemp
xj2  d gj1 d1  nfet20hsjfet2 w=w dtemp=dtemp
xj3  s gj2 s1  nfet20hsjfet1 w=w dtemp=dtemp
xj4  s gj2 s1  nfet20hsjfet2 w=w dtemp=dtemp
e1  d1 gj1     value='max(v(d1,s1),0)*gv'
e2  s1 gj2     value='max(v(s1,d1),0)*gv'
cgdx g d   c='(cgdx1_nfet20hs*w)'  dtemp=dtemp
cgsx g s   c='(cgdx1_nfet20hs*w)'  dtemp=dtemp
*
xdw1 b d1  nfet20hsnwd area='(w+2.9e-06)*(3.5e-06)' perimeter='2*((w+2.9e-06)+3.5e-06)' dtemp=dtemp
xdw2 b s1  nfet20hsnwd area='(w+2.9e-06)*(3.5e-06)' perimeter='2*((w+2.9e-06)+3.5e-06)' dtemp=dtemp
*
.model mosinsub nmos level=49 version=3.3  capmod=2
+  mobmod=1  nqsmod=0  noimod=3
+  k1=k1_nfet20hs
+  k2=k2_nfet20hs     k3=6.7740e+00
+  k3b=-6.910e+00     nch=8.5940e+16	 vth0='vth0_nfet20hs+dvthmat'
+  voff=-1.500e-01    dvt0=dvt0_nfet20hs dvt1=5.7550e-01
+  dvt2=-1.860e-17    keta=0.0000e+00
+  pscbe1=1.0000e+09  pscbe2=1.0000e-09
+  alpha0=0.0000e+00  beta0=1.6000e+02
+  dvt0w=0.0000e+00   dvt1w=1.4800e+05	 dvt2w=-3.000e-03
+  ua=1.4080e-10      ub=1.0000e-18	 uc=-3.737e-11
+  u0='uo_nfet20hs*(1+dumat)'
+  dsub=1.0000e+00    eta0=1.9440e-05	 etab=-5.499e-05
+  nfactor=1.3210e+00 em=4.1000e+07	 pclm=1.9320e+00
+  drout=4.9650e-01   a0=9.0640e-01	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_nfet20hs
+  ags=4.1330e-02     b0=5.6920e-07	 b1=1.0000e-07
+  pdiblcb=-1.000e-03 pdiblc1=1.2270e-01 pdiblc2=1.0000e-05
+  delta=1.0000e-03   w0=2.5000e-06	 dlc=dlc_nfet20hs
+  dwc=1.5650e-07     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=1.0000e+02	     ute=-1.896e+00
+  kt1=-9.828e-01     kt2=0.0000e+00	 kt1l=0.0000e+00
+  ua1=0.0000e+00     ub1=0.0000e+00	 uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_nfet20hs cgdo=1.0000e-12    cgbo=1.2000e-09
+  cgdl=1.0000e-10    cgsl=1.0000e-10	 ckappa=3.0000e+00
+  cf=0.0000e+00      elm=5.0000e+00
+  xpart=5.0000e-01   clc=1.0000e-15	 cle=6.0000e-01
+  rdsw=rdsw_eff
+  cdsc=5.8300e-16    cdscb=-7.385e-17	 cdscd=3.4650e-11
+  prwb=0.0000e+00    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_nfet20hs   ngate=0.0000e+00	 nlx=1.7440e-07
+  xl=xl_nfet20hs     xw=xw_nfet20hs
+  af=1.17780+00      kf=5.0550e-27 	 ef=0.9000e+00
+  noia='1.3362e+21*0.4*noia_mul'
+  noib='8.9755e+05*0.3*noib_mul'
+  noic='-5.963e-11*0.2*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=1.4000e+02
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=-3.374e-07
+  wint=1.5650e-07    ldif=0.000e+00	 hdif=0.0000e+00
+  xj=3.0000e-07      js=1.1470e-06	 is=0.0
+  n=1.0400e+00	      tlev=0		 tlevc=1
+  jsw=5.1480e-12     cj=cj_nfet20hs	 cjsw=cjsw_nfet20hs
+  fc=0.0000e+00      fcsw=0.0000e+00    xti=9.0460e-01
+  pb=6.5700e-01      pbsw=3.2370e-01
.ends nfet20hs
*
* HV-jfet 1
*
.subckt	 nfet20hsjfet1 d b s
.param w=1e-6  dtemp=0
jnfet20hsjfet1 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta1_nfet20hs/(1+(3.4198e-03)*pdelt)*(w+(5.1000e-09))/(1+(2.0806e-03)*pdelt+(1.0000e-10)*pdelt**2)'
+ vto='vth1_nfet20hs*(1+(3.4198e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfet20hsjfet1
*
* HV-jfet 2
*
.subckt	 nfet20hsjfet2 d b s
.param w=1e-6  dtemp=0
jnfet20hsjfet2 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta2_nfet20hs/(1+(3.4198e-03)*pdelt)*(w+(5.1000e-09))/(1+(2.0806e-03)*pdelt+(1.0000e-10)*pdelt**2)'
+ vto='vth2_nfet20hs*(1+(3.4198e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfet20hsjfet2
*
* Parasitic DIODE
*
.subckt	 nfet20hsnwd a c
.param area=1.0e-12  perimeter=1e-06  dtemp=0
dnfet20hsnwd  a c  diodeinsub area=area pj=perimeter  dtemp=dtemp
.model diodeinsub d level=1
+ js=1.147e-06   jsw=5.148e-12
+ n=1.040e+00
+ cj=1.125e-04	 cjsw=4.025e-10
+ m=4.579e-01	 mjsw=9.554e-02
+ vj=6.570e-01	 php=3.237e-01
+ af=1.000e+00	 kf=0.000e+00
+ xti=9.046e-01	 tt=0.000e+00
+ expli=1.000e+12
+ tref=2.500e+01
.ends nfet20hsnwd

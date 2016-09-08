* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfet50hs.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HV MOSFET: NFET50HS
*
*
* *****************************************************************************
.subckt	 nfet50hs d g s b
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(2.2160e-06/l+1.1390e+00)'
+ mv_nfet50hs = agauss(0,1,1)
+ mu_nfet50hs = agauss(0,1,1)
+ dvthmat = 'mv_nfet50hs*(2.326e-08/sqrt(l*w*mult))'
+ dumat = 'mu_nfet50hs*(5.940e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
+ rdsw_eff = 'max(0,(8350*(pdelt/298.0)))'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.0
+  noideva   = 1.56e-10
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dnf50hsnoi*noi_scale)'
+  noib_mul  = 'exp(dnf50hsnoi*noi_scale/2)'
+  noic_mul  = 'exp(dnf50hsnoi*noi_scale/4)'
*
mnfet50hs  d1 g s1 b  mosinsub w=w l=l nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 dtemp=dtemp
rd d1 d r='(rj_nfet50hs/(w+(1.0830e-06)))'  tc1=4.4311e-03  tc2=2.9831e-06  dtemp=dtemp
rs s s1 r='(rj_nfet50hs/(w+(1.0830e-06)))'  tc1=4.4311e-03  tc2=2.9831e-06  dtemp=dtemp
xj1  d gj1 d1  nfet50hsjfet1 w=w dtemp=dtemp
xj2  d gj1 d1  nfet50hsjfet2 w=w dtemp=dtemp
xj3  s gj2 s1  nfet50hsjfet1 w=w dtemp=dtemp
xj4  s gj2 s1  nfet50hsjfet2 w=w dtemp=dtemp
e1  d1 gj1     value='max(v(d1,s1),0)*gv'
e2  s1 gj2     value='max(v(s1,d1),0)*gv'
cgdx g d   c='(cgdx1_nfet50hs*w)'  dtemp=dtemp
cgsx g s   c='(cgdx1_nfet50hs*w)'  dtemp=dtemp
*
xdw1 b d1  nfet50hsnwd area='(w+10.3e-06)*(10.3e-06)' perimeter='2*((w+10.3e-06)+10.3e-06)' dtemp=dtemp
xdw2 b s1  nfet50hsnwd area='(w+10.3e-06)*(10.3e-06)' perimeter='2*((w+10.3e-06)+10.3e-06)' dtemp=dtemp
*
.model mosinsub nmos level=49 version=3.3  capmod=2
+  mobmod=1  nqsmod=0  noimod=3
+  k1=k1_nfet50hs
+  k2=k2_nfet50hs     k3=9.0140e+00
+  k3b=-2.960e+00     nch=8.7120e+16	 vth0='vth0_nfet50hs+dvthmat'
+  voff=-1.500e-01    dvt0=dvt0_nfet50hs dvt1=5.3490e-01
+  dvt2=-1.534e-18    keta=0.0000e+00
+  pscbe1=1.0000e+09  pscbe2=1.0000e-09
+  alpha0=0.0000e+00  beta0=1.6000e+02
+  dvt0w=0.0000e+00   dvt1w=1.4800e+05	 dvt2w=-3.000e-03
+  ua=4.3310e-10      ub=1.0000e-18	 uc=-1.000e-11
+  u0='uo_nfet50hs*(1+dumat)'
+  dsub=1.0000e+00    eta0=1.8660e-05	 etab=-5.279e-05
+  nfactor=1.1730e+00 em=4.1000e+07	 pclm=2.7080e+00
+  drout=4.9650e-01   a0=7.5600e-01	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_nfet50hs
+  ags=2.8780e-02     b0=1.2150e-06	 b1=1.0000e-07
+  pdiblcb=0.0000e+00 pdiblc1=2.5750e-01 pdiblc2=1.0000e-05
+  delta=1.0000e-03   w0=2.5000e-06	 dlc=dlc_nfet50hs
+  dwc=-1.893e-07     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=3.8338e+04	     ute=-1.988e+00
+  kt1=-1.207e+00     kt2=0.0000e+00	 kt1l=0.0000e+00
+  ua1=0.0000e+00     ub1=0.0000e+00	 uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_nfet50hs cgdo=1.0000e-12    cgbo=1.0000e-09
+  cgdl=3.0000e-10    cgsl=1.0000e-10	 ckappa=2.9540e+00
+  cf=0.0000e+00      elm=5.0000e+00
+  xpart=1.0000e+00   clc=1.0000e-15	 cle=6.0000e-01
+  rdsw=rdsw_eff
+  cdsc=5.8300e-16    cdscb=-7.385e-17	 cdscd=3.3260e-11
+  prwb=0.0000e+00    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_nfet50hs   ngate=0.0000e+00	 nlx=1.6050e-07
+  xl=xl_nfet50hs     xw=xw_nfet50hs
+  af=1.1393e+00      kf=2.9723e-27 	 ef=0.9000e+00
+  noia='1.3717e+21*0.4*noia_mul'
+  noib='7.0543e+05*0.5*noib_mul'
+  noic='-4.071e-11*0.5*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=1.4000e+02
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=-4.762e-07
+  wint=-1.893e-07    ldif=0.000e+00	 hdif=0.0000e+00
+  xj=3.0000e-07      js=1.1470e-06	 is=0.0
+  n=1.0400e+00	      tlev=0		 tlevc=1
+  jsw=5.1480e-12     cj=cj_nfet50hs	 cjsw=cjsw_nfet50hs
+  fc=0.0000e+00      fcsw=0.0000e+00    xti=9.0460e-01
+  pb=6.5700e-01      pbsw=3.2370e-01
.ends nfet50hs
*
* HV-jfet 1
*
.subckt	 nfet50hsjfet1 d b s
.param w=1e-6  dtemp=0
jnfet50hsjfet1 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta1_nfet50hs/(1+(4.2751e-03)*pdelt)*(w+(1.0830e-06))/(1+(4.4311e-03)*pdelt+(2.9831e-06)*pdelt**2)'
+ vto='vth1_nfet50hs*(1+(4.2751e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfet50hsjfet1
*
* HV-jfet 2
*
.subckt	 nfet50hsjfet2 d b s
.param w=1e-6  dtemp=0
jnfet50hsjfet2 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta2_nfet50hs/(1+(4.2751e-03)*pdelt)*(w+(1.0830e-06))/(1+(4.4311e-03)*pdelt+(2.9831e-06)*pdelt**2)'
+ vto='vth2_nfet50hs*(1+(4.2751e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfet50hsjfet2
*
* Parasitic DIODE
*
.subckt	 nfet50hsnwd a c
.param area=1.0e-12  perimeter=1e-06  dtemp=0
dnfet50hsnwd  a c  diodeinsub area=area pj=perimeter  dtemp=dtemp
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
.ends nfet50hsnwd

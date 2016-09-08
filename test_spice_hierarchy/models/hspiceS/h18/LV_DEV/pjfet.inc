* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pjfet.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *********************************************************************
*
*>  HV PJFET
*
*
* *********************************************************************
.subckt	 pjfet d b s sub
+        w=10.0e-6 l=7.6e-6 dtemp=0
.param
+ pdelt = 'temper+dtemp-25.0'
 
jpjfet  d b s	 jfetinsub dtemp=dtemp
xdsub   sub b    pjfetdnsx area='(w+7.2e-06)*19.9e-06' perimeter='2*((w+19.9e-06)+7.6e-06)' dtemp=dtemp

.model jfetinsub  pjf level=1
+ beta='(beta_pjfet*(w-4.464e-07)/l/(1+(3.5240e-03+(1.1410e-05*pdelt))*pdelt))'
+ vto='(-vta_pjfet-2.110e-03*pdelt)'
+ lambda='(lambda_pjfet/l)'
+ rs=1.0000e+00	 rd=1.0000e+00
+ pb=9.7060e-01	 mj=5.3580e-01
+ n=1.0000e+00
+ is='(6.2050e-07*w*l+2.9660e-12*(w+l))'
+ xti=5.4630e-01
+ cgs='(cgsa_pjfet*w*l+cgsp_pjfet*(w+l))'
+ cgd='(cgda_pjfet*w*l+cgdp_pjfet*(w+l))'
.ends pjfet
*
* Parasitic DIODE
*
.subckt pjfetdnsx a c
.param area=1.0e-12 perimeter=1e-12 dtemp=0
pjfetdnsx a c diodeinsub area=area pj=perimeter dtemp=dtemp
.model diodeinsub d level=1
+    js=6.205e-07    jsw=2.966e-12
+     n=1.040e+00
+    cj=1.296e-04   cjsw=5.672e-10
+     m=3.127e-01   mjsw=3.124e-01
+    vj=4.561e-01    php=6.040e-01
+    af=1.000e+00     kf=0.000e+00
+   xti=9.039e-01     tt=0.000e+00
+ expli=1.000e+12
+  tref=2.500e+01
.ends pjfetdnsx

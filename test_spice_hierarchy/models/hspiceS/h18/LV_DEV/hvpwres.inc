* Path, Component, Release: cmhv7sf/rel/HSPICE/models/hvpwres.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *********************************************************************
*
*>  HV PWell Resistor
*
*
* *********************************************************************
.subckt	 hvpwres d b s
+        w=4.0e-6 l=100.0e-6 dtemp=0
.param
+ mmw_hvpwr = agauss(0,1,1)
+ dmat  = 'mmw_hvpwr*(1.77e-08/sqrt(l*w))'
+ pdelt = 'temper+dtemp-25.0'
 
jhvpwres  d b s	 jfetinsub dtemp=dtemp

.model jfetinsub  pjf level=1
+ beta='(beta_hvpwr*(1+dmat)*(w-(wd_hvpwr))/(l-(-2.876e-06))/(1+(2.3350e-03+(5.3800e-06*pdelt))*pdelt))'
+ vto='(-420.3+(8.066e-04/(w-(wd_hvpwr))))'
+ lambda='(-1.195e-07/(l-(-2.876e-06)))'
+ rs=1.0000e+00	 rd=1.0000e+00
+ pb=6.5700e-01	 mj=4.5790e-01
+ n=1.0400e+00
+ is='(5.7350e-07*w*l+5.1480e-12*(w+l))'
+ xti=9.0460e-01
+ cgs='(cgsa_hvpwr*w*l+cgsp_hvpwr*(w+l))'
+ cgd='(cgda_hvpwr*w*l+cgdp_hvpwr*(w+l))'
.ends hvpwres

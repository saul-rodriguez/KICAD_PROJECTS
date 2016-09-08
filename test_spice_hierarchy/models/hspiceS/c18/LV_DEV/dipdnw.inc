* Path, Component, Release: cmos7base/rel/HSPICE/models/dipdnw.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  dipdnw    P+ Nwell Diode - voltage reference diode
*
***********************************************************************
*                               
*                         anode  o
*                                |
*                                |
*                               ----    
*                      P+ Nwell \  /      
*                         Diode  \/          
*                               ----    
*                                |      
*                                |      
*                                |            
*                            SX  o   
*                                    
***********************************************************************
*
*  DIMENSIONS: W = Design width  of RX
*              L = Design length of RX
*
*  SYNTAX:     Specify both width and length and number of fingers:
*              xxx  a  sx dipdnw (w=2u  l=5u  nf=1)
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*	 	par  --> Explicit device multiplicity.
*
*
*  NOTES:
*
*  1. Model supports only rectangular diode with cathode connected to
*     ground (SX).
*
*                                
***********************************************************************
*
.subckt dipdnw  a  sx  w=1.6u  l=10u  nf=1  par=1  dtemp=0 

.param
* Check for minimum/maximum width, calculate effective width
+ aw = 'max(w,0.8u)'
+ anodew = 'min(aw,2u) + delrx'

* Check for minimum length, calculate effective length
+ anodel = 'max(l,2u) + delrx'

* Calculate area & perimeter for capacitance
+ totp  = '2 * nf * (anodel + anodew)'
+ tota = 'nf * anodel * anodew'

* Calculate the resistance, a function of length of cathode RX.
*   dirs is the vertical resistance through the diode 
+ dirs = '50p/tota'
*rnw is the resistance through the nw
+ rnw = '(nwrs*anodew)/(12*anodel*nf)+(nwrs*0.34u)/(2*anodel*nf)+(nwrs*0.6u)/(6*anodel*nf)'
*rvnw is the vertical resistance through the nw (nw contact)
+ rvnw = 'nrnw/(anodel*0.6u*(nf+1))'
+ rstot = 'dirs + (rnw + rvnw)/2'

* Mis-match Calculation
+ dima = 3.0
+ diml = 0.0
+ dimw = 0.5
+ dioma   = 'dima * dima / (anodew * anodel * nf * 1e12)'
+ dioml   = 'diml * diml / (anodel * anodel * nf * nf * 1e12)'
+ diomw   = 'dimw * dimw / (anodew * anodew * 1e12)'
+ dio3sig = '0.01 * sqrt(dioma + dioml + diomw)'
+ diomm   = 'dio3sig * 0.7071 / sqrt(par)'
+ mmdio  = agauss(0,1,3)
+ mmatd  = '1 + (diomm * mmdio)'

*  Diode network
dpri  a  sx   didio  area=tota  pj=totp  dtemp=dtemp

* P+ to NW Diode
* rs is multiplied by area as rstot is acutal resistance and rs 
*   gets divided by area of device
*
.model didio d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+    rs = 'rstot*tota'
+     n = 1.006
+    js = 'js_p*(1 + tdeldi)*mmatd'
+   jsw = 'jsw_p*(1 + tdeldi)*mmatd'
+    cj = 'cj_p'
+   cta = 'cta_p'
+    pb = 'pb_p'
+   tpb = 'pta_p'
+    mj = 'mj_p'
+   cjp = 'cjsw_p'
+   ctp = 'ctp_p'
+   php = 'pbsw_p'
+  tphp = 'ptp_p'
+  mjsw = 'mjsw_p'
+    vb = '10.5'

.ends dipdnw

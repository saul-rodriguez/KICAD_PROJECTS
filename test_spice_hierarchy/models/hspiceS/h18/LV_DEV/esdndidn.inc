* Path, Component, Release: cmhv7sf/rel/HSPICE/models/esdndidn.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
*> esdndidn    ESD diode - N+ isolated Pwell(over DN)
*
***********************************************************************
*
*                                   dn o
*                                      |
*                                      |
*                                    ----
*                                     /\
*                           DP/DN    /  \
*                           Diode    ----
*                                      |
*                                      |
*                           (Anode) pw o
*                                      |
*                                      / 
*             (Internal PCell   rser   \
*              resistance)             /
*                                      |
*                                   aa o
*                                      |        
*                                      +--------------+
*                                      |              |
*                                     ----     gleak / \
*                            N+ Pwell \  /          /   \
*                               Diode  \/           \   /
*                                     ----           \ /
*                                      |              |
*                                      +--------------+
*                                      |         
*                                   nd o         
*                                  (Cathode)
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter and number of cathodes
*              xxx (pw nd dn) esdndidn area=1p  perim=4u ncath=1 dtemp=0
*
*  OPTIONAL:   dtemp -->  Device temperature difference with respect to
*                         the simulated circuit temperature (deg C).
*              area  -->  Total area of anode RX shape
*             perim  -->  Total perimeter of anode RX shape
*             ncath  -->  Number of cathode fingers
*             rwire  -->  Wiring resistance used for pre-extraction simulation
*              acsp  -->  Anode to cathode spacing
*             vdnsx  -->  DN/SX max voltage option (50V or 120V)
*
*  NOTES:
*
*  1. Node order must be as specified.
*
*                                
***********************************************************************
.subckt esdndidn  (pw nd dn)  area=1p perim=4u ncath=1 dtemp=0 rwire=0.1m acsp=0.36u vdnsx=50
*
.param
*  We start by calculating the length of cathode rx
+ c = 0
+ alpha = 'area/ncath + 2*c*c'
+ beta  = '(2-sqrt(2))*c+perim/(4*ncath)'
+ lcathn = 'beta + sqrt(abs(beta*beta - alpha))'
+ wcathn = 'alpha/lcathn'
+ wcath = 'wcathn + delrx'
+ lcath = 'lcathn + delrx'
*  We then determine the total area and perimeter of cathode region
+ acath = '(lcath*wcath - 2*c*c)*ncath'
+ pcath = '(lcath + wcath + 2*sqrt(2)*c - 4*c)*ncath*2'
*
*  We then determine the total area and perimeter of isoPW region
* Calculate area & perimeter for parasitic diode
+ wanodn = 0.72u
+ lpw = 'lcathn + 2*(acsp + wanodn + 2.22u) - delnw'
+ wpw = 'ncath*(2*acsp + wcathn) + (ncath+1)*wanodn + 2.22u - delnw'
+ totapw = 'lpw * wpw'
+ totppw = '2 * (lpw + wpw)'
*
* Calculate the internal resistance
*   acsp is the anode to cathode separation
+ pwrs = 315
+ prpw = 1.0n
+ acspx = 'acsp-delrx'
*   wanodn is the anode width
+ wanod = 'wanodn+delrx'
*   rc2 is the resistance through the nw
+ rc2 = '(pwrs*acspx)/(2*lcath*ncath)+(pwrs*wcath)/(12*lcath*ncath)+(pwrs*wanod)/(6*lcath*ncath)'
*   rc3 is the resistance through the vertical pw
+ rc3 = 'prpw/(lcath*wanod*(ncath+1))'
*
* leakage current
+ lk10 = 4p
+ lk1a = 720.4u
+ lk1p = 1.567n
+ lkt  = 13
+ lk3  = 0
+ lk1  = '(lk10 + lk1a*area + lk1p*perim)*pwr((temper+273)/298,lkt)'
*
* ESD Parameters
+ esdvsat_1n = 7
+ esdnsat_1n = 10.3
+ esdvsat_mm = 1.0
+ esdnsat_mm = 15.0
+ esdvsat_hb = 1.19
+ esdnsat_hb = 12.0
+ rwire_int = '(esd_event==0)*(0.014u/(lcath*ncath)) + (esd_event==1)*(13.3u/(lcath*ncath)) + (esd_event==2)*(4u/(lcath*ncath)) + (esd_event==3)*(18u/(lcath*ncath))'
+ rsp = 100p
+ p_rs = 11p
+ rtot = '(esd_event==0)*(rc2+rc3) + (esd_event>0)*1e-4'
+ esdvsat   = '1000*(esd_event==0) + esdvsat_hb*(esd_event==1) + esdvsat_mm*(esd_event==2) + esdvsat_1n*(esd_event==3)'
+ esdnsat   = '1*(esd_event==0)	   + esdnsat_hb*(esd_event==1) + esdnsat_mm*(esd_event==2) + esdnsat_1n*(esd_event==3)'
+ It2       = '1000*(esd_event==0) + 17.5e-3*(esd_event==1)    + 16.9e-3*(esd_event==2)    + 42e-3*(esd_event==3)'
+ It_valid  = '1000*(esd_event==0) + 5*(esd_event==1)          + 5*(esd_event==2)          + 15*(esd_event==3)'

* Subcircuit
dpri   aa   nd  dionpw  area=acath  pj=pcath dtemp=dtemp
gleak  aa   nd  cur='lk1*pwr(v(aa,nd),1)'
rser   pw  aa3  r=rtot
xpdn   pw   dn  diodepwdn  area=totapw perimeter=totppw

.if (esd_event > 0)
 grtlp       aa2  aa     cur='v(aa2,aa)/((rwire + rwire_int) + (((rsp+p_rs)*0.5-(rsp-p_rs)*0.5*tanh(100*v(aa2,aa))) / (acath))*pwr((1+pwr(abs(v(aa2,aa))/esdvsat,esdnsat)),1.0/esdnsat))'
 xesdmonitor aa3  aa2 	 It2_monitor keyp=pcath It2=It2 esd_exit=esd_exit It_valid=It_valid
.else
r11 aa3 aa  r=1e-4
.endif

.model dionpw d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+     n = n_ni
+    rs = 0p
+    js = '(js_ni/acath)*20p'
+   jsw = jsw_ni
+    cj = cj_ni
+    pb = pb_ni
+    mj = mj_ni
+   cjp = cjsw_ni
+   php = pbsw_ni
+  mjsw = mjsw_ni
+   cta = cta_ni
+   tpb = pta_ni
+   ctp = ctp_ni
+  tphp = ptp_ni
+    vb = 13.5

.ends esdndidn

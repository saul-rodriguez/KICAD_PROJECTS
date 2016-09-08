* Path, Component, Release: cmhv7sf/rel/HSPICE/models/esdvpnpnw.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
*>  esdvpnpnw    ESD diode - P+ Nwell
*
***********************************************************************
*                                   (Anode)
*                                   pd o
*                                      |
*                                      o----------------+
*                                      |                |
*                                     ----      gleak  /\
*                            P+ Nwell \  /            /  \
*                               Diode  \/             \  /
*                                     ----             \/
*                                      |                |
*                                   ab o----------------+
*                                      |            
*                                      |            
*                                    -----          
*                            VSENS=0V ---           
*                                    -----          
*                                     ---           
*                                      |            
*             nw       rserc        nwa|            
*   (Cathode) o--------\/\/\-----------o--------------+ 
*                     -     +          |              |
*                                      |              |
*                                      |          pos |
*                                     ----        fsx ^  
*                                NW/SX /\            /  \
*                                Diode/  \           \  /
*                                     ----        neg \/
*                                      |              |
*                                      |              |
*             sx      + Rsx -        ac|              |
* (Substrate) o---------/\/\-----------o--------------+
*
*
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter and number of anodes
*              xxx (pd nw sx) esdvpnpnw area=1p  perim=4u nanod=1 rsx=50 dtemp=0
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*              area  -->  Total area of anode RX shape
*
*             perim  -->  Total perimeter of anode RX shape
*
*             nanod  -->  Number of anode fingers
*
*               rsx  -->  Substrate resistance, dependent upon layout
*                         and location of substrate contact relative to device
*
*             rwire  -->  Wiring resistance used for pre-extraction simulation
*
*              acsp  -->  Anode to cathode spacing
*
*  NOTES:
*
*  1. Node order must be as specified.
*
*                                
***********************************************************************
.subckt esdvpnpnw  (pd nw sx)  area=1p perim=4u nanod=1 rsx=50 dtemp=0 rwire=0.1m acsp=0.36u
*
.param
*  We start by calculating the length of anode rx
+ c = 0.2u
+ alpha = 'area/nanod + 2*c*c'
+ beta  = '(2-sqrt(2))*c+perim/(4*nanod)'
+ lanodn = 'beta + sqrt(abs(beta*beta - alpha))'
+ wanodn = 'alpha/lanodn'
+ wanod = 'wanodn + delrx'
+ lanod = 'lanodn + delrx'
*  We then determine the total area and perimeter of anode region
+ aanod = '(lanod*wanod - 2*c*c)*nanod'
+ panod = '(lanod + wanod + 2*sqrt(2)*c - 4*c)*nanod*2'
*
* Calculate area & perimeter for parasitic diode
+ wcathn = 0.72u
+ lnw = 'lanodn + 2*acsp + delnw'
+ wnw = 'nanod*(2*acsp + wanodn) + (nanod+1)*wcathn + delnw'
+ totanw = 'lnw * wnw'
+ totpnw = '2 * (lnw + wnw)'
*
* Calculate the internal resistance
* acsp is the anode to cathode separation
+ acspx = 'acsp-delrx'
*wcath is the cathode width
+ wcath = 'wcathn+delrx'
*rc2 is the resistance through the nw
+ rc2 = '(nwrs*acspx)/(2*lanod*nanod)+(nwrs*wanod)/(12*lanod*nanod)+(nwrs*wcath)/(6*lanod*nanod)'
*rc3 is the resistance through the vertical nw
+ rc3 = 'nrnw/(lanod*wcath*(nanod+1))'
+ rtot = '(esd_event==0)*(rc2+rc3)+(esd_event>0)*1e-4'
* 
* Set the gain on the current flowing through the cathode
+ cgain = 0.53
*
* leakage current
+ tgs = 13
+ gleak = '1.3e-1*pwr((temper+273)/298,tgs)'
*
* ESD paraameters
+ p_rs_esdpnb_wf = 10p
+ rsp = 10u
+ esdvsat   = '1000*(esd_event==0) + 683e-3*(esd_event==1)   + 850e-3*(esd_event==2) + 17.19*(esd_event==3)'
+ esdnsat   = '1*(esd_event==0)    + 48.44*(esd_event==1)    +  10*(esd_event==2)    + 3.325*(esd_event==3)'
+ ro        = '1e-6*(esd_event==0) + 37.29e-6*(esd_event==1) + 30e-6*(esd_event==2)  + 36.87e-6*(esd_event==3)'
+ rwire_int = '(ro/perim)+10m' 
+ It2       = '1000*(esd_event==0) + 15e-3*(esd_event==1)    + 20e-3*(esd_event==2)  + 50e-3*(esd_event==3)'
+ It_valid  = '1000*(esd_event==0) + 5.0*(esd_event==1)      + 5.0*(esd_event==2)    + 20*(esd_event==3)'

* Subcircuit
dpri  pdi1 ab  diopnws  area=aanod  pj=panod  dtemp=dtemp
vsens  ab nwa  0v
rserc  nwa nw  r=rtot
Fsx    nwa ac  vsens    cgain
dnwsx  ac nwa  ddnwsx   area=totanw  pj=totpnw  dtemp=dtemp
rrsx   sx ac   r=rsx
gleakp ab pdi1 cur='v(ab,pdi)*gleak*aanod'

.if (esd_event > 0)
grtlp pdi pd  cur='v(pdi,pd)/((rwire+rwire_int) + (((rsp+p_rs_esdpnb_wf)*0.5-(rsp-p_rs_esdpnb_wf)*0.5*tanh(100*v(pdi,pd))) / (panod))*pwr((1+pwr(abs(v(pdi,pd))/esdvsat,esdnsat)),1.0/esdnsat))'
.else
r11   pd  pdi r=1
.endif
xesdmonitor pdi pdi1 It2_monitor keyp=panod It2=It2 It_valid=It_valid esd_exit=esd_exit

.model diopnws d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+     n = n_p
+    js = js_p
+   jsw = jsw_p
+    cj = cj_p
+    pb = pb_p
+    mj = mj_p
+   cjp = cjsw_p
+   php = pbsw_p
+  mjsw = mjsw_p
+   cta = cta_p
+   tpb = pta_p
+   ctp = ctp_p
+  tphp = ptp_p
+    vb = 9.5
+    ik = 200e6

.model ddnwsx d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.15
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+     n = n_nw
+    js = js_nw
+   jsw = jsw_nw
+    cj = cj_nw
+    pb = pb_nw
+    mj = mj_nw
+   cjp = cjsw_nw
+   php = pbsw_nw
+  mjsw = mjsw_nw
+   cta = cta_nw
+   tpb = pta_nw
+   ctp = ctp_nw
+  tphp = ptp_nw
+    vb = 10.0

.ends esdvpnpnw

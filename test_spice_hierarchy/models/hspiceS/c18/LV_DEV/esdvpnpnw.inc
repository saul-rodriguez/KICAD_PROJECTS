* Path, Component, Release: cmos7base/rel/HSPICE/models/esdvpnpnw.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  esdvpnpnw    ESD diode - P+ Nwell
*
***********************************************************************
*                                   (Anode)
*                                   pd o
*                                      |
*                                     / \
*                                     \ /  xesdmonitor 
*                                      | 
*                                     / \  
*                                     \ /  grtlp
*                                      |
*                                    + /
*             (Internal PCell   rsera  \
*              wiring resistance)    - /
*                                      |
*                                   aa o
*                                      |
*                                     ----    
*                            P+ Nwell \  /      
*                               Diode  \/          
*                                     ----    
*                                      |            
*                                   ab o            
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
*                                      |            + |
*                                     ----        Fsx /\
*                                NW/SX /\            /  \
*                                Diode/  \           \  /
*                                     ----          - \/
*                                      |              |
*                                      |              |
*             sx      + Rsx -        ac|              |
* (Substrate) o---------/\/\-----------o--------------+
*
*
*
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter and number of anodes
*              xxx (pd nw sx) esdvpnpnw area=1p  perim=4u nanod=1 rsx=50 dtemp=0
*
*  OPTIONAL:   dtemp -->  Device temperature difference with respect to
*                         the simulated circuit temperature (deg C).
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
*              rwire -->  Wiring resistance (use for pre-layout
*                         simulations)  [ohm]
*
*  NOTES:
*
*  1. Node order must be as specified.
*                                
***********************************************************************
*
.subckt esdvpnpnw  (pd nw sx)  area=1p  perim=4u  nanod=1  rsx=50  dtemp=0 rwire=1e-4 
*
* We start by calculating the length of anode rx
+ c = 0.2u
+ alpha = 'area/nanod +2*c*c'
+ beta  = '(2-sqrt(2))*c+perim/(4*nanod)'
+ lanodn = 'beta + sqrt(abs(beta*beta - alpha))'
+ wanodn = 'alpha/lanodn'
+ wanod = 'wanodn + delrx'
+ lanod = 'lanodn + delrx'
* We then determine the total area and perimeter of anode region
+ aanod = '(lanod*wanod - 2*c*c)*nanod'
+ panod = '(lanod + wanod + 2*sqrt(2)*c - 4*c)*nanod*2'
*
* Calculate area & perimeter for parasitic diode
+ lnw = 'lanod + 3.44u + delnw'
+ wnw = '(nanod-1)*2.52u + 0.72u + 3.8u + delnw'
+ totanw = 'lnw * wnw' 
+ totpnw = '2 * (lnw + wnw)'
*
* Calculate the internal resistance, starting with the wiring
* ncath is the # of cathodes
+ ncath = 'nanod+1'
* metwid is the M1 wire width
+ metwid = 2.88u
* ametl and cmetl are the anode and cathode metal wire lengths
+ ametl = '2.88u*nanod+0.72u'
+ cmetl = '2.88u*ncath-0.78u'
* nawires is the # of anode wires
* ncwires is the # of cathode wires
+ nawires = 'max(int((lanodn+3.14u)/7.44u + 0.01),1)'
+ ncwires = 'max(nawires-1,1)'
* rma is the resistance of the metal wiring to the cathode
+ rma = '(m1rs*ametl)/(metwid*nawires)'
* rmc is the resistance of the wires leaving the cathode
+ rmc = '(m1rs*cmetl)/(metwid*ncwires)'
*
* acsp is the anode to cathode separation
+ acsp = 0.78u
+ acspx = 'acsp-delrx'
* wcathn is the cathode width
+ wcathn = 0.60u
+ wcath = 'wcathn+delrx'
* rc2 is the resistance through the nw
+ rc2 = '(nwrs*acspx)/(2*lanod*nanod)+(nwrs*wanod)/(12*lanod*nanod)+(nwrs*wcath)/(6*lanod*nanod)'
* rc3 is the resistance through the vertical nw
+ rc3 = 'nrnw/(lanod*wcath*ncath)'
* rtota is the total series resistance near the anode
+ rtota = rma
* rtotc is the total series resistance near the cathode
+ rtotc = 'rc2+rc3+rmc'
* 
* Set the gain on the current flowing through the cathode
+ cgain = 0.53
*
* esd parameters
+ esdvsat = '1000*(esd_event==0)+ 121.7m*(esd_event==1)+ 6.936*(esd_event==2)+ 10*(esd_event==3)'
+ esdnsat =    '1*(esd_event==0)+ 1.33*(esd_event==1)+ 3.0*(esd_event==2)+   10*(esd_event==3)'
+ rsp =2p
+ p_rs=1p
+ rdcc=10p
+ rwint_esd= '1e-4*(esd_event==0)+(102m)*(esd_event==1)+(10.9p/aanod)*(esd_event==2)+(13.85p/aanod)*(esd_event==3)'
+ voff_esd='0*(esd_event==0)+180m*(esd_event==1)+157.2m*(esd_event==2)+133.3m*(esd_event==3)'
+ rtota ='(rma+(100p/aanod))*(esd_event==0)+rdcc/aanod*(esd_event==1)+rdcc/aanod*(esd_event==2)+rdcc/aanod*(esd_event==3)'
+ rtotc ='(rc2+rc3+rmc)*(esd_event==0)+1e-4*(esd_event==1)+1e-4*(esd_event==2)+1e-4*(esd_event==3)'
+ rwire_int='(esd_extr==1)?1e-4:rwint_esd'
+ It2_HBM=29.7e-3
+ It_valid_HBM=5.5
+ It2_MM=45.05e-3
+ It_valid_MM=5.23
+ It2_CDM=139.3e-3
+ It_valid_CDM=20.0
+ It2='1000*(esd_event==0)+It2_HBM*(esd_event==1)+It2_MM*(esd_event==2)+It2_CDM*(esd_event==3)'
+ It_valid='1000*(esd_event==0)+It_valid_HBM*(esd_event==1)+It_valid_MM*(esd_event==2)+It_valid_CDM*(esd_event==3)'

* Subcircuit
*
xesdmonitor (pd pd1) It2_monitor keyp=panod It2=It2 esd_event=esd_event esd_exit=esd_exit It_valid=It_valid
grtlp (pd1 pd2) cur='(v(pd1,pd2)-voff_esd)/((rwire + rwire_int) + (((rsp+p_rs)*0.5-(rsp-p_rs)*0.5*tanh(100*(v(pd1,pd2)-voff_esd)))/(aanod))*pwr((1+pwr(abs(v(pd1,pd2)-voff_esd)/esdvsat,esdnsat)),1.0/esdnsat))'
rsera pd2 aa  r=rtota
dpri  aa  ab  diopnws  area=aanod   pj=panod   dtemp=dtemp
vsens ab  nwa 0v
rserc nwa nw  r=rtotc
Fsx   nwa ac  vsens  cgain
dnwsx ac  nwa ddnwsx   area=totanw  pj=totpnw  dtemp=dtemp
rrsx  sx  ac  r=rsx

.model diopnws d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.15
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
+    vb = 10.5

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

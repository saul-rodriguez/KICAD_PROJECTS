* Path, Component, Release: cmos7base/rel/HSPICE/models/esdndpi.inc, tech7_models, mod_cmos7base
* CMVC Revision: 1.2 09/11/20 08:50:23
*
*>  IBM 7RF/7WL  esdndpi    ESD diode - N+ isolated Pwell(over PI)
*
***********************************************************************
*                                   (Anode)
*                                   pw o
*                                      |
*                                      /
*             (Internal PCell    rser  \
*              resistance)             /
*                                      |
*                                   aa o--------+
*                                      |        |
*                                     ----      /\
*                            N+ Pwell \  /     /  \ Gleak 
*                               Diode  \/      \  /    
*                                     ----      \/ 
*                                      |        |    
*                                      |        |
*                                      +--------+
*                                      |             
*                                     / \
*                                     \ /  grtlp
*                                      | 
*                                     / \  
*                                     \ /  xesdmonitor
*                                      |
*                                   nd o             
*                                  (Cathode)
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter and 'number of cathodes'
*              xxx (pw nd) esdndpi area=1p  perim=4u ncath=1 dtemp=0
*
*  OPTIONAL:   dtemp -->  Device temperature difference with respect to
*                         the simulated circuit temperature (deg C).
*
*              area  -->  Total area of anode RX shape
*
*             perim  -->  Total perimeter of anode RX shape
*
*             ncath  -->  Number of cathode fingers
*
*             rwire  -->  Wiring resistance (use for pre-layout
*                         simulations)  [ohm]
*
*  NOTES:
*
*  1. Node order must be as specified.
*
* IBM CONFIDENTIAL
* (C) 2009 IBM Corporation
*                                
***********************************************************************
*
.subckt esdndpi  (pw nd)  area=1p  perim=4u  ncath=1  dtemp=0  rwire=1e-4
*
.param
*  We start by calculating the length of cathode rx
+ c = 0.2u
+ alpha = 'area/ncath +2*c*c'
+ beta  = '(2-sqrt(2))*c+perim/(4*ncath)'
+ lcathn = 'beta + sqrt(abs(beta*beta - alpha))'
+ wcathn = 'alpha/lcathn'
+ wcath = 'wcathn + delrx'
+ lcath = 'lcathn + delrx'
*  We then determine the total area and perimeter of cathode region
+ acath = '(lcath*wcath - 2*c*c)*ncath'
+ pcath = '(lcath + wcath + 2*sqrt(2)*c - 4*c)*ncath*2'
*
*  Calculate the internal resistance, starting with the wiring
*   ncath is the # of cathodes
+ nanod = 'ncath+1'
*   metwid is the M1 wire width
*   ametl and cmetl are the anode and cathode metal wire lengths
+ metwid = 2.88u
+ cmetl = '2.88u*ncath+0.72u'
+ ametl = '2.88u*nanod-0.78u'
*   nawires is the # of anode wires
*   ncwires is the # of cathode wires
+ ncwires = 'max(int((lcathn+3.14u)/7.44u + 0.01),1)'
+ nawires = 'max(ncwires-1,1)'
*   rmc is the resistance of the metal wiring to the cathode
+ rmc = '(m1rs*cmetl)/(metwid*ncwires)'
*   rma is the resistance of the wires leaving the anode
+ rma = '(m1rs*ametl)/(metwid*nawires)'
*
*   acsp is the anode to cathode separation
+ pwrs = 315
+ prpw = 1.0n
+ acsp = 0.78u
+ acspx = 'acsp-delrx'
*   wanodn is the anode width
+ wanodn = 0.60u
+ wanod = 'wanodn+delrx'
*   rc2 is the resistance through the pw
+ rc2 = '(pwrs*acspx)/(2*lcath*ncath)+(pwrs*wcath)/(12*lcath*ncath)+(pwrs*wanod)/(6*lcath*ncath)'
*   rc3 is the resistance through the vertical pw
+ rc3 = 'prpw/(lcath*wanod*nanod)'
*
*  esd parameters
+ esdvsat = '1000*(esd_event==0)+ 220m*(esd_event==1)+ 6.061*(esd_event==2)+3.09*(esd_event==3)'
+ esdnsat =  '1*(esd_event==0)+ 690.4m*(esd_event==1)+  2.899*(esd_event==2)+  2.54*(esd_event==3)'
+ rsp       = '1p'
+ p_rs_esdpnb_wf=1.506p
+ rdcc=10p
+ rwint_esd='1e-4*(esd_event==0)+(80m)*(esd_event==1)+(10p/acath)*(esd_event==2)+(13p/acath)*(esd_event==3)'
+ voff_esd='0*(esd_event==0)+200m*(esd_event==1)+200m*(esd_event==2)+200m*(esd_event==3)'
+ rtot='(rma+rc2+rc3+rmc)*(esd_event==0)+rdcc/acath*(esd_event==1)+rdcc/acath*(esd_event==2)+rdcc/acath*(esd_event==3)'
+ rwire_int='(esd_extr==1)?1e-4:rwint_esd'
+ It2_HBM=29.7e-3
+ It_valid_HBM=5.5
+ It2_MM=45.05e-3
+ It_valid_MM=5.23
+ It2_CDM=139.3e-3
+ It_valid_CDM=20.0
+ It2='1000*(esd_event==0)+It2_HBM*(esd_event==1)+It2_MM*(esd_event==2)+It2_CDM*(esd_event==3)'
+ It_valid='1000*(esd_event==0)+It_valid_HBM*(esd_event==1)+It_valid_MM*(esd_event==2)+It_valid_CDM*(esd_event==3)'
* 
*  We then calculate the leakage parameters
+ lk1 = '7.9u*acath + 145p*pcath'
+ lk3 = '0.3u*acath + 0.87p*pcath'

*  Internal wiring and SX resistors
xesdmonitor (nb1 nd) It2_monitor keyp=pcath It2=It2 esd_event=esd_event esd_exit=esd_exit It_valid=It_valid
grtlp (nb2  nb1) cur='(v(nb2,nb1)-voff_esd)/((rwire + rwire_int)+(((rsp+p_rs_esdpnb_wf)*0.5-(rsp-p_rs_esdpnb_wf)*0.5*tanh(100*(v(nb2,nb1)-voff_esd)))/(acath))*pwr((1+pwr(abs((v(nb2,nb1)-voff_esd))/esdvsat,esdnsat)),1.0/esdnsat))'
dpri  aa nb2  dionpw   area=acath  pj=pcath dtemp=dtemp
gleak aa nb2  cur='lk1*pwr(V(aa,nb2),1) + lk3*pwr(V(aa,nb2),3)'
rser  aa pw  r=rtot

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
+     n = n_n
+    js = '(0.14*(ncath==1)+1)*js_n'
+   jsw = '(0.14*(ncath==1)+1)*jsw_n'
+    cj = cj_n
+    pb = pb_n
+    mj = mj_n
+   cjp = cjsw_n
+   php = pbsw_n
+  mjsw = mjsw_n
+   cta = cta_n
+   tpb = pta_n
+   ctp = ctp_n
+  tphp = ptp_n
+    vb = 15.0

.ends esdndpi

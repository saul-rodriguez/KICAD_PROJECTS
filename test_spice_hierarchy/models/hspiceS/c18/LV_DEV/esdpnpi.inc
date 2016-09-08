* Path, Component, Release: cmos7base/rel/HSPICE/models/esdpnpi.inc, tech7_models, mod_cmos7base
* CMVC Revision: 1.2 09/11/20 08:50:36
*
*>  IBM 7RF/7WL  esdpnpi    ESD diode - P+ Nwell over PI
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
*                                      /
*             (Internal PCell   rser   \
*              resistance)             /
*                                      |
*                                   aa o--------+
*                                      |        |
*                                     ----      /\
*                            P+ Nwell \  /     /  \ Gleakp
*                               Diode  \/      \  /
*                                     ----      \/
*                                      |        |   
*                                      +--------+   
*                                      |
*                                   nw o
*                                 (Cathode)
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter and 'number of anodes'
*              xxx (pd nw) esdpnpi area=1p  perim=4u nanod=1 dtemp=0
*
*  OPTIONAL:  dtemp -->  Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*             area  -->  Total area of anode RX shape
*
*            perim  -->  Total perimeter of anode RX shape
*
*            nanod  -->  Number of anode fingers
*
*             rwire -->  Wiring resistance (use for pre-layout
*                        simulations)  [ohm]
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
.subckt esdpnpi  (pd nw)  area=1p  perim=4u  nanod=1  dtemp=0  rwire=1e-4 
*
.param
*  We start by calculating the length of anode rx
+ c = 0.2u
+ alpha = 'area/nanod +2*c*c'
+ beta  = '(2-sqrt(2))*c+perim/(4*nanod)'
+ lanodn = 'beta + sqrt(abs(beta*beta - alpha))'
+ wanodn = 'alpha/lanodn'
+ wanod = 'wanodn + delrx'
+ lanod = 'lanodn + delrx'
*  We then determine the total area and perimeter of anode region
+ aanod = '(lanod*wanod - 2*c*c)*nanod'
+ panod = '(lanod + wanod + 2*sqrt(2)*c - 4*c)*nanod*2'
*
*  Calculate the internal resistance, starting with the wiring
*   ncath is the # of cathodes
+ ncath = 'nanod+1'
*   metwid is the M1 wire width
*   ametl and cmetl are the anode and cathode metal wire lengths
+ metwid = 2.88u
+ ametl = '2.88u*nanod+0.72u'
+ cmetl = '2.88u*ncath-0.78u'
*   nawires is the # of anode wires
*   ncwires is the # of cathode wires
+ nawires = 'max(int((lanodn+3.14u)/7.44u + 0.01),1)'
+ ncwires = 'max(nawires-1,1)'
*   rma is the resistance of the metal wiring to the anode
+ rma = '(m1rs*ametl)/(metwid*nawires)'
*   rmc is the resistance of the wires leaving the cathode
+ rmc = '(m1rs*cmetl)/(metwid*ncwires)'
*
*   acsp is the anode to cathode separation
+ acsp = 0.78u
+ acspx = 'acsp-delrx'
*   wcathn is the cathode width
+ wcathn = 0.60u
+ wcath = 'wcathn+delrx'
*   rc2 is the resistance through the nw
+ rc2 = '(nwrs*acspx)/(2*lanod*nanod)+(nwrs*wanod)/(12*lanod*nanod)+(nwrs*wcath)/(6*lanod*nanod)'
*   rc3 is the resistance through the vertical nw
+ rc3 = 'nrnw/(lanod*wcath*ncath)'
* 
* We then calculate the leakage parameters
+ lk1 = '1.8u*aanod + 2.4p*panod'
+ lk3 = '0.1u*aanod + 4.3p*panod'
*
* esd parameters
+ esdvsat = '1000*(esd_event==0)+ 121.7m*(esd_event==1)+ 6.936*(esd_event==2)+ 10*(esd_event==3)'
+ esdnsat =    '1*(esd_event==0)+ 1.33*(esd_event==1)+ 3.0*(esd_event==2)+   10*(esd_event==3)'
+ rsp=2p
+ p_rs=1p
+ rdcc=10p
+ rwint_esd= '1e-4*(esd_event==0)+(102m)*(esd_event==1)+(10.9p/aanod)*(esd_event==2)+(13.85p/aanod)*(esd_event==3)'
+ voff_esd='0*(esd_event==0)+180m*(esd_event==1)+157.2m*(esd_event==2)+133.3m*(esd_event==3)'
+ rtot ='(rma+rc2+rc3+rmc+(100p/aanod))*(esd_event==0)+rdcc/aanod*(esd_event==1)+rdcc/aanod*(esd_event==2)+rdcc/aanod*(esd_event==3)'
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
xesdmonitor (pd pd1) It2_monitor keyp=panod It2=It2 esd_event=esd_event esd_exit=esd_exit It_valid=It_valid
grtlp (pd1 pd2) cur='(v(pd1,pd2)-voff_esd)/((rwire + rwire_int) + (((rsp+p_rs)*0.5-(rsp-p_rs)*0.5*tanh(100*(v(pd1,pd2)-voff_esd)))/(aanod))*pwr((1+pwr(abs(v(pd1,pd2)-voff_esd)/esdvsat,esdnsat)),1.0/esdnsat))'
rsera pd2 aa  r=rtot
dpri  aa  nw  diopnws  area=aanod   pj=panod   dtemp=dtemp
gleak aa nw  cur='lk1*pwr(V(aa,nw),1) + lk3*pwr(V(aa,nw),3)'

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
+    js = '(0.04*(nanod==1)+1)*js_p'
+   jsw = '(0.04*(nanod==1)+1)*jsw_p'
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
+    vb = 10.0

.ends esdpnpi

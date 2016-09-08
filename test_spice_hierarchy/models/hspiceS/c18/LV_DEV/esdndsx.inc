* Path, Component, Release: cmos7base/rel/HSPICE/models/esdndsx.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  esdndsx   N+ or Nwell to Substrate Junction Diode for ESD
*
***********************************************************************
*
*  Model can be used in conjunction with the design system extraction
*  program which calculates/combines junction parasitic capacitance
*  per node.
*
*                  o  nwell (n)
*                  |  or n diffusion
*                 / \
*                 \ /  xesdmonitor 
*                  | 
*                 / \  
*                 \ /  grtlp
*                  |
*                  |
*                ----
*                 /\   Dnwx
*                /  \         Diode includes junction capacitance,
*                ----         resistance and sat current parameters.
*                  |
*                  |
*                  \
*                  /  Rseries
*                  \
*                  |
*                  o  substrate (sx)
*
***********************************************************************
*
*  SYNTAX:     Specify both total area and perimeter and 'number of cathodes'
*              as well as whether or not N-well is used
*              xxx  (n sx)  esdndsx (area=1p  perim=4u  ncath=1  nw=1  dtemp=0)
*
*
*  NOTES:
*
*  1. Node order must be as specified.
*
*  2. Input parameters are 
*
*              area  -->  Total area of cathode RX shape
*
*             perim  -->  Total perimeter of cathode RX shape
*
*             ncath  -->  Number of cathode fingers
*
*                nw  -->  NW/SX (nw=1) or N+/SX (nw=0),
*                         default is nw=1 NW/SX diode
*
*             dtemp  -->  Device temperature difference with respect to
*                         the simulated circuit temperature (deg C).
*
*              rwire -->  Wiring resistance (use for pre-layout
*                         simulations)   [ohm]
*
*                                
***********************************************************************
*
.subckt esdndsx  (n sx)  area=1p  perim=4u  ncath=1  nw=0  dtemp=0 rwire=1e-4
*
*  We start by calculating the length of cathode rx
+ pfac = 'perim / (4*ncath)'
+ lcathn = 'pfac + sqrt(abs(pfac*pfac - area/ncath))'
+ wcathn = 'area / (ncath*lcathn)'
+ wcath = 'wcathn + delrx'
+ lcath = 'lcathn + delrx'
*  We then determine the total area and perimeter of cathode region
+ acath = 'lcath*wcath*ncath'
+ pcath = '(lcath + wcath)*ncath*2'
*
*  We then calculate the series resistance, starting with the wire resistance
*  nanod is the # of anodes
*  ncath is the # of cathodes
+ nanod = 'ncath+1'
*  metwid is the M1 wire width
+ metwid = 2.88u
*  ametl/cmetl is the length of the metal wire connecting the anode/cathode 
+ ametl = '7.32u*ncath+1.54u'
+ cmetl = '7.32u*ncath-1.86u'
*  nawires/ncwires is the # of anode/cathode wires
+ ncwires = 'max(int((lcath+4.36u)/7.44u + 0.01),1)'
+ nawires = 'max(ncwires-1,1)'
*  rma/rmc is the resistance of the metal wiring to the anode/cathode
+ rma = '(m1rs*ametl)/(metwid*nawires)'
+ rmc = '(m1rs*cmetl)/(metwid*ncwires)'
*
+ pwrs = 315
+ prpw = 1.0n
*  acsp is the anode to cathode separation
+ acsp = 0.78u
+ acspx = 'acsp-delrx'
*  wcathn is the cathode width
+ wanodn = 0.60u
+ wanod = 'wcathn+delrx'
*  rc2 is the resistance through the pw
+ rc2 = '(pwrs*acspx)/(2*lcath*ncath)+(pwrs*wcath)/(12*lcath*ncath)+(pwrs*wanod)/(6*lcath*ncath)'
*  rc3 is the resistance through the vertical pw
+ rc3 = 'prpw/(lcath*wanod*nanod)'
*
*  esd parameters
+ esdvsat = '1000*(esd_event==0)+ 220m*(esd_event==1)+ 6.061*(esd_event==2)+3.09*(esd_event==3)'
+ esdnsat =  '1*(esd_event==0)+ 690.4m*(esd_event==1)+  2.899*(esd_event==2)+  2.54*(esd_event==3)'
+ rsp = 1p
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

*  Subcircuit
xesdmonitor (nb1 n) It2_monitor keyp=pcath It2=It2 esd_event=esd_event esd_exit=esd_exit It_valid=It_valid
grtlp (nb2  nb1) cur='(v(nb2,nb1)-voff_esd)/((rwire + rwire_int)+(((rsp+p_rs_esdpnb_wf)*0.5-(rsp-p_rs_esdpnb_wf)*0.5*tanh(100*(v(nb2,nb1)-voff_esd)))/(acath))*pwr((1+pwr(abs((v(nb2,nb1)-voff_esd))/esdvsat,esdnsat)),1.0/esdnsat))'
dnwa   nb3  nb2   dnsx  area=acath  pj=pcath  dtemp=dtemp
rser   nb3  sx  r=rtot

* N/NW to SX Diode
*
.model dnsx d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+     n = 'nw*n_nw + (1-nw)*n_n'
+    js = 'nw*js_nw + (1-nw)*js_n'
+   jsw = 'nw*jsw_nw + (1-nw)*jsw_n'
+    cj = 'nw*cj_nw + (1-nw)*cj_n'
+    pb = 'nw*pb_nw + (1-nw)*pb_n'
+    mj = 'nw*mj_nw + (1-nw)*mj_n'
+   cjp = 'nw*cjsw_nw + (1-nw)*cjsw_n'
+   php = 'nw*pbsw_nw + (1-nw)*pbsw_n'
+  mjsw = 'nw*mjsw_nw + (1-nw)*mjsw_n'
+   cta = 'nw*cta_nw + (1-nw)*cta_n'
+   tpb = 'nw*pta_nw + (1-nw)*pta_n'
+   ctp = 'nw*ctp_nw + (1-nw)*ctp_n'
+  tphp = 'nw*ptp_nw + (1-nw)*ptp_n'
+    vb = 'nw*10.0 + (1-nw)*15.0'

.ends esdndsx

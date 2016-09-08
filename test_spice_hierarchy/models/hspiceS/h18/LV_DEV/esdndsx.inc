* Path, Component, Release: cmhv7sf/rel/HSPICE/models/esdndsx.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
*>  esdndsx   N+ to Substrate Junction Diode for ESD
*
***********************************************************************
*
*  Model can be used in conjunction with the design system extraction
*  program which calculates/combines junction parasitic capacitance
*  per node.
*
*                     o  n diffusion (n)
*                     |  
*       +-------------+  
*       |             |
*      /\ gleak     ----
*     /  \           /\   Dnwx
*     \  /          /  \         Diode includes junction capacitance,
*      \/           ----         resistance and sat current parameters.
*       |             |
*       +-------------o aa  
*                     |
*                     \
*                     /  Rseries
*                     \
*                     |
*                     |
*                     o  substrate (sx)
*
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter and 'number of cathodes'
*              xxx  (n sx)  esdndsx (area=1p  perim=4u  ncath=1  nw=0  dtemp=0)
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
*                         Not used in model, parameter kept for back compatability
*
*             dtemp  -->  Device temperature difference with respect to
*                         the simulated circuit temperature (deg C).
*
*             rwire  -->  Wiring resistance used for pre-extraction simulation
*
*              acsp  -->  Anode to cathode spacing
*
*
*                                
***********************************************************************
.subckt esdndsx  (n sx) area=1p perim=4u ncath=1 nw=0 dtemp=0 rwire=0.1m acsp=0.36u
*
.param
*  We start by calculating the length of cathode rx
+ pfac = 'perim / (4*ncath)'
+ lcathn = 'pfac + sqrt(abs(pfac*pfac - area/ncath))'
+ wcathn = 'area / (ncath*lcathn)'
+ wcath = 'wcathn + delrx'
+ lcath = 'lcathn + delrx'
*  We then determine the total area and perimeter of cathode region
+ acath = 'lcath*wcath*ncath'
+ pcath = '2*(lcath + wcath)*ncath'
*
* Calculate the internal resistance
*  acsp is the anode to cathode separation
+ pwrs = 315
+ prpw = 1.0n
+ acspx = 'acsp-delrx'
*  wcathn is the cathode width
+ wanodn = 0.72u
+ wanod = 'wanodn+delrx'
*  rc2 is the resistance through the pw
+ rc2 = '(pwrs*acspx)/(2*lcath*ncath)+(pwrs*wcath)/(12*lcath*ncath)+(pwrs*wanod)/(6*lcath*ncath)'
*  rc3 is the resistance through the vertical pw
+ rc3 = 'prpw/(lcath*wanod*(ncath+1))'
*
* leakage current
+ lk10 = 4p
+ lk1a = 720.4u
+ lk1p = 1.567n
+ lkt  = 13
+ lk3  = 0
+ lk1  = '(lk10 + lk1a*area + lk1p*perim)*pow((temper+273)/298,lkt)'
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
+ It2       = '1000*(esd_event==0) + 17.5e-3*(esd_event==1)    + 16.9e-3*(esd_event==2)	   + 42e-3*(esd_event==3)'
+ It_valid  = '1000*(esd_event==0) + 5*(esd_event==1)          + 5*(esd_event==2)	   + 15*(esd_event==3)'
 
* Subcircuit
dnsa   aa   n  dnsx  area=acath  pj=pcath dtemp=dtemp
gleak  aa   n  cur='lk1*pwr(v(aa,n),1)'
rser   sx aa3  r=rtot
.if (esd_event > 0)
 grtlp       aa2  aa   cur='v(aa2,aa)/((rwire + rwire_int) + (((rsp+p_rs)*0.5-(rsp-p_rs)*0.5*tanh(100*v(aa2,aa))) / (acath))*pwr((1+pwr(abs(v(aa2,aa))/esdvsat,esdnsat)),1.0/esdnsat))'
 xesdmonitor aa3  aa2  It2_monitor keyp=pcath It2=It2 esd_exit=esd_exit It_valid=It_valid
.else
r11    aa3 aa  r=1e-4
.endif

* N+ to SX Diode
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
+     n = n_n
+    js = '(js_n/acath)*20p'
+   jsw = jsw_n
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
+    vb = 13.5

.ends esdndsx

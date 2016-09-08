* Path, Component, Release: cmhv7sf/rel/HSPICE/models/vncap_hv.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  IBM CMHV7SF  vncap_hv    High Voltage VNCAP Capacitor
*
***********************************************************************
*
* The model is comprised of a capacitor and series resistances and inductance.
* The input (lower plate) has losses to substrate characterized by capacitors
* and series resistor.
*
*
*            r1           c     |------|        r2
*                        | |    |  l1  |     
*  o ------/\  /\--------| |----|      |------/\  /\-----o
* in    |    \/          | |    |------|        \/    |  out
*       |                                             |
*     -----                                         ------
*     -----  c1                               c2    ------
*       |                                             |
*       |                                             |
*       -----------------|-----------------------------
*                        |    
*                        \     
*                        /  r3
*                        \            
*                        |
*                        |  reference plane
*                        | 
*                o-------|---------------------------o
*
*
***********************************************************************
*
*  DIMENSIONS: 
*              w --> desired width.
*
*              l --> length of the VNCAP.
*
*	       m1s --> M1 spacing (default m1s = 0.36um; 50V device)
*                                  m1s = 0.6um; 120V device
*
*	       mxs --> Mx spacing (default = 0.5um; 50V device)
*                                  mxs = 0.84um; 120V device
*
*  SYNTAX:     Specify both length, width and metal spacings:
*              xxx  in out ref  vncap_hv (l=100u w=100u m1s=0.36u mxs=0.5u botlev=1 toplev=6)
*
*  OPTIONAL:   botlev  --> Indicates the lowest thin metal level of the VNCAP.
*                          Possible values are 1,2,3,4,5 or 6. Default = 1.
*
*              toplev  --> Indicates the top thin metal level of the VNCAP.
*                          Possible values are 1,2,3,4,5 or 6. Default = 4. 
*
*              setind  --> User determined value for the parasitic inductance.
*                          The default value of -2, which is used as a switch,
*                          forces the calculated inductance to be used.
*
*              est     --> Include estimated bottom plate to substrate
*                          capacitance (default, est=1). Turn
*                          switch off (est=0) for extracted layout.
*
*	       rsx     --> Specifies the substrate resistance
*
*	       par     --> Device multiplicity 
*
*              dtemp   --> Local temperature variation from reference circuit
*                          temperature. Default value = 0.
*
*  NOTES:
*
*  1. Node assignment  - Node "in"  
*                      - Node "out"
*                      - Node "ref" Typically substrate contact node. 
*
*  2. Metal levels comprising the VNCAP capacitor must be adjacent to each
*     other in the back end of the line stack.  For example, a VNCAP built
*     using only levels M1, M2, and M4 is not allowed.  
*
*  3. Estimated bottom plate parasitic capacitance calculation assumes
*     device only over substrate or N-well. Accurate parasitic
*     capacitance value for case with devices under VNCAP can only be
*     obtained from extracted layout.
*
*  4. The parasitic inductance included in this model is for the VNCAP only,
*     It does not include any connections to the VNCAP.
*     The inductance assumes the wiring is into the VNCAP centered on one side
*     and out of the VNCAP centered on the opposite side. These two sides are
*     assumed to be sides defined by the parameter w. For any other connection
*     the inductance would be different than the model indicates.
*
*
*
***********************************************************************
.subckt vncap_hv  in out ref  w=100u l=100u m1s=0.36u mxs=0.5u botlev=1 toplev=4 est=1 setind=-2 dtemp=0 rsx=50 par=1 
*
******************************************************************
*  Device Type
+      vn120  = '(m1s==0.60u)||(mxs==0.84u)'
+      vn50   = '(1 - vn120)'
*
* Metal finger width [m]
+      mwx0_n  = 'vn50*0.28u + vn120*0.32u'
+      mwm1_n  = 'vn50*0.42u + vn120*0.56u'
+      mwx1_f  = 'mwm1_n+vn50*delm1+vn120*delm1i'
+      mwx2_f  = 'mwx0_n+0.0916u+ vn120*0.0816u+delm2'
+      mwx3_f  = 'mwx0_n+0.0916u+ vn120*0.0816u+delm3'
+      mwx4_f  = 'mwx0_n+0.0916u+ vn120*0.0816u+delm4'
+      mwx5_f  = 'mwx0_n+0.0916u+ vn120*0.0816u+delm5'
+      mwx6_f  = 'mwx0_n+0.0916u+ vn120*0.0816u+delmt'
*
* Metal finger space [m]
+      mspx0_n = 'vn50*0.5u + vn120*0.84u'
+      mspm1_n = 'vn50*0.36u + vn120*0.6u'
+      mspx1_f = 'mspm1_n-vn50*delm1-vn120*delm1i'
+      mspx2_f = 'mspx0_n-vn50*0.0916u- vn120*0.0816u-delm2'
+      mspx3_f = 'mspx0_n-vn50*0.0916u- vn120*0.0816u-delm3'
+      mspx4_f = 'mspx0_n-vn50*0.0916u- vn120*0.0816u-delm4'
+      mspx5_f = 'mspx0_n-vn50*0.0916u- vn120*0.0816u-delm5'
+      mspx6_f = 'mspx0_n-vn50*0.0916u- vn120*0.0816u-delmt'
*
* tab width [m]
+      mwtab_n = '1.00u'
+      m1tab_f = 'mwtab_n+vn50*delm1+vn120*delm1i'
+      m2tab_f = 'mwtab_n+delm2'
+      m3tab_f = 'mwtab_n+delm3'
+      m4tab_f = 'mwtab_n+delm4'
+      m5tab_f = 'mwtab_n+delm5'
+      m6tab_f = 'mwtab_n+delmt'
*
* finger-end to tab space  [m]
+      mdend0_n = 'vn50*0.80u + vn120*1.60u'
+      mdend1_f  = 'mdend0_n-vn50*delm1+vn120*delm1i'
+      mdend2_f  = 'mdend0_n-delm2'
+      mdend3_f  = 'mdend0_n-delm3'
+      mdend4_f  = 'mdend0_n-delm4'
+      mdend5_f  = 'mdend0_n-delm5'
+      mdend6_f  = 'mdend0_n-delmt'

******************************************************************
* calculations to determine # fingers, finger length, # vias per finger
* Determine the total number of fingers from the width
*
+  fingtot  = '(int(((w-((2*mwx0_n)+mspx0_n))/(2*(mwx0_n+mspx0_n)))+1e-5)*2)+2'
*
* Calculate fingers per plate.  Each plate has to have the same number 
* of fingers. Thus an even number of total fingers, the int function
* prevents fractional finger in case this rule was somehow violated
*
+  fing     = 'int(fingtot/2)'
*
* Determine the actual finger lengths, common run length
*
+  lfng     = 'l-2*m2tab_f-2*mdend2_f'
+  lfng_n   = 'l-2*mwtab_n-2*mdend0_n'
*
* Determine number of vias present for each finger
*
+   viax    = '0'
*
************* Logic Calculations ****************************
******************************************************************
* VNCAP capacitance has a length component and an end component
* First, figure out which levels are being used.
* logic calculations: metal and via layers used
******************************************************************
+      met1  = '(botlev == 1)&&(toplev >= 1)'
+      met2  = '(botlev <= 2)&&(toplev >= 2)'
+      met3  = '(botlev <= 3)&&(toplev >= 3)'
+      met4  = '(botlev <= 4)&&(toplev >= 4)'
+      met5  = '(botlev <= 5)&&(toplev >= 5)'
+      met6  = '(botlev <= 6)&&(toplev == 6)'
*
*** Define via levels that are present***********************
+      via1  = '(botlev == 1)&&(toplev > 1)'
+      via2  = '(botlev <= 2)&&(toplev > 2)'
+      via3  = '(botlev <= 3)&&(toplev > 3)'
+      via4  = '(botlev <= 4)&&(toplev > 4)'
+      via5  = '(botlev <= 5)&&(toplev > 5)'
*
*
*****************************************************************
* Define rough estimate of relative dielectric constant (F/m)
+        er1 = 'vn50*7.547 + vn120*9.8*(met1-.15*(toplev>1))'
+        er2 = 'vn50*7.236 + vn120*10.2*(met2-.15*( (met1&&(toplev==2)) + ((botlev==2)&&(toplev>2)) )-.2*(met1&&toplev>2))'
+        er3 = 'vn50*7.236 + vn120*10.2*(met3-.15*( (met2&&(toplev==3)) + ((botlev==3)&&(toplev>3)) )-.2*(met2&&toplev>3))'
+        er4 = 'vn50*7.236 + vn120*10.2*(met4-.15*( (met3&&(toplev==4)) + ((botlev==4)&&(toplev>4)) )-.2*(met3&&toplev>4))'
+        er5 = 'vn50*7.236 + vn120*10.2*(met5-.15*( (met4&&(toplev==5)) + ((botlev==5)&&(toplev>5)) )-.2*(met4&&toplev>5))'
+        er6 = 'vn50*7.236 + vn120*10.2*(met6-.15*met5)'
*
*****************************************************************
* Define finger to finger capacitance where vias are not present (F/m)
****************************************************************
* Calculate fringe scaled length for each finger length
+  fingercfx1 = 'vn50*0.955 + vn120*0.96'
+   fingercfx = 'vn50*0.924 + vn120*0.96'
*
+     cm1  = 'er1*e0*((vn50*m1tv + vn120*m1ti)/mspx1_f)*fingercfx1'
+     cm2  = 'er2*e0*(m2t/mspx2_f)*fingercfx'
+     cm3  = 'er3*e0*(m3t/mspx3_f)*fingercfx'
+     cm4  = 'er4*e0*(m4t/mspx4_f)*fingercfx'
+     cm5  = 'er5*e0*(m5t/mspx5_f)*fingercfx'
+     cm6  = 'er6*e0*(mtt/mspx6_f)*fingercfx'
**************************************************************************
* Define additive finger to finger capacitance where vias are present (F/m)
**************************************************************************
* Calculate fringe scaling for each via (set to 0 because no via present)
+     viacf1 = '0'
+     viacf2 = '0'
+     viacf3 = '0'
+     viacf4 = '0'
+     viacf5 = '0'
+    capvia1 = '(m1m2t/m1m2tn)*(0.0120n*viacf1)'
+    capvia2 = '(m2m3t/m2m3tn)*(0.0120n*viacf2)'
+    capvia3 = '(m3m4t/m3m4tn)*(0.0120n*viacf3)'
+    capvia4 = '(m4m5t/m4m5tn)*(0.0120n*viacf4)'
+    capvia5 = '(mxmtt/mxmttn)*(0.0120n*viacf5)'
*
******************************************************************
* Define end component of each possible set of levels in F per finger.
******************************************************************
* Calculate fringe scaled length for each finger end
+    endcfx1 = '0.996879/1.8'
+     endcfx = '1.016776/1.8'
+      cwan1 = '(2/pi)*((mspx1_f/mdend1_f)*atan(1/(mspx1_f/mdend1_f)) + atan(mspx1_f/mdend1_f)/(mspx1_f/mdend1_f) + log(4*((mspx1_f/mdend1_f)**2 + 1)/(mspx1_f/mdend1_f)))'
+      cwan2 = '(2/pi)*((mspx2_f/mdend2_f)*atan(1/(mspx2_f/mdend2_f)) + atan(mspx2_f/mdend2_f)/(mspx2_f/mdend2_f) + log(4*((mspx2_f/mdend2_f)**2 + 1)/(mspx2_f/mdend2_f)))'
+      cwan3 = '(2/pi)*((mspx3_f/mdend3_f)*atan(1/(mspx3_f/mdend3_f)) + atan(mspx3_f/mdend3_f)/(mspx3_f/mdend3_f) + log(4*((mspx3_f/mdend3_f)**2 + 1)/(mspx3_f/mdend3_f)))'
+      cwan4 = '(2/pi)*((mspx4_f/mdend4_f)*atan(1/(mspx4_f/mdend4_f)) + atan(mspx4_f/mdend4_f)/(mspx4_f/mdend4_f) + log(4*((mspx4_f/mdend4_f)**2 + 1)/(mspx4_f/mdend4_f)))'
+      cwan5 = '(2/pi)*((mspx5_f/mdend5_f)*atan(1/(mspx5_f/mdend5_f)) + atan(mspx5_f/mdend5_f)/(mspx5_f/mdend5_f) + log(4*((mspx5_f/mdend5_f)**2 + 1)/(mspx5_f/mdend5_f)))'
+      cwan6 = '(2/pi)*((mspx6_f/mdend6_f)*atan(1/(mspx6_f/mdend6_f)) + atan(mspx6_f/mdend6_f)/(mspx6_f/mdend6_f) + log(4*((mspx6_f/mdend6_f)**2 + 1)/(mspx6_f/mdend6_f)))'
*
* Calculate capacitance per finger end
*
+     ecm1 = '(vn50*m1tv + vn120*m1ti)*e0*er1*endcfx1*(mwx1_f/mdend1_f + 2*cwan1)'
+     ecm2 = 'm2t*e0*er2*endcfx*(mwx2_f/mdend2_f + 2*cwan2)'
+     ecm3 = 'm3t*e0*er3*endcfx*(mwx3_f/mdend3_f + 2*cwan3)'
+     ecm4 = 'm4t*e0*er4*endcfx*(mwx4_f/mdend4_f + 2*cwan4)'
+     ecm5 = 'm5t*e0*er5*endcfx*(mwx5_f/mdend5_f + 2*cwan5)'
+     ecm6 = 'mtt*e0*er6*endcfx*(mwx6_f/mdend6_f + 2*cwan6)'
*
******************************************************************
* Calculate end and length components of capacitance for thin levels
* and accumulate.
******************************************************************
*  Temperature coef.
+    pdeltat = 'temper-25+dtemp'
+    tc1m1   = '-14e-6'
+    tc2m1   = '-0.04e-6'
+    tc1mx   = '-65e-6'
+    tc2mx   = '-0.07e-6'
+    tcoefm1 = '1 + tc1m1*pdeltat + tc2m1*pdeltat*pdeltat'
+    tcoefmx = '1 + tc1mx*pdeltat + tc2mx*pdeltat*pdeltat'
*
**** Capacitance per unit length for portion of finger with no vias
+    capxlnv = 'met1*cm1*tcoefm1 + (met2*cm2+met3*cm3+met4*cm4+met5*cm5+met6*cm6)*tcoefmx'
*
**** Add in capacitance per unit length due to vias
+    capxlv  = 'via1*capvia1+via2*capvia2+via3*capvia3+via4*capvia4+via5*capvia5'
*
**** Capacitance of end component per finger
+    capxe   = 'met1*ecm1*tcoefm1 + (met2*ecm2+met3*ecm3+met4*ecm4+met5*ecm5+met6*ecm6)*tcoefmx'
*
**** Calculate capacitances for each portion of finger (including vias)
+    viasize = '0.28u'
+    capxnv  = 'lfng*capxlnv*(fingtot-1)'
+    capxv   = 'viax*viasize*capxlv*(fingtot-1)'
* Two outermost fingers have 1/2 of the end capacitance of inner fingers
+    capxet  = '(fingtot-1)*capxe'
+    capxtot = 'capxnv+capxv+capxet'
*
******************************************************************
* VNCAP resistance has a length component.  Define it for each level.
* r1-re are in ohms/m.
******************************************************************
+         r1 = '((vn50*m1rsv + vn120*m1rsi)/mwx1_f)'
+         r2 = '(m2rs/mwx2_f)'
+         r3 = '(m3rs/mwx3_f)'
+         r4 = '(m4rs/mwx4_f)'
+         r5 = '(m5rs/mwx5_f)'
+         r6 = '(mtrs/mwx6_f)'
*****************************************************************************
* Resistance scaling from presence of vias up this level
* (from EMSIM simulations). The vias contribute very little 
* reduction in resistance due to the current flow being primarily
* in a lateral direction through the fingers.
*****************************************************************************
+     vscale = '1'
******************************************************************
* VNCAP resistance has a length component.  Each finger is a bunch
* of wires in parallel, with the vias providing a little
* reduction in resistance. Resistance of all finger (ohms).
******************************************************************
+    invres  = 'vscale*(met1/r1 + met2/r2 + met3/r3 + met4/r4 + met5/r5 + met6/r6)'
+    fresxl  = '1.0/(invres+1e-15)'
*
******************************************************************
* Now the resistance of the bar that connects the fingers.
* The finger resistance is scaled by the proper ratio
* Ex, if the tab width is 2.8u and the finger width is .28u then
* the resistance per unit length of the tab is 1/10 that of a finger
******************************************************************
*
+     rtabm1 = '(vn50*m1rsv + vn120*m1rsi)/m1tab_f'
+     rtabm2 = 'm2rs/m2tab_f'
+     rtabm3 = 'm3rs/m3tab_f'
+     rtabm4 = 'm4rs/m4tab_f'
+     rtabm5 = 'm5rs/m5tab_f'
+     rtabm6 = 'mtrs/m6tab_f'
*
+     invbres= 'met1/rtabm1 + met2/rtabm2 + met3/rtabm3 + met4/rtabm4 + met5/rtabm5 + met6/rtabm6'
*
+     bresxl = '1/(invbres+1e-20)'
+     rbarx  = 'bresxl*w/5'
*
******************************************************************
* We are accounted for each finger seperatly.
******************************************************************
+      fres  = 'fresxl*(lfng+mdend2_f)/(3.0*fing)+rbarx'
******************************************************************
* Inductance per finger: use the Grover formula with the wire
* length and width values obtained by adding finger widths and 
* lengths.  First define the effective thicknesses based on the
* metal levels used.
******************************************************************
+     windx  = '2*fing*mwx0_n'
+     windm1 = '2*fing*mwm1_n'
+     tindx  = 'met2*m2t + met3*m3t + met4*m4t + met5*m5t + met6*mtt'
+     tindm1 = 'met1*(vn50*m1tv + vn120*m1ti) '
*
******************************************************************
* Grover's formula, suitably scaled (based on EMSIM simulations)
* we should have 1/3 of finger inductance and '2' for input and output 
******************************************************************
+     ratx   = '2*lfng/(windx+tindx)'
+     ratm1  = '2*lfng/(windm1+tindm1)'
+     findx  = '(l*2e-7)*(log(ratx)+0.5+0.447/ratx)'
+     findm1 = '(l*2e-7)*(log(ratm1)+0.5+0.447/ratm1)'
+     plind  = '(findx*findm1/(findx+findm1))/(3.0)*2'
* Check to see if the user has overridden the inductance value
+    indval  = '(setind>=0)*setind + (setind<0)*(plind)'
******************************************************************
* Parasitic capacitance to substrate calculations
******************************************************************
* Determine which metal level forms the bottom plate
+       bot1 = 'botlev==1'
+       bot2 = 'botlev==2'
+       bot3 = 'botlev==3'
+       bot4 = 'botlev==4'
+       bot5 = 'botlev==5'
+       bot6 = 'botlev==6'
* Determine which metal level forms the top plate
+       top1 = 'toplev==1'
+       top2 = 'toplev==2'
+       top3 = 'toplev==3'
+       top4 = 'toplev==4'
+       top5 = 'toplev==5'
+       top6 = 'toplev==6'
* Find what tolerance we need
+      bdelw = 'bot1*delm1+bot2*delm2+bot3*delm3+bot4*delm4+bot5*delm5+bot6*delmt'
* Calculate the finger widths of the bottom plate
+      botwx = 'mwx1_f*bot1+mwx2_f*bot2+mwx3_f*bot3+mwx4_f*bot4+mwx5_f*bot5+mwx6_f*bot6'
* Calculate the area of the fingers
+      farea = '2*(lfng+mdend2_f)*(fing*botwx)'
* Calculate area of tabs
+      barea = '2*(mwtab_n+bdelw)*w'
*
* Calculate thickness of dielectric below each metal layer
* For vncap 50V:
* 25pct of VNCAP groundplane area is RX.  The rest is over STI
* For vncap 120V: no RX or PC fill
+    m1thkn  = 'oppcstif+oppcthk+capcti'
+    m1thk   = 'm1thkn-vn50*(.50*oppcstif)'
+    m2thk   = 'm1thk+(vn50*m1tv + vn120*m1ti)+m1m2t'
+    m3thk   = 'm2thk+m2t+m2m3t'
+    m4thk   = 'm3thk+m3t+m3m4t'
+    m5thk   = 'm4thk+m4t+m4m5t'
+    m6thk   = 'm5thk+m5t+mxmtt'
* Calculate effective dielectric height
+    heffec  = 'bot1*m1thk+bot2*m2thk+bot3*m3thk+bot4*m4thk+bot5*m5thk+bot6*m6thk'
* Total area
+      tarea = 'farea+barea'
* Area term of parasitic capacitance
+      carea = 'eoxdepo*e0*tarea/(heffec+1e-35)'
*
*****************************************************************
*Perimeter term of capacitance to substrate
*****************************************************************
* Total perimeter
+     tperim = '2*((l+bdelw)+(w+bdelw))'
+       weff = 'fingtot*(mwx0_n+bdelw)*(toplev > 1) + fingtot*(mwm1_n+bdelw)*(toplev == 1)'
+       htop = 'top1*m1thk+top2*m2thk+top3*m3thk+top4*m4thk+top5*m5thk+top6*m6thk'
+       mtop = 'top1*m1tv+top2*m2t+top3*m3t+top4*m4t+top5*m5t+top6*mtt'
*
* Calculate the singularity term of the fringe capacitance
+  csingp    = 'eoxdepo*e0*(2/(pi-2)*log(pi/2))'
*
* Calculate the terms of the top plate
+  ctopedgp  = 'eoxdepo*e0*(2/pi)*log(1+mtop/htop)'
+  ctoplp    = 'eoxdepo*e0*log(1+(weff/(htop+mtop)))'
+  ctopwp    = 'eoxdepo*e0*log(1+((l+bdelw)/(htop+mtop)))'
*
* Calculate the edge and top terms for the lower plates
+  cf1       = 'eoxdepo*e0*((2/pi)*log(1+m1tv/m1thk)+(1/pi)*log(1+(2*m1m2t/(m1tv+m1thk))))'
+  cf2       = 'eoxdepo*e0*((2/pi)*log(1+m2t/m2thk)+(1/pi)*log(1+(2*m2m3t/(m2t+m2thk))))'
+  cf3       = 'eoxdepo*e0*((2/pi)*log(1+m3t/m3thk)+(1/pi)*log(1+(2*m3m4t/(m3t+m3thk))))'
+  cf4       = 'eoxdepo*e0*((2/pi)*log(1+m4t/m4thk)+(1/pi)*log(1+(2*m4m5t/(m4t+m4thk))))'
+  cf5       = 'eoxdepo*e0*((2/pi)*log(1+m5t/m5thk)+(1/pi)*log(1+(2*mxmtt/(m5t+m5thk))))'
*
* Calculate the sum of the lower plate capacitances
+   clowerp1 = 'cf1*((botlev==1)*(toplev>=2))+cf2*((botlev<=2)*(toplev>=3))'
+   clowerp2 = 'cf3*((botlev<=3)*(toplev>=4))+cf4*((botlev<=4)*(toplev>=5))'
+   clowerp3 = 'cf5*((botlev<=5)*(toplev>=6))'
+   clowerp  = 'clowerp1+clowerp2+clowerp3'
*
* Calculate fringe term of parasitic capacitance
+     cperim = '2*(w+bdelw)*ctopwp + 2*(l+bdelw)*ctoplp + tperim*(csingp+ctopedgp+clowerp)'
* Calculate total parasitic cap, divide by 2 for distrib
+        csx = '(cperim+carea)/2'
*
******************************************************************
* Determine VCC
+ vncapvc1 = '0'
+ m1vc2 = '-0.024e-6*((botlev == 1)&&(toplev == 1))'
+ m2vc2 = '-0.078e-6*((botlev == 2)&&(toplev == 2))'
+ m3vc2 = '-0.043e-6*((botlev == 3)&&(toplev == 3))'
+ m4vc2 = '-0.043e-6*((botlev == 4)&&(toplev == 4))'
+ m5vc2 = '-0.043e-6*((botlev == 5)&&(toplev == 5))'
+ m6vc2 = '-0.043e-6*((botlev == 6)&&(toplev == 6))'
+ mxmxvc= '-0.057e-6*(1-(botlev == toplev))'
+ vncapvc2 = 'm1vc2+ m2vc2+ m3vc2+ m4vc2+ m5vc2+ m6vc2+ mxmxvc'
******************************************************************
* Mis-match Calculation
+    mma     = '(vn50*(16.0)+ vn120*(16.0))/ (w*l * 1e12)'
+    mmw     = '(0) / (w*w* 1e12)'
+    mml     = '(0) / (l*l* 1e12)'
+    nlayers = 'int(toplev -botlev +1)'
+    m1mod   = '1+((-0.38*(1/nlayers))*met1)'
+    m3sig   = '((0.01 * (sqrt(mma+mmw+mml)+0.20) * 0.7071)*m1mod)/(sqrt(max(1,((nlayers*4)-4)))) / sqrt(par)'
+   mmcap    = agauss(0,1,3)
+   mmatc    = '1 + (m3sig * mmcap)'
*
**********VNCAP Subcircuit****************************************
 r1  in   1   r='max(0.001,fres)'     tc1=0.004 dtemp=dtemp
 l1  1    2   l='max(1e-20,indval)'             dtemp=dtemp	
 c   2    3   pricap                            
 r2  3    out r='max(0.001,fres)'     tc1=0.004 dtemp=dtemp
 c1  1    4   c='max(0.01f,(csx*est))'          dtemp=dtemp
 c2  3    4   c='max(0.01f,(csx*est))'          dtemp=dtemp
 r3  4    ref r='rsx'        		        dtemp=dtemp

.model pricap c
+  cap = 'capxtot*mmatc'
+  vc1 = 'vncapvc1'
+  vc2 = 'vncapvc2'


.ends vncap_hv

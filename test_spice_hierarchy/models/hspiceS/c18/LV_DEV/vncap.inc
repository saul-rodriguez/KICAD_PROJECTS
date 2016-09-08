* Path, Component, Release: cmos7base/rel/HSPICE/models/vncap.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  vncap           VNCAP Capacitor
*
***********************************************************************
*
* The model is comprised of a capacitor and series resistances and inductance.
* The input (lower plate) has losses to substrate characterized by capacitors
* and series resistor.
*
*            r1         c       |------|        r2
*                      | |      |  l1  |     
*  o ------/\  /\------| |------|      |------/\  /\-----o
* in    |    \/        | |      |------|        \/    |  out
*       |                                             |
*     -----                                         ------
*     -----  c1                               c2    ------
*       |                                             |
*       |                                             |
*       -----------o-----o-----o-----------------------
*                  |           |
*                  \           |
*                  / Rsub    ----- Csub
*                  \         ----- 
*                  |           |
*         o--------o-----------o--------o
*                     reference
*                       plane
*
***********************************************************************
*
*  DIMENSIONS: 
*              w --> desired width.
*
*              l --> length of the VNCAP.
*
*  SYNTAX:     Specify both length and width:
*              xxx  in out ref  vncap (l=100u w=100u botlev=1 toplev=5)
*
*  OPTIONAL:   
*              botlev  --> Indicates the lowest thin metal level of the VNCAP.
*                          Possible values are 1,2,3,4,5 or 6 for both the AM/ML
*                          or DM(MA) BEOL options. Default value = 1.
*
*              toplev  --> Indicates the top thin metal level of the VNCAP.
*                          Possible values are 1,2,3,4,5 or 6 for both the
*                          AM/ML or DM(MA) BEOL options.
*                          Default value = 4. 
*
*              setind  --> User determined value for the parasitic inductance.
*                          The default value of -2, which is used as a switch,
*                          forces the calculated inductance to be used.
*
*              est     --> Include estimated bottom plate to substrate
*                          capacitance (default, est=1). Turn
*                          switch off (est=0) for extracted layout.
*
*              rsx     --> Substrate resistance, default = -1
*                          -1 = model estimate based on groundplane, substrate options
*                           0 = substrate model (sxmodel) to be placed by user
*                          >0 = user-defined value
*
*              bp      --> Specify groundplane, bp=3 (SX), default
*                                               bp=2 (BB), bp=1 (NW)
*                                               bp=-5 (High Res, 7RF only)
*
*	       par     --> Device multiplicity 
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
***********************************************************************
.subckt vncap  in out ref  w=100u l=100u botlev=1 toplev=4 nlev=4 lm=1 est=1 setind=-2 dtemp=0 rsx=-1 bp=3 par=1
*
**********************************
+      mwx0  = '0.36u'		$ Metal finger width
+      mwx1  = '0.36u+delm1'	$ M1
+      mwx2  = '0.36u+delm2'	$ M2
+      mwx3  = '0.36u+delm3'	$ M3
+      mwx4  = '0.36u+delm4'	$ M4
+      mwx5  = '0.36u+delm5'	$ M5
+      mwx6  = '0.36u+delmt'	$ MT
+      mspx0 = '0.32u'		$ Metal finger spacing
+      mspx1 = '0.32u-delm1'  	$ M1
+      mspx2 = '0.32u-delm2'  	$ M2
+      mspx3 = '0.32u-delm3'  	$ M3
+      mspx4 = '0.32u-delm4'  	$ M4
+      mspx5 = '0.32u-delm5'  	$ M5
+      mspx6 = '0.32u-delmt'  	$ MT
+      mwtab = '1.00u'		$ Tab width
+      mdend = '0.40u'		$ Distance from finger end to tab
******************************************************************
* Determine the total number of fingers from the width
+    fingtot = '(int(((w-((2*mwx0)+mspx0))/(2*(mwx0+mspx0)))+1e-5)*2)+2'
* Calculate fingers per plate.  Each plate has to have the same number 
* of fingers. Thus an even number of total fingers, the int function
* prevents fractional finger in case this rule was somehow violated
+       fing = 'int(fingtot/2)'
* Determine the actual finger lengths, common run length
+       lfng = 'l-2*mwtab-2*mdend'
* Determine number of vias present for each finger
+       viax = 'int((lfng-1.32u)/1.12u)+1'
*
************* Logic Calculations ****************************
******************************************************************
* VNCAP capacitance it has a length component and an end component
* First, figure out which levels are being used.
* Note how the following variables work:  If botlev=2 and toplev=5
* then b2t2=b2t3=b2t4=b2t5=1, all others =0. but
* tb2t5=1, all others =0.
******************************************************************
+       b1t1 = '(botlev == 1)*(toplev >= 1)'
+       b1t2 = '(botlev == 1)*(toplev >= 2)'
+       b1t3 = '(botlev == 1)*(toplev >= 3)'
+       b1t4 = '(botlev == 1)*(toplev >= 4)'
+       b1t5 = '(botlev == 1)*(toplev >= 5)'
+       b1t6 = '(botlev == 1)*(toplev == 6)'
+       b2t2 = '(botlev == 2)*(toplev >= 2)'
+       b2t3 = '(botlev == 2)*(toplev >= 3)'
+       b2t4 = '(botlev == 2)*(toplev >= 4)'
+       b2t5 = '(botlev == 2)*(toplev >= 5)'
+       b2t6 = '(botlev == 2)*(toplev == 6)'
+       b3t3 = '(botlev == 3)*(toplev >= 3)'
+       b3t4 = '(botlev == 3)*(toplev >= 4)'
+       b3t5 = '(botlev == 3)*(toplev >= 5)'
+       b3t6 = '(botlev == 3)*(toplev == 6)'
+       b4t4 = '(botlev == 4)*(toplev >= 4)'
+       b4t5 = '(botlev == 4)*(toplev >= 5)'
+       b4t6 = '(botlev == 4)*(toplev == 6)'
+       b5t5 = '(botlev == 5)*(toplev >= 5)'
+       b5t6 = '(botlev == 5)*(toplev == 6)'
+       b6t6 = '(botlev == 6)*(toplev == 6)'
*
*** Define via levels that are present***********************
+      via1  = '(botlev == 1)*(toplev > 1)'
+      via2  = '(botlev <= 2)*(toplev > 2)'
+      via3  = '(botlev <= 3)*(toplev > 3)'
+      via4  = '(botlev <= 4)*(toplev > 4)'
+      via5  = '(botlev <= 5)*(toplev > 5)'
*
***** Define bottom and top plates***************************
+      tb1t1 = '(botlev == 1)*(toplev == 1)'
+      tb1t2 = '(botlev == 1)*(toplev == 2)'
+      tb1t3 = '(botlev == 1)*(toplev == 3)'
+      tb1t4 = '(botlev == 1)*(toplev == 4)'
+      tb1t5 = '(botlev == 1)*(toplev == 5)'
+      tb1t6 = '(botlev == 1)*(toplev == 6)'
+      tb2t2 = '(botlev == 2)*(toplev == 2)'
+      tb2t3 = '(botlev == 2)*(toplev == 3)'
+      tb2t4 = '(botlev == 2)*(toplev == 4)'
+      tb2t5 = '(botlev == 2)*(toplev == 5)'
+      tb2t6 = '(botlev == 2)*(toplev == 6)'
+      tb3t3 = '(botlev == 3)*(toplev == 3)'
+      tb3t4 = '(botlev == 3)*(toplev == 4)'
+      tb3t5 = '(botlev == 3)*(toplev == 5)'
+      tb3t6 = '(botlev == 3)*(toplev == 6)'
+      tb4t4 = '(botlev == 4)*(toplev == 4)'
+      tb4t5 = '(botlev == 4)*(toplev == 5)'
+      tb4t6 = '(botlev == 4)*(toplev == 6)'
+      tb5t5 = '(botlev == 5)*(toplev == 5)'
+      tb5t6 = '(botlev == 5)*(toplev == 6)'
+      tb6t6 = '(botlev == 6)*(toplev == 6)'
*****************************************************************
* Define rough estimate of relative dielectric constant
+        er1 = '7.547'
+        er2 = '7.236'
+        er3 = '7.236'
+        er4 = '7.236'
+        er5 = '7.236'
+        er6 = '7.236'
*****************************************************************
* Define finger to finger capacitance where vias are not present (F/m)
****************************************************************
* Calculate fringe scaled length for each finger length
+ fingercfx1 = '0.981246'
+  fingercfx = '1.098746'
+      cb1t1 = '(m1tv*e0*er1*fingercfx1/mspx1)'
+      cb1t2 = '(m2t*e0*er2*fingercfx/mspx2)'
+      cb1t3 = '(m3t*e0*er3*fingercfx/mspx3)'
+      cb1t4 = '(m4t*e0*er4*fingercfx/mspx4)'
+      cb1t5 = '(m5t*e0*er5*fingercfx/mspx5)'
+      cb1t6 = '(mtt*e0*er6*fingercfx/mspx6)'
+      cb2t2 = '(m2t*e0*er2*fingercfx/mspx2)'
+      cb2t3 = '(m3t*e0*er3*fingercfx/mspx3)'
+      cb2t4 = '(m4t*e0*er4*fingercfx/mspx4)'
+      cb2t5 = '(m5t*e0*er5*fingercfx/mspx5)'
+      cb2t6 = '(mtt*e0*er6*fingercfx/mspx6)'
+      cb3t3 = '(m3t*e0*er3*fingercfx/mspx3)'
+      cb3t4 = '(m4t*e0*er4*fingercfx/mspx4)'
+      cb3t5 = '(m5t*e0*er5*fingercfx/mspx5)'
+      cb3t6 = '(mtt*e0*er6*fingercfx/mspx6)'
+      cb4t4 = '(m4t*e0*er4*fingercfx/mspx4)'
+      cb4t5 = '(m5t*e0*er5*fingercfx/mspx5)'
+      cb4t6 = '(mtt*e0*er6*fingercfx/mspx6)'
+      cb5t5 = '(m5t*e0*er5*fingercfx/mspx5)'
+      cb5t6 = '(mtt*e0*er6*fingercfx/mspx6)'
+      cb6t6 = '(mtt*e0*er6*fingercfx/mspx6)'
**************************************************************************
* Define additive finger to finger capacitance where vias are present (F/m)
**************************************************************************
* Calculate fringe scaling for each via
+     viacf1 = '0.5'
+     viacf2 = '2.5'
+     viacf3 = '2.5'
+     viacf4 = '2.5'
+     viacf5 = '2.5'
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
+    endcfx1 = '0.996879'
+     endcfx = '1.016776'
+      cwan1 = '(2/pi)*((mspx1/mdend)*atan(1/(mspx1/mdend)) + atan(mspx1/mdend)/(mspx1/mdend) + log(4*((mspx1/mdend)**2 + 1)/(mspx1/mdend)))'
+      cwan2 = '(2/pi)*((mspx2/mdend)*atan(1/(mspx2/mdend)) + atan(mspx2/mdend)/(mspx2/mdend) + log(4*((mspx2/mdend)**2 + 1)/(mspx2/mdend)))'
+      cwan3 = '(2/pi)*((mspx3/mdend)*atan(1/(mspx3/mdend)) + atan(mspx3/mdend)/(mspx3/mdend) + log(4*((mspx3/mdend)**2 + 1)/(mspx3/mdend)))'
+      cwan4 = '(2/pi)*((mspx4/mdend)*atan(1/(mspx4/mdend)) + atan(mspx4/mdend)/(mspx4/mdend) + log(4*((mspx4/mdend)**2 + 1)/(mspx4/mdend)))'
+      cwan5 = '(2/pi)*((mspx5/mdend)*atan(1/(mspx5/mdend)) + atan(mspx5/mdend)/(mspx5/mdend) + log(4*((mspx5/mdend)**2 + 1)/(mspx5/mdend)))'
+      cwan6 = '(2/pi)*((mspx6/mdend)*atan(1/(mspx6/mdend)) + atan(mspx6/mdend)/(mspx6/mdend) + log(4*((mspx6/mdend)**2 + 1)/(mspx6/mdend)))'
* Calculate capacitance per finger end
+     ecb1t1 = 'm1tv*e0*er1*endcfx1*(mwx1/mdend + 2*cwan1)'
+     ecb1t2 = 'm2t*e0*er2*endcfx*(mwx2/mdend + 2*cwan2)'
+     ecb1t3 = 'm3t*e0*er3*endcfx*(mwx3/mdend + 2*cwan3)'
+     ecb1t4 = 'm4t*e0*er4*endcfx*(mwx4/mdend + 2*cwan4)'
+     ecb1t5 = 'm5t*e0*er5*endcfx*(mwx5/mdend + 2*cwan5)'
+     ecb1t6 = 'mtt*e0*er6*endcfx*(mwx6/mdend + 2*cwan6)'
+     ecb2t2 = 'm2t*e0*er2*endcfx*(mwx2/mdend + 2*cwan2)'
+     ecb2t3 = 'm3t*e0*er3*endcfx*(mwx3/mdend + 2*cwan3)'
+     ecb2t4 = 'm4t*e0*er4*endcfx*(mwx4/mdend + 2*cwan4)'
+     ecb2t5 = 'm5t*e0*er5*endcfx*(mwx5/mdend + 2*cwan5)'
+     ecb2t6 = 'mtt*e0*er6*endcfx*(mwx6/mdend + 2*cwan6)'
+     ecb3t3 = 'm3t*e0*er3*endcfx*(mwx3/mdend + 2*cwan3)'
+     ecb3t4 = 'm4t*e0*er4*endcfx*(mwx4/mdend + 2*cwan4)'
+     ecb3t5 = 'm5t*e0*er5*endcfx*(mwx5/mdend + 2*cwan5)'
+     ecb3t6 = 'mtt*e0*er6*endcfx*(mwx6/mdend + 2*cwan6)'
+     ecb4t4 = 'm4t*e0*er4*endcfx*(mwx4/mdend + 2*cwan4)'
+     ecb4t5 = 'm5t*e0*er5*endcfx*(mwx5/mdend + 2*cwan5)'
+     ecb4t6 = 'mtt*e0*er6*endcfx*(mwx6/mdend + 2*cwan6)'
+     ecb5t5 = 'm5t*e0*er5*endcfx*(mwx5/mdend + 2*cwan5)'
+     ecb5t6 = 'mtt*e0*er6*endcfx*(mwx6/mdend + 2*cwan6)'
+     ecb6t6 = 'mtt*e0*er6*endcfx*(mwx6/mdend + 2*cwan6)'
*
******************************************************************
* Calculate end and length components of capacitance for thin levels
* and accumulate.
******************************************************************
*
**** Capacitance per unit length for portion of finger with no vias
+   capxlnv1 = 'b1t1*cb1t1+b1t2*cb1t2+b1t3*cb1t3+b1t4*cb1t4+b1t5*cb1t5+b1t6*cb1t6+b2t2*cb2t2'
+   capxlnv2 = 'b2t3*cb2t3+b2t4*cb2t4+b2t5*cb2t5+b2t6*cb2t6+b3t3*cb3t3+b3t4*cb3t4+b3t5*cb3t5'
+   capxlnv3 = 'b3t6*cb3t6+b4t4*cb4t4+b4t5*cb4t5+b4t6*cb4t6+b5t5*cb5t5+b5t6*cb5t6+b6t6*cb6t6'
+   capxlnv  = 'capxlnv1+capxlnv2+capxlnv3'
**** Add in capacitance per unit length due to vias
+    capxlv  = 'via1*capvia1+via2*capvia2+via3*capvia3+via4*capvia4+via5*capvia5'
*
**** Capacitance of end component per finger
+     capxe1 = 'b1t1*ecb1t1+b1t2*ecb1t2+b1t3*ecb1t3+b1t4*ecb1t4+b1t5*ecb1t5+b1t6*ecb1t6+b2t2*ecb2t2'
+     capxe2 = 'b2t3*ecb2t3+b2t4*ecb2t4+b2t5*ecb2t5+b2t6*ecb2t6+b3t3*ecb3t3+b3t4*ecb3t4+b3t5*ecb3t5'
+     capxe3 = 'b3t6*ecb3t6+b4t4*ecb4t4+b4t5*ecb4t5+b4t6*ecb4t6+b5t5*ecb5t5+b5t6*ecb5t6+b6t6*ecb6t6'
+     capxe  = 'capxe1+capxe2+capxe3'
*
**** Calculate capacitances for each portion of finger
+    capxnv  = 'lfng*capxlnv*(fingtot-1)'
+    capxv   = 'viax*.28u*capxlv*(fingtot-1)'
* Two outermost fingers have 1/2 of the end capacitance of inner fingers
+    capxet  = '(fingtot-1)*capxe'
+    capxtot = 'capxnv+capxv+capxet'
******************************************************************
* VNCAP resistance has a length component.  Define it for each level.
* r1-re are in ohms/m.
******************************************************************
+         r1 = '(m1tvn/m1tv)*(m1rsv/mwx0)/(mwx1/mwx0)'
+         r2 = '(m2tn/m2t)*(m2rs/mwx0)/(mwx2/mwx0)'
+         r3 = '(m3tn/m3t)*(m3rs/mwx0)/(mwx3/mwx0)'
+         r4 = '(m4tn/m4t)*(m4rs/mwx0)/(mwx4/mwx0)'
+         r5 = '(m5tn/m5t)*(m5rs/mwx0)/(mwx5/mwx0)'
+         r6 = '(mttn/mtt)*(mtrs/mwx0)/(mwx6/mwx0)'
*****************************************************************************
* Resistance scaling from presence of vias up this level
* (from EMSIM simulations). The vias contribute very little 
* reduction in resistance due to the current flow being primarily
* in a lateral direction through the fingers.
*****************************************************************************
+     vscale = '0.95'
******************************************************************
* VNCAP resistance has a length component.  Each finger is a bunch
* of wires in parallel, with the vias providing a little
* reduction in resistance.
******************************************************************
+      rb1t1 = 'r1'
+      rb1t2 = 'rb1t1*r2*vscale/(rb1t1+r2*vscale)'
+      rb1t3 = 'rb1t2*r3*vscale/(rb1t2+r3*vscale)'
+      rb1t4 = 'rb1t3*r4*vscale/(rb1t3+r4*vscale)'
+      rb1t5 = 'rb1t4*r5*vscale/(rb1t4+r5*vscale)'
+      rb1t6 = 'rb1t5*r6*vscale/(rb1t5+r6*vscale)'
+      rb2t2 = 'r2'
+      rb2t3 = 'rb2t2*r3*vscale/(rb2t2+r3*vscale)'
+      rb2t4 = 'rb2t3*r4*vscale/(rb2t3+r4*vscale)'
+      rb2t5 = 'rb2t4*r5*vscale/(rb2t4+r5*vscale)'
+      rb2t6 = 'rb2t5*r6*vscale/(rb2t5+r6*vscale)'
+      rb3t3 = 'r3'
+      rb3t4 = 'rb3t3*r4*vscale/(rb3t3+r4*vscale)'
+      rb3t5 = 'rb3t4*r5*vscale/(rb3t4+r5*vscale)'
+      rb3t6 = 'rb3t5*r6*vscale/(rb3t5+r6*vscale)'
+      rb4t4 = 'r4'
+      rb4t5 = 'rb4t4*r5*vscale/(rb4t4+r5*vscale)'
+      rb4t6 = 'rb4t5*r6*vscale/(rb4t5+r6*vscale)'
+      rb5t5 = 'r5'
+      rb5t6 = 'rb5t5*r6*vscale/(rb5t5+r6*vscale)'
+      rb6t6 = 'r6'
******************************************************************
* resistance per finger (ohms).  Notice that we are switching 
* to the tb1t5 type variables now.
******************************************************************
+     fres1  = 'tb1t1*rb1t1+tb1t2*rb1t2+tb1t3*rb1t3+tb1t4*rb1t4+tb1t5*rb1t5+tb1t6*rb1t6'
+     fres2  = 'tb2t2*rb2t2+tb2t3*rb2t3+tb2t4*rb2t4+tb2t5*rb2t5+tb2t6*rb2t6'
+     fres3  = 'tb3t3*rb3t3+tb3t4*rb3t4+tb3t5*rb3t5+tb3t6*rb3t6'
+     fres4  = 'tb4t4*rb4t4+tb4t5*rb4t5+tb4t6*rb4t6'
+     fres5  = 'tb5t5*rb5t5+tb5t6*rb5t6'
+     fres6  = 'tb6t6*rb6t6'
+     fresxl = 'fres1+fres2+fres3+fres4+fres5+fres6'
******************************************************************
* Now the resistance of the bar that connects the fingers.
* The finger resistance is scaled by the proper ratio
* Ex, if the tab width is 2.8u and the finger width is .28u then
* the resistance per unit length of the tab is 1/10 that of a finger
******************************************************************
+     rbb1t1 = 'rb1t1/(mwtab/mwx1)'
+     rbb1t2 = 'rb1t2/(mwtab/mwx2)'
+     rbb1t3 = 'rb1t3/(mwtab/mwx3)'
+     rbb1t4 = 'rb1t4/(mwtab/mwx4)'
+     rbb1t5 = 'rb1t5/(mwtab/mwx5)'
+     rbb1t6 = 'rb1t6/(mwtab/mwx6)'
+     rbb2t2 = 'rb2t2/(mwtab/mwx2)'
+     rbb2t3 = 'rb2t3/(mwtab/mwx3)'
+     rbb2t4 = 'rb2t4/(mwtab/mwx4)'
+     rbb2t5 = 'rb2t5/(mwtab/mwx5)'
+     rbb2t6 = 'rb2t6/(mwtab/mwx6)'
+     rbb3t3 = 'rb3t3/(mwtab/mwx3)'
+     rbb3t4 = 'rb3t4/(mwtab/mwx4)'
+     rbb3t5 = 'rb3t5/(mwtab/mwx5)'
+     rbb3t6 = 'rb3t6/(mwtab/mwx6)'
+     rbb4t4 = 'rb4t4/(mwtab/mwx4)'
+     rbb4t5 = 'rb4t5/(mwtab/mwx5)'
+     rbb4t6 = 'rb4t6/(mwtab/mwx6)'
+     rbb5t5 = 'rb5t5/(mwtab/mwx5)'
+     rbb5t6 = 'rb5t6/(mwtab/mwx6)'
+     rbb6t6 = 'rb6t6/(mwtab/mwx6)'
******************************************************************
* resistance per bar.
* This expression comes from EMSIM simulations where the connection
* to the bar is in the center of the bar.
******************************************************************
+     bres1  = 'tb1t1*rbb1t1+tb1t2*rbb1t2+tb1t3*rbb1t3+tb1t4*rbb1t4+tb1t5*rbb1t5+tb1t6*rbb1t6'
+     bres2  = 'tb2t2*rbb2t2+tb2t3*rbb2t3+tb2t4*rbb2t4+tb2t5*rbb2t5+tb2t6*rbb2t6'
+     bres3  = 'tb3t3*rbb3t3+tb3t4*rbb3t4+tb3t5*rbb3t5+tb3t6*rbb3t6'
+     bres4  = 'tb4t4*rbb4t4+tb4t5*rbb4t5+tb4t6*rbb4t6'
+     bres5  = 'tb5t5*rbb5t5+tb5t6*rbb5t6'
+     bres6  = 'tb6t6*rbb6t6'
+     bresxl = 'bres1+bres2+bres3+bres4+bres5+bres6'
+     rbarx  = 'bresxl*w/5'
*
******************************************************************
* There is '2' in the fres calculation because we are splitting
* fres up between the two sets of fingers.
******************************************************************
+      fres  = 'fresxl*lfng/(2*1.5*fing)+rbarx/2'
******************************************************************
* Inductance per finger: use the Grover formula with the wire
* length and width values obtained by adding finger widths and 
* lengths.  First define the effective thicknesses based on the
* metal levels used.
******************************************************************
+      windx = '2*fing*mwx0'
+     tindx1 = 'b1t1*m1tv+b1t2*m2t+b1t3*m3t+b1t4*m4t+b1t5*m5t+b1t6*mtt+b2t2*m2t'
+     tindx2 = 'b2t3*m3t+b2t4*m4t+b2t5*m5t+b2t6*mtt+b3t3*m3t+b3t4*m4t+b3t5*m5t'
+     tindx3 = 'b3t6*mtt+b4t4*m4t+b4t5*m5t+b4t6*mtt+b5t5*m5t+b5t6*mtt+b6t6*mtt'
+     tindx  = 'tindx1+tindx2+tindx3'
******************************************************************
* Grover's formula, suitably scaled (based on EMSIM simulations)
******************************************************************
+     ratx   = '2*lfng/(windx+tindx)'
+     findx = '(l*2e-7)*(log(ratx)+0.498)'
+     plind  = 'findx/2'
* Check to see if the user has overridden the inductance value
+    indval  = '(setind!=-2)*setind + (setind==-2)*(plind)'
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
+      botwx = 'mwx1*bot1+mwx2*bot2+mwx3*bot3+mwx4*bot4+mwx5*bot5+mwx6*bot6'
* Calculate the area of the fingers
+      farea = '2*lfng*(fing*botwx)'
* Calculate area of tabs
+      barea = '2*(mwtab+bdelw)*w'
*
* Calculate thickness of dielectric below each metal layer
* 45pct of VNCAP groundplane area is PC and 45pct is RX.  The rest is over STI
+    m1thkn  = 'oppcstif+oppcthk+capcti'
+    m1thk   = 'm1thkn-(.25*oppcthk)-(.45*oppcstif)'
+    m2thk   = 'm1thk+m1tv+m1m2t'
+    m3thk   = 'm2thk+m2t+m2m3t'
+    m4thk   = 'm3thk+m3t+m3m4t'
+    m5thk   = 'm4thk+m4t+m4m5t'
+    m6thk   = 'm5thk+m5t+mxmtt'
* Calculate effective dielectric height
+    heffec  = 'bot1*m1thk+bot2*m2thk+bot3*m3thk+bot4*m4thk+bot5*m5thk+bot6*m6thk'
* Total area
+      tarea = 'farea+barea'
* Area term of parasitic capacitance
+      carea = 'eoxdepo*e0*tarea/heffec'
*
*****************************************************************
*Perimeter term of capacitance to substrate
*****************************************************************
* Total perimeter
+     tperim = '2*((l+bdelw)+(w+bdelw))'
+       weff = 'fingtot*(mwx0+bdelw)'
+       htop = 'top1*m1thk+top2*m2thk+top3*m3thk+top4*m4thk+top5*m5thk+top6*m6thk'
+       mtop = 'top1*m1tv+top2*m2t+top3*m3t+top4*m4t+top5*m5t+top6*mtt'
*
* Calculate the singularity term of the fringe capacitance
+  csingp    = 'eoxdepo*e0*(2/(pi-2)*log(pi/2))'
*
* Calculate the terms of the top plate
+  ctopedgp  = 'eoxdepo*e0*(2/pi)*log(1+mtop/htop)'        $ edge term
+  ctoplp    = 'eoxdepo*e0*log(1+(weff/(htop+mtop)))'      $ top length term
+  ctopwp    = 'eoxdepo*e0*log(1+((l+bdelw)/(htop+mtop)))' $ top width  term
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
+  cperim    = '2*(w+bdelw)*ctopwp + 2*(l+bdelw)*ctoplp + tperim*(csingp+ctopedgp+clowerp)'
* Calculate total parasitic cap, divide by 2 for distrib
+     csx    = '(cperim+carea)/2'
*
*****************************************************************
* Substrate resistance and capacitance calculations
*****************************************************************
+ ptnw = '(bp==1)'
+ ptbb = '(bp==2)'
+ ptsx = '(bp==3)'
+ pthr = '(bp==-5)'
+ prsx = '((ptnw+ptsx)*50 + ptbb*500 + pthr*5000)*(rsx==-1) + 1m*(rsx==0) + rsx*(rsx>0)'
+ prho = '(ptnw+ptsx)*rsub + ptbb*rsubbb + pthr*rsubhr'
+ pcsx = '(e0*ersi*prho)/prsx'
*
******************************************************************
* Temperature calculation
+ m1on    = '.095*(botlev==1)'
+ m2on    = '.141*((b1t2+b1t3+b1t4+b1t5+b1t6+b2t2+b2t3+b2t4+b2t5+b2t6)>0)'
+ m3on    = '.141*((b1t3+b1t4+b1t5+b1t6+b2t3+b2t4+b2t5+b2t6+b3t3+b3t4+b3t5+b3t6)>0)'
+ m4on    = '.141*((b1t4+b1t5+b1t6+b2t4+b2t5+b2t6+b3t4+b3t5+b3t6+b4t4+b4t5+b4t6)>0)'
+ m5on    = '.141*((b1t5+b1t6+b2t5+b2t6+b3t5+b3t6+b4t5+b4t6+b5t5+b5t6)>0)'
+ m6on    = '.141*((b1t6+b2t6+b3t6+b4t6+b5t6+b6t6)>0)'
+ denom   = 'm1on+m2on+m3on+m4on+m5on+m6on'
+ ptcc    = '((-2.5e-5*m1on)+(-6.9e-5*(m2on+m3on+m4on+m5on+m6on)))/denom'
*
*****************************************************************
* Mis-match Calculation
+   mma = '(82.43) / (w*l * 1e12)'
+   mmw = '(0) / (w*w * 1e12)'
+   mml = '(0) / (l*l * 1e12)'
+ m1mod = '1+((-0.38*(1/((toplev-botlev)+1)))*((b1t1+b1t2+b1t3+b1t4+b1t5+b1t6)>0))'
+ m3sig = '((0.01 * (sqrt(mma+mmw+mml)+0.138) * 0.7071)*m1mod)/(sqrt(max(1,((((toplev-botlev)+1)*4)-4))))/sqrt(par)'
+ mmcap = agauss(0,1,3)
+ mmatc = '1 + (m3sig * mmcap)'
*
**********VNCAP Subcircuit****************************************
 r1  in   1   r='max(0.001,fres)'       tc1=0.004    dtemp=dtemp
 l1  1    2   l=indval           		     dtemp=dtemp	
 c   2    3   c='capxtot*mmatc'         tc1=ptcc     dtemp=dtemp
 r2  3    out r='max(0.001,fres)'       tc1=0.004    dtemp=dtemp
 c1  1    4   c='max(0.01f,(csx*est))'               dtemp=dtemp
 c2  3    4   c='max(0.01f,(csx*est))'               dtemp=dtemp
 rsb 4    ref r=prsx         		             dtemp=dtemp
 csb 4    ref c=pcsx         		             dtemp=dtemp

.ends vncap

* Path, Component, Release: cmrf7sf/rel/HSPICE/models/dindpw.inc, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 2.0
*
*>  CMRF7SF  dindpw   Bipolar Junction Transistor Model for N/isoPW Forward Bias Diode
*
*******************************************************************************
*
* SYNTAX: xxx ( tw pw nd sx) dindpw   <- Default:  2.5u base width, 1 x 1 emitter
*         +        w = 1.6u    <- Width of the emitter                        
*         +        l = 10.0u   <- Length of the emitter             
*         +       nf = 1       <- Number of emitter fingers
*         +      par = 1       <- Explicit Multiplicity     
*         +    dtemp = 0       <- Device temp rise from ambient (deg C)
*
* SUBCIRCUIT SCHEMATIC:
*                                    O e
*                                    |               
*                                    |               
*                                    |               
*                                 | /                
*   b                             |/            
*  O------------------------------|        
*                                 |\                       
*                                q| \                
*                                    |               
*                                    |
*                                    |
*                                    O c
*                                                                             
*
*******************************************************************************
.subckt dindpw  (tw pw nd sx)  w=1.6u l=10u nf=1 par=1 dtemp=0
*
.param
*---- Drawn Geometry ----------------------------------------------------------
+      wpic = 0.60u                              $ Triple well contact width
+      wpwc = 0.60u                              $ Pwell contact width
+     e2pwc = 0.38u                              $ Emit to Pwell contact space
+   pwc2pic = 0.76u                              $ Pwell to Triple well contact space
+     e2pic = 1.74u                              $ Emit to Triple well contact space
+     e2pwe = 1.32u                              $ Emit to Pwell edge
+       wpw = 'w*nf + 2*(nf-1)*e2pwc + (nf-1)*wpwc + 2*e2pwe' $ Pwell width
+       lpw = 'l+2*e2pwe'                          $ Pwell length
*
*---- Drawn Geometry + Mask Bias ----------------------------------------------
+      wex = 'w + tdelrx'                           $ Emit width
+      lex = 'l + tdelrx'                           $ Emit length
+     wpwx = 'wpw - delnw'                         $ Pwell width
+     lpwx = 'lpw - delnw'                         $ Pwell length
*
*---- Effective Area, Perimeter Dimensions ------------------------------------
+     areae = 'wex*lex*nf'                         $ Total emit area
+    perime = '2*(wex+lex)*nf'                     $ Total emit perim
+     aeout = 'wex*lex + 0.5*wex*wex*(nf-1)'
+      aein = 'areae - aeout'
+     peout = '2*(lex + wex*nf)'
+      pein = 'perime - peout'
+    areapw = 'wpwx*lpwx'                          $ Total base area
+   perimpw = '2*(wpwx+lpwx)'                      $ Total base perim
*
*---- Current Gain Parameters (Gummel Poon) -----------------------------------
*     This divides up the emitter-base current into area and perimeter 
*     contributions (fracr) and the portions on the exterior and interior 
*     (fracp and fraca).  The coefficients give the portion of emitter current
*     from each of these contributions that exits the device through the base
*     
+     xaout = xaout_dipi
+      xain = xain_dipi
+     xpout = xpout_dipi
+      xpin = xpin_dipi
+   totcurr = 'aeout*jso_dipi + aein*jsi_dipi + peout*jswo_dipi + pein*jswi_dipi'
+    ibcurr = 'xaout*aeout*jso_dipi +xain*aein*jsi_dipi + xpout*peout*jswo_dipi + xpin*pein*jswi_dipi'
+  iboverie = 'ibcurr/totcurr'
+       pbf = '(1.0/iboverie) - 1.0'               $ forward beta
+  iboveric = 0.99
+       pbr = '(1.0/iboveric) - 1.0'               $ reverse beta
*
*---- Emission Coefficients ---------------------------------------------------
+       pnf = n_n                              $ fwd emission
+       pnr = n_n                              $ rev emission
+      pnen = 2.0                               $ BE, non-ideal emission leakage
+      pncn = 2.0                                $ BC, non-ideal emission leakage
*
*---- VPNP Saturation Currents ------------------------------------------------
+      pibe = 'totcurr*(1-iboverie)'              $ BE, non-ideal
+      pibc = '(js_pwi*areapw + jsw_pwi*perimpw)*(1-iboveric)' $ BC, non-ideal
+      pise = '550e-6*areae'                       $ BE leakage saturation current
+      pisc = 0                                  $ BC leakage saturation current
*
*---- Knee Currents -----------------------------------------------------------
+      pikf = 0
+      pikr = 0
*
*---- Early Voltages ----------------------------------------------------------
+      pvef = 400                                $ fwd early
+      pver = 0                                  $ rev early
*
*---- Emitter Resistance ------------------------------------------------------
+       pre = '100p/areae + m1rs*(l+2*e2pwe)/((w-0.8u)*nf)'  $ emit res
*
*---- Collector Resistance ----------------------------------------------------
+      weff = 'min(wpw,lpw)'
+      leff = 'max(wpw,lpw)'
+      wcon = 'weff+2*pwc2pic'
+      lcon = 'leff+2*pwc2pic'
+      rundr = 'nwrs*weff/(12*leff + 20*weff)'
+      rtrap = '(nwrs/4)*log(wcon/weff)*log(lcon/leff)/(log(wcon/weff)+log(lcon/leff))'
+      rucon = 'nwrs*wpic/(6*(wcon+lcon))'
+      rvert = 'nrnw/(2*(wcon+lcon)*wpic)'                   
+        prc = 'rundr + rtrap + rucon + rvert'                         
*
*---- Base Resistance ---------------------------------------------------------
+      prpw = 0.52n
+      pwrs = 415
*
+       lbh = 'e2pwc' 
+       wbh = 'l + 2*e2pwc'
+     prbhe = 'pwrs*w/(12*l*nf)'
+      prbh = 'pwrs*lbh/(wbh*2*nf)'
+     prbhc = '(pwrs/(6*nf))*(wpwc/(l+2*e2pwc))'   
+      prbv = 'prpw/((l+2*e2pwc)*wpwc*(nf+1))'     
+      bmet = '(m1rs/(nf+1))*(l+2*e2pwe)/(0.42e-6)'
+       prb = '1.0*(prbhe + prbh + prbhc + prbv + bmet)'         
*
*---- Mis-match Calculation ----------------------------------------------------
+   dioma   = '17.0 * 17.0 / (wex * lex * nf * 1e12)'
*   dioml   = 'diml * diml / (lex * lex * nf * nf * 1e12)'
*   diomw   = 'dimw * dimw / (wex * wex * 1e12)'
+   dio3sig = '0.01 * sqrt(dioma)'
+   diomm   = 'dio3sig * 0.7071 / sqrt(par)'
+    mmdio  = agauss(0,1,3)
+    mmatd  = '1 + (diomm * mmdio)'
*
*---- Base-Emitter Capacitance ------------------------------------------------
+      pcje = 'cj_n*areae + cjsw_n*perime'         $ base-emit capacitance
+      pvje = 0.6                                $ base-emit built-in potential
+      pmje = 0.4                               $ base-emit junction exponent
*
*---- Base-Coll Capacitance ---------------------------------------------------
+      pcjc = 'cj_pwi*areapw + cjsw_pwi*perimpw'     $ base-emit capacitance
+      pvjc = 0.7                                $ base-emit built-in potential
+      pmjc = 0.3                               $ base-emit junction exponent
*
*---- Current Limits ----------------------------------------------------------
+    pimelt = 10                                   $ explosion current
*
*---- VPNP Model --------------------------------------------------------------
q    tw pw nd  qdindpw  area=1  areab=1  dtemp=dtemp
xdsx sx tw  diodepisx area='(wpwx+1.1u)*(lpwx+1.1u)'  perim='2*((wpwx+1.1u)+(lpwx+1.1u))' dtemp=dtemp

.model qdindpw npn
+ level=1
+ tlev=2          
+ dcap=2          
+ tlevc=1
+ tref=25
+ subs=1
+ eg=1.12
+ xti=3.0
+ gap1=473u
+ gap2=636
+ xtb=0        
+ trb1=0.0038
+ trm1=0.0038
+ trc1=0.0038
+ ibe='pibe*mmatd*(1 + tdeldipi)'
+ ibc=pibc
+ ise=pise       
+ isc=pisc       
+ iss=0           
+ nf=pnf
+ nr=pnr 
+ ne=pnen
+ nc=pncn
+ ns=1            
+ bf=pbf
+ br=pbr
+ vaf=pvef       
+ var=pver       
+ re=pre
+ rb=prb
+ rc=prc
+ cje=pcje
+ vje=pvje
+ mje=pmje
+ cjc=pcjc
+ vjc=pvjc
+ mjc=pmjc
+ cjs=0           
+ xcjc=1     
+ expli=pimelt    

.ends dindpw

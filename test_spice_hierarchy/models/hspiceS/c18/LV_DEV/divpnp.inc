* Path, Component, Release: cmrf7sf/rel/HSPICE/models/divpnp.inc, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 2.0
*
*>  CMRF7SF  divpnp         Bipolar Junction Transistor Model for DI Diode
*
*******************************************************************************
*
* SYNTAX: xxx ( c b e ) divpnp   <- Default:  2.5u base width, 1 x 1 emitter
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
* PHYSICAL DEVICE LAYOUT:  (single emitter device)
*
*                |<-------------------wc------------------>|
*                                                                             
*                +-----------------------------------------+  -
*                |                                         |  |                 
*                |       |<-----------wb---------->|       |  |
*                |                                         |  |
*                |       +-------------------------+  -    |  | 
*                |       |                         |  A    |  | 
*                |       |       |<---w--->|       |  |    |  | 
*                |       |       +---------+  -    |  |    |  | 
*                |       |       |         |  A    |  |    |  | 
*                |       |       |         |  |    |  |    |  |lc
*                |       |       | Emitter |  |    |  |    |  |    
*                |       |       |         |  |    |  |    |  |  
*                |       |       |         |  |    |  |    |  | 
*                |       |       |         |  |    |  |lb  |  |  
*                |       |       |         |  |    |  |    |  |  
*                |       |       |         |  |l   |  |    |  |   
*                |       |       |         |  |    |  |    |  | 
*                |       |       |         |  |    |  |    |  |  
*                |       |       |         |  |    |  |    |  |  
*                |       |       |         |  |    |  |    |  |  
*                |       |       |         |  |    |  |    |  |  
*                |       |       |         |  V    |  |    |  |  
*                |       |       +---------+  -    |  |    |  |  
*                |       |                         |  |    |  |  
*                |       |           Base          |  V    |  |  
*                |       +-------------------------+  -    |  |  
*                |                                         |  |       
*                |                                         |  |       
*                |                 Collector               |  V  
*                +-----------------------------------------+  -   
*
*
*******************************************************************************
.subckt divpnp  c b e   w=1.6u  l=10u  nf=1  par=1  dtemp=0
*
.param
*---- Drawn Geometry ----------------------------------------------------------
+      wsxc = 0.60u                                $ Substrate contact width
+      wnwc = 0.60u                                $ Nwell contact width
+   nwc2sxc = 0.76u                                $ Nwell contact to Substrate contact space
+     e2nwc = 0.34u                                $ Emit to Nwell contact space
+     e2sxc = 1.70u                                $ Emit to Substrate contact space
+     e2nwe = 1.36u                                $ Emit to Nwell edge
+       wnw = 'w*nf + 2*(nf-1)*e2nwc + (nf-1)*wnwc + 2*e2nwe' $ Nwell width
+       lnw = 'l+2*e2nwe'                          $ Nwell length
*
*---- Drawn Geometry + Mask Bias ----------------------------------------------
+      wex = 'w + tdelrx'                          $ Emit width
+      lex = 'l + tdelrx'                          $ Emit length
+     wnwx = 'wnw + delnw'                         $ Nwell width
+     lnwx = 'lnw + delnw'                         $ Nwell length
*
*---- Effective Area, Perimeter Dimensions ------------------------------------
+     areae = 'wex*lex*nf'                         $ Total emit area
+    perime = '2*(wex+lex)*nf'                     $ Total emit perim
+    areanw = 'wnwx*lnwx'                          $ Total base area
+   perimnw = '2*(wnwx+lnwx)'                      $ Total base perim
*
*---- Current Gain Parameters (Gummel Poon) -----------------------------------
*     This divides up the emitter-base current into area and perimeter 
*     contributions (fracr) and the portions on the exterior and interior 
*     (fracp and fraca).  The coefficients give the portion of emitter current
*     from each of these contributions that exits the device through the base
*     
+     fracr = 'jsw_p*(lex+wex)/(js_p*lex*wex/2 + jsw_p*(lex+wex))'
+     fracp = '(lex+wex*nf)/((lex+wex)*nf)'
+     fraca = '(lex*wex+(nf-1)*wex*wex/2)/(lex*wex*nf)'
+     xaout = xaout_di
+      xain = xain_di
+     xpout = xpout_di
+      xpin = xpin_di
+  iboverie = 'xpout*fracp*fracr + xpin*(1-fracp)*fracr  + xaout*fraca*(1-fracr) + xain*(1-fraca)*(1-fracr)'
+       pbf = '(1.0/iboverie) - 1.0'               $ forward beta
*     This is a similar thing in dividing up the collector-base junction current
*     into area and perimter components (fracrc).  The coefficients give the
*     portion of each of these that flow out the base contact (nearly all).
+    fracrc = 'jsw_di*(lnwx+wnwx)/(js_di*lnwx*wnwx/2 + jsw_di*(lnwx+wnwx))'
+        yp = 1.00
+        ya = 0.99
+  iboveric = 'yp*fracrc +ya*(1-fracrc)'
+       pbr = '(1.0/iboveric) - 1.0'               $ reverse beta
*
*---- Emission Coefficients ---------------------------------------------------
+       pnf = 1.006                                $ fwd emission
+       pnr = 1.023                                $ rev emission
+      pnen = 2.0                                  $ BE, non-ideal emission leakage
+      pncn = 2.0                                  $ BC, non-ideal emission leakage
*
*---- VPNP Saturation Currents ------------------------------------------------
+      pibe = '(js_p*areae + jsw_p*perime)*(1-iboverie)' $ BE, non-ideal
+      pibc = '(js_di*areanw + jsw_di*perimnw)*(1-iboveric)' $ BC, non-ideal
+      pise = '18e-6*areae'                        $ BE leakage saturation current
+      pisc = 0                                    $ BC leakage saturation current
*
*---- Knee Currents -----------------------------------------------------------
+      pikf = '9.4e7*areae'
+      pikr = 0
*
*---- Early Voltages ----------------------------------------------------------
+      pvef = 400                                  $ fwd early
+      pver = 0                                    $ rev early
*
*---- Emitter Resistance ------------------------------------------------------
+       pre = '1p/areae + m1rs*(l+2*e2nwe)/(nf*1.0u)'         $ emit res
*
*---- Collector Resistance ----------------------------------------------------
+      prpw = 1.0n
+      pwrs = 315
*       lch = '(nf*w + (nf+1)*wnwc + wsxc)/2 + nf*e2nwc + nwc2sxc' 
*       wch = 'l + 2*e2sxc + wsxc/2'
*     wsxcx = 'wsxc+delrx'
*      wchd = 'min(wch,lch)'
*      lchd = 'max(wch,lch)'
*      difd = 'lchd-wchd'
*      rch1 = '(pwrs/4)'                           $ single triangle resistance
*      rch2 = '(pwrs/2)*((difd*difd*log((difd+1e-20)/lchd))/(wchd*(2*lchd-wchd))+1/2)'    $ single trapzoid resistance
*      prch = '(1/2)*((rch1*rch2)/(rch1 + rch2))'  $ coll horizontal res
*      prcv = 'prpw/((wch+lch+wsxc)*wsxcx*2)'      $ coll vertical res
*       prc = prcv                                 $ coll res
*
+      weff = 'min(wnw,lnw)'
+      leff = 'max(wnw,lnw)'
+      wcon = 'weff+2*nwc2sxc'
+      lcon = 'leff+2*nwc2sxc'
*      the resistance is divided up into four parts:
*      (1) rundr a parallel combination for under the anode 
*      (2) rtrap for the combination of trapezoids from Nwell to SX
*      (3) rucon for under the contact itself, and
*      (4) rvert for the vertical resistance up through contact
+      rundr = 'pwrs*weff/(12*leff + 20*weff)'
+      rtrap = '(pwrs/4)*log(wcon/weff)*log(lcon/leff)/(log(wcon/weff)+log(lcon/leff))'
+      rucon = 'pwrs*wsxc/(6*(wcon+lcon))'
+      rvert = 'prpw/(2*(wcon+lcon)*wsxc)'                   
+        prc = 'rundr + rtrap + rucon + rvert'                         
*
*---- Base Resistance ---------------------------------------------------------
*       lbh = '(w + wnwc)/2 + e2nwc' 
*       wbh = 'l + 2*e2nwc+ wnwc'
*      prbh = '(nwrs/(2*nf))*(lbh/wbh)'            $ coll horizontal res
*      prbv = 'nrnw/(wbh*wnwc*(nf+1))'             $ coll vertical res
*       prb = 'prbh + prbv'                        $ base res
*
+       lbh = e2nwc
+       wbh = 'l + 2*e2nwc'
+      prbh = '(nwrs/(2*nf))*log(wbh/l)/2'         
+     prbhc = '(nwrs/(6*nf))*(wnwc/(l+2*e2nwc))'   
+      prbv = 'nrnw/((l+2*e2nwc)*wnwc*(nf+1))'     
+      bmet = '(m1rs/(nf+1))*(l+2*e2nwe)/(0.42e-6)'
+       prb = '1.0*(prbh + prbhc + prbv + bmet)'         
*
*---- Base-Emitter Capacitance ------------------------------------------------
+      pcje = 'cj_p*areae + cjsw_p*perime'       $ base-emit capacitance
+      pvje = 0.8                                $ base-emit built-in potential
+      pmje = 0.33                               $ base-emit junction exponent
*
*---- Base-Coll Capacitance ---------------------------------------------------
+      pcjc = 'cj_di*areanw + cjsw_di*perimnw'   $ base-emit capacitance
+      pvjc = 0.6                                $ base-emit built-in potential
+      pmjc = 0.23                               $ base-emit junction exponent
*
*---- Transit Time & Excess Phase ---------------------------------------------
+       ptf = '2.017n - 2.7u*fracp*perime'       $ fwd transit
+       ptr = ptf                                $ rev transit time
+      pvtf = 1.0                                $ tf bias dependence on vbc
+      pitf = '7.5e15*pibe'                      $ tf bias dependence on ie
+      pxtf = 8                                  $ tf bias dependence coeff
+       pfc = 0.5
+      pptf = 2.5                                $ fwd excess phase multiplier
*
*---- Current Limits ----------------------------------------------------------
+    pimelt = 10                                 $ explosion current
*
*---- Mis-match Calculation ----------------------------------------------------
+   dioma   = '3.15 * 3.15 / (wex * lex * nf * 1e12)'
*   dioml   = 'diml * diml / (lex * lex * nf * nf * 1e12)'
+   diomw   = '0.525 * 0.525 / (wex * wex * 1e12)'
+   dio3sig = '0.01 * sqrt(dioma + diomw)'
+   diomm   = 'dio3sig * 0.7071 / sqrt(par)'
+    mmdio  = agauss(0,1,3)
+    mmatd  = '1 + (diomm * mmdio)'
*
*---- VPNP Model --------------------------------------------------------------
q     c b e  qdipdnw  area=1  areab=1  dtemp=dtemp

.model qdipdnw pnp
+ level=1
+ tlev=2          
+ dcap=1          
+ tlevc=1
+ tref=25
+ subs=1
+ eg=1.12
+ xti=3.0
+ gap1=473u
+ gap2=636
+ xtb=0        
+ trb1=tnwrs
+ trm1=tnwrs
+ trc1=0.0038
+ ibe='pibe*mmatd*(1 + tdeldi)'
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
+ ikf=pikf        
+ ikr=pikr     
+ vaf=pvef       
+ var=pver       
+ re=pre
+ rb=prb
+ rc=prc
+ fc=pfc          
+ cje=pcje
+ vje=pvje
+ mje=pmje
+ cjc=pcjc
+ vjc=pvjc
+ mjc=pmjc
+ cjs=0           
+ xcjc=1     
+ tf=ptf          
+ xtf=pxtf         
+ itf=pitf        
+ vtf=pvtf        
+ ptf=pptf        
+ tr=ptr          
+ expli=pimelt    

.ends divpnp

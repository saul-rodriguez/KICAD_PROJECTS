* Path, Component, Release: cmos7base/rel/HSPICE/models/sblkpdres.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  sblkpdres    One sided P+ S/D Resistor for Ballasted pFET
*
***********************************************************************
*
*  Distributed R-C network which accounts for end resistance effects,
*  parasitic capacitance and includes a fixed substrate resistance.
*
*           Rend       Rmid     Eva     Evb     Rmid        
*   in  o--/\/\/\--o--/\/\/\--o--l|--o--|l--o--/\/\/\--o--------o  fet
*                  |                 |                 |
*                  |                 |                 |
*                ----              ----              ----
*           Dpnw \  /         Dpnw \  /         Dpnw \  /
*                 \/                \/                \/ 
*                ----              ----              ----
*                  |                 |                 |
*                  |                 |                 |  
*                  \                 \                 \
*              Rg  /              Rg /              Rg /
*                  \                 \                 \
*                  |                 |                 |     
*                  |                 |                 |    
*                  o-----------------o-----------------o
*                                    |
*  Parasitic capacitance is          |
*  divided among diodes in           \
*  1/6 - 2/3 - 1/6 ratios            /  Rsub (Rsx)
*                                    \
*                                    |
*                                    |
*                                    o nw (Connect to positive power supply)
*
***********************************************************************
*
*  DIMENSIONS: W = Design width  of RX
*              L = Design length of OP
*
*  SYNTAX:     Specify both width and length:
*              xxx  in out nw  sblkpdres (w=2u  l=5u)
*
*       OR     Specify width and resistance:
*              xxx  in out nw  sblkpdres (w=2u  r=250)
*
*  SERIES:        s  --> Defined model parameter,   Reff = Rbar * s
*
*  PARALLEL:      m  --> Implicit model parameter,  Reff = Rbar / m
*
*              pbar  --> Defined model parameter,   Reff = Rbar
*
*               par  --> Explicit device multiplicity (par must equal m in netlist)
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*                rsx --> Fixed nwell resistance, default = 50 ohm.
*
*  NOTES:
*
*  1. Model supports only rectangular resistors with contacts at one
*     end (in) of the resistor bar. "Dogbone" or multiple tap layouts 
*     are not supported.
*
*  2. Capacitance is determined from OP area and edge alone.
*
*  3. The nwell node (nw) should be tied to the most positive power supply
*     in the circuit. The value of the resistor will be modulated by the
*     voltage on the nwell node according to the voltage coefficient.
*
*
*                                
***********************************************************************
*
.subckt sblkpdres  in fet nw w=2u  l=-1u  r=-1  s=1  pbar=1  dtemp=0  rsx=50  par=1

.param
* Check for minimum width, calculate effective width
+ opwdth = 'max(w,0.4u) + oppddwf'

* Calculate op length, assumes w,r and groundrule spacings for contacts
+ rendn = '1u*(exp(oppdrenn) - 10)'
+ pleqn = '((r*pbar*(w+oppddwn) - rendn) / oppdrsn) - oppddln'

* Select op length, user input takes precedence over calculated length
+ plnom = 'max(l,0) + ((l-abs(l))/(2*l))*pleqn'

* Check for minimum length, calculate effective length
+ oplen = 'max(plnom,0.48u) + oppddlf'

* Resistance calculation
+ rmid = 'oppdrsf * (oplen / opwdth) / 2'
+ rend = '1u*(exp(oppdrenf) - 10) / opwdth'

* Calculate area, perimeter for capacitance
* Only area and edge of the sblk OP is used, 
* area outside OP is handled by extraction
+ opcaplen  = '2 * ((oplen-oppddln) + (opwdth-oppddwn))'
+ opcaparea = '(oplen-oppddln) * (opwdth-oppddwn)'

* Partition p+ to nw capacitance area, perimeter
+ apnw = 'opcaparea / 3'
+ ppnw = 'opcaplen  / 3'

* Mis-match Calculation
+ opma   = 'oppdma * oppdma / (oplen * opwdth * 1e12)'
+ opml   = 'oppdml * oppdml / (opwdth * oplen * oplen * 1e18)'
+ opmw   = 'oppdmw * oppdmw / (opwdth * opwdth * 1e12)'
+ op3sig = '0.01 * sqrt(opma + opml + opmw)'
+ opmm   = 'op3sig * 0.7071 / sqrt(s*pbar*par)'
+ mmres  = agauss(0,1,3)
+ mmatr  = '1 + (opmm * mmres)'

* Effective resistance from conductance
+ rg = '1/(24e2*opwdth + 8.5e2*oplen)'

*Flicker Noise
+ lnoi = 'oplen - oppddlf'
+ wnoi = 'opwdth - oppddwf'
+ rtot = '2*rmid+rend'
+ k1 = 'exp(log(10e-24)+dnoipd*log(2.75))*(exp(1.45*log(wnoi/lnoi)))*(rtot/rmid)*(rtot/rmid)/(s*pbar*par)'

* Resistor network
rea  in   1            'rend*mmatr*s/pbar'  dtemp=dtemp  tc1=oppdrntc
rma   1   2  resnoi  r='rmid*mmatr*s/pbar'  dtemp=dtemp  tc1=oppdrstc
rmb   4   5            'rmid*mmatr*s/pbar'  dtemp=dtemp  tc1=oppdrstc
reb   5 fet  r=1m

eva   2   3  poly(2)  6 3  in  2  0 0 0 0 oppdvcr
evb   3   4  poly(2)  6 3  4 fet  0 0 0 0 oppdvcr

dnwa  1    6  dpnwa  area='(apnw/2)*s*pbar'  pj='(ppnw/2)*s*pbar'  dtemp=dtemp
dnwb  3    6  dpnwa  area='(2*apnw)*s*pbar'  pj='(2*ppnw)*s*pbar'  dtemp=dtemp
dnwc  5    6  dpnwa  area='(apnw/2)*s*pbar'  pj='(ppnw/2)*s*pbar'  dtemp=dtemp

rsb  6  nw   r='rsx'

.model resnoi r noise=1 kf=k1 af=2 lf=0 wf=2 ef=1 dw=0u dlr=0u l=lnoi w=wnoi

* P+ to NW Diodes
*
.model dpnwa d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+    rs = '3*rg*apnw'
+     n = n_p
+    js = js_p33
+   jsw = jsw_p33
+    cj = cj_p33
+   cta = cta_p
+    pb = pb_p33
+   tpb = pta_p
+    mj = mj_p33
+   cjp = cjsw_p33
+   ctp = ctp_p
+   php = pbsw_p33
+  tphp = ptp_p
+  mjsw = mjsw_p33
+    vb = 12.0

.ends sblkpdres

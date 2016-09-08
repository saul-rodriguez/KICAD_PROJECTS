* Path, Component, Release: cmhv7sf/rel/HSPICE/models/oppdres.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  oppdres    P+ S/D Resistor
*
***********************************************************************
*
*  Distributed R-C network which accounts for end resistance effects,
*  parasitic capacitance and includes a fixed substrate resistance.
*
*           Rend       Rmid     Eva     Evb     Rmid       Rend
*   in  o--/\/\/\--o--/\/\/\--o--l|--o--|l--o--/\/\/\--o--/\/\/\--o  out
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
*  1/6 - 2/3 - 1/6 ratios            /    Rsub (Rsx)
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
*              xxx  in out nw  oppdres (w=2u  l=5u)
*
*       OR     Specify width and resistance:
*              xxx  in out nw  oppdres (w=2u  r=250)
*
*  SERIES:        s  --> Defined model parameter,  Reff = Rbar * s
*
*  PARALLEL: m (par) --> Multiplicity parameters,  Reff = Rbar / m (par)
*
*              pbar  --> Defined model parameter,  Reff = Rbar
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*                rsx --> Fixed nwell resistance, default = 50 ohm.
*
*  NOTES:
*
*  1. Model supports only rectangular resistors with contacts at each
*     end of the resistor bar. "Dogbone" or multiple tap layouts are 
*     not supported.
*
*  2. Model assumes minimum groundrule spacings used for placing contacts
*     to calculate the end resistance effects based on OP design length.
*
*  3. The nwell node (nw) should be tied to the most positive power supply
*     in the circuit. The value of the resistor will be modulated by the
*     voltage on the nwell node according to the voltage coefficient.
*
*                                
***********************************************************************
.subckt oppdres  in out nw  w=2u l=-1u r=-1 s=1 par=1 pbar=1 dtemp=0 rsx=50 vdnsx=50

.param
* Check for minimum width, calculate effective width
+ opwdth = 'max(w,0.4u) + oppddwf'
*
* Calculate op length, assumes w,r and groundrule spacings for contacts
+ rendn = '1u*(exp(oppdrenn) - 10)'
+ pleqn = '((r*pbar*(w+oppddwn) - 2*rendn) / oppdrsn) - oppddln'
*
* Select op length, user input takes precedence over calculated length
+ plnom = 'max(l,0) + ((l-abs(l))/(2*l))*pleqn'
*
* Check for minimum length, calculate effective length
+ oplen = 'max(plnom,0.48u) + oppddlf'
*
* Resistance calculation
+ rmid = 'oppdrsf * (oplen / opwdth) / 2'
+ rend = '1u*(exp(oppdrenf) - 10) / opwdth'
*
* Calculate area, perimeter for capacitance
* Subtract delta w, delta l to obtain drawn dimensions,
* Then include region outside of op mask
+ opcaplen  = '2 * ((oplen-oppddln) + 2*opendf + (opwdth-oppddwn))'
+ opcaparea = '((oplen-oppddln) + 2*opendf) * (opwdth-oppddwn)'
*
* Partition p+ to nw capacitance area, perimeter
+ apnw = 'opcaparea / 3'
+ ppnw = 'opcaplen  / 3'
*
* Mis-match Calculation
+ opma   = 'oppdma * oppdma / (oplen * opwdth * 1e12)'
+ opml   = 'oppdml * oppdml / (opwdth * oplen * oplen * 1e18)'
+ opmw   = 'oppdmw * oppdmw / (opwdth * opwdth * 1e12)'
+ op3sig = '0.01 * sqrt(opma + opml + opmw)'
+ opmm   = 'op3sig * 0.7071 / sqrt(s*pbar*par)'
+ mmres  = agauss(0,1,3)
+ mmatr  = '1 + (opmm * mmres)'
*
* Effective resistance from conductance
+ rg = '1/(24e2*opwdth + 8.5e2*oplen)'
*
* Flicker Noise
+ lnoi = 'oplen - oppddlf'
+ wnoi = 'opwdth - oppddwf'
+ rtot = '2*rmid+2*rend'
+ k1 = 'exp(log(10e-24)+dnoipd*log(2.75))*(exp(1.45*log(wnoi/lnoi)))*(rtot/rmid)*(rtot/rmid)/(s*pbar*par)'
*
* Resistor network
rea  in   1 	      'rend*mmatr*s/pbar'  dtemp=dtemp  tc1=oppdrntc
reb   5 out  	      'rend*mmatr*s/pbar'  dtemp=dtemp  tc1=oppdrntc
rma   1   2  resnoi r='rmid*mmatr*s/pbar'  dtemp=dtemp  tc1=oppdrstc
rmb   4   5  	      'rmid*mmatr*s/pbar'  dtemp=dtemp  tc1=oppdrstc

eva   2   3  poly(2)  6 3  in  2  0 0 0 0 oppdvcr
evb   3   4  poly(2)  6 3  4 out  0 0 0 0 oppdvcr

dnwa  1  6  dpnwa  area='(apnw/2)*s*pbar'  pj='(ppnw/2)*s*pbar'  dtemp=dtemp
dnwb  3  6  dpnwa  area='(2*apnw)*s*pbar'  pj='(2*ppnw)*s*pbar'  dtemp=dtemp
dnwc  5  6  dpnwa  area='(apnw/2)*s*pbar'  pj='(ppnw/2)*s*pbar'  dtemp=dtemp

rsb   6  nw r=rsx

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
+    js = js_p
+   jsw = jsw_p
+     n = n_p
+    rs = '3*rg*apnw'
+    cj = cj_p
+   cta = cta_p
+    pb = pb_p
+   tpb = pta_p
+    mj = mj_p
+   cjp = cjsw_p
+   ctp = ctp_p
+   php = pbsw_p
+  tphp = ptp_P
+  mjsw = mjsw_p
+    vb = 12.0

.ends oppdres

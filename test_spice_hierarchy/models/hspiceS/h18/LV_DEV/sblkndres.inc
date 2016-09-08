* Path, Component, Release: cmhv7sf/rel/HSPICE/models/sblkndres.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  sblkndres    One sided N+ S/D Resistor for Ballasted nFET
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
*                 /\  Dsnx          /\  Dsnx          /\  Dsnx
*                /  \              /  \              /  \
*                ----              ----              ----
*                  |                 |                 |
*                  |                 |                 |
*                  \                 \                 \
*                  /  Rg             /  Rg             /  Rg
*                  \                 \                 \
*                  |                 |                 |
*                  o-----------------o-----------------o
*                                    |
*                                    |
*  Parasitic capacitance and         \
*  resistance is                     / Rsub
*  divided among diodes in           \
*  1/6 - 2/3 - 1/6 ratios            |
*                                    o substrate (sx)
*
***********************************************************************
*
*  DIMENSIONS: W = Design width  of RX
*              L = Design length of SBLK & OP 
*
*  SYNTAX:     Specify both width and length:
*              xxx  in fet sx  sblkndres (w=2u  l=5u)
*
*       OR     Specify width and resistance:
*              xxx  in fet sx  sblkndres (w=2u  r=150)
*
*  SERIES:        s  --> Defined model parameter,   Reff = Rbar * s
*
*  PARALLEL: m (par) --> Multiplicity parameters,   Reff = Rbar / m (par)
*
*              pbar  --> Defined model parameter,   Reff = Rbar
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*                rsx --> Fixed substrate resistance, default = 50 ohm.
*
*  NOTES:
*
*  1. Model supports only rectangular resistors with contacts at one
*     end (in) of the resistor bar. "Dogbone" or multiple tap layouts 
*     are not supported.
*
*  2. Capacitance is determined from OP area and edge alone.
*
*
*                                
***********************************************************************
*
.subckt sblkndres  in fet sx  w=2u l=-1u r=-1 s=1 par=1 pbar=1 dtemp=0 rsx=50

.param
* Check for minimum width, calculate effective width
+ opwdth = 'max(w,0.4u) + opnddwf'
*
* Calculate op length, assumes w,r and groundrule spacings for contacts
+ rendn = '1u*(exp(opndrenn) + 2.793)'
+ pleqn = '((r*pbar*(w+opnddwn) - rendn) / opndrsn) - opnddln'
*
* Select op length, user input takes precedence over calculated length
+ plnom = 'max(l,0) + ((l-abs(l))/(2*l))*pleqn'
*
* Check for minimum length, calculate effective length
+ oplen = 'max(plnom,0.48u) + opnddlf'
*
* Resistance calculation
+ rmid = 'opndrsf * (oplen / opwdth) / 2'
+ rend = '1u*(exp(opndrenf) + 2.793) / opwdth'
*
* Calculate area, perimeter for capacitance
* Only area and edge of the sblk OP is used, 
* area outside OP is handled by extraction
+ opcaplen  = '2 * ((oplen-opnddln) + (opwdth-opnddwn))'
+ opcaparea = '(oplen-opnddln) * (opwdth-opnddwn)'
*
* Partition capacitance area, perimeter
+ ansx = 'opcaparea / 3'
+ pnsx = 'opcaplen  / 3'
*
* Mis-match Calculation
+ opma   = 'opndma * opndma / (oplen * opwdth * 1e12)'
+ opml   = 'opndml * opndml / (opwdth * oplen * oplen * 1e18)'
+ opmw   = 'opndmw * opndmw / (opwdth * opwdth * 1e12)'
+ op3sig = '0.01 * sqrt(opma + opml + opmw)'
+ opmm   = 'op3sig * 0.7071 / sqrt(s*pbar*par)'
+ mmres  = agauss(0,1,3)
+ mmatr  = '1 + (opmm * mmres)'
*
* Effective resistance from local conductance
+ rg = '1/(9.4e2*opwdth + 3.3e2*oplen)'
*
* Flicker Noise
+ lnoi = 'oplen - opnddlf'
+ wnoi = 'opwdth - opnddwf'
+ rtot = '2*rmid+rend'
+ k1 = 'exp(log(6e-24)+dnoind*log(6))*(exp(1.45*log(wnoi/lnoi)))*(rtot/rmid)*(rtot/rmid)/(s*pbar*par)'
*
* Resistor network
rea  in   1            'rend*mmatr*s/pbar'  dtemp=dtemp  tc1=opndrntc
rma   1   2  resnoi  r='rmid*mmatr*s/pbar'  dtemp=dtemp  tc1=opndrstc
rmb   4   5            'rmid*mmatr*s/pbar'  dtemp=dtemp  tc1=opndrstc
reb   5 fet  r=1m  

eva   2   3  poly(2)  3 sx  in  2  0 0 0 0  opndvcr
evb   3   4  poly(2)  3 sx  4 fet  0 0 0 0  opndvcr

dnsa  6   1  dnsxa  area='(ansx/2)*s*pbar'  pj='(pnsx/2)*s*pbar' dtemp=dtemp
dnsb  6   3  dnsxa  area='(2*ansx)*s*pbar'  pj='(2*pnsx)*s*pbar' dtemp=dtemp
dnsc  6   5  dnsxa  area='(ansx/2)*s*pbar'  pj='(pnsx/2)*s*pbar' dtemp=dtemp

rsub  6  sx  r='rsx'

.model resnoi r noise=1 kf=k1 af=2 lf=0 wf=2 ef=1 dw=0u dlr=0u l=lnoi w=wnoi

* N+ to SX Diodes
*
.model dnsxa d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+    js = js_n
+   jsw = jsw_n
+     n = n_n
+    rs = '3*rg*ansx'
+    cj = cj_n
+   cta = cta_n
+    pb = pb_n
+   tpb = pta_n
+    mj = mj_n
+   cjp = cjsw_n
+   ctp = ctp_n
+   php = pbsw_n
+  tphp = ptp_n
+  mjsw = mjsw_n
+    vb = 11.5

.ends sblkndres

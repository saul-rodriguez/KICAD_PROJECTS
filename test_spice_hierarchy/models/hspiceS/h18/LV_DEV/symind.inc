* Path, Component, Release: cmhv7sf/relAM/HSPICE/models/symind.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
***************************************************************************
*
* Scalable, Symmetric, Single Layer, Octagonal Inductor Model
*
***************************************************************************
*
* The Symind model contains:
*
* 1. Call to indstack subcircuit that models the two symmetric coupled halves of
*    the spiral.
* 2. A spiral centertap resistance (rct) that models the resistance of the
*    connection to the symmetric center of the spiral. This is set to zero if
*    no centertap connection is present.
* 3. A center tap inductance (lct) that models the inductance of the connection
*    to the symmetric center of the spiral. This is set to zero if no center tap
*    connection is present.
* 4. A high value shunt resistance to ground to provide a DC path to ground from
*    the node "ct" in case there is no center tap connection.
* 5. Two capacitors (cprct, csect) that represent the capacitance between the
*    centertap connection and the primary and secondary halves of the spiral.
*    These are set to very small values if no centertap connection is present.
*
*                                      o ct
*                                      |
*                                      +-------------------------------------+
*                                      |				     |     
* 				    _ _ _ _ 				     |
* 				   |	   |				     |
* 				   |  lct  |				     |
* 				   |_ _ _ _| 				     |
*     				       |				     |
*				       + ct_int				     |
*				       |				     |
*                                      \				     |
*                                      /                                     |
*                                      \ rct                                 |
*                                      /                                     \
*                      cprct           \          csect               rctref /
*                        ||            |            ||                       \
*             +----------||--------+---+---+--------||--------+              /
*             |          ||        | ctprse|        ||        |              |
*             |                    o       o                  |              |
*             |    +------------------------------------+     |              |
* outpr o-----+---o|outpr        inpr     inse     outse|o----+-----o outse  |
*                  |                                    |                    |
*                  |         "indstack subcircuit"      |                    |
*                  |                                    |                    |
*                  |                 ref                |                    |
*                  +------------------------------------+                    |
*                                      o                                     |
*                                      |                                     |
*                                      +-------------------------------------+
*                                      |
*                                      o
*                      ref (substrate/groundplane)
*
*******************************************************************************
*
* NOTES:
*
*  1. Outer dimension (x) may vary from 100um to 300um.
*
*  2. Supported spiral widths (w) may vary from 3.24um to 25um.
*
*  3. Turn to turn space (s) may vary from 2.8um to 5um depending on spiral width.
*
*  4. Number of turns (n) may vary from 1 to filled-in by 1-turn increments.
*
*
*******************************************************************************
.subckt symind (outpr outse ct ref)
*
*
+    x      =  100u    $ Largest outer dimension of octagonal spiral (m)
+    w      =  5u      $ Width of spiral turn (m)
+    s      =  5u      $ Turn to turn space (m)
+    n      =  2       $ Number of turns in 1-turn increments.
+    wu     =  -1u     $ Width of spiral centertap connection (m)
*                      $ if not passed-in (or set to -1u)
*                      $ then no spiral center tap connection preesent
+    nlev   =  4       $ Number of metal levels in the design.
+    grnd   =  -1      $ Indicator for grounding scheme under the spiral.
*                      $  -1 = BB (Default)
*                      $  -2 = M1 groundplane
+     xov   =  0       $ Presence/Absence of wider and parallel-stacked crossovers.
*                      $  0 = No (Default)
*                      $  1 = Yes
+    dtemp  =  0       $ Temperature difference between element and
*                      $ circuit temperature (deg C).
+    altct  =  0       $ 0 = center-tap connection closest to the IND outline (Default)
*		       $ 1 = center-tap connection in alternate direction to the default
*
.param lenmult=1
.param px='x*lenmult'
.param pw='w*lenmult'
.param ps='(s*(n>1)+(n==1)*4u)*lenmult'
.param ppwu='wu*lenmult'
.param rxflfrac=0.20'
.param rxeff='oppcstif-2*rxflfrac*oppcstif'
.param pcflfrac=0.20
.param pceff='oppcthk-2*pcflfrac*oppcthk'
.param m1flfrac=0.09
.param m1teff='m1t-2*m1flfrac*m1t'
.param mtflfrac=0.00
.param mtteff='mtt-2*mtflfrac*mtt'
.param amflfrac=0.00
.param amteff='amt-2*amflfrac*amt'
.param m2flfrac=0.00
.param m2teff='m2t-2*m2flfrac*m2t'
.param m3flfrac=0.00
.param m3teff='m3t-2*m3flfrac*m3t'
.param m4flfrac=0.00
.param m4teff='m4t-2*m4flfrac*m4t'
.param m5flfrac=0.00
.param m5teff='m5t-2*m5flfrac*m5t'
*
* grnd conversion to bptype
.param bptype=grnd
*
* Calculations of stack height info.
.param prt3=amt
.param delpr3='(delam)/1'
.param prrs3='1/(1/(amrs))'
.param temcpr3='(amrs*tamrs)'
.param temcprnum3=amrs
.param sect3=mtt
.param delsec3='(delmt)/1'
.param secrs3='1/(1/(mtrs))'
.param temcse3='(mtrs*tmtrs)'
.param temcsenum3=mtrs
.param secprt3=mtamt
.param ctrs3=m1rs
*
.param prt4=amt
.param delpr4='(delam)/1'
.param prrs4='1/(1/(amrs))'
.param temcpr4='(amrs*tamrs)'
.param temcprnum4=amrs
.param sect4=mtt
.param delsec4='(delmt)/1'
.param secrs4='1/(1/(mtrs))'
.param temcse4='(mtrs*tmtrs)'
.param temcsenum4=mtrs
.param secprt4=mtamt
.param ctrs4=m2rs
*
.param prt5=amt
.param delpr5='(delam)/1'
.param prrs5='1/(1/(amrs))'
.param temcpr5='(amrs*tamrs)'
.param temcprnum5=amrs
.param sect5='(xov==0)*mtt+(xov==1)*(m3t+mxmtt+mtt)'
.param delsec5='(xov==0)*(delmt)/1+(xov==1)*(delm3+delmt)/2'
.param secrs5='(xov==0)*(1/(1/(mtrs)))+(xov==1)*(1/(1/(m3rs)+1/(mtrs)))'
.param temcse5='(xov==0)*(mtrs*tmtrs)+(xov==1)*(m3rs*tm3rs+mtrs*tmtrs)'
.param temcsenum5='(xov==0)*(mtrs)+(xov==1)*(m3rs+mtrs)'
.param secprt5=mtamt
.param ctrs5=m2rs
*
.param prt6=amt
.param delpr6='(delam)/1'
.param prrs6='1/(1/(amrs))'
.param temcpr6='(amrs*tamrs)'
.param temcprnum6=amrs
.param sect6='(xov==0)*mtt+(xov==1)*(m3t+m3m4t+m4t+mxmtt+mtt)'
.param delsec6='(xov==0)*(delmt)/1+(xov==1)*(delm3+delm4+delmt)/3'
.param secrs6='(xov==0)*(1/(1/(mtrs)))+(xov==1)*(1/(1/(m3rs)+1/(m4rs)+1/(mtrs)))'
.param temcse6='(xov==0)*(mtrs*tmtrs)+(xov==1)*(m3rs*tm3rs+m4rs*tm4rs+mtrs*tmtrs)'
.param temcsenum6='(xov==0)*(mtrs)+(xov==1)*(m3rs+m4rs+mtrs)'
.param secprt6=mtamt
.param ctrs6=m2rs
*
.param prt7=amt
.param delpr7='(delam)/1'
.param prrs7='1/(1/(amrs))'
.param temcpr7='(amrs*tamrs)'
.param temcprnum7=amrs
.param sect7='(xov==0)*mtt+(xov==1)*(m3t+m3m4t+m4t+m4m5t+m5t+mxmtt+mtt)'
.param delsec7='(xov==0)*(delmt)/1+(xov==1)*(delm3+delm4+delm5+delmt)/4'
.param secrs7='(xov==0)*(1/(1/(mtrs)))+(xov==1)*(1/(1/(m3rs)+1/(m4rs)+1/(m5rs)+1/(mtrs)))'
.param temcse7='(xov==0)*(mtrs*tmtrs)+(xov==1)*(m3rs*tm3rs+m4rs*tm4rs+m5rs*tm5rs+mtrs*tmtrs)'
.param temcsenum7='(xov==0)*(mtrs)+(xov==1)*(m3rs+m4rs+m5rs+mtrs)'
.param secprt7=mtamt
.param ctrs7=m2rs
*
* Calculations of primary and secondary.
.param pprt='(nlev==3)*prt3+(nlev==4)*prt4+(nlev==5)*prt5+(nlev==6)*prt6+(nlev==7)*prt7'
.param pdelpr='(nlev==3)*delpr3+(nlev==4)*delpr4+(nlev==5)*delpr5+(nlev==6)*delpr6+(nlev==7)*delpr7'
.param pprrs='(nlev==3)*prrs3+(nlev==4)*prrs4+(nlev==5)*prrs5+(nlev==6)*prrs6+(nlev==7)*prrs7'
.param temcpr='(nlev==3)*temcpr3+(nlev==4)*temcpr4+(nlev==5)*temcpr5+(nlev==6)*temcpr6+(nlev==7)*temcpr7'
.param temcprnum='(nlev==3)*temcprnum3+(nlev==4)*temcprnum4+(nlev==5)*temcprnum5+(nlev==6)*temcprnum6+(nlev==7)*temcprnum7'
.param psect='(nlev==3)*sect3+(nlev==4)*sect4+(nlev==5)*sect5+(nlev==6)*sect6+(nlev==7)*sect7'
.param pdelsec='(nlev==3)*delsec3+(nlev==4)*delsec4+(nlev==5)*delsec5+(nlev==6)*delsec6+(nlev==7)*delsec7'
.param psecrs='(nlev==3)*secrs3+(nlev==4)*secrs4+(nlev==5)*secrs5+(nlev==6)*secrs6+(nlev==7)*secrs7'
.param temcse='(nlev==3)*temcse3+(nlev==4)*temcse4+(nlev==5)*temcse5+(nlev==6)*temcse6+(nlev==7)*temcse7'
.param temcsenum='(nlev==3)*temcsenum3+(nlev==4)*temcsenum4+(nlev==5)*temcsenum5+(nlev==6)*temcsenum6+(nlev==7)*temcsenum7'
.param psecprt='(nlev==3)*secprt3+(nlev==4)*secprt4+(nlev==5)*secprt5+(nlev==6)*secprt6+(nlev==7)*secprt7'
.param pctrs='(nlev==3)*ctrs3+(nlev==4)*ctrs4+(nlev==5)*ctrs5+(nlev==6)*ctrs6+(nlev==7)*ctrs7'
.param h3='rxeff+pceff+capct+m1teff+mxmtt+psect+psecprt+pprt'
.param h4='rxeff+pceff+capct+m1teff+m1m2t+m2teff+mxmtt+psect+psecprt+pprt'
.param h5='rxeff+pceff+capct+m1teff+m1m2t+m2teff+m2m3t+m3teff+mxmtt+psect+psecprt+pprt'
.param h6='rxeff+pceff+capct+m1teff+m1m2t+m2teff+m2m3t+m3teff+m3m4t+m4teff+mxmtt+psect+psecprt+pprt'
.param h7='rxeff+pceff+capct+m1teff+m1m2t+m2teff+m2m3t+m3teff+m3m4t+m4teff+m4m5t+m5teff+mxmtt+psect+psecprt+pprt'
.param phpr='(nlev==3)*h3+(nlev==4)*h4+(nlev==5)*h5+(nlev==6)*h6+(nlev==7)*h7-pprt'
.param phsec='phpr-psect-psecprt'
.param phct='rxeff+pceff+capct+(m1teff+m1m2t)*(nlev>3)'
.param pctt='(nlev==3)*m1t+(nlev>3)*m2t'
*
* Calculations of M1 shield stack height.
.param phm1sx='oppcstif+oppcthk+capct+m1t'
.param phpreff='phpr-(grnd==-2)*phm1sx'
.param phseceff='phsec-(grnd==-2)*phm1sx'
.param phcteff='((grnd==-1)*phct+(grnd==-2)*(max(1e-9,(nlev>3)*m1m2t)))'
*
* Calculations of Temc. Coefficient
.param ptprrs='temcpr/temcprnum'
.param ptsers='temcse/temcsenum'
*
* PR Single Layer Coefficients
.param ppcprs='e0*4.100/phpreff'
.param ppcus='e0*4.100/phseceff'
.param ppccts='e0*4.100/phcteff'
.param ppcpru='e0*4.100/psecprt'
.param ppcpruf='e0*4.100*(2*1.064/(pi-2)*log(pi/2)+2*1.064/pi*log(1+pprt/psecprt))'
.param ppcprsf='e0*4.100*(2*0.835/(pi-2)*log(pi/2)+2*1.537/pi*log(1+pprt/phpreff))'
.param ppcusf='e0*4.100*(2*0.592/(pi-2)*log(pi/2)+2*2.803/pi*log(1+psect/phseceff))'
.param ppcctsf='e0*4.100*(2*0.592/(pi-2)*log(pi/2)+2*2.803/pi*log(1+pctt/phcteff))'
.param palphapru='atan((max(1u,(ps-pdelpr)))/1.257/psecprt)'
.param ppcmpruf='e0*4.100*(0.695*(1-cos(2*palphapru))/(2*palphapru-sin(2*palphapru))*log(2*palphapru/sin(2*palphapru)))'
.param palphapr='atan((max(1u,(ps-pdelpr)))/0.687/phpreff)'
.param ppcmprsf='e0*4.100*(0.445*(1-cos(2*palphapr))/(2*palphapr-sin(2*palphapr))*log(2*palphapr/sin(2*palphapr)))'
.param pbeta='pi/2-2*palphapr'
.param ppcprpr='e0*4.100*(1/pi*log(1+pw/(max(1u,(ps-pdelpr))))+0.000/(pi-2)*log(pi/2)+1.177*pprt/(max(1u,(ps-pdelpr)))+1.192/2*(1-cos(pbeta))/(pbeta-sin(pbeta))*log(pbeta/sin(pbeta)))'
.param nummet=2
*
* Centertap resistance
.param pwct= 'min(30u,1.4142*pw+ps)'
.param plct= '(altct==0)*((n-1)*(pw+ps)+pw) + (altct==1)*(x-((n-1)*(pw+ps)+pw))'
.param prct='(xov==0)*(max(1e-5,(ppwu*1e6>0)*plct/pwct*pprrs))+(xov==1)*(max(1e-5,(ppwu*1e6>0)*plct/pwct*pctrs))'
.param prctrsx='(grnd==-1)*49+1'
.param ind_ct= '1e-7*2*plct*(log((2*plct)/(pwct+m2t))+.50049+((pwct+m2t)/(3*plct)))'
*
* Centertap capacitance
.param pccts='(xov==0)*(1e-15)+(xov==1)*(max(1e-15,(ppwu*1e6>0)*(plct*pwct*ppccts+2*(plct+pwct)*ppcctsf)))'
*
* Calculate gap distance between two symmetric halves of spiral
.param uspace='3*1e-6'
.param vwithin='0.6*1e-6'
.param ppgap='pwct+2*(uspace+vwithin)'
*
* Centertap to ground shunt resistance
.param prctgrnd=1e9
*
* Centertap to primary and secondary capacitances
.param numop='(ppwu*1e6>0)*int((n-1)/2)'
.param xovarea='(xov==0)*(pwct*(2*pw+ps)-pow(((pwct-0.8284*pw)/2+ps/2),2))+(xov==1)*((pwct*plct)-pow(((pwct-1.822*pw)/2),2))'
.param pcspct='max(1e-16,numop*xovarea*ppcpru)'
.param pcprct='pcspct/2'
.param pcsect='pcspct/2'
*
rctref ct ref                r=prctgrnd
rct ctprse ct_int            r=prct
lct ct_int ct		     l=ind_ct
rctrsx ctref ref             r=prctrsx
cprct ctprse outpr           c=pcprct
csect ctprse outse           c=pcsect
ccts ctprse ctref            c=pccts
*
xstack outpr ctprse outse ctprse ref indstack
+ xp=px
+ xs=px
+ wp=pw
+ ws=pw
+ sp='pw+2*ps'
+ ss='pw+2*ps'
+ np='n/2'
+ ns='n/2'
+ pgap=ppgap
+ pwu='pw+(xov==1)*7e-6'
+ pstack=3
+ pgrnd=bptype
+ gprs=m1rs
+ tgprs=tm1rs
+ ctrs=m1rs
+ tctrs=tm1rs
+ rsx=rsub
+ trsx=trsub
+ pdtemp=dtemp
+ delpr=pdelpr
+ prrs=pprrs
+ prt=pprt
+ tprrs=ptprrs
+ delse=pdelpr
+ sers=pprrs
+ sect=pprt
+ tsers=ptprrs
+ delup=pdelsec
+ uprs=psecrs
+ tuprs=ptsers
+ upt=psect
+ cprs=ppcprs
+ cprsf=ppcprsf
+ cmprsf=ppcmprsf
+ cprpr=ppcprpr
+ cpru=ppcpru
+ cpruf=ppcpruf
+ cmpruf=ppcmpruf
+ cses=ppcprs
+ csesf=ppcprsf
+ cmsesf=ppcmprsf
+ csese=ppcprpr
+ cprse=ppcprpr
+ cprsef=1f
+ cmprsef=1f
+ cus=ppcprs
+ cusf=ppcusf
+ sxthk=pmsxt
*
* optimization coefficients
*
.param prscrfmin =0.001
.param prscrfmax =0.005
.param prscrfa =0.026
.param prscrfb =-0.0014
.param prfb =3e-3
.param ppowa =0
.param ppowb =0
.param pamax =7000
.param paa =150
.param pab =150
.param condsib =1
.param prgptb =0.1
.param rsxcorrb =0.8
.param csxcormax =0.75
.param csxcorra =0.00009
.param csxcorrb =1.0
.param pcmprsb =1
.param pcmsesb =1
.param pcofprsb =1
.param pcofsesb =1
.param pcoprseb =1
.param pcmprseb =1
.param posplx ='(grnd==-1)*0.15 + (grnd==-2)*(0.28-(w>=15u)*0.05)'
.param plscrfmax =0.3
.param plscrfa =0.1
.param plscrfb =0.05
.param pcoo ='1 + (n>=8)*0.3'
*
.ends symind

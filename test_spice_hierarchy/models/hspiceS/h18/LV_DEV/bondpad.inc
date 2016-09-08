* Path, Component, Release: cmhv7sf/relAM/HSPICE/models/bondpad.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  bondpad  Bondpad over BB, PC or M1 groundplane
*
***************************************************************************
*
*                                   in
*  Cox represents oxide capacitance  o
*  between the AM bondpad and the    |-----------+
*  groundplane.                      |           |
*                             Cox1 -----  Cox2 -----
*                                  -----       -----
*                                    |           |
*                          Cgp2      |           |
*                     +___||___+     |           |
*                     |   ||   |     |           |
*                     |        |     |           |
*                 +---+-/\/\/\/+---- | ----------+ 2
*                 |     Rgp2         |           |
*                 |                  |           |
*          gp  o--+---+-/\/\/\/+-----+ 1         |
*                     | Rgp1   |     |           |
*                     |        |     |           |
*                     +___||___+     |           |
*                         ||         |           |
*    Rgp and Cgp           Cgp1      |           |
*    represent the                   |           |  Rsb is set to a high
*    groundplane resistance          |           |  value (1GOhm) to
*    and capacitance                 \           \  effectively remove this
*                                    /           /  node from the circuit.
*                               Rsb1 \      Rsb2 \  This node is provided
*                                    /           /  for compatibility with
*                                    |           |  bondpad model topologies
*                                    +-----------+  from BiCMOS technologies.
*                                          |
*                                          |
*                                          o sx (dummy node for compatibility)
*
*  All elements (Cox, Cgp, Rgp) are distributed in order to account
*  for high frequency effects.
********************************************************************************
*
*  DIMENSIONS: W, L = Design width, length of AM bondpad
*
*  SYNTAX:     Specify both width and length:
*              xxx  in gp sx  bondpad (w=70u  l=100u)
*
*      OR:     Specify length only (width default = -1 for square bondpad)
*              xxx  in gp sx  bondpad (l=100u)
*
*  OPTIONAL:   nlev  --> Indicates number of metal levels including AM.
*                        Possible values = 3, 4, 5, 6, or 7.  (default, nlev=5)
*
*              rect  --> Flag to select rectangular (default, rect=1) or
*                        octagonal (rect=-1) bondpad shape.
*
*                bp  --> Indicator for grounding scheme under bondpad,
*                        Default= 2 (BB) or specify 8 (M1) or specify 7 (PC)
*
*              dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*
*  EXAMPLES:
*
*
*   For rectangular bondpad with AM = 5th level over BB:
*       x1  in gp sx  bondpad  l=100u  w=70u
*
*
*   For symmetrical octagonal bondpad with AM = 6th level over M1:
*       x1  in gp sx  bondpad  l=100u  bp=8 rect=-1  nlev=6
*                               ____________
*                             /              \      /|\
*                            /                \      |
*                           /                  \     |
*                          |                    |
*                          |     AM Bondpad     | W=100um
*                          |                    |
*                           \                  /     |
*                            \                /      |
*                             \______________/      \|/
*                          <----  L=100um  ----->
*
*
*   For asymmetrical octagonal (rectangular with beveled corners)
*       with AM = 4th level over BB:
*       x1  in gp sx  bondpad  l=100u  w=70u  nlev=4  rect=-1
*                              ______________
*                            /                \     /|\
*                           /                  \     |
*                          |                    |
*                          |     AM Bondpad     | W=70um
*                           \                  /     |
*                            \________________/     \|/
*                          <----  L=100um  ----->
*
*******************************************************************************
*
* NOTES:
*
*  1. Either length and width or area and perimeter must be specified in
*     order to get a valid result. Otherwise, the internal oxide capacitance
*     will be set to zero.
*
*     When specifying area and perimeter, the statistical variation and metal
*     bias of the width and length of the bondpad will not be calculated.
*
*  2. This model provides a terminal for the groundplane connection.
*     For BB version (bp=2), this connection represents a substrate
*      contact that connects to the substrate underneath the bondpad.  This
*      connection would be connected to the same potential as all other
*      substrate contacts in a design.
*     For PC version (bp=7), this connection represents a PC
*      contact that connects to the PC layer underneath the bondpad.
*      This connection should be tied to any "quiet" AC ground.
*     For M1 version (bp=8), this connection represents a M1
*      contact that connects to the M1 layer underneath the bondpad.
*      This connection should be tied to any "quiet" AC ground.
*
*  3. For a bondpad with PC or M1 groundplane, the groundplane resistance scales
*     with the geometry and gets distributed into Rgp1 and Rgp2 to improve the
*     model accuracy at high frequencies.
*
*  4. For a BB bondpad, the substrate resistance scales with the area of the
*     bondpad and its value is extracted from fitting the model to measured
*     hardware.
*
*  5. The series resistance, Rsb, is set to a very high value in order to
*     remove the "dummy" node from the circuit.  This node is provided for
*     topology compatability between CMOS and BiCMOS technologies.  BiCMOS
*     technologies generally include an NS groundplane option that requires
*     use of this third outside node.
*
*
*******************************************************************************
*
.subckt bondpad  ( in gp sx ) 
* 
+	l=-1u 			$ Length of bondpad (m)
+	w=-1u 			$ Width of bondpad (m)
+       wbc4=-1     		$ Currently unused
+	area=-1p 		$ Currently unused
+	perim=-1p  		$ Currently unused
+	nlev=4 			$ Number of metal levels
+	rect=1 			$ 1 = Rectangular (Default)
*				  -1 = Octagonal
+	bp=2			$  2 = BB Groundplane
*				$  7 = PC Groundplane
*				$  8 = M1 Groundplane
+	dtemp=0
*
.param
*
* Calculation of effective height of metals based on fill factors
*
+ rxflfrac=0.45
+ rxeff='oppcstif-2*rxflfrac*oppcstif'
+ pcflfrac=0.02
+ pceff='oppcthk-2*pcflfrac*oppcthk'
+ m1flfrac=0.09
+ m1teff='m1t-2*m1flfrac*m1t'
+ m2flfrac=0.09
+ m2teff='m2t-2*m2flfrac*m2t'
+ m3flfrac=0.09
+ m3teff='m3t-2*m3flfrac*m3t'
+ m4flfrac=0.09
+ m4teff='m4t-2*m4flfrac*m4t'
+ m5flfrac=0.09
+ m5teff='m5t-2*m5flfrac*m5t'
+ mtflfrac=0.09
+ mtteff='mtt-2*mtflfrac*mtt'
+ amflfrac=0.00
+ amteff='amt-2*amflfrac*amt'
*
*  Calculations of stack height info.
*
+ pprt    = amt
+ psect   = mtt
+ psecprt = mtamt
*
+ h3 = 'rxeff+pceff+capct+m1teff+m1mtt+psect+psecprt+pprt'
+ h4 = 'rxeff+pceff+capct+m1teff+m1m2t+m2teff+mxmtt+psect+psecprt+pprt'
+ h5 = 'rxeff+pceff+capct+m1teff+m1m2t+m2teff+m2m3t+m3teff+mxmtt+psect+psecprt+pprt'
+ h6 = 'rxeff+pceff+capct+m1teff+m1m2t+m2teff+m2m3t+m3teff+m3m4t+m4teff+mxmtt+psect+psecprt+pprt'
+ h7 = 'rxeff+pceff+capct+m1teff+m1m2t+m2teff+m2m3t+m3teff+m3m4t+m4teff+m4m5t+m5teff+mxmtt+psect+psecprt+pprt'
*
+ phpr= '(nlev==3)*h3+(nlev==4)*h4+(nlev==5)*h5+(nlev==6)*h6+(nlev==7)*h7-pprt'
*
* Calculate # Sides
+ rbp  = '(rect==1)'                            $ rectangular
+ obp  = '(rect==-1)'                           $ octagonal
+ pn   = '(rbp*4 + obp*8)'                      $ number of sides
*
* Set width for square or rectangular pad
+ pwpp = '((w*1e6>0)*w + (w*1e6<=0)*l)'         $ w=l if w is not given
*
* Check to see if length is less than width
+ pw   = '(min(pwpp,l)+delam)'                  $ net width
+ pl   = '(max(pwpp,l)+delam)'                  $ net length
*
* Calculate appropriate area and perimeter depending on geometry
+ sbp    = '(pw*(rbp + obp*(2**0.5 -1)))'       $ length of one side
+ areap  = '((rbp + obp*4.82843)*sbp**2)'
+ parea  = '((l*1e6>0)*(areap+(pl-pw)*pw) + (l*1e6<=0)*(area>0)*area)'
+ pperim = '((l*1e6>0)*(pn*sbp+2*(pl-pw)) + (l*1e6<=0)*(perim*1e6>0)*perim)'
*
* Calculations of groundplane stack height.
*
+ phgpsx= '(bp==2)*(0)+(bp==8)*(oppcstif+oppcthk+capct)+(bp==7)*(oppcstif+oppcthk)'
+ phpreff= 'phpr-phgpsx'
*
* Calculations of groundplane resistance
*
+ gpres= '((bp==2)*813.9+(bp==8)*100*m1rs+(bp==7)*1.25*pcrsi)*(1/3)*pl/pw'
+ tgp= '(bp==2)*(trsub)+(bp==8)*(tm1rs)+(bp==7)*(tpcrsi)'
+ rsx= 1e9
*
* PR Capacitance Coefficients
*
+ pcprs='e0*4.217/phpreff'
+ pcprsf='e0*4.217*(2*0.697/(pi-2)*log(pi/2)+2*0.697/pi*log(1+pprt/phpreff))'
*
* Calculate AM bondpad to substrate oxide capacitance
*
+ pcox = '(pcprs*parea + pcprsf*pperim)'
+ csx   = '(2.143e-6*parea)'
*
* Subcircuit network
cox1  in 1  c = '0.5*pcox'   dtemp=dtemp
cox2  in 2  c = '0.5*pcox'   dtemp=dtemp
cgp1  gp 1  c = '0.6*csx'    dtemp=dtemp
cgp2  gp 2  c = '2*csx'      dtemp=dtemp
rgp1  gp 1  r = '0.5*gpres'  tc1=tgp   dtemp=dtemp
rgp2  gp 2  r = '2*gpres'    tc1=tgp   dtemp=dtemp
rsb1  sx 1  r = 'rsx*2'
rsb2  sx 2  r = 'rsx*2'

.ends bondpad

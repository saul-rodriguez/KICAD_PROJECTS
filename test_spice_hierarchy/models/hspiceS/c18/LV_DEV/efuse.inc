* Path, Component, Release: cmos7base/rel/HSPICE/models/efuse.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  efuse     Polysilicide Electrically Programmable Fuse
*
*******************************************************************************
*
*  A single resistor is used to simulate the resistance.
*
*                                  Rfuse
*                          in  o--/\/\/\/--o  out
*
*  SYNTAX: 
*
*    Specify fuse as intact (default, pblow=0) or programmed (pblow=1).
*
*    xxx  in out  efuse (pblow=0)
*
*  NOTES:
*
*  1. Model values based on PCELL layout as provided in the design kit. No
*     other geometries or layouts are supported.
*
*  2. Resistance toggles between maximum spec value for intact fuse (<=200 ohm)
*     and minimum spec value for programmed fuse (> 2 kohm).
*
*
*******************************************************************************
.subckt efuse  in out  
+   pblow = 0

  rfuse  in out  r='200*(1-pblow) + 2000*pblow'

.ends efuse

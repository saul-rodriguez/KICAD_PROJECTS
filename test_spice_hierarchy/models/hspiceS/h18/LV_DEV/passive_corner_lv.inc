* Path, Component, Release: cmhv7sf/rel/HSPICE/models/passive_corner_lv.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *********************************************************************
*
*>  Low Voltage Passive Fixed Process Corner Parameter Settings
*
*
* *********************************************************************
 
.lib lvrtt
.param
***********************************************************************
* "TT" corner : Nominal (default) process
***********************************************************************
+      fixcnrr     = 0
+      cor_res_fc  = 0
.endl lvrtt
 
.lib lvrmax
.param
***********************************************************************
* "RMAX" : High resistance
***********************************************************************
+      fixcnrr     = 1
+      cor_res_fc  = 2.5
.endl lvrmax
 
.lib lvrmin
.param
***********************************************************************
* "RMIN" : Low resistance
***********************************************************************
+      fixcnrr     = 1
+      cor_res_fc  = -2.75
.endl lvrmin
 
.lib lvctt
.param
***********************************************************************
* "TT" corner : Nominal (default) process
***********************************************************************
+      fixcnrc     = 0
+      cor_cap_fc  = 0
+      cor_ind_fc  = 0
.endl lvctt
 
.lib lvcmax
.param
***********************************************************************
* "CMAX" : High capacitance
***********************************************************************
+      fixcnrc     = 1
+      cor_cap_fc  = 2.1
+      cor_ind_fc  = 1.1
.endl lvcmax
 
.lib lvcmin
.param
***********************************************************************
* "CMIN" : Low capacitance
***********************************************************************
+      fixcnrc     = 1
+      cor_cap_fc  = -2.1
+      cor_ind_fc  = -1.2
.endl lvcmin
 
.lib lvdtt
.param
***********************************************************************
* "TT" corner : Nominal (default) process
***********************************************************************
+      fixcnrd     = 0
+      cor_dio_fc  = 0
.endl lvdtt
 
.lib lvdmax
.param
***********************************************************************
* "DMAX" : High diode current
***********************************************************************
+      fixcnrd     = 1
+      cor_dio_fc  = 2.9
.endl lvdmax
 
.lib lvdmin
.param
***********************************************************************
* "DMIN" : Low diode current
***********************************************************************
+      fixcnrd     = 1
+      cor_dio_fc  = -2.9
.endl lvdmin

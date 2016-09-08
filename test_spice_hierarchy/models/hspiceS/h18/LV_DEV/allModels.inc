* Path, Component, Release: cmhv7sf/rel/HSPICE/models/allModels.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>   HSPICE model library file to define include statements
*		   for nominal, fixed corner and Monte Carlo analyses.
*
*
* *****************************************************************************
*
***********************************************************************
* "TT" corner : Nominal (default) process
***********************************************************************
.lib tt
.lib './fixed_corner_lv.inc' lvtt
.lib './fixed_corner_hv.inc' hvtt
.lib './fixed_corner_hv.inc' hvrtt
.lib './fixed_corner_hv.inc' hvbiptt
.lib './passive_corner_lv.inc' lvrtt
.lib './passive_corner_lv.inc' lvctt
.lib './passive_corner_lv.inc' lvdtt
.lib './process_lv.inc' lvstats
.lib './process_hv.inc' hvstats
.inc './models.inc'
.endl tt
*
***********************************************************************
* "FFF" functional corner : "Fast" NMOS, "Fast" PMOS, "Fast" Passives
***********************************************************************
.lib fff
.lib './fixed_corner_lv.inc' lvfff
.lib './fixed_corner_hv.inc' hvfff
.lib './fixed_corner_hv.inc' hvrmin
.lib './fixed_corner_hv.inc' hvbiphs
.lib './passive_corner_lv.inc' lvrmin
.lib './passive_corner_lv.inc' lvcmin
.lib './passive_corner_lv.inc' lvdmax
.lib './process_lv.inc' lvstats
.lib './process_hv.inc' hvstats
.inc './models.inc'
.endl fff
*
***********************************************************************
* "SSF" functional corner : "Slow" NMOS, "Slow" PMOS, "Slow" Passives
***********************************************************************
.lib ssf
.lib './fixed_corner_lv.inc' lvssf
.lib './fixed_corner_hv.inc' hvssf
.lib './fixed_corner_hv.inc' hvrmax
.lib './fixed_corner_hv.inc' hvbiplb
.lib './passive_corner_lv.inc' lvrmax
.lib './passive_corner_lv.inc' lvcmax
.lib './passive_corner_lv.inc' lvdmin
.lib './process_lv.inc' lvstats
.lib './process_hv.inc' hvstats
.inc './models.inc'
.endl ssf
*
***********************************************************************
* "FS" corner : "Fast" NMOS, "Slow" PMOS, "Nom" Passives
***********************************************************************
.lib fs
.lib './fixed_corner_lv.inc' lvfs
.lib './fixed_corner_hv.inc' hvfs
.lib './fixed_corner_hv.inc' hvrtt
.lib './fixed_corner_hv.inc' hvbiptt
.lib './passive_corner_lv.inc' lvrtt
.lib './passive_corner_lv.inc' lvctt
.lib './passive_corner_lv.inc' lvdtt
.lib './process_lv.inc' lvstats
.lib './process_hv.inc' hvstats
.inc './models.inc'
.endl fs
*
***********************************************************************
* "SF" corner : "Slow" NMOS, "Fast" PMOS, "Nom" Passives
***********************************************************************
.lib sf
.lib './fixed_corner_lv.inc' lvsf
.lib './fixed_corner_hv.inc' hvsf
.lib './fixed_corner_hv.inc' hvrtt
.lib './fixed_corner_hv.inc' hvbiptt
.lib './passive_corner_lv.inc' lvrtt
.lib './passive_corner_lv.inc' lvctt
.lib './passive_corner_lv.inc' lvdtt
.lib './process_lv.inc' lvstats
.lib './process_hv.inc' hvstats
.inc './models.inc'
.endl sf
*
***********************************************************************
* "FF" corner : "Fast" NMOS, "Fast" PMOS, "Fast" Passives
***********************************************************************
.lib ff
.lib './fixed_corner_lv.inc' lvff
.lib './fixed_corner_hv.inc' hvff
.lib './fixed_corner_hv.inc' hvrmin
.lib './fixed_corner_hv.inc' hvbiphs
.lib './passive_corner_lv.inc' lvrmin
.lib './passive_corner_lv.inc' lvcmin
.lib './passive_corner_lv.inc' lvdmax
.lib './process_lv.inc' lvstats
.lib './process_hv.inc' hvstats
.inc './models.inc'
.endl ff
*
***********************************************************************
* "SS" corner : "Slow" NMOS, "Slow" PMOS, "Slow" Passives
***********************************************************************
.lib ss
.lib './fixed_corner_lv.inc' lvss
.lib './fixed_corner_hv.inc' hvss
.lib './fixed_corner_hv.inc' hvrmax
.lib './fixed_corner_hv.inc' hvbiplb
.lib './passive_corner_lv.inc' lvrmax
.lib './passive_corner_lv.inc' lvcmax
.lib './passive_corner_lv.inc' lvdmin
.lib './process_lv.inc' lvstats
.lib './process_hv.inc' hvstats
.inc './models.inc'
.endl ss
*
***********************************************************************
* "MC" : Monte Carlo (statistical) analysis
***********************************************************************
.lib mc
.lib './fixed_corner_lv.inc' lvtt
.lib './fixed_corner_hv.inc' hvtt
.lib './fixed_corner_hv.inc' hvrtt
.lib './fixed_corner_hv.inc' hvbiptt
.lib './passive_corner_lv.inc' lvrtt
.lib './passive_corner_lv.inc' lvctt
.lib './passive_corner_lv.inc' lvdtt
.lib './process_lv.inc' lvstats
.lib './process_hv.inc' hvstats
.inc './models.inc'
.endl mc

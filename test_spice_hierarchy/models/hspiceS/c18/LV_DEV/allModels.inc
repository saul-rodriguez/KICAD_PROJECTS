* Path, Component, Release: cmos7base/rel/HSPICE/models/allModels.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
* *****************************************************************************
*
*>  7RF / 7WL  HSPICE model .lib file to define include statements
*                  for nominal, fixed corner and Monte Carlo analyses.
*
*
* *****************************************************************************
*
***********************************************************************
* "TT" corner : Nominal (default) process and Monte Carlo analyses
***********************************************************************
.lib tt
.lib './fixed_corner' tt
.lib './skew.file' stats
.inc './skew_psp.file'
.inc './models.inc'
.endl tt
*
***********************************************************************
* "FFF" functional corner : "Fast" NMOS, "Fast" PMOS
***********************************************************************
.lib fff
.lib './fixed_corner' fff
.lib './skew.file' stats
.inc './skew_psp.file'
.inc './models.inc'
.endl fff
*
***********************************************************************
* "SSF" functional corner : "Slow" NMOS, "Slow" PMOS
***********************************************************************
.lib ssf
.lib './fixed_corner' ssf
.lib './skew.file' stats
.inc './skew_psp.file'
.inc './models.inc'
.endl ssf
*
***********************************************************************
* "FS" corner : "Fast" NMOS, "Slow" PMOS
***********************************************************************
.lib fs
.lib './fixed_corner' fs
.lib './skew.file' stats
.inc './skew_psp.file'
.inc './models.inc'
.endl fs
*
***********************************************************************
* "SF" corner : "Slow" NMOS, "Fast" PMOS
***********************************************************************
.lib sf
.lib './fixed_corner' sf
.lib './skew.file' stats
.inc './skew_psp.file'
.inc './models.inc'
.endl sf
*
***********************************************************************
* "FF" corner : "Fast" NMOS, "Fast" PMOS
***********************************************************************
.lib ff
.lib './fixed_corner' ff
.lib './skew.file' stats
.inc './skew_psp.file'
.inc './models.inc'
.endl ff
*
***********************************************************************
* "SS" corner : "Slow" NMOS, "Slow" PMOS
***********************************************************************
.lib ss
.lib './fixed_corner' ss
.lib './skew.file' stats
.inc './skew_psp.file'
.inc './models.inc'
.endl ss

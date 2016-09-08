* Path, Component, Release: cmhv7sf/rel/HSPICE/models/esdnsh_base.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
************************************************************************************
*
*   Licensed Materials 
*
************************************************************************************
* 
* ESD nMOSFETs model 
* Please note this release enables only esdnfet (1.8V gate silicided) and esdnfetm (5.0V gate-non-silicided) models.
*  esdnfet  (esdoxide=1, gns=0)
*  esdnfetm (esdoxide=4, gns=1)

.subckt esdnsh_base (d g s b)  wesd=1u lesd=1u esdoxide=1 nf=1 ldop=2.0u lsop=0.48u gns=0 

 xesdnsh_base_va   (d g s b)  esdnsh_base_va wesd=wesd lesd=lesd nf=nf ldop=ldop lsop=lsop esdoxide=esdoxide gns=gns esd_event=esd_event esd_exit=esd_exit

.ends esdnsh_base

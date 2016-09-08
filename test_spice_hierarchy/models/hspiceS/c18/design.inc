* Path, Component, Release: cmrf7sf/rel/HSPICE/models/design.inc, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 1.1 09/11/18 12:15:31
*
* *****************************************************************************
*
*>  IBM CMRF7SF    HSPICE file for global switches, corner
*                  parameters and other user-defined settings
*
* IBM CONFIDENTIAL
* (C) 2009 IBM Corporation
*
* Licensed Materials - Property of IBM
* US Government Users Restricted Rights - Use, duplication or disclosure
* restricted by GSA ADP Schedule contract with IBM Corporation.
*
* *****************************************************************************
*
* Custom Process Corner Parameters:
* --------------------------------
*
* Please read the "Corner Simulation Methodology" section of the CMRF7SF
* Model Reference Guide before running corner simulations.
*
* The following corner parameter flags affect the skew parameters for a group
* of devices.  If a skew parameter is shared between different groups, it is
* varied only in one group (where it is expected to have a dominant effect) to
* keep it physical.
*
* Set the following cor_* flags between -3 and +3 to get the corresponding
* sigma variations in the skew parameters of the devices affected.
*
* Following corner parameters affect a group of devices in a dominant manner.
* Positive values of the corner parameter give following characteristics:
*  cor_nmos: High current, high speed for NMOS devices
*  cor_pmos: High current, high speed for PMOS devices
*  cor_jfet: High current, high speed for JFET devices
*  cor_res : High resistance for resistors
*  cor_cap : High capacitance for capacitors
*  cor_ind : High quality factor for inductors & transmission lines
*
* The following corner parameters affect more than one group of devices in a
* dominant manner. A positive value for these corner parameters gives these
* characteristics:
*  cor_tox : Small oxide thickness for thin-oxide MOSFETs, PCDCAPs,
*                  and nMOS varactors (high current, high capacitance)
*  cor_toxdg : Small oxide thickness for dual-gate MOSFETs, PCDCAPs,
*                    and nMOS varactors (high current, high capacitance)
*  cor_toxtg : Small oxide thickness for triple-gate MOSFETs, PCDCAPs,
*                    and nMOS varactors (high current, high capacitance)
*  cor_pc  : Small gate length for all MOSFETs (high current)
*  cor_rx  : Large width for for all MOSFETs (high current)
*  cor_noin : Low flicker (1/f) noise for NMOS devices
*  cor_noip : Low flicker (1/f) noise for PMOS devices
*
* Set these parameters to +3 (or -3) for 3-sigma variations in process
* parameters to skew device characteristics as mentioned above.
*
* *****************************************************************************
*
* MOSFET STI Stress:
* -----------------
*
* gsti      Switch to enable the STI stress effect (thin oxide NFETs only).
*
*     = 2   Stress effect enabled and calculated for all devices based
*           on the value of netlist parameters (AS, AD).
*
*     = 0   Stress effect disabled independent of any instance parameters.
*
*     = 1   (default) -- Stress effect included based on setting of local (stis)
*           parameter for each device instance; stis = 2, enabled (default).
*
* *****************************************************************************
*
* VLNPN and Resistor Self-Heating:
* -------------------------------
*
* gsh       Switch to enable vlnpn, resistor self-heating effect.
*
*     = 2   (default) -- Self-heating enabled for devices with this effect.
*
*     = 1   Self-heating effect controlled by instance parameter 'sh' setting.
*
*     = 0   Self-heating effect disabled independent of any instance parameter.
*
*
* VLNPN Impact Ionization:
* -----------------------
*
* gii       Switch to enable vlnpn impact ionization modeling.
*
*     = 2   (default) -- Impact ionization enabled for all vlnpn devices.
*
*     = 1   Impact ionization controlled by instance parameter 'ii' setting.
*
*     = 0   Impact ionization disabled independent of any instance parameter.
*
*
* Wafer Thickness:
* ---------------
*
* waferthk : Wirebond parts have various backside grind thicknesses available.
*            This parameter is provided for the user to over-ride the default
*            setting of 737 microns for the p- wafer thickness and is used in
*            the inductor models.
*
* ****************************************************************************
*
* ESD Model Switches:
* ------------------
*
* esd_event   Switch to specify ESD event switching
*
*     = 0   (default) -- ESD high current features disabled
*
*     = 1     ESD high current features enabled for Human Body Model (HBM)
*
*     = 2     ESD high current features enabled for Machine Model (MM)
*
*     = 3     ESD high current features enabled for Charge Device Model (CDM)
* 
* esd_exit    Switch to stop simulation if ESD failure occurs
*
*     = 1   (default) -- Simulation ends if ESD failure is encountered
*
*     = 0     Continue with simulation even if ESD failure occurs
* 
* esd_extr    Switch to include wiring parasitics for pre-layout simulation
*
*     = 0   (default) -- Do not include estimated wiring resistance/capacitance
*
*     = 1     Include estimated wiring parasitic resistance/capacitance
*
* ****************************************************************************
*
.lib noitm
.param
+ cor_nmos=0
+ cor_pmos=0
+ cor_jfet=0
+ cor_ind=0
+ cor_tox=0
+ cor_toxdg=0
+ cor_toxtg=0
+ cor_pc=0
+ cor_rx=0
+ cor_noin=0
+ cor_noip=0
+ gsti=1
+ gsh=2
+ gii=2
+ waferthk=737.0
+ esd_event=0
+ esd_exit=1
+ esd_extr=0
+ p5vonly=0
+ phires=0
.inc './LV_DEV/wafer.inc' 
.endl noitm
*********************
.lib noimax
.param
+ cor_nmos=0
+ cor_pmos=0
+ cor_jfet=0
+ cor_ind=0
+ cor_tox=0
+ cor_toxdg=0
+ cor_toxtg=0
+ cor_pc=0
+ cor_rx=0
+ cor_noin=-3
+ cor_noip=-3
+ gsti=1
+ gsh=2
+ gii=2
+ waferthk=737.0
+ esd_event=0
+ esd_exit=1
+ esd_extr=0
+ p5vonly=0
+ phires=0
.inc './LV_DEV/wafer.inc' 
.endl noimax
*********************
.lib noimin
.param
+ cor_nmos=0
+ cor_pmos=0
+ cor_jfet=0
+ cor_ind=0
+ cor_tox=0
+ cor_toxdg=0
+ cor_toxtg=0
+ cor_pc=0
+ cor_rx=0
+ cor_noin=3
+ cor_noip=3
+ gsti=1
+ gsh=2
+ gii=2
+ waferthk=737.0
+ esd_event=0
+ esd_exit=1
+ esd_extr=0
+ p5vonly=0
+ phires=0
.inc './LV_DEV/wafer.inc' 
.endl noimin
*********************
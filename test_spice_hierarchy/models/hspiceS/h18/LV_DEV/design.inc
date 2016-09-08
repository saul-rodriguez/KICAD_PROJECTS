* Path, Component, Release: cmhv7sf/rel/HSPICE/models/design.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HSPICE design file for global switches, corner
*		   parameters and other user-defined settings
*
*
* *****************************************************************************
*
* Custom Process Corner Parameters:
* --------------------------------
*
* Please read the "Corner Simulation Methodology" section of the CMHV7SF
* Model Reference Guide before running corner simulations.
*
* The following corner parameter flags affect the process parameters for a
* group of devices. If a process parameter is shared between different groups,
* it is varied only in one group (where it is expected to have a dominant
* effect) to keep it physical.
*
* Set the following cor_* flags between -3 and +3 to get the corresponding
* sigma variations in the process parameters of the devices affected.
*
* Following corner parameters affect a group of devices in a dominant manner.
* Positive values of the corner parameter give following characteristics:
*  cor_hv_nmos: High current, high speed for high voltage NMOS devices
*  cor_hv_pmos: High current, high speed for high voltage PMOS devices
*  cor_lv_nmos: High current, high speed for low voltage NMOS devices
*  cor_lv_pmos: High current, high speed for low voltage PMOS devices
*  cor_hv_bip : High current, high speed for high voltage parasitic bipolars
*  cor_dio    : High current for LV forward-biased diodes
*  cor_res    : High resistance for LV resistors
*  cor_hv_res : High resistance for HV Well resistors
*  cor_cap    : High capacitance for BEOL capacitors
*  cor_ind    : High capacitance for vncaps; low metal line resistance
*
* The following corner parameters affect more than one group of devices in a
* dominant manner. A positive value for these corner parameters gives these
* characteristics:
*  cor_tox  : Small oxide thickness for all thin-oxide MOSFETs, LV PCDCAPs
*		    and MOS varactors (high current, high capacitance)
*  cor_toxm : Small oxide thickness for all medium-oxide MOSFETs, LV PCDCAPs
*		    and MOS varactors (high current, high capacitance)
*  cor_toxh : Small oxide thickness for all thick-oxide MOSFETs (high current)
*  cor_pc   : Small gate length for all LV MOSFETs (high current)
*  cor_rx   : Large width for for all LV MOSFETs (high current)
*  cor_hv_noin : Low flicker (1/f) noise for high voltage NMOS devices
*  cor_hv_noip : Low flicker (1/f) noise for high voltage PMOS devices
*  cor_lv_noin : Low flicker (1/f) noise for low voltage NMOS devices
*  cor_lv_noip : Low flicker (1/f) noise for low voltage PMOS devices
*
* Set these parameters to +3 (or -3) for 3-sigma variations in process
* parameters to skew device characteristics as mentioned above.
*
* *****************************************************************************
*
* Low Voltage MOSFET STI Stress:
* -----------------------------
*
* gstis	    Switch to enable the STI stress effect (thin oxide devices only).
*
*     = 2   Stress effect enabled and calculated for all devices based
*	    on the value of netlist parameters (AS, AD).
*
*     = 0   Stress effect disabled independent of any instance parameters.
*
*     = 1   (default) -- Stress effect included based on setting local (lstis)
*	    parameter for each device instance; lstis = 2, enabled (default).
*
*
* Resistor Self-Heating:
* ---------------------
*
* gsh	    Switch to enable low voltage resistor self-heating effect.
*
*     = 2   (default) -- Self-heating enabled for devices with this effect.
*
*     = 1   Self-heating effect controlled by instance parameter 'sh' setting.
*
*     = 0   Self-heating effect disabled independent of any instance parameter.
*
* *****************************************************************************
*
* Wafer Thickness:
* ---------------
*
* waferthk : Wirebond parts have various backside grind thicknesses available.
*	     This parameter is provided for the user to over-ride the default
*	     setting of 737 microns for the p- wafer thickness and is used in
*	     the inductor models.
*
* ****************************************************************************
*
* ESD Model Switches:
* ------------------
*
* esd_event Switch to specify ESD event switching
*
*     = 0   (default) -- ESD high current features disabled
*
*     = 1   ESD high current features enabled for Human Body Model (HBM)
*
*     = 2   ESD high current features enabled for Machine Model (MM)
*
*     = 3   ESD high current features enabled for Charge Device Model (CDM)
*
* esd_exit  Switch to stop simulation if ESD failure occurs
*
*     = 1   (default) -- Simulation ends if ESD failure is encountered
*
*     = 0   Continue with simulation even if ESD failure occurs
*
* esd_extr  Switch to include wiring parasitics for pre-layout simulation
*
*     = 0   (default) -- Do not include estimated wiring resistance/capacitance
*
*     = 1   Include estimated wiring parasitic resistance/capacitance
*
* ****************************************************************************
.param
+ cor_hv_nmos=0
+ cor_hv_pmos=0
+ cor_lv_nmos=0
+ cor_lv_pmos=0
+ cor_hv_bip=0
+ cor_dio=0
+ cor_res=0
+ cor_hv_res=0
+ cor_cap=0
+ cor_ind=0
+ cor_tox=0
+ cor_toxm=0
+ cor_toxh=0
+ cor_pc=0
+ cor_rx=0
+ cor_hv_noin=0
+ cor_hv_noip=0
+ cor_lv_noin=0
+ cor_lv_noip=0
+ gstis=1
+ gsh=2
+ waferthk=737.0
+ esd_event=0
+ esd_exit=1
+ esd_extr=0

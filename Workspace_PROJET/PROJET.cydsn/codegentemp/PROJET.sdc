# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\jlabe\Desktop\H21\GBM2100_Projet\PROJET\Workspace_PROJET\PROJET.cydsn\PROJET.cyprj
# Date: Thu, 08 Apr 2021 15:44:24 GMT
#set_units -time ns
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyClk_LF} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyFLL} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fll}]]
create_clock -name {CyClk_HF0} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/hfclk_0}]]
create_clock -name {CyClk_Fast} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fastclk}]]
create_clock -name {CyClk_Peri} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk}]]
create_generated_clock -name {CyClk_Slow} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/slowclk}]]
create_generated_clock -name {UART_1_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 37 73} [list [get_pins {ClockBlock/ff_div_1}]]
create_generated_clock -name {I2C_1_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 5 9} [list [get_pins {ClockBlock/ff_div_2}]]
create_generated_clock -name {ADC_intSarClock} -source [get_pins {ClockBlock/periclk}] -edges {1 51 101} [list [get_pins {ClockBlock/ff_div_49}]]
create_generated_clock -name {EINK_Clock} -source [get_pins {ClockBlock/periclk}] -edges {1 25001 50001} [list [get_pins {ClockBlock/ff_div_11}]]
create_generated_clock -name {PWM_CLOCK} -source [get_pins {ClockBlock/periclk}] -edges {1 2501 5001} [list [get_pins {ClockBlock/ff_div_12}]]
create_generated_clock -name {CY_EINK_SPIM_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/ff_div_6}]]
create_clock -name {CyPeriClk_App} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk_App}]]
create_clock -name {CyIMO} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/imo}]]


# Component constraints for C:\Users\jlabe\Desktop\H21\GBM2100_Projet\PROJET\Workspace_PROJET\PROJET.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\jlabe\Desktop\H21\GBM2100_Projet\PROJET\Workspace_PROJET\PROJET.cydsn\PROJET.cyprj
# Date: Thu, 08 Apr 2021 15:44:00 GMT

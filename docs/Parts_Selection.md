# Parts Selection for Low Gain Radio  
**Table of Contents**
 * [Microcontroller](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#U1-NXP-MKW01Z128)   
 * [PA](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#U2-SkyWorks-SKY65116)  
 * [LNA](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#U8-MAACOM-MAAL-010704)  
 * [RF-Switch](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#u9-skyworks-sky13405_490f)  
 * [MCU LDO](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#u4-texas-instruments-lp5907mfx-33)  
 * [PA LDO](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#u7-st-microelectronics-dm00102135)
 * [LNA LDO](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#u6-texas-instruments-lp5907mfx-33)  
 * [SPI Cache](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#u3-winbond-w25q80dvsnig-tr)  
 * [Crystal](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#y1-epson-fa-20h)  
 * [JTAG Connector](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#cm1-cnc-tech-3220-10-0100-00)
 * [40 Pin Header](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#y1-harwin-inc-m50-3202045)
 * [MCX Connector](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#cf2-linx-technologies-inc-conmcx003062) 
 * [Inverter](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#u5a-fairchild-semiconductor-nc7sz05p5x)
 * [RF Shield (1)](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#sh1-laird-technologies-bmi-s-202-c-bmi-s-202-f)
 * [RF Shield (2)](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#sh2-laird-technologies-bmi-s-202-c-bmi-s-202-f)
 * [Electrolytic Capacitor](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#c43-avx-tajc107k010rnj)
 * [LEDs](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#leds)
 * [Capacitors](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#capacitors)
 * [Inductors](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#inductors)
 * [Resistors](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#resistors)


#### Format note  
Eagle Referance, Manufacturer, Manufacturer's Part Number  
Vendor  
Vendor Part No  
Datasheet  
Reasons  
Rad-hard Analogue  

#### U1 NXP MKW01Z128:  
Part: Microcontroller  
Vendor: Digi-Key  
Vendor Part No.: MKW01Z128CHN-ND  
[Datasheet](http://cache.nxp.com/files/microcontrollers/doc/data_sheet/MKW01Z128.pdf)  
Reasons: Requirement for the project. Chosen since it has an integrated transceiver, needed peripherals and meets JDEC standards.     
Rad-Hard Analogue: N/A  
  
#### U2 SkyWorks SKY65116: 
Part: Power Amplifier  
Vendor: Mouser    
Vendor Part No.: 873-SKY65116-21  
[Datasheet](http://www.skyworksinc.com/uploads/documents/SKY65116_200510I.pdf)  
Reasons: Able to provide 1W power output. Also has low voltage rails, but asks for a higher current draw (~1-1.3A).  
Rad-Hard Analogue: N/A  
  
#### U8 MAACOM MAAL-010704:  
Part: Low Noise Amplifier  
Vendor: Digi-Key    
Vendor Part No.: 1465-1261-1-ND  
[Datasheet](http://cdn.macom.com/datasheets/MAAL-010704.pdf)  
Reasons: Provides >0.7dB Noise level at average space temperatures (~-40C) at 436.5MHz. At different temperatures, we see an increase of about .1~.2dBs at the same frequency, so it's not perfect though. 
Rad-Hard Analogue: N/A  
**_Alternatives_**     
Part No.: HMC616LP3    
Manufacturer: Hittite  
[Datasheet](http://www.radiant.su/other/hittite/pdf/hmc616lp3.pdf)  
Reasons: This part would be better than the one selected. Provides >0.6dB Noise at all temperatures and at most frequencies. At average space temperatures, around 0.3dB Noise level at 436.5MHz. However it is vaporware in the USA. It might be available from China, however shipping and part price is expensive/long.  
Part No.: SKY67110_396LF  
Manufacturer: SkyWorks  
[Datasheet](http://www.skyworksinc.com/uploads/documents/SKY67110_396LF_201792B.pdf)  
Reasons: Brand new part from Skyworks. Would work better than what we have. Has a gain of ~21dB at desired frequency and a noise figure of 0.65dB at 25C and around 0.5dB at 40C. Seems like a slightly more complicated setup however.   

#### U9 SkyWorks SKY13405_490F:    
Part: RF Switch   
Vendor: Digi-Key  
Vendor Part No.: 863-1649-1-ND  
[Datasheet](http://www.skyworksinc.com/uploads/documents/SKY13405_490LF_201609I.pdf)  
Reasons: Comes from SkyWorks which has been a reliable manufacturer for RF parts for this project (such as the PA). Small footprint, it has a low insertion loss and works within the desired frequency range.   
Rad-Hard Analogue: N/A  
**_Alternatives_**     
Part No.: PE42723A-Z      
Manufacturer: Peregrine-Semiconductor    
[Datasheet](http://www.psemi.com/pdf/datasheets/pe42723ds.pdf)  
Reasons: Better footprint for the way the kw0x outputs Tx and Rx. This would get rid of the need for an inverter. Also has a better insertion loss and similar footprint. This switch is a possibility for the next revision of the LGR.  

#### U4 Texas Instruments LP5907MFX-3.3:  
Part: LNA LDO  
Vendor: Digi-Key    
Vendor Part No.: 296-38557-1-ND      
[Datasheet](http://www.ti.com/lit/ds/symlink/lp5907.pdf)  
Reasons: Same LDO as MCU so easy to access and cheaper to buy. Again, it also has low noise rejection. Also has internal pull-down resistors and the same footprint as the AAT3215 which is what we originally designed the board to use.    
Rad-Hard Analogue: N/A    
**_Alternatives_**    
Part No.: AAT3215    
Manufacturer: Skyworks    
[Datasheet](http://www.skyworksinc.com/uploads/documents/AAT3215_202408B.pdf)  
Reasons: This was the original choice, but manufacturing stopped during the design period, meaning we could only purchase parts by the 3,000 instead of 1 at a time.   
Part No.: TPS789xx      
Manufacturer: Texas Instruments  
[Datasheet](http://www.mouser.com/ds/2/405/tps789-558350.pdf)  
Reasons: Works, but went with the same LDO as the LNA for simplicity and cost effectiveness.  
 
#### U7 ST Microelectronics DM00102135:  
Part: PA LDO  
Vendor: Digi-Key  
Vendor Part No.: 497-15229-2-ND  
[Datasheet](http://www.mouser.com/ds/2/389/DM00102135-524580.pdf)  
Reasons:  The PA requires a high current draw, much larger than the LNA or MCU so it required its own LDO. This LDO allows for up to 2A output, which is about 500mA above what's required. Also looking for a low drop-out voltage which this has a fairly decent value at 250mV at max.  
Rad-Hard Analogue: N/A  

#### U6 Texas Instruments LP5907MFX-3.3:  
Part: LNA LDO  
Vendor: Digi-Key    
Vendor Part No.: 296-38557-1-ND      
[Datasheet](http://www.ti.com/lit/ds/symlink/lp5907.pdf)  
Reasons: Same LDO as MCU so easy to access and cheaper to buy. Again, it also has low noise rejection. Also has internal pull-down resistors and the same footprint as the AAT3215 which is what we originally designed the board to use.    
Rad-Hard Analogue: N/A    
**_Alternatives_**    
Part No.: AAT3215   
Manufacturer: Skyworks    
[Datasheet](http://www.skyworksinc.com/uploads/documents/AAT3215_202408B.pdf)  
Reasons: This was the original choice, but manufacturing stopped during the design period, meaning we could only purchase parts by the 3,000 instead of 1 at a time.  

#### U3 Winbond W25Q80DVSNIG TR:  
Part: SPI Cache  
Vendor: Digi-Key  
Vendor Part No.: W25Q80DVSNIG CT-ND    
[Datasheet](http://www.winbond.com/resource-files/w25q80dv_revf_02112015.pdf)  
Reasons: 8MB worth of storage for a boot loader. Easy hardware implementation.   
Rad-Hard Analogue: N/A  
**_Alternative_**       
Part No.: LE25FU406BMB     
Manufacturer: SANYO      
[Datasheet](http://media.digikey.com/pdf/Data%20Sheets/ON%20Semiconductor%20PDFs/LE25FU406B.pdf)  
Reasons: 4MB storage. Unfortunately it was vaporware at the time and has less storage.   

#### Y1 Epson FA-20H:  
Part: MCU Crystal  
Vendor: Digi-Key   
Vendor Part No.: SER4044CT-ND	  
[Datasheet](https://support.epson.biz/td/api/doc_check.php?dl=brief_FA-20H_en.pdf)  
Reasons: Fits the frequency we wanted at 32MHz for bumping up the integrated transceiver to 48MHz. High bit rate operations for 600kbits on the KW0x needed a crystal of maximum +- 15ppm, which this is 10ppm. Also fits within the temperature range of -40C-85C.    
Rad-Hard Analogue: Swept quartz is likely required for space operation. From some searching there seem to be none that fit the footprint of normal devices.  

#### CM1 CNC Tech 3220-10-0100-00:  
Part: JTAG Connector    
Vendor: Digi-Key  
Vendor Part No.: 1175-1627-ND    
[Datasheet](http://cnctech.us/pdfs/3220-XX-0100-00.pdf)  
Reasons: Supports serial wire debug interface which is the only one supported by our MCU.

#### CF1 Harwin Inc. M50-3202045:     
Part: 40-Pinout Header     
Vendor: Digi-Key  
Vendor Part No.: 952-1381-5-ND  	  
[Datasheet](https://cdn.harwin.com/pdfs/60page104.pdf)  
Reasons: Design requirement for communication from the Cubesat and allows for communication between the LGR and the System Controller.  

#### CF2 Linx Technologies Inc. CONMCX003.062:       
Part: MCX Connector   
Vendor: Digi-Key  
Vendor Part No.: CONMCX003.062-ND  	  
[Datasheet](http://www.linxtechnologies.com/resources/documents/mcx_rp-mcx_specs.pdf)  
Reasons: Connector for RF signal to the antenna on the back panel. Set at the back of the board next to the 40-Pinout so it can hook-up easily to the back panel of the Cubesat.  

#### U5A Fairchild Semiconductor NC7SZ05P5X:    
Part: Inverter       
Vendor: Digi-Key  
Vendor Part No.: NC7SZ05P5XTR-ND  	  
[Datasheet](https://www.fairchildsemi.com/datasheets/NC/NC7SZ05.pdf)  
Reasons: Inverter was needed since the PA and LNA outputs from the KW0x is reverse that of the RF Switch. In order to not have the lines cross, the inverter was used to invert the switch so that there wouldn't be a constant high voltage to the switch when receiving.  

#### SH1 Laird Technologies BMI-S-202-C BMI-S-202-F:     
Part: RF Shield 1    
Vendor: Digi-Key  
Vendor Part No. Shield: 903-1014-ND
Vendor Part No. Mount: 903-1051-1-ND  
[Datasheet Shield](http://cdn.lairdtech.com/home/brandworld/files/Board%20Level%20Shields%20Catalog%20Download.pdf)  
[Datasheet Mount](http://media.digikey.com/pdf/Data%20Sheets/Laird%20Technologies/BMI-S-202.pdf)  
Reasons: RF shielding for the PA portion of the RF part of the board to prevent interference from other signals.

#### SH2 Laird Technologies BMI-S-202-C BMI-S-202-F:     
Part: RF Shield 2   
Vendor: Digi-Key  
Vendor Part No.: 903-1014-ND  	 
Vendor Part No. Mount: 903-1051-1-ND   
[Datasheet Shield](http://cdn.lairdtech.com/home/brandworld/files/Board%20Level%20Shields%20Catalog%20Download.pdf)  
[Datasheet Mount](http://media.digikey.com/pdf/Data%20Sheets/Laird%20Technologies/BMI-S-202.pdf)  
Reasons: RF shielding for the LNA portion of the RF part of the board to prevent interference from other signals.

#### C43 AVX TAJC107K010RNJ:    
Part: Tantalum Capacitors - Solid SMD 10volts 100uF 10%  
Vendor: Digi-Key  
Vendor Part No.: 478-1704-1-ND  	  
[Datasheet](http://datasheets.avx.com/TAJ.pdf)  
Reasons: 100 uF Electrolytic capacitor is used in the LNA schematic setup in accordance to the recommended circuit from the datasheet for a <0.7dB noise figure.

### LEDs
**LED1, LED2, LED3, LED4, Lite-On Inc. LTST-C191KGKT**:      
Part: Green LEDs    
Vendor: Digi-Key  
Vendor Part No.: 160-1446-1-ND  
[Datasheet](http://optoelectronics.liteon.com/upload/download/DS22-2000-228/S_110_LTST-C191KGKT.pdf)  
Reasons: Green LEDs are used for debugging power. The green LEDs are placed at the front of the board for easy viewing and when on represent that the power line of interest is working. There are LEDs for the 3.3V power supply from the LNA and MCU LDOs, V+ from the photovoltaic bus and for the LDO on the PA. These will be removed before the actual launch and are only used for debugging purposes.    

**LED5, LED6, LED7, LED8, Broadcom Limited HSMA-C120**:      
Part: Amber LEDs    
Vendor: Digi-Key  
Vendor Part No.: 516-2486-1-ND    
[Datasheet](http://www.avagotech.com/docs/AV02-0975EN)  
Reasons: Amber LEDs are used for error checks during debugging and are placed on the debugging lines for PTC1-4. They will also be removed before actual launch.

### Capacitors

**C1, C3, C16, C18, C20, C21, C37, C40 Murata GRM188R71H103KA01D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0603 0.01uF 50volts X7R 10%  
Vendor: Digi-Key  
Vendor Part No.: 490-1512-2-ND  
[Datasheet](http://www.murata.com/~/media/webrenewal/support/library/catalog/products/capacitor/mlcc/c02e.ashx)  
Reasons: C1 and C3 are used for the feed network filter to prevent RF feedback into the MCUs VR_PA pins. They are designated by the kw0x datasheet. C16, C18, C20, and C21 are bypass capacitors on the PA as designated by the PA datasheet. Both C37 and C40 are used for the bypass line on the AAT3215 LDOs for both the MCU and LNA and are also dictated by their datasheet.   

**C2, C4 Murata GRM1885C1H120JA01D**:        
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0603 12pF 50volts C0G 5%  
Vendor: Digi-Key  
Vendor Part No.: 490-1405-2-ND  
[Datasheet](http://www.murata.com/~/media/webrenewal/support/library/catalog/products/capacitor/mlcc/c02e.ashx)  
Reasons: Used in part of the filter for both the Tx and Rx lines in effort to filter the signal to 436.5 MHz.    

**C5, C6, C9, C10 Murata GRM1885C1H150JA01D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0603 15pF 50volts C0G 5%  
Vendor: Digi-Key  
Vendor Part No.: 490-1407-2-ND  
[Datasheet](http://www.murata.com/~/media/webrenewal/support/library/catalog/products/capacitor/mlcc/c02e.ashx)  
Reasons: Used in part of the filter for both the Tx and Rx lines in effort to filter the signal to 436.5 MHz.   

**C7, C8 Murata GRM1885C1H2R2CA01D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0603 2.2pF 50volts C0G +/-0.25pF  
Vendor: Digi-Key  
Vendor Part No.: 490-9668-2-ND  
[Datasheet](http://www.murata.com/~/media/webrenewal/support/library/catalog/products/capacitor/mlcc/c02e.ashx)  
Reasons: Used in part of the filter for both the Tx and Rx lines in effort to filter the signal to 436.5 MHz.      

**C11, C12 Murata GQM1885C1H8R2CB01D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 25 volts 8.2pF ULTRA LOW ESR  
Vendor: Mouser  
Vendor Part No.: 81-GQM1885C1H8R2CB01    
[Datasheet](http://datasheets.avx.com/AutoU_Series.pdf)  
Reasons: Used in part of the filter for both the Tx and Rx lines in effort to filter the signal to 436.5 MHz.  

**C13, C15, C17, C19, C22, C38, C41, C52, C53 Murata GRM188R60J106ME47J**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 10uF 6.3Volts 20%  
Vendor: Digi-Key  
Vendor Part No.: 490-6405-2-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM188R60J106ME47-01.pdf)  
Reasons: C13 is a bypass capacitor on the PA LDO in accordance to the datasheet. C15, C17, C19, and C22 are bypass capacitors on the PA voltage lines also in accordance to the datasheet. Used as bypass caps on the LDO's vbias lines for the kw0x and LNA in accordance to the datasheet. C53 is something Andrew did.      

**C14, C26, C27, C28, C30, C31, C32, C33, C42, C45, C47, C48, C49 AVX 06035C104JAT2A**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 50volts 0.1uF 5% X7R  
Vendor: Digi-Key  
Vendor Part No.: 478-5778-1-ND  
[Datasheet](http://datasheets.avx.com/X7RDielectric.pdf)  
Reasons: C14 is a coupling capacitor between the PA and the 436.5 MHz filter. All the other 100nF capacitors are used as bypass capacitors valued in accordance to the datasheets.    

**C23, C24, C25 Murata GRM155R71H102KA01D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0402 1000pF 50volts X7R 10%  
Vendor: Digi-Key  
Vendor Part No.: 490-1303-1-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM155R71H102KA01-01.pdf)  
Reasons: The capacitors on the LNA are used in accordance to the datasheet. MACOM requested 0402s for these parts due to the LNAs possible sensitivity.    

**C34, C35 Murata GQM1885C2A6R0CB01D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0603 6.0pF 100volts C0G +/-0.25pF  
Vendor: Digi-Key  
Vendor Part No.: 490-3561-1-ND    
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GQM1875C2E6R0BB12-01.pdf)  
Reasons: Bypass capacitors on the Epson crystal for the MCU.    

**C36, C39 Murata GRM188R61A105KA61D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0603 1uF 10volts X5R 10%  
Vendor: Digi-Key  
Vendor Part No.: 490-1543-2-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM188R61A105KA61-01.pdf)  
Reasons: Bypass capacitors on the AAT3215 LDOs in accordance to their datasheet.    

**C44 Murata GRM155R71H103KA88D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0402 0.01uF 50volts X7R 10%  
Vendor: Digi-Key  
Vendor Part No.: 490-4516-1-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM155R71H103KA88-01.pdf)  
Reasons: Bypass capacitor for the LNA Vbias line. The values used here were suggested directly from the manufacturer allow for the proper noise factor at 436.5 MHz.    

**C46 Murata GRM188R60J106ME47J**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 10uF 6.3Volts 20%  
Vendor: Digi-Key  
Vendor Part No.: 490-6405-2-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM188R60J106ME47-01.pdf)  
Reasons: Output bypass capacitor on the PA LDO in accordance to the recommended circuit from the datasheet.  

**C50, C51, C54 Murata GRM155R71H102KA01D**:       
Part: Multilayer Ceramic Capacitors MLCC - SMD/SMT 0402 1000pF 50volts X7R 10%  
Vendor: Digi-Key  
Vendor Part No.: 490-1303-1-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM155R71H102KA01-01.pdf)  
Reasons: C50 and C51 are filters for the debugging LEDs. C54 isa filter between V+ and the RF_GND.   

#### Inductors

**L1, L2 Murata LQW18AN22NG00D**:  
Part: Fixed Inductors 0603 22nH 2% 500mA  
Vendor: Digi-Key  
Vendor Part No.: 490-6874-1-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/PDF/ENG/L0075S0080LQW18A_00.pdf)  
Reasons: L1 and L2 are used for the feed network filter to prevent RF feedback into the MCUs VR_PA pins. They are designated by the kw0x datasheet.    

**L3, L4, L5, L6 Murata LQW18AN15NG00D**:  
Part: Fixed Inductors 0603 15nH  
Vendor: Digi-Key  
Vendor Part No.: 490-6866-1-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/PDF/ENG/L0075S0080LQW18A_00.pdf)  
Reasons: Used in part of the filter for both the Tx and Rx lines in effort to filter the signal to 436.5 MHz.  

**L8 Murata LQW18AN82NG00D**:  
Part: Fixed Inductors 0603 82nH  
Vendor: Digi-Key  
Vendor Part No.: 490-6912-2-ND  
[Datasheet](http://search.murata.co.jp/Ceramy/image/img/PDF/ENG/L0075S0080LQW18A_00.pdf)  
Reasons: Used in the LNA Vbias to the output. Value was suggested by manufacturer for optimum Noise Factor (<0.7dB) at desired frequency of 436.5 MHz.  

#### Resistors

**R1	Samsung	RC1608F2490CS**:      
Part: RES SMD 249 OHM 1% 1/10W 0603  
Vendor: Digi-Key  
Vendor Part No.: 1276-4592-2-ND  
[Datasheet](http://media.digikey.com/pdf/Data%20Sheets/Samsung%20PDFs/RC_Series_ds.pdf)  
Reasons: Used in the LNA Vbias to the output. Value was suggested by manufacturer for optimum Noise Factor (<0.7dB) at desired frequency of 436.5 MHz.    

**R2, R3, R5	Yageo RC0603FR-0710KL**:      
Part: Thick Film Resistors - SMD 10K OHM 1%  
Vendor: Digi-Key  
Vendor Part No.: 311-10.0KHRCT-ND  
[Datasheet](http://www.yageo.com/documents/recent/PYu-RC_Group_51_RoHS_L_04.pdf)  
Reasons: Pull-up resistors on the power lines for the LDO and the SPI Cache's !HOLD and !WP.

**R4, R8, R9, R10, R11, R12 Yageo RC0603FR-071KL**:      
Part: Thick Film Resistors - SMD 1K OHM 1%  
Vendor: Digi-Key  
Vendor Part No.: 311-1.00KHRCT-ND  
[Datasheet](http://www.yageo.com/documents/recent/PYu-RC_Group_51_RoHS_L_04.pdf)  
Reasons: LED current limiting resistors. DNPs for launch.

**R6, R7 Yageo RC0603FR-071KL**:      
Part: Thick Film Resistors - SMD 1K OHM 1%    
Vendor: Digi-Key  
Vendor Part No.: 311-1.00KHRCT-ND  
[Datasheet](http://www.yageo.com/documents/recent/PYu-RC_Group_51_RoHS_L_04.pdf)  
Reasons: Current limiting resistor for PA and LNA LDO LEDs. DNPs for launch.

**R13, R14 Yageo RC0603JR-070RL**:      
Part: Thick Film Resistors - SMD ZERO OHM JUMPER  
Vendor: Digi-Key  
Vendor Part No.: 311-0.0GRTR-ND  
[Datasheet](http://www.yageo.com/documents/recent/PYu-RC_Group_51_RoHS_L_04.pdf)  
Reasons: Used for the separate ground between the signal and the LEDs for debugging. DNPs for launch. 



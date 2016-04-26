# Parts Selection for Low Gain Radio (Work in Progress)  
**Table of Contents**
 * [Microcontroller](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#microcontroller)   
 * [PA](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#pa)  
 * [LNA](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#lna)  
 * [RF-Switch](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#rf-switch)  
 * [MCU LDO](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#mcu-ldo)  
 * [PA LDO](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#pa-ldo)  
 * [LNA LDO](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#lna-ldo)  
 * [SPI Cache](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#spi-cache)  
 * [Crystal](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#crystal)  
 * [JTAG Connector](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#jtag-connector)
 * [40 Pin Header](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#40-pin-header)
 * [MCX Connector](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#mcx-connector)
 * [LEDs](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#leds)
 * [Inverter](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#inverter)
 * [Electrolytic Capacitor](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#electrolytic-capacitor)
 * [Capacitors](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#capacitors)
 * [Inductors](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#inductors)
 * [Resistors](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#resistors)
 * [RF Shield Frame](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#rf-shield-frame)
 * [RF Shield (1)](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#rf-shield-1)
 * [RF Shield (2)](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#rf-shield-2)

#### Format note  
EAGLE REF, MANF, MANF PART  
Vend  
Vend Part No  
Datasheet  
Reasons:  
Rad-hard:  

#### U1 NXP MKW01Z128:  
Part: Microcontroller  
Vendor: Digi-Key  
Vendor Part No.: MKW01Z128CHN-ND  
[Datasheet](http://cache.nxp.com/files/microcontrollers/doc/data_sheet/MKW01Z128.pdf)  
Reasons: Requirement for the project  
Rad-Hard Analogue: N/A  
  
#### U2 SkyWorks SKY65116: 
Part: Power Amplifier  
Vendor: SkyWorks  
Vendor Part No.: SKY65116  
[Datasheet](http://www.skyworksinc.com/uploads/documents/SKY65116_200510I.pdf)  
Reasons: Able to provide 1W power output. Also has low voltage rails, but asks for a higher current draw.  
Rad-Hard Analogue: N/A  
  
#### U8 MAACOM MAAL-010704:  
Part: Low Noise Amplifier 
Vendor: MAACOM  
Vendor Part No.: MAAL-010704    
[Datasheet](http://cdn.macom.com/datasheets/MAAL-010704.pdf)  
Reasons: Provides >0.7dB Noise level at average space temperatures (~-40C) at 436.5MHz.  
Rad-Hard Analogue: N/A  
**_Alternative_**   
Part No.: HMC616LP3    
Manufacturer: Hittite  
[Datasheet](http://www.radiant.su/other/hittite/pdf/hmc616lp3.pdf)  
Reasons: This part would be better than the one selected. Provides >0.6dB Noise at all temperatures and at most frequencies. At average space temperatures, around 0.3dB Noise level at 436.5MHz. However it is vaporware in the USA. It might be available from China, however shipping and part price is expensive/long.  

#### U9 SkyWorks SKY13405_490F:    
Part: RF Switch   
Vendor: SkyWorks  
Vendor Part No.: SKY13405_490F  
[Datasheet](http://www.skyworksinc.com/uploads/documents/SKY13405_490LF_201609I.pdf)  
Reasons: Comes from SkyWorks which has been a reliable manufacturer for RF parts for thsi project (such as the PA). Small footprint, it has a low insertion loss and is within the desired frequency range.   
Rad-Hard Analogue: N/A  

#### U4 SkyWorks AAT3215:
Part: MCU LDO 
Vendor: SkyWorks  
Vendor Part No.: AAT3215    
[Datasheet](http://www.skyworksinc.com/uploads/documents/AAT3215_202408B.pdf)  
Reasons: Low noise rejection. Cheap. Works for other parts as well.     
Rad-Hard Analogue:  
**_Alternative_**  
Part No.: TPS789xx      
Manufacturer: Texas Instruments  
[Datasheet](http://www.mouser.com/ds/2/405/tps789-558350.pdf)  
Reasons: Works, but went with the same LDO as the LNA for simplicity and cost effectiveness.  
 
#### U7 ST Microelectronics DM00102135:  
Part: PA LDO 
Vendor: Digi-Key  
Vendor Part No.: 497-15229-2-ND  
[Datasheet](http://www.st.com/web/en/resource/technical/document/datasheet/DM00102135.pdf)  
Reasons:  
Rad-Hard Analogue: N/A  

#### U6 SkyWorks AAT3215:  
Part: LNA LDO  
Vendor: SkyWorks  
Vendor Part No.: AAT3215    
[Datasheet](http://www.skyworksinc.com/uploads/documents/AAT3215_202408B.pdf)  
Reasons: Same LDO as MCU so easy to access and cheaper to buy. Again, it also has low noise rejection.   
Rad-Hard Analogue: N/A  

#### U3 Winbond W25Q80DVSNIG TR:  
Part: SPI Cache  
Vendor: Digi-Key  
Vendor Part No.: W25Q80DVSNIG CT-ND    
[Datasheet](http://www.winbond.com/resource-files/w25q80dv_revf_02112015.pdf)  
Reasons: 8MB worth of storage. Easy hardware implementation.   
Rad-Hard Analogue: N/A  
**_Alternative_**       
Part No.: LE25FU406BMB     
Manufacturer: SANYO      
[Datasheet](http://media.digikey.com/pdf/Data%20Sheets/ON%20Semiconductor%20PDFs/LE25FU406B.pdf)  
Reasons: 4MB storage. Unfortunately it was vaporware at the time and has less storage.   

#### Y1 Epson FA-20H:  
Part: MCU Crystal  
Vendor: Digi-Key   
Vendor Part No.: SER4044CT-ND	  
[Datasheet](https://support.epson.biz/td/api/doc_check.php?dl=brief_FA-20H_en.pdf)  
Reasons: Fits the frequency we wanted at 32MHz. High bit rate operations for 600kbits on the KW0x needed a crystal of maximum +- 15ppm, which this is 10ppm. Also fits within the temperature range of -40C-85C.    
Rad-Hard Analogue: Swept quartz is likely required for space operation. From some searching there seem to be none that fit the footprint of normal devices.

#### CM1 CNC Tech 3220-10-0100-00:  
Part: JTAG Connector    
Vendor: Digi-Key  
Vendor Part No.: 1175-1627-ND    
[Datasheet](http://cnctech.us/pdfs/3220-XX-0100-00.pdf)  
Reasons: Generic JTAG connector used from practicum.

#### Y1 Harwin Inc. M50-3202045:     
Part: 40-Pinout Header     
Vendor: Digi-Key  
Vendor Part No.: 952-1381-5-ND  	  
[Datasheet](https://cdn.harwin.com/pdfs/60page104.pdf)  
Reasons: Design requirement for communication from the Cubesat.

#### CF2 Linx Technologies Inc. CONMCX003.062:       
Part: MCX Connector   
Vendor: Digi-Key  
Vendor Part No.: CONMCX003.062-ND  	  
[Datasheet](http://www.linxtechnologies.com/resources/documents/mcx_rp-mcx_specs.pdf)  
Reasons: Connector for RF signal to the antenna on the back panel. Set at the back of the board next to the 40-Pinout so it can hook-up easily to the back panel of the Cubesat.

#### LEDs:      
Part No.: FA-20H  
Manufacturer: Epson  
Vendor: Digi-Key  
Vendor Part No.: SER4044CT-ND	  
Eagle Part Reference: Y1  
[Datasheet](https://support.epson.biz/td/api/doc_check.php?dl=brief_FA-20H_en.pdf)  
Reasons: Fits the frequency we wanted at 32MHz. High bit rate operations for 600kbits on the KW0x needed a crystal of maximum +- 15ppm, which this is 10ppm. Also fits within the temperature range of -40C-85C.    
Rad-Hard Analogue: Swept quartz is likely required for space operation. From some searching there seem to be none that fit the footprint of normal devices.  (TODO)

#### U5A Fairchild Semiconductor NC7SZ05P5X:    
Part: Inverter       
Vendor: Digi-Key  
Vendor Part No.: NC7SZ05P5XTR-ND  	  
[Datasheet](https://www.fairchildsemi.com/datasheets/NC/NC7SZ05.pdf)  
Reasons: Inverter was needed since the PA and LNA outputs from the KW0x is reverse that of the RF Switch. In order to not have the lines cross, the inverter was used to invert the switch so that there wouldn't be a constant high voltage to the switch when receiving.  

#### C43 AVX TAJC107K010RNJ:    
Part: Electrolytic Capacitor  
Vendor: Digi-Key  
Vendor Part No.: 478-1704-1-ND  	  
[Datasheet](http://datasheets.avx.com/TAJ.pdf)  
Reasons: Electrolytic capacitor was asked for at this point in accordance to the recommended circuit from the LNA datasheet. 

#### Capacitors:       
Part No.: FA-20H  
Manufacturer: Epson  
Vendor: Digi-Key  
Vendor Part No.: 490-1303-1-ND	  
Eagle Part Reference: Y1  
[Datasheet](https://support.epson.biz/td/api/doc_check.php?dl=brief_FA-20H_en.pdf)  
Reasons: Fits the frequency we wanted at 32MHz. High bit rate operations for 600kbits on the KW0x needed a crystal of maximum +- 15ppm, which this is 10ppm. Also fits within the temperature range of -40C-85C.    
Rad-Hard Analogue: Swept quartz is likely required for space operation. From some searching there seem to be none that fit the footprint of normal devices.  (TODO)

#### Inductors:      
Part No.: FA-20H  
Manufacturer: Epson  
Vendor: Digi-Key  
Vendor Part No.: SER4044CT-ND	  
Eagle Part Reference: Y1  
[Datasheet](https://support.epson.biz/td/api/doc_check.php?dl=brief_FA-20H_en.pdf)  
Reasons: Fits the frequency we wanted at 32MHz. High bit rate operations for 600kbits on the KW0x needed a crystal of maximum +- 15ppm, which this is 10ppm. Also fits within the temperature range of -40C-85C.    
Rad-Hard Analogue: Swept quartz is likely required for space operation. From some searching there seem to be none that fit the footprint of normal devices.  (TODO)

#### Resistors:    
Part No.: FA-20H  
Manufacturer: Epson  
Vendor: Digi-Key  
Vendor Part No.: SER4044CT-ND	  
Eagle Part Reference: Y1  
[Datasheet](https://support.epson.biz/td/api/doc_check.php?dl=brief_FA-20H_en.pdf)  
Reasons: Fits the frequency we wanted at 32MHz. High bit rate operations for 600kbits on the KW0x needed a crystal of maximum +- 15ppm, which this is 10ppm. Also fits within the temperature range of -40C-85C.    
Rad-Hard Analogue: Swept quartz is likely required for space operation. From some searching there seem to be none that fit the footprint of normal devices.  (TODO) 

#### SH1 & SH2 Laird Technologies BMI-S-202-F:    
Part: RF Shield Mount(s)     
Vendor: Digi-Key  
Vendor Part No.: 903-1051-1-ND  	  	  
[Datasheet](http://media.digikey.com/pdf/Data%20Sheets/Laird%20Technologies/BMI-S-202.pdf)  
Reasons:  

#### SH1 Laird Technologies BMI-S-202-C:     
Part: RF Shield 1    
Vendor: Digi-Key  
Vendor Part No.: 903-1014-ND  	  
[Datasheet](http://cdn.lairdtech.com/home/brandworld/files/Board%20Level%20Shields%20Catalog%20Download.pdf)  
Reasons: 

#### SH2 Laird Technologies BMI-S-202-C:     
Part: RF Shield 2   
Vendor: Digi-Key  
Vendor Part No.: 903-1014-ND  	  
[Datasheet](http://cdn.lairdtech.com/home/brandworld/files/Board%20Level%20Shields%20Catalog%20Download.pdf)  
Reasons: 

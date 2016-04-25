# Parts Selection  
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

### Low Gain Radio 

#### Microcontroller:  
Part No.: MKW01Z128   
Manufacturer: NXP  
Vendor: Digi-Key  
Vendor Part No.: MKW01Z128CHN-ND  
Eagle Part Reference: U1  
[Datasheet](http://cache.nxp.com/files/microcontrollers/doc/data_sheet/MKW01Z128.pdf)  
Reasons: Requirement for the project  
Rad-Hard Analogue: N/A  
  
#### PA: 
Part No.: SKY65116  
Manufacturer: SkyWorks  
Vendor: SkyWorks  
Vendor Part No.: SKY65116  
Eagle Part Reference: U2  
[Datasheet](http://www.skyworksinc.com/uploads/documents/SKY65116_200510I.pdf)  
Reasons: Able to provide 1W power output. Also has low voltage rails, but asks for a higher current draw.  
Rad-Hard Analogue: N/A  
  
#### LNA:  
Part No.: MAAL-010704  
Manufacturer: MAACOM  
Vendor: MAACOM  
Vendor Part No.: MAAL-010704    
Eagle Part Reference: U8  
[Datasheet](http://cdn.macom.com/datasheets/MAAL-010704.pdf)  
Reasons: Provides >0.7dB Noise level at average space temperatures (~-40C) at 436.5MHz.  
Rad-Hard Analogue: N/A  
**_Alternative_**   
Part No.: HMC616LP3    
Manufacturer: Hittite  
[Datasheet](http://www.radiant.su/other/hittite/pdf/hmc616lp3.pdf)  
Reasons: This part would be better than the one selected. Provides >0.6dB Noise at all temperatures and at most frequencies. At average space temperatures, around 0.3dB Noise level at 436.5MHz. However it is vaporware in the USA. It might be available from China, however shipping and part price is expensive/long.  

#### RF Switch:    
Part No.: SKY13405_490F  
Manufacturer: SkyWorks  
Vendor: SkyWorks  
Vendor Part No.: SKY13405_490F  
Eagle Part Reference: U9  
[Datasheet](http://www.skyworksinc.com/uploads/documents/SKY13405_490LF_201609I.pdf)  
Reasons: Comes from SkyWorks which has been a reliable manufacturer for RF parts for thsi project (such as the PA). Small footprint, it has a low insertion loss and is within the desired frequency range.   
Rad-Hard Analogue: N/A  

#### MCU LDO:
Part No.: AAT3215  
Manufacturer: SkyWorks  
Vendor: SkyWorks  
Vendor Part No.: AAT3215    
Eagle Part Reference: U4  
[Datasheet](http://www.skyworksinc.com/uploads/documents/AAT3215_202408B.pdf)  
Reasons: Low noise rejection. Cheap. Works for other parts as well.     
Rad-Hard Analogue:  
**_Alternative_**  
Part No.: TPS789xx      
Manufacturer: Texas Instruments  
[Datasheet](http://www.mouser.com/ds/2/405/tps789-558350.pdf)  
Reasons: Works, but went with the same LDO as the LNA for simplicity and cost effectiveness.  
 
#### PA LDO:  
Part No.: DM00102135  
Manufacturer: ST Microelectronics  
Vendor: Digi-Key  
Vendor Part No.: 497-15229-2-ND  
Eagle Part Reference: U7  
[Datasheet](http://www.st.com/web/en/resource/technical/document/datasheet/DM00102135.pdf)  
Reasons:  
Rad-Hard Analogue: N/A  

#### LNA LDO:  
Part No.: AAT3215  
Manufacturer: SkyWorks  
Vendor: SkyWorks  
Vendor Part No.: AAT3215    
Eagle Part Reference: U6  
[Datasheet](http://www.skyworksinc.com/uploads/documents/AAT3215_202408B.pdf)  
Reasons: Same LDO as MCU so easy to access and cheaper to buy. Again, it also has low noise rejection.   
Rad-Hard Analogue: N/A  

#### SPI Cache:  
Part No.: w25q80dv  
Manufacturer: Winbond  
Vendor: Digi-Key  
Vendor Part No.: W25Q80DVSSIG-ND    
Eagle Part Reference: U3    
[Datasheet](http://www.winbond-usa.com/resource-files/w25q80dv_revf_02112015.pdf)  
Reasons: 8MB worth of storage. Easy hardware implementation.   
Rad-Hard Analogue: N/A  
**_Alternative_**       
Part No.: LE25FU406BMB     
Manufacturer: SANYO      
[Datasheet](http://media.digikey.com/pdf/Data%20Sheets/ON%20Semiconductor%20PDFs/LE25FU406B.pdf)  
Reasons: 4MB storage. Unfortunately it was vaporware at the time and has less storage.   

#### Crystal:  
Part No.: FA-20H  
Manufacturer: Epson  
Vendor: Digi-Key  
Vendor Part No.: SER4044CT-ND	  
Eagle Part Reference: Y1  
[Datasheet](https://support.epson.biz/td/api/doc_check.php?dl=brief_FA-20H_en.pdf)  
Reasons: Fits the frequency we wanted at 32MHz. High bit rate operations for 600kbits on the KW0x needed a crystal of maximum +- 15ppm, which this is 10ppm. Also fits within the temperature range of -40C-85C.    
Rad-Hard Analogue: Swept quartz is likely required for space operation. From some searching there seem to be none that fit the footprint of normal devices.  

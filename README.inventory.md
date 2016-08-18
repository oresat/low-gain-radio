

### Version 1.2 boards

* Three boards total from OSHPARK.

* DIO0 Modwire: DIO0 was incorrectly connected to RESET (RF) during design.
 * This prevents DIO0 from being used as a Packet Mode information pin.
 * Reference: Table 7-3 p.7-7 MKW01xxRM Reference Manual, Rev. 3, 04/2016

#### Board A

* DIO0 Modwire	PTE30 -> RESET (RF)    Wed 02 August 2016
* Location: Jake Heath

#### Board B

* DIO0 Modwire
* Fails to program flash. Thu 18 August 2016 13:12:48 (PDT)
* Location: K Wilson 

#### Board C

* DIO0 Modwire
* Program flash but fails at switch to PLL clock. Thu 18 August 2016 13:13:02 (PDT)
* Location: K Wilson



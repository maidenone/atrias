# Hardware #

## Computers ##

| # | Model / Make | CPU | RAM | Ethernet adapters | Harddrive | location (CMU / UMi / OSU) |
|:--|:-------------|:----|:----|:------------------|:----------|:---------------------------|
|1  |Dell Optiplex 755|Intel Core 2 Quad @ 2.40 GHz|2 x 1GB, 2 x 512MB, 3GB total|Intel 82566DM-2 Gigabit|Western Digital Caviar 250GB 7200RPM|OSU                         |
|2  |Dell Optiplex GX260|Intel Pentium 4 (single) @ 3.06GHz|2 x 512MB|Intel 82540EM Gigabit Ethernet controller and Intel PRO/100 M Desktop Adapter 82557|Western Digital 80GB|OSU                         |
|3  |Zotac ZBOXHD-ID40 PLUS|Intel Atom (dual) D525 @ 1.8GHz|1 x 2GB|10/100/1000 ethernet (Realtek)|Samsung 320GB 5400RPM|OSU                         |

## Tested Setups ##

|#| Date | xpc-version | xpc-host | xpc-target | Boot Method | Results / Issues |
|:|:-----|:------------|:---------|:-----------|:------------|:-----------------|
|1|N/A   |R2011b (5.1) |1         |2           |PXE Netboot  |Test 4 failed (compiling and executing model on target PC)|
|2|6-29-12|R2012a (5.2) |1         |2           |PXE Netboot  |All tests successful! (Note: Needed to set up compiler)|

## Interesting links ##

[xpc and WiFi](http://www.mathworks.com/support/solutions/en/data/1-1BNXX/index.html?product=XP&solution=1-1BNXX)

# Ethercat #

Compatible Ethercat cards for xpc target are listed in Matlab documentation and under http://www.mathworks.com/help/toolbox/xpc/io_ref/bsc7yr_-1.html#bslz9wv-1

Asteriks for discontinued cards with link to notice;

|0x1229|	Intel PRO/100 M Desktop Adapter: 82557, 82558, [82559\*, 82550\*, 82551\*](http://www.intel.com/content/dam/doc/specification-update/product-change-notification-109390-01.pdf) |
|:-----|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|0x1209|	Fast Ethernet Controller: 82551xER, 82551IT                                                                                                                                     |
|0x1059|	[Fast Ethernet PCI Controller: 82551QM](http://www.intel.com/content/www/us/en/ethernet-controllers/82551qm-er-it-fast-ethernet-pci-mdi-x-appl-note.html)                       | [$29,08](http://www.nyetex.com/network-cards-n-adapters/26678-intel-pro-100-m-desktop-adapter.html)                                                                             |
|0x2449|	Integrated 10Base-T/100Base-T TX Ethernet Controller: 8x559ER                                                                                                                   |
|0x103A|	LAN Controller: 82562ET, 82562EZ, 82563ET, 82801DB                                                                                                                              |
|0x1039|	LAN Controller: 82562ET, 82562EZ, 82562VE, 82562VM                                                                                                                              |
|0x1050|	Pro/100 VE Network Connection: 8201EB, 8201ER                                                                                                                                   |
|0x27DC|	Intel PRO/100 VE Desktop Adapter: 82562V                                                                                                                                        |

## Medulla ESI files ##

Version: 0.2 (With distributed clock) 06/28/12

XML link: http://atrias.googlecode.com/svn/trunk/ethercat/ESC_files/Medulla.xml

EEPROM link: http://atrias.googlecode.com/svn/trunk/ethercat/ESC_files/medulla.bin

[more information](ETHERCAT_setup.md)
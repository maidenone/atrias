# Introduction #

The SII file is a binary file that is generated from the ESI (EtherCAT Slave Information) file. This binary is downloaded to the EEPROM on an EtherCAT to provide hardware configuration and to allow the slave to advertise it's PDO entries.

The real documentation for the SII file can be found starting on page 35 of the ETG1000.6 EtherCAT specification. This page simply contains some notes on the SII file and documents some parts of the file that appear to be undocumented in the EtherCAT specification, but are used by TwinCAT.

## General Category Structure ##
  * Although the SII file spec. has functionality for including a device icon in the SII file, it appears this is not used by Beckhoff in either TwinCAT or the EtherCAT Configurator.
  * Byte at address 0x000E of general category contains index of Group Name (not group Type which is stored at 0x0000).
  * Order string indexes the name of the device specified in type tag.
  * Byte 0x0004 of the general category is supposed to be reserved for future use, but The EtherCAT Configurator sets this byte to 1. I don't know what this value refers to, but my best guess is that it's an index to a string.

## Secondary FMMU Category ##
Although not documented in ETG1000.6, TwinCAT and EtherCAT Configurator use a second category for storing FMMU configuration information. Below is what I have been able to determine from the output of the EtherCAT Configurator. The following values are repeated once in the category for each FMMU specified in the ESI file.
| **Byte Address** | **Data Type** | **Parameter** |
|:-----------------|:--------------|:--------------|
| 0x0000           | Unsigned8     | Sort of Unknown. <br> Bit0 - Always 0 <br> Bit1 - Sync Manager Assigned (1 if true) |<br> Bit2 - Sync Unit Assigned (1 if true) <br> Bit3-7 - Always 1<br>
<tr><td> 0x0001           </td><td> Unsigned8     </td><td> Unknown -- Always 0xFF </td></tr>
<tr><td> 0x0002           </td><td> Unsigned8     </td><td> Assigned Sync Manager </td></tr>
<tr><td> 0x0003           </td><td> Unsigned8     </td><td> Assigned Sync Unit </td></tr></tbody></table>

<h2>PDO Flags</h2>
In the ETG1000.6 specification, the Flags field of the PDO Structure Category is listed for future use. However TwinCAT appears to use this flags word. By reverse engineering the generated SII files, I have determined the following flags, there may be more, but I can't tell.<br>
<ul><li>Bit 0: The PDO must be assigned to the default sync manager (set with Mandatory attribute of PdoType in ESI file)<br>
</li><li>Bit 4: PDO cannot be remapped (Set using Fixed attribute of PdoType in ESI file)</li></ul>

<h2>Sync Manager</h2>
The ETG1000.6 specification is not clear on how multiple sync manager elements should be put into the SII file. The SII file should contain a single sync manager category which contains the SyncM element multiple times, one for each defined sync manager.<br>
<br>
<h2>DC Clock</h2>

In the specification the DC clock category has the category ID of 60 assigned to it. However, it is listed as for future use and is not documented. TwinCAT does include a DC clock category in the SII files that it generates. I have reverse engineered the majority of the section, however there are 5 bytes at the end of the section which I have not been able to figure out, and are always zero. The following table describes the structure I have identified:<br>
<table><thead><th> <b>Byte Address</b> </th><th> <b>Data Type</b> </th><th> <b>Parameter</b> </th></thead><tbody>
<tr><td> 0x0000              </td><td> Unsigned32       </td><td> Cycle Time Sync 0 </td></tr>
<tr><td> 0x0004              </td><td> Signed32         </td><td> Shift Time Sync 0 </td></tr>
<tr><td> 0x0008              </td><td> Signed32         </td><td> Shift Time Sync 1 </td></tr>
<tr><td> 0x000C              </td><td> Signed16         </td><td> Cycle Time Sync 1 Factor </td></tr>
<tr><td> 0x000E              </td><td> Unsigned16       </td><td> Assign Activate Word </td></tr>
<tr><td> 0x0010              </td><td> Signed16         </td><td> Cycle Time Sync 0 Factor </td></tr>
<tr><td> 0x0012              </td><td> Unsigned8        </td><td> DC Sync Name (index to STRINGS) </td></tr>
<tr><td> 0x0013              </td><td> BYTE[<a href='5.md'>5</a>] </td><td> Unused? (Couldn't figure these bytes out) </td></tr>
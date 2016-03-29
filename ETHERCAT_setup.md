# Introduction #

EtherCat is an Ethernet-based industrial bus standard developed and maintained by the [EtherCat techology group (ETG)](http://www.ethercat.org).

We are using Ethercat to connect our main robot computer (EtherCat master / currently Zotac ZBoxHD) to the sensor/controller PCBs. The Ethercat slave controller (ESC) is a [Beckhoff ET1100](http://www.beckhoff.com/english.asp?ethercat/et1100_et1200.htm), a ATXMega128A1 distributes the information.

To provide the Ethercat master with necessary information about the network topology and the information the slaves expect and provide, a EtherCat slave identifier (ESI) is generated and stored in the slave's EEPROM.

# Introduction to the EtherCAT protocol #
EtherCAT is a master/slave bus, in which single device acts as a master and is connected to multiple slave devices. All slave devices are connected in a daisy chain fashion to the EtherCAT master. The master initiates all communication with the slaves. To either send or receive data from any of the slaves master sends an Ethernet encapsulated EtherCAT packet to the first slave. The first slave will then insert any data it transmits into the packet in real time as it forwards the packet to the next slave. The process continues down the chain of slaves until it reaches the end of the chain. When the packet reaches the end, it is returned back to the master by being passed back up through the slaves.

## Sync Mangers (Sm) and Fieldbus Memory Management Unit (FMMU) ##
There are two forms of communication through the EtherCAT protocol.
  * **Mailbox mode** is used to send commands to slaves. When either the master or slave sends a mailbox message, the receiving device must read the data before the more data can be sent. This mode ensures that no data gets lost.
  * **Buffered mode** allows the master and a slave to share data through a data buffer interface. In this mode, the master and slave can write or read data at any time. When a device reads data it will get the data transmitted in the most recent EtherCAT packet. This ensures that the most recent data will be received, but data can be lost.

For our applications, we are using the buffered mode because we do not need the functionality of the mailbox mode. In both these modes, this data sharing is managed by what is known as the Sync Manager. In the case of buffered mode, the sync manager keeps buffers for the master and the slave to make sure there are not data collisions. Each sync manager can be configured for one of four modes:
  * RX Mailbox - Mailbox receive to slave
  * TX Mailbox - Mailbox transmit from slave
  * RX Buffered - Buffered receive to slave
  * TX Buffered - Buffered transmit from slave

On the ET1100 there are four Sync Managers, labeled 0 through 3. Although any Sync manager can be configured to behave in any way, by EtherCAT convention sync managers 0 and 1 should be configured for RX and TX mailbox mode, and 2 and 3 should be configured for RX and TX buffered mode.

Although from slave and master program's perspective, the data being sent from a slave appears to be a chunk of memory that is the sync manager, all the data from all the slaves is actually placed into a single EtherCAT packet. The Fieldbus Memory Management Units (FMMUs) are the parts of the slave controller that are responsible for mapping memory from the Sync Managers into the EtherCAT frame. There has to be a FMMU associated with each sync manager so that the data from that sync manager is placed correctly into the EtherCAT frame. As with the Sync Manager the FMMU has to be configured with the direction a data direction, either input or output from the perspective of the slave.

## Process Data Objects (PDOs) ##
As mentioned earlier, we are using the Buffered mode for our data communications. The sync managers essentially provide a shared memory interface between a master and a slave. This great but it doesn't provide a way to define a communications protocol between a master and a slave. This problem is solved by Process Data Objects (PDOs). PDOs are a way of defining how data is packed into a buffered sync manager. The use of a standardized PDO description (as described in the ESI file) make it possible for any EtherCAT master stack to communicate with any slave without large amounts of customization.

Each Process Data Object is supposed to contain the information for a particular subsystem of the slave. A sync manager can have many PDOs and each PDO can contain more than one variable. To use and example from ATRIAS, each Medulla has one or more encoder PDOs, and each of those PDOs contain a variable for the encoder position and a timestamp variable containing the exact time when the reading was taken. This encapsulates everything you would need to know to use the data from the encoder.

All the PDOs are placed into the Sync Manager memory in the order that they have been defined in the ESI XML file. The size of the PDO is calculated based upon the sum of the sizes of the PDO elements as defined in the ESI file. Therefore, any one PDO element can be found in the Sync Manager memory based upon the order of PDOs in the ESI file, and the order and size of the elements of each PDO.


# Generating ESI #
The EtherCAT Slave Information (ESI) file is an XML file that is used by some EtherCAT master stacks to configure the slaves and generate network description files. However, it's main purpose is to describe how data is shared with the slave, including what sync managers it uses, and what PDOs are in each sync manager. The ESI file can also be used to generate an EEPROM image that can be downloaded to the slave so the slave will be able to identify it's self on the EtherCAT bus. It is important to note that the same ESI file cannot be used for any Medulla. Depending on what firmware is running on the xMega, what data that medulla wants to transmit and receive, a custom ESI file needs to be generated.

There are several ways to create the ESI file a Medulla slave. There are tools such as the [EtherCAT Design Tool](http://www.port.de/pages/products/industrial_ethernet/ethercat/tools/dt.php?lang=en) from Port gmbh. However, we have to had much luck using these tools, and since the ESI file is just and XML file it is not too difficult to write one by hand. This documentation will try to describe everything needed to create a basic ESI file for a Medulla, however the full description of ESI XML Schema can be found in the [ETG.2000 document](http://ethercat.org/MemberArea/Download/PDF/ETG2000_S_R_V1i0i4_EtherCATSlaveInformationSpecification.pdf) from the EtherCAT Technology Group.

## Global ESI File Elements ##
All information inside the ESI file is wrapped inside an EtherCATInfo element. This tag also contains the following tag to specify the xml schema used by the file.
```
<?xml version="1.0"?>
<EtherCATInfo xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="EtherCATInfo.xsd" Version="1.2">
</EtherCATInfo>
```

Inside this element there are two more elements. The Vendor element specifies the vendor ID and name of the EtherCAT slaves specified in the file. All devices in a file will have this vendor set as their vendor ID/Name. The vendor element should look something like this:
```
<EtherCATInfo>
    <Vendor>
        <Id>1551</Id> <!-- Vendor ID assigned by the EtherCAT Technology Group-->
        <Name>OSU Dynamic Robotics Laboratory</Name> <!-- Vendor name to be displayed by master -->
    </Vendor>
</EtherCATInfo>
```

The other Element in the EtherCATInfo tag is the Descriptions tag. Inside this tag all the devices and device groups are defined. All devices in an ESI XML file have to be put inside a group by using the GroupType element inside the Device element. This does nothing as far as the slave configuration, however it is used by master software to organize slave devices in lists. The Groups element is pretty simple. It contains Group elements with a Type and a Name.

Note: It is important specify the LcId (Location ID) parameter in the group Name tag. The LcId for the US is 1033.

Example of Groups element from the Medulla ESI file for ATRIAS 2.1:
```
<Descriptions>
    <Groups>
        <Group> <!-- A single Group element, there can be multiple of these in a single ESI file -->
            <Type>Medulla</Type> <!-- The group type is now the group is referred to in the device definition -->
            <Name LcId="1033">Medulla 1.5</Name> <!-- This is how the group appears in software reading the ESI file -->
        </Group>
    </Groups>
</Descriptions>
```

The Descriptions element also contains the Devices element. The Devices element contains all of the definitions for the slaves defined in file. It can contain as many devices as is desired.

```
<Descriptions>
    <Devices>
        <Device Physics="YY">
        </Device>
    </Devices>
</Descriptions>
```

## ESI Device Specification Elements ##
Each Device element inside the Devices element specifies a new device. Each Device element should have the Physics property set. This property specifies which hardware EtherCAT ports to use on the slave, and what kind of interface they provide. The Physics property is a string, Each character represents a port on the slave. If the character is a "Y" then the port is uses as a MII (Ethernet) port. If the character is a "K" then the port is specified to be an E-Bus port. If the character is a space (" "), then the port is disabled. Since on the medulla boards we have two ports, both of which are Ethernet our Device tag looks like this:
```
<Device Physics="YY"> <!-- Tells ports 0 and 1 to operate in MII mode -->
```

For a basic slave, at least one of each of the following elements are required in the Device element:
  * Type
  * Name
  * GroupType
  * Fmmu
  * Sm
  * RxPdo or TxPdo
  * Eeprom

In addition to this, multiple Fmmu, Sm, RxPdo, and TxPdo elements can be placed in a Device file. There are many other elements that can be added, for ATRIAS the only other element we use is the Dc element, which allows us to configure the distributed clock.

### Type element ###
The Type element specifies the product code, revision, and name of the device as it appears when the EtherCAT bus is scanned. The product code and Revision are specified as the properties ProductCode and GroupType in the Type element. The name of the device is specified as a string inside the element.
```
<Device Physics="YY">
    <Type ProductCode="#x00000004" RevisionNo="#x00000003">ATRIAS 2.1 EtherCAT Test (Medulla 1.5)</Type>
</Device>
```

### Name element ###
The Name element defines how the device appears in software that reads the ESI XML file. As with other elements that define strings shown in software, the LcId property has to be set in the Name element. In addition, the content of the Name element can be wrapped in a CDATA tag so the string will not be parsed by XML parser. This may not be necessary.
```
<Device Physics="YY">
    <Name LcId="1033"><![CDATA[ATRIAS 2.1 EtherCAT Test (Medulla 1.5)]]></Name>
</Device>
```

### GroupType element ###
The group type element tells programs that read the ESI file which group to file the device under. This doesn't change anything about how the device is configured, just how it will show up in software. However, it is still necessary. The following example shows a combination of how a Group and GroupType are defined:
```
<Descriptions>
    <Groups>
        <Group>
            <Type>Medulla</Type>
            <Name LcId="1033">Medulla 1.5</Name>
        </Group>
    </Groups>
    <Devices>
        <Device Physics="YY">
            <GroupType>Medulla</GroupType>
        </Device>
    </Devices>
</Descriptions>
```

### Fmmu element ###
The Fmmu element configures an FMMU to map the data from a sync manager into the EtherCAT packet. The Sm property of this element specifies which sync manager to map into the EtherCAT frame. The value of the element must either be the string "Outputs", "Inputs", or "MBoxState". The string "Outputs" is to be used on a sync manager for RxPDOs and the "Outputs" string is used for TxPDO sync managers. FMMUs only need to be specified for sync managers that are being used.
```
<Device Physics="YY">
    <Fmmu Sm="2">Outputs</Fmmu> <!-- Sync manager 2 is used for RxPDOs -->
    <Fmmu Sm="3">Inputs</Fmmu> <!-- Sync manager 2 is used for TxPDOs -->
</Device>
```

### Sm Element ###
The Sm elements of the ESI file specify the configuration for each Sync manager used by the slave. The Sync Manager that each Sm element configures is based upon the order in the Device element. The first Sm element, configures the Sync Manager 0, the second element configures Sync Manager 1, and so on. Therefore, if you want to configure Sync Manager 2, you need to first configure Sync Managers 0 and 1. As with the FMMU, the value of the Sm element tells the parser the direction of the Sync Manager. The possible values are:
  * **MBoxOut** - Mailbox data from master to slave
  * **MBoxIn** - Mailbox data from slave to master
  * **Outputs** - Buffered data from master to slave
  * **Inputs** - Buffered data from slave to master

The Sm element has several properties that you should specify. First, the Enable property specifies if the sync manager is used, it is specified as a string, of either "0" or "1". If it is zero, then the sync manager is disabled, if it's one, then the Sm is enabled. The StartAddress property sets the register address in the ESC's memory where the sync manager data will be stored. This is the address read or written by the xMega to send or receive EtherCAT data. Lastly you need to configure the ControlByte property. This property sets a register in the Sync manager's memory that configures the type and direction of the sync manager. In general, an RxPDO should have a control byte value of "#x4" and a TxPDO should have a value of "#x0". See page 177 in the ET1100 datasheet for more description of how to configure this register.
```
<Device Physics="YY">
    <Sm Enable="0" /> <!-- Disable Sync Managers 0 and 1 -->
    <Sm Enable="0" />
    <Sm StartAddress="#x1000" ControlByte="#x4" Enable="1">Outputs</Sm> <!-- Enable Sm 2 for RxPDOs starting at address 0x1000 -->
    <Sm StartAddress="#x2000" ControlByte="#x0" Enable="1">Inputs</Sm> <!-- Enable Sm3 for TxPDOs starting at address 0x2000 -->
</Device>
```

### RxPDO and TxPDO Elements ###
A RxPdo or TxPdo elements are used to describe the PDO elements of the slave. The TxPdo and RxPdo elements have two properties that we have found useful. The Sm property specifies which sync manager the PDO will reside in. The TxPdo and RxPdo elements use the following elements to define the PDO:
  * **Index** - Address of the PDO in the EtherCAT frame. For RxPdos the index should start at #x1600 and increment by one for every RxPdo. For TxPdos the index should start at #x1A00 and increment by one for each PDO.
  * **Name** - Name of the PDO
  * **Entry** - This element is used to define each PDO entry in the Rx or Tx PDO. The Entry element is described below:

#### Entry Element ####
Each entry element in a PDO element essentially adds a new data field to the PDO. There are five elements that are used to configure the field:
  * **Name** - The name of the PDO entry data field.
  * **BitLen** - The size of the data type that is stored in the PDO entry in bits
  * **Index** - Index of the entry, This index is dictated by the data type transferred. See table below to choose index.
  * **SubIndex** - Each entry of each type in a PDO have to a different sub-index. Usually this sub index will start at 1 and increment for each element of that data type.
  * **DataType** - The data type being stored in the PDO entry. See table below for possible data types.

Base PDO entry data types:
| **DataType** | **Index** | **BitLen** | **Description** |
|:-------------|:----------|:-----------|:----------------|
| SINT         | #x0002    | 8          | Signed 8 bit integer |
| USINT        | #x0005    | 8          | Unsigned 8 bit integer |
| INT          | #x0003    | 16         | Signed 16 bit integer |
| UINT         | #x0006    | 16         | Unsigned 16 bit integer |
| DINT         | #x0004    | 32         | Signed 32 bit integer |
| UDINT        | #x0007    | 32         | Unsigned 32 bit integer |
| LINT         | #x0015    | 64         | Signed 64 bit integer |
| ULINT        | #x001B    | 64         | Unsigned 64 bit integer |
| REAL         | #x0008    | 32         | 32 bit floating point number |
| LREAL        | #x0011    | 64         | 64 bit floating point number |

This is an example of a very basic RxPDO definition. TxPDOs are defined in exactly the same way.
```
<Device Physics="YY">
    <RxPdo Fixed="1" Sm="2"> <!-- This is an RX pdo, so put it in an Rx Sync manager -->
        <Index>#x1600</Index> <!-- First RxPDO so we start at #x1600 -->
        <Name>uControllerInput</Name>
        <Entry>
            <Index>#x0005</Index> <!-- Unsigned 8 bit, so use #x0005 for index -->
            <SubIndex>1</SubIndex> <!-- First element of this data type, so use SubIndex of 1 -->
            <BitLen>8</BitLen> <!-- Even though we already said the data type, we have to specify the length -->
            <Name>Command</Name>
            <DataType>USINT</DataType>
        </Entry>					
        <Entry>
            <Index>#x0003</Index> <!-- For this one we use a different index, because we have a different data type -->
            <SubIndex>1</SubIndex> <!-- We use the same SubIndex though because it is still the first entry with this data type -->
            <BitLen>16</BitLen>
            <Name>Motor Current</Name>
            <DataType>INT</DataType>
        </Entry>
    </RxPdo>
</Device>
```
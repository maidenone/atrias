# Introduction #

The medulla drivers are responsible for the actual decoding of sensor values from the medullas, as well as encoding of new commands to the medullas.

# Medulla class #

All the medulla drivers subclass the Medulla class. This class provides common decoding methods (such as processADCValue) as well as some structs used for pdo entry registration (described in the next section of this page).

# PDO Entry Registration #

Each medulla type has a getPDORegData() function, which returns a struct of type PDORegData. This struct contains an array of PDOEntryDatas, which allows higher-level EtherCAT code to assign the PDO entry locations directly into the driver's pointers.

In the EtherCAT connector, the code simply loops through the array of PDOEntryDatas and assigns the pointers therein. An EtherLabs-based connector, however, will need to individually assign each pointer, since EtherLabs's API is different from SOEM's API.
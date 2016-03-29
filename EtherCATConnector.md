# Introduction #

The EtherCAT connector is responsible for connecting with the Medullas, processing the data from the Medullas, and sending out new commands to the robot.

The EtherCAT connector is contained in the atrias\_ecat\_conn package.

# Conn Manager #

The initialization and main loop for the EtherCAT connector are in the ConnManager class. This class primarily consists of calls to SOEM's functions.

# Medulla Manager #

The MedullaManager class does the work of detecting the medullas, initializing the medulla drivers, and calling every driver each cycle.

The medullasInit() function is responsible for medulla identification. A specific function for each type of medulla is used to actually create the driver objects.
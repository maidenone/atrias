# Introduction #

The Connectors serve to connect RTOps with the robot. Each connector is responsible for periodically calling RT Ops with a new robot state, as well as for providing an operation allowing RT Ops to send out a new controller state.

The connectors provide RT Ops with the current timestamp by updating the Header inside the robot state.

We currently have 4 connectors. These connectors are documented below.

## Noop Connector ##

The Noop Connector, short for "no-operation connector", is designed purely for testing purposes. It runs the system at 1 kHz, providing timestamps but no other data. It is contained in the atrias\_noop\_conn package.

## Sim Connector ##

The Sim Connector connects our system with the simulation. It does this by using Orocos's RTT-ROS integration. This connector is in the atrias\_sim\_conn package.

## EtherCAT Connector ##

Our main EtherCAT connector is in the package atrias\_ecat\_conn. This connector is documented in the EtherCATConnector page.

## EtherLabs Connector ##

We have a second EtherCAT connector in the atrias\_elabs\_conn package. Currently, this connector is unmaintained (and incomplete), but hopefully it'll become a functional backup to the SOEM-based EtherCAT Connector in the future.
# TSB SM02's CAN protocol

⚠️ **SM02's CAN Bus needs to run at 500 kbps given that the Fuel Cell is limited to this speed.** ⚠️

⚠️ **CAN ID 0x00 is FORBIDDEN since this is a FC configuration message.** ⚠️

⚠️ **CAN ID 0x510 is FORBIDDEN since this is reserved for Isabellenhütte's Current Shunt internal use.** ⚠️

⚠️ **CAN TSB now uses tonton81's FlexCAN_T4 library check the example at the end of this README** ⚠️


#### Index

- [ID structure](#ID)
- [Code](#Código)


<a name="ID"/>

### ID structure

| Priority bits |  Data ID | Source ID |
|:-------------:|:--------:|:---------:|
|    2 bits     |  5 bits  |  4 bits   |


#### Priority bits

- Defines the message priority
- 00 maximum priority
- 11 lowest priority

#### Data ID

- Defines the message content
- With respect to each device

#### Source ID

- Defines which node sent the message
- Together with the Data ID defines which message was sent

| Source ID (4 bits) |           Node          |
|:------------------:|:-----------------------:|
|       0x0          |  [Throttle](#THROTTLE_MSG)       |
|       0x1          |  [BMS](#BMS_MSG)            |
|       0x2          |  [Fuel Cell](#FC_MSG)      |
|        -           |  [VESC](#VESCs_MSG)           |
|       0x4          |  [CAN WiFi](#CANWIFI)       |
|	    0x5		     |	[Dashboard](#0x5)      |
|       0x6          |  [BoP PCB](#BOP_MSG)        |
|        -           |  [Pressure Sensor](#0x7)|
|        -           |  [FC Current Shunt](#FC_SHUNT_MSG)|
|        -           |  [Battery Current Shunt](#FC_SHUNT_MSG)|


<br/>

<a name="THROTTLE_MSG"/>

## Throttle:
### status (CAN ID: 0x10)
**LEN = 2**

| Offset | Buffer Function |  Name  | Scale |          Description          |
| :----: | :-------------: | :----: | :---: | :---------------------------: |
|   0    |     int8_t      | value  |   -   |        Requested power        |
|   1    |     uint8_t     | status |   -   |          Status bits          |

#### Status bits:
| Position | Message |                   Description                   |
| :------: | :-----: | :---------------------------------------------: |
|    7     |    -    |                                                 |
|    6     |    -    |                                                 |
|    5     |    -    |                                                 |
|    4     |    -    |                                                 |
|    3     |    -    |                                                 |
|    2     |    -    |                                                 |
|    1     |  Mode   | If set FC mode, else battery mode               |
|    0     |  Zero   | If set, throttle has gone to zero after startup |


<a name="FC_MSG"/>

## Fuel Cell:

Be aware that we are not using the default CAN ID's the Stack node number (NN) is 0x02.

### Summary message (CAN ID: 0x182)
**LEN = 8**

### Detailed cell voltage (CAN ID: 0x282)
**LEN = 8**

### Status message (CAN ID: 0x582)
**LEN = 8**

### Node number configuration (CAN ID: 0x000)
**LEN = 2**

### General configuration (CAN ID: 0x602)
**LEN = 5**

<a name="CANWIFI"/>

## CAN WiFi:
### time (CAN ID: 0x04)
**LEN = 4**

|  Offset |   Type   |        Name       |          Scale           |            Description        |
|:-------:|:--------:|:-----------------:|:------------------------:|:-----------------------------:|
|    0    | uint32_t |  Time             | 						-             | seconds since 1/1/1970 in UTC |

<a name="CANWIFI"/>

## BoP PCB:

### BOP_TEMP_STATUS (CAN ID: ?)
**LEN = 8**

| Offset | Buffer Function |  Name  | Scale |          Description          |
| :----: | :-------------: | :----: | :---: | :---------------------------: |
|    0   | uint8_t |    Temp_WC_In    |   -   |    Temperature Cooling Inlet    |
|    1   | uint8_t |    Temp_WC_Out   |   -   |    Temperature Cooling Outlet   |
|    2   | uint8_t |    Temp_Amb   |   -   |      Temperature inside BoP box     |
|    3   | uint8_t |   Temp_Blower   |   -   |  Temperature Air Blower     |
|    4   | uint8_t |    -   |   -   |    -   |
|    5   | uint8_t |    -  |   -   |      -   |
|    6   | uint8_t |  - |   -   |  - |
|    7   | uint8_t | Status |   -   | - |

#### Status messages:
| Position |        Message       | Description |
|:--------:|:--------------------:|-------------|
|     7    |           -          |             |
|     6    |           -          |             |
|     5    |           -          |             |
|     4    |  Status_KNF          | 1 means KNF is ON|
|     3    |  Status_Blower  | 1 means Blower is ON |
|     2    |  Status_Mode    | 1 means FC mode |
|     1    |  Status_H2_Solen     | 1 means valve is open |
|     0    |  Status_Cooling_Pump | 1 means pump is ON    |

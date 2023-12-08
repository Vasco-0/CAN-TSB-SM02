# TSB SM02's CAN protocol

⚠️ **SM02's CAN Bus needs to run at 500 kbps given that the Fuel Cell is limited to this speed.** ⚠️

⚠️ **CAN TSB now uses 4 bits for Source and 5 bits for Data.** ⚠️

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
|       0x1          |  [BMS](#0x1)            |
|       0x2          |  [Fuel Cell](#0x2)      |
|        -           |  [VESC](#0x3)           |
|       0x4          |  [CAN WiFi](#0x4)       |
|	    0x5		     |	[Dashboard](#0x5)      |
|       0x6          |  [BoP PCB](#0x6)        |
|        -           |  [Pressure Sensor](#0x7)|


<br/>

<a name="THROTTLE_MSG"/>

## Throttle Messages:
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


<a name="SCREEN_MSG"/>

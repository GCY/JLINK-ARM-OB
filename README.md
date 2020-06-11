# JLINK-ARM-OB
This is JLink-OB ARM ICE tool, [STM32F103 Jan 7 2019 firmware](https://github.com/GCY/JLINK-ARM-OB/blob/master/J-Link%20OB-STM32F103%20V1%20compiled%20Jan%20%207%202019/JLink-OB%20STM32F103%20JLinkARM.dll%20v6.44f%20.bin) extract from v6.44 JLinkARM.dll.

This version([STM32F103 Jan 7 2019](https://github.com/GCY/JLINK-ARM-OB/blob/master/J-Link%20OB-STM32F103%20V1%20compiled%20Jan%20%207%202019/JLink-OB%20STM32F103%20JLinkARM.dll%20v6.44f%20.bin) ) failed to upgrade the firmware of the JLink-OB with JLinkConfig.

![](https://github.com/GCY/JLINK-ARM-OB/blob/master/J-Link%20OB-STM32F103%20V1%20compiled%20Jan%20%207%202019/JLinkARM.dll%20dump%20%20firmware.png?raw=true)

## Use
 - 1.burning [STM32F103 Jan 7 2019 firmware](https://github.com/GCY/JLINK-ARM-OB/blob/master/J-Link%20OB-STM32F103%20V1%20compiled%20Jan%20%207%202019/JLink-OB%20STM32F103%20JLinkARM.dll%20v6.44f%20.bin) to DIY JLink-OB.
 - 2.Connect targer(For example the following picture is my [STM32F405 Digital Stethoscope project](https://github.com/GCY/Digital-Stethoscope-for-Heart-and-Lung-sounds))
![](https://github.com/GCY/JLINK-ARM-OB/blob/master/J-Link%20OB-STM32F103%20V1%20compiled%20Jan%20%207%202019/mem%200x8000000%2040960/jtag%20swd%20connect.png?raw=true)

 - 1.Run JLinkExe.
 - 2.J-Link > connect.
 - 3.Select device.     # the example is STM32F405
 - 4.Device > S.        # for SWD Port
 - 5.Speed = 4000kHz
![](https://github.com/GCY/JLINK-ARM-OB/blob/master/J-Link%20OB-STM32F103%20V1%20compiled%20Jan%20%207%202019/mem%200x8000000%2040960/connect%20JLink-OB%20to%20STM32F405.png?raw=true)

 - 1.J-Link > mem 0x8000000 40960
 - 2.Test dump target flash.
 - 3.You DIY JLink-OB done.
![](https://github.com/GCY/JLINK-ARM-OB/blob/master/J-Link%20OB-STM32F103%20V1%20compiled%20Jan%20%207%202019/mem%200x8000000%2040960/dump%20STM32F405%20mem%200x8000000%2040960%20with%20JLink-OB%201.png?raw=true)

## Reference
 - [DIY JLink-OB-072 (JLink + COM)](http://akb77.com/g/stm32/jlink-ob/)
 - [JLink hack reference (cht)](https://www.amobbs.com/thread-5653964-1-1.html)
 - [J-Link Commander](https://wiki.segger.com/J-Link_Commander#savebin)
 - [Firmware extract from JLinkARM.dll (cht)](https://blog.csdn.net/qq_39663845/article/details/81086499)

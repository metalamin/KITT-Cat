# KITT-Cat
Smart card hacking tools based on Arduino.

This tools are intended to supply a starting point for smart card hacking. It's also intended to be cheap and easy to use.

A modified library for Arduino to support parity is needed. You can find it here: https://github.com/metalamin/SoftwareSerialPar

## Hardware
* Arduino nano
* Smart Card PCB (I use an old piccard2 without the PIC) 


![ISO 7816 Pinout](https://upload.wikimedia.org/wikipedia/commons/thumb/0/06/SmartCardPinout.svg/440px-SmartCardPinout.svg.png)

ISO 7816 Pin | Arduino Pin | Comment
------------ | ------------- | -------------
Gnd | Gnd | For common ground
RST | D2 | Must be Interrupt pin (D2 or D3)
I/O | D8 | Could be any Digital pin

## KITT-Cat Bridge
Emulated smart card on arduino nano and controled by the PC over USB.

Bytes sent to arduino are relayed to the smart card reader and viceversa.

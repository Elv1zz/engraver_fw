===========
engraver_fw
===========

Firmware for laser engraver based on Arduino Mega 2560

This project is based on Laserplotter project of Christian Nolte published in German computer magazine c't for "Mach flott den Schrott" competition. 

See 
http://www.heise.de/ct/artikel/Laserplotter-aus-alten-DVD-Brennern-1589363.html
and 
http://www.heise.de/hardware-hacks/projekte/Laserplotter-1351340.html

License
-------

See file LICENSE


Maintainer
----------

Elv1zz
elv1zz.git@gmail.com


Getting started
---------------

If your design and hardware layout is just like mine, you simply have to compile and upload the code.
To do so, create a build directory, execute cmake and make. Then connect your Arduino to your computer, upload the binary and you're done!

The commands
____________

mkdir build

cd build

cmake ..

make

make engraver-upload

That's it! Fairly simple, isn't it?


If your design is different than mine, you will have to edit the firmware source (engraver/main.cpp). Maybe you also have to edit engraver/CMakeLists.txt when you have a different Arduino board than "Arduino Mega 2560" or it is not connected to /dev/ttyACM0.

Currently arduino-cmake supports the following boards and programmers:

-- Arduino Boards:

--            uno: Arduino Uno

--      atmega328: Arduino Duemilanove w/ ATmega328

--      diecimila: Arduino Diecimila or Duemilanove w/ ATmega168

--        nano328: Arduino Nano w/ ATmega328

--           nano: Arduino Nano w/ ATmega168

--       mega2560: Arduino Mega 2560 or Mega ADK

--           mega: Arduino Mega (ATmega1280)

--        mini328: Arduino Mini w/ ATmega328

--           mini: Arduino Mini w/ ATmega168

--       ethernet: Arduino Ethernet

--            fio: Arduino Fio

--          bt328: Arduino BT w/ ATmega328

--             bt: Arduino BT w/ ATmega168

--     lilypad328: LilyPad Arduino w/ ATmega328

--        lilypad: LilyPad Arduino w/ ATmega168

--       pro5v328: Arduino Pro or Pro Mini (5V, 16 MHz) w/ ATmega328

--          pro5v: Arduino Pro or Pro Mini (5V, 16 MHz) w/ ATmega168

--         pro328: Arduino Pro or Pro Mini (3.3V, 8 MHz) w/ ATmega328

--            pro: Arduino Pro or Pro Mini (3.3V, 8 MHz) w/ ATmega168

--      atmega168: Arduino NG or older w/ ATmega168

--        atmega8: Arduino NG or older w/ ATmega8

-- 


-- Arduino Programmers:

--         avrisp: AVR ISP

--     avrispmkii: AVRISP mkII

--     usbtinyisp: USBtinyISP

--         usbasp: USBasp

--       parallel: Parallel Programmer

--     arduinoisp: Arduino as ISP


# pi-top-gpio-display

Displays the logic value of the general purpose gpio pins on the 
pi-top hub connector. The pi-top hub is used in the pi-top, a laptop kit
based on the Raspberry Pi (see http://pi-top.com)

![Alt text](screenshot.jpg?raw=true "pi-top-gpio-display")

There are 3 versions of this program
- pi-gpio-display displays the pins of the 40 pin connector of the Raspberry Pi https://github.com/rricharz/pi-gpio-display
- pi-top-gpio-display displays the pins of the pi-top hub connector https://github.com/rricharz/pi-top-gpio-display
- pi-top-proto-display displays the pins of the pi-topPROTO board https://github.com/rricharz/pi-top-proto-display

**You must be user pi to install and run this program**

To install:

- Open a terminal and type:

```
  cd Downloads
  git clone git://github.com/rricharz/pi-top-gpio-display
  cd pi-top-gpio-display
  chmod +x ./install
  ./install
```
- Reboot your pi

If you want to recompile the program, you need to install

```
  sudo apt-get install libgtk-3-dev
```

You can test the compilation with

```
  touch application.c
  make
```

The program uses Wiring Pi, which is installed in Raspbian Jessie and the pi-top-OS based on Jessie.
If you do not use Jessie, see wiringpi.com for instructions on how to install Wiring Pi.
The **gpio** command used below is included in Wiring Pi.

This program does not change the mode of any of the pins, it just observes
the logic value. If you want to set any of the these pins to output, and observe
the change, you can open a console and type the following commands.
**pin#** is the green wiringPi number on the display (not the pi-top connector pin number!),
**new_value** is either 1 or 0)


```
  gpio mode pin# out
  gpio write pin# new_value
```

A description of all the options of the gpio command can be found at
http://wiringpi.com/the-gpio-utility

If you want to observe the state of any of the pins as input, you can connect
the pin with a suitable resistor to ground or 3.3V,
and set the pin to input using the command

```
  gpio mode pin# in
```

**Be carefull with the gpio command** and use it only with a proper green wiringPi pin#.
Also, **be carefull hooking up anything to the pi-top hub connector**. You might destroy
your hardware if you make a mistake. **Do not hook up any pin to 5V**.


Please help to improve this program by tweeting to
**http://twitter.com/r_richarz** or opening an issue on this repository
if you have any problem or suggestion.

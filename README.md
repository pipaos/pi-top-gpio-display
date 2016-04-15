# pi-top-gpio-display

Displays the logic value of the general purpose gpio pins on the pi-top hub connector.
** You must be user pi to install and run this program **

To install:

- Download the repository to your pi-top using the "download zip" button
- Using the file manager, go to your download folder,
 right click on "pi-top-gpio-display-master.zip" and choose "Extract here"
- Open a console window and type the following commands

```
  cd Downloads
  cd pi-top-gpio-display-master
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


Please help to improve this program by by opening an issue on this repository
if you any problems or suggestions.

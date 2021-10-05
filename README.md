# RockSense
This project's intentions is to design a driver for a Linux-based system, **RockPi S** to interact with a **I2C Barometric Pressure/Temp Sensor** and output the data to the user in a comprehendable way. 

### Requirements
Begin this project by obtaining the following:
- RockPi S
- A Host PC/Laptop with Windows or Linux
- I2C Barometric Pressure + Temp Sensor
- Preferably 16GB MicroSD Card
- USB Type-C power adapter
- USB Type-C charging power cable
- USB to TTL serial cable

### DataSheets
[I2C Barometric Pressure + Temp Sensor](https://www.nxp.com/docs/en/data-sheet/MPL115A2.pdf)

[RockPi S](https://dl.radxa.com/rockpis/docs/hw/ROCK-PI-S_v10_sch_20190323.pdf)

### Setup
To begin there are two paths one could take
- Build your own Image
- Use the given prebuilt Image 

### Building an Image
Choose the approach desired: https://wiki.radxa.com/RockpiS/dev

### Prebuilt Images
Choose one you prefer to boot from here: https://wiki.radxa.com/RockpiS/downloads

<img src="https://wiki.radxa.com/mw/images/thumb/8/8a/Rockpis-serial-connection.jpeg/795px-Rockpis-serial-connection.jpeg" width="400">

### Connecting to the Rock Pi S
**Notice**: While I was doing this project I came accross a bug where the hostname of the rock pi s was unable to be found on a network. I got arround this by installing a listener and utilizing Putty, found at https://www.putty.org/, to handle the communications between my computer and the targeted hardware.

[Refrence](https://wiki.radxa.com/RockpiS/ssh)
If this bug/problem does not occur for you, you can simply connect to the rock pi s with [openSSH](https://man7.org/linux/man-pages/man1/ssh.1.html), utlizing a command simmilar to 
```bash
ssh [user@]hostname :
```

### Setting up physical connections
Read the datasheets for both components
connect the following wires to the Rock Pi S:
+ SDA 
+ SCL 
+ VDD
+ GRD 

### Stting Up A Cross Compling Setup
With everything connected now, we need a manner of compling a samle of code on the targeted hardware. Look back at the datasheet to understand what type of architecture the cpu is running.

Install the new GCC complier on the compliation machine.
Debian based with apt package manager
```bash 
sudo apt-get install gcc-aarch64-linux-gnu
```

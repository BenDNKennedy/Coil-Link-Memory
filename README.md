# Coil-Link-Memory

Device Drivers: 
  - ADS1X1X   (Working)
  - ADS1X4S0X (In Progress)

***
Set ZEPHYR_BASE system variable to your zephyr repo path - Example: https://i.imgur.com/3gSTP4d.png
***

Builds are contained within each individual workspace. First navigate to your desired workspace:
 - Note: (COILLINKMEM-MAIN contains drivers for both ADS1X1X & ADS1X4S0X ADCs)
```
cd $DESIRED-WORKSPACE
```
The "app" folders contain the given workspace's main.c file. Build the application:
```
west build -b $DESIRED-BOARD app
```
Flash the application to your board (Using JLink runner):
```
west flash -r jlink
```

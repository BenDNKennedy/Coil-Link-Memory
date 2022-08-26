# Coil-Link-Memory

Set ZEPHYR_BASE system variable to your zephyr repo path - Example: https://i.imgur.com/3gSTP4d.png
***

Builds are contained within each individual workspace. First navigate to your desired workspace:
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

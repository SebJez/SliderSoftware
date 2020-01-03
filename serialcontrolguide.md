# Controlling the slider through the serial connection:

## Initializing the connection

After selecting the serial control option the slider initializes a connection through Arduino's built-in serial-to-USB adapter. The parameters are default for the Arduino `Serial.begin()` function (in doubt see <https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/>): 
- baud rate **9600**
- **8** data bits
- **no** parity
- **1** stop bit

After connecting the slider starts repeatedly sending its configuration, for example:
```
K 0.02  //length of one step (mm)
L 200.0 //length of the slider (maximal position, mm)
S 5.0   //speed (mm/s)
X 0.0   //current position (mm)
```

To acknowledge receiving the configuration and begin normal operation the digit `0` (0x30) should be sent to the slider.

## Available commands
All commands start with an uppercase letter and and with newline (`\n`).
### H - homing
    After receiving the command `H` the slider will perform the homing procedure - move until it hits the starting position endstop and set that position as 0.

    Finishing the procedure is confirmed by sending back the letter `H`.

### X - movement
    Syntax: 
    ```
    X 10.0  //move forward by 10 mm
    X -0.2  //move back by 0.2 mm
    ```
    
    After finishing the movement the slider replies with the letter `X` follow by its current position eg. `X 20.3`. **Warning**: the position might not be the one requested    if the slider reaches the end of its range or the requested move is not a multiple of the length of one step.

### S - speed
    Syntax:
    ```
    S 5.0   //set speed to 5 mm/s
    ```
    
    The slider replies with the letter `S` followed by its current speed setting.

### I - print configuration
    The slider replies with its configuration (format is the same as during initialization).
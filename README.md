# Basic STM32 Application

This application is intended to be used with the Nucleo-L476RG

## Build

Requirements:
- CMake (3.23 >)
- arm-none-eabi-gcc package

While in the top level of the directory, run:

```
mkdir build && cd build
cmake ..
make
```

This will result in a file called `app.elf` in the `build` folder. 

Then run `objcopy` on the file to obtain the `.bin` file (which can then be flashed to your MCU)

```
arm-none-eabi-objcopy -O binary app.elf app.bin
```
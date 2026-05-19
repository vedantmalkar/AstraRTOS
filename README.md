# AstraRTOS

Minimal RTOS built from scratch for STM32F429ZI (Cortex-M4)

## Build

### Requirements
- `arm-none-eabi-gcc`
- `openocd` (not confirmed for now)
- `qemu-system-arm` (for make qemu)

### Commands
```
make          # build
make flash    # flash to board
make clean    # clean build files
make qemu     # run in qemu
```
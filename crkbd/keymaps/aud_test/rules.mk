
RGB_MATRIX_ENABLE = yes
BOOTLOADER = atmel-dfu # elite-c

POINTING_DEVICE_ENABLE = yes
SRC += pimoroni_trackball.c
QUANTUM_LIB_SRC += i2c_master.c
MOUSEKEY_ENABLE = no
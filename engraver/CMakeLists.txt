# This file configures the engraver_fw project

# define some default values
set(ARDUINO_DEFAULT_BOARD mega2560) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM00) # Default Port, when not specified


#====================================================================#
# Project specific definitions
#====================================================================#
set(FIRMWARE_NAME engraver)

set(${FIRMWARE_NAME}_BOARD mega2560)
set(${FIRMWARE_NAME}_SRCS main.cpp MSMotorShield.cpp)
set(${FIRMWARE_NAME}_HDRS MSMotorShield.h)
set(${FIRMWARE_NAME}_PORT /dev/ttyACM0)

generate_arduino_firmware(${FIRMWARE_NAME})


#=============================================================================#
# Author: QueezyTheGreat                                                      #
# Date:   26.04.2011                                                          #
#                                                                             #
# Description: Arduino CMake example                                          #
#                                                                             #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain


cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup project:  engraver_fw                                       #
#  Author:         Elv1zz                                            #
#  Last modified:  02.08.2012                                        #
#                                                                    #
#  Description:    Firmware for laser engraver based on Arduino      #
#====================================================================#
project(Engraver C CXX)

print_board_list()
print_programmer_list()

add_subdirectory(engraver)


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Dealer.cc \
../src/Input.cc \
../src/Play.cc \
../src/Player.cc \
../src/Tick.cc \
../src/Top.cc \
../src/TopControllers.cc \
../src/TopMain.cc 

O_SRCS += \
../src/Dealer.o \
../src/Input.o \
../src/Play.o \
../src/Player.o \
../src/Tick.o \
../src/Top.o \
../src/TopControllers.o \
../src/TopMain.o 

CC_DEPS += \
./src/Dealer.d \
./src/Input.d \
./src/Play.d \
./src/Player.d \
./src/Tick.d \
./src/Top.d \
./src/TopControllers.d \
./src/TopMain.d 

OBJS += \
./src/Dealer.o \
./src/Input.o \
./src/Play.o \
./src/Player.o \
./src/Tick.o \
./src/Top.o \
./src/TopControllers.o \
./src/TopMain.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -IC:/Users/Dev/Downloads/Papyrus-RT/plugins/org.eclipse.papyrusrt.rts_1.0.0.201707181457/umlrts/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



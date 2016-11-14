################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Alarm.cpp \
../DiodeTempSensor.cpp \
../Fan.cpp \
../Filter.cpp \
../HPF.cpp \
../LCDManager.cpp \
../LPF.cpp \
../LiquidCrystal.cpp \
../PID.cpp \
../Sensor.cpp \
../SensorArray.cpp \
../main.cpp 

OBJS += \
./Alarm.o \
./DiodeTempSensor.o \
./Fan.o \
./Filter.o \
./HPF.o \
./LCDManager.o \
./LPF.o \
./LiquidCrystal.o \
./PID.o \
./Sensor.o \
./SensorArray.o \
./main.o 

CPP_DEPS += \
./Alarm.d \
./DiodeTempSensor.d \
./Fan.d \
./Filter.d \
./HPF.d \
./LCDManager.d \
./LPF.d \
./LiquidCrystal.d \
./PID.d \
./Sensor.d \
./SensorArray.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/tim/Desktop/arduino-1.6.11/hardware/tools/avr/avr/include/ -I../home/tim/Desktop/arduino-1.6.11/hardware/arduino/avr/cores/arduino/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



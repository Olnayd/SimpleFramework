################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/itc/Dispatcher.cpp \
../src/itc/EventLoop.cpp 

OBJS += \
./src/itc/Dispatcher.o \
./src/itc/EventLoop.o 

CPP_DEPS += \
./src/itc/Dispatcher.d \
./src/itc/EventLoop.d 


# Each subdirectory must supply rules for building sources it contributes
src/itc/%.o: ../src/itc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/oleh/Work/workspaces/MyWorkspace/Common/src" -I"/home/oleh/Work/workspaces/MyWorkspace/Common" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



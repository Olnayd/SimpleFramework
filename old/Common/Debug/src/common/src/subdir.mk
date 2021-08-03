################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/common/src/Operation.cpp \
../src/common/src/guard.cpp 

OBJS += \
./src/common/src/Operation.o \
./src/common/src/guard.o 

CPP_DEPS += \
./src/common/src/Operation.d \
./src/common/src/guard.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/src/%.o: ../src/common/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/oleh/Work/workspaces/MyWorkspace/Common/src" -I"/home/oleh/Work/workspaces/MyWorkspace/Common" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



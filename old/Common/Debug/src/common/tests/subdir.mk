################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/common/tests/CCommandTest.cpp 

OBJS += \
./src/common/tests/CCommandTest.o 

CPP_DEPS += \
./src/common/tests/CCommandTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/tests/%.o: ../src/common/tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/oleh/Work/workspaces/MyWorkspace/Common/src" -I"/home/oleh/Work/workspaces/MyWorkspace/Common" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



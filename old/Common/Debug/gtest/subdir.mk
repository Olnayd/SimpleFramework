################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../gtest/gtest-all.cc 

CC_DEPS += \
./gtest/gtest-all.d 

OBJS += \
./gtest/gtest-all.o 


# Each subdirectory must supply rules for building sources it contributes
gtest/%.o: ../gtest/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/oleh/Work/workspaces/MyWorkspace/Common" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



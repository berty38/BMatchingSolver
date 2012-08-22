################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../matlab/BMatchingSolver.cpp 

OBJS += \
./matlab/BMatchingSolver.o 

CPP_DEPS += \
./matlab/BMatchingSolver.d 


# Each subdirectory must supply rules for building sources it contributes
matlab/%.o: ../matlab/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



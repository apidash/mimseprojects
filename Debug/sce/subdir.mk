################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sce/Dynamic.cpp \
../sce/Instance.cpp \
../sce/Volume.cpp \
../sce/main.cpp 

OBJS += \
./sce/Dynamic.o \
./sce/Instance.o \
./sce/Volume.o \
./sce/main.o 

CPP_DEPS += \
./sce/Dynamic.d \
./sce/Instance.d \
./sce/Volume.d \
./sce/main.d 


# Each subdirectory must supply rules for building sources it contributes
sce/%.o: ../sce/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



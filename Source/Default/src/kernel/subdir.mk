################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/kernel/irq.c \
../src/kernel/isr.c \
../src/kernel/panic.c 

OBJS += \
./src/kernel/irq.o \
./src/kernel/isr.o \
./src/kernel/panic.o 

C_DEPS += \
./src/kernel/irq.d \
./src/kernel/isr.d \
./src/kernel/panic.d 


# Each subdirectory must supply rules for building sources it contributes
src/kernel/%.o: ../src/kernel/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



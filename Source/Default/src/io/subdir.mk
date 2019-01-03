################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/io/gdt.c \
../src/io/idt.c \
../src/io/portio.c \
../src/io/tty.c 

OBJS += \
./src/io/gdt.o \
./src/io/idt.o \
./src/io/portio.o \
./src/io/tty.o 

C_DEPS += \
./src/io/gdt.d \
./src/io/idt.d \
./src/io/portio.d \
./src/io/tty.d 


# Each subdirectory must supply rules for building sources it contributes
src/io/%.o: ../src/io/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../src/asm/boot.asm \
../src/asm/gdt.asm \
../src/asm/interrupt.asm 

OBJS += \
./src/asm/boot.o \
./src/asm/gdt.o \
./src/asm/interrupt.o 


# Each subdirectory must supply rules for building sources it contributes
src/asm/%.o: ../src/asm/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



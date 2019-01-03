################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/memory/kheap.c \
../src/memory/memmanager.c \
../src/memory/page_fault.c \
../src/memory/paging.c 

OBJS += \
./src/memory/kheap.o \
./src/memory/memmanager.o \
./src/memory/page_fault.o \
./src/memory/paging.o 

C_DEPS += \
./src/memory/kheap.d \
./src/memory/memmanager.d \
./src/memory/page_fault.d \
./src/memory/paging.d 


# Each subdirectory must supply rules for building sources it contributes
src/memory/%.o: ../src/memory/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



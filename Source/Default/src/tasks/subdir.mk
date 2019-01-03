################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tasks/context-switch.c \
../src/tasks/elf32.c \
../src/tasks/execve.c \
../src/tasks/fork.c \
../src/tasks/pit.c \
../src/tasks/sched.c \
../src/tasks/sync.c 

OBJS += \
./src/tasks/context-switch.o \
./src/tasks/elf32.o \
./src/tasks/execve.o \
./src/tasks/fork.o \
./src/tasks/pit.o \
./src/tasks/sched.o \
./src/tasks/sync.o 

C_DEPS += \
./src/tasks/context-switch.d \
./src/tasks/elf32.d \
./src/tasks/execve.d \
./src/tasks/fork.d \
./src/tasks/pit.d \
./src/tasks/sched.d \
./src/tasks/sync.d 


# Each subdirectory must supply rules for building sources it contributes
src/tasks/%.o: ../src/tasks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/tasks/fork.o: ../src/tasks/fork.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/home/arawn/opt/cross/bin -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/tasks/fork.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../core/Config.cpp 

CC_SRCS += \
../core/Solver.cc 

OBJS += \
./core/Config.o \
./core/Solver.o 

CC_DEPS += \
./core/Solver.d 

CPP_DEPS += \
./core/Config.d 


# Each subdirectory must supply rules for building sources it contributes
core/%.o: ../core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -DNDEBUG -I"/home/sam/workspaceC/modsat/modsat" -I"/home/sam/workspaceC/modsat" -O3 -g3 -Wall -c -fmessage-length=0 -msse2  -std=c++11 -Wno-unused-variable -Wno-unused-but-set-variable -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

core/%.o: ../core/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -DNDEBUG -I"/home/sam/workspaceC/modsat/modsat" -I"/home/sam/workspaceC/modsat" -O3 -g3 -Wall -c -fmessage-length=0 -msse2  -std=c++11 -Wno-unused-variable -Wno-unused-but-set-variable -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



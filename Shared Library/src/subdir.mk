################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BMatchingLibrary.cpp \
../src/BMatchingProblem.cpp \
../src/BMatchingSolver.cpp \
../src/BeliefPropagator.cpp \
../src/BipartiteFunctionOracle.cpp \
../src/BipartiteMatrixOracle.cpp \
../src/EuclideanDistance.cpp \
../src/FunctionOracle.cpp \
../src/IndexHeap.cpp \
../src/InnerProduct.cpp \
../src/IntDoubleMap.cpp \
../src/IntSet.cpp \
../src/MatrixOracle.cpp \
../src/OscillationDetector.cpp \
../src/WeightFunction.cpp \
../src/WeightOracle.cpp \
../src/utils.cpp 

OBJS += \
./src/BMatchingLibrary.o \
./src/BMatchingProblem.o \
./src/BMatchingSolver.o \
./src/BeliefPropagator.o \
./src/BipartiteFunctionOracle.o \
./src/BipartiteMatrixOracle.o \
./src/EuclideanDistance.o \
./src/FunctionOracle.o \
./src/IndexHeap.o \
./src/InnerProduct.o \
./src/IntDoubleMap.o \
./src/IntSet.o \
./src/MatrixOracle.o \
./src/OscillationDetector.o \
./src/WeightFunction.o \
./src/WeightOracle.o \
./src/utils.o 

CPP_DEPS += \
./src/BMatchingLibrary.d \
./src/BMatchingProblem.d \
./src/BMatchingSolver.d \
./src/BeliefPropagator.d \
./src/BipartiteFunctionOracle.d \
./src/BipartiteMatrixOracle.d \
./src/EuclideanDistance.d \
./src/FunctionOracle.d \
./src/IndexHeap.d \
./src/InnerProduct.d \
./src/IntDoubleMap.d \
./src/IntSet.d \
./src/MatrixOracle.d \
./src/OscillationDetector.d \
./src/WeightFunction.d \
./src/WeightOracle.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



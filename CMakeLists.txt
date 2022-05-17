cmake_minimum_required(VERSION 3.21)
project(lab9_10)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab9_10 main.cpp Domain/Product.cpp Domain/Product.h VendingMachineService/VendingMachineService.cpp VendingMachineService/VendingMachineService.h Tests/Tests.h Repository/MemoryRepository.h Repository/IRepo.h ProductValidator/ProductValidator.cpp ProductValidator/ProductValidator.h Repository/FileRepository.h VendingMachineUI/VendingMachineUI.cpp VendingMachineUI/VendingMachineUI.h Domain/MyException.h Domain/Coins.cpp Domain/Coins.h ProductValidator/CoinsValidator.cpp ProductValidator/CoinsValidator.h)
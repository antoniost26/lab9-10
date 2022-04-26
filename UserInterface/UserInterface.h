//
// Created by Antonio on 4/16/2022.
//
#include "../Domain/Product.h"
#include "../Repository/MemoryRepository.h"
#include "../ProductValidator/ProductValidator.h"
#include "../ProductService/ProductService.h"
#include <sstream>
#include <random>
#include <utility>

#ifndef LAB9_10_USERINTERFACE_H
#define LAB9_10_USERINTERFACE_H

class UserInterface {
private:
    ProductService& productService;
public:
    /**
     *
     * @param _productService
     */
    explicit UserInterface(
                ProductService& _productService
            ) :
                productService{_productService} {}

    /**
     * Runs the user interface
     */
    void run();

    /**
     * Prints the menu
     */
    static void printMenu();

    /**
     * Splits a string into a vector by a delimiter
     * @param s a string
     * @param delimiter a delimiter
     * @return a vector of strings
     */
    std::vector<std::string> split(const std::string& s, char delimiter);

    /**
     * Runs a command
     * @param input user input
     */
    void runCommand(const std::string& input);

    /**
     * Handles add to repository command
     * @param args arguments
     */
    void handleAdd(std::vector<std::string> args);

    /**
     * Handles print from repository command
     * @param args arguments
     */
    void handlePrint(std::vector<std::string> args);

    /**
     * Checks to see if a string is a number
     * @param s a string
     * @return true if the string is a number, false otherwise
     */
    bool isNumber(std::string s);

    /**
     * Checks to see if a string is a float/double
     * @param s a string
     * @return true if the string is a float/double, false otherwise
     */
    bool isFloat(std::string s);

    void handleAutoAdd();
};


#endif //LAB9_10_USERINTERFACE_H

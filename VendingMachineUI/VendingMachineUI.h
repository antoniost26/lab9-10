//
// Created by Antonio on 5/3/2022.
//
#include "../Domain/Product.h"
#include "../Repository/MemoryRepository.h"
#include "../VendingMachineService/VendingMachineService.h"
#include "../ProductValidator/CoinsValidator.h"
#include <sstream>
#include <random>
#include <utility>
#include <map>
#include <fstream>
#include <iomanip>

#ifndef LAB9_10_VENDINGMACHINE_H
#define LAB9_10_VENDINGMACHINE_H


class VendingMachineUI {
private:
    std::string balanceFileName = "../Database/balance.txt";
    bool isAdmin;
    VendingMachineService &machineService;
public:
    /**
     * Deletes no argument constructor
     */
    VendingMachineUI() = delete;

    /**
     * Destructor
     */
    ~VendingMachineUI() = default;

    /**
     * Constructor
     * @param _productService product service
     */
    explicit VendingMachineUI(VendingMachineService &_machineService) : machineService{_machineService}, isAdmin{false} {};

    /**
     * Runs the vending machine
     */
    void run();

    /**
     * Runs a given input/command
     * @param input command
     */
    void runCommand(const std::string &input);

    /**
     * Splits a string by a given delimiter
     * @param s a string
     * @param delimiter a delimiter
     * @return a vector of strings
     */
    static std::vector<std::string> split(const std::string &s, char delimiter);

    /**
     * Prints available commands
     */
    void printMenu();

    /**
     * Handles adding a product
     * @param args arguments
     */
    void handleAdd(std::vector<std::string> args);

    /**
     * Handles printing the products
     * @param args arguments
     */
    void handlePrint(std::vector<std::string> args);

    /**
     * Checks to see if a string contains a number only.
     * @param s a string
     * @return true if it does, false otherwise
     */
    static bool isNumber(std::string s);

    /**
     * Checks to see if a string contains a float number only.
     * @param s a string
     * @return true if it does, false otherwise
     */
    static bool isFloat(std::string s);

    /**
     * Handles generating products
     */
    void handleAutoAdd();

    /**
     * Handles removing a product
     * @param args arguments
     */
    void handleRemove(std::vector<std::string> args);

    /**
     * Handles buying a product
     * @param args arguments
     */
    void handleBuy(std::vector<std::string> args);

    /**
     * Gets available balance
     * @return sum of available banknotes
     */
    int getBalance();

    /**
     * Prints available balance
     */
    void printSum();

    /**
     * Prints available banknotes and its quantity
     */
    void printChange();

    /**
     * Initializes banknotes if needed
     */
    void initializeBanknotes();

    /**
     * Handles editing a product
     * @param args arguments
     */
    void handleEdit(std::vector<std::string> args);

    void handleEditCode(std::vector<std::string> args);
};


#endif //LAB9_10_VENDINGMACHINE_H

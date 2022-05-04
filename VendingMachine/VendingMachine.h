//
// Created by Antonio on 5/3/2022.
//
#include "../Domain/Product.h"
#include "../Repository/MemoryRepository.h"
#include "../ProductValidator/ProductValidator.h"
#include "../ProductService/ProductService.h"
#include <sstream>
#include <random>
#include <utility>
#include <map>
#include <fstream>

#ifndef LAB9_10_VENDINGMACHINE_H
#define LAB9_10_VENDINGMACHINE_H


class VendingMachine {
private:
    std::map<int, int> availableBalance;
    std::string balanceFileName = "../balance.txt";
    bool isAdmin;
    ProductService& productService;
public:
    VendingMachine() = delete;

    ~VendingMachine() {
        std::ofstream file(balanceFileName);
        for (auto it : availableBalance) {
            file << it.first << " " << it.second << std::endl;
        }
        file.close();
    };

    explicit VendingMachine(ProductService& _productService) : productService{_productService}, isAdmin{false} {
        std::ifstream file(balanceFileName);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                int first, second;
                std::vector<std::string> info = split(line, ' ');
                first = std::stoi(info[0]);
                second = std::stoi(info[1]);
                availableBalance[first] = second;
            }
        }
        this->initializeBanknotes();
        file.close();
    }

    void run();

    void runCommand(const std::string &input);

    static std::vector<std::string> split(const std::string &s, char delimiter);

    void printMenu();

    void handleAdd(std::vector<std::string> args);

    void handlePrint(std::vector<std::string> args);

    static bool isNumber(std::string s);

    static bool isFloat(std::string s);

    void handleAutoAdd();

    void handleRemove(std::vector<std::string> args);

    void handleBuy(std::vector<std::string> args);

    int getBalance();

    void printSum();

    void printChange();

    void initializeBanknotes();
};


#endif //LAB9_10_VENDINGMACHINE_H

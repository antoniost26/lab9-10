//
// Created by Antonio on 5/3/2022.
//

#include "VendingMachineUI.h"

void VendingMachineUI::run() {
    std::cout << "Welcome to the User Interface!" << std::endl;
    std::cout << "To view the command menu, type 'help'" << std::endl;

    std::string input;
    do {
        std::cout << "Waiting for input..." << std::endl;
        std::cout << "> ";
        try {
            std::getline(std::cin, input);
            if (!input.empty()) {
                runCommand(input);
            } else {
                std::cout << "No input detected." << std::endl;
            }
        }
        catch (MyException &e) {
            std::cout << "MyException: " << e.what() << std::endl;
        }
        catch (std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Unknown error." << std::endl;
        }
    } while (input != "quit");
}

void VendingMachineUI::runCommand(const std::string &input) {
    std::vector<std::string> args = split(input, ' ');
    std::string shouldDo = args[0];
    args.erase(args.begin());
    if (shouldDo == "help") {
        printMenu();
    } else if (shouldDo == "buy") {
        handleBuy(args);
    } else if (shouldDo == "print") {
        handlePrint(args);
    } else if (shouldDo == "quit") {
        std::cout << "Thanks for using my app! Goodbye." << std::endl;
    } else if (shouldDo == "add") {
        if (!this->isAdmin) {
            std::cout << "You are not an admin." << std::endl;
        } else {
            handleAdd(args);
        }
    } else if (shouldDo == "autoload") {
        if (!this->isAdmin) {
            throw MyException("You are not an admin!");
        } else {
            this->handleAutoAdd();
        }
    } else if (shouldDo == "remove") {
        if (!this->isAdmin) {
            throw MyException("You are not an admin!");
        } else {
            this->handleRemove(args);
        }
    } else if (shouldDo == "balance") {
        if (!this->isAdmin) {
            throw MyException("You are not an admin!");
        } else {
            this->printChange();
        }
    } else if (shouldDo == "sum") {
        if (!this->isAdmin) {
            throw MyException("You are not an admin!");
        } else {
            this->printSum();
        }
    } else if (shouldDo == "*1234*") {
        if (this->isAdmin) {
            this->isAdmin = false;
            return;
        }
        std::cout << "Enter admin password: ";
        std::string password;
        std::getline(std::cin, password);
        if (password == "parola123") {
            this->isAdmin = true;
        } else {
            std::cout << "Invalid password." << std::endl;
        }
    } else if (shouldDo == "edit") {
        if (!this->isAdmin) {
            throw MyException("You are not an admin!");
        } else {
            this->handleEdit(args);
        }
    } else if (shouldDo == "editcode") {
        if (!this->isAdmin) {
            throw MyException("You are not an admin!");
        } else {
            this->handleEditCode(args);
        }
    } else {
        std::cout << "Invalid command. Try typing 'help' to see all commands." << std::endl;
    }
}

std::vector<std::string> VendingMachineUI::split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void VendingMachineUI::printMenu() {
    std::cout << "Commands:" << std::endl;
    std::cout << "buy <code> \n\t Buys a product using an id"
                 "\n\t Supports multiple id for multiple buy." << std::endl;
    std::cout << "print \n\t Prints all available products." << std::endl;
    std::cout << "quit \n\t Quits the program." << std::endl;
    if (this->isAdmin) {
        std::cout << "add <id> <code> <name> <price> <quantity> \n\t Adds a product to the vending machine."
                  << std::endl;
        std::cout << "remove <id> \n\t Removes a product from the vending machine." << std::endl;
        std::cout << "editcode <id> <new-code>"
                     "\n\t Edits an existing product. Id must exist." << std::endl;
        std::cout << "edit <id> <new-code> <new-name> <new-price> <new-quantity>"
                     "\n\t Edits an existing product. Id must exist." << std::endl;
        std::cout << "edit <id> <new-quantity> "
                     "\n\t Edits an existing product. Id must exist." << std::endl;
        std::cout << "edit <id> <new-price> "
                     "\n\t Edits an existing product. Id must exist." << std::endl;
        std::cout << "edit <id> <new-name> "
                     "\n\t Edits an existing product. Id must exist." << std::endl;
        std::cout << "autoload "
                     "\n\t Adds random products to the vending machine." << std::endl;
        std::cout << "balance"
                     "\n\t Prints available balance by banknotes." << std::endl;
        std::cout << "sum "
                     "\n\t Prints the sum of balance." << std::endl;
    }
}

void VendingMachineUI::handleAdd(std::vector<std::string> args) {
    if (args.size() != 5) {
        throw MyException("Invalid number of arguments. Try typing 'help' to see all commands.");
    }
    int id = std::stoi(args[0]);
    std::string code = args[1];
    std::string name = args[2];
    double price = std::stod(args[3]);
    int quantity = std::stoi(args[4]);

    Product product(id, code, name, price, quantity);
    this->machineService.addProduct(product);
}

void VendingMachineUI::handlePrint(std::vector<std::string> args) {
    std::cout << "Products:" << std::endl;
    for (auto &product: this->machineService.getAll()) {
        isAdmin
        ? std::cout << std::setprecision(2) << std::fixed << product.toStringAdmin() << std::endl
        : std::cout << std::setprecision(2) << std::fixed << product << std::endl;
    }
}

bool VendingMachineUI::isNumber(std::string s) {
    return !s.empty() && std::find_if(
            s.begin(),
            s.end(),
            [](char c
            ) {
                return !std::isdigit(c);
            }) == s.end();
}

bool VendingMachineUI::isFloat(std::string s) {
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}

void VendingMachineUI::handleAutoAdd() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 100.0);

    for (int i = 0; i < 10; i++) {
        this->machineService.addProduct(
                Product(
                        (int) floor(dist(mt)),
                        std::to_string(i),
                        "Product" + std::to_string((int) floor(dist(mt))),
                        (int) floor(dist(mt)),
                        (int) floor(dist(mt))
                )
        );
    }
}

void VendingMachineUI::handleRemove(std::vector<std::string> args) {
    if (args.size() != 1) {
        throw MyException("Invalid number of arguments. Try typing 'help' to see all commands.");
    }
    int id = std::stoi(args[0]);
    this->machineService.removeProduct(id);
}

void VendingMachineUI::handleBuy(std::vector<std::string> args) {
    if (args.empty()) {
        throw MyException("Invalid number of arguments. Try typing 'help' to see all commands.");
    }
    double total = 0;
    std::vector<Product> products = this->machineService.getAll();
    for (auto it: args) {
        auto product = std::find_if(
                products.begin(),
                products.end(),
                [it](Product &product) {
                    return product.getCode() == it;
                }r
        );
        if (product == products.end()) {
            throw MyException("Product with code " + it + " does not exist.");
        }

        if (product->getQuantity() == 0) {
            throw MyException("Product with code " + it + " is out of stock.");
        }
        total += product->getPrice();
        product->setQuantity(product->getQuantity() - 1);
    }
    std::cout << "Total: " << total << std::endl;

    std::map<double, int> balance;
    double maxBalance = 0;

    do {
        std::string _money;

        std::cout << "Insert money: ";
        std::getline(std::cin, _money);

        double money = std::stod(_money);

        if (!CoinsValidator::isValid(Coins(money, 1))) {
            std::cout << "Invalid money inserted." << std::endl;
        } else {
            balance[money]++;
            maxBalance += money;
            std::cout << "Money inserted" << std::endl;
            std::cout << "Current balance: " << maxBalance << std::endl;
        }
        std::cout << "Current balance: " << maxBalance << std::endl;
    } while (maxBalance < total);
    std::vector<Coins> toBuy;
    for (auto it: balance) {
        toBuy.emplace_back(it.first, it.second);
    }


    std::vector<Coins> change = this->machineService.buy(args, toBuy);
    std::cout << "Change: " << std::endl;
    for (auto it: change) {
        std::cout << it.getValue() << ": " << it.getQuantity() << std::endl;
    }
}

int VendingMachineUI::getBalance() {
    int availableSumBalance = 0;
    for (auto coin: this->machineService.getCoins()) {
        availableSumBalance += coin.getValue() * coin.getQuantity();
    }
    return availableSumBalance;
}

void VendingMachineUI::printSum() {
    std::cout << "Available balance: " << std::setprecision(2) << std::fixed << this->getBalance() << std::endl;
}

void VendingMachineUI::printChange() {
    std::cout << "Available change: " << std::endl;
    for (auto coin: this->machineService.getCoins()) {
        std::cout << std::setprecision(2) << std::fixed << coin.getValue() << ": " << coin.getQuantity() << std::endl;
    }
}

void VendingMachineUI::handleEdit(std::vector<std::string> args) {
    if (args.size() < 2 || args.size() > 4 || args.size() == 3) {
        std::cout << "Invalid number of arguments." << std::endl;
        return;
    }

    if (args.size() == 2) {
        if (this->isNumber(args[1])) {
            this->machineService.updateProduct(std::stoi(args[0]), std::stoi(args[1]));
        } else if (!this->isNumber(args[1]) && !this->isFloat(args[1])) {
            this->machineService.updateProduct(std::stoi(args[0]), args[1]);
        } else {
            this->machineService.updateProduct(std::stoi(args[0]), std::stod(args[1]));
        }
    } else if (args.size() == 5) {
        this->machineService.updateProduct(Product(
                std::stoi(args[0]), args[1], args[2], std::stod(args[3]), std::stoi(args[4]))
        );
    }
}

void VendingMachineUI::handleEditCode(std::vector<std::string> args) {
    if (args.size() != 2) {
        throw MyException("Invalid number of arguments.");
    }

    this->machineService.updateProductCode(std::stoi(args[0]), args[1]);
}

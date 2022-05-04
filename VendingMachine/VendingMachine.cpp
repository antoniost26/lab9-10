//
// Created by Antonio on 5/3/2022.
//

#include "VendingMachine.h"

void VendingMachine::run() {
    std::cout << "Welcome to the User Interface!" << std::endl;
    std::cout << "To view the command menu, type 'help'" << std::endl;

    std::string input;
    do{
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
        catch (std::out_of_range &e) {
            std::cout << "Out of range: " << e.what() << std::endl;
        }
        catch (std::invalid_argument &e) {
            std::cout << "Invalid argument: " << e.what() << std::endl;
        }
        catch (std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    } while (input != "quit");
}

void VendingMachine::runCommand(const std::string& input) {
    bool isAdmin = false;
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
            throw std::invalid_argument("You are not an admin!");
        } else {
            this->handleAutoAdd();
        }
    } else if (shouldDo == "remove") {
        if (!this->isAdmin) {
            throw std::invalid_argument("You are not an admin!");
        } else {
            this->handleRemove(args);
        }
    } else if (shouldDo == "change") {
        if (!this->isAdmin) {
            throw std::invalid_argument("You are not an admin!");
        } else {
            this->printChange();
        }
    } else if (shouldDo == "sum") {
        if (!this->isAdmin) {
            throw std::invalid_argument("You are not an admin!");
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
    } else {
        std::cout << "Invalid command. Try typing 'help' to see all commands." << std::endl;
    }
}

std::vector<std::string> VendingMachine::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void VendingMachine::printMenu() {
    std::cout << "Commands:" << std::endl;
    std::cout << "buy <id>" << std::endl;
    std::cout << "print \n\t Prints all available products." << std::endl;
    std::cout << "quit \n\t Quits the program." << std::endl;
    if (this->isAdmin) {
        std::cout << "add <id> <name> <price> <quantity> \n\t Adds a product to the vending machine." << std::endl;
        std::cout << "autoload \n\t Adds all products to the vending machine." << std::endl;
        std::cout << "remove <id> \n\t Removes a product from the vending machine." << std::endl;
        std::cout << "change \n\t Prints available change." << std::endl;
        std::cout << "sum \n\t Prints the sum of balance." << std::endl;
    }
}

void VendingMachine::handleAdd(std::vector<std::string> args) {
    if (args.size() != 4) {
        throw std::invalid_argument("Invalid number of arguments. Try typing 'help' to see all commands.");
    }
    int id = std::stoi(args[0]);
    std::string name = args[1];
    double price = std::stod(args[2]);
    int quantity = std::stoi(args[3]);

    Product product(id, name, price, quantity);
    this->productService.addProduct(product);
}

void VendingMachine::handlePrint(std::vector<std::string> args) {
    std::cout << "Products:" << std::endl;
    for (auto &product : this->productService.getAll()) {
        std::cout << product << std::endl;
    }
}

bool VendingMachine::isNumber(std::string s) {
    return !s.empty() && std::find_if(
            s.begin(),
            s.end(),
            [](char c
            ) {
                return !std::isdigit(c);
            }) == s.end();
}

bool VendingMachine::isFloat(std::string s) {
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}

void VendingMachine::handleAutoAdd() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 100.0);

    for (int i = 0; i < 10; i++) {
        this->productService.addProduct(
                Product(
                        (int) floor(dist(mt)),
                        "Product" + std::to_string((int) floor(dist(mt))),
                        (int) floor(dist(mt)),
                        (int) floor(dist(mt))
                )
        );
    }
}

void VendingMachine::handleRemove(std::vector<std::string> args) {
    if (args.size() != 1) {
        throw std::invalid_argument("Invalid number of arguments. Try typing 'help' to see all commands.");
    }
    int id = std::stoi(args[0]);
    this->productService.removeProduct(id);
}

void VendingMachine::handleBuy(std::vector<std::string> args) {
    if (args.size() != 1) {
        throw std::invalid_argument("Invalid number of arguments. Try typing 'help' to see all commands.");
    }

    int id = std::stoi(args[0]);
    Product product = this->productService.getProduct(id);

    if (product.getQuantity() == 0) {
        std::cout << "Product out of stock." << std::endl;
        return;
    }

    std::map<int, int> balance;

    balance[1] = 0;
    balance[5] = 0;
    balance[10] = 0;
    balance[20] = 0;
    balance[50] = 0;
    balance[100] = 0;
    balance[200] = 0;
    balance[500] = 0;

    int maxBalance = 0;

    do {
        std::string _money;

        std::cout << "Insert money: ";
        std::getline(std::cin, _money);

        int money = std::stoi(_money);

        if (money != 1 && money != 5 && money != 10 && money != 20 && money != 50 && money != 100 && money != 200 && money != 500) {
            std::cout << "Invalid money amount." << std::endl;
        } else {
            balance[money]++;
            maxBalance+=money;
        }
    } while (maxBalance < product.getPrice());

    double change = maxBalance - product.getPrice();
    std::map <int, int> coins = this->availableBalance;
    int sumBalance = this->getBalance();

    std::cout << "Change to be given: " << change << std::endl;

    std::map<int, int>::reverse_iterator it;

    for (it = coins.rbegin(); it != coins.rend(); ++it) {
        while (change >= it->first && it->second > 0) {
            change -= it->first;
            it->second--;
        }
    }

    if (change == 0) {
        std::cout << "Thank you for your purchase." << std::endl;
        this->availableBalance = coins;
        for (auto it : balance) {
            it.second > 0 ? this->availableBalance[it.first]+= it.second : 0;
        }
        product.setQuantity(product.getQuantity() - 1);
        this->productService.updateProduct(product);
    } else {
        std::cout << "Vending machine doesn't have enough change. We're sorry." << std::endl;
    }
}

int VendingMachine::getBalance() {
    int availableSumBalance = 0;
    for (auto coin : this->availableBalance) {
        availableSumBalance += coin.first * coin.second;
    }
    return availableSumBalance;
}

void VendingMachine::printSum() {
    std::cout << "Available balance: " << this->getBalance() << std::endl;
}

void VendingMachine::printChange() {
    std::cout << "Available change: " << std::endl;
    for (auto coin : this->availableBalance) {
        std::cout << coin.first << ": " << coin.second << std::endl;
    }
}

void VendingMachine::initializeBanknotes() {
    std::vector<int> banknotes = {1, 5, 10, 20, 50, 100, 200};
    for (auto banknote : banknotes) {
        this->availableBalance[banknote]? this->availableBalance[banknote] : 0;
    }
}

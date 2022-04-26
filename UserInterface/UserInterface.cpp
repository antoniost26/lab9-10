//
// Created by Antonio on 4/16/2022.
//

#include <algorithm>
#include "UserInterface.h"

void UserInterface::run() {
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

void UserInterface::runCommand(const std::string& input) {
    std::vector<std::string> args = split(input, ' ');
    std::string shouldDo = args[0];
    args.erase(args.begin());
    if (shouldDo == "help") {
        printMenu();
    } else if (shouldDo == "add") {
        handleAdd(args);
    } else if (shouldDo == "print") {
        handlePrint(args);
    } else if (shouldDo == "quit") {
        std::cout << "Thanks for using my app! Goodbye." << std::endl;
    } else if (shouldDo == "autoadd") {
        this->handleAutoAdd();
    } else {
        std::cout << "Invalid command. Try typing 'help' to see all commands." << std::endl;
    }
}

std::vector<std::string> UserInterface::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void UserInterface::printMenu() {
    std::cout << "Commands:" << std::endl;
    std::cout << "add <id> <price> <quantity>\n\t Adds a product to productService. *Awaits input for title and description." << std::endl;
    std::cout << "print \n\t Prints all products from productService." << std::endl;
    std::cout << "quit \n\t Quits the program." << std::endl;
}

void UserInterface::handleAdd(std::vector<std::string> args) {
    if (args.size() != 3) {
        throw std::invalid_argument("Invalid number of arguments. Try typing 'help' to see all commands.");
    }

    std::string description, title;

    std::cout << "Please enter a title for the product." << std::endl;
    std::cout << "> ";
    std::getline(std::cin, title);

    std::cout << "Please enter a description for the product." << std::endl;
    std::cout << "> ";
    std::getline(std::cin, description);

    int id = std::stoi(args.at(0));
    double price = std::stof(args.at(1));
    int quantity = std::stoi(args.at(2));
    Product product(id, title, description, price, quantity);
    this->productService.addProduct(product);
}

void UserInterface::handlePrint(std::vector<std::string> args) {
    std::cout << "Products:" << std::endl;
    for (auto &product : this->productService.getAll()) {
        std::cout << product << std::endl;
    }
}

bool UserInterface::isNumber(std::string s) {
    return !s.empty() && std::find_if(
            s.begin(),
            s.end(),
            [](char c
            ) {
        return !std::isdigit(c);
    }) == s.end();
}

bool UserInterface::isFloat(std::string s) {
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}

void UserInterface::handleAutoAdd() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 100.0);

    for (int i = 0; i < 10; i++) {
        this->productService.addProduct(
                Product(
                        (int)floor(dist(mt)),
                        "Product " + std::to_string((int)floor(dist(mt))),
                        "Description " + std::to_string((int)floor(dist(mt))),
                        (int)floor(dist(mt)),
                        (int)floor(dist(mt))
                )
        );
    }
}
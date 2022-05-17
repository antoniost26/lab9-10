//
// Created by Antonio on 4/16/2022.
//

#include "VendingMachineService.h"

void VendingMachineService::addProduct(Product p) {

    std::string errors = ProductValidator::validate(p);
    if (errors.empty()) {
        this->doesExist(p);

        this->productRepo.add(p);
    } else {
        throw MyException(errors.c_str());
    }
}

void VendingMachineService::removeProduct(int _id) {
    this->productRepo.remove(_id);
}

void VendingMachineService::updateProduct(Product p) {
    std::string errors = ProductValidator::validate(p);
    if (errors.empty()) {
        this->productRepo.update(p);
    } else {
        throw MyException(errors.c_str());
    }
}

std::vector<Product> VendingMachineService::getAll() {
    return this->productRepo.getAll();
}

int VendingMachineService::getSize() {
    return this->productRepo.getSize();
}

Product VendingMachineService::getProduct(int i) {
    return this->productRepo.get(i);
}

void VendingMachineService::updateProduct(int _id, int _quantity) {
    Product newProduct = this->productRepo.get(_id);
    newProduct.setQuantity(_quantity);
    std::string errors = ProductValidator::validate(newProduct);
    if (errors.empty()) {
        this->productRepo.update(newProduct);
    } else {
        throw MyException(errors.c_str());
    }
}

void VendingMachineService::updateProduct(int _id, std::string _name) {
    Product newProduct = this->productRepo.get(_id);
    newProduct.setName(_name);
    std::string errors = ProductValidator::validate(newProduct);
    if (errors.empty()) {
        this->productRepo.update(newProduct);
    } else {
        throw MyException(errors.c_str());
    }
}

void VendingMachineService::updateProduct(int _id, double price) {
    Product newProduct = this->productRepo.get(_id);
    newProduct.setPrice(price);
    std::string errors = ProductValidator::validate(newProduct);
    if (errors.empty()) {
        this->productRepo.update(newProduct);
    } else {
        throw MyException(errors.c_str());
    }
}

Product VendingMachineService::getProductByCode(std::string code) {
    return this->productRepo.get(code);
}

void VendingMachineService::doesExist(Product &product) {
    std::vector<Product> products = this->productRepo.getAll();

    for (auto& _product : products) {
        if (_product.getId() == product.getId()) {
            throw MyException(std::string("Product with id " + std::to_string(product.getId()) + " already exists!").c_str());
        }
    }
}

void VendingMachineService::updateProductCode(int id, std::string newCode) {
    Product newProduct = this->productRepo.get(id);
    newProduct.setCode(newCode);
    std::string errors = ProductValidator::validate(newProduct);
    if (errors.empty()) {
        this->productRepo.update(newProduct);
    } else {
        throw MyException(errors.c_str());
    }
}

std::vector<Coins> VendingMachineService::buy(std::vector<std::string> codes, std::vector<Coins> balance) {

    std::vector<Coins> returnChange;
    double total = 0;
    for (auto& code : codes) {
        Product product = this->productRepo.get(code);
        total += product.getPrice();
    }

    double totalBalance = 0;
    for (auto& coin : balance) {
        totalBalance += coin.getValue()*coin.getQuantity();
    }

    if (total > totalBalance) {
        throw MyException("Not enough money!");
    }

    double change = totalBalance - total;

    std::vector<Coins>::reverse_iterator it;
    std::vector<Coins> coins = this->coinsRepo.getAll();
    for (it = coins.rbegin(); it != coins.rend(); ++it) {

        while (change >= it->getValue() && it->getQuantity() > 0) {
            if (returnChange.empty()) {
                returnChange.emplace_back(it->getValue(), 1);
            } else {
                if (returnChange.back().getValue() == it->getValue()) {
                    returnChange.back().setQuantity(returnChange.back().getQuantity() + 1);
                } else {
                    returnChange.push_back(*it);
                }
            }
            change -= it->getValue();
            it->setQuantity(it->getQuantity() - 1);
            this->coinsRepo.update(*it);
        }
    }

    if (change > 0.01) {
        throw MyException("Machine doesn't have enough money!");
    }

    for (auto& code : codes) {
        Product product = this->productRepo.get(code);
        product.setQuantity(product.getQuantity() - 1);
        this->productRepo.update(product);
    }

    return returnChange;
}

std::vector<Coins> VendingMachineService::getCoins() {
    return this->coinsRepo.getAll();
}

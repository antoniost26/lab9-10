//
// Created by Antonio on 4/16/2022.
//

#include "ProductService.h"

void ProductService::addProduct(Product p) {

    std::string errors = ProductValidator::validate(p);
    if (errors.empty()) {
        this->doesExist(p);

        this->repo.add(p);
    } else {
        throw MyException(errors);
    }
}

void ProductService::removeProduct(int _id) {
    this->repo.remove(_id);
}

void ProductService::updateProduct(Product p) {
    std::string errors = ProductValidator::validate(p);
    if (errors.empty()) {
        this->repo.update(p);
    } else {
        throw MyException(errors);
    }
}

std::vector<Product> ProductService::getAll() {
    return this->repo.getAll();
}

int ProductService::getSize() {
    return this->repo.getSize();
}

Product ProductService::getProduct(int i) {
    return this->repo.get(i);
}

void ProductService::updateProduct(int _id, int _quantity) {
    Product newProduct = this->repo.get(_id);
    newProduct.setQuantity(_quantity);
    std::string errors = ProductValidator::validate(newProduct);
    if (errors.empty()) {
        this->repo.update(newProduct);
    } else {
        throw MyException(errors);
    }
}

void ProductService::updateProduct(int _id, std::string _name) {
    Product newProduct = this->repo.get(_id);
    newProduct.setName(_name);
    std::string errors = ProductValidator::validate(newProduct);
    if (errors.empty()) {
        this->repo.update(newProduct);
    } else {
        throw MyException(errors);
    }
}

void ProductService::updateProduct(int _id, double price) {
    Product newProduct = this->repo.get(_id);
    newProduct.setPrice(price);
    std::string errors = ProductValidator::validate(newProduct);
    if (errors.empty()) {
        this->repo.update(newProduct);
    } else {
        throw MyException(errors);
    }
}

Product ProductService::getProductByCode(std::string code) {
    return this->repo.get(code);
}

void ProductService::doesExist(Product &product) {
    std::vector<Product> products = this->repo.getAll();

    for (auto& _product : products) {
        if (_product.getId() == product.getId()) {
            throw MyException("Product with id " + std::to_string(product.getId()) + " already exists!");
        }
    }
}

void ProductService::updateProductCode(int id, std::string newCode) {
    Product newProduct = this->repo.get(id);
    newProduct.setCode(newCode);
    std::string errors = ProductValidator::validate(newProduct);
    if (errors.empty()) {
        this->repo.update(newProduct);
    } else {
        throw MyException(errors);
    }
}

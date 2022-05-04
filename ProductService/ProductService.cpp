//
// Created by Antonio on 4/16/2022.
//

#include "ProductService.h"

void ProductService::addProduct(Product p) {
    this->validator.setProduct(p);
    this->validator.validate();
    this->repo.add(p);
}

void ProductService::removeProduct(int _id) {
    this->repo.remove(_id);
}

void ProductService::updateProduct(Product p) {
    this->validator.setProduct(p);
    this->validator.update();
    this->repo.update(p);
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

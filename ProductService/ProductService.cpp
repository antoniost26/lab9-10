//
// Created by Antonio on 4/16/2022.
//

#include "ProductService.h"

void ProductService::addProduct(Product p) {
    this->validator.setProduct(p);
    this->validator.validate();
    this->repo.add(p);
}

void ProductService::removeProduct(Product p) {
    this->validator.setProduct(p);
    this->validator.validate();
    this->repo.remove(p);
}

void ProductService::updateProduct(Product p) {
    this->validator.setProduct(p);
    this->validator.validate();
    this->repo.update(p);
}

std::vector<Product> ProductService::getAll() {
    return this->repo.getAll();
}

int ProductService::getSize() {
    return this->repo.getSize();
}

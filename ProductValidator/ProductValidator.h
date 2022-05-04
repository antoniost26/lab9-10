//
// Created by Antonio on 4/22/2022.
//
#include "../Domain/Product.h"
#include "../Repository/IRepo.h"
#include <algorithm>

#ifndef LAB9_10_PRODUCTVALIDATOR_H
#define LAB9_10_PRODUCTVALIDATOR_H


class ProductValidator {
private:
    Product product;
    IRepo<Product>& repo;
public:
    explicit ProductValidator(IRepo<Product>& _repo) : repo{_repo} {};

    void validate();

    void setProduct(Product other) {this->product = other;};

    bool doesExit();

    void update();
};


#endif //LAB9_10_PRODUCTVALIDATOR_H

//
// Created by Antonio on 4/22/2022.
//
#include "../Domain/Product.h"
#include "../Repository/IRepo.h"
#include <algorithm>
#include "../Domain/MyException.h"

#ifndef LAB9_10_PRODUCTVALIDATOR_H
#define LAB9_10_PRODUCTVALIDATOR_H


class ProductValidator {
public:
    /**
     * Validates a product
     * @param p the product to be validated
     */
    static std::string validate(Product &p);
};


#endif //LAB9_10_PRODUCTVALIDATOR_H

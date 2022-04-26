//
// Created by Antonio on 4/22/2022.
//

#include "ProductValidator.h"

void ProductValidator::validate() {
    if(this->doesExit()) {
        throw std::invalid_argument("Product already exists.");
    } else if (this->product.getId() <= 0) {
        throw std::invalid_argument("Product's id needs to be a positive integer.");
    } else if (this->product.getPrice() <= 0) {
        throw std::invalid_argument("Product's price needs to be a positive double/float.");
    } else if (this->product.getQuantity() < 0) {
        throw std::invalid_argument("Product's quantity has to be greater or equal to 0.");
    } else if (this->product.getName().empty()) {
        throw std::invalid_argument("Product needs a name.");
    } else if (this->product.getDescription().empty()) {
        throw std::invalid_argument("Product needs a description.");
    }
}

bool ProductValidator::doesExit() {
    for (auto it : this->repo.getAll()) {
        if (it.getId() == this->product.getId()) {
            return true;
        }
    }
    return false;
}

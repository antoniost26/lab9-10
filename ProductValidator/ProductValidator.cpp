//
// Created by Antonio on 4/22/2022.
//

#include "ProductValidator.h"

std::string ProductValidator::validate(Product &p) {
    std::string errors;
    if (p.getId() <= 0) {
        errors += ("Product's id needs to be a positive integer.");
    } else if (p.getCode().empty()) {
        errors += ("Product's code needs to be a non-empty string.");
    } else if (std::stod(p.getCode()) <= 0) {
        errors += ("Product's code needs to be a positive number.");
    } else if (p.getPrice() <= 0) {
        errors += ("Product's price needs to be a positive double/float.");
    } else if (p.getQuantity() < 0) {
        errors += ("Product's quantity has to be greater or equal to 0.");
    } else if (p.getName().empty()) {
        errors += ("Product needs a name.");
    }
    return errors;
}

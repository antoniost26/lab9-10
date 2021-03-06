//
// Created by Antonio on 5/10/2022.
//
#include "../Domain/Coins.h"
#include "../Domain/MyException.h"

#ifndef LAB9_10_COINSVALIDATOR_H
#define LAB9_10_COINSVALIDATOR_H


class CoinsValidator {
public:
    /**
     * Validates the coins.
     * @param _value a Coins object.
     */
    static bool isValid(Coins _value);
};


#endif //LAB9_10_COINSVALIDATOR_H

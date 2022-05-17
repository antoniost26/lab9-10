//
// Created by Antonio on 5/10/2022.
//

#include "CoinsValidator.h"

bool CoinsValidator::isValid(Coins _value) {
    std::vector<Coins> coins;
    {
        coins.emplace_back(0.01, 1);
        coins.emplace_back(0.05, 1);
        coins.emplace_back(0.10, 1);
        coins.emplace_back(0.50, 1);
        coins.emplace_back(1, 1);
        coins.emplace_back(5, 1);
        coins.emplace_back(10, 1);
        coins.emplace_back(20, 1);
        coins.emplace_back(50, 1);
        coins.emplace_back(100, 1);
        coins.emplace_back(200, 1);
        coins.emplace_back(500, 1);
    }

    if (_value.getValue() <= 0) {
        return false;
    } else {
        bool isValid = false;
        for (auto it: coins) {
            if (it == _value) {
                isValid = true;
            }
        }
        if (!isValid) {
            return false;
        }
    }
    return true;
}

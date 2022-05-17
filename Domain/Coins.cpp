//
// Created by Antonio on 5/10/2022.
//

#include <complex>
#include "Coins.h"

Coins::Coins() {
    this->value = 0;
    this->quantity = 0;
}

Coins::Coins(double value, int quantity) {
    this->value = value;
    this->quantity = quantity;
}

void Coins::setValue(double _value) {
    this->value = _value;
}

void Coins::setQuantity(int _quantity) {
    this->quantity = _quantity;
}

double Coins::getValue() const {
    return this->value;
}

int Coins::getQuantity() const {
    return this->quantity;
}

bool Coins::operator==(Coins &c) const {
    return (std::abs(this->value - c.getValue()) < 1e-9);
}

bool Coins::operator!=(Coins &c) {
    return !(*this == c);
}

bool Coins::operator<(Coins &c) const {
    return (this->value < c.getValue());
}

bool Coins::operator>(Coins &c) const {
    return (this->value > c.getValue());
}

bool Coins::operator<=(Coins &c) const {
    return (*this == c || *this < c);
}

bool Coins::operator>=(Coins &c) const {
    return (*this == c || *this > c);
}

bool Coins::operator>(double x) const {
    return (std::abs(this->value - x) < 1e-9);
}

Coins::Coins(double value) {
    this->value = value;
    this->quantity = 0;
}

Coins::Coins(std::string args) {
    std::vector<std::string> elements;
    std::stringstream ss(args);
    std::string item;
    while (getline(ss, item, ' ')) {
        elements.push_back(item);
    }
    if (elements.size() == 2) {
        std::stringstream i(elements[0]);
        i >> this->value;
        std::stringstream c(elements[1]);
        c >> this->quantity;
    }
}

std::string Coins::toString() const {
    return std::to_string(this->value) + " " + std::to_string(this->quantity);
}

bool Coins::operator==(int i) const {
    return (std::abs(this->value - i) < 1e-9);
}

std::string Coins::getCode() const {
    return std::to_string(this->value);
}

double Coins::getId() const {
    return this->value;
}

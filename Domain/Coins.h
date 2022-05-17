//
// Created by Antonio on 5/10/2022.
//
#include <vector>
#include <string>

#ifndef LAB9_10_COINS_H
#define LAB9_10_COINS_H


class Coins {
private:
    double value;
    int quantity;
public:
    Coins();
    explicit Coins(std::string args);
    explicit Coins(double value);
    Coins(double value, int quantity);
    void setValue(double _value);
    void setQuantity(int _quantity);
    double getValue() const;
    int getQuantity() const;
    std::string getCode() const;
    double getId() const;
    bool operator==(Coins &c) const;
    bool operator==(int i) const;
    bool operator!=(Coins &c);
    bool operator<(Coins &c) const;
    bool operator>(Coins &c) const;
    bool operator>(double x) const;
    bool operator<=(Coins &c) const;
    bool operator>=(Coins &c) const;
    std::string toString() const;
};


#endif //LAB9_10_COINS_H

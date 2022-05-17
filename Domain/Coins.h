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
    /**
     * Constructor
     */
    Coins();

    /**
     * Constructor
     * @param args vector of strings
     */
    explicit Coins(std::string args);

    /**
     * Constructor
     * @param value coin value
     */
    explicit Coins(double value);

    /**
     * Constructor
     * @param value coin value
     * @param quantity coin quantity
     */
    Coins(double value, int quantity);

    /**
     * Setter for value
     * @param _value coin value
     */
    void setValue(double _value);

    /**
     * Setter for quantity
     * @param _quantity coin quantity
     */
    void setQuantity(int _quantity);

    /**
     * Getter for value
     * @return coin value
     */
    double getValue() const;

    /**
     * Getter for quantity
     * @return coin quantity
     */
    int getQuantity() const;

    /**
     * Getter for value
     * @return coin value as string
     */
    std::string getCode() const;

    /**
     * Getter for value
     * @return coin value as "id"
     */
    double getId() const;

    /**
     * Overload to operator ==
     * @param c a Coins object
     * @return true if value is equal, false otherwise
     */
    bool operator==(Coins &c) const;

    /**
     * Overload to operator ==
     * @param i an integer to be compared
     * @return true if equal, false otherwise
     */
    bool operator==(int i) const;

    /**
     * Overload to operator !=
     * @param c a Coins object
     * @return true if value is not equal, false otherwise
     */
    bool operator!=(Coins &c);

    /**
     * Overload to operator <
     * @param c a Coins object
     * @return true if value is less than, false otherwise
     */
    bool operator<(Coins &c) const;

    /**
     * Overload to operator >
     * @param c a Coins object
     * @return true if value is greater than, false otherwise
     */
    bool operator>(Coins &c) const;

    /**
     * Overload to operator >
     * @param x a double to be compared
     * @return true if value is greater than, false otherwise
     */
    bool operator>(double x) const;

    /**
     * Overload to operator <=
     * @param c a Coins object
     * @return true if value is less than or equal to, false otherwise
     */
    bool operator<=(Coins &c) const;

    /**
     * Overload to operator >=
     * @param x a double to be compared
     * @return true if value is greater than or equal to, false otherwise
     */
    bool operator>=(Coins &c) const;

    /**
     * Returns the object as string
     * @return the object as string
     */
    std::string toString() const;
};


#endif //LAB9_10_COINS_H

//
// Created by Antonio on 4/15/2022.
//

#include "Product.h"

#include <utility>

Product::Product() {
    this->id = -1;
    this->name = "";
    this->description = "";
    this->price = 0;
    this->quantity = 0;
}

Product::Product(int _id, std::string _name, std::string _description, double _price, int _quantity) {
    this->id = _id;
    this->name = std::move(_name);
    this->description = std::move(_description);
    this->price = _price;
    this->quantity = _quantity;
}

Product::Product(const Product &product) {
    this->id = product.id;
    this->name = product.name;
    this->description = product.description;
    this->price = product.price;
    this->quantity = product.quantity;
}

Product::~Product() = default;

int Product::getId() const {
    return this->id;
}

std::string Product::getName() const {
    return this->name;
}

std::string Product::getDescription() const {
    return this->description;
}

double Product::getPrice() const {
    return this->price;
}

void Product::setId(int _id) {
    this->id = _id;
}

void Product::setName(std::string _name) {
    this->name = _name;
}

void Product::setDescription(std::string _description) {
    this->description = _description;
}

void Product::setPrice(double _price) {
    this->price = _price;
}

bool Product::operator==(const Product &product) const {
    return (this->id == product.id && this->name == product.name && this->description == product.description &&
            this->price == product.price);
}

bool Product::operator!=(const Product &product) const {
    return !(*this == product);
}

bool Product::operator<(const Product &product) const {
    return (this->price < product.price);
}

bool Product::operator>(const Product &product) const {
    return !(*this < product);
}

bool Product::operator<=(const Product &product) const {
    return (*this < product || *this == product);
}

bool Product::operator>=(const Product &product) const {
    return !(*this < product || *this != product);
}

Product &Product::operator=(const Product &product) {
    this->id = product.id;
    this->name = product.name;
    this->description = product.description;
    this->price = product.price;
    this->quantity = product.quantity;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Product &product) {
    os << "(id " << product.getId() << ") - [name: '" << product.getName() << "', description: '" <<
    product.getDescription() << "', price: " << product.getPrice() << ", quantity: " << product.getQuantity() << "]"
    << std::endl;
    return os;
}
std::istream &operator>>(std::istream &is, Product &product) {
    is >> product.id >> product.name >> product.description >> product.price >> product.quantity;
    return is;
}

int Product::getQuantity() const {
    return this->quantity;
}

void Product::setQuantity(int _quantity) {
    this->quantity = _quantity;
}

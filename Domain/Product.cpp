//
// Created by Antonio on 4/15/2022.
//

#include "Product.h"
#include <vector>
#include <sstream>

Product::Product() {
    this->id = -1;
    this->name = "";
    this->price = 0;
    this->quantity = 0;
}

Product::Product(int _id,std::string code, std::string _name, double _price, int _quantity) {
    this->id = _id;
    this->code = code;
    this->name = _name;
    this->price = _price;
    this->quantity = _quantity;
}

Product::Product(const Product &product) {
    this->id = product.id;
    this->code = product.code;
    this->name = product.name;
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

double Product::getPrice() const {
    return this->price;
}

void Product::setId(int _id) {
    this->id = _id;
}

void Product::setName(std::string _name) {
    this->name = _name;
}

void Product::setPrice(double _price) {
    this->price = _price;
}

bool Product::operator==(const Product &product) const {
    return (this->id == product.id && this->code == product.code && this->name == product.name &&
            this->price == product.price && this->quantity == product.quantity);
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
    this->code = product.code;
    this->name = product.name;
    this->price = product.price;
    this->quantity = product.quantity;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Product &product) {
    os << "(code: " << product.code << ") - [name: '" << product.getName() <<
    "', price: " << product.getPrice() << ", quantity: " << product.getQuantity() << "]"
    << std::endl;
    return os;
}
std::istream &operator>>(std::istream &is, Product &product) {
    is >> product.id >> product.code >> product.name >> product.price >> product.quantity;
    return is;
}

int Product::getQuantity() const {
    return this->quantity;
}

void Product::setQuantity(int _quantity) {
    this->quantity = _quantity;
}

std::string Product::toString() {
    return std::to_string(this->id) + " " + this->code + " " + this->name + " " + std::to_string(this->price) + " "+
    std::to_string(this->quantity) + ",";
}

std::string Product::toStringAdmin(){
    return "(id: " + std::to_string(this->id) + ", code: " + this->code + ") - [name: '" + this->getName() +
                     "', price: " + std::to_string(this->getPrice())+ ", quantity: " +
                     std::to_string(this->getQuantity()) + "]";
}

void Product::fromString(std::string args) {
    std::vector<std::string> elements;
    std::stringstream ss(args);
    std::string item;
    while (getline (ss, item, ' ')) {
        elements.push_back(item);
    }
    if(elements.size() == 5) {
        std::stringstream i(elements[0]);
        i >> this->id;
        std::stringstream c(elements[1]);
        c >> this->code;
        std::stringstream n(elements[2]);
        n >> this->name;
        std::stringstream p(elements[3]);
        p >> this->price;
        std::stringstream q(elements[4]);
        q >> this->quantity;
    }
}

Product::Product(std::string args) {
    this->fromString(args);
}

std::string Product::getCode() const {
    return this->code;
}

void Product::setCode(std::string _code) {
    this->code = _code;
}

bool Product::operator==(const int id) const {
    return this->id == id;
}

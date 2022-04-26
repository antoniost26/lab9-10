//
// Created by Antonio on 4/15/2022.
//

//#include "ProductRepository.h"
//
//ProductRepository::ProductRepository() = default;
//
//ProductRepository::~ProductRepository() = default;
//
//void ProductRepository::addProduct(Product product) {
//    if (this->getPositionInVector(product.getId()) != -1) {
//        throw std::invalid_argument("Product with this id already exists!");
//    }
//    this->products.push_back(product);
//}
//
//void ProductRepository::removeProduct(Product product) {
//    if (this->getPositionInVector(product.getId()) == -1) {
//        throw std::out_of_range("Product with this id does not exist!");
//    }
//    auto it = this->products.begin() + getPositionInVector(product.getId());
//    if (it != this->products.end()) {
//        this->products.erase(it);
//    }
//}
//
//std::vector<Product> ProductRepository::getProducts() {
//    return this->products;
//}
//
//Product ProductRepository::getProduct(int id) {
//    if (this->getPositionInVector(id) == -1) {
//        throw std::out_of_range("Product with this id does not exist!");
//    }
//    return this->products[getPositionInVector(id)];
//}
//
//void ProductRepository::updateProduct(Product product) {
//    if (this->getPositionInVector(product.getId()) == -1) {
//        throw std::out_of_range("Product with this id does not exist!");
//    }
//    this->products[getPositionInVector(product.getId())] = product;
//}
//
//int ProductRepository::getPositionInVector(int _id) {
//    int index = 0;
//    for (const auto& it : this->products) {
//        if (it.getId() == _id) {
//            return index;
//        }
//        index++;
//    }
//    return -1;
//}
//
//unsigned int ProductRepository::getSize() {
//    return this->products.size();
//}

//
// Created by Antonio on 4/16/2022.
//
#include <utility>

#include "../Domain/Product.h"
#include "../Repository/MemoryRepository.h"
#include "../ProductValidator/ProductValidator.h"

#ifndef LAB9_10_PRODUCTSERVICE_H
#define LAB9_10_PRODUCTSERVICE_H


class ProductService {
private:
    IRepo<Product>& repo;
    ProductValidator validator;
public:
    explicit ProductService(IRepo<Product>& otherRepository, ProductValidator _validator) : repo{otherRepository},
                                                                                            validator{std::move(_validator)} {};
    ~ProductService() = default;
    void addProduct(Product p);
    void removeProduct(int _id);
    void updateProduct(Product p);
    std::vector<Product> getAll();
    int getSize();

    Product getProduct(int i);
};


#endif //LAB9_10_PRODUCTSERVICE_H

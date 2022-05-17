//
// Created by Antonio on 4/16/2022.
//
#include <utility>

#include "../Domain/Product.h"
#include "../Repository/MemoryRepository.h"
#include "../ProductValidator/ProductValidator.h"
#include "../Domain/Coins.h"

#ifndef LAB9_10_PRODUCTSERVICE_H
#define LAB9_10_PRODUCTSERVICE_H


class VendingMachineService {
private:
    IRepo<Product> &productRepo;
    IRepo<Coins> &coinsRepo;
public:
    /**
     * Constructor for the VendingMachineService class
     * @param otherRepository a repository
     */
    explicit VendingMachineService(IRepo<Product> &otherRepository, IRepo<Coins> &coinsRepo)
            : productRepo{otherRepository}, coinsRepo(coinsRepo) {};

    /**
     * Destructor
     */
    ~VendingMachineService() = default;

    /**
     * Adds a product to the repository
     * @param p a product
     */
    void addProduct(Product p);

    /**
     * Removes a product from the repository
     * @param _id product id
     */
    void removeProduct(int _id);

    /**
     * Updates a product in the repository
     * @param p a product
     */
    void updateProduct(Product p);

    /**
     * Updates a product in the repository
     * @param _id product id
     * @param _quantity product quantity
     */
    void updateProduct(int _id, int _quantity);

    /**
     * Updates a product in the repository
     * @param _id product id
     * @param _name product name
     */
    void updateProduct(int _id, std::string _name);

    /**
     * Updates a product in the repository
     * @param _id product id
     * @param price product price
     */
    void updateProduct(int _id, double price);

    /**
     * Gets all products from the repository
     * @return a vector containing all products
     */
    std::vector<Product> getAll();

    /**
     * Gets repository size
     * @return repository size
     */
    int getSize();

    /**
     * Gets a product from the repository
     * @param i product id
     * @return a product
     */
    Product getProduct(int i);

    /**
     * Gets a product from the repository
     * @param code product code
     * @return a product
     */
    Product getProductByCode(std::string code);

    /**
     * Checks to see if product exists in the repository
     * @param product a product
     */
    void doesExist(Product &product);

    /**
     * Updates product code for a product
     * @param id product id
     * @param newCode new product code
     */
    void updateProductCode(int id, std::string newCode);

    /**
     * Buys a product from the repository
     * @param codes product codes
     * @return returns a vector containing cash change
     */
    std::vector<Coins> buy(std::vector<std::string> codes, std::vector<Coins> balance);

    std::vector<Coins> getCoins();
};


#endif //LAB9_10_PRODUCTSERVICE_H

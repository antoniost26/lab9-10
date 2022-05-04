#include "./Domain/Product.h"
#include "./Tests/Tests.h"
#include "./ProductValidator/ProductValidator.h"
#include "./Repository/FileRepository.h"
#include "./VendingMachine/VendingMachine.h"

int main() {
    Tests::testAll();

    MemoryRepository<Product> repository;
    FileRepository<Product> fileRepo("../products.txt");
    IRepo<Product>& repoRef = fileRepo;

    ProductValidator validator(repoRef);
    ProductService productService(repoRef, validator);

    VendingMachine vendingMachine(productService);
    vendingMachine.run();

    return EXIT_SUCCESS;
}
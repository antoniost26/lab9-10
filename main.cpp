#include "./Domain/Product.h"
#include "./Tests/Tests.h"
#include "./UserInterface/UserInterface.h"
#include "./ProductValidator/ProductValidator.h"
#include "./Repository/FileRepository.h"

int main() {
    Tests::testAll();

    MemoryRepository<Product> repository;
    FileRepository<Product> fileRepo("../products.txt");
    IRepo<Product>& repoRef = fileRepo;

    ProductValidator validator(repoRef);
    ProductService productService(repoRef, validator);

    UserInterface UserInterface(productService);
    UserInterface.run();

    return EXIT_SUCCESS;
}
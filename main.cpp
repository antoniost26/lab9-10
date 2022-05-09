#include "./Domain/Product.h"
#include "./Tests/Tests.h"
#include "./ProductValidator/ProductValidator.h"
#include "./Repository/FileRepository.h"
#include "./VendingMachineUI/VendingMachineUI.h"

int main() {
    Tests::testAll();

    MemoryRepository<Product> repository;
    FileRepository<Product> fileRepo("../Database/products.txt");
    IRepo<Product>& repoRef = fileRepo;

    ProductService productService(repoRef);

    VendingMachineUI vendingMachine(productService);
    vendingMachine.run();

    return EXIT_SUCCESS;
}
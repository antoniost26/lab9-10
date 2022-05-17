#include "./Domain/Product.h"
#include "./Tests/Tests.h"
#include "./ProductValidator/ProductValidator.h"
#include "./Repository/FileRepository.h"
#include "./VendingMachineUI/VendingMachineUI.h"

int main() {
    Tests::testAll();

    MemoryRepository<Product> repository;
    FileRepository<Product> fileRepo("../Database/products.txt");
    FileRepository<Coins> coinsRepo("../Database/balance.txt");
    IRepo<Product>& repoRef = fileRepo;
    IRepo<Coins>& coinsRepoRef = coinsRepo;

    VendingMachineService vendingMachineService(repoRef, coinsRepoRef);

    VendingMachineUI vendingMachine(vendingMachineService);
    vendingMachine.run();

    return EXIT_SUCCESS;
}
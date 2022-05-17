//
// Created by Antonio on 4/16/2022.
//
#include "../Domain/Product.h"
#include "../Repository/MemoryRepository.h"
#include "../ProductValidator/ProductValidator.h"
#include "../VendingMachineService/VendingMachineService.h"
#include "../Repository/FileRepository.h"
#include <cassert>
#include <chrono>
#include <thread>

#ifndef LAB9_10_TESTS_H
#define LAB9_10_TESTS_H

class Tests {
public:
    static void testProduct() {
        Product p1(1, "1","p1", 1, 10);
        Product p2(2, "2", "p2", 2, 11);
        Product p3(3, "3","p3", 3, 12);
        assert(p1.getId() == 1);
        assert(p1.getName() == "p1");
        assert(p1.getPrice() == 1);
        assert(p2.getId() == 2);
        assert(p2.getName() == "p2");
        assert(p2.getPrice() == 2);
        assert(p3.getId() == 3);
        assert(p3.getName() == "p3");
        assert(p3.getPrice() == 3);
    }

    static void testMemoryRepository() {
        MemoryRepository<Product> r;
        IRepo<Product>& repo = r;
        testRepoAdd(repo);
        testRepoGetAll(repo);
        testRepoUpdate(repo);
        testRepoRemove(repo);
    }

    static void testRepoAdd(IRepo<Product> &repo) {
        Product p1(1, "2","p1", 1, 10);
        Product p2(2, "2","p2", 2, 11);
        Product p3(3, "3","p3", 3, 12);
        repo.add(p1);
        assert(repo.getSize() == 1);
        repo.add(p2);
        assert(repo.getSize() == 2);
        repo.add(p3);
        assert(repo.getSize() == 3);
        assert(repo.get(1) == p1);
        assert(repo.get(2) == p2);
        assert(repo.get(3) == p3);
    }

    static void testRepoGetAll(IRepo<Product> &repo) {
        std::vector<Product> v = repo.getAll();
        assert(v[0] == Product(1, "2","p1", 1, 10));
        assert(v[1] == Product(2, "2","p2", 2, 11));
        assert(v[2] == Product(3, "3","p3", 3, 12));
    }

    static void testRepoUpdate(IRepo<Product> &repo) {
        repo.update(Product(1, "1", "p1test", 1, 10));
        assert(repo.get(1).getName() == "p1test");
    }

    static void testRepoFile(IRepo<Product> &repo) {
        std::vector<Product> testVector;
        std::string line;
        std::ifstream myFile("./test.txt");

        while (getline(myFile, line)) {
            Product p(line);
            testVector.push_back(p);
        }

        assert(testVector[0].getName() == "p1test");
        assert(testVector[0].getPrice() == 1);
        assert(testVector[0].getId() == 1);
        assert(testVector[0].getQuantity() == 10);
        assert(testVector[1] == Product(2, "2","p2", 2, 11));
        assert(testVector[2] == Product(3, "3","p3", 3, 12));

    }

    static void testRepoRemove(IRepo<Product> &repo) {
        repo.remove(1);
        assert(repo.getSize() == 2);
        repo.remove(2);
        assert(repo.getSize() == 1);
        repo.remove(3);
        assert(repo.getSize() == 0);
    }

    static void testFileRepository() {
        FileRepository<Product> r("./test.txt");
        IRepo<Product>& repo = r;
        testRepoAdd(repo);
        testRepoGetAll(repo);

        testRepoUpdate(repo);

        testRepoFile(repo);

        testRepoRemove(repo);

        remove("./test.txt");
    }

    static void testServiceAdd(VendingMachineService &service) {
        Product p1(1,"1", "p1", 1, 10);
        Product p2(2, "2", "p2", 2, 11);
        Product p3(3, "3","p3", 3, 12);
        service.addProduct(p1);
        assert(service.getSize() == 1);
        service.addProduct(p2);
        assert(service.getSize() == 2);
        service.addProduct(p3);
        assert(service.getSize() == 3);
        assert(service.getProduct(1) == p1);
        assert(service.getProduct(2) == p2);
        assert(service.getProduct(3) == p3);
    }

    static void testServiceGetAll(VendingMachineService &service) {
        std::vector<Product> v1 = service.getAll();
        assert(v1[0] == Product(1,"1", "p1", 1, 10));
        assert(v1[1] == Product(2, "2", "p2", 2, 11));
        assert(v1[2] == Product(3, "3","p3", 3, 12));
    }

    static void testServiceUpdate(VendingMachineService &service) {
        service.updateProduct(Product(1,"1", "p1test", 2, 11));
        assert(service.getProduct(1).getName() == "p1test");
        assert(service.getProduct(1).getPrice() == 2);
        assert(service.getProduct(1).getId() == 1);
        assert(service.getProduct(1).getQuantity() == 11);
        assert(service.getProduct(1) != Product(1,"1", "p1", 1, 10));
        service.updateProduct(2, 19.99);
        assert(service.getProduct(2).getPrice() == 19.99);
        assert(service.getProduct(2).getId() == 2);
        assert(service.getProduct(2).getQuantity() == 11);
        assert(service.getProduct(2) != Product(2, "2", "p2", 2, 11));
        service.updateProduct(3, 20);
        assert(service.getProduct(3).getPrice() == 3);
        assert(service.getProduct(3).getId() == 3);
        assert(service.getProduct(3).getQuantity() == 20);
        assert(service.getProduct(3) != Product(3, "3","p3", 3, 12));
    }

    static void testServiceRemove(VendingMachineService &service) {
        service.removeProduct(1);
        assert(service.getSize() == 2);
        service.removeProduct(2);
        assert(service.getSize() == 1);
        service.removeProduct(3);
        assert(service.getSize() == 0);
    }

    static void testService() {
        FileRepository<Product> r("./test.txt");
        FileRepository<Coins> r2("./test2.txt");
        IRepo<Product>& repo = r;
        IRepo<Coins>& coinsRepo = r2;
        VendingMachineService s(repo, coinsRepo);
        testServiceAdd(s);
        testServiceGetAll(s);
        testServiceUpdate(s);
        testServiceRemove(s);
        remove("./test.txt");
    }

    static void testAll() {
        std::cout << "Running tests..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Tests::testProduct();
        Tests::testMemoryRepository();
        Tests::testFileRepository();
        Tests::testService();
        std::cout << "All tests passed!" << std::endl;
    }
};

#endif //LAB9_10_TESTS_H

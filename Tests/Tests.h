//
// Created by Antonio on 4/16/2022.
//
#include "../Domain/Product.h"
#include "../Repository/MemoryRepository.h"
#include <cassert>
#include <chrono>
#include <thread>

#ifndef LAB9_10_TESTS_H
#define LAB9_10_TESTS_H

class Tests {
public:
    static void testProduct() {
        Product p1(1, "p1", 1, 10);
        Product p2(2, "p2", 2, 11);
        Product p3(3, "p3", 3, 12);
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

    static void testRepository() {
        MemoryRepository<Product> r;
        IRepo<Product>& repo = r;
        Product p1(1, "p1", 1, 10);
        Product p2(2, "p2", 2, 11);
        Product p3(3, "p3", 3, 12);
        repo.add(p1);
        assert(repo.getSize() == 1);
        repo.add(p2);
        assert(repo.getSize() == 2);
        repo.add(p3);
        assert(repo.getSize() == 3);
        assert(repo.get(1) == p1);
        assert(repo.get(2) == p2);
        assert(repo.get(3) == p3);
        std::vector<Product> v = repo.getAll();
        assert(v[0] == p1);
        assert(v[1] == p2);
        assert(v[2] == p3);
        repo.remove(p1.getId());
        assert(repo.getSize() == 2);
        repo.remove(p2.getId());
        assert(repo.getSize() == 1);
        repo.remove(p3.getId());
        assert(repo.getSize() == 0);
    }

    static void testService() {

    }

    static void testAll() {
        std::cout << "Running tests..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Tests::testProduct();
        Tests::testRepository();
        Tests::testService();
        std::cout << "All tests passed!" << std::endl;
    }
};

#endif //LAB9_10_TESTS_H

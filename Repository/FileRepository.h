//
// Created by Antonio on 4/25/2022.
//
#include "./IRepo.h"
#include <string>
#include <fstream>

#ifndef LAB9_10_FILEREPOSITORY_H
#define LAB9_10_FILEREPOSITORY_H

template <class R>
class FileRepository : public IRepo<R> {
private:
    std::string filePath;
    std::vector<R> repo;
public:
    explicit FileRepository(std::string _filePath){
        this->filePath = _filePath;
        this->repo = this->readFromFile();
    };

    std::vector<R> readFromFile() {
        std::ifstream file(this->filePath);
        std::vector<R> _repo;
        R r;
        while (file >> r) {
            _repo.push_back(r);
        }
        return repo;
    }

    void writeToFile() {
        std::ofstream file(this->filePath);
        for (auto r : this->repo) {
            file << r << std::endl;
        }
    }

    ~FileRepository() {
        this->writeToFile();
    };

    void add(R r) {
        this->repo.push_back(r);
        this->writeToFile();
    };
    void remove(R r) {
        for(int i = 0; i < this->repo.size(); i++) {
            if(this->repo[i] == r) {
                this->repo.erase(this->repo.begin() + i);
                this->writeToFile();
                return;
            }
        }
    };
    void update(R r) {
        for(int i = 0; i < this->repo.size(); i++) {
            if(this->repo[i] == r) {
                this->repo[i] = r;
                this->writeToFile();
                return;
            }
        }
    };

    R get(int id) {
        for(int i = 0; i < this->repo.size(); i++) {
            if(this->repo[i].getId() == id) {
                return this->repo[i];
            }
        }
        return R();
    };

    std::vector<R> getAll() {
        return this->repo;
    };
    int getSize() {
        return this->repo.size();
    };
};

#endif //LAB9_10_FILEREPOSITORY_H

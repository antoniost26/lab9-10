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
        this->readFromFile();
    };

    void readFromFile() {
        std::string line;
        std::ifstream myFile(this->filePath);
        while (getline(myFile, line)) {
            R r(line);
            this->repo.push_back(r);
        }
    }

    void writeToFile() {
        std::ofstream myFile(this->filePath);
        for (auto r : this->repo) {
            myFile << r.toString() << std::endl;
        }
    }

    ~FileRepository() {
        this->writeToFile();
    };

    void add(R r) {
        this->repo.push_back(r);
        this->writeToFile();
    };
    void remove(int _id) {
        for(int i = 0; i < this->repo.size(); i++) {
            if(this->repo[i].getId() == _id) {
                this->repo.erase(this->repo.begin() + i);
                this->writeToFile();
                return;
            }
        }
        throw std::out_of_range("No element with id " + std::to_string(_id));
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
        throw std::out_of_range("No element with this id!");
    };

    std::vector<R> getAll() {
        return this->repo;
    };
    int getSize() {
        return this->repo.size();
    };
};

#endif //LAB9_10_FILEREPOSITORY_H

//
// Created by Antonio on 4/25/2022.
//
#include "./IRepo.h"
#include <string>
#include <fstream>

#ifndef LAB9_10_FILEREPOSITORY_H
#define LAB9_10_FILEREPOSITORY_H

template<class R>
class FileRepository : public IRepo<R> {
private:
    std::string filePath;

    std::vector<R> repo;
public:
    /**
     * Constructor
     * @param _filePath file path
     */
    explicit FileRepository(std::string _filePath) {
        this->filePath = _filePath;
        this->readFromFile();
    };

    /**
     * Reads entities from file
     */
    void readFromFile() {
        std::string line;
        std::ifstream myFile(this->filePath);
        while (getline(myFile, line)) {
            R r(line);
            this->repo.push_back(r);
        }
    }

    /**
     * Writes entities to file
     */
    void writeToFile() {
        std::ofstream myFile(this->filePath);
        for (auto r: this->repo) {
            myFile << r.toString() << std::endl;
        }
    }

    /**
     * Destructor
     */
    ~FileRepository() {
        this->writeToFile();
    };

    /**
     * Adds an entity to the repository
     * @param r an entity
     */
    void add(R r) override {
        this->repo.push_back(r);
        this->writeToFile();
    };

    /**
     * Removes an entity from the repository
     * @param _id entity id
     */
    void remove(int _id) override {
        for (int i = 0; i < this->repo.size(); i++) {
            if (this->repo[i] == _id) {
                this->repo.erase(this->repo.begin() + i);
                this->writeToFile();
                return;
            }
        }
        throw MyException((char *) ("No element with id " + std::to_string(_id)).c_str());
    };

    /**
     * Updates an entity in the repository
     * @param r an entity
     */
    void update(R r) override {
        for (int i = 0; i < this->repo.size(); i++) {
            if (this->repo[i].getId() == r.getId()) {
                this->repo[i] = r;
                this->writeToFile();
                return;
            }
        }
    };

    /**
     * Gets an entity from the repository
     * @param _id entity id
     * @return an entity
     */
    R get(int _id) override {
        for (int i = 0; i < this->repo.size(); i++) {
            if (this->repo[i].getId() == _id) {
                return this->repo[i];
            }
        }
        throw MyException((char *) ("No element with id " + std::to_string(_id)).c_str());
    };

    /**
     * Gets all entities from the repository
     * @return a vector with all entities
     */
    std::vector<R> getAll() override {
        return this->repo;
    };

    /**
     * Gets the size of the repository
     * @return the size of the repository
     */
    int getSize() override {
        return this->repo.size();
    };

    /**
     * Gets an entity from the repository by code.
     * @param _code entity's code
     * @return the entity, if found
     */
    R get(std::string _code) override {
        for (int i = 0; i < this->repo.size(); i++) {
            if (this->repo[i].getCode() == _code) {
                return this->repo[i];
            }
        }
        throw MyException(std::string("No element with code " + _code).c_str());
    }
};

#endif //LAB9_10_FILEREPOSITORY_H

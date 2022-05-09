//
// Created by Antonio on 5/9/2022.
//

#ifndef LAB9_10_MYEXCEPTION_H
#define LAB9_10_MYEXCEPTION_H


#include <exception>
#include <string>
#include <utility>

class MyException : std::exception {
public:
    explicit MyException(const char *message) : message(message), message_string(std::string()) {}
    explicit MyException(std::string message) : message_string(std::move(message)), message(nullptr) {}
    const char *what() const noexcept override {
        return message? message : message_string.c_str();
    }
private:
    const char *message{};
    const std::string message_string;
};


#endif //LAB9_10_MYEXCEPTION_H

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
    /**
     * Constructor
     * @param message exception message
     */
    explicit MyException(std::string message) : message(std::move(message)) {}

    /**
     * @return the message of the exception
     */
    const char *what() { return message.c_str(); }

private:
    std::string message;
};


#endif //LAB9_10_MYEXCEPTION_H

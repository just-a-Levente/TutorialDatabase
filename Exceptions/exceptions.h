//
// Created by lkovacs on 4/28/25.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class UnsignedIntNotFoundException : public std::exception {
    std::string message;

public:
    UnsignedIntNotFoundException(std::string _msg);
    const char* what() const noexcept override;
};


class InvalidDurationException : public std::exception {
    std::string message;

public:
    InvalidDurationException(std::string _msg);
    const char* what() const noexcept override;
};


class TutorialValidationException : public std::exception {
    std::string message;

public:
    TutorialValidationException(std::string _msg);
    const char* what() const noexcept override;
};


class TutorialWithSameLinkException : public std::exception {
    std::string message;

public:
    TutorialWithSameLinkException(std::string _msg);
    const char* what() const noexcept override;
};


class TutorialNotFoundException : public std::exception {
    std::string message;

public:
    TutorialNotFoundException(std::string _msg);
    const char* what() const noexcept override;
};


class UndoRedoException : public std::exception {
    std::string message;

public:
    UndoRedoException(std::string _msg);
    const char* what() const noexcept override;
};

#endif //EXCEPTIONS_H

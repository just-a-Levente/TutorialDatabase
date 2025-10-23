//
// Created by lkovacs on 4/28/25.
//

#include "exceptions.h"

#include <utility>

UnsignedIntNotFoundException::UnsignedIntNotFoundException(std::string _msg) : message{std::move(_msg)} {}

const char * UnsignedIntNotFoundException::what() const noexcept {
    return message.c_str();
}

InvalidDurationException::InvalidDurationException(std::string _msg) : message{std::move(_msg)} {}

const char * InvalidDurationException::what() const noexcept {
    return message.c_str();
}

TutorialValidationException::TutorialValidationException(std::string _msg) : message{std::move(_msg)} {}

const char * TutorialValidationException::what() const noexcept {
    return message.c_str();
}

TutorialWithSameLinkException::TutorialWithSameLinkException(std::string _msg) : message{std::move(_msg)} {}

const char * TutorialWithSameLinkException::what() const noexcept {
    return message.c_str();
}

TutorialNotFoundException::TutorialNotFoundException(std::string _msg) : message{std::move(_msg)} {}

const char * TutorialNotFoundException::what() const noexcept {
    return message.c_str();
}

UndoRedoException::UndoRedoException(std::string _msg) : message{std::move(_msg)} {}

const char * UndoRedoException::what() const noexcept {
    return message.c_str();
}
//
// Created by lkovacs on 4/29/25.
//

#include "TutorialValidator.h"
#include "../Exceptions/exceptions.h"
#include <stdexcept>

void TutorialValidator::validateDataPoints(const vector<string>& inputDataPoints) {

    if (inputDataPoints.size() < 5)
        throw TutorialValidationException("Not enough data points to construct a Tutorial entity!\n");

    string errors;
    // Checking whether any provided data point is empty
    int i = 0;
    for (const string& dataPoint : inputDataPoints) {
        if (dataPoint.empty()) {
            errors += string("The ");
            errors += std::to_string(i+1);
            errors += string(". data point is empty!\n");
        }
        ++i;
    }

    // Checking minutes (characters are digits)
    try {

        int duration_minutes = std::stoi(inputDataPoints[3]);
        if (duration_minutes < 0)
            errors += string("The number of minutes must be positive!\n");

    } catch (std::invalid_argument const& excep) {
        errors += string("The number of minutes must be a positive base-10 integer!\n");
    } catch (std::out_of_range const& excep) {
        errors += string("The number of minutes is too large to store!\n");
    }

    // Checking seconds (characters are digits and the number is less than 60)
    try {

        int duration_seconds = std::stoi(inputDataPoints[4]);
        if (duration_seconds < 0 || duration_seconds >= 60)
            errors += string("The number of seconds must be between 0 and 59!\n");

    } catch (std::invalid_argument const& excep) {
        errors += string("The number of seconds must be a positive base-10 integer!\n");
    } catch (std::out_of_range const& excep) {
        errors += string("The number of seconds is too large to store!\n");
    }

    // Checking number of likes, if provided (characters are digits)
    if (inputDataPoints.size() == 6) {
        try {

            int number_of_likes = std::stoi(inputDataPoints[5]);
            if (number_of_likes < 0)
                errors += string("The number of likes must be positive!\n");

        } catch (std::invalid_argument const& excep) {
            errors += string("The number of likes must be a positive base-10 integer!\n");
        } catch (std::out_of_range const& excep) {
            errors += string("The number of likes is too large to store!\n");
        }
    }

    if (!errors.empty())
        throw TutorialValidationException(errors);
}

void TutorialValidator::validateDuration(const vector<string> &inputDuration) {
    string errors;
    // Checking minutes (characters are digits)
    try {

        int duration_minutes = std::stoi(inputDuration[0]);
        if (duration_minutes < 0)
            errors += string("The number of minutes must be positive!\n");

    } catch (std::invalid_argument const& excep) {
        errors += string("The number of minutes must be a positive base-10 integer!\n");
    } catch (std::out_of_range const& excep) {
        errors += string("The number of minutes is too large to store!\n");
    }

    // Checking seconds (characters are digits and the number is less than 60)
    try {

        int duration_seconds = std::stoi(inputDuration[1]);
        if (duration_seconds < 0 || duration_seconds >= 60)
            errors += string("The number of seconds must be between 0 and 59!\n");

    } catch (std::invalid_argument const& excep) {
        errors += string("The number of seconds must be a positive base-10 integer!\n");
    } catch (std::out_of_range const& excep) {
        errors += string("The number of seconds is too large to store!\n");
    }

    if (!errors.empty())
        throw InvalidDurationException(errors);
}

void TutorialValidator::validateUnsignedInt(const string &inputNumber) {
    string errors;
    try {
        unsigned int number_of_likes = std::stoull(inputNumber);
    } catch (std::invalid_argument const& excep) {
        errors += "The string must be a positive base-10 integer!\n";
    } catch (std::out_of_range const& excep) {
        errors += "The integer is too large to store\n";
    }

    if (!errors.empty())
        throw UnsignedIntNotFoundException(errors);
}

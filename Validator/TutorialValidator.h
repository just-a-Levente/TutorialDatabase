//
// Created by lkovacs on 4/29/25.
//

#ifndef TUTORIALVALIDATOR_H
#define TUTORIALVALIDATOR_H

#include <string>
#include <vector>

using std::vector, std::string;

class TutorialValidator {
public:
    static void validateDataPoints(const vector<string>& inputDataPoints);

    static void validateDuration(const vector<string>& inputDuration);

    static void validateUnsignedInt(const string& inputNumber);
};

#endif //TUTORIALVALIDATOR_H

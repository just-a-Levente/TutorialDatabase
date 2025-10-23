//
// Created by lkovacs on 3/25/25.
//

#include "repository.h"
#include <algorithm>
#include <fstream>
#include "../Exceptions/exceptions.h"

void Repository::saveTutorials() const {
    std::ofstream output_file(this->fileName);
    for (const auto &tutorial: this->tutorials) {
        output_file << tutorial;
    }
}

void Repository::loadTutorials() {
    std::ifstream input_file(this->fileName);
    Tutorial lineTutorial;
    try {
        while (input_file >> lineTutorial) {
            this->tutorials.push_back(lineTutorial);
        }
    } catch (std::invalid_argument const& excep) {
        std::cout << "Data points read in\n\n";
    }
}

Repository::Repository(const string &inputFileName) : fileName(inputFileName) { this->Repository::loadTutorials(); }

unsigned int Repository::getNumberOfTutorials() const { return this->tutorials.size(); }

vector<Tutorial> &Repository::getVector() { return this->tutorials; }

void Repository::addTutorial(const Tutorial &new_tutorial) {
    for (const auto &iter_tutorial: this->tutorials) {
        if (iter_tutorial == new_tutorial) {
            throw TutorialWithSameLinkException("Tutorial with same link already exists!\n");
        }
    }
    this->tutorials.push_back(new_tutorial);
    this->saveTutorials();
}

void Repository::removeTutorial(const Tutorial &tutorial_remove) {
    const string tutorial_link_remove = tutorial_remove.getLink();
    auto nr_of_erased_elements = std::erase_if(this->tutorials, [tutorial_link_remove](const Tutorial &iter_tutorial) {
        return iter_tutorial.getLink() == tutorial_link_remove;
    });
    if (nr_of_erased_elements < 1)
        throw TutorialNotFoundException("No tutorial with the given link was found!\n");
    this->saveTutorials();
}

void Repository::updateTutorial(const Tutorial &updated_tutorial) {
    int i = 0;
    for (const auto &iter_tutorial: this->tutorials) {
        if (iter_tutorial == updated_tutorial) {
            this->tutorials[i] = updated_tutorial;
            this->saveTutorials();
            return;
        }
        ++i;
    }
    throw TutorialNotFoundException("No tutorial with the given link was found!\n");
}

Tutorial Repository::findTutorial(const string &tutorial_link_find) {
    const auto search_result = std::find_if(this->tutorials.begin(), this->tutorials.end(),
                                            [tutorial_link_find](const Tutorial &iter_tutorial) {
                                                return iter_tutorial.getLink() == tutorial_link_find;
                                            });
    if (search_result == this->tutorials.end())
        throw TutorialNotFoundException("No tutorial with the given link was found!\n");
    return *search_result;
}


SQLRepository::SQLRepository(const string &inputFileName) : Repository(inputFileName) {
    while (!this->tutorials.empty())
        this->tutorials.erase(this->tutorials.begin());

    this->SQLRepository::loadTutorials();
}

void SQLRepository::saveTutorials() const {

}

void SQLRepository::loadTutorials() {

}

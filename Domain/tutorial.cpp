//
// Created by lkovacs on 3/24/25.
//

#include "tutorial.h"

#include <utility>
#include <sstream>

Tutorial::Tutorial() : likes(0) {}

Tutorial::Tutorial(string link, string title, string presenter, const t_duration &duration, const unsigned int likes) {
    this->link = std::move(link);
    this->title = std::move(title);
    this->presenter = std::move(presenter);
    this->duration = duration;
    this->likes = likes;
}

Tutorial::Tutorial(const Tutorial &copy) {
    this->link = copy.link;
    this->title = copy.title;
    this->presenter = copy.presenter;
    this->duration = copy.duration;
    this->likes = copy.likes;
}

Tutorial &Tutorial::operator=(const Tutorial &copy) {
    if (this == &copy) return *this;
    this->link = copy.link;
    this->title = copy.title;
    this->presenter = copy.presenter;
    this->duration = copy.duration;
    this->likes = copy.likes;
    return *this;
}

Tutorial::~Tutorial() = default;

string Tutorial::getLink() const { return this->link; }

string Tutorial::getTitle() const {
    return this->title;
}

string Tutorial::getPresenter() const {
    return this->presenter;
}

t_duration Tutorial::getDuration() const {
    return this->duration;
}

unsigned int Tutorial::getLikes() const {
    return this->likes;
}

void Tutorial::setTitle(string new_title) {
    this->title = std::move(new_title);
}

void Tutorial::setPresenter(string new_presenter) {
    this->presenter = std::move(new_presenter);
}

void Tutorial::setDuration(const t_duration &new_duration) {
    this->duration = new_duration;
}

void Tutorial::setLikes(const unsigned int new_amount_of_likes) {
    this->likes = new_amount_of_likes;
}

string Tutorial::toString() const {
    std::stringstream representation;
    representation << this->getLink() << " - ";
    representation << this->getTitle() << " - ";
    representation << this->getPresenter() << " - ";
    representation << this->getDuration().first << ":";
    if (this->getDuration().second < 10)
        representation << "0";
    representation << this->getDuration().second << " - ";
    representation << this->getLikes() << " likes";
    return representation.str();
}

std::istream & operator>>(std::istream &input_stream, Tutorial &input_tutorial) {
    string line;
    getline(input_stream, line);

    std::stringstream sstr(line);
    string new_link, new_title, new_presenter, new_duration_min, new_duration_sec, new_likes_str;
    getline(sstr, new_link, ',');
    getline(sstr, new_title, ',');
    getline(sstr, new_presenter, ',');
    getline(sstr, new_duration_min, ':');
    getline(sstr, new_duration_sec, ',');
    getline(sstr, new_likes_str, '\n');
    t_duration new_duration;
    new_duration.first = std::stoi(new_duration_min);
    new_duration.second = std::stoi(new_duration_sec);
    const unsigned int new_likes = std::stoi(new_likes_str);

    input_tutorial.link = new_link;
    input_tutorial.title = new_title;
    input_tutorial.presenter = new_presenter;
    input_tutorial.duration = new_duration;
    input_tutorial.likes = new_likes;

    return input_stream;
}

std::ostream & operator<<(std::ostream &output_stream, const Tutorial &output_tutorial) {
    output_stream << output_tutorial.getLink() << ","
                << output_tutorial.getTitle() << ","
                << output_tutorial.getPresenter() << ","
                << output_tutorial.getDuration().first << ":" << output_tutorial.getDuration().second << ","
                << output_tutorial.getLikes() << std::endl;
    return output_stream;
}


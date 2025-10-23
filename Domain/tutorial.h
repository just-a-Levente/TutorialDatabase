//
// Created by lkovacs on 3/24/25.
//

#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <utility>
#include <iostream>
#include <string>

typedef std::pair<unsigned int, unsigned int> t_duration;
using std::string;

/** Class containing information and functionalities related to managing tutorials */
class Tutorial {

    string link;
    string title;
    string presenter;
    t_duration duration;
    unsigned int likes;

public:
    /**
     * Default constructor
     */
    Tutorial();

    /**
     * Constructor, initializing the object's fields
     * @param link The link of the website containing the tutorial
     * @param title The title of the tutorial
     * @param presenter The presenter of the tutorial
     * @param duration Minutes and seconds of the tutorial
     * @param likes The number of likes of the tutorial
     */
    Tutorial(string link, string title, string presenter, const t_duration &duration, unsigned int likes = 0);

    /**
     * Copy constructor
     * @param copy The Tutorial object to be copied
     */
    Tutorial(const Tutorial &copy);

    /**
     * Copy assignment operator
     * @param copy The Tutorial object from which we take the values
     * @return Reference to the caller Tutorial, with the updated values
     */
    Tutorial &operator=(const Tutorial &copy);

    /**
     * Default destructor
     */
    ~Tutorial();

    /**
     * Getter for the Tutorial's link
     * @return link
     */
    [[nodiscard]] string getLink() const;

    /**
     * Getter for the Tutorial's title
     * @return title
     */
    [[nodiscard]] string getTitle() const;

    /**
     * Getter for the Tutorial's presenter
     * @return presenter
     */
    [[nodiscard]] string getPresenter() const;

    /**
     * Getter for the Tutorial's duration
     * @return duration
     */
    [[nodiscard]] t_duration getDuration() const;

    /**
     * Getter for the Tutorial's number of likes
     * @return likes
     */
    [[nodiscard]] unsigned int getLikes() const;

    /**
     * Setter for the Tutorial's title
     * @param new_title The new updated title
     */
    void setTitle(string new_title);

    /**
     * Setter for the Tutorial's presenter
     * @param new_presenter The new updated presenter
     */
    void setPresenter(string new_presenter);

    /**
     * Setter for the Tutorial's duration
     * @param new_duration The new updated duration
     */
    void setDuration(const t_duration &new_duration);

    /**
     * Setter for the Tutorial's number of likes
     * @param new_amount_of_likes The new updated amount of likes
     */
    void setLikes(unsigned int new_amount_of_likes);

    /**
     * Constructs a Tutorial's string representation for output
     * @return String containing the Tutorial's fields
     */
    [[nodiscard]] string toString() const;

    friend std::istream &operator>>(std::istream &input_stream, Tutorial &input_tutorial);
    friend std::ostream &operator<<(std::ostream &output_stream, const Tutorial &output_tutorial);
};

/**
 * Checks the equality of two Tutorial objects
 * @param left Tutorial on the left of the operator
 * @param right Tutorial on the right of the operator
 * @return true, if the links are equal, false otherwise
 */
inline bool operator==(const Tutorial &left, const Tutorial &right) {
    if (left.getLink() == right.getLink()) return true;
    return false;
}

#endif //TUTORIAL_H

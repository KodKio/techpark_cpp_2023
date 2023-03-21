#ifndef PROJECT_INCLUDE_FILM_H_
#define PROJECT_INCLUDE_FILM_H_

#include <string>
#include <iostream>

struct film_t {
    std::string id;
    float rate;
    std::string name;

    film_t(std::string_view id, float rate, std::string_view name);

    friend std::ostream& operator<<(std::ostream& out, const film_t& f);
};

#endif  // PROJECT_INCLUDE_FILM_H_

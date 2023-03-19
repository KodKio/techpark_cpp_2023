#include "Top.h"
#include <algorithm>

Top::Top(std::vector<Film> &_films) : films(_films) {
    std::ranges::sort(films, std::ranges::greater(), &Film::rate);
}

std::vector<Film> Top::getTop() {
    return films;
}

Top::Top(std::vector<Film> &&_films) : films(std::move(_films)) {
    std::ranges::sort(films, std::ranges::greater(), &Film::rate);
}

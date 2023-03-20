#include "Top.h"
#include <algorithm>
#include <ranges>

Top::Top(const std::vector<Film> &_films)
    : films(_films) {
    std::ranges::sort(films, std::ranges::greater(), &Film::rate);
    auto tmp = films | std::views::take(10);
    films = std::vector<Film>(tmp.begin(), tmp.end());
}

std::vector<Film> Top::getTop() {
    return films;
}

Top::Top(std::vector<Film> &&_films)
    : films(std::move(_films)) {
    std::ranges::sort(films, std::ranges::greater(), &Film::rate);
    auto tmp = films | std::views::take(10);
    films = std::vector<Film>(tmp.begin(), tmp.end());
}

#include "Top.h"

#include <ranges>
#include <algorithm>

Top::Top(const std::vector<film_t> &_films, int _top_size)
    : films(_films),
      top_size(_top_size) {
    generateTop();
}

Top::Top(std::vector<film_t> &&_films, int _top_size)
        : films(std::move(_films)),
          top_size(_top_size) {
    generateTop();
}

std::vector<film_t> Top::getTop() {
    return films;
}

void Top::generateTop() {
    std::ranges::sort(films, std::ranges::greater(), &film_t::rate);
    auto tmp = films | std::views::take(top_size);
    films = std::vector<film_t>(tmp.begin(), tmp.end());
}

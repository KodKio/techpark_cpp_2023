#include "Film.h"

film_t::film_t(std::string_view id, float rate, std::string_view name)
    : id(id),
      rate(rate),
      name(name) {}

std::ostream &operator<<(std::ostream &out, const film_t &f) {
    out << f.name << " " << f.rate;
    return out;
}


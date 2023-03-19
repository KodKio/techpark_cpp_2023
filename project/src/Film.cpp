#include "Film.h"

Film::Film(std::string_view id, float rate, std::string_view name)
    : id(id),
      rate(rate),
      name(name) {}

std::ostream &operator<<(std::ostream &out, const Film &f) {
    out << f.name << " " << f.rate;
    return out;
}


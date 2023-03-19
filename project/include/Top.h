#ifndef PROJECT_INCLUDE_TOP_H_
#define PROJECT_INCLUDE_TOP_H_

#include <vector>
#include "Film.h"

class Top {
 public:
    Top(std::vector<Film>& _films);
    Top(std::vector<Film>&& _films);
    std::vector<Film> getTop();
 private:
    std::vector<Film> films;
};

#endif  // PROJECT_INCLUDE_TOP_H_

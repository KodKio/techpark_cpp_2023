#ifndef PROJECT_INCLUDE_TOP_H_
#define PROJECT_INCLUDE_TOP_H_

#include <vector>
#include <string>

#include "Film.h"

class Top {
 public:
    Top(const std::string& year, const std::string& akas_filename, const std::string& basics_filename,
        const std::string& ratings_filename);

    int createTop();
    std::vector<Film> getTop();
 private:
    std::string year;
    std::string akas_filename;
    std::string basics_filename;
    std::string ratings_filename;
    std::vector<Film> films;
    int getFilmsInfo();
    int getFilmsRates();
    int getRuNames();
    int getFilms();
};

#endif  // PROJECT_INCLUDE_TOP_H_

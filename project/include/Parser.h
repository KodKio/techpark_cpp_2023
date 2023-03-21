#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <vector>
#include <string>
#include <unordered_map>

#include "Film.h"

#define EMPTY (-1)

class Parser {
 public:
    int parse(std::istream &basics, std::istream &ratings, std::istream &akas, std::string_view year);
    std::vector<film_t> getResult();

 private:
    struct info_t {
        std::string id;
        std::string type;
        std::string title;
        std::string originalTitle;
        std::string isAdult;
        std::string startYear;
    };

    struct rate_t {
        std::string id;
        float rate = EMPTY;
        int numVotes = EMPTY;
    };

    struct translation_t {
        std::string id;
        std::string newTitle;
        std::string region;
        std::string ordering;
    };

    friend std::istream& operator>>(std::istream& in, info_t& i);
    friend std::istream& operator>>(std::istream& in, rate_t& r);
    friend std::istream& operator>>(std::istream& in, translation_t& t);

    std::unordered_map<std::string, film_t> films;
    int getFilmsInfo(std::istream &basics, std::string_view year);
    int getFilmsRates(std::istream &ratings);
    int getRuNames(std::istream &akas);
};

#endif  // PROJECT_INCLUDE_PARSER_H_

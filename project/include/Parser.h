#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <vector>
#include <string>

#include "Film.h"

#define INIT_RATE (-1)
#define INIT_NUMVOTES (-1)

class Parser {
 public:
    Parser(std::string year, std::istream& akasStream, std::istream& basicsStream,
        std::istream& ratingsStream);

    int parse();
    std::vector<Film> getResult();
 private:

    struct Info {
        std::string id;
        std::string type;
        std::string title;
        std::string originalTitle;
        std::string isAdult;
        std::string startYear;
    };

    struct Rate {
        std::string id;
        float rate = INIT_RATE;
        int numVotes = INIT_NUMVOTES;
    };

    struct Translation {
        std::string id;
        std::string newTitle;
        std::string region;
        std::string ordering;
    };

    friend std::istream& operator>>(std::istream& in, Info& i);
    friend std::istream& operator>>(std::istream& in, Rate& r);
    friend std::istream& operator>>(std::istream& in, Translation& t);

    std::string year;
    std::istream akas;
    std::istream basics;
    std::istream ratings;
    std::vector<Film> films;
    int getFilmsInfo();
    int getFilmsRates();
    int getRuNames();
    int getFilms();
};

#endif  // PROJECT_INCLUDE_PARSER_H_

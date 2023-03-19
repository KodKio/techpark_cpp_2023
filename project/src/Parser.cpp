#include "Parser.h"

#include <ranges>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>

#define SEARCH_TYPE "movie"
#define SEARCH_REGION "RU"
#define IS_ADULT "0"

Parser::Parser(std::string year, std::istream& akasStream, std::istream& basicsStream,
         std::istream& ratingsStream)
        : year(std::move(year)),
          akas(nullptr),
          basics(nullptr),
          ratings(nullptr) {
    akas.rdbuf(akasStream.rdbuf());
    basics.rdbuf(basicsStream.rdbuf());
    ratings.rdbuf(ratingsStream.rdbuf());
}

int Parser::parse() {
    if (getFilms()) {
        return 1;
    }
    return 0;
}

std::vector<Film> Parser::getResult() {
    return films;
}

int Parser::getFilmsInfo() {
    std::string line;
    bool flag = false;

    while (std::getline(basics, line)) {
        std::istringstream ss(line);
        Info tmp;
        ss >> tmp;

        if ((tmp.isAdult.empty() || tmp.startYear.empty() || tmp.type.empty()) && flag) {
            return 1;
        }
        if (tmp.type == SEARCH_TYPE && tmp.startYear == year && tmp.isAdult == IS_ADULT) {
            films.emplace_back(tmp.id, -1, tmp.title);
        }

        flag = true;
    }
    return 0;
}

int Parser::getFilmsRates() {
    std::string line;
    int i = 0;
    bool flag = false;

    while (std::getline(ratings, line)) {
        Rate tmp;
        std::istringstream ss(line);
        ss >> tmp;

        if ((tmp.rate == INIT_RATE || tmp.numVotes == INIT_NUMVOTES) && flag) {
            return 1;
        }
        if (tmp.id == films[i].id) {
            if (tmp.numVotes >= 1000)
                films[i].rate = tmp.rate;
            i++;
        }

        flag = true;
    }
    std::erase_if(films, [](auto film) { return film.rate == INIT_RATE;});
    return 0;
}

int Parser::getRuNames() {
    std::string line;
    int i = 0;
    bool flag = false;

    while (std::getline(akas, line)) {
        Translation tmp;
        std::istringstream ss(line);
        ss >> tmp;

        if ((tmp.region.empty() || tmp.id.empty() || tmp.newTitle.empty()) && flag) {
            return 1;
        }
        if (tmp.id > films[i].id && i + 1 < (int)films.size() && flag) {
            i++;
        }
        if (tmp.id == films[i].id) {
            if (tmp.region == SEARCH_REGION) {
                films[i].name = tmp.newTitle;
                i++;
            }
        }

        flag = true;
    }
    return 0;
}

int Parser::getFilms() {
    if (getFilmsInfo()) {
        return 1;
    }
    if (getFilmsRates()) {
        return 1;
    }
    if (getRuNames()) {
        return 1;
    }
    return 0;
}

std::istream &operator>>(std::istream &in, Parser::Info &i) {
    std::getline(in, i.id, '\t');
    std::getline(in, i.type, '\t');
    std::getline(in, i.title, '\t');
    std::getline(in, i.originalTitle, '\t');
    std::getline(in, i.isAdult, '\t');
    std::getline(in, i.startYear, '\t');
    return in;
}

std::istream &operator>>(std::istream &in, Parser::Rate &r) {
    std::getline(in, r.id, '\t');
    in >> r.rate >> r.numVotes;
    return in;
}

std::istream &operator>>(std::istream &in, Parser::Translation &t) {
    std::getline(in, t.id, '\t');
    std::getline(in, t.ordering, '\t');
    std::getline(in, t.newTitle, '\t');
    std::getline(in, t.region, '\t');
    return in;
}

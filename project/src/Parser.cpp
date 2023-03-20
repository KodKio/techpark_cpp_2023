#include "Parser.h"

#include <ranges>
#include <sstream>
#include <algorithm>

#define SEARCH_TYPE "movie"
#define SEARCH_REGION "RU"
#define IS_ADULT "0"

int Parser::parse(std::istream &basics, std::istream &ratings, std::istream &akas, std::string_view year) {
    if (getFilmsInfo(basics, year)) {
        return 1;
    }
    if (getFilmsRates(ratings)) {
        return 1;
    }
    if (getRuNames(akas)) {
        return 1;
    }
    return 0;
}

std::vector<Film> Parser::getResult() {
    std::vector<Film> res;
    res.reserve(films.size());
    for (auto& [_, film] : films) {
        res.emplace_back(film);
    }
    return res;
}

int Parser::getFilmsInfo(std::istream &basics, std::string_view year) {
    std::string line;
    bool isData = false;
    while (std::getline(basics, line)) {
        std::istringstream ss(line);
        info_t tmp;
        ss >> tmp;
        if ((tmp.isAdult.empty() || tmp.startYear.empty() || tmp.type.empty()) && isData) {
            return 1;
        }
        if (tmp.type == SEARCH_TYPE && tmp.startYear == year && tmp.isAdult == IS_ADULT) {
            films.emplace(tmp.id, Film(tmp.id, -1, tmp.title));
        }
        isData = true;
    }
    if (!isData) {
        return 1;
    }
    return 0;
}

int Parser::getFilmsRates(std::istream &ratings) {
    std::string line;
    bool isData = false;
    while (std::getline(ratings, line)) {
        rate_t tmp;
        std::istringstream ss(line);
        ss >> tmp;

        if ((tmp.rate == EMPTY || tmp.numVotes == EMPTY) && isData) {
            return 1;
        }
        if (films.find(tmp.id) != films.end() && tmp.numVotes >= 1000) {
            films.at(tmp.id).rate = tmp.rate;
        }
        isData = true;
    }
    std::erase_if(films, [](const auto& item) { return item.second.rate == EMPTY; });
    return 0;
}

int Parser::getRuNames(std::istream &akas) {
    std::string line;
    bool isData = false;
    while (std::getline(akas, line)) {
        translation_t tmp;
        std::istringstream ss(line);
        ss >> tmp;

        if ((tmp.region.empty() || tmp.id.empty() || tmp.newTitle.empty()) && isData) {
            return 1;
        }
        if (films.find(tmp.id) != films.end() && tmp.region == SEARCH_REGION) {
            films.at(tmp.id).name = tmp.newTitle;
        }
        isData = true;
    }
    return 0;
}

std::istream &operator>>(std::istream &in, Parser::info_t &i) {
    std::getline(in, i.id, '\t');
    std::getline(in, i.type, '\t');
    std::getline(in, i.title, '\t');
    std::getline(in, i.originalTitle, '\t');
    std::getline(in, i.isAdult, '\t');
    std::getline(in, i.startYear, '\t');
    return in;
}

std::istream &operator>>(std::istream &in, Parser::rate_t &r) {
    std::getline(in, r.id, '\t');
    in >> r.rate >> r.numVotes;
    return in;
}

std::istream &operator>>(std::istream &in, Parser::translation_t &t) {
    std::getline(in, t.id, '\t');
    std::getline(in, t.ordering, '\t');
    std::getline(in, t.newTitle, '\t');
    std::getline(in, t.region, '\t');
    return in;
}

#include "Top.h"

#include <ranges>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

Top::Top(const std::string& year, const std::string& akas_filename, const std::string& basics_filename,
         const std::string& ratings_filename)
         : year(year), akas_filename(akas_filename), basics_filename(basics_filename),
           ratings_filename(ratings_filename) {}

int Top::createTop() {
    if (getFilms()) {
        return 1;
    }
    std::ranges::sort(films, std::ranges::greater(), &Film::rate);
    return 0;
}

std::vector<Film> Top::getTop() {
    return films;
}

int Top::getFilmsInfo() {
    std::ifstream basics(basics_filename);
    if (!basics.is_open()) {
        return 1;
    }
    try {
        std::string line;
        while (std::getline(basics, line)) {
            std::string id, type, title, originalTitle, startYear, isAdult;
            std::istringstream ss(line);
            ss >> id >> std::ws >> type >> std::ws;
            std::getline(ss, title, '\t');
            std::getline(ss, originalTitle, '\t');
            ss >> isAdult >> std::ws >> startYear >> std::ws;
            if (type == "movie" && startYear == year && isAdult == "0") {
                films.emplace_back(id, -1, title);
            }
        }
    } catch (...) {
        return 1;
    }
    return 0;
}

int Top::getFilmsRates() {
    std::ifstream ratings(ratings_filename);
    if (!ratings.is_open()) {
        return 1;
    }
    try {
        std::string line;
        int i = 0;
        while (std::getline(ratings, line)) {
            std::string id;
            float rate;
            int numVotes;
            std::istringstream ss(line);
            ss >> id >> std::ws >> rate >> numVotes;
            if (id == films[i].id) {
                if (numVotes >= 1000)
                    films[i].rate = rate;
                i++;
            }
        }
        std::erase_if(films, [](auto film) { return film.rate == -1;});
    } catch(...) {
        return 1;
    }
    return 0;
}

int Top::getRuNames() {
    std::ifstream akas(akas_filename);
    if (!akas.is_open()) {
        return 1;
    }
    try {
        std::string line;
        int i = 0;
        while (std::getline(akas, line)) {
            std::string id, title, region;
            int ordering;
            std::istringstream ss(line);
            ss >> id >> std::ws >> ordering >> std::ws;
            std::getline(ss, title, '\t');
            ss >> region;
            if (id > films[i].id && i + 1 < films.size())
                i++;
            if (id == films[i].id) {
                if (region == "RU") {
                    films[i].name = title;
                    i++;
                }
            }
        }
    } catch (...) {
        return 1;
    }
    return 0;
}

int Top::getFilms() {
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

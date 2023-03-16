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
    std::string line;
    bool flag = false;
    while (std::getline(basics, line)) {
        std::string id, type, title, originalTitle, startYear, isAdult;
        std::istringstream ss(line);
        std::getline(ss, id, '\t');
        std::getline(ss, type, '\t');
        std::getline(ss, title, '\t');
        std::getline(ss, originalTitle, '\t');
        std::getline(ss, isAdult, '\t');
        std::getline(ss, startYear, '\t');
        if ((isAdult.empty() || startYear.empty() || type.empty()) && flag)
            return 1;
        if (type == "movie" && startYear == year && isAdult == "0") {
            films.emplace_back(id, -1, title);
        }
        flag = true;
    }
    return 0;
}

int Top::getFilmsRates() {
    std::ifstream ratings(ratings_filename);
    if (!ratings.is_open()) {
        return 1;
    }
    std::string line;
    int i = 0;
    bool flag = false;
    while (std::getline(ratings, line)) {
        std::string id;
        float rate = -1;
        int numVotes = -1;
        std::istringstream ss(line);
        std::getline(ss, id, '\t');
        ss >> rate >> numVotes;
        if ((rate == -1 || numVotes == -1) && flag)
            return 1;
        if (id == films[i].id) {
            if (numVotes >= 1000)
                films[i].rate = rate;
            i++;
        }
        flag = true;
    }
    std::erase_if(films, [](auto film) { return film.rate == -1;});
    return 0;
}

int Top::getRuNames() {
    std::ifstream akas(akas_filename);
    if (!akas.is_open()) {
        return 1;
    }
    std::string line;
    int i = 0;
    bool flag = false;
    while (std::getline(akas, line)) {
        std::string id, title, region;
        int ordering;
        std::istringstream ss(line);
        std::getline(ss, id, '\t');
        ss >> ordering >> std::ws;
        std::getline(ss, title, '\t');
        std::getline(ss, region, '\t');
        if ((region.empty() || id.empty() || title.empty()) && flag)
            return 1;
        if (id > films[i].id && i + 1 < films.size())
            i++;
        if (id == films[i].id) {
            if (region == "RU") {
                films[i].name = title;
                i++;
            }
        }
        flag = true;
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

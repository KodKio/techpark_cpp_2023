#include <iostream>
#include <string>
#include "Top.h"

void printUsage() {
    std::cerr << "Something went wrong!" << std::endl;
    std::cout << "Usage: ./films_top --year (YYYY) --title-akas-path path/to/title.akas.tsv --title-basics-path "
                 "path/to/title.basics.tsv --title-ratings-path path/to/title.ratings.tsv" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 9) {
        printUsage();
        return 1;
    }

    std::string year = "";
    std::string akas_filename = "";
    std::string basics_filename = "";
    std::string ratings_filename = "";

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--title-akas-path") {
            akas_filename = std::string(argv[i + 1]);
            i++;
        } else if (std::string(argv[i]) == "--title-basics-path") {
            basics_filename = std::string(argv[i + 1]);
            i++;
        } else if (std::string(argv[i]) == "--title-ratings-path") {
            ratings_filename = std::string(argv[i + 1]);
            i++;
        } else if (std::string(argv[i]) == "--year") {
            year = std::string(argv[i + 1]);
            i++;
        } else {
            printUsage();
            return 1;
        }
    }

    Top top(year, akas_filename, basics_filename, ratings_filename);
    if (top.getTop()) {
        std::cerr << "Wrong file format" << std::endl;
        return 1;
    }

    return 0;
}

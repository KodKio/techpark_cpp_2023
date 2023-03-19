#include <getopt.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Top.h"
#include "Parser.h"

void printUsage() {
    std::cerr << "Something went wrong!" << std::endl;
    std::cout << "Usage: ./films_top --year (YYYY) --title-akas-path path/to/title.akas.tsv "
                 "--title-basics-path path/to/title.basics.tsv "
                 "--title-ratings-path path/to/title.ratings.tsv" << std::endl;
}

int run(int argc, char* argv[]) {
    if (argc != 9) {
        printUsage();
        return 1;
    }

    std::string year;
    std::string akas_filename;
    std::string basics_filename;
    std::string ratings_filename;

    static struct option long_options[] = {
            {"title-basics-path", 1, nullptr, 'b'},
            {"title-akas-path", 1, nullptr, 'a'},
            {"title-ratings-path", 1, nullptr, 'r'},
            {"year", 1, nullptr, 'y'},
            {nullptr,0,nullptr,0}
    };

    int ch;

    while ((ch = getopt_long(argc, argv, "b:a:r:y:", long_options, nullptr)) != -1) {
        if (ch == 'b')
            basics_filename = optarg;
        else if (ch == 'a')
            akas_filename = optarg;
        else if (ch == 'r')
            ratings_filename = optarg;
        else if (ch == 'y')
            year = optarg;
        else {
            printUsage();
            return 1;
        }
    }

    std::ifstream akas(akas_filename);
    std::ifstream basics(basics_filename);
    std::ifstream ratings(ratings_filename);
    if (!akas.is_open() || !basics.is_open() ||!ratings.is_open()) {
        std::cerr << "Wrong file paths" << std::endl;
        return 1;
    }

    Parser parser(year, akas, basics, ratings);
    if (parser.parse()) {
        std::cerr << "Wrong file format" << std::endl;
        return 1;
    }

    auto res = Top(parser.getResult()).getTop();
    for (const auto& i : res) {
        std::cout << i << "\n";
    }

    return 0;
}

int main(int argc, char* argv[]) {
    return run(argc, argv);
}

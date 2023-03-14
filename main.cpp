#include <iostream>
#include <string>
#include "Top.h"

void run(int argc, char* argv[]) {
    std::string year = argv[1];
    std::string akas_filename(argv[2]);
    std::string basics_filename(argv[3]);
    std::string ratings_filename(argv[4]);
    Top top(year, akas_filename, basics_filename, ratings_filename);
    top.getTop();
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "Usage: ./films_top year(YYYY) path/to/title.akas.tsv path/to/title.basics.tsv"
                     "path/to/title.ratings.tsv";
        return 1;
    }
    run(argc, argv);
    return 0;
}

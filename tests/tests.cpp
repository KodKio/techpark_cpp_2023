#include <gtest/gtest.h>
#include <vector>
#include <sstream>

#include "Film.h"
#include "Top.h"
#include "Parser.h"

void genStrings(std::string& basicsStr, std::string& akasStr, std::string& ratingsStr, std::string& fail) {

    basicsStr = "tconst\ttitleType\tprimaryTitle\toriginalTitle\tisAdult\tstartYear\tendYear\truntimeMinutes\tgenres\n"
              "tt0000000\tshort\tLe clown et ses chiens\tLe clown et ses chiens\t0\t1892\t\\N\t5\tAnimation,Short\n"
              "tt0000001\tmovie\tStar Wars\tFilm1 a\t0\t2005\t\\N\t10\t1\n"
              "tt0000002\tmovie\tMarvel's film\tMarvel\t0\t2004\t\\N\t11\t1\n"
              "tt0000003\tshort\tMarvel's film\tMarvel\t0\t2005\t\\N\t11\t1\n"
              "tt0000004\tmovie\tMarvel's film\tMarvel\t1\t2005\t\\N\t11\t1\n"
              "tt0000005\tmovie\tLord of The rings\tLoTr\t0\t2005\t\\N\t110\t1\n"
              "tt0000006\tmovie\tHobbit\tHobbit\t0\t2005\t\\N\t110\t1\n";

    akasStr = "titleId\tordering\ttitle\tregion\tlanguage\ttypes\tattributes\tisOriginalTitle\n"
            "tt0000000\t1\tКарменсіта\tUA\t\\N\timdbDisplay\t\\N\t0\n"
            "tt0000005\t1\tВластелин Колец\tRU\t\\N\timdbDisplay\t\\n\t0";

    ratingsStr = "tconst\taverageRating\tnumVotes\n"
               "tt0000001\t5.7\t1953\n"
               "tt0000005\t8.9\t1400\n"
               "tt0000006\t9.1\t500\n";

    fail = "titleId\tordering\ttitle\tregion\tlanguage\ttypes\tattributes\tisOriginalTitle\n"
           "tt0000000 1 Карменсіта UA \\N imdbDisplay \\N 0\n"
           "tt0000001 2 Carmencita DE \\N \\N literal title 0\n";
}

TEST(FilmSuite, TestFilmInit) {
  Film f("tt0000000", -1, "test_film");
  EXPECT_EQ(f.id, "tt0000000");
  EXPECT_EQ(f.rate, -1);
  EXPECT_EQ(f.name, "test_film");
}

TEST(FilmSuite, TestFilmOutput) {
    testing::internal::CaptureStdout();
    Film f("tt0000000", -1, "test_film");
    std::cout << f;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "test_film -1");
}

TEST(ParserSuite, TestSimple) {
    std::string basicsStr;
    std::string akasStr;
    std::string ratingsStr;
    std::string failStr;
    genStrings(basicsStr, akasStr, ratingsStr, failStr);

    std::istringstream basics(basicsStr);
    std::istringstream akas(akasStr);
    std::istringstream ratings(ratingsStr);

    Parser parser("2005", akas, basics, ratings);
    int res = parser.parse();
    auto films = parser.getResult();
    EXPECT_EQ(res, 0);

    std::vector<Film> expected = {
            {"t1", 5.7, "Star Wars"},
            {"t2", 8.9, "Властелин Колец"},
    };
    EXPECT_EQ(expected.size(), films.size());
    for (int i = 0; i < films.size(); i++) {
        EXPECT_EQ(films[i].name, expected[i].name);
        EXPECT_EQ(films[i].rate, expected[i].rate);
    }
}

TEST(ParserSuite, TestWrongData) {
    std::string basicsStr;
    std::string akasStr;
    std::string ratingsStr;
    std::string failStr;
    genStrings(basicsStr, akasStr, ratingsStr, failStr);

    std::istringstream basics1(basicsStr);
    std::istringstream ratings1(ratingsStr);
    std::istringstream fail1(failStr);
    Parser parser1("2005", fail1, basics1, ratings1);
    int res = parser1.parse();
    EXPECT_EQ(res, 1);

    std::istringstream akas2(akasStr);
    std::istringstream ratings2(ratingsStr);
    std::istringstream fail2(failStr);
    Parser parser2("2005", akas2, fail2, ratings2);
    res = parser2.parse();
    EXPECT_EQ(res, 1);

    std::istringstream basics3(basicsStr);
    std::istringstream akas3(akasStr);
    std::istringstream fail3(failStr);
    Parser parser3("2005", akas3, basics3, fail3);
    res = parser3.parse();
    EXPECT_EQ(res, 1);
}

TEST(TopSuite, TestWithRvalue) {
    Top top({
        {"t1", 5.7, "Star Wars"},
        {"t2", 8.9, "Властелин Колец"},
        {"t3", 9.1, "Hobbit"},
    });
    std::vector<Film> expected = {
        {"t3", 9.1, "Hobbit"},
        {"t2", 8.9, "Властелин Колец"},
        {"t1", 5.7, "Star Wars"},
    };
    auto films = top.getTop();
    EXPECT_EQ(expected.size(), films.size());
    for (int i = 0; i < films.size(); i++) {
        EXPECT_EQ(films[i].name, expected[i].name);
        EXPECT_EQ(films[i].rate, expected[i].rate);
    }
}

TEST(TopSuite, TestWithLvalue) {
    std::vector<Film> films = {
            {"t1", 5.7, "Star Wars"},
            {"t2", 8.9, "Властелин Колец"},
            {"t3", 9.1, "Hobbit"},
    };
    Top top(films);
    std::vector<Film> expected = {
            {"t3", 9.1, "Hobbit"},
            {"t2", 8.9, "Властелин Колец"},
            {"t1", 5.7, "Star Wars"},
    };
    auto result = top.getTop();
    EXPECT_EQ(expected.size(), result.size());
    for (int i = 0; i < result.size(); i++) {
        EXPECT_EQ(result[i].name, expected[i].name);
        EXPECT_EQ(result[i].rate, expected[i].rate);
    }
}

int main(int argc, char** argv) {
  setlocale(0, ".UTF8");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

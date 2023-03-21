#include <gtest/gtest.h>
#include <vector>
#include <sstream>

#include "Film.h"
#include "Top.h"
#include "Parser.h"

class ParserSuite : public ::testing::Test {
 protected:
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

    void SetUp() override {
        std::string basicsStr;
        std::string akasStr;
        std::string ratingsStr;
        std::string failStr;
        genStrings(basicsStr, akasStr, ratingsStr, failStr);

        basics = std::istringstream(basicsStr);
        akas = std::istringstream(akasStr);
        ratings = std::istringstream(ratingsStr);
        fail = std::istringstream(failStr);
    }

    std::istringstream basics;
    std::istringstream akas;
    std::istringstream ratings;
    std::istringstream fail;
    Parser parser;
};

class TopSuite : public ::testing::Test {
 protected:
    void SetUp() override {
        films = {
                {"t1", 5.7, "Star Wars"},
                {"t2", 8.9, "Властелин Колец"},
                {"t3", 9.1, "Hobbit"},
        };

        expected = {
                {"t3", 9.1, "Hobbit"},
                {"t2", 8.9, "Властелин Колец"},
                {"t1", 5.7, "Star Wars"},
        };
    }

    std::vector<film_t> films;
    std::vector<film_t> expected;
};

TEST(FilmSuite, TestFilmInit) {
  film_t f("tt0000000", -1, "test_film");
  EXPECT_EQ(f.id, "tt0000000");
  EXPECT_EQ(f.rate, -1);
  EXPECT_EQ(f.name, "test_film");
}

TEST(FilmSuite, TestFilmOutput) {
    testing::internal::CaptureStdout();
    film_t f("tt0000000", -1, "test_film");
    std::cout << f;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "test_film -1");
}

TEST_F(ParserSuite, TestSimple) {
    int res = parser.parse(basics, ratings, akas, "2005");
    EXPECT_EQ(res, 0);

    std::vector<film_t> expected = {
            {"t1", 8.9, "Властелин Колец"},
            {"t2", 5.7, "Star Wars"},
    };
    auto films = parser.getResult();
    EXPECT_EQ(expected.size(), films.size());
    for (int i = 0; i < films.size(); i++) {
        EXPECT_EQ(films[i].name, expected[i].name);
        EXPECT_EQ(films[i].rate, expected[i].rate);
    }
}

TEST_F(ParserSuite, TestBasicsWrongData) {;
    int res = parser.parse(fail, ratings, akas, "2005");
    EXPECT_EQ(res, 1);
}

TEST_F(ParserSuite, TestRatingsWrongData) {;
    int res = parser.parse(basics, fail, akas, "2005");
    EXPECT_EQ(res, 1);
}

TEST_F(ParserSuite, TestAkasWrongData) {;
    int res = parser.parse(basics, ratings, fail, "2005");
    EXPECT_EQ(res, 1);
}

TEST_F(TopSuite, TestWithRvalue) {
    Top top(std::move(films), 10);
    auto films = top.getTop();
    EXPECT_EQ(expected.size(), films.size());
    for (int i = 0; i < films.size(); i++) {
        EXPECT_EQ(films[i].name, expected[i].name);
        EXPECT_EQ(films[i].rate, expected[i].rate);
    }
}

TEST_F(TopSuite, TestWithLvalue) {
    Top top(films, 10);
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

#include <gtest/gtest.h>

#include "Film.h"
#include "Top.h"

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

TEST(TopSuite, TestTop) {
    testing::internal::CaptureStdout();
    Top top("2005", "../../data/title.akas.tsv",
            "../../data/title.basics.tsv", "../../data/title.ratings.tsv");
    int res = top.getTop();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Звёздные войны. Эпизод 3: Месть Ситхов 7.6"
                      "Труп невесты 7.3"
                      "Фантастическая четвёрка 5.7");
    EXPECT_EQ(res, 0);
}

TEST(TopSuite, TestFailFileOpen) {
    Top top1("2005", "", "../../data/title.basics.tsv",
            "../../data/title.ratings.tsv");
    int res = top1.getTop();
    EXPECT_EQ(res, 1);
    Top top2("2005", "../../data/title.akas.tsv", "",
             "../../data/title.ratings.tsv");
    res = top2.getTop();
    EXPECT_EQ(res, 1);
    Top top3("2005", "../../data/title.akas.tsv", "../../data/title.basics.tsv",
             "");
    res = top3.getTop();
    EXPECT_EQ(res, 1);
}

int main(int argc, char** argv) {
  setlocale(LC_CTYPE, "rus");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
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
    top.getTop();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Звёздные войны. Эпизод 3: Месть Ситхов 7.6\n Труп невесты 7.3\n Фантастическая четвёрка 5.7");
}

int main(int argc, char** argv) {
  setlocale(LC_CTYPE, "rus");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include <vector>

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
    Top top("2005", "../../data/title.akas.tsv",
            "../../data/title.basics.tsv", "../../data/title.ratings.tsv");
    int res = top.createTop();
    auto films = top.getTop();
    EXPECT_EQ(res, 0);

    std::vector<Film> expected = {
            {"t1", 7.6, "Звёздные войны. Эпизод 3: Месть Ситхов"},
            {"t2", 7.3, "Труп невесты"},
            {"t3", 5.7, "Фантастическая четвёрка"},
    };
    EXPECT_EQ(expected.size(), films.size());
    for (int i = 0; i < films.size(); i++) {
        EXPECT_EQ(films[i].name, expected[i].name);
        EXPECT_EQ(films[i].rate, expected[i].rate);
    }
}

TEST(TopSuite, TestFailFileOpen) {
    Top top1("2005", "", "../../data/title.basics.tsv",
            "../../data/title.ratings.tsv");
    int res = top1.createTop();
    EXPECT_EQ(res, 1);
    Top top2("2005", "../../data/title.akas.tsv", "",
             "../../data/title.ratings.tsv");
    res = top2.createTop();
    EXPECT_EQ(res, 1);
    Top top3("2005", "../../data/title.akas.tsv", "../../data/title.basics.tsv",
             "");
    res = top3.createTop();
    EXPECT_EQ(res, 1);
}

int main(int argc, char** argv) {
  setlocale(LC_CTYPE, "rus");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

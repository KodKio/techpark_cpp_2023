#include <gtest/gtest.h>
#include <string>
#include "CatOperation.h"
#include "WcOperation.h"
#include "EchoOperation.h"
#include "Pipeline.h"
#include "Exceptions.h"


class EchoSuite : public ::testing::Test {
protected:
    void SetUp() override {
        expected = "test_output\n";
        o1 = std::make_shared<EchoOperation>("foo");
        o2 = std::make_shared<EchoOperation>("test_output");
        o1->SetNextOperation(o2);
    }

    std::string expected;
    std::shared_ptr<EchoOperation> o1;
    std::shared_ptr<EchoOperation> o2;
};


TEST_F(EchoSuite, CoutTest) {
    testing::internal::CaptureStdout();
    o2->HandleEndOfInput();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, output);
}

TEST_F(EchoSuite, PassOnAndIgnoreTest) {
    testing::internal::CaptureStdout();
    o1->HandleEndOfInput();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, output);
}


class CatSuite : public ::testing::Test {
protected:
    void SetUp() override {

        std::string s1 = "file1\ncontent1\n";
        std::string s2 = "file2\ncontent2\n";
        std::istringstream ss1(s1);
        std::istringstream ss2(s2);

        o1 = std::make_shared<CatOperation>(ss1);
        o2 = std::make_shared<CatOperation>(ss2);

        o1->SetNextOperation(o2);
    }

    std::shared_ptr<CatOperation> o1;
    std::shared_ptr<CatOperation> o2;
};


TEST_F(CatSuite, CoutTest) {
    std::string expected = "file2\ncontent2\n";

    testing::internal::CaptureStdout();
    o2->HandleEndOfInput();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, output);
}

TEST_F(CatSuite, PassOnTest) {
    std::string expected = "file1\ncontent1\nfile2\ncontent2\n";

    testing::internal::CaptureStdout();
    o1->HandleEndOfInput();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, output);
}


TEST(WcSuite, SimpleTest) {

    std::string s1 = "file1\ncontent1\n";
    std::istringstream ss1(s1);

    std::shared_ptr<CatOperation> o1 = std::make_shared<CatOperation>(ss1);
    std::shared_ptr<WcOperation> o2 = std::make_shared<WcOperation>();
    o1->SetNextOperation(o2);

    std::string expected = "2\n";

    testing::internal::CaptureStdout();
    o1->HandleEndOfInput();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, output);
}

TEST(PipelineSuite, SimpleExecuteTest) {
    Pipeline pl;
    pl.Construct("echo 1 | cat file.txt | echo 2 | wc -l | wc -l");
    std::string expected = "1\n";

    testing::internal::CaptureStdout();
    pl.Execute();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, output);
}

TEST(PipelineSuite, ExpectThrowFromExecuteTest) {
    Pipeline pl;
    EXPECT_THROW(pl.Construct("echo 1 | cats file.txt | echo 2 | wc -l"), UnknownCommandException);
}

TEST(PipelineSuite, ThrowMessageFromExecuteTest) {
    try {
        Pipeline pl;
        pl.Construct("echo 1 | cats file.txt | echo 2 | wc -l");
    } catch (std::exception& exc) {
        EXPECT_EQ(std::string(exc.what()), "Unknown command: cats file.txt");
    };
}

#include <gtest/gtest.h>

#include "csvtoker.hpp"

class CsvTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
};

TEST_F(CsvTest, trim_empty) {
  std::string s = "abcdef";
  EXPECT_EQ("", CsvToker::trim(s.data(), s.data()));
  EXPECT_EQ("a", CsvToker::trim(s.data(), s.data()+1));
  EXPECT_EQ("", CsvToker::trim(s.data(), s.data()-1));
}

TEST_F(CsvTest, trim_comma) {
  std::string s = "\"abcdef\",";
  EXPECT_EQ("abcdef", CsvToker::trim(s.data(), s.data() + s.size()));
}

TEST_F(CsvTest, parse_trunc_quoted) {
  std::string s = "\"abcdef,";
  std::vector<std::string> vec;
  CsvToker::parse(s,vec);
  ASSERT_EQ(1, vec.size());

  // input is invalid, so either of these can be considered fine:

  EXPECT_EQ("abcdef", vec[0]);
  //EXPECT_EQ("abcdef,", vec[0]);
}

TEST_F(CsvTest, parse_invalid_quoted_right) {
  std::string s = "a\"";
  std::vector<std::string> vec;
  CsvToker::parse(s,vec);
  ASSERT_EQ(1, vec.size());
  EXPECT_EQ("a", vec[0]);
}

TEST_F(CsvTest, parse_embedded_quote) {
  std::string s = "\"abc\"\"def\",g";
  std::vector<std::string> vec;
  CsvToker::parse(s,vec);
  ASSERT_EQ(2, vec.size());
  EXPECT_EQ("abc\"def", vec[0]);
}

TEST_F(CsvTest, parse_non_ascii) {
  std::string s = "hi,😀,newline\n,four";
  std::vector<std::string> vec;
  CsvToker::parse(s,vec);
  ASSERT_EQ(4, vec.size());
  EXPECT_EQ("😀", vec[1]);
}

TEST_F(CsvTest, parse_all_commas) {
  std::string s = ",,,";
  std::vector<std::string> vec;
  CsvToker::parse(s,vec);
  ASSERT_EQ(4, vec.size());
  EXPECT_EQ("", vec[1]);
}

TEST_F(CsvTest, parse_start_end_commas) {
  std::string s = ",b,c,";
  std::vector<std::string> vec;
  CsvToker::parse(s,vec);
  ASSERT_EQ(4, vec.size());
  EXPECT_EQ("", vec[3]);
}


TEST_F(CsvTest, remove_embedded_quotes) {
  std::string s1 = "65\"\" Sony";
  EXPECT_EQ("65\" Sony", CsvToker::remove_embedded_quotes(s1.data(),s1.data()+s1.size()));

  std::string s2 = "\"\"";
  EXPECT_EQ("\"", CsvToker::remove_embedded_quotes(s2.data(),s2.data()+s2.size()));

  std::string s3 = "\"\"start";
  EXPECT_EQ("\"start", CsvToker::remove_embedded_quotes(s3.data(),s3.data()+s3.size()));

  std::string s4 = "end\"\"";
  EXPECT_EQ("end\"", CsvToker::remove_embedded_quotes(s4.data(),s4.data()+s4.size()));

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int status= RUN_ALL_TESTS();
  return status;
}

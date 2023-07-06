#include "v8/Base/TemplateUtils.h"

#include <glog/logging.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace v8::base::template_utils_unittest {

namespace {
template <typename T, size_t Size>
void CheckArrayEquals(const std::array<T, Size>& arr1,
                      const std::array<T, Size>& arr2) {
  for (size_t i = 0; i < Size; ++i) {
    CHECK_EQ(arr1[i], arr2[i]);
  }
}
}  // namespace

TEST(TemplateUtilsTest, MakeArraySimple) {
  auto computed_array = base::make_array<3>([](int i) { return 1 + (i * 3); });
  std::array<int, 3> expected{{1, 4, 7}};
  CheckArrayEquals(computed_array, expected);
}

namespace {
constexpr auto doubleIntValue(int i) -> int { return i * 2; }
}  // namespace

TEST(TemplateUtilsTest, MakeArrayConstexpr) {
  constexpr auto ComputedArray = base::make_array<3>(doubleIntValue);
  constexpr std::array<int, 3> Expected{{0, 2, 4}};
  CheckArrayEquals(ComputedArray, Expected);
}

// Wrap into this helper struct, such that the type is printed on errors.
template <typename T1, typename T2>
struct CheckIsSame {
  static_assert(std::is_same_v<T1, T2>, "test failure");
};

#define TEST_PASS_VALUE_OR_REF0(remove_extend, expected, given)               \
  static_assert(                                                              \
      sizeof(CheckIsSame<expected,                                            \
                         pass_value_or_ref<given, remove_extend>::type>) > 0, \
      "check")

#define TEST_PASS_VALUE_OR_REF(expected, given)                          \
  static_assert(                                                         \
      sizeof(CheckIsSame<expected, pass_value_or_ref<given>::type>) > 0, \
      "check")

TEST_PASS_VALUE_OR_REF(int, int&);
TEST_PASS_VALUE_OR_REF(int, int&&);
TEST_PASS_VALUE_OR_REF(const char*, const char[14]);
TEST_PASS_VALUE_OR_REF(const char*, const char*&&);
TEST_PASS_VALUE_OR_REF(const char*, const char (&)[14]);
TEST_PASS_VALUE_OR_REF(const std::string&, std::string);
TEST_PASS_VALUE_OR_REF(const std::string&, std::string&);
TEST_PASS_VALUE_OR_REF(const std::string&, const std::string&);
TEST_PASS_VALUE_OR_REF(int, const int);
TEST_PASS_VALUE_OR_REF(int, const int&);
TEST_PASS_VALUE_OR_REF(const int*, const int*);
TEST_PASS_VALUE_OR_REF(const int*, const int* const);
TEST_PASS_VALUE_OR_REF0(false, const char[14], const char[14]);
TEST_PASS_VALUE_OR_REF0(false, const char[14], const char (&)[14]);
TEST_PASS_VALUE_OR_REF0(false, const std::string&, std::string);
TEST_PASS_VALUE_OR_REF0(false, const std::string&, std::string&);
TEST_PASS_VALUE_OR_REF0(false, const std::string&, const std::string&);
TEST_PASS_VALUE_OR_REF0(false, int, const int);
TEST_PASS_VALUE_OR_REF0(false, int, const int&);

}  // namespace v8::base::template_utils_unittest

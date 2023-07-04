#include "v8/Base/TemplateUtils.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <glog/logging.h>

namespace v8 {
namespace base {
namespace template_utils_unittest {

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

}  // namespace template_utils_unittest
}  // namespace base
}  // namespace v8
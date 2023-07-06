#ifndef V8_BASE_TEMPLATE_UTILS_H
#define V8_BASE_TEMPLATE_UTILS_H

#include <array>
#include <functional>
#include <iosfwd>
#include <tuple>
#include <type_traits>
#include <utility>

namespace v8::base {

namespace detail {

template <typename Function, std::size_t... Indexes>
constexpr inline auto make_array_helper(
    Function&& f, std::index_sequence<Indexes...> /*unused*/)
    -> std::array<decltype(f(0)), sizeof...(Indexes)> {
  return {{std::forward<Function>(f)(Indexes)...}};
}

}  // namespace detail

// base::make_array: Create an array of fixed length, initialized by a function.
// The content of the array is created by calling the function with 0 .. Size-1.
// Example usage to create the array {0, 2, 4}:
//   std::array<int, 3> arr = base::make_array<3>(
//       [](std::size_t i) { return static_cast<int>(2 * i); });
// The resulting array will be constexpr if the passed function is constexpr.
template <std::size_t Size, class Function>
constexpr auto make_array(Function&& f) {
  return detail::make_array_helper(std::forward<Function>(f),
                                   std::make_index_sequence<Size>{});
}

// Helper to determine how to pass values: Pass scalars and arrays by value,
// others by const reference (even if it was a non-const ref before; this is
// disallowed by the style guide anyway).
// The default is to also remove array extends (int[5] -> int*), but this can be
// disabled by setting {remove_array_extend} to false.
template <typename T, bool RemoveArrayExtend = true>
struct pass_value_or_ref {
  using NorefType = std::remove_reference_t<T>;
  using DecayType =
      std::conditional_t<std::is_array_v<NorefType> && !RemoveArrayExtend,
                         NorefType, std::decay_t<NorefType>>;
  using type = std::conditional_t<std::is_scalar_v<DecayType> ||
                                      std::is_array_v<DecayType>,
                                  DecayType, const DecayType&>;
};

}  // namespace v8::base

#endif  // V8_BASE_TEMPLATE_UTILS_H
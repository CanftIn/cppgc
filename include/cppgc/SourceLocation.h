#ifndef CPPGC_SOURCE_LOCATION_H
#define CPPGC_SOURCE_LOCATION_H

#include <string>

#if defined(__has_builtin)
#define CPPGC_SUPPORTS_SOURCE_LOCATION                                   \
  (__has_builtin(__builtin_FUNCTION) && __has_builtin(__builtin_FILE) && \
   __has_builtin(__builtin_LINE))  // NOLINT
#else
#define CPPGC_SUPPORTS_SOURCE_LOCATION 0
#endif

namespace cppgc {

class SourceLocation final {
 public:
  /**
   * Construct source location information corresponding to the location of the
   * call site.
   */
#if CPPGC_SUPPORTS_SOURCE_LOCATION
  static constexpr auto Current(const char* function = __builtin_FUNCTION(),
                                const char* file = __builtin_FILE(),
                                size_t line = __builtin_LINE())
      -> SourceLocation {
    return SourceLocation(function, file, line);
  }
#else
  static constexpr auto Current() -> SourceLocation { return SourceLocation(); }
#endif  // CPPGC_SUPPORTS_SOURCE_LOCATION

  /**
   * Constructs unspecified source location information.
   */
  constexpr SourceLocation() = default;

  /**
   * Returns the name of the function associated with the position represented
   * by this object, if any.
   *
   * \returns the function name as cstring.
   */
  constexpr auto Function() const -> const char* { return function_; }

  /**
   * Returns the name of the current source file represented by this object.
   *
   * \returns the file name as cstring.
   */
  constexpr auto FileName() const -> const char* { return file_; }

  /**
   * Returns the line number represented by this object.
   *
   * \returns the line number.
   */
  constexpr auto Line() const -> size_t { return line_; }

  /**
   * Returns a human-readable string representing this object.
   *
   * \returns a human-readable string representing source location information.
   */
  auto ToString() const -> std::string {
    if (!file_) {
      return {};
    }
    return std::string(function_) + "@" + file_ + ":" + std::to_string(line_);
  }

 private:
  constexpr SourceLocation(const char* function, const char* file, size_t line)
      : function_(function), file_(file), line_(line) {}

  const char* function_ = nullptr;
  const char* file_ = nullptr;
  size_t line_ = 0U;
};

}  // namespace cppgc

#endif  // CPPGC_SOURCE_LOCATION_H
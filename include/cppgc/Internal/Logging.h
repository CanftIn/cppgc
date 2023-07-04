#ifndef CPPGC_INTERNAL_LOGGING_H
#define CPPGC_INTERNAL_LOGGING_H

#include "cppgc/Config.h"
#include "cppgc/SourceLocation.h"

namespace cppgc::internal {

void DCheckImpl(const char*, const SourceLocation& = SourceLocation::Current());
[[noreturn]] void FatalImpl(const char*,
                            const SourceLocation& = SourceLocation::Current());

// Used to ignore -Wunused-variable.
template <typename>
struct EatParams {};

#if defined(DEBUG)
#define CPPGC_DCHECK_MSG(condition, message)  \
  do {                                        \
    if (CPPGC_UNLIKELY(!(condition))) {       \
      ::cppgc::internal::DCheckImpl(message); \
    }                                         \
  } while (false)
#else  // !defined(DEBUG)
#define CPPGC_DCHECK_MSG(condition, message)       \
  (static_cast<void>(::cppgc::internal::EatParams< \
                     decltype(static_cast<void>(condition), message)>{}))
#endif  // !defined(DEBUG)

#define CPPGC_DCHECK(condition) CPPGC_DCHECK_MSG(condition, #condition)

#define CPPGC_CHECK_MSG(condition, message)  \
  do {                                       \
    if (CPPGC_UNLIKELY(!(condition))) {      \
      ::cppgc::internal::FatalImpl(message); \
    }                                        \
  } while (false)

#define CPPGC_CHECK(condition) CPPGC_CHECK_MSG(condition, #condition)

}  // namespace cppgc::internal

#endif  // CPPGC_INTERNAL_LOGGING_H
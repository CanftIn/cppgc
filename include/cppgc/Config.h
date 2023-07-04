#ifndef CPPGC_CONFIG_H
#define CPPGC_CONFIG_H

namespace cppgc {

#if defined(__clang__)
#define CPPGC_HAS_BUILTIN_EXPECT (__has_builtin(__builtin_expect))
#elif defined(__GNUC__)
#define CPPGC_HAS_BUILTIN_EXPECT 1
#endif

#if HAS_BUILTIN_EXPECT
#define CPPGC_UNLIKELY(condition) (__builtin_expect(!!(condition), 0))
#define CPPGC_LIKELY(condition) (__builtin_expect(!!(condition), 1))
#else
#define CPPGC_UNLIKELY(condition) (condition)
#define CPPGC_LIKELY(condition) (condition)
#endif

}  // namespace cppgc

#endif  // CPPGC_CONFIG_H
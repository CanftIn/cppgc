#include "cppgc/Internal/Logging.h"


namespace cppgc::internal {

//void DCheckImpl(const char* message, const SourceLocation& loc) {
//  V8_Dcheck(loc.FileName(), static_cast<int>(loc.Line()), message);
//}
//
//void FatalImpl(const char* message, const SourceLocation& loc) {
//#if DEBUG
//  V8_Fatal(loc.FileName(), static_cast<int>(loc.Line()), "Check failed: %s.",
//           message);
//#elif !defined(OFFICIAL_BUILD)
//  V8_Fatal("Check failed: %s.", message);
//#else
//  V8_Fatal("ignored");
//#endif
//}

} // namespace cppgc::internal

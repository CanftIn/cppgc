#ifndef CPPGC_COMMON_H
#define CPPGC_COMMON_H

namespace cppgc {

/**
 *  Indicator for the stack state of the embedder.
 */
enum class EmbedderStackState {
  /**
   * Stack may contain interesting heap pointers.
   */
  kMayContainHeapPointers,
  /**
   * Stack does not contain any interesting heap pointers.
   */
  kNoHeapPointers,
};

}  // namespace cppgc

#endif  // CPPGC_COMMON_H
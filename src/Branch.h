#pragma once

#include "Shape.h"

#include <vector>
#include "llvm/IR/Instruction.h"

namespace llvm {
namespace Relooper {

///
/// Info about a branching from one block to another
///
struct Branch {
  enum FlowType {
    Direct = 0, // We will directly reach the right location through other
                // means, no need for continue or break
    Break = 1,
    Continue = 2,
    Nested = 3 // This code is directly reached, but we must be careful to
               // ensure it is nested in an if - it is not reached
    // unconditionally, other code paths exist alongside it that we need to make
    // sure do not intertwine
  };
  Shape
      *Ancestor; // If not nullptr, this shape is the relevant one for purposes
                 // of getting to the target block. We break or continue on it
  Branch::FlowType
      Type;     // If Ancestor is not nullptr, this says whether to break or
                // continue
  bool Labeled; // If a break or continue, whether we need to use a label
  const char *Condition; // The condition for which we branch. For example,
                         // "my_var == 1". Conditions are checked one by one.
                         // One of the conditions should have nullptr as the
                         // condition, in which case it is the default
                         // FIXME: move from char* to LLVM data structures
 std::vector<const llvm::Instruction*> Code; // If provided, code that is run right before the branch is
                    // taken. This is useful for phis
                    // FIXME: move from char* to LLVM data structures

  Branch(const char *ConditionInit, const std::vector<const llvm::Instruction*> *CodeInit = nullptr);
  ~Branch();
};

} // namespace Relooper
} // namespace llvm

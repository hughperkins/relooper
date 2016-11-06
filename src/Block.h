#pragma once

#include "Relooper.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"

#include <vector>
#include <string>

namespace llvm {
namespace Relooper {

///
/// Represents a basic block of code - some instructions that end with a
/// control flow modifier (a branch, return or throw).
///
struct Block {
  // Branches become processed after we finish the shape relevant to them. For
  // example, when we recreate a loop, branches to the loop start become
  // continues and are now processed. When we calculate what shape to generate
  // from a set of blocks, we ignore processed branches. Blocks own the Branch
  // objects they use, and destroy them when done.
  OwningBlockBranchMap BranchesOut;
  BlockSet BranchesIn;
  OwningBlockBranchMap ProcessedBranchesOut;
  BlockSet ProcessedBranchesIn;
  Shape *Parent; // The shape we are directly inside
  int Id; // A unique identifier, defined when added to relooper. Note that this
          // uniquely identifies a *logical* block - if we split it, the two
          // instances have the same content *and* the same Id
  std::string name;
  std::vector<const llvm::Instruction*> Code;
  // const char *Code;      // The string representation of the code in this block.
  //                        // Owning pointer (we copy the input)
  //                        // FIXME: move from char* to LLVM data structures
  std::vector<llvm::BasicBlock *> BranchVar;
  // const char *BranchVar; // A variable whose value determines where we go; if
  //                        // this is not nullptr, emit a switch on that variable
  //                        // FIXME: move from char* to LLVM data structures
  bool IsCheckedMultipleEntry; // If true, we are a multiple entry, so reaching
                               // us requires setting the label variable

  Block(std::string name);
  ~Block();

  void AddBranchTo(Block *Target, const char *Condition,
                   const std::vector<const llvm::Instruction*> *Code = nullptr);
};

} // namespace Relooper
} // namespace llvm

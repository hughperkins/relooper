// Copyright Alon Zakai 2011, Hugh Perkins 2016
//
//===-- Relooper.cpp - Top-level interface for WebAssembly  ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
///
/// \file
/// \brief This implements the Relooper algorithm. This implementation includes
/// optimizations added since the original academic paper [1] was published.
///
/// [1] Alon Zakai. 2011. Emscripten: an LLVM-to-JavaScript compiler. In
/// Proceedings of the ACM international conference companion on Object
/// oriented programming systems languages and applications companion
/// (SPLASH '11). ACM, New York, NY, USA, 301-312. DOI=10.1145/2048147.2048224
/// http://doi.acm.org/10.1145/2048147.2048224
///
//===-------------------------------------------------------------------===//

// Block

#include "Block.h"

#include "Branch.h"

#include "llvm/IR/Instruction.h"

#include <memory>

namespace llvm {
namespace Relooper {

Block::Block(std::string name)
    : Parent(nullptr), Id(-1), IsCheckedMultipleEntry(false) {
    this->name = name;
  // FIXME: move from char* to LLVM data structures
  // Code = strdup(CodeInit);
  // BranchVar = BranchVarInit ? strdup(BranchVarInit) : nullptr;
}

Block::~Block() {
  // FIXME: move from char* to LLVM data structures
  // free(static_cast<void *>(const_cast<char *>(Code)));
  // free(static_cast<void *>(const_cast<char *>(BranchVar)));
}

void Block::AddBranchTo(Block *Target, const char *Condition,
                        const std::vector<const llvm::Instruction*> *Code) {
  assert(!contains(BranchesOut, Target) &&
         "cannot add more than one branch to the same target");

  BranchesOut[Target] = make_unique<Branch>(Condition, Code);
}

} // Relooper
} // llvm

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

#include "Branch.h"

// Branch

namespace llvm {
namespace Relooper {

Branch::Branch(const char *ConditionInit, const std::vector<const llvm::Instruction*>  *CodeInit)
    : Ancestor(nullptr), Labeled(true) {
  // FIXME: move from char* to LLVM data structures
  Condition = ConditionInit ? strdup(ConditionInit) : nullptr;
  // Code = CodeInit ? strdup(CodeInit) : nullptr;
  if(CodeInit != 0) {
    Code = *CodeInit;
  }
}

Branch::~Branch() {
  // FIXME: move from char* to LLVM data structures
  // free(static_cast<void *>(const_cast<char *>(Condition)));
  // free(static_cast<void *>(const_cast<char *>(Code)));
}

} // Relooper
} // llvm

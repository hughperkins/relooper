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

#pragma once

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

namespace llvm {
namespace Relooper {

struct RelooperAnalysis final : public FunctionPass {
  static char ID;
  RelooperAnalysis() : FunctionPass(ID) {}
  const char *getPassName() const override { return "relooper"; }
  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }
  bool runOnFunction(Function &F) override;
};

} // Relooper
} // llvm

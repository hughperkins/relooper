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

#include "RelooperAnalysis.h"

#include "RelooperAlgorithm.h"
#include "Branch.h"
#include "Block.h"

// #include "llvm/ADT/STLExtras.h"
// #include "llvm/IR/CFG.h"
#include "llvm/IR/BasicBlock.h"
// #include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/CFG.h"

#define DEBUG_TYPE "relooper"

using namespace llvm;

namespace llvm {

FunctionPass *createWebAssemblyRelooper() {
  return new Relooper::RelooperAnalysis();
}

namespace Relooper {

char RelooperAnalysis::ID = 0;

bool RelooperAnalysis::runOnFunction(Function &F) {
  DEBUG(dbgs() << "Relooping function '" << F.getName() << "'\n");
  RelooperAlgorithm R;
  // FIXME: remove duplication between relooper's and LLVM's BBs.
  std::map<const BasicBlock *, Block *> BB2B;
  std::map<const Block *, const BasicBlock *> B2BB;
  for (const BasicBlock &BB : F) {
    // FIXME: getName is wrong here, Code is meant to represent amount of code.
    // FIXME: use BranchVarInit for switch.
    std::string name = BB.getName().str();
    if(name == "") {
       name = "v" + toString(HughsBlockId);
       HughsBlockId++;
     }
    DEBUG(dbgs() << "name data: [" << BB.getName().data() << "]\n");
    Block *B = new Block(name);
    for(auto it=BB.begin(); it != BB.end(); it++) {
      const Instruction *inst = &*it;
      // if(isa<BranchInst>(inst)) {
        B->Code.push_back(inst);
      // } elses {
      //   B->Code.push_back(inst);
      // }
    }
    DEBUG(dbgs() << "   block " << name << "\n");
    R.AddBlock(B);
    assert(BB2B.find(&BB) == BB2B.end() && "Inserting the same block twice");
    assert(B2BB.find(B) == B2BB.end() && "Inserting the same block twice");
    BB2B[&BB] = B;
    B2BB[B] = &BB;
  }
  for (Block *B : R.Blocks) {
    const BasicBlock *BB = B2BB[B];
    DEBUG(dbgs() << "adding successors for " << B->name << "\n");
    for (const BasicBlock *Successor : successors(BB)) {
      // FIXME: add branch's Condition and Code below.
      DEBUG(dbgs() << "  got successor " << "\n");
      B->AddBranchTo(BB2B[Successor], /*Condition=*/nullptr, /*Code=*/nullptr);
    }
  }
  R.Calculate(BB2B[&F.getEntryBlock()]);
  return false; // Analysis passes don't modify anything.
}

} // Relooper
} // llvm

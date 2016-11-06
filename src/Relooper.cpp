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

#include "Relooper.h"

#include "WebAssembly.h"
#include "Branch.h"
#include "Block.h"
#include "Shape.h"
#include "SimpleShape.h"
#include "MultipleShape.h"
#include "LoopShape.h"
#include "LabeledShape.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#include <cstring>
#include <cstdlib>
#include <functional>
#include <list>
#include <stack>
#include <string>
#include <sstream>

#define DEBUG_TYPE "relooper"

using namespace llvm;
using namespace Relooper;
using namespace std;

namespace llvm {
namespace Relooper {

} // Relooper
} // llvm

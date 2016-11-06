// Copyright Alon Zakai 2011, Hugh Perkins 2016
//
//===-- Relooper.h - Top-level interface for WebAssembly  ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===-------------------------------------------------------------------===//
///
/// \file
/// \brief This defines an optimized C++ implemention of the Relooper
/// algorithm, originally developed as part of Emscripten, which
/// generates a structured AST from arbitrary control flow.
///
//===-------------------------------------------------------------------===//

#pragma once

// #include "Shape.h"
// #include "Block.h"

#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/Casting.h"

#include <cassert>

#include <cstdarg>
#include <cstdio>
#include <deque>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include <sstream>
#include <string>

namespace llvm {
namespace Relooper {

struct Block;
struct Branch;
struct Shape;

typedef SetVector<Block *> BlockSet;
typedef MapVector<Block *, Branch *> BlockBranchMap;
typedef MapVector<Block *, std::unique_ptr<Branch>> OwningBlockBranchMap;

// Blocks with the same id were split and are identical, so we just care about
// ids in Multiple entries
typedef std::map<int, Shape *> IdShapeMap;

// Helpers

typedef MapVector<Block *, BlockSet> BlockBlockSetMap;
typedef std::list<Block *> BlockList;

template <class T, class U>
static bool contains(const T &container, const U &contained) {
  return container.count(contained);
}

template<typename T>
std::string toString(T val) {
  std::ostringstream oss;
  oss << val;
  return oss.str();
}

extern int HughsBlockId;

inline std::string getNewBlockname() {
  std::string name = "v" + toString(HughsBlockId);
  HughsBlockId++;
  return name;
}

} // namespace Relooper
} // namespace llvm

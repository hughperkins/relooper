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

#include "Shape.h"
#include "Block.h"

namespace llvm {
namespace Relooper {

///
/// Simple: No control flow at all, just instructions.
///
struct SimpleShape : public Shape {
  Block *Inner;

  SimpleShape() : Shape(SK_Simple), Inner(nullptr) {}

  static bool classof(const Shape *S) { return S->getKind() == SK_Simple; }
};

} // namespace Relooper
} // namespace llvm

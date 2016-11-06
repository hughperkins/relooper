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

#include "LabeledShape.h"

namespace llvm {
namespace Relooper {

///
/// Multiple: A shape with more than one entry. If the next block to
///           be entered is among them, we run it and continue to
///           the next shape, otherwise we continue immediately to the
///           next shape.
///
struct MultipleShape : public LabeledShape {
  IdShapeMap InnerMap; // entry block ID -> shape
  int Breaks; // If we have branches on us, we need a loop (or a switch). This
              // is a counter of requirements,
              // if we optimize it to 0, the loop is unneeded
  bool UseSwitch; // Whether to switch on label as opposed to an if-else chain

  MultipleShape() : LabeledShape(SK_Multiple), Breaks(0), UseSwitch(false) {}

  static bool classof(const Shape *S) { return S->getKind() == SK_Multiple; }
};

} // namespace Relooper
} // namespace llvm

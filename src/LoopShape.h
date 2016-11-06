#pragma once

#include "LabeledShape.h"

namespace llvm {
namespace Relooper {

///
/// Loop: An infinite loop.
///
struct LoopShape : public LabeledShape {
  Shape *Inner;

  LoopShape() : LabeledShape(SK_Loop), Inner(nullptr) {}

  static bool classof(const Shape *S) { return S->getKind() == SK_Loop; }
};

} // namespace Relooper
} // namespace llvm

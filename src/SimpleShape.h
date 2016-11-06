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

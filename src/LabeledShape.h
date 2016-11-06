#pragma once

#include "Shape.h"

namespace llvm {
namespace Relooper {

///
/// A shape that may be implemented with a labeled loop.
///
struct LabeledShape : public Shape {
  bool Labeled; // If we have a loop, whether it needs to be labeled

  LabeledShape(ShapeKind KindInit) : Shape(KindInit), Labeled(false) {}
};

} // Relooper
} //llvm

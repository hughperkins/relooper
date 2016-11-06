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

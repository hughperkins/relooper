#pragma once

namespace llvm {
namespace Relooper {

///
/// Represents a structured control flow shape
///
struct Shape {
  int Id; // A unique identifier. Used to identify loops, labels are Lx where x
          // is the Id. Defined when added to relooper
  Shape *Next;    // The shape that will appear in the code right after this one
  Shape *Natural; // The shape that control flow gets to naturally (if there is
                  // Next, then this is Next)

  /// Discriminator for LLVM-style RTTI (dyn_cast<> et al.)
  enum ShapeKind { SK_Simple, SK_Multiple, SK_Loop };

private:
  ShapeKind Kind;

public:
  ShapeKind getKind() const { return Kind; }

  Shape(ShapeKind KindInit) : Id(-1), Next(nullptr), Kind(KindInit) {}
};

} // namespace Relooper
} // namespace llvm

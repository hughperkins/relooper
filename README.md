# relooper
Reloop llvm IR output, to have `for`s, `if`s, `while`s.  From https://reviews.llvm.org/D12744

## Why?

I'm using this personally for my [cuda-on-cl](https://github.com/hughperkins/cuda-on-cl) project, to 'reloop' the OpenCL, so it's not full of `goto`s and labels :-)

This code came originally from From https://reviews.llvm.org/D12744 , ie WebAssembly target for llvm.

I * think* the WebAssembly reloop *may* have come originally from https://github.com/kripken/Relooper , but I'm unclear on this point at this time.

I havent definitively decided to use this coe or not in cuda-on-cl, but it sounds promising.  Probably better than rolling my own...

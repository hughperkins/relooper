// some initial test of relooper...

#include "argparsecpp.h"

#include "WebAssembly.h"

#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/CFG.h"

#include <iostream>
#include <memory>
using namespace std;

int main(int argc, char *argv[]) {
    string inputfile;
    argparsecpp::ArgumentParser parser;
    parser.add_string_argument("--inputfile", &inputfile)->help("input IR file");
    if(!parser.parse_args(argc, argv)) {
        return 1;
    }

    SMDiagnostic smDiagnostic;
    std::unique_ptr<llvm::Module> M = parseIRFile(inputfile, smDiagnostic, context);
    if(!M) {
        smDiagnostic.print(argv[0], errs());
        return 1;
    }

    FunctionPass *llvm::createWebAssemblyRelooper();

    return 0;
}

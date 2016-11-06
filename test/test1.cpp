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
#include "llvm/Support/SourceMgr.h"

#include <iostream>
#include <memory>
using namespace std;
using namespace llvm;

namespace llvm {
    extern bool DebugFlag;
}

namespace cocl {

void analyzeModule(Module *M, string specificFunction, FunctionPass *relooper_pass) {
    for(auto it=M->begin(); it != M->end(); it++) {
        Function *F = &*it;
        string name = F->getName();
        if(specificFunction != "" && name != specificFunction) {
            continue;
        }
        cout << "name " << name << endl;
        relooper_pass->runOnFunction(*F);
    }
}

} // namespace cocl

int main(int argc, char *argv[]) {
    llvm::DebugFlag = true;

    string inputfile;
    string specificFunction;
    argparsecpp::ArgumentParser parser;
    parser.add_string_argument("--inputfile", &inputfile)->help("input IR file")->required();
    parser.add_string_argument("--specific_function", &specificFunction);
    if(!parser.parse_args(argc, argv)) {
        return 1;
    }

    llvm::LLVMContext context;
    SMDiagnostic smDiagnostic;
    std::unique_ptr<llvm::Module> M = parseIRFile(inputfile, smDiagnostic, context);
    if(!M) {
        smDiagnostic.print(argv[0], errs());
        return 1;
    }

    FunctionPass *relooper_pass = llvm::createWebAssemblyRelooper();
    cocl::analyzeModule(M.get(), specificFunction, relooper_pass);

    return 0;
}

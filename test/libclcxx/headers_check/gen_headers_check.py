import sys;
from os import listdir
from os.path import isfile, join, splitext

def make_header(out):
    out.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify\n")
    out.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-fp16-enable -cl-std=c++ -fsyntax-only -pedantic -verify\n")
    out.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-fp64-enable -cl-std=c++ -fsyntax-only -pedantic -verify\n")
    out.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-fp16-enable -cl-fp64-enable -cl-std=c++ -fsyntax-only -pedantic -verify\n")
    out.write("// expected-no-diagnostics\n\n")
    out.write("#ifdef cl_khr_fp16\n#pragma OPENCL EXTENSION cl_khr_fp16 : enable\n#endif\n\n")
    out.write("#ifdef cl_khr_fp64\n#pragma OPENCL EXTENSION cl_khr_fp64 : enable\n#endif\n\n")

if (len(sys.argv) < 1):
    print("This python script requires to pass headers directory as first argument.")
    sys.exit(1)

headersDir = sys.argv[1]

try:
    out = open("TestBasicHeaders.cl", "w+")
    make_header(out)
    

    headers = [f for f in listdir(headersDir) if isfile(join(headersDir, f)) and (splitext(f)[1] == ".h" or splitext(f)[1] == "")]
    for h in headers:
        individual = open("TestBasicHeaders_"+splitext(h)[0]+".cl", "w+")
        make_header(individual)
        individual.write("#include<"+h+">\n")
        individual.write("\nkernel void worker(){ }\n")
        individual.close()
        
        out.write("#include <"+h+">\n")
    
    out.write("\nkernel void worker(){ }\n")
    out.close()
    
except IOError:
    sys.exit(2)

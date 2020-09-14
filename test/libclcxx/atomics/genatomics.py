import sys;

try:
    from enum import IntEnum
except ImportError:
    sys.exit(1)

class Type(IntEnum):
    int = 0
    uint = 1
    long = 2
    ulong = 3
    float = 4
    double = 5
    size_t = 6
    ptrdiff_t = 7
    intptr_t = 8
    uintptr_t = 9
    
    # invalid atomic types
    bool = 10
    char = 11
    short = 12
    memory_order = 13
    memory_scope = 14
    
    FIRST_INVALID = bool
  
class GenericType(IntEnum):
    A = 0 #atomic type
    C = 1 #underlying type
    M = 2 #arithmetic operation result's type
    
    A_ref = 10
    C_ref = 11
    M_ref = 12
    
    A_ptr = 20
    C_ptr = 21
    M_ptr = 22
  
class Atomic:
    def __init__(self, type, ptr):
        self.type = type
        self.is_pointer = ptr
        self.ifdef = False
        
    def is_valid(self):
        if (self.is_pointer == True):
            return True
            
        return (self.type < Type.FIRST_INVALID)
            
    def get_type_name_for_generic(self, generic):
        mod = ""
        if (type(generic) is GenericType):
            if (generic >= 20):
                mod = "*"
                generic = generic-20
            elif (generic >= 10):
                mod = "&"
                generic = generic-10
        
        if (generic == GenericType.A):
            return "atomic<"+self.type.name+("*" if self.is_pointer else "")+">"+mod
        elif (generic == GenericType.C):
            return self.type.name+("*" if self.is_pointer else "")+mod
        elif (generic == GenericType.M):
            return ("ptrdiff_t" if self.is_pointer else self.type.name)+mod
        else:
            return generic.name
            
    def get_tmp_name_for_generic(self, generic, name_suffix = ""):
        return "_"+self.get_short_name()+generic.name+name_suffix;
            
    def is_arithmetic_capable(self):
        return (self.is_pointer or (self.type != Type.float and self.type != Type.double))
            
    def get_short_name(self):
        return ("p" if self.is_pointer else "")+self.type.name
    def get_var_name(self):
        return "_atomic_"+self.get_short_name()
    def get_var_type(self):
        return self.get_type_name_for_generic(GenericType.A)
        
    def make_declaration(self):
        return self.get_var_type()+" "+self.get_var_name()+";"
        
    def get_underlaying_type_name(self):
        return self.get_type_name_for_generic(GenericType.C)
        
    def make_tmp_var_declaration(self, generic, name_suffix = ""):
        if (type(generic) is GenericType and generic >= 10 and generic < 20):
            return self.get_type_name_for_generic(generic)[:-1]+" "+self.get_tmp_name_for_generic(generic, name_suffix)+";"
        else:
            return self.get_type_name_for_generic(generic)+" "+self.get_tmp_name_for_generic(generic, name_suffix)+";"
            
            
    def print_ifdefs(self, out):
        if (self.ifdef == True):
            return
            
        if (self.is_pointer == False and (self.type == Type.double or self.type == Type.long or self.type == Type.ulong)):
            self.ifdef = True
            if (self.type == Type.double):
                out.write("#if defined(cl_khr_fp64) && defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics)\n")
            else:
                out.write("#if defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics)\n")
    
    def end_ifdefs(self, out):
        if (self.ifdef == True):
            out.write("#endif\n")
        self.ifdef = False
    
    
declarations = []
class AtomicFunctionCall:
    def __init__(self, atomic, fname, fargs, fopt_args, rettype, arithmetic = False):
        self.atomic = atomic
        self.fname = fname
        self.fargs = fargs
        self.fopt_args = fopt_args
        self.rettype = rettype
        self.is_arithmetic_func = arithmetic
        
    def is_valid(self):
        return (self.atomic.is_valid() and (self.atomic.is_arithmetic_capable() or not self.is_arithmetic_func))
        
    def spawn_call(self, out):
        
        self.atomic.print_ifdefs(out)

        if (self.is_valid()):
            out.write("    {//valid\n")
        else:
            out.write("    {//invalid\n")
            
        args_counter = {}
        args_no = {}
        arg_idx = 0
        for arg in self.fargs+self.fopt_args:
            if self.atomic.get_tmp_name_for_generic(arg) not in args_counter:
                args_counter[self.atomic.get_tmp_name_for_generic(arg)] = 0
            else:
                args_counter[self.atomic.get_tmp_name_for_generic(arg)] = args_counter[self.atomic.get_tmp_name_for_generic(arg)]+1
            args_no[arg_idx] = args_counter[self.atomic.get_tmp_name_for_generic(arg)]
            arg_idx = arg_idx+1
            
        
        arg_idx = 0
        out.write("    "+self.atomic.make_declaration()+"\n");
        for arg in self.fargs+self.fopt_args:
            out.write("      "+self.atomic.make_tmp_var_declaration(arg, "_"+str(args_no[arg_idx]))+"\n")
            arg_idx = arg_idx+1
        
        out.write("      ")
        out.write(self.atomic.get_var_name()+"."+self.fname+"(");
        i = 0
        for arg in self.fargs:
            out.write(("" if i == 0 else " ")+self.atomic.get_tmp_name_for_generic(arg, "_"+str(args_no[i]))+("" if i+1 == len(self.fargs) else ","))
            i = i+1
            
        out.write(");\n")
        
        if (len(self.fopt_args) != 0):
            out.write("      ")
            out.write(self.atomic.get_var_name()+"."+self.fname+"(");
            i = 0
            for arg in self.fargs+self.fopt_args:
                out.write(("" if i == 0 else " ")+self.atomic.get_tmp_name_for_generic(arg, "_"+str(args_no[i]))+("" if i+1 == len(self.fargs+self.fopt_args) else ","))
                i = i+1
            
            out.write(");\n\n")
        else:
            out.write("\n")
            
            
        out.write("    }\n")
        self.atomic.end_ifdefs(out)
        
   
atomic_functions = [
    ("store", [GenericType.C], [Type.memory_order, Type.memory_scope], None, False),
    ("load", [], [Type.memory_order, Type.memory_scope], GenericType.C, False),
    ("exchange", [GenericType.C], [Type.memory_order, Type.memory_scope], GenericType.C, False),
    
    ("fetch_add", [GenericType.M], [Type.memory_order, Type.memory_scope], GenericType.C, True),
    ("fetch_sub", [GenericType.M], [Type.memory_order, Type.memory_scope], GenericType.C, True),
    ("fetch_and", [GenericType.M], [Type.memory_order, Type.memory_scope], GenericType.C, True),
    ("fetch_or", [GenericType.M], [Type.memory_order, Type.memory_scope], GenericType.C, True),
    ("fetch_xor", [GenericType.M], [Type.memory_order, Type.memory_scope], GenericType.C, True),
    
    ("compare_exchange_strong", [GenericType.C_ref, GenericType.C], [], Type.bool, False),
    ("compare_exchange_strong", [GenericType.C_ref, GenericType.C, Type.memory_order, Type.memory_order], [Type.memory_scope], Type.bool, False),
    ("compare_exchange_weak", [GenericType.C_ref, GenericType.C], [], Type.bool, False),
    ("compare_exchange_weak", [GenericType.C_ref, GenericType.C, Type.memory_order, Type.memory_order], [Type.memory_scope], Type.bool, False)
]

files = {}

def make_header(file, neg):
    file.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify\n")
    file.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -emit-llvm -o - -cl-fp64-enable -Dcl_khr_int64_base_atomics -Dcl_khr_int64_extended_atomics\n")
    if (neg == False):
        file.write("// expected-no-diagnostics\n\n")
    else:
        file.write("// XFAIL: *\n\n")

    file.write("#include <opencl_atomic>\nusing namespace cl;\n\n")
    file.write("kernel void worker()\n{\n")
    
def make_footer(file):
    file.write("}\n")

def open_file(atomic, test_type, suffix = ""):
    filename = "TestBasicAtomic"+("_"+test_type if test_type != "" else "")+("" if atomic == None else "_"+atomic.get_short_name())+suffix+".cl"
    if (filename not in files):
        try:
            files[filename] = open(filename, "w+")
        except IOError:
            sys.exit(2)
            
        make_header(files[filename], suffix == "_neg")
    
    return files[filename]

def generate_atomic_test_cases():
    #declarations
    
    decl_ok_file = open_file(None, "Declaration")
    decl_neg_file = open_file(None, "Declaration", "_neg")
    
    atomics = []
    for type in Type:
        if (type == Type.memory_order):
            break
        atomic = Atomic(type, False)
        atomic_ptr = Atomic(type, True)
        atomics.append(atomic)
        atomics.append(atomic_ptr)
        
    for atom in atomics:
        if (not atom.is_valid()):
            atom.print_ifdefs(decl_neg_file)
            decl_neg_file.write("    "+atom.make_declaration()+"\n")
            atom.end_ifdefs(decl_neg_file)
            continue
            
        atom.print_ifdefs(decl_ok_file)
        decl_ok_file.write("    "+atom.make_declaration()+"\n")
        atom.end_ifdefs(decl_ok_file)
        
        for name, args, opt_args, rettype, arithm in atomic_functions:
            call = AtomicFunctionCall(atom, name, args, opt_args, rettype, arithm)
            out = None
            if (call.is_valid()):
                out = open_file(atom, name)
            else:
                out = open_file(atom, name, "_neg")
                
            call.spawn_call(out)
    
    for name,f in files.items():
        make_footer(f)
        f.close()
    
try:
    generate_atomic_test_cases()
except:
    sys.exit(-1) #unhandled exception
    

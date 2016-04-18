import sys;

try:
    import itertools
    from enum import IntEnum
except ImportError:
    sys.exit(1)

class ChannelType(IntEnum):
    void = 0
    float = 1
    half = 2
    double = 3
    int = 4
    char = 5
    short = 6
    long = 7
    uint = 8
    uchar = 9
    ushort = 10
    ulong = 11
    bool = 12
    size_t = 13
    
class Type:
    def __init__(self, channel, channels, ptr=False):
        self.type = channel
        self.channels = channels
        self.ptr = ptr

    def make(self):
        postfix = "*" if self.ptr else ""
        if (self.channels == 1):
            return self.type.name + postfix
            
        return self.type.name + str(self.channels) + postfix
        
    def makeDummyValue(self):
        if (self.ptr == True):
            return "static_cast<" + self.make() + ">(nullptr)"
            
        ret = self.make() + "{ "
        for i in range(0,self.channels):
            ret += "0"
            if (i+1 < self.channels):
                ret += ", "
                
        return ret+" }"
        
    def transform(self, type):
        return self
        
Type.void = Type(ChannelType.void, 1)
Type.size_t = Type(ChannelType.size_t, 1)

class ChannelsWrapper:
    def __init__(self, channels):
        self.channels = channels
        
    def make(self):
        return str(self.channels)
        
class TypeTransformation:
    def __init__(self, impl, args = []):
        self.chain = None
        self.args = args
        self.impl = impl
        
    def transform(self, type):
        type = self.impl(type, *self.args)
        if (self.chain):
            type = self.chain.transform(type)
            
        return type
        
    def glue(self, next_transform):
        old = self.chain
        self.chain = next_transform
        if (old != None):
            self.chain.glue(old)
            
        return self

    @staticmethod
    def make_scalar():
        return TypeTransformation(lambda orig: Type(orig.type, 1))
        
    @staticmethod
    def make_ptr():
        return TypeTransformation(lambda orig: Type(orig.type, orig.channels, True))
        
    @staticmethod
    def replace(old_type, new_type):
        return TypeTransformation(lambda orig, old, new: new if orig == old else orig, [old_type, new_type])
        
    @staticmethod
    def set_channel(new_channel):
        return TypeTransformation(lambda orig, new: Type(new, orig.channels, orig.ptr), [new_channel])
        
    @staticmethod
    def replace_channel(replace_map):
        return TypeTransformation(lambda orig, map: Type(map[orig.type], orig.channels, orig.ptr) if orig.type in map else orig, [replace_map])
        
    @staticmethod
    def replace_size(replace_map):
        return TypeTransformation(lambda orig, map: Type(orig.type, map[orig.channels], orig.ptr) if orig.channels in map else orig, [replace_map])
        
TypeTransformation.T = TypeTransformation(lambda orig: orig)
TypeTransformation.T_SCALAR = TypeTransformation.make_scalar()
TypeTransformation.T_PTR = TypeTransformation.make_ptr()
TypeTransformation.T_SCALAR_PTR = TypeTransformation.make_scalar().glue(TypeTransformation.make_ptr())
TypeTransformation.SCALAR_PTR = TypeTransformation.make_scalar().glue(TypeTransformation.make_ptr())
TypeTransformation.BOOLEAN = TypeTransformation.set_channel(ChannelType.bool)
TypeTransformation.BOOLEAN_SCALAR = TypeTransformation.set_channel(ChannelType.bool).glue(TypeTransformation.make_scalar())
TypeTransformation.BOOLEAN_PTR = TypeTransformation.set_channel(ChannelType.bool).glue(TypeTransformation.make_ptr())
TypeTransformation.INT = TypeTransformation.set_channel(ChannelType.int)
TypeTransformation.INT_SCALAR = TypeTransformation.set_channel(ChannelType.int).glue(TypeTransformation.make_scalar())
TypeTransformation.INT_PTR = TypeTransformation.set_channel(ChannelType.int).glue(TypeTransformation.make_ptr())
TypeTransformation.FP_WITH_SIZE = TypeTransformation.replace_channel({ ChannelType.ushort: ChannelType.half,
                                 ChannelType.uint: ChannelType.float,
                                 ChannelType.ulong: ChannelType.double })
TypeTransformation.UNSIGNED = TypeTransformation.replace_channel({ ChannelType.char: ChannelType.uchar,
                             ChannelType.short: ChannelType.ushort,
                             ChannelType.int: ChannelType.uint,
                             ChannelType.long: ChannelType.ulong })
TypeTransformation.SIGNED = TypeTransformation.replace_channel({ ChannelType.uchar: ChannelType.char,
                           ChannelType.ushort: ChannelType.short,
                           ChannelType.uint: ChannelType.int,
                           ChannelType.ulong: ChannelType.long })
                           
TypeTransformation.UPPER = TypeTransformation.replace_channel({ ChannelType.char: ChannelType.short,
                          ChannelType.uchar: ChannelType.ushort,
                          ChannelType.short: ChannelType.int,
                          ChannelType.ushort: ChannelType.uint,
                          ChannelType.int: ChannelType.long,
                          ChannelType.uint: ChannelType.ulong })
                          
TypeTransformation.GET_CHANNELS = TypeTransformation(lambda type: ChannelsWrapper(type.channels))
                              
def getTypes(channel_types_list, channels_counts_list):
    ret = []
    for e in itertools.product(channel_types_list, channels_counts_list):
        ret.append(Type(e[0], e[1]))
        
    return ret
    
    
any_fp = getTypes([ChannelType.float, ChannelType.half, ChannelType.double], [1, 2, 3, 4, 8, 16])
vector_fp = getTypes([ChannelType.float, ChannelType.half, ChannelType.double], [2, 3, 4, 8, 16])
any_integer = getTypes([ChannelType.char, ChannelType.short, ChannelType.int, ChannelType.long, ChannelType.uchar, ChannelType.ushort, ChannelType.uint, ChannelType.ulong], [1, 2, 3, 4, 8, 16])
any_float = getTypes([ChannelType.float], [1, 2, 3, 4, 8, 16])

vector_half = getTypes([ChannelType.half], [2, 3, 4, 8, 16])
any_half = vector_half+[Type(ChannelType.half, 1)]

any_geometric = getTypes([ChannelType.float, ChannelType.half, ChannelType.double], [1, 2, 3, 4])
any_boolean = getTypes([ChannelType.bool], [1, 2, 3, 4, 8, 16])
any = any_fp+any_integer
any_vector = [t for t in any if t.channels != 1]
    
class FunctionProto:
    def __init__(self, header_name, acceptable_types, rettype, fname, args, explicit_template = None, require_half_extension = True):
        self.header_name = header_name
        self.acceptable_types = acceptable_types
        self.rettype = rettype
        self.fname = fname
        self.args = args
        self.explicit_template = explicit_template
        self.req_fp16 = require_half_extension
        
    def make(self, out):
        tidx = 0
        out.write("  {\n")
        for t in self.acceptable_types:            
            types = [self.rettype.transform(t).type]
            for a in self.args:
                types.append(a.transform(t).type)
                
            needs_half = (ChannelType.half in types and self.req_fp16)
            needs_double = (ChannelType.double in types)
            
            if (needs_half and needs_double):
                out.write("#if defined(cl_khr_fp16) && defined(cl_khr_fp64)\n")
            elif (needs_half):
                out.write("#ifdef cl_khr_fp16\n")
            elif (needs_double):
                out.write("#ifdef cl_khr_fp64\n")
            
            out.write("    ")
            rt = self.rettype.transform(t)
            if (rt.type != ChannelType.void):
                out.write(rt.make()+" result"+str(tidx)+" = ")
                
            out.write(self.fname)
            if (self.explicit_template != None):
                out.write("<"+self.explicit_template.transform(t).make()+">")
            out.write("(")
            
            aidx = 0
            for a in self.args:
                out.write(a.transform(t).makeDummyValue())
                aidx = aidx+1
                if (aidx < len(self.args)):
                    out.write(", ")
                    
            out.write(");\n")
            
            if (needs_double or needs_half):
                out.write("#endif\n")
            
            tidx = tidx+1
            
        out.write("  }\n")

functions = [
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "acos", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "acosh", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "acospi", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "asin", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "asinh", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "asinpi", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "atan", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "atan2", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "atanh", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "atanpi", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "atan2pi", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "cbrt", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "ceil", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "copysign", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "cos", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "cosh", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "cospi", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "erfc", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "erf", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "exp", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "exp2", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "exp10", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "expm1", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "fabs", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "fdim", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "floor", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "fma", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "fmax", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], vector_fp, TypeTransformation.T, "fmax", [TypeTransformation.T, TypeTransformation.T_SCALAR]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "fmin", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], vector_fp, TypeTransformation.T, "fmin", [TypeTransformation.T, TypeTransformation.T_SCALAR]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "fmod", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "fract", [TypeTransformation.T, TypeTransformation.T_PTR]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "frexp", [TypeTransformation.T, TypeTransformation.INT_PTR]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "hypot", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.INT, "ilogb", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "ldexp", [TypeTransformation.T, TypeTransformation.INT]),
    FunctionProto(["opencl_math"], vector_fp, TypeTransformation.T, "ldexp", [TypeTransformation.T, TypeTransformation.INT_SCALAR]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "lgamma", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "lgamma_r", [TypeTransformation.T, TypeTransformation.INT_PTR]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "log", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "log2", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "log10", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "log1p", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "logb", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "mad", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "maxmag", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "minmag", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "modf", [TypeTransformation.T, TypeTransformation.T_PTR]),
    FunctionProto(["opencl_math"], getTypes([ChannelType.ushort, ChannelType.uint, ChannelType.ulong], [1, 2, 3, 4, 8, 16]), TypeTransformation.FP_WITH_SIZE, "nan", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "nextafter", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "pow", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "pown", [TypeTransformation.T, TypeTransformation.INT]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "powr", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "remainder", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "remquo", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.INT_PTR]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "rint", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "rootn", [TypeTransformation.T, TypeTransformation.INT]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "round", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "rsqrt", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "sin", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "sinh", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "sinpi", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "sqrt", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "tan", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "tanh", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "tanpi", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "tgamma", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_fp, TypeTransformation.T, "trunc", [TypeTransformation.T]),
    
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::cos", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::divide", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::exp", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::exp2", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::exp10", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::log", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::log2", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::log10", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::powr", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::recip", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::rsqrt", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::sin", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::sqrt", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "native_math::tan", [TypeTransformation.T]),
    
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::cos", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::divide", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::exp", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::exp2", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::exp10", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::log", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::log2", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::log10", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::powr", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::recip", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::rsqrt", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::sin", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::sqrt", [TypeTransformation.T]),
    FunctionProto(["opencl_math"], any_float, TypeTransformation.T, "half_math::tan", [TypeTransformation.T]),
    
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.UNSIGNED, "abs", [TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.UNSIGNED, "abs_diff", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "add_sat", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "hadd", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "rhadd", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer", "opencl_common"], any_integer, TypeTransformation.T, "clamp", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
   #FunctionProto(["opencl_integer", "opencl_common"], any_integer, TypeTransformation.T, "clamp", [TypeTransformation.T, TypeTransformation.SIGNED, TypeTransformation.SIGNED]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "clz", [TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "ctz", [TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "mad_hi", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "mad_sat", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer", "opencl_common"], any_integer, TypeTransformation.T, "max", [TypeTransformation.T, TypeTransformation.T]),
    #FunctionProto["opencl_integer", "opencl_common"], (any_integer, TypeTransformation.T, "max", [TypeTransformation.T, TypeTransformation.SIGNED]),
    FunctionProto(["opencl_integer", "opencl_common"], any_integer, TypeTransformation.T, "min", [TypeTransformation.T, TypeTransformation.T]),
   #FunctionProto(["opencl_integer", "opencl_common"], any_integer, TypeTransformation.T, "min", [TypeTransformation.T, TypeTransformation.SIGNED]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "mul_hi", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "rotate", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "sub_sat", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], getTypes([ChannelType.char, ChannelType.short, ChannelType.int], [1, 2, 3, 4, 8, 16]), TypeTransformation.UPPER, "upsample", [TypeTransformation.T, TypeTransformation.UNSIGNED]),
    FunctionProto(["opencl_integer"], getTypes([ChannelType.uchar, ChannelType.ushort,ChannelType.uint], [1, 2, 3, 4, 8, 16]), TypeTransformation.UPPER, "upsample", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], any_integer, TypeTransformation.T, "popcount", [TypeTransformation.T]),
    FunctionProto(["opencl_integer"], getTypes([ChannelType.int, ChannelType.uint], [1, 2, 3, 4, 8, 16]), TypeTransformation.T, "mad24", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_integer"], getTypes([ChannelType.int, ChannelType.uint], [1, 2, 3, 4, 8, 16]), TypeTransformation.T, "mul24", [TypeTransformation.T, TypeTransformation.T]),
    
    
    FunctionProto(["opencl_common", "opencl_integer"], any_fp, TypeTransformation.T, "clamp", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_common", "opencl_integer"], any_fp, TypeTransformation.T, "clamp", [TypeTransformation.T, TypeTransformation.T_SCALAR, TypeTransformation.T_SCALAR]),
    FunctionProto(["opencl_common"], any_fp, TypeTransformation.T, "degrees", [TypeTransformation.T]),
    FunctionProto(["opencl_common", "opencl_integer"], any_fp, TypeTransformation.T, "max", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_common", "opencl_integer"], any_fp, TypeTransformation.T, "max", [TypeTransformation.T, TypeTransformation.T_SCALAR]),
    FunctionProto(["opencl_common", "opencl_integer"], any_fp, TypeTransformation.T, "min", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_common", "opencl_integer"], any_fp, TypeTransformation.T, "min", [TypeTransformation.T, TypeTransformation.T_SCALAR]),
    FunctionProto(["opencl_common"], any_fp, TypeTransformation.T, "mix", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_common"], any_fp, TypeTransformation.T, "radians", [TypeTransformation.T]),
    FunctionProto(["opencl_common"], any_fp, TypeTransformation.T, "step", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_common"], any_fp, TypeTransformation.T, "step", [TypeTransformation.T_SCALAR, TypeTransformation.T]),
    FunctionProto(["opencl_common"], any_fp, TypeTransformation.T, "smoothstep", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_common"], any_fp, TypeTransformation.T, "smoothstep", [TypeTransformation.T_SCALAR, TypeTransformation.T_SCALAR, TypeTransformation.T]),
    FunctionProto(["opencl_common"], any_fp, TypeTransformation.T, "sign", [TypeTransformation.T]),
    
    
    FunctionProto(["opencl_geometric"], getTypes([ChannelType.half, ChannelType.float, ChannelType.double], [3, 4]), TypeTransformation.T, "cross", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_geometric"], any_geometric, TypeTransformation.T_SCALAR, "dot", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_geometric"], any_geometric, TypeTransformation.T_SCALAR, "distance", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_geometric"], any_geometric, TypeTransformation.T_SCALAR, "length", [TypeTransformation.T]),
    FunctionProto(["opencl_geometric"], any_geometric, TypeTransformation.T, "normalize", [TypeTransformation.T]),
    
    
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isequal", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isnotequal", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isgreater", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isgreaterequal", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isless", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "islessequal", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "islessgreater", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isfinite", [TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isinf", [TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isnan", [TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isnormal", [TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isordered", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "isunordered", [TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_fp, TypeTransformation.BOOLEAN, "signbit", [TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_boolean, TypeTransformation.T_SCALAR, "any", [TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any_boolean, TypeTransformation.T_SCALAR, "all", [TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any, TypeTransformation.T, "bitselect", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.T]),
    FunctionProto(["opencl_relational"], any, TypeTransformation.T, "select", [TypeTransformation.T, TypeTransformation.T, TypeTransformation.BOOLEAN]),
    
    
    FunctionProto(["opencl_vector_load_store"], any_vector, TypeTransformation.T, "vload", [Type.size_t, TypeTransformation.T_SCALAR_PTR], TypeTransformation.GET_CHANNELS),
    FunctionProto(["opencl_vector_load_store"], any_vector, Type.void, "vstore", [TypeTransformation.T, Type.size_t, TypeTransformation.T_SCALAR_PTR]),
    FunctionProto(["opencl_vector_load_store"], any_half, TypeTransformation.replace_channel({ ChannelType.half: ChannelType.float }), "vload_half", [Type.size_t, TypeTransformation.T_SCALAR_PTR], TypeTransformation.GET_CHANNELS, False),
    FunctionProto(["opencl_vector_load_store"], any_half, Type.void, "vstore_half", [TypeTransformation.replace_channel({ ChannelType.half: ChannelType.float }), Type.size_t, TypeTransformation.T_SCALAR_PTR], None, False),
    FunctionProto(["opencl_vector_load_store"], any_half, Type.void, "vstore_half", [TypeTransformation.replace_channel({ ChannelType.half: ChannelType.double }), Type.size_t, TypeTransformation.T_SCALAR_PTR], None, False),
    FunctionProto(["opencl_vector_load_store"], vector_half, TypeTransformation.set_channel(ChannelType.float), "vloada_half", [Type.size_t, Type(ChannelType.half, 1, True)], TypeTransformation.GET_CHANNELS, False),
    FunctionProto(["opencl_vector_load_store"], vector_half, Type.void, "vstorea_half", [TypeTransformation.set_channel(ChannelType.float), Type.size_t, Type(ChannelType.half, 1, True)], None, False),
    FunctionProto(["opencl_vector_load_store"], vector_half, Type.void, "vstorea_half", [TypeTransformation.set_channel(ChannelType.double), Type.size_t, Type(ChannelType.half, 1, True)], None, False)
]

files = {}

def make_header(file, headers, neg):
    file.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify -o /dev/null\n")
    file.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-fp16-enable -cl-std=c++ -fsyntax-only -pedantic -verify -o /dev/null\n")
    file.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-fp64-enable -cl-std=c++ -fsyntax-only -pedantic -verify -o /dev/null\n")
    file.write("// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-fp16-enable -cl-fp64-enable -cl-std=c++ -fsyntax-only -pedantic -verify -o /dev/null\n")
    if (neg == False):
        file.write("// expected-no-diagnostics\n\n")
    else:
        file.write("// XFAIL: *\n\n")

    for h in headers:
        file.write("#include <" + h + ">\n")
    if len(headers) > 1:
        file.write("\n")

    file.write("using namespace cl;\n\n")
    file.write("kernel void worker()\n{\n")
    
def make_footer(file):
    file.write("}\n")

def open_file(function, suffix = ""):
    filename = "TestBasicFunctions_"+function.fname.replace("::", "_")+suffix+".cl"
    if (filename not in files):
        try:
            files[filename] = open(filename, "w+")
        except IOError:
            sys.exit(2)
            
        make_header(files[filename], function.header_name, suffix == "_neg")
    
    return files[filename]

def generate_functions_test_cases():
    for f in functions:
        out = open_file(f)
        f.make(out)
        
    for name,f in files.items():
        make_footer(f)
        f.close()

try:
    generate_functions_test_cases()
except:
    sys.exit(-1) #unhandled exception

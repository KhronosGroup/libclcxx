#ifndef __OPENCL_NEW_DELETE
#define __OPENCL_NEW_DELETE

inline void* operator new(size_t _s, void *ptr) noexcept {
    return ptr;
}

inline void* operator new[](size_t _s, void *ptr) noexcept {
    return ptr;
}

// Clang doesn't compile this yet due to a bug:  llvm.org/PR50736
// void operator delete(void*, void*){

// }

// void operator delete[](void*, void*){

// }

#endif /* !__OPENCL_NEW_DELETE -> define __OPENCL_NEW_DELETE */

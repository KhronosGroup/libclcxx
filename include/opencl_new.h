inline void* operator new(size_t _s, void *ptr) noexcept {
    return ptr;
}

inline void* operator new[](size_t _s, void *ptr) noexcept {
    return ptr;
}

// Clang doesn't compile this yet due to a bug
// void operator delete(void*, void*){

// }

// void operator delete[](void*, void*){

// }
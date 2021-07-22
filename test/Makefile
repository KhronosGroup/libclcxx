# To run: make PATH_TO_LIBCXX_INCLUDE=<Path to libc++ library>
# If needed, to pass extra flags use: EXTRA_FLAGS=<other flags>
CLANG_PATH ?= clang
libcxx_include = -I${PATH_TO_LIBCXX_INCLUDE}
test-all: *.bc

*.bc: *.clcpp
	${CLANG_PATH} ${EXTRA_ARGS} ${libcxx_include} -c *.clcpp --target=spir -emit-llvm

clean:
	rm *.bc


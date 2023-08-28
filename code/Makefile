all:
	make debug

run:
	devour build/main

dbg:
	cgdb build/main

default:
	cmake -B build -G Ninja . && cmake --build build && build/main

profile:
	cmake -B build -G Ninja -DCMAKE_CXX_FLAGS="-O0 -pg" -DCMAKE_EXE_LINKER_FLAGS="-g" . && cmake --build build && cd build && ./main
	cd build && gprof main gmon.out | gprof2dot | dot -Tpdf -o output.pdf

debug:
	cmake -B build -G Ninja -DCMAKE_CXX_FLAGS="-O0 -g" -DCMAKE_EXE_LINKER_FLAGS="-g" . && cmake --build build

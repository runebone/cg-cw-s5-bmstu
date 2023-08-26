all:
	make dbg

run:
	build/main

default:
	mkdir -p build
	cd build && cmake .. && make && ./main

profile:
	mkdir -p build
	cd build && cmake -DCMAKE_CXX_FLAGS="-O0 -pg" .. && make && ./main
	cd build && gprof main gmon.out | gprof2dot | dot -Tpdf -o output.pdf

fast:
	mkdir -p build
	cd build && cmake -DCMAKE_CXX_FLAGS="-O3" .. && make && ./main

fp:
	mkdir -p build
	cd build && cmake -DCMAKE_CXX_FLAGS="-O3 -pg" .. && make && ./main
	cd build && gprof main gmon.out | gprof2dot -s -w | dot -Tpdf -o output.pdf

dbg:
	mkdir -p build
	cd build && cmake -DCMAKE_CXX_FLAGS="-g" -DCMAKE_EXE_LINKER_FLAGS="-g" .. && make

all:
	mkdir -p build
	cd build && cmake .. && make && ./main

profile:
	mkdir -p build
	cd build && cmake -DCMAKE_CXX_FLAGS="-O0 -pg" .. && make && ./main
	cd build && gprof main gmon.out | gprof2dot -s -w | dot -Tpng -o output.png

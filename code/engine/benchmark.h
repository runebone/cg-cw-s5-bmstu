#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <fstream>

namespace bm {
    long get_cpu_time_ns();
    void log();
    void createCubeOfCubes(int n);
    void createPlaneOfCubes(int n);
    void createLineOfCubes(int n);

    extern std::ofstream logfile;
}

#endif // __BENCHMARK_H__

#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

namespace bm {
    long get_cpu_time_ns();
    void log();
    void createCubeOfCubes(int n);
    void createPlaneOfCubes(int n);
    void createLineOfCubes(int n);
}

#endif // __BENCHMARK_H__

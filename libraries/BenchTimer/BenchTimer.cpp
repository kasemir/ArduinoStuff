// Benchmark timer
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#include "BenchTimer.h"

long BenchTimer::runtimeMicros()
{
    return end_micros - start_micros;
}
 
const char *BenchTimer::info(long runs)
{
    long mics = runtimeMicros();
    // Round 'up'
    long runs_per_second = (long) ((runs * 1000000.0) / mics + 0.5);
    sprintf(bench_info,
       "%ld runs in %ld us: %ld runs/second",
       runs, mics, runs_per_second);
    return bench_info;
}


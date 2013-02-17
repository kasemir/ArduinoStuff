// Benchmark timer
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#include <Arduino.h>

class BenchTimer
{
    char bench_info[100];
    long start_micros;
    long end_micros;
public:
    /** Initialize (and start) */ 
    BenchTimer()
    {
        start();
    }
    
    /** Start the timer */ 
    void start()
    {
        start_micros = micros();
    }

    /** Stop the timer */
    void stop()
    {
        end_micros = micros();
    }
    
    /** @return Runtime in microseconds */ 
    long runtimeMicros();

    /** Provide user-readable info:
     *  @param runs Number of runs
     *  @return ".. runs in .. : .. runs/second"
     */
     const char *info(long runs);
};



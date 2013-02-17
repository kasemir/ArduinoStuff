// Benchmark timer
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#include "BenchTimer.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("BenchTimer Demo");
}

void loop()
{
    // Timer starts automatically
    BenchTimer timer;
    int runs = random(1, 10);
    for (int i=0; i<runs; ++i)
        delay(100);
    timer.stop();
    Serial.println(timer.info(runs));

    // Re-use timer
    timer.start();
    runs = random(1, 10);
    for (int i=0; i<runs; ++i)
        delay(50);
    timer.stop();
    Serial.print("Runtime: ");
    Serial.print(timer.runtimeMicros());
    Serial.println(" usec");
    Serial.println(timer.info(runs));
}

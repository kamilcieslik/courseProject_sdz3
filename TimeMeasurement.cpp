//
// Created by mrfarinq on 22.05.17.
//

#include "TimeMeasurement.h"

TimeMeasurement::TimeMeasurement() {

}

TimeMeasurement::~TimeMeasurement() {

}

void TimeMeasurement::TimeStart() {
    timeStart = Clock::now();
}

void TimeMeasurement::TimeStop() {
    timeStop = Clock::now();
}

double TimeMeasurement::GetTimeInSeconds() {
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
            timeStop - timeStart);
    return time_span.count();
}

const std::string TimeMeasurement::currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    
    return buf;
}








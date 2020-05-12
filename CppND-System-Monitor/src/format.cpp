#include <string>
#include <iostream> // debug
#include <sstream>
#include <iomanip> // std::setw

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)
{
    const int hourInSec = 3600;
    const int minInSec = 60;
    int hour = 0;
    int min = 0;
    int sec = 0;

    // computing the time for the HH:MM:SS format
    hour = seconds/hourInSec;
    min = (seconds - (hour * hourInSec))/minInSec;
    sec = (seconds - (hour * hourInSec)) - (min * minInSec);

    std::stringstream timeStream;

    timeStream << std::setfill('0') << std::setw(1) << hour << ":";
    timeStream << std::setfill('0') << std::setw(1) << min << ":";
    timeStream << std::setfill('0') << std::setw(1) << sec;

    return timeStream.str();
}

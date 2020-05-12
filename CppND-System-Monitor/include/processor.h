#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor
{
public:
    float Utilization();  // TODO: See src/processor.cpp

    // TODO: Declare any necessary private members
private:
    float m_actualTotalJiffs;
    float m_previousTotalJiffs;
    float m_idleJiffs;
    float m_actualUtilJiffs;
    float m_previousUtilJiffs;
    float m_cpuUtilization;

};

#endif

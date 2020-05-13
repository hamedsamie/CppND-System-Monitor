#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{

    // Initialization
    m_actualTotalJiffs = 0.0;
    m_idleJiffs = 0.0;
    m_actualTotalJiffs = 0;
    m_previousTotalJiffs = 0;
    m_previousUtilJiffs = 0;
    m_cpuUtilization = 0;
    std::vector<std::string> cpuJiffs = LinuxParser::CpuUtilization();

    for (unsigned i=0; i<cpuJiffs.size(); i++)
    {
        if (i!=LinuxParser::kGuest_ && i!=LinuxParser::kGuestNice_)
        {
            m_actualTotalJiffs += std::stof(cpuJiffs.at(i));
        }
        if (i==LinuxParser::kIdle_ || i==LinuxParser::kIOwait_)
        {
            m_idleJiffs += std::stof(cpuJiffs.at(i));
        }
    }
    m_actualUtilJiffs = m_actualTotalJiffs - m_idleJiffs;
    m_cpuUtilization = (m_actualUtilJiffs - m_previousUtilJiffs)/(m_actualTotalJiffs - m_previousTotalJiffs);
    m_previousTotalJiffs = m_actualTotalJiffs;
    m_previousUtilJiffs = m_actualUtilJiffs;

    return m_cpuUtilization;
}



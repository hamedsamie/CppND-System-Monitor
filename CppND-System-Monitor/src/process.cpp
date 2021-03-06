#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

//constructor
Process::Process(int pid)
{
    m_pid = pid;
    m_cpuUtilization = Process::CpuUtilization();
}


// TODO: Return this process's ID
int Process::Pid()
{
    return m_pid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    float totalTime = LinuxParser::ActiveJiffies(m_pid)/sysconf(_SC_CLK_TCK);
    float seconds = LinuxParser::UpTime(m_pid);
    float cpuUtilization = totalTime/seconds;
    return cpuUtilization;
}

// TODO: Return the command that generated this process
string Process::Command()
{
    return LinuxParser::Command(m_pid);
}

// TODO: Return this process's memory utilization
string Process::Ram()
{
    return LinuxParser::Ram(m_pid);
}

// TODO: Return the user (name) that generated this process
string Process::User()
{
    std::string user =LinuxParser::User(m_pid);
    return user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime()
{
    return LinuxParser::UpTime(m_pid);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const
{
    return m_cpuUtilization > a.m_cpuUtilization;
}



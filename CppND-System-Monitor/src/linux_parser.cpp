#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>


#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem()
{
    string line;
    string key;
    string value;
    std::ifstream filestream(kOSPath);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::replace(line.begin(), line.end(), ' ', '_');
            std::replace(line.begin(), line.end(), '=', ' ');
            std::replace(line.begin(), line.end(), '"', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value)
            {
                if (key == "PRETTY_NAME")
                {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        }
    }
    return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel()
{
    std::string os = "", version = "", kernel = "";
    std::string line = "";
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open())
    {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
    }
    return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids()
{
    vector<int> pids;
    DIR* directory = opendir(kProcDirectory.c_str());
    struct dirent* file;
    while ((file = readdir(directory)) != nullptr)
    {
        // Is this a directory?
        if (file->d_type == DT_DIR)
        {
            // Is every character of the name a digit?
            string filename(file->d_name);
            if (std::all_of(filename.begin(), filename.end(), isdigit))
            {
                int pid = stoi(filename);
                pids.push_back(pid);
            }
        }
    }
    closedir(directory);
    return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{
    std::string line = "";
    std::string memName = "";
    std::string memValue = "";
    float memTotal = 0.0;
    float memFree = 0.0;
    float memUtilization = 0.0;

    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            linestream >> memName;

            if (memName == "MemTotal")
            {
                linestream >> memValue;
                memTotal = std::stof(memValue);
            }

            if (memName == "MemFree")
            {
                linestream >> memValue;
                memFree = std::stof(memValue);
            }
        }
    }
    // computing the memory utilization percentage
    memUtilization = (memTotal - memFree)/memTotal;
    return (memTotal > 0) ? memUtilization : 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{
    std::string line = "";
    std::string upTime = "";

    std::ifstream filestream(kProcDirectory + kUptimeFilename);
    if (filestream.is_open())
    {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> upTime;
    }
    return (std::stol(upTime));
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies()
{
    std::string line = "";
    std::string cpu = "";
    std::string user = "", nice = "", system = "", idle = "", iOwait = "", irq = "", softIrq = "", steal = "", guest = "", guestNice = "";

    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open())
    {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iOwait >> irq >> softIrq >> steal >> guest >> guestNice;
    }

    return (std::stol(user) + std::stol(nice) + std::stol(system) + std::stol(idle) + std::stol(iOwait)) + std::stol(irq) + std::stol(softIrq) + std::stol(steal)+std::stol(guest) + std::stol(guestNice);
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid)
{
    std::string line ="", value = "";
    std::string uTime = "", sTime = "", cuTime = "", csTime = "";
    std::vector<std::string> statusList;


    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
    if (filestream.is_open())
    {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        while (linestream >> value)
        {
            statusList.push_back(value);
        }
    }
    // http://man7.org/linux/man-pages/man5/proc.5.html)
    uTime = statusList.at(13);
    sTime = statusList.at(14);
    cuTime = statusList.at(15);
    csTime = statusList.at(16);

    return (std::stol(uTime) + std::stol(sTime) + std::stol(cuTime) + std::stol(csTime));
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies()
{
    std::string line = "";
    std::string cpu = "";
    std::string user = "", nice = "", system = "", idle = "", iOwait = "", irq = "", softIrq = "", steal = "", guest = "", guestNice = "";

    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open())
    {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user>> nice >> system >> idle >> iOwait >> irq>> softIrq >> steal >> guest >> guestNice;
    }

    return (std::stol(user) + std::stol(nice) + std::stol(system) + std::stol(irq) + std::stol(softIrq) + std::stol(steal) + std::stol(guest) + std::stol(guestNice));
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies()
{
    std::string line = "";
    std::string cpu = "";
    std::string user = "", nice = "", system = "", idle = "", iOwait = "", irq = "", softIrq = "", steal = "", guest = "", guestNice = "";

    std::ifstream filestream(kProcDirectory+kStatFilename);
    if (filestream.is_open())
    {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user>> nice >> system >> idle >> iOwait >> irq>> softIrq >> steal >> guest >> guestNice;
    }

    return (std::stol(idle) + std::stol(iOwait));;
}

// TODO: Read and return CPU utilization
vector<std::string> LinuxParser::CpuUtilization()
{
    std::string line = "", key = "";
    vector<std::string> cpUJiffies;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open())
    {
        std::getline(stream, line);
        std::istringstream linestream(line);
        // seperating the "cpu" from the Jiffies Vector
        linestream >> key;;
        while (linestream >> key)
        {
            cpUJiffies.push_back(key);
        }
    }
    return cpUJiffies;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
    std::string line = "";
    std::string key = "";
    std::string value = "";
    int totalProcessNumber = 0;

    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            linestream >> key;
            if (key == "processes")
            {
                linestream >> value;
                totalProcessNumber = std::stoi(value);
            }
        }
    }
    return totalProcessNumber;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
    std::string line = "";
    std::string key = "";
    std::string value = "";
    int runningProcessNumber = 0;

    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            linestream >> key;
            if (key == "procs_running")
            {
                linestream >> value;
                runningProcessNumber = std::stoi(value);
            }
        }
    }
    return runningProcessNumber;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Command(int pid)
{
    std::string line = "";
    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
    if (filestream.is_open())
    {
        std::getline(filestream, line);
        filestream.close();
        return line;
    }
    return std::string();
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid)
{
    std::string key = "", value = "", line = "";
    int vmSize = 0;

    std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
    if (stream.is_open())
    {
        while (std::getline(stream, line))
        {
            std::istringstream linestream(line);
            linestream >> key;
            if (key == "VmSize:")
            {
                linestream >> value;
                vmSize = std::stoi(value)/1000;
            }
        }
    }
    return std::to_string(vmSize);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid)
{
    std::string line = "", key = "", value = "";

    std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            linestream >> key;
            if (key == "Uid:")
            {
                linestream >> value;
            }
        }
    }
    return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid)
{
    std::string user = "root"; // user by default
    std::string tempUser = "", passwd = "", uId = "", line = "";

    std::string parsedUserId = LinuxParser::Uid(pid);
    std::ifstream stream(kPasswordPath);
    if (stream.is_open())
    {
        while (std::getline(stream, line))
        {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> tempUser >> passwd >> uId)
            {
                if (uId == parsedUserId)
                {
                    user = tempUser;
                }
            }
        }
    }
    return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid)
{
    std::string value = "", line = "";
    std::vector<std::string> statusList;
    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
    if (filestream.is_open())
    {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        while (linestream >> value)
        {
            statusList.push_back(value);
        }
    }
    //http://man7.org/linux/man-pages/man5/proc.5.html) (22) starttime
    return LinuxParser::UpTime() - std::stol(statusList[21])/sysconf(_SC_CLK_TCK);;
}

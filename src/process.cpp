#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
{
    this->pid_ = pid;
}

int Process::Pid() { return this->pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    float activeJiffie = (float)LinuxParser::ActiveJiffies();
    float upTime = (float)LinuxParser::UpTime();
    float upTimePid = (float)LinuxParser::UpTime(this->pid_);
    float seconds = (upTime - upTimePid) / (float)sysconf(_SC_CLK_TCK);

    return (activeJiffie / (float)sysconf(_SC_CLK_TCK) / seconds);
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return (long int)LinuxParser::UpTime(this->pid_); }

bool Process::operator<(Process const &a) const
{
    long myRam = std::stol(LinuxParser::Ram(this->pid_));
    long otherRam = std::stol(LinuxParser::Ram(a.pid_));
    return  otherRam < myRam;
}
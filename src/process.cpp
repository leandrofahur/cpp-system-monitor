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

Process::Process(int pid) {
    this->pid_ = pid;
    this->user_ = LinuxParser::User(this->pid_);
    this->command_ = LinuxParser::Command(this->pid_);
}

int Process::Pid() { return this->pid_; }

float Process::CpuUtilization() {
    float jiffieStart, jiffieEnd, uptimeStart, upTimeEnd;
    
    // jiffieStart = (float)LinuxParser::Jiffies();
    // uptimeStart = (float)LinuxParser::UpTime(this->pid_);

    // unsigned int microsseconds = 10000;
    // usleep(microsseconds);

    // jiffieEnd = (float)LinuxParser::Jiffies();
    // upTimeEnd = (float)LinuxParser::UpTime(this->pid_);
    
    // return (jiffieEnd - jiffieStart)/(upTimeEnd - uptimeStart);
    return 0.0f;
}

string Process::Command() { return this->command_; }

string Process::Ram() { return LinuxParser::Ram(this->pid_); }

string Process::User() { return this->user_; }

long int Process::UpTime() { return LinuxParser::UpTime(this->pid_); }

bool Process::operator<(Process const& a) const { 
    long myRam = std::stol(LinuxParser::Ram(this->pid_));
    long otherRam = std::stol(LinuxParser::Ram(a.pid_));
    return myRam > otherRam; 
    return false;
}
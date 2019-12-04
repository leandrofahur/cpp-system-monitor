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

int Process::Pid() { return 0; } //{ return this->pid_; }

float Process::CpuUtilization() {
    // long jiffieStart, jiffieEnd, uptimeStart, upTimeEnd;
    
    // jiffieStart = LinuxParser::Jiffies();
    // uptimeStart = LinuxParser::UpTime(this->pid_);

    // unsigned int microsseconds = 10000;
    // usleep(microsseconds);

    // jiffieEnd = LinuxParser::Jiffies();
    // upTimeEnd = LinuxParser::UpTime(this->pid_);

    //return (jiffieEnd - jiffieStart)/(upTimeEnd - uptimeStart);

    return 0;
}

string Process::Command() { return string(); }

string Process::Ram() { return string(); }//{ return LinuxParser::Ram(this->pid_); }

string Process::User() { return string(); }//{ return this->user_; }

long int Process::UpTime() { //return LinuxParser::UpTime(this->pid_);
return 0; }

bool Process::operator<(Process const& a) const { 
    // long myRam = std::stol(LinuxParser::Ram(this->pid_));
    // long otherRam = std::stol(LinuxParser::Ram(a.pid_));
    // return myRam > otherRam; 
    return false;
}
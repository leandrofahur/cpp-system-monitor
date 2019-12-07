#include <dirent.h>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <vector>

#include "linux_parser.h"

// using std::stof;
// using std::string;
// using std::to_string;
// using std::vector;

// DONE: An example of how to read data from the filesystem
std::string LinuxParser::OperatingSystem()
{
  std::string line;
  std::string key;
  std::string value;
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
std::string LinuxParser::Kernel()
{
  std::string os, version, kernel;
  std::string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return (version + ' ' + kernel);
}

// BONUS: Update this to use std::filesystem
std::vector<int> LinuxParser::Pids()
{
  std::vector<int> pids;
  DIR *directory = opendir(kProcDirectory.c_str());
  struct dirent *file;
  while ((file = readdir(directory)) != nullptr)
  {
    // Is this a directory?
    if (file->d_type == DT_DIR)
    {
      // Is every character of the name a digit?
      std::string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit))
      {
        int pid = std::stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization()
{
  std::string line, key, value;
  float memTotal, memFree;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open())
  {
    while (std::getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineStream(line);
      while (lineStream >> key >> value)
      {
        ;
        if (key == "MemTotal")
        {
          memTotal = std::stof(value);
        }
        if (key == "MemFree")
        {
          memFree = std::stof(value);
          break;
        }
      }
    }
  }
  return (memTotal - memFree) / memTotal;
}

long LinuxParser::UpTime()
{
  std::string line, value;
  long seconds;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream lineStream(line);
    lineStream >> value;
    seconds = std::stol(value);
  }
  return seconds;
}

long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
std::vector<std::string> LinuxParser::CpuUtilization() { return {}; }

int LinuxParser::TotalProcesses()
{
  std::string line, key, value;
  int totalProcesses{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "processes")
        {
          totalProcesses = std::stoi(value);
          return totalProcesses;
        }
      }
    }
  }
  return totalProcesses;
}

int LinuxParser::RunningProcesses()
{
  std::string line, key, value;
  int runningProcesses{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "procs_running")
        {
          runningProcesses = std::stoi(value);
          return runningProcesses;
        }
      }
    }
  }
  return runningProcesses;
}

std::string LinuxParser::Command(int pid)
{
  std::string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    if (line == "")
    {
      return "None";
    }
    return line;
  }
}

std::string LinuxParser::Ram(int pid)
{
  std::string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "VmSize")
        {
          std::stringstream ram;
          ram << std::fixed << std::setprecision(3) << stof(value) / 1000;
          return ram.str();
        }
      }
    }
  }
  return std::to_string(0);
}

std::string LinuxParser::Uid(int pid)
{
  std::string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "Uid")
        {
          return value;
        }
      }
    }
  }
  return std::string("");
}

std::string LinuxParser::User(int pid)
{
  std::string line, key, value, uid;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> uid)
      {
        if (uid == LinuxParser::Uid(pid))
        {
          return key;
          break;
        }
      }
    }
  }
  return std::string();
}

long LinuxParser::UpTime(int pid[[maybe_unused]]) { 
  std::string line, value;
  std::vector<std::string> buffer;
  long time = 0;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::stringstream sstream(line);
    while (std::getline(sstream, line, ' ')) {
      buffer.push_back(line);  // std::cout << line << std::endl;
    }
    if (buffer.size() > 0) {
      time = std::stol(buffer[21]) / sysconf(_SC_CLK_TCK);
      return time;
    }
  }
  return 0l;
}
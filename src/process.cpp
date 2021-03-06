#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using namespace LinuxParser;
using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() const { return this->pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const {
  vector<float> cpu_time = LinuxParser::CpuUtilization(Pid());
  float total_time;
  total_time = cpu_time[0] + cpu_time[1] + cpu_time[2] + cpu_time[3];
  long uptime = LinuxParser::UpTime();
  float seconds = uptime - (cpu_time[4] / sysconf(_SC_CLK_TCK));
  float cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) / seconds;
  return cpu_usage;
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// Return the age of this process (in seconds)
long int Process::UpTime() {
  return LinuxParser::UpTime() - LinuxParser::UpTime(Pid());
}

// Overload the "less than" comparison operator for Process object
bool Process::operator<(Process const& a) const {
  return CpuUtilization() > a.CpuUtilization();
}
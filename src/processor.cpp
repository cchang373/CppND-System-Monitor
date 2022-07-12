#include "processor.h"
#include "linux_parser.h"
#include <sstream>
#include <string>

using namespace LinuxParser;
using std::string;
using std::stof;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
     string line;
     string key;
     string user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
     float non_idle_time, idle_time, total_time;
     float total_d, idle_d;
     std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
     if (filestream.is_open()) {
         std::getline(filestream, line);
         std::istringstream linestream(line);
         linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
         if (key == "cpu") {
            non_idle_time = stof(user) + stof(nice) +stof(system) + stof(irq) + stof(softirq) + stof(steal);
            idle_time = stof(idle) + stof(iowait);
            total_time = non_idle_time + idle_time;
            
            total_d = total_time - this->PrevTotal;
            idle_d = idle_time - this->PrevIdle;

            this->PrevIdle = idle_time;
            this->PrevTotal = total_time;
            return (total_d - idle_d) / total_d;
         }
     }
}
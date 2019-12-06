#include <unistd.h>

#include "processor.h"
#include "linux_parser.h"



// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
        
    jiffies = (float)LinuxParser::Jiffies();
    activeJiffies = (float)LinuxParser::ActiveJiffies();

    float JiffiesDiff = jiffies - prevJiffies;
    float activeJiffiesDiff = activeJiffies - prevActiveJiffies;

    if(prevJiffies == 0 && prevActiveJiffies == 0) {
        prevJiffies = jiffies;
        prevActiveJiffies = activeJiffies;
    }

    return (activeJiffiesDiff / JiffiesDiff);
}
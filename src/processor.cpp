#include <unistd.h>

#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    
    jiffiesStart = (float)LinuxParser::Jiffies();
    activeJiffiesStart = (float)LinuxParser::ActiveJiffies();

    unsigned int microsseconds = 1000000;
    usleep(microsseconds);

    jiffiesEnd = (float)LinuxParser::Jiffies();
    activeJiffiesEnd = (float)LinuxParser::ActiveJiffies();


    if((activeJiffiesEnd - activeJiffiesStart) <= 0) {
        return 0.0f;
    } 

    return ((jiffiesEnd - jiffiesStart)/(activeJiffiesEnd - activeJiffiesStart))*0.01;
}
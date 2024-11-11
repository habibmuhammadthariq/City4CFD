#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

class Process {
    public:
        std::string StartProcess(std::string configPath, std::string outputDir, std::string filename);
};

#endif
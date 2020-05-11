#include "Logger.h"

std::ofstream Logger::file;

Logger::Logger() {
    time_t now = time(0);
    std::string dt = string(ctime(&now));
    std::string name = string(FILE_FOLDER) + "log_file_" + dt + ".txt";
    file.open(name, ios::out | ios::app);
    
    file << "Welcome to my log file \n \n";
    file.flush();
}

Logger::~Logger() {
    if(file.is_open()) {
        file.flush();
        file.close();
    }
}

void Logger::writeToLogFile(std::string msg) {
    if(file.is_open()) {
        file << msg + "\n";
        file.flush();
    }
    
}

void Logger::closeFileInThisScope() {
    if(file.is_open()) {
        file.close();
    }

}
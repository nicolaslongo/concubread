#ifndef LOGGER_H_
#define LOGGER_H_

#define EOL " \n"
#define FILE_FOLDER "logfiles/"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex>          // std::mutex, std::lock
using namespace std;

class Logger {

    private:
        static std::ofstream file;

    protected:

    public:
        Logger();
        ~Logger();
        static void writeToLogFile(std::string msg);
        //static void writeToLogFile(std::string& msg);
        static void closeFileInThisScope();
};

#endif
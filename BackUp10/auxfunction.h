#ifndef AUXFUNCTION
#define AUXFUNCTION
#include "boost/filesystem.hpp"
#include <QtCore>
#include <thread>
#include <functional>
namespace fs = boost::filesystem;

void logger(const fs::path &pDir, const QString & path="D://CMLog.txt");

void clearDirectory(fs::path &dir);

template<class Func, class ...Args>
void runEndless(int msec, Func func, Args &&...args)
{
    auto endless = [=](Args &&...args){
        while(true){
            func(std::forward<Args>(args)...);
            std::this_thread::sleep_for(std::chrono::milliseconds(msec));
        }
    };

    std::thread thread(endless, args...);
    thread.detach();
}



#endif // AUXFUNCTION


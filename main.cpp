#include <iostream>
#include <thread>
#include <QApplication>
#include <QtWidgets>
#include <QtCore>
#include <functional>
#include <memory>
#include "catalogwatcher.h"

namespace fs = boost::filesystem;

namespace clearManage
{
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


void clearDirectory(fs::path &dir)
{
    std::vector<fs::path> files{fs::directory_iterator{dir}, {}};
    if(!files.empty())
    {
        for(const auto &file:files)
        {
            if(!fs::is_directory(file))
            {
                fs::remove(file);

            } else fs::remove_all(file);

        }
    }
}

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    setlocale(LC_ALL, "RUS");
    fs::path from_dir("D:\\DirFrom");
    fs::path to_dir("D:\\DirTo");

    auto cw=std::make_unique<CatalogManage::CatalogWatcher>(nullptr,from_dir,to_dir);

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    clearManage::runEndless(10000, clearManage::clearDirectory, std::ref(to_dir));

    return a.exec();
}

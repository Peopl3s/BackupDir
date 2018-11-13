#include <iostream>
#include <QApplication>
#include <QtWidgets>
#include <QtCore>
#include <memory>
#include "catalogwatcher.h"
#include "boost/filesystem.hpp"
namespace fs = boost::filesystem;




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    setlocale(LC_ALL, "RUS");
    std::string from{}, to{};
    //std::cin>>from>>to;
    fs::path from_dir(R"(D:\\artsets)");
    fs::path to_dir(R"(D:\\000)");

    auto cw=std::make_unique<CatalogManage::CatalogWatcher>(nullptr,from_dir,to_dir);

   /* std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    clearManage::runEndless(10000, clearManage::clearDirectory, std::ref(to_dir));*/

    return a.exec();
}

#ifndef CATALOGWATCHER
#define CATALOGWATCHER
#include <QtWidgets>
#include <QtCore>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include "boost\filesystem.hpp"
namespace fs = boost::filesystem;

namespace CatalogManage
{

class CatalogWatcher final: public QObject
{
    Q_OBJECT
public:
    CatalogWatcher(QObject *p=0, const fs::path &f_d=fs::path(), const fs::path &t_d=fs::path());
    CatalogWatcher(const CatalogWatcher &)=delete;
    CatalogWatcher& operator=(const CatalogWatcher &)=delete;
    ~CatalogWatcher(){}
    void copyFile(const fs::path &, const fs::path &);
    void firstCopyRun( const fs::path &, const fs::path &);
    std::vector<fs::path> files(const fs::path &);
public slots:
    void catalogChanged(const QString &path);
private:
    QFileSystemWatcher *fw;
    std::vector<fs::path> allFiles;
    fs::path from_directory, to_directory;
};

}
#endif // CATALOGWATCHER


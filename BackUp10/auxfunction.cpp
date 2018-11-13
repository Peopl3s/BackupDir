#include "auxfunction.h"

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

void logger(const fs::path &pDir, const QString & path)
{
    QFile file(path);
    if(file.open(QIODevice::Append))
    {
        QDateTime dt = QDateTime::currentDateTime();
        QString msg{};
        if(fs::is_directory(pDir))
        {

           msg="Произошло изменение, добавлена директория "+QString::fromStdString(pDir.string())+" "+dt.toString()+"\n";
        } else if(fs::is_regular_file(pDir))
        {
            msg="Произошло изменение, добавлен файл "+QString::fromStdString(pDir.string())+" "+dt.toString()+"\n";
        }
        QTextStream writeStream(&file);
        writeStream <<msg+"\r\n";
       file.close();
    }

}

#include "catalogwatcher.h"
#include "auxfunction.h"
namespace CatalogManage
{
    CatalogWatcher::CatalogWatcher(QObject *p, const fs::path &f_d, const fs::path &t_d):QObject(p), from_directory(f_d), to_directory(t_d)
    {
        fw=new QFileSystemWatcher(this);
        fw->addPath( QString::fromStdString(from_directory.string()));
        allFiles=files(from_directory);
        firstCopyRun(from_directory, to_directory);
        connect(fw, SIGNAL(directoryChanged(QString)),this, SLOT(catalogChanged(QString)));

    }

    void CatalogWatcher::copyFile(const fs::path &from_dir, const fs::path &to_dir)
    {
        if(fs::is_directory(from_dir))
        {

            fs::create_directory(to_dir/from_dir.filename());
            std::vector<fs::path> copy_files{fs::directory_iterator(from_dir), fs::directory_iterator()};

            for(const auto &file:copy_files)
            {
                copyFile(file, to_dir/from_dir.filename());
                allFiles.push_back(file);
                logger(file);
            }
            qDebug()<<"xyi"<<QString::fromUtf8((from_dir).string().c_str());

        }
        else
        {
            try
            {
                fs::copy_file(from_dir, to_dir/from_dir.filename(), fs::copy_option::overwrite_if_exists);
            }
            catch(fs::filesystem_error& e)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                fs::copy_file(from_dir, to_dir/from_dir.filename(), fs::copy_option::overwrite_if_exists);
            }

            logger(from_dir);
            allFiles.push_back(from_dir);
        }
    }

    void CatalogWatcher::firstCopyRun(const fs::path &from_dir, const fs::path &to_dir)
    {
        if (fs::exists(from_dir))
        {
            if(!fs::exists(to_dir))
            {
                fs::create_directory(to_dir);
            }
            try
            {
                std::vector<fs::path> copy_files{fs::directory_iterator(from_dir), {}};

                for (auto& file : copy_files)
                {
                   /* if (!fs::is_directory(file))
                    {
                        fs::copy_file(file, to_dir/file.filename(), fs::copy_option::overwrite_if_exists);
                        //allFiles.push_back(file);

                    } else*/
                        copyFile(file,to_dir);

                }

            }
            catch(fs::filesystem_error& e)
            {
                std::cerr << e.what();
            }
        }
        else
        {
            throw std::runtime_error("Source directory " + from_dir.string() + " does not exist or is not a directory");
        }
    }

    std::vector<fs::path> CatalogWatcher::files(const fs::path &dir)
    {
        return {fs::recursive_directory_iterator(dir), {}};
    }

    void CatalogWatcher::catalogChanged(const QString &path)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        from_directory=fs::path(path.toStdString());
        std::vector<fs::path> copy_files{fs::directory_iterator(from_directory), {}};
        for (auto& file : copy_files)
        {
            if(find(allFiles.begin(), allFiles.end(), file)==allFiles.end())
            {
               // allFiles.push_back(file);
             /*   if (!fs::is_directory(file))
                {
                    fs::copy_file(file, to_directory/file.filename(), fs::copy_option::overwrite_if_exists);

                } else copyFile(file, to_directory);*/
                copyFile(file, to_directory);
            }
        }
       qDebug()<<path<<"\n";
        for(const auto &x: fw->directories())
        {
            std::vector<fs::path> copy_f{fs::recursive_directory_iterator(x.toStdString()), {}};
            for( const auto &fil:copy_f)
            {
                if(fs::is_directory(fil)){
                   fw->addPath(QString::fromStdString(fil.string()));
                }
                if(find(allFiles.begin(), allFiles.end(), fil)==allFiles.end())
                {
                   allFiles.push_back(fil);
                }
            }

        }
    }


}

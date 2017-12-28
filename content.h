#ifndef CONTENT_H
#define CONTENT_H

#include <QDir>
#include <QFileDialog>
#include <vector>

class Content: public QDir
{
    std::vector<QString> fileNames;
public:
    Content(){}
    size_t size(){return fileNames.size();}
    void reset()
    {
        fileNames.clear();
        setPath(QFileDialog::getExistingDirectory());
        auto EntryList=entryList();
        fileNames.reserve(EntryList.size());
        for (auto i=EntryList.begin();i!=EntryList.end();++i)
            fileNames.push_back(*i);
    }

    QString operator [](int i)
    {
        return absolutePath()+'/'+fileNames[i];
    }
    QString name(int i)
    {
        return fileNames[i];
    }
};

#endif // CONTENT_H

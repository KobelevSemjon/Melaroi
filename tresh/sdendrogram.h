#ifndef SDENDROGRAM_H
#define SDENDROGRAM_H
#include <spie.h>
#include <set>
#include <QPoint>


struct SSubCluster{};

struct SLeaf:public SSubCluster,QPoint
{
    SLeaf(int x,int y):QPoint(x,y){}
};


struct SCluster:public SSubCluster
{
    SSubCluster* first;
    double R;
    SSubCluster* second;

    SCluster(double distance,int x1,int y1,int x2,int y2);
    SCluster(SSubCluster* first,SSubCluster* second)
    {

    }

    bool operator<(const SCluster& other)const{return R<other.R;}
    ~SCluster(){delete first;delete second;}
};


class SDendrogram
{
    const SPie& pie;
    std::multiset<SCluster> tree;
public:
    SDendrogram(const SPie& pie);
};

#endif // SDENDROGRAM_H

#include "sdendrogram.h"

SCluster::SCluster(double distance, int x1, int y1, int x2, int y2):R(distance)
{
    first=new SLeaf(x1,y1);
    second=new SLeaf(x2,y2);
}

SDendrogram::SDendrogram(const SPie &pie):pie(pie)
{
    //horizontal links
    for(int y=0;y<pie.height();++y)
        for(int x=0;x<pie.width()-1;++x)
        {
            tree.emplace(pie.distance(x,y,x+1,y),x,y,x+1,y);
        }
    //vertical links
    for(int y=0;y<pie.height()-1;++y)
        for(int x=0;x<pie.width();++x)
        {
            tree.emplace(pie.distance(x,y,x,y+1),x,y,x+1,y);
        }
    for(auto i=tree.begin();i!=tree.end();++i)
    {

    }

}



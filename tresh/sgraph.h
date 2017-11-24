#ifndef SGRAPH_H
#define SGRAPH_H
#include <vector>



struct SLink;
struct SKnot
{
    int id;
    std::vector<*SLink> links;
};
struct SLink
{
    double distance=0;
    SKnot* f,s;
    SLink(const SPoint& first,const SPoint& second)
    {
        if (first.size()!=second.size()) throw "Bad points";
        for(int i=0;i<first.size();++i)
        {
            distance+=abs(first[i]-second[i]);
        }
    }
    bool operator<(const SLink& other)
    {
        return distance<other.distance;
    }
};
class SGraph
{


public:
    SGraph();
    void join(SKnot& first,SKnot& second)
    {

    }
};

#endif // SGRAPH_H

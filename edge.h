#ifndef __EDGE_H__
#define __EDGE_H__
#include <iostream>
#include <vector>
#include <memory>

class Player;
class Vertex;

class Edge {
    int index;
    int ownerPos;
    Player* owner;
    std::vector<Vertex*> neighbourVertices; 

    public:
    Edge(int idx = -1);
    ~Edge();
    int getIndex() const;
    int getOwnerPos() const;
    Player* getOwner() const;
    std::vector<Vertex*> getNeighbourVertices() const;

    void setIndex(int idx);
    void setOwnerPos(int op);
    void setOwner(Player* ow);
    void attachVertex( Vertex* ptrv ); 
};

#endif


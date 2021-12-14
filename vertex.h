#ifndef __VERTEX_H__
#define __VERTEX_H__
#include <vector>
#include <memory>
#include "observer.h"

class Player;
class Tile;
class Edge;

class Vertex : public Observer {
    int index;
    char buildType;
    int ownerPos; // position of owner in the players vector in Board (0-3)
    Player* owner;
    std::vector<Edge*> neighbourEdges;

    public:
    Vertex(int idx = -1);
    ~Vertex();
    int getIndex() const;
    char getBuildType() const;
    int getOwnerPos() const;
    Player* getOwner() const;
    std::vector<Edge*> getNeighbourEdges() const;

    void setIndex(int idx);
    void setBuildType(char bt);
    void setOwnerPos(int op);
    void setOwner( Player* ptrp );  
    void attachEdgeDoubly( Edge* ptre );

    virtual void wasNotified( Tile& whoNotified ) override;
};

#endif


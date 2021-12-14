#ifndef __TILE_H__
#define __TILE_H__
#include <vector>
#include "subject.h"

class Vertex;

class Tile : public Subject {
    int index;
    char resourceType;
    int value;

    public:
    Tile(int idx = -1);
    virtual ~Tile();
    int getIndex() const;
    char getResourceType() const;
    int getValue() const;
    void setIndex(int idx);
    void setResourceType(char rt);
    void setValue(int v);

    virtual void notifyObservers() override;
};

#endif


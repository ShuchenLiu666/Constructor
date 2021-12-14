#include "edge.h"
#include "vertex.h"
#include "player.h"
#include <iostream>
#include <memory>
using namespace std;

Edge::Edge(int idx): index{idx}, ownerPos{-1}, owner{nullptr} {}
Edge::~Edge() {}

int Edge::getIndex() const { return index; }
int Edge::getOwnerPos() const { return ownerPos; }
Player* Edge::getOwner() const { return owner; }
vector<Vertex*> Edge::getNeighbourVertices() const { return neighbourVertices; }

void Edge::setIndex(int idx) { index = idx; }
void Edge::setOwnerPos(int op) { ownerPos = op; }
void Edge::setOwner(Player* ow) { owner = ow; }

void Edge::attachVertex( Vertex* ptrv ) {
    if ( ptrv == nullptr ) cout << "WARNING: NULLPTR parameter in Edge::attachVertex!" << endl;
    neighbourVertices.emplace_back(ptrv);
}
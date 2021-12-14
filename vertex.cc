#include "vertex.h"
#include "tile.h"
#include "edge.h"
#include "player.h"
#include <iostream>
#include <memory>
using namespace std;

Vertex::Vertex(int idx): index{idx}, buildType{'-'}, ownerPos{-1}, owner{nullptr} {}
Vertex::~Vertex() {}

int Vertex::getIndex() const { return index; }
char Vertex::getBuildType() const { return buildType; }
int Vertex::getOwnerPos() const { return ownerPos; }
Player* Vertex::getOwner() const { return owner; }
vector<Edge*> Vertex::getNeighbourEdges() const { return neighbourEdges; }

void Vertex::setIndex(int idx) { index = idx; }
void Vertex::setBuildType(char bt) { buildType = bt; }
void Vertex::setOwnerPos(int op) { ownerPos = op; }
void Vertex::setOwner( Player* ptrp ) { owner = ptrp; }

void Vertex::attachEdgeDoubly( Edge* ptre ) {
    if ( ptre == nullptr ) cout << "WARNING: NULLPTR parameter in Vertex::attachEdgeDoubly!" << endl;
    neighbourEdges.emplace_back(ptre);
    ptre->attachVertex(this);
}

void Vertex::wasNotified( Tile& whoNotified ) {
    if ( owner != nullptr ) {
        char tileResourceType = whoNotified.getResourceType();
        if ( buildType != 'B' && buildType != 'H' && buildType != 'T' ) { cout << "WARNING: owner exist but buildType not any of B, H, T!" << endl; return; }
        if ( buildType == 'B' || buildType == 'H' || buildType == 'T') { owner->addResource(tileResourceType); }
        if ( buildType == 'H' || buildType == 'T') { owner->addResource(tileResourceType); }
        if ( buildType == 'T') { owner->addResource(tileResourceType); }
    }
}

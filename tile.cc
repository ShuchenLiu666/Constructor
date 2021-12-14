#include "tile.h"
#include "observer.h"
#include <iostream>
using namespace std;

Tile::Tile(int idx): index{idx}, resourceType{'-'}, value{-1} {}
Tile::~Tile() {}

int Tile::getIndex() const { return index; }
char Tile::getResourceType() const { return resourceType; }
int Tile::getValue() const { return value; }

void Tile::setIndex(int idx) { index = idx; }
void Tile::setResourceType(char rt) { resourceType = rt; }
void Tile::setValue(int v) { value = v; }

void Tile::notifyObservers() {
    if ( resourceType == '-' ) { cout << "WARNING: uninitialized Tile value!" << endl; return; }
    if ( resourceType == 'P' ) return; // no resource to spread
    for ( size_t i = 0; i < observers.size(); i++ ) {
        observers[i]->wasNotified(*this);
    }
}

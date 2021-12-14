#include "player.h"
#include "vertex.h"
#include "edge.h"
#include "strategy.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <memory>
#include <chrono>
using namespace std;


Player::Player(): 
    numHeat{0}, numWifi{0}, numEnergy{0}, numBrick{0}, numGlass{0}
    ,numBuild{0}, buildPoints{0}, dice{Dice(make_shared<DiceLoad>())} { }
Player::~Player() {}

int Player::getNumResource(char resourceType) { 
    switch( resourceType ) {
        case 'H':
            return numHeat; break;
        case 'W':
            return numWifi; break;
        case 'E':
            return numEnergy; break;
        case 'B':
            return numBrick; break;
        case 'G':
            return numGlass; break;
        default:
            throw "WRONG RESOURCE TYPE FOR Player::getNumResource";
            return -1; break;
    }
}

int Player::getNumBuild() { return numBuild; }

int Player::getBuildPoint() { return buildPoints; }

vector<int> Player::getEdgeIndex(){
    vector<int> list;
    for (size_t i = 0; i < ownEdges.size(); i++){
        int ind = ownEdges[i]->getIndex();
        list.emplace_back(ind);
    }
    return list;
}


void Player::loadRes( Vertex* ptrv, char buildType ) {
    if ( ptrv == nullptr ) {cout << "FATAL WARNING: Player::buildRes pass a nullptr ";return;}
    if ( ptrv->getOwner() != nullptr || ptrv->getBuildType() != '-' ) {cout << "WARNING: this place is occupied by other or self" << endl;return;}
    if ( ptrv->getIndex() == -1 ) {cout << "WARNING: vertex index unitialized" << endl;return;}
    if ( ptrv->getIndex() < 0 || ptrv->getIndex() > 53 ) {cout << "WARNING: vertex index out of range" << endl;return;}
    numBuild += 1;
    if ( buildType == 'B' ) {
        ptrv->setBuildType('B');
        buildPoints += 1;
    } else if ( buildType == 'H' ) {
        ptrv->setBuildType('H');
        buildPoints += 2;
    } else if ( buildType == 'T' ) {
        ptrv->setBuildType('T');
        buildPoints += 3;
    } else {
        cout << "WARNING: Player::buildRes wrong buildType" << endl;
    }
    ownVertices.emplace_back(ptrv);
    ptrv->setOwner(this);
    return;
}


void Player::loadRoad( Edge* ptre ) { 
    if ( ptre == nullptr ) {cout << "FATAL WARNING: Player::buildRoad pass a nullptr ";return;}
    if ( ptre->getOwner() != nullptr ) {cout << "WARNING: this road is occupied by other or self" << endl;return;}
    if ( ptre->getIndex() == -1 ) {cout << "WARNING: edges index unitialized" << endl;return;}
    if ( ptre->getIndex() < 0 || ptre->getIndex() > 71 ) {cout << "WARNING: edge index out of range" << endl;return;}
    ownEdges.emplace_back(ptre);
    ptre->setOwner(this);
    return;
}


// WARNING: need to set <ownerPos in Vertex *ptrv> in Board::buildRes
bool Player::buildResFree( Vertex* ptrv ) {
    if ( ptrv == nullptr ) {cout << "FATAL WARNING: Player::buildResFree pass a nullptr ";return false;}
    if ( ptrv->getOwner() != nullptr || ptrv->getBuildType() != '-' ) {cout << "WARNING: this place is occupied by other or self" << endl;return false;}
    if ( ptrv->getIndex() == -1 ) {cout << "WARNING: vertex index unitialized" << endl;return false;}
    if ( ptrv->getIndex() < 0 || ptrv->getIndex() > 53 ) {cout << "WARNING: vertex index out of range" << endl;return false;}
    vector<Edge*> ne = ptrv->getNeighbourEdges();
    vector<Vertex*> nev;
    bool noNearBuilding = true;
    for ( size_t i = 0; i < ne.size(); i++ ) {
        nev = ne[i]->getNeighbourVertices();
        // get neighbour edge's neighbour vertice (ok to check self vertex)
        for ( size_t j = 0; j < nev.size(); j++ ) {
            // if exist nearby building, break
            if ( nev[j]->getBuildType() != '-' || nev[j]->getOwner() != nullptr) {
                noNearBuilding = false;
                break;
            }
        }
        if ( noNearBuilding == false ) break;
    }
    if ( noNearBuilding == false ) { cout << "WARNING: Adjacent building nearby, cannot build here" << endl; return false; }
    
    // update Player field, no need to dec resource
    numBuild += 1; buildPoints += 1;
    ownVertices.emplace_back(ptrv);
    // update Vertex field
    ptrv->setBuildType('B');
    ptrv->setOwner(this);
    return true;
}


// WARNING: need to set <ownerPos in Vertex *ptrv> in Board::buildRes
// need to consider whether you are allowed build here
// resource check and nearby check can be change sequence
bool Player::buildRes( Vertex* ptrv ) {
    if ( ptrv == nullptr ) {cout << "FATAL WARNING: Player::buildRes pass a nullptr ";return false;}
    if ( ptrv->getOwner() != nullptr || ptrv->getBuildType() != '-' ) {cout << "WARNING: this place is occupied by other or self" << endl;return false;}
    if ( ptrv->getIndex() == -1 ) {cout << "WARNING: vertex index unitialized" << endl;return false;}
    if ( ptrv->getIndex() < 0 || ptrv->getIndex() > 53 ) {cout << "WARNING: vertex index out of range" << endl;return false;}
    // check resource enough
    if ( numBrick < 1 || numEnergy < 1 || numGlass < 1 || numWifi < 1 ) {cout << "WARNING: resource not enough for building residence" << endl;return false;}
    // check NO nearby ANY color building
    //     get neighbour edge
    vector<Edge*> ne = ptrv->getNeighbourEdges();
    vector<Vertex*> nev;
    bool noNearBuilding = true;
    for ( size_t i = 0; i < ne.size(); i++ ) {
        nev = ne[i]->getNeighbourVertices();
        // get neighbour edge's neighbour vertice (ok to check self vertex)
        for ( size_t j = 0; j < nev.size(); j++ ) {
            // if exist nearby building, break
            if ( nev[j]->getBuildType() != '-' || nev[j]->getOwner() != nullptr) {
                noNearBuilding = false;
                break;
            }
        }
        if ( noNearBuilding == false ) break;
    }
    if ( noNearBuilding == false ) { cout << ">  Adjacent building nearby, cannot build here" << endl; return false; }
    // exist same color neighbour road around
    bool sameColorNearRoad = false;
    for ( size_t i = 0; i < ne.size(); i++ ) {
        if ( ne[i]->getOwner() == this ) { sameColorNearRoad = true; break; }
    }
    if ( sameColorNearRoad == false ) { cout << ">  No adjacent same color road nearby, cannot build here" << endl; return false; }
    // update Player field, need to dec resource
    numBrick -= 1; numEnergy -= 1; numGlass -= 1; numWifi -= 1;
    numBuild += 1; buildPoints += 1;
    ownVertices.emplace_back(ptrv);
    ptrv->setOwner(this);
    // update Vertex field
    ptrv->setBuildType('B');
    return true;
}


// WARNING: need to set <ownerPos in Vertex *ptrv> in Board::buildRes
// cannot cross existing other color building
// can only build around color vertex or color edge
bool Player::buildRoad( Edge* ptre ) { 
    if ( ptre == nullptr ) {cout << "FATAL WARNING: Player::buildRoad pass a nullptr ";return false;}
    if ( ptre->getOwner() != nullptr ) {cout << "WARNING: this road is occupied by other or self" << endl;return false;}
    if ( ptre->getIndex() == -1 ) {cout << "WARNING: edges index unitialized" << endl;return false;}
    if ( ptre->getIndex() < 0 || ptre->getIndex() > 71 ) {cout << "WARNING: edge index out of range" << endl;return false;}
    // check resource enough
    if ( numHeat < 1 || numWifi < 1) {cout << "WARNING: resource not enough for building road" << endl;return false;}
    // cannot build without around color vertex or color edge
    bool sameColorNear = false;
    vector<Vertex*> nv = ptre->getNeighbourVertices();
    vector<Edge*> nve;
    // check nearby same color vertice
    for ( size_t i = 0; i < nv.size(); i++ ) {
        if ( nv[i] == nullptr ) { cout << "WARNING: Player::buildRoad dereference nullptr at line:" << __LINE__ << endl; return false; }
        if ( nv[i]->getOwner() == this ) { sameColorNear = true; break; }
    }
    // check nearby same color road
    for ( size_t i = 0; i < nv.size(); i++ ) {
        nve = nv[i]->getNeighbourEdges();
        // get neighbour vertex's neighbour edge (ok to check self edge because self edge no owner)
        for ( size_t j = 0; j < nve.size(); j++ ) {
            // if exist nearby same color edge, break
            if (nve[j] == nullptr ) { cout << "WARNING: Player::buildRoad dereference nullptr at line:" << __LINE__ << endl; return false; }
            if (nve[j]->getOwner() == this) {
                sameColorNear = true; break;
            }
        }
        if ( sameColorNear == true ) break;
    }
    if ( sameColorNear == false ) { cout << ">  No adjacent same color road or vertice nearby, cannot build here" << endl; return false; }
    
    
    // cannot cross existing other color building if only road there
    // satisfy condition 1 or 2 then can build road
    bool noCrossOther = false;
    // 1- exist same color nearby vertex
    for ( size_t i = 0; i < nv.size(); i++ ) {
        if ( nv[i] == nullptr ) { cout << "WARNING: Player::buildRoad dereference nullptr at line:" << __LINE__ << endl; return false; }
        if ( nv[i]->getOwner() == this ) { noCrossOther = true; break; }
    }
    // 2- exist same color nearby road without cutting by other color vertex
    //    exist same color nearby road with no owner vertex in the middle (with owner has already checked in condition 1)
    // check nearby same color road
    Vertex* curVertex = nullptr;
    for ( size_t i = 0; i < nv.size(); i++ ) {
        curVertex = nv[i];
        if ( curVertex == nullptr ) { cout << "WARNING: Player::buildRoad dereference nullptr at line:" << __LINE__ << endl; return false; }
        nve = curVertex->getNeighbourEdges();
        // get neighbour vertex's neighbour edge (ok to check self edge because self edge no owner)
        for ( size_t j = 0; j < nve.size(); j++ ) {
            // if exist nearby same color edge without cutting by other color vertex, break
            if (nve[j] == nullptr ) { cout << "WARNING: Player::buildRoad dereference nullptr at line:" << __LINE__ << endl; return false; }
            if (nve[j]->getOwner() == this) {
                if ( curVertex->getOwner() == nullptr ) {
                    noCrossOther = true; break;
                }
            }
        }
        if ( noCrossOther == true ) break;
    }
    if ( noCrossOther == false ) { cout << ">  No nearby same color building and all nearby same color road cross nearby other color building, cannot build here" << endl; return false; }
    

    numHeat -= 1; numWifi -= 1;
    ownEdges.emplace_back(ptre);
    ptre->setOwner(this);
    return true;
}


bool Player::improveRes( Vertex* ptrv ) { 
    if ( ptrv == nullptr ) {cout << "FATAL WARNING: Player::improveRes pass a nullptr ";return false;}
    if ( ptrv->getOwner() != this || ptrv->getOwner() == nullptr || ptrv->getBuildType() == '-') {cout << "WARNING: this place is not occupied by current player" << endl;return false;}
    if ( ptrv->getIndex() == -1 ) {cout << "WARNING: vertex index unitialized" << endl;return false;}
    if ( ptrv->getIndex() < 0 || ptrv->getIndex() > 53 ) {cout << "WARNING: vertex index out of range" << endl;return false;}
    if ( ptrv->getBuildType() == 'T' ) {cout << "WARNING: cannot improve a top level building" << endl;return false;}
    // check resource enough
    if ( ptrv->getBuildType() == 'B' ) {
        if ( numGlass < 2 || numHeat < 3 ) {cout << "WARNING: resource not enough for improving residence" << endl;return false;}
    }
    if ( ptrv->getBuildType() == 'H' ) {
        if ( numBrick < 3 || numEnergy < 2 || numGlass < 2 || numWifi < 1 || numHeat < 2 ) {cout << "WARNING: resource not enough for improving residence" << endl;return false;}
    }
    if ( ptrv->getBuildType() == 'B' ) {
        numGlass -= 2; numHeat -= 3;
        buildPoints += 1;
        ptrv->setBuildType('H');
        return true;
    } else if ( ptrv->getBuildType() == 'H' ) {
        numBrick -= 3 ; numEnergy -= 2 ; numGlass -= 2 ; numWifi -= 1 ; numHeat -= 2;
        buildPoints += 1;
        ptrv->setBuildType('T');
        return true;
    } else {
        cout << "WARNING: wrong type for building type" << endl;return false;
    }
}


bool Player::existResource() {
    return ( (numHeat==0) && (numWifi==0) && (numEnergy==0) && (numBrick==0) && (numGlass==0) );
}


void Player::setResource(char resourceType, int n) {
    switch( resourceType ) {
        case 'H':
            numHeat = n; break;
        case 'W':
            numWifi = n; break;
        case 'E':
            numEnergy = n; break;
        case 'B':
            numBrick = n; break;
        case 'G':
            numGlass = n; break;
        default:
            throw "WRONG RESOURCE TYPE FOR Player::setResource"; break;
    }
}


void Player::addResource(char resourceType) {
    switch( resourceType ) {
        case 'H':
            numHeat +=1; break;
        case 'W':
            numWifi +=1; break;
        case 'E':
            numEnergy +=1; break;
        case 'B':
            numBrick +=1; break;
        case 'G':
            numGlass +=1; break;
        default:
            throw "WRONG RESOURCE TYPE FOR Player::addResource"; break;
    }
}


bool Player::decResource(char resourceType) { // need to check non-0
    switch( resourceType ) {
        case 'H':
            if (numHeat == 0) { cout << "WARNING: this resource is already 0" << endl; return false; }
            numHeat -=1; break;
        case 'W':
            if (numWifi == 0) { cout << "WARNING: this resource is already 0" << endl; return false; }
            numWifi -=1; break;
        case 'E':
            if (numEnergy == 0) { cout << "WARNING: this resource is already 0" << endl; return false; }
            numEnergy -=1; break;
        case 'B':
            if (numBrick == 0) { cout << "WARNING: this resource is already 0" << endl; return false; }
            numBrick -=1; break;
        case 'G':
            if (numGlass == 0) { cout << "WARNING: this resource is already 0" << endl; return false; }
            numGlass -=1; break;
        default:
            throw "WRONG RESOURCE TYPE FOR Player::decResource"; break;
    }
    return true;
}


//Shuchen
int Player::rollDice( int value, int seed ) {
    if (strategy == 'L') {
        dice.setStrategy(make_shared<DiceLoad>());
        dice.setPoint(value);
    } else {
        dice.setStrategy(make_shared<DiceRand>()); 
    }
    dice.roll();
    return dice.getPoint();
}

void Player::setStrategyState(char state) {
    strategy = state;
}




// helper function: generate resource vector
vector<char> Player::generateResBoard() {
    vector<char> generateBoard(numHeat,'H');
    generateBoard.insert(generateBoard.end(), numWifi, 'W');
    generateBoard.insert(generateBoard.end(), numEnergy, 'E');
    generateBoard.insert(generateBoard.end(), numBrick, 'B');
    generateBoard.insert(generateBoard.end(), numGlass, 'G');
    return generateBoard;
}


char Player::beStolen(int seed) {
    vector<char> generateBoard = generateResBoard();
    int totalRes = numHeat + numWifi + numEnergy + numBrick + numGlass;
    unsigned sd = seed;
    std::default_random_engine g{sd};
    std::uniform_int_distribution<int> distribution(0,totalRes - 1);
    int ranIdx = distribution(g);
    char resoureStolen = generateBoard[ranIdx];
    //update number of resource
    if (resoureStolen == 'H') numHeat--;
    if (resoureStolen == 'W') numWifi--;
    if (resoureStolen == 'E') numEnergy--;
    if (resoureStolen == 'B') numBrick--;
    if (resoureStolen == 'G') numGlass--;
    return resoureStolen;
}

void Player::loseHalfResource(int seed) {
    unsigned sd = seed;
    vector<char> generateBoard = generateResBoard();
    std::shuffle(generateBoard.begin(), generateBoard.end(), std::default_random_engine(sd));
    // the first half of generateResBoard
    size_t half_size = generateBoard.size() % 2 == 0 ? generateBoard.size() / 2 : (generateBoard.size() / 2) + 1;
    vector<char> firstHalf(generateBoard.begin(), generateBoard.begin() + half_size);
    // update number of resource
    numHeat = count(firstHalf.begin(), firstHalf.end(), 'H');
    numWifi = count(firstHalf.begin(), firstHalf.end(), 'W');
    numEnergy = count(firstHalf.begin(), firstHalf.end(), 'E');
    numBrick = count(firstHalf.begin(), firstHalf.end(), 'B');
    numGlass = count(firstHalf.begin(), firstHalf.end(), 'G');
}

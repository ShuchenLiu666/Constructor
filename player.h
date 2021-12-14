#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector> 
#include "dice.h"

class Vertex;
class Edge;

class Player {
    int numHeat;
    int numWifi;
    int numEnergy;
    int numBrick;
    int numGlass;
    int numBuild;
    int buildPoints;
    std::vector<Vertex*> ownVertices;
    std::vector<Edge*> ownEdges;
    Dice dice;
    char strategy = 'L'; // 'L' -> Loaded; 'R' -> Random
    std::vector<char> generateResBoard(); // helper

    public:
    Player();
    ~Player();
    int getNumResource(char resourceType);
    int getNumBuild();
    int getBuildPoint();
    std::vector<int> getEdgeIndex();
    
    void loadRes( Vertex* ptrv, char buildType );
    void loadRoad( Edge* ptre );
    bool buildResFree( Vertex* ptrv );
    bool buildRes( Vertex* ptrv ); // WARNING: need to set <ownerPos in Vertex *ptrv> in Board::buildRes
    bool buildRoad( Edge* ptre ); 
    bool improveRes( Vertex* ptrv );
    void setResource(char resourceType, int n);
    void addResource(char resourceType);
    bool decResource(char resourceType);  // need to check non-0
    bool existResource();

    char beStolen(int seed);
    int rollDice( int value, int seed); // if roll random dice -> randDice set to true, otherwise set to false
    void setStrategyState(char state);
    void loseHalfResource(int seed);
};

#endif


#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <string>
#include <memory> 
#include "strategy.h"

class Tile;
class Vertex;
class Edge;
class Player;

class Board {
    int posGeese = 7 ;
    int seed = -1;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::vector<std::shared_ptr<Edge>> edges;
    std::vector<std::shared_ptr<Player>> players; 
    int curTurn = 0;
    int winPoints = 10;
    
    // 5 helper function for Board::printBoard()
    std::string ttype(int pos); 
    std::string tval(int pos);
    std::string vfo(int pos);
    std::string efo(int pos);
    std::string gfo(int pos);

    public:
    // ctor
    Board();
    int getCurTurn() const;
    void setCurTurn(int ind);
    void setGeese( int ind );
    int getGeese() const;
    void setWinPoints( int winPoints);
 
    void printBoard();
    void printAllPlayerStatus();
    void printCurPlayerRes();

    void initAttachBoard();
    void initRandBoard();
    bool initLoadBoard( std::string file );
    void initSeedBoard( int seed );
    void loadGame( std::string file );
    void loadRes( int posPlayer, int pos, char buildType = 'B' );
    void loadRoad( int posPlayer, int pos );
    std::string saveGame();

    void setDice(bool fair);
    int rollDice(int value = 0); // if roll loaded dice, pass value
    void gainResources(int tileVal);

    bool buildResFree( int posPlayer, int pos );
    bool buildRes( int pos );
    bool buildRoad( int pos );
    bool improveRes( int pos );

    void printUsingChoice();
    int trade( std::string otherplayer, std::string ownResources, std::string otherResource );
    void loseHalf();
    int moveGeese( int pos );       // return -1 when receives an eof

    bool checkWon();

    void endCurTurn();
    
};

#endif


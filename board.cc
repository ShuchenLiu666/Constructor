#include <random>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <utility>
#include <iomanip>
#include <memory>
#include "board.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "player.h"

using namespace std;

Board::Board() {
    for ( int i = 0; i < 4; i++ ) { 
        players.emplace_back(make_shared<Player>());
    }
    for ( int i = 0; i < 19; i++ ) { 
        tiles.emplace_back(make_shared<Tile>(i));
    }
    for ( int j = 0; j < 54; j++ ) { 
        vertices.emplace_back(make_shared<Vertex>(j));
    }
    for ( int k = 0; k < 72; k++ ) { 
        edges.emplace_back(make_shared<Edge>(k));
    } 
    initAttachBoard();
}

int Board::getCurTurn() const {return this->curTurn; }
void Board::setCurTurn(int ind) {this->curTurn = ind; }
int Board::getGeese() const {return posGeese;};

void Board::initAttachBoard() { 
    // attach Vertex neighbours to Tile
    tiles[0]->attach(vertices[0].get());        // tile 0
    tiles[0]->attach(vertices[1].get());
    tiles[0]->attach(vertices[3].get());
    tiles[0]->attach(vertices[4].get());
    tiles[0]->attach(vertices[8].get());
    tiles[0]->attach(vertices[9].get());

    for (int i = 1; i < 3; i++){                // tile 1,2
        tiles[i]->attach(vertices[i*2].get());
        tiles[i]->attach(vertices[i*2+1].get());
        tiles[i]->attach(vertices[i*2+5].get());
        tiles[i]->attach(vertices[i*2+6].get());
        tiles[i]->attach(vertices[i*2+11].get());
        tiles[i]->attach(vertices[i*2+12].get());
    }

    for (int i = 3; i < 16; i++) {               // tile 3-15
        int j = 0;
        if (i > 5) j += 1;
        if (i > 7) j += 1;
        if (i > 10) j += 1;
        if (i > 12) j += 1;
        tiles[i]->attach(vertices[i*2+j].get());
        tiles[i]->attach(vertices[i*2+1+j].get());
        tiles[i]->attach(vertices[i*2+6+j].get());
        tiles[i]->attach(vertices[i*2+7+j].get());
        tiles[i]->attach(vertices[i*2+12+j].get());
        tiles[i]->attach(vertices[i*2+13+j].get());
    }
 
    for (int i = 16; i < 18; i++) {               // tile 16,17
        tiles[i]->attach(vertices[i*2+5].get());
        tiles[i]->attach(vertices[i*2+6].get());
        tiles[i]->attach(vertices[i*2+11].get());
        tiles[i]->attach(vertices[i*2+12].get());
        tiles[i]->attach(vertices[i*2+16].get());
        tiles[i]->attach(vertices[i*2+17].get());
    }

    tiles[18]->attach(vertices[44].get());            // tile 18
    tiles[18]->attach(vertices[45].get());
    tiles[18]->attach(vertices[49].get());
    tiles[18]->attach(vertices[50].get());
    tiles[18]->attach(vertices[52].get());
    tiles[18]->attach(vertices[53].get());


    // attach Edge neighbours to Vertex
    vertices[0]->attachEdgeDoubly(edges[0].get());
    vertices[0]->attachEdgeDoubly(edges[1].get()); 

    vertices[1]->attachEdgeDoubly(edges[0].get());
    vertices[1]->attachEdgeDoubly(edges[2].get());

    vertices[2]->attachEdgeDoubly(edges[3].get());
    vertices[2]->attachEdgeDoubly(edges[5].get());

    for (int i = 3; i < 5; i++) {
        vertices[i]->attachEdgeDoubly(edges[i-2].get());
        vertices[i]->attachEdgeDoubly(edges[i].get());
        vertices[i]->attachEdgeDoubly(edges[i+3].get());
    }

    vertices[5]->attachEdgeDoubly(edges[4].get());
    vertices[5]->attachEdgeDoubly(edges[8].get());

    vertices[6]->attachEdgeDoubly(edges[9].get());
    vertices[6]->attachEdgeDoubly(edges[12].get());

    for (int i = 7; i < 11; i++) {
        int j = 2;
        if (i > 8) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i-2].get());
        vertices[i]->attachEdgeDoubly(edges[i+j].get());
        vertices[i]->attachEdgeDoubly(edges[i+6].get());
    }

    vertices[11]->attachEdgeDoubly(edges[11].get());
    vertices[11]->attachEdgeDoubly(edges[17].get());

    vertices[12]->attachEdgeDoubly(edges[12].get());
    vertices[12]->attachEdgeDoubly(edges[20].get());

    for (int i = 13; i < 17; i++) {
        int j = 5;
        if (i > 13) j -= 1;
        if (i > 15) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i].get());
        vertices[i]->attachEdgeDoubly(edges[i+j].get());
        vertices[i]->attachEdgeDoubly(edges[i+8].get());
    }

    vertices[17]->attachEdgeDoubly(edges[17].get());
    vertices[17]->attachEdgeDoubly(edges[25].get()); 

    for (int i = 18; i < 24; i++) {
        int j = 8;
        if (i > 18) j -= 1;
        if (i > 20) j -= 1;
        if (i > 22) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i+2].get());
        vertices[i]->attachEdgeDoubly(edges[i+j].get());
        vertices[i]->attachEdgeDoubly(edges[i+11].get());
    }

    vertices[24]->attachEdgeDoubly(edges[29].get());
    vertices[24]->attachEdgeDoubly(edges[37].get());

    for (int i = 25; i < 29; i++) {
        int j = 10;
        if (i > 25) j -= 1;
        if (i > 27) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+5].get());
        vertices[i]->attachEdgeDoubly(edges[i+j].get());
        vertices[i]->attachEdgeDoubly(edges[i+13].get());
    }

    vertices[29]->attachEdgeDoubly(edges[34].get());
    vertices[29]->attachEdgeDoubly(edges[42].get());

    for (int i = 30; i < 36; i++) {
        int j = 13;
        if (i > 30) j -= 1;
        if (i > 32) j -= 1; 
        if (i > 34) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i+7].get());
        vertices[i]->attachEdgeDoubly(edges[i+j].get());
        vertices[i]->attachEdgeDoubly(edges[i+16].get());
    }

    vertices[36]->attachEdgeDoubly(edges[46].get());
    vertices[36]->attachEdgeDoubly(edges[54].get());

    for (int i = 37; i < 41; i++) {
        int j = 15;
        if (i > 37) j -= 1;
        if (i > 39) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+10].get());
        vertices[i]->attachEdgeDoubly(edges[i+j].get());
        vertices[i]->attachEdgeDoubly(edges[i+18].get());
    }

    vertices[41]->attachEdgeDoubly(edges[51].get());
    vertices[41]->attachEdgeDoubly(edges[59].get());

    vertices[42]->attachEdgeDoubly(edges[54].get());
    vertices[42]->attachEdgeDoubly(edges[60].get());

    for (int i = 43; i < 47; i++) {
        int j = 17;
        if (i > 44) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+12].get());
        vertices[i]->attachEdgeDoubly(edges[i+j].get());
        vertices[i]->attachEdgeDoubly(edges[i+20].get());
    }

    vertices[47]->attachEdgeDoubly(edges[59].get());
    vertices[47]->attachEdgeDoubly(edges[62].get());

    vertices[48]->attachEdgeDoubly(edges[63].get());
    vertices[48]->attachEdgeDoubly(edges[67].get());

    for (int i = 49; i < 51; i++) { 
        vertices[i]->attachEdgeDoubly(edges[i+15].get());
        vertices[i]->attachEdgeDoubly(edges[i+18].get());
        vertices[i]->attachEdgeDoubly(edges[i+20].get());
    }

    vertices[51]->attachEdgeDoubly(edges[66].get());
    vertices[51]->attachEdgeDoubly(edges[68].get());

    vertices[52]->attachEdgeDoubly(edges[69].get());
    vertices[52]->attachEdgeDoubly(edges[71].get());

    vertices[53]->attachEdgeDoubly(edges[70].get());
    vertices[53]->attachEdgeDoubly(edges[71].get());
}

// Jim Part_________________________________________________________________

char ownerPosToChar( int ownerPos ) {
    switch( ownerPos ) {
        case 0:
            return 'B'; break;
        case 1:
            return 'R'; break;
        case 2:
            return 'O'; break;
        case 3:
            return 'Y'; break;
        default:
            throw "WRONG ownerPos TYPE FOR ownerPosToChar"; return '-'; break;
    }
}


string Board::ttype(int pos) {
    char tileType = tiles[pos]->getResourceType();
    switch( tileType ) {
        case 'H':
            return "  HEAT   "; break;
        case 'W':
            return "  WIFI   "; break;
        case 'E':
            return " ENERGY  "; break;
        case 'B':
            return "  BRICK  "; break;
        case 'G':
            return "  GLASS  "; break;
        case 'P':
            return "  PARK   "; break;
        default:
            cout << "WRONG RESOURCE TYPE FOR Board::ttype" << endl;
            throw -1; break;
    }
}


string Board::tval(int pos) {
    string ret = "  ";
    int tileVal = tiles[pos]->getValue();
    if ( tiles[pos]->getResourceType() == 'P' ) {
        ret += "  ";
    } else {
        if ( tileVal < 10 ) ret += " ";
        ret += to_string(tileVal);
    }
    ret += "  ";
    return ret;
}


string Board::vfo(int pos) {
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return "-";}
    string ret = "|";
    if ( vertices[pos]->getOwner() == nullptr ) {
        if ( pos < 10 ) ret += " ";
        ret += to_string(pos);
    } else {
        int ownerPos = vertices[pos]->getOwnerPos();
        ret += ownerPosToChar(ownerPos);
        ret += vertices[pos]->getBuildType();
    }
    ret += "|";
    return ret;
}


string Board::efo(int pos) {
    if ( pos < 0 || pos > 71 ) {cout << "WARNING: edge index out of range" << endl;return "-";}
    string ret;
    if ( edges[pos]->getOwner() == nullptr ) {
        if ( pos < 10 ) ret += " ";
        ret += to_string(pos);
    } else {
        int ownerPos = edges[pos]->getOwnerPos();
        ret += ownerPosToChar(ownerPos);
        ret += "R";
    }
    return ret;
}


string Board::gfo(int pos) {
    if (posGeese == pos) return "  GEESE  ";
    return "         ";
}

string id( int n ) {
    string ret;
    if (n<10) ret+= " ";
    ret += to_string(n);
    return ret;
}

void Board::printBoard() {
    cout << "                          "<<vfo(0)<<"--"<<efo(0)<<"--"<<vfo(1)<<endl;
    cout << "                            |         |"<<endl;
    cout << "                           "<<efo(1)<<"   "<< id(0) <<"   "<<efo(2)<<endl;
    cout << "                            |"<<ttype(0)<<"|"<<endl;
    cout << "                "<<vfo(2)<<"--"<<efo(3)<<"--"<<vfo(3)<<tval(0)<<vfo(4)<<"--"<<efo(4)<<"--"<<vfo(5)<<endl;
    cout << "                  |         |"<<gfo(0)<<"|         |"<<endl;
    cout << "                 "<<efo(5)<<"   "<< id(1) <<"   "<<efo(6)<<"        "<<efo(7)<<"   "<< id(2) <<"   "<<efo(8)<<endl;
    cout << "                  |"<<ttype(1)<<"|         |"<<ttype(2)<<"|"<<endl;
    cout << "      "<<vfo(6)<<"--"<<efo(9)<<"--"<<vfo(7)<<tval(1)<<vfo(8)<<"--"<<efo(10)<<"--"<<vfo(9)<<tval(2)<<vfo(10)<<"--"<<efo(11)<<"--"<<vfo(11)<< endl;
    for ( int i = 0; i < 3; i++ ) {
    cout << "        |         |"<<gfo(5*i+1)<<"|         |"<<gfo(5*i+2)<<"|         |"<<endl;
    cout << "       "<<efo(17*i+12)<<"   "<< id(5*i+3) <<"   "<<efo(17*i+13)<<"        "<<efo(17*i+14)<<"   "<< id(5*i+4) <<"   "<<efo(17*i+15)<<"        "<<efo(17*i+16)<<"   "<< id(5*i+5) <<"   "<<efo(17*i+17)<<endl;
    cout << "        |"<<ttype(5*i+3)<<"|         |"<<ttype(5*i+4)<<"|         |"<<ttype(5*i+5)<<"|"<< endl;
    cout << "      "<<vfo(12*i+12)<<tval(5*i+3)<<vfo(12*i+13)<<"--"<<efo(17*i+18)<<"--"<<vfo(12*i+14)<<tval(5*i+4)<<vfo(12*i+15)<<"--"<<efo(17*i+19)<<"--"<<vfo(12*i+16)<<tval(5*i+5)<<vfo(12*i+17)<<endl;
    cout << "        "<<"|"<<gfo(5*i+3)<<"|         |"<<gfo(5*i+4)<<"|"<<"         "<<"|"<<gfo(5*i+5)<<"|"<<endl;
    cout << "       "<<efo(17*i+20)<<"        "<<efo(17*i+21)<<"   "<< id(5*i+6) <<"   "<<efo(17*i+22)<<"        "<<efo(17*i+23)<<"   "<< id(5*i+7) <<"   "<<efo(17*i+24)<<"        "<<efo(17*i+25) << endl;
    cout << "        |         |"<<ttype(5*i+6)<<"|         |"<<ttype(5*i+7)<<"|         |" << endl;
    cout << "      "<<vfo(12*i+18)<<"--"<<efo(17*i+26)<<"--"<<vfo(12*i+19)<<tval(5*i+6)<<vfo(12*i+20)<<"--"<<efo(17*i+27)<<"--"<<vfo(12*i+21)<<tval(5*i+7)<<vfo(12*i+22)<<"--"<<efo(17*i+28)<<"--"<<vfo(12*i+23) << endl;
    }
    cout << "                  |"<<gfo(16)<<"|         |"<<gfo(17)<<"|" << endl;
    cout << "                 "<<efo(63)<<"        "<<efo(64)<<"   18   "<<efo(65)<<"        "<<efo(66)<<endl;
    cout << "                  |         |"<<ttype(18)<<"|         |"<<endl;
    cout <<"                "<<vfo(48)<<"--"<<efo(67)<<"--"<<vfo(49)<<tval(18)<<vfo(50)<<"--"<<efo(68)<<"--"<<vfo(51)<<endl;
    cout << "                            |"<<gfo(18)<<"|" << endl;
    cout << "                           "<<efo(69)<<"        "<<efo(70) << endl;
    cout << "                            |         |" << endl;
    cout << "                          "<<vfo(52)<<"--"<<efo(71)<<"--"<<vfo(53) << endl;
}


void Board::printAllPlayerStatus() {
    for ( int i = 0; i < 4; i++ ) {
        cout << ">  Builder ";
        switch( i ) {
            case 0:
                cout << "Blue     "; break;
            case 1:
                cout << "Red      "; break;
            case 2:
                cout << "Orange   "; break;
            case 3:
                cout << "Yellow   "; break;
            default:
                throw "WRONG curTurn TYPE FOR Board::printAllPlayerStatus"; return; break;
        }
        cout << "has " << setfill(' ')  << setw(2) << players[i]->getBuildPoint();
        cout << " building points";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('B') << " BRICK";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('E') << " ENERGY";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('G') << " GLASS";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('H') << " HEAT";
        cout << ", " << setfill(' ')  << setw(2) << players[i]->getNumResource('W') << " WIFI";
        cout << '.' << endl;
    }
}


void Board::printCurPlayerRes() {
    switch( curTurn ) {
        case 0:
            cout << ">  Blue "; break;
        case 1:
            cout << ">  Red "; break;
        case 2:
            cout << ">  Orange "; break;
        case 3:
            cout << ">  Yellow "; break;
        default:
            throw "WRONG curTurn TYPE FOR Board::printCurPlayerRes"; return; break;
    }
    cout << "has built:" << endl;
    for ( int i = 0; i < 54; i++ ) {
        if ( vertices[i]->getOwnerPos() == curTurn ) {
            cout << setfill(' ')  << setw(2) << i <<" "<< vertices[i]->getBuildType() << endl;
        }
    }
}


void Board::loadRes( int posPlayer, int pos, char buildType ) {
    Vertex* destVertex = vertices[pos].get();
    size_t position = pos;
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return;}
    if ( position > vertices.size() - 1 ){cout << "WARNING: vertices length wrong" << endl;return;}
    if ( destVertex == nullptr ){cout << "FATAL WARNING: Board::loadRes access nullptr to pass ";return;}
    players[posPlayer]->loadRes(destVertex, buildType);
    destVertex->setOwnerPos(posPlayer);
}


void Board::loadRoad( int posPlayer, int pos ) {
    Edge* destEdge = edges[pos].get();
    size_t position = pos;
    if ( pos < 0 || pos > 71 ) {cout << "WARNING: edge index out of range" << endl;return;}
    if ( position > edges.size() - 1 ){cout << "WARNING: edges length wrong" << endl;return;}
    if ( destEdge == nullptr ){cout << "FATAL WARNING: Board::loadRoad access nullptr to pass ";return;}
    players[posPlayer]->loadRoad(destEdge);
    destEdge->setOwnerPos(posPlayer);
    return;
}


bool Board::buildResFree( int posPlayer, int pos ) {
    Vertex* destVertex = vertices[pos].get();
    size_t position = pos;
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return false;}
    if ( position > vertices.size() - 1 ){cout << "WARNING: vertices length wrong" << endl;return false;}
    if ( destVertex == nullptr ){cout << "FATAL WARNING: Board::buildResFree access nullptr to pass ";return false;}
    bool tmp = players[posPlayer]->buildResFree(destVertex);
    if (tmp == true) destVertex->setOwnerPos(posPlayer);
    return tmp;
}


bool Board::buildRes( int pos ) {
    Vertex* destVertex = vertices[pos].get();
    size_t position = pos;
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return 0;}
    if ( position > vertices.size() - 1 ){cout << "WARNING: vertices length wrong" << endl;return 0;}
    if ( destVertex == nullptr ){cout << "FATAL WARNING: Board::buildRes access nullptr to pass ";return 0;}
    bool tmp = players[curTurn]->buildRes(destVertex);
    if (tmp == true) destVertex->setOwnerPos(curTurn);
    return tmp;
}


bool Board::buildRoad( int pos ) {
    Edge* destEdge = edges[pos].get();
    size_t position = pos;
    if ( pos < 0 || pos > 71 ) {cout << "WARNING: edge index out of range" << endl;return 0;}
    if ( position > edges.size() - 1 ){cout << "WARNING: edges length wrong" << endl;return 0;}
    if ( destEdge == nullptr ){cout << "FATAL WARNING: Board::buildRoad access nullptr to pass ";return 0;}
    bool tmp = players[curTurn]->buildRoad(destEdge);
    if (tmp == true) destEdge->setOwnerPos(curTurn);
    return tmp;
}


bool Board::improveRes( int pos ) {
    Vertex* destVertex = vertices[pos].get();
    size_t position = pos;
    if ( pos < 0 || pos > 53 ) {cout << "WARNING: vertex index out of range" << endl;return 0;}
    if ( position > vertices.size() - 1 ){cout << "WARNING: vertices length wrong" << endl;return 0;}
    if ( destVertex == nullptr ){cout << "FATAL WARNING: Board::improveRes access nullptr to pass ";return 0;}
    bool tmp = players[curTurn]->improveRes(destVertex);
    return tmp;
}


//Shuchen____________________________________________________________________

// helper function: generate random number
int myrandom (int i) { return std::rand()%i;}

// helper function: initialize resource vector
std::vector<char> initResourse() {
    std::vector<char> resource(3, 'W');
    resource.insert(resource.end(), 3, 'H');
    resource.insert(resource.end(), 4, 'B');
    resource.insert(resource.end(), 4, 'E');
    resource.insert(resource.end(), 4, 'G');
    resource.emplace_back('P');
    return resource;
}


void Board::initRandBoard() {
    srand(time(0));

    // create resourse vector and shuffle with the above random generated seed
    std::vector<char> resource = initResourse();
    std::random_shuffle(resource.begin(), resource.end(), myrandom);

    //create value vector and shuffle with the above random generated seed
    std::vector<int> value = {2,12,7,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11};
    std::random_shuffle(value.begin(), value.end(), myrandom);

    // deal with park
    int parkIdx = std::find(resource.begin(), resource.end(), 'P') - resource.begin();
    int sevenIdx = std::find(value.begin(), value.end(), 7) - value.begin();
    std::swap(value[sevenIdx], value[parkIdx]);
    
    //create Tile 
    for (int i = 0; i < 19; i++) { 
        tiles[i]->setResourceType(resource[i]);
        tiles[i]->setValue(value[i]); 
        if ( resource[i] == 'P' ) posGeese = i;
    }
}

// Shuchen
void Board::initSeedBoard( int seed ) {
    // set seed
    unsigned sd = seed;

    // create random resource with seed
    std::vector<char> resource = initResourse();
    std::shuffle(resource.begin(), resource.end(), std::default_random_engine(sd));

    // create random value with seed
    std::vector<int> value = {2,12,7,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11};
    std::shuffle(value.begin(), value.end(), std::default_random_engine(sd));

    // deal with park
    int parkIdx = std::find(resource.begin(), resource.end(), 'P') - resource.begin();
    int sevenIdx = std::find(value.begin(), value.end(), 7) - value.begin();
    std::swap(value[sevenIdx], value[parkIdx]);

    // create Tile
    for (int i = 0; i < 19; i++) { 
        tiles[i]->setResourceType(resource[i]);
        tiles[i]->setValue(value[i]); 
        if ( resource[i] == 'P' ) posGeese = i;
    }
}


// Ivy_________________________________________

// a helper
int intResourceIdentifier(char resource) { 
    switch( resource ) {
        case 'B':
            return 0; break;
        case 'E':
            return 1; break;
        case 'G':
            return 2; break;
        case 'H':
            return 3; break;
        case 'W':
            return 4; break;
        case 'P':
            return 5; break;
    } 
    return -1;
}
// a helper
char charResourceIdentifier(int resourceType) { 
    switch( resourceType ) {
        case 0:
            return 'B'; break;
        case 1:
            return 'E'; break;
        case 2:
            return 'G'; break;
        case 3:
            return 'H'; break;
        case 4:
            return 'W'; break;
        case 5:
            return 'P'; break;
    } 
    return 'N';
}
// a helper
string autoCorrect(string resource) {
    char first = resource[0];
    if ((first == 'B') || (first == 'b')) { return "BRICK"; }
    if ((first == 'E') || (first == 'e')) { return "ENERGY"; }
    if ((first == 'G') || (first == 'g')) { return "GLASS"; }
    if ((first == 'H') || (first == 'h')) { return "HEAT"; }
    if ((first == 'W') || (first == 'w')) { return "WIFI"; }
    return "DNE";
}

bool Board::initLoadBoard(string file) { 
    ifstream fileIn{file};
    int resourceType;
    int value; 
    int i = 0;
    while (fileIn >> resourceType >> value) {
        if ((resourceType < 0) || (resourceType > 5) || (value < 2) || (value > 12) || (i >= 19)) {
            cerr << ">  Invalid file! Check if recourcesNum is between 0-5, tileValue between 2-12, 38 numbers in total." << endl;
            return false;
        }
        if (resourceType == 5) setGeese(i);
        char type = charResourceIdentifier(resourceType);
        tiles[i]->setResourceType(type);
        tiles[i]->setValue(value);
        i += 1;
    } 
    return true;
}

void Board::loadGame(string file) { 
    ifstream fileIn{file}; 
    string line;
    getline(fileIn, line);
    setCurTurn(stoi(line));                 // curTurn

    int v1,v2,v3,v4,v5,builtRoads;
    string temp;
    int i = 0;
    while (getline(fileIn, line)) {
        istringstream builderLine{line};
        builderLine >> v1 >> v2 >> v3 >> v4 >> v5 >> temp;
        if (temp != "r") break;             // finish checking player status
        players[i]->setResource('B', v1);
        players[i]->setResource('E', v2);
        players[i]->setResource('G', v3);
        players[i]->setResource('H', v4);
        players[i]->setResource('W', v5);
        while (builderLine >> builtRoads) {
            loadRoad(i, builtRoads);
        }
        builderLine.ignore();
        builderLine.clear(); 
        char type;
        builderLine >> temp; 
        while (builderLine >> v1 >> type) {
            loadRes(i, v1, type);
        }
        i += 1;
    }
    istringstream boardLine{line};           // board
    int resourceType;
    int value; 
    i = 0;
    while (boardLine >> resourceType >> value) {
        char type = charResourceIdentifier(resourceType);
        tiles[i]->setResourceType(type);
        tiles[i]->setValue(value);
        i += 1;
    } 
    fileIn >> v1;
    setGeese(v1);                           // geese
}

string Board::saveGame() { 
    ostringstream out;
    out << curTurn << endl;                             // <curTurn>
    vector<int> temp; 
    size_t playerSize = players.size();
    vector<vector<int>> res(playerSize,temp);           // house info
    for ( size_t i = 0; i < vertices.size(); i++ ) {
        int owner = vertices[i]->getOwnerPos();
        if (owner != -1) res[owner].emplace_back(i);
    }
    for (size_t i = 0; i < playerSize; i++) {           // <builder i's Data>
        out << players[i]->getNumResource('B') << " ";
        out << players[i]->getNumResource('E') << " ";
        out << players[i]->getNumResource('G') << " ";
        out << players[i]->getNumResource('H') << " ";
        out << players[i]->getNumResource('W') << " ";   
        // print out roads
        vector<int> roads = players[i]->getEdgeIndex();
        sort(roads.begin(), roads.end());
        out << "r " ;
        for (auto r : roads) {
            out << r << " ";
        }
        out << "h ";
        // print out residence
        for (auto pos: res[i]){
            char buildType = vertices[pos]->getBuildType();
            out << pos << " " << buildType << " ";
        }
        out << endl;
    }
    for (size_t i = 0; i < tiles.size(); i++) {            // <board>
        char type = tiles[i]->getResourceType();
        out << intResourceIdentifier(type) << " ";
        out << tiles[i]->getValue() << " ";
        if (i == tiles.size()-1) out << endl;
    }
    out << posGeese;                                      // <geese>
    return out.str();
}



//Shuchen

void Board::setDice(bool fair) {
    if (fair) {// set loaded strategy
        players[curTurn]->setStrategyState('R');
    } else {
        players[curTurn]->setStrategyState('L');
    }
}

int Board::rollDice(int value) {
    return players[curTurn]->rollDice(value, seed);
}

void Board::gainResources(int tileVal){
    vector<int> oldHeat, oldWifi, oldEnergy, oldBrick, oldGlass;
    for ( size_t i = 0; i < players.size(); i++ ) {
        oldHeat.emplace_back(players[i]->getNumResource('H'));
        oldWifi.emplace_back(players[i]->getNumResource('W'));
        oldEnergy.emplace_back(players[i]->getNumResource('E'));
        oldBrick.emplace_back(players[i]->getNumResource('B'));
        oldGlass.emplace_back(players[i]->getNumResource('G'));
    }

    // notify observers of tileVal
    // only notify which has been build
    for ( size_t i = 0; i < tiles.size(); i++ ) {
        if ( tiles[i] == nullptr ) { cout << "WARNING: Board::gainResources dereference nullptr at line:" << __LINE__ << endl; return; }
        if ( static_cast<int>(i) == posGeese ) continue;
        if ( tiles[i]->getResourceType() == 'P' ) continue;
        if ( tiles[i]->getValue() == tileVal ) {
            tiles[i]->notifyObservers();
        }
    }
    vector<string> fourPlayers = {"Blue", "Red", "Orange", "Yellow"};
    for ( size_t i = 0; i < players.size(); i++ ) {
        int Heat = players[i]->getNumResource('H') - oldHeat[i];
        int Wifi = players[i]->getNumResource('W') - oldWifi[i];
        int Energy = players[i]->getNumResource('E') - oldEnergy[i];
        int Brick = players[i]->getNumResource('B') - oldBrick[i];
        int Glass = players[i]->getNumResource('G') - oldGlass[i];
        int sumR = Heat+Wifi+Energy+Brick+Glass;
        if (sumR > 0) cout << "Builder " << fourPlayers[i] << " gained: ";
        if (Heat > 0) cout << Heat << " HEAT ";
        if (Wifi > 0) cout << Wifi << " WIFI ";
        if (Energy > 0) cout << Energy << " ENERGY ";
        if (Brick > 0) cout << Brick << " BRICK ";
        if (Glass > 0) cout << Glass << " GLASS ";
        if (sumR > 0) cout << endl;
    }
}


// Ivy
void Board::printUsingChoice() {
    cout << ">  Based on your current resources, actions avaiable are: " << endl;
    int cur = getCurTurn();
    int numHeat = players[cur]->getNumResource('H');
    int numGlass = players[cur]->getNumResource('G');
    int numBrick = players[cur]->getNumResource('B');
    int numEnergy = players[cur]->getNumResource('E');
    int numWifi = players[cur]->getNumResource('W');
    if ((numHeat > 0) && (numWifi > 0)) { cout << ">          build-road <edge#>: Build a Road; " << endl; }
    if ((numGlass > 0) && (numBrick > 0) && (numEnergy > 0) && (numWifi > 0)) {
        cout << ">          build-res <housing#>: Build a Basement; " << endl;
    }
    if ((numHeat > 2) && (numGlass > 1)) { cout << ">          improve <housing#>: Improve a Basement to House; " << endl; }
    if ((numHeat > 0) && (numGlass > 1) && (numBrick > 2) && (numEnergy > 1) && (numWifi > 0)) { 
        cout << ">          improve <housing#>: Improve a House to Tower; " << endl; 
    }
    if ((numHeat > 0) || (numGlass > 0) || (numBrick > 0) || (numEnergy > 0) || (numWifi > 0)) {
        cout << ">          trade <colour> <give> <take>: Trade with other players; " << endl;
    }
    cout << ">          next: Pass control onto the next builder; " << endl;
    cout << ">  To list all commands, please enter 'help' " << endl;
}

string askForString() {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd = "eof";
    while (true) {
        try { 
            cin >> cmd;  break;
        }  
        catch (ios::failure &) {
            if (cin.eof())  return "eof"; 
        }       
    }
    return cmd;
}


int Board::trade( string otherplayer, string ownResources, string otherResource ){
    int cur = getCurTurn();
    if ((otherplayer[0] == 'B') || (otherplayer[0] == 'b')) otherplayer = "Blue";
    if ((otherplayer[0] == 'R') || (otherplayer[0] == 'r')) otherplayer = "Red";
    if ((otherplayer[0] == 'O') || (otherplayer[0] == 'o')) otherplayer = "Orange";
    if ((otherplayer[0] == 'Y') || (otherplayer[0] == 'y')) otherplayer = "Yellow";

    vector<string> fourPlayer = {"Blue", "Red", "Orange", "Yellow"};
    int other = -1;
    for (int i = 0; i<4; i++) {
        if (fourPlayer[i] == otherplayer) {
            other = i; break;
        }
    }
    if (other == -1) {cerr << ">  Invalid player's name color!" << endl; return 0;}

    ownResources = autoCorrect(ownResources);
    otherResource = autoCorrect(otherResource);
    if ((ownResources == "DNE") || (otherResource == "DNE")) {
        cerr << ">  Invalid resources type!" << endl; return 0;
    }
    

    int numResOwn = players[cur]->getNumResource(ownResources[0]);
    int numResOther = players[other]->getNumResource(otherResource[0]);
    if ((numResOwn != 0) && (numResOther != 0)) {
        cout << ">  " << fourPlayer[cur]<<" offers " << otherplayer;
        cout << " one " << ownResources << " for one " << otherResource << "." << endl;
        cout << ">  Does " << otherplayer << " accept this offer?   yes/no (accept any case)" << endl; 
        while (true) {
            string choice = askForString();
            if (choice == "eof") return -1; 
            int size = choice.length();
            for (int i = 0; i < size; i++){
                choice[i] = toupper(choice[i]);
            }
            if (choice == "YES") {
                players[cur]->addResource(otherResource[0]);
                players[cur]->decResource(ownResources[0]);
                players[other]->addResource(ownResources[0]);
                players[other]->decResource(otherResource[0]);
                cout << ">  Successfully traded!" << endl;
                return 0;
            } else if (choice == "NO") {
                cout << ">  Trade request was refused!" << endl;
                return 0;
            } else { 
                cout << ">  Please enter either: 'yes' or 'no' (accept any case)" << endl;
            }
        }
    } else if (numResOwn == 0){
        cerr << ">  You do not have enough resources." << endl;
    } else {
        cerr << ">  " << otherplayer << " do not have enough resources." << endl;
    }
    return 0;
}



//Shuchen
void Board::loseHalf() {
    // iterate each player & find 10 or more resource
    for (size_t i = 0; i < players.size(); i++) {
        int oldHeat = players[i]->getNumResource('H');
        int oldWifi = players[i]->getNumResource('W');
        int oldEnergy = players[i]->getNumResource('E');
        int oldBrick = players[i]->getNumResource('B');
        int oldGlass = players[i]->getNumResource('G');
        int totalRes = oldHeat + oldWifi + oldEnergy + oldBrick + oldGlass;
        if (totalRes >= 10) {
            players[i]->loseHalfResource(seed);
            // resource lost
            int lostHeat = oldHeat - players[i]->getNumResource('H');
            int lostWifi = oldWifi - players[i]->getNumResource('W');
            int lostEnergy = oldEnergy - players[i]->getNumResource('E');
            int lostBrick = oldBrick - players[i]->getNumResource('B');
            int lostGlass = oldGlass - players[i]->getNumResource('G');
            int totalLost = lostHeat + lostWifi + lostEnergy + lostBrick + lostGlass;
            char currPlayer = 'B';
            if (i == 1) currPlayer = 'R';
            if (i == 2) currPlayer = 'O';
            if (i == 3) currPlayer = 'Y';
            // print message
            cout << ">  Builder " << currPlayer << " loses " << totalLost << " resources to the geese. They lose:" << endl;
            if (lostHeat != 0) cout << ">  " << lostHeat << " HEAT" << endl;
            if (lostWifi != 0) cout << ">  " << lostWifi << " WIFI" << endl;
            if (lostEnergy != 0) cout << ">  " << lostEnergy << " ENERGY" << endl;
            if (lostBrick != 0) cout << ">  " << lostBrick << " BRICK" << endl;
            if (lostGlass != 0) cout << ">  " << lostGlass << " GLASS" << endl;
        }
    }
}



int Board::moveGeese( int pos ){
    // get potential-to-be-stolen player
    // getneighbour vertices
    vector<int> neighbour;
    if (pos == 0) neighbour = {0,1,3,4,8,9};
    if (pos == 1) neighbour ={2,3,7,8,13,14};
    if (pos == 2) neighbour ={4,5,9,10,15,16};
    if (pos == 3) neighbour ={6,7,12,13,18,19};
    if (pos == 4) neighbour ={8,9,14,15,20,21};
    if (pos == 5) neighbour ={10,11,16,17,22,23};
    if (pos == 6) neighbour ={13,14,19,20,25,26};
    if (pos == 7) neighbour ={15,16,21,22,27,28};
    if (pos == 8) neighbour ={18,19,24,25,30,31};
    if (pos == 9) neighbour ={20,21,26,27,32,33};
    if (pos == 10) neighbour ={22,23,28,29,34,35};
    if (pos == 11) neighbour ={25,26,31,32,37,38};
    if (pos == 12) neighbour ={27,28,33,34,39,40};
    if (pos == 13) neighbour ={30,31,36,37,42,43};
    if (pos == 14) neighbour ={32,33,38,39,44,45};
    if (pos == 15) neighbour ={34,35,40,41,46,47};
    if (pos == 16) neighbour ={37,38,43,44,48,49};
    if (pos == 17) neighbour ={39,40,45,46,50,51};
    if (pos == 18) neighbour ={44,45,49,50,52,53};
    // get player
    vector<char> playerqueue = {'B','R','O','Y'};
    vector<char> neighbourPlayer;
    for (auto idx : neighbour) {
        int ownerIdx = vertices[idx]->getOwnerPos();
        if (ownerIdx == -1 || ownerIdx == curTurn) {
            continue;
        }
        // check 0 resource
        int totalRes = players[ownerIdx]->getNumResource('H') + players[ownerIdx]->getNumResource('W') +
                       players[ownerIdx]->getNumResource('E') + players[ownerIdx]->getNumResource('B') +
                       players[ownerIdx]->getNumResource('G');
        if (totalRes == 0) {
            continue;
        } else {
            neighbourPlayer.emplace_back(playerqueue[ownerIdx]);
        }
    }
    // current player
    string currPlayer;
    if (curTurn == 0) currPlayer = "Blue";
    if (curTurn == 1) currPlayer = "Red";
    if (curTurn == 2) currPlayer = "Orange";
    if (curTurn == 3) currPlayer = "Yellow";
    // if no neighbour player
    if (neighbourPlayer.size() == 0) {
        cout << ">  Builder " << currPlayer << " has no builders to steal from." << endl;
    } else {
        // remove duplicates
        sort( neighbourPlayer.begin(), neighbourPlayer.end() );
        neighbourPlayer.erase(unique( neighbourPlayer.begin(), neighbourPlayer.end() ), neighbourPlayer.end() );
        // print message
        cout << ">  Builder " << currPlayer << " can choose to steal from ";
        for (size_t i = 0; i < neighbourPlayer.size(); i++) {
            if (neighbourPlayer[i] == 'B') cout << "Blue";
            if (neighbourPlayer[i] == 'R') cout << "Red";
            if (neighbourPlayer[i] == 'O') cout << "Orange";
            if (neighbourPlayer[i] == 'Y') cout << "Yellow";
            if (i != neighbourPlayer.size() - 1) cout << ", ";
        }
        cout << "." << endl;
        cout << ">  Choose a builder to steal from." << endl;
        // ask for respone
        string response;
        while (true) {
            response = askForString();
            if (response == "eof") return -1; 
            // check if response is valid
            char res;
            if (response == "Blue") res = 'B';
            if (response == "Red") res = 'R';
            if (response == "Orange") res = 'O';
            if (response == "Yellow") res = 'Y';
            if (find(neighbourPlayer.begin(),neighbourPlayer.end(),res) == neighbourPlayer.end()) {
                cout << ">  Please select a builder mentioned above." << endl;
            } else {
                break;
            }
        }
        char resourceStolen;
        if (response == "Blue") resourceStolen = players[0]->beStolen(seed);
        if (response == "Red") resourceStolen = players[1]->beStolen(seed);
        if (response == "Orange") resourceStolen = players[2]->beStolen(seed);
        if (response == "Yellow") resourceStolen = players[3]->beStolen(seed);
        string resStolen;
        if (resourceStolen == 'H') resStolen = "HEAT";
        if (resourceStolen == 'W') resStolen = "WIFI";
        if (resourceStolen == 'E') resStolen = "ENERGY";
        if (resourceStolen == 'B') resStolen = "BRICK";
        if (resourceStolen == 'G') resStolen = "GLASS";
        cout << ">  Builder " << currPlayer << " steals " << resStolen << " from builder " << response << "." << endl;
        // update player resource
        players[curTurn]->addResource(resourceStolen);
    }
    // move GEESE display
    posGeese = pos;
    return 0;
}


void Board::setGeese( int pos ){posGeese = pos;}

void Board::setWinPoints( int winPoints ){ this->winPoints = winPoints;};

bool Board::checkWon() {
    int points = players[curTurn]->getBuildPoint();
    if (points >= winPoints) return true;
    return false;
}

void Board::endCurTurn() {
    curTurn += 1;
    if (curTurn == 4) curTurn = 0;
}

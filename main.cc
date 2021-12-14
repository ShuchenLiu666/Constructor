#include <iostream> 
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "ctorgame.h"
using namespace std;

bool checkFile(string file) { 
    ifstream in{file};
    string line;
    if (!getline(in, line)) return 0;   // read fail
    if (line == "") return 0;           // empty/DNE
    return 1;
}

int main(int argc, char *argv[]) {
    CtorGame game; 
    int seed;
    if (argc == 1) {                    // no cmdline arguments given
        game.setFile("layout.txt");     // Using the default board
    } else {
        for (int i = 1; i < argc; i++) { 
            string cmd{argv[i]};
            if (cmd == "-random-board") {
                game.setRandBoard(1);
            } else if (cmd == "-customize") { 
                game.setCustomized(1);
            } else {
                if (i == (argc-1)) {    // rest commands should in pairs 
                    cerr << "ERROR: Commands for " << argv[i] << " should be provided!"<< endl;
                    return 1;
                }
                if (cmd == "-seed") {  
                    istringstream is{argv[i+1]};
                    if (!(is >> seed)) {
                        cerr << "Usage: Seed should be Integer!" << endl;
                        return 1;
                    } 
                    game.setSeed(seed);
                    i += 1;
                } 
                
                else if (cmd == "-load"){
                    game.setLoad(1);
                    game.setRandBoard(0);
                    game.setBoard(0);
                    if (!checkFile(argv[i+1])) {
                        cerr << "Load File is empty or dose not exist!" << endl;
                        return 1;
                    }
                    game.setFile(argv[i+1]); 
                    i += 1;
                } 
                
                else if (cmd == "-board"){
                    game.setBoard(1);
                    game.setLoad(0);
                    game.setRandBoard(0);
                    if (!checkFile(argv[i+1])) {
                        cerr << "Board File is empty or dose not exist!" << endl;
                        return 1;
                    }
                    game.setFile(argv[i+1]); 
                    i += 1;
                }  

                else {
                    cerr << "ERROR: Invalid command line arguments!" << endl;
                    return 1;
                }
            }
        }
    }

    while (true) {
        if (!game.play()) break;
    }
    
}

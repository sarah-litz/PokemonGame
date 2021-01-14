//header file for class Game; class that keeps track of stuff going on as the game is getting executed. 
#include <iostream>
using namespace std;
#include "Pokemon.h"
#include "Tile.h"
#include "Player.h"
#include <vector> 

//class to read map file, read pokemon file 

#include <iostream> //always include
using namespace std; //always include


#ifndef GAME_H
#define GAME_H

class Game{
    private: 
        //----private datamembers----
        Tile map[25][16]; //double array of tiles; all the tiles w/ their row number, column number, and tile type
        Pokemon pokemonIndex[151]; //array of Pokemon; all the diff. pokemons and their stats to be read from file 
        //----private functions------
        int split(string words, char delimiter, string arr[], int lengthArr); 
        void assignWildPokemonRandomLocation(int index); //used in fightWildPokemon function
        
    public: 
        Game(); 
        Game(Tile _map[25][16], Pokemon _pokemonIndex[151]); 



        //Start of Game functions-------------------------------
        Player player; //automatically creates player @ game start (this represents person who is playing game) 
        vector<Player> trainers; //automatically creates 15 trainers when game instance is created @ game start 
        vector<Pokemon> wildPokemon; //size set to 20 in createWildPokemon function 

        void readMap(string fileName); //get map info from data file
        vector<Tile> getLocationsOfType(string tileType); //returns vector of all the map[y][x] aka locations of specified Tile type (w,p,C,G) 
        void printMap(); //print 7x7 Map to screen using symbols specified in directions
        
        void readPokemon(string fileName);//getline from pokemonFile.txt, create a Pokemon class instance for every pokemon 
        Pokemon stoPokemon(string pokemonName);
        
        void createTrainers(); //sets location
        void createWildPokemon(); //sets location
        
        //Player Functions----------------------------
        int movePlayer(int numDirection); //called from driver when player chooses "travel" option 
        void restPlayer(); //called from driver when player chooses "rest" option
        void tryLuck(); 
        
        //Check Location/Map Info Functions-----------------------
        bool mapEdgeCase(int rowVal, int columnVal); 
        int checkLocationTypeByRange(int rowRange, int columnRange, vector<Tile> tileType);
        
        //Wild Pokemon Functions----------------------------
        int checkWildPokeByRange(int rowRange, int columnRange); 
        bool checkWildPokeByTile(Tile mapTile); //checks single tile for wildPokemon 
        void scatterWildPokemon(); //moves all wildPokemon one tile in random direction
        void switchSuiteFromPokedex(string numbers); 
        //Fight or Flee: Wild Pokemon Encounter  
        int fightWildPokemon(int index);
            int fightCount; 
        int runFromWildPokemon(int index); 
            int runCount; 
            
        //Trainers-----------------------------------
        int checkTrainerByTile(Tile mapTile); //checks single tile for Trainer(if trainer exists, returns index of that trainer in trainers vector)
        int fightTrainer(int trainerIndex); 
        
        //Random Events------------------------------
        Pokemon getSpawnPokemon(); 
};
#endif
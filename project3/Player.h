//class for player info/stats AND trainer info/stats throughout game execution
#include <iostream>
#include <vector> 
using namespace std;
#include "Pokemon.h"
#include "Tile.h"


#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    private: 
        //Tile location[1][1]; //tile instance to keep track of player's location //i don't think i should trea
        //location info
        Tile location; 
        int rowVal; //y
        int columnVal; //x
        //player stats: 
        string username; //username of the player that they decide on @game start. 
        int pokeballs; //initialized to 10 @game start //pokeball = game "currency" 
        int badges; //end game if 6 collected
        int points; 
        
        //counters for player's collected pokemon: 
        int activeCount; 
        int pokedexCount;
        
        bool isTrainer; 
    public: 
        //-----------setters
        Player(); //default constructor
        Player(string _username, int _pokeballs, int _badges, int _points, bool _isTrainer); //parameterized constructor
        
        vector<Pokemon> activePokemon; //should be named pokemonSuite
        vector<Pokemon> pokedex; //overflow from pokemonSuite
        vector<Pokemon> deadPokemon; //pokemon placed here after/if they die in a battle (have hp==0) 
        
        vector<Pokemon> getDeadPokemon(); 
        string getUsername(); 
        Tile getLocation(); 
        int getPokeballs(); 
        int getBadges(); 
        int getPoints();
        
        void setDeadPokemon(Pokemon pokemon);
        void setLocation(int _rowVal, int _columnVal); 
        void setUsername(string _username); 
        void setPokeballs(int _pokeballs);
        void setBadges(int _badges); 
        void setPoints(int _points);
        
        void addPokemon(Pokemon newPokemon); 
        Pokemon getActivePokemon(); //returns 1st pokemon in activePokemon array  
        void switchActivePokemon(int idx); //switches pokemon in index idx to be the first pokemon in vector activePokemon
        int getActiveCount(); //returns # of active pokemon that the player has
        int getPokedexCount(); //returns # of pokemon in player's pokedex 
        //void getPokemonSuite(); 
        bool printPokemonSuite(); //displays entire activePokemon array 
        void printActivePokemon(); //displays the name and stats of active pokemon (position 0 of activePokemon array) to screen 
        void printPokedex() ; //prints out pokemon in pokedex 
        
}; 
#endif
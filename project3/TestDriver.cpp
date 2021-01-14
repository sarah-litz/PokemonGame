#include <iostream>
#include <istream>
using namespace std;
#include "Tile.h"
#include "Game.h"
#include "Player.h"
#include "Pokemon.h" 

//~~~~~initializers~~~~~
Game game1;
string username; 

//~~~~~~~~~~~~~~~~~~~~~~
//reads both the map txt file and the pokemon txt file 
void readFiles(){
    game1.readMap("mapPoke.txt"); 
    //display map function? 
    game1.readPokemon("pokemon.txt"); 
    //add starterPokemon to activePokemon array
    for(int i=0; i<12;i++){
        game1.player.addPokemon(game1.pokemonIndex[i]);
    }
    cout << "Welcome to the Pokémon Center. All Pokémon in your party have been healed. Do you want to change the members of your party (Y/N): " << endl; 
    string answer; 
    cin >> answer; 
    while(answer!="Y"&&answer!="y"&&answer!="N"&&answer!="n"){
        cout << "Invalid entry. Please choose betweeen Y or N" << endl; 
        cin >> answer; 
    }
    //int answerInt = stoi(answer);
    if(answer.compare("y")||answer.compare("Y")){
        cout << "Here are all the Pokémon in your Pokédex. Enter at most 6 numbers separated by commas, followed by Q for quit." << endl; 
        game1.player.printPokemonSuite(); 
        game1.player.printPokedex(); 
        string numbers;
        cin.ignore(); 
        getline(cin, numbers);
        game1.switchSuiteFromPokedex(numbers); 
        cout << "Here are your new 6 Pokémon you've chosen. Please choose which one should be the Active pokémon: " << endl; 
        game1.player.printPokemonSuite(); //prints all 6 pokemon 
    }
}

//switched the delimiter in function back to ' ' instead of it being ','
//make sure to put pokemonIndex back to private in game class 

void startGame(){
    game1.createTrainers(); //places trainers on map
    game1.createWildPokemon(); //places wild poke on map
}


int main(){
    readFiles();
}

 

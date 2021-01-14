//class for player info/stats AND trainer info/stats throughout game execution
#include <iostream>
#include "Player.h"
#include "Game.h" 
#include "Pokemon.h"
#include "Tile.h"
using namespace std;


/**PLAYER CLASS*/

//default constructor
Player::Player(){
    //player stats
    username =""; 
    pokeballs = 10; 
    badges = 0; 
    points = 0; 
    
    //activePokemon[6];  
    activeCount = 0; 
    //pokedex: 
    pokedexCount = 0; 
    //pokedex[8];  
}; 
//parameterized constructor 
Player::Player(string _username, int _pokeballs, int _badges, int _points, bool _isTrainer){
    username = _username; 
    pokeballs = _pokeballs; 
    badges = _badges; 
    points = _points; 
    //activePokemon[6] = _activePokemon[6];  //if in this suite, they can be used in battle 
    //pokedex[8] = _pokedex[8]; 
    isTrainer = _isTrainer; 
}
//---------------- player stats: -----------------
//setters
void Player::setLocation(int _rowVal, int _columnVal){
    rowVal = _rowVal; 
    columnVal = _columnVal; 
}
void Player::setUsername(string _username){
    username = _username; 
}
void Player::setPokeballs(int _pokeballs){
    pokeballs = _pokeballs; 
}
void Player::setBadges(int _badges){
    badges = _badges; 
}
void Player::setPoints(int _points){
    points = _points; 
}

//-----------getters
string Player::getUsername(){
    return username; 
}
Tile Player::getLocation(){
    Tile location; 
    location.setRow(rowVal); 
    location.setColumn(columnVal); 
    return location;  
}
int Player::getPokeballs(){
    return pokeballs;  
}
int Player::getBadges(){
    return badges; 
}
int Player::getPoints(){
    return points; 
}

//-------------- Player's collection of pokemon functions: ----------------------- 
void Player::addPokemon(Pokemon newPokemon){ //maxAcitve =6 
    //if Active Pokemon (max=6) is not full, adds newPokemon to activePokemon[]
    //if activePokemon[] is full, adds newPokemon to pokedex[]
    if(activePokemon.size()<6){ //size is 1-based index 
        activePokemon.insert(activePokemon.end(),newPokemon);
        activeCount++; 
    }
    else{
        pokedex.insert(pokedex.end(),newPokemon); 
        pokedexCount++; 
    }
}
void Player::switchActivePokemon(int idx){ //pass index of pokemon in pokemonSuite that player wants as new active pokemon 
    //switches order of activePokemon 
    Pokemon newActive = activePokemon.at(idx); 
    activePokemon.erase(activePokemon.begin()+idx); 
    activePokemon.insert(activePokemon.begin(),newActive); 
    return; 
}


void Player::setDeadPokemon(Pokemon pokemon){
    deadPokemon.insert(deadPokemon.end(), pokemon); //adds Pokemon from argument to array of dead pokemon 
}
vector <Pokemon> Player::getDeadPokemon(){
    return deadPokemon; //returns vector of dead pokemon 
}
Pokemon Player::getActivePokemon(){
    //returns first pokemon in active pokemon vector 
    return activePokemon.at(0);
}
int Player::getActiveCount(){
    return activeCount; 
}
int Player::getPokedexCount(){
    return pokedexCount; 
}

//--------------print stuff to screen functions: 
void Player::printActivePokemon(){ //displays the names of players' active pokemon on screen
    //display all stats about pokemon also 
    for(int i=0;i<1;i++){
        cout << i+1 << ". " << activePokemon.at(i).getName() << " (ACTIVE)"; 
        cout << ", Hit Points: " << activePokemon.at(i).getHitPoints(); 
        cout << ", Attack Strength: " << activePokemon.at(i).getAttack(); 
        cout << ", Defense Strength:  " << activePokemon.at(i).getDefense();
        cout << ", Max Strength: " << activePokemon.at(i).getMaxStrength(); 
        cout << ", Speed: " << activePokemon.at(i).getSpeed();
        cout << endl; 
    }
};
bool Player::printPokemonSuite(){ //displays the names of players' active pokemon on screen
//returns false if no pokemon are in pokedex suite, otherwise returns true if suite contains pokemon
    //Pokemon Suite = positions 1-6 in activePokemon vector = player's pokemon suite 
    //display all stats about pokemon
    if(activePokemon.size()<1){
        cout << "Your pokémon suite is empty!"; 
        return false; 
    }
    for(int i=0;i<activePokemon.size();i++){
        cout << i+1 << ". Name: " << activePokemon.at(i).getName(); 
        /*cout << ", Hit Points: " << activePokemon.at(i).getHitPoints(); 
        cout << ", Attack Strength: " << activePokemon.at(i).getAttack(); 
        cout << ", Defense Strength:  " << activePokemon.at(i).getDefense();
        cout << ", Max Strength: " << activePokemon.at(i).getMaxStrength(); 
        cout << ", Speed: " << activePokemon.at(i).getSpeed();*/
        cout << endl;
    }
    return true;
};



void Player::printPokedex(){ //displays the names of players' pokedex on screen
    //printCount = how many pokemon you want to be shown (max 6) 
    if(pokedex.size()<=0){
        cout << "Your pokedex is empty!"; 
        return; 
    }
    //display all stats about pokemon also 
    for(int i=0;i<pokedex.size();i++){
        cout << i+1 << ". " << pokedex.at(i).getName(); 
        /*cout << ": Hit Points: " << pokedex.at(i).getHitPoints(); 
        cout << ", Attack Strength: " << pokedex.at(i).getAttack(); 
        cout << ", Defense Strength:  " << pokedex.at(i).getDefense();
        cout << ", Max Strength: " << pokedex.at(i).getMaxStrength(); 
        cout << ", Speed: " << pokedex.at(i).getSpeed();*/
        cout << endl; 
    }
};

//---------------Trainer Functions: ------------------------

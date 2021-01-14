//keep track of hazard tiles aka locations of the wild pokemon and trainers 
#include <iostream>
using namespace std;
#include "Tile.h" 

#ifndef HAZARDTILES_H
#define HAZARDTILES_H

//array of Tiles(each instance of Tile stores a row,column, and type)
//keep track of locations for wild pokemon and trainers
class HazardTiles{
    private: 
        Tile wildPokemonLocation[]; //initialize to 20 
        Tile trainerLocation[]; //initialize to 15
    public: 
        //---------setters
        HazardTiles(); 
        HazardTiles(_wildPokemonLocation, _trainerLocation); 
        
        addWildPokemon(Tile newWildPokemonLocation); //adding tile instance to array wildPokemonLocation[] 
        addTrainerLocation(Tile newTrainerLocation); //adding tile instance to array trainerLocation[] 
        
        //----------getters
        checkHazardNearby(); //to check to see if wild pokemon are in fighting distance, and then after to check if another Trainer is in fighting distance 
}
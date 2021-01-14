#include <iostream>
using namespace std;
#include "Tile.h"

//default constructor 
//a Tile class instance = defines the x-y coordinate, and the type of ONE tile spot only. (an array of tiles = a single row; a double array of tiles = map!) 
Tile::Tile(){
    xVal = 0; //columnVal
    yVal = 0; //rowVal
} 
Tile::Tile(int _xVal,int _yVal, string _type){
    xVal = _xVal; 
    yVal = _yVal; 
}

//---------------setters-----------------------
void Tile::setRow(int _yVal){
    yVal = _yVal; 
}

void Tile::setColumn(int _xVal){
    xVal = _xVal; 
} 

void Tile::setType(string _type){
    type = _type;     
}

//---------------getters-------------------------
int Tile::getRowNum(){
    return yVal; 
} 
int Tile::getColumnNum(){
    return xVal; 
} 

string Tile::getType(){
    return type; 
}
#include <iostream>
using namespace std;

#ifndef TILE_H
#define TILE_H

//each instance stores info on ONE specific tile: its row,column,and type. 
class Tile{
    private: 
        int xVal; //column val 
        int yVal; //row val
        string type; 
    public: 
        Tile(); 
        Tile(int _xVal,int _yVal, string _type);
        Tile(int _xVal, int _yVal); 
        
        void setRow(int _yVal); 
        void setColumn(int _xVal); 
        void setType(string _type);
        
        int getRowNum(); 
        int getColumnNum(); 
        string getType(); 
}; 
#endif
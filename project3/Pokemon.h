//class for pokemon info/stats 
#include <iostream>
using namespace std;

#ifndef POKEMON_H
#define POKEMON_H

class Pokemon
{
    private: 
        string name; 
        int level; 
        int hitPoints; 
        int attack; //strength of attack
        int defense; //strength/resistance against attacks
        int maxStrength; //maximum strength/resilience value of attacks and defense as they level up
        int speed; 
        string type1; 
        string type2; 
        Tile location; //wild pokemon use only 
    public: 
        Pokemon(); 
        Pokemon(string _name, int _hitPoints,int _attack,int _defense,int _maxStrength,int _speed,string _type1,string _type2); 
        //--------setters
        void setLevel(int _level);
        void setName(string _name); 
        void setHitPoints(int _hitPoints); 
        void setAttack(int _attack); 
        void setDefense(int _defense); 
        void setMaxStrength(int _maxStrength); 
        void setSpeed(int _speed); 
        void setType1(string _type1); 
        void setType2(string _type2); 
        
        //---------getters
        int getLevel(); 
        string getName(); 
        int getHitPoints(); 
        int getAttack(); 
        int getDefense(); 
        int getMaxStrength(); 
        int getSpeed(); 
        string getType1(); 
        string getType2(); 
        
        //for wild pokemon only: 
        void setLocation(Tile location); 
        Tile getLocation(); 
        
        //other functions
        void levelUp(); 
};
#endif

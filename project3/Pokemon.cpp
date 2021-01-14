//class for pokemon info/stats 
#include <iostream>
using namespace std;
#include "Pokemon.h"
#include "Tile.h"

//default constructor
Pokemon::Pokemon(){
    level = 1; 
    name = ""; 
    hitPoints=0; 
    attack=0; 
    defense=0; 
    maxStrength=0; 
    speed=0; 
    type1="";
    type2="";
}
//parameterized constructor
Pokemon::Pokemon(string _name, int _hitPoints,int _attack,int _defense,int _maxStrength,int _speed,string _type1,string _type2){
    name = _name; 
    hitPoints = _hitPoints; 
    attack = _attack; 
    defense = _defense; 
    maxStrength = _maxStrength; 
    speed = _speed; 
    type1 = _type1; 
    type2 = _type2; 
}

//------------------------------MEMBER FUNCTIONS-----------------------------------
//---------setters
    void Pokemon::setLevel(int _level){
        level = _level; 
    }
    void Pokemon::setName(string _name){
        name = _name; 
    }
    void Pokemon::setHitPoints(int _hitPoints){
        hitPoints = _hitPoints; 
    } 
    void Pokemon::setAttack(int _attack){
        attack = _attack; 
    }
    void Pokemon::setDefense(int _defense){
        defense = _defense; 
    } 
    void Pokemon::setMaxStrength(int _maxStrength){
        maxStrength = _maxStrength; 
    }
    void Pokemon::setSpeed(int _speed){
        speed = _speed; 
    } 
    void Pokemon::setType1(string _type1){
        type1 = _type1; 
    } 
    void Pokemon::setType2(string _type2){
        type2 = _type2;
    } 
    
//---------getters
    int Pokemon::getLevel(){
        return level; 
    }
    string Pokemon::getName(){
        return name; 
    }
    int Pokemon::getHitPoints(){
        return hitPoints; 
    } 
    int Pokemon::getAttack(){
        return attack; 
    }
    int Pokemon::getDefense(){
        return defense; 
    }
    int Pokemon::getMaxStrength(){
        return maxStrength; 
    } 
    int Pokemon::getSpeed(){
        return speed; 
    } 
    string Pokemon::getType1(){
        return type1; 
    } 
    string Pokemon::getType2(){
        return type2; 
    }
    

//for Wild Pokemon use only: 
    void Pokemon::setLocation(Tile _location){
        location = _location; 
    }
    Tile Pokemon::getLocation(){
        return location; 
    }

//other functions: 
void Pokemon::levelUp(){
    //when pokemon wins a battle and makes opponent faint, that pokemon levels up and this function gets called to do so 
    //+1 level = HP, Attack, Defense, and Speed increase by 2% (1/50)       //vals round to nearest int 
    //attack and defense stat cannot exceed the max attack/defense val
    
    level = level+1; 
    //HP and Speed Level Up: 
    hitPoints = hitPoints + hitPoints/50; 
    speed = speed + speed/50; 
    //check if pokemon has max strength capacity to level up attack val: 
    if(attack+attack/50<=maxStrength){ //if leveled up attackVal is less than pokemon's max strength, set new attack val for pokemon
        attack = attack + attack/50; 
    }
    if(defense+defense/50<=maxStrength){//if leveled up defenseVal is less than pokemon's max strength, set new defense val for pokemon
        defense = defense + defense/50; 
    }
    //check if pokemon has max strength capacity to level up Defense val: 

    /*
    pokemon.setLevel(pokemon.getLevel()+1);
    
    //HP and Speed level up: 
    pokemon.setHitPoints(pokemon.getHitPoints()+pokemon.getHitPoints()/50); 
    pokemon.setSpeed(pokemon.getSpeed()+pokemon.getSpeed()/50); 
    
    //check maxVal stats 
    int max = pokemon.getMaxStrength();
    //check if pokemon has max strength capacity to level up Attack val: 
    int attack = pokemon.getAttack();
    if((attack+attack/50)<=max){ //if leveled up attackVal is less than pokemon's max strength, set new attack val for pokemon
        pokemon.setAttack(attack+attack/50); 
    }
    //check if pokemon has max strength capacity to level up Defense val: 
    int defense = pokemon.getDefense();
    if(defense+defense/50<=max){ //if leveled up defenseVal is less than pokemon's max strength, set new defense val for pokemon
        pokemon.setDefense(defense+defense/50); 
    }*/
}
//header file for class Game; class that keeps track of stuff going on as the game is getting executed. 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string> 
#include "Game.h"
using namespace std;

//class to read map file, read pokemon file 

//default constructor: 
Game::Game(){
    //columnSize = 16; //length of one row 
    //rowSize = 25; //length of one column aka number of rows in file 
    map[25][16];
    pokemonIndex[151]; 
}
    
//parameterized constructor 
Game::Game(Tile _map[25][16], Pokemon _pokemonIndex[151]){
    map[25][16]= _map[25][16]; 
    pokemonIndex[151] = _pokemonIndex[151]; 
} 

//------------------------MEMBER FUNCTIONS:-----------------------------------

//-------read fileName functions:
//executed once @ beginning of game: 
void Game::readMap(string fileName){ //fill data member map[][] (which is of class Tile) 
    //Tile arrMap[25][16]; //initializes double array of tiles; contains the map, basically.  
    int rowCounter = 0; 
    //--------------------function stuff:--------------------
    ifstream file; 
    file.open(fileName); 
    if(file.is_open()){
        string line; 
        int rowSize = 25; 
        int columnSize = 16; 
        while(getline(file,line)){ //gets 1 line at a time from file
            if(line!=""){
                char delimiter = ','; 
                string arrStr[columnSize]; //array of values in one row (so each number is its own column)
                split(line,delimiter,arrStr,columnSize); //breaks (one line only) STRING up into 4 smaller strings, and places inside of the array arrStr
                //set map[][] values (using tile class!!! need to make that function)
                //for each line, split up vals between commas, and create an instance of tile class for each of them. 
                //1 row = 16 spots 
                    for(int columnCounter=0; columnCounter<columnSize; columnCounter++){
                         map[rowCounter][columnCounter].setRow(rowCounter); 
                         map[rowCounter][columnCounter].setColumn(columnCounter);
                         map[rowCounter][columnCounter].setType(arrStr[columnCounter]); 
                    }
                     rowCounter++; 
            }
        }
    }
}

//returns vector of the tile instances from map[][] that are of 'tileType' //in other words... //returns vector of double array map[y][x] which is of Tile type
vector<Tile> Game::getLocationsOfType(string tileType){
    vector<Tile> waterTiles; 
    vector<Tile> plainTiles; 
    vector<Tile> centerTiles; 
    vector<Tile> gymTiles; 
    string type;
    for(int y=0; y<25; y++){ //row
        for(int x=0; x<16; x++){ //column
            type = map[y][x].getType(); 
            if(type=="w"){
                //if arrMap[y][x].getType() == w, insert this Tile instance into the waterTiles vector 
                waterTiles.insert(waterTiles.end(), map[y][x]);
            }
            else if(type=="p"){
                plainTiles.insert(plainTiles.end(), map[y][x]); 
            }
            else if(type=="C"){
                centerTiles.insert(centerTiles.end(), map[y][x]); 
            }
            else if(type=="G"){
                gymTiles.insert(gymTiles.end(), map[y][x]); 
            }
        }
    }
    if(tileType=="w"){
        return waterTiles; 
    }
    else if(tileType=="p"){
        return plainTiles; 
    }
    else if(tileType=="C"){
        return centerTiles; 
    }
    else if(tileType=="G"){
        return gymTiles; 
    }
}

void Game::printMap(){ //couts map to screen 
    //7*7 map that gets displayed on screen; Player location is always center of map 
    Tile playerLocation = player.getLocation();
    int startRow = playerLocation.getRowNum()-3; 
    int startColumn = playerLocation.getColumnNum()-3; 
    
    //Tile upperLeftMap(mapColumn,mapRow); //upper left tile in the subset of map[][]
    //upperLeftMap.setRow(mapRow); 
    //upperLeftMap.setColumn(mapColumn); 
    
    string type; 
    for(int r=startRow;r<(startRow+7);r++){ //row loop (y coordinate) 
        for(int c=startColumn;c<(startColumn+7);c++){ //column loop (x coordinate) 
            //mapScreenView[r][c-startColum]=map[r][c]; //sets variable for use in tryLuck function
            type = map[r][c].getType(); 
            if(r==playerLocation.getRowNum()&&c==playerLocation.getColumnNum()){
                cout << "@ ";
            }
            else if(type=="p"){
                cout << "* ";  
            }
            else if(type=="w"){
                cout << "~ ";  
            }
            else if(type=="G"){
                cout << "G "; 
            }
            else if(type=="C"){
                cout << "C "; 
            }
            else{ //out of bounds
                cout << "x "; 
            }
        }
        cout << endl; //moving onto next row 
    }
}


//getline from pokemonFile.txt, create a Pokemon class instance for every pokemon 
void Game::readPokemon(string fileName){
    //Pokemon pokemonIndex[151]; //array of all the possible pokemon options 
    ifstream file; 
    file.open(fileName); 
    if(file.is_open()){
        int rowCounter = 0; //starting on 2nd line cuz first line is just the headings for the pokemon table 
        //int columnCounter = 1; //starting on 2nd column cuz first column is just numberings for the pokemon 
        string line; 
        //int rowSize = 152; 
        int columnSize = 9; //used in split function for how many pieces each line is split up into.  
        while(getline(file,line)){ //gets 1 line at a time from file
            if(rowCounter!=0){
                if(line!=""){
                    char delimiter = ','; 
                    string arrStr[columnSize]; //array of values in one row (so each number is its own column)
                    split(line,delimiter,arrStr,columnSize); //breaks (one line only) STRING up into 4 smaller strings, and places inside of the array arrStr
                    //each row = new instance of pokemon class; 1 instance per line
                    //for each new instance, set all atributes of that pokemon: 
                    //that instance will be accessible in the pokemonIndex[] array.
                    pokemonIndex[rowCounter-1].setName(arrStr[1]);
                    pokemonIndex[rowCounter-1].setHitPoints(stoi(arrStr[2])); 
                    pokemonIndex[rowCounter-1].setAttack(stoi(arrStr[3])); 
                    pokemonIndex[rowCounter-1].setDefense(stoi(arrStr[4])); 
                    pokemonIndex[rowCounter-1].setSpeed(stoi(arrStr[5])); 
                    pokemonIndex[rowCounter-1].setMaxStrength(stoi(arrStr[6])); 
                    pokemonIndex[rowCounter-1].setType1(arrStr[7]); 
                    if(arrStr[8]!=""){
                        pokemonIndex[rowCounter-1].setType2(arrStr[8]); 
                    }else{
                        pokemonIndex[rowCounter-1].setType2("This Pokemon only has 1 type."); 
                    }
                }
            }
            rowCounter++;
        }
    }
}

Pokemon Game::stoPokemon(string pokemonName){ //converts string to Pokemon (finds where pokemonName exists in pokemonIndex) )
    //find pokemonName in pokemonIndex 
    for(int i=0; i<151; i++){
        if(pokemonName == pokemonIndex[i].getName()){
            return pokemonIndex[i]; 
        }
    }
    cout << "Pokemon does not exist/theres an issue here...this message is from fucntion stoPokemon in Game.cpp" << endl; 
    return pokemonIndex[1]; 
}

void Game::createTrainers(){ //called once @ game start
    trainers.resize(15); //initalizes vector of trainers(player class) to 15 
    //set trainer locations: 1 @ each gym 
    vector<Tile> gymTiles; 
    gymTiles = getLocationsOfType("G"); 
    for(int n=0; n<15; n++){
        Tile newLocation = gymTiles.at(n);
        trainers.at(n).setLocation(newLocation.getRowNum(),newLocation.getColumnNum());
    }
    //assign trainer pokemon at random (each get between 1-6 diff. pokemon)
    //(rand()%10) //this gives us random number between 0 and 9 
    for(int t=0; t<15; t++){ //loop to cycle thru all 15 trainers
        int numPoke = (rand()%6)+1; //how many new pokemon trainer gets (between 1-6)
        int newPoke[numPoke]; //array of index for new pokemon to get assigned
        for(int n=0; n<numPoke; n++){ //loop to assign random number <numPoke> worth of pokemon 
            newPoke[n] = (rand()%152); //assigns index num for new pokemon
            for(int a=0; a<n; a++){ //loop for error check
                if(newPoke[n]==newPoke[a]){ //error check to make sure all newPoke are diff. 
                    n--; //repeat (int n) for loop if newPoke has already been used 
                }
            }//end n loop, "survived" error check once it exits
            //setActivePokemon for trainer as it exits: 
                //retrieve Pokemon @ index=newPoke[n], add this pokemon to trainer's active pokemon array 
            Pokemon addPoke = pokemonIndex[newPoke[n]]; 
            trainers.at(t).addPokemon(addPoke);
        }//end n loop for pokemon index loop
    }//end t loop for trainer loop
}

void Game::createWildPokemon(){
    //set 20 wildPoke to pokemon from pokemonIndex: 
    vector<int> randWildIndex; 
    fightCount = 0; //initializes variable for later use in fightWildPokemon
    runCount = 0; //initializes variable for later use in runFromWildPokemon
    //scatter the 20 wild Pokemon randomly among the land, or "p" tiles; also can't be @playerLocation or a tile already containing a wild poke
    wildPokemon.resize(20); //sets vector size to 20
    //locate plain tiles and add them to vector
    vector<Tile> plainTiles = getLocationsOfType("p"); //getLocationsOfType returns vector of double array map[y][x] which is of Tile type
    //erase playerLocation tile from plainTiles vector so wildPokemon cannot be set to same spot 
    for(int v=0; v<plainTiles.size(); v++){ 
        if((plainTiles[v].getRowNum()==player.getLocation().getRowNum())&&(plainTiles[v].getColumnNum()==player.getLocation().getColumnNum())){
            //ifStatement says: if rowVal and columnVal both match (aka they have the same location), then enter loop
            plainTiles.erase(plainTiles.begin()+v); //erase this tile from plainTiles vector
        }
    } //@loop exit, should have full vector of plain Tiles minus the playerLocation tile. 
    
    //initialize all 20 wildPokemon to pokemon in pokemonIndex: 
    int pokeIdx; 
    for(int wp=0; wp<20; wp++){//for looping thru all 20 wild pokemon
        //initialize wildPoke to a pokemon from the pokemonIndex array (no repeats)
        for(int n=0; n<wp; n++){ //error check: for looping thru the wildPoke[] that have already been assigned to a pokemon from pokemonIndex[]
            pokeIdx = rand()%152; 
            if(pokemonIndex[pokeIdx].getName()==wildPokemon.at(n).getName()){
                n--; //repeats entire loop so will try a diff. index for the same wildPokemon
            }            
        }//end n loop, pokeIdx "survived" error check once it exits
        //set new wildPokemon 
        wildPokemon.at(wp) = pokemonIndex[pokeIdx]; //initalizes wildPokemon(wp=1 thru 20)
    }//end wp loop
    
    //set wildPokeLocation: 
    int randIndex; //index for setting location of wildPokemon
    for(int wp=0; wp<20; wp++){ //for looping thru all 20 wild pokemon
        wildPokemon.at(wp) = pokemonIndex[rand()%152];     
        //get random index of tile from plainTiles
        randIndex = rand()%(plainTiles.size()); //rand()%100 is random val between 0 and 99, so don't need to -1
        //set wildPokemon location by passing function setLocation the map tile instance in the plainTiles vector, at position=randIndex 
        wildPokemon.at(wp).setLocation(plainTiles.at(randIndex)); 
        //remove assigned tile from plainTiles vector so it doesn't get reassigned 
        plainTiles.erase(plainTiles.begin()+randIndex); 
    }
    //*note: vec.erase(vec.begin()+2); //erases the 3rd element in vector
}


int Game::movePlayer(int numDirection){
    Tile currentLocation = player.getLocation(); //returns Tile: location of player //cause player has no member fucntion .getRowNum or .getColumnNum
    Tile newLocation; //for finding new x-y coordinates of move, then will be used to retreive Tile from map[y][x] 
    //int errorCheck=-1; //to check if it makes it thru if statements at bottom of loop
    //while(errorCheck<0){
        switch(numDirection){
            case 1: //move North ~ (move up one row)
                //if(currentLocation.getRowNum)
                if(mapEdgeCase(currentLocation.getRowNum()-1,currentLocation.getColumnNum())==false){
                        return 1; 
                }
                newLocation = map[currentLocation.getRowNum()-1][currentLocation.getColumnNum()];
                break; 
            case 2: //move East ~ (move over one column) 
                if(mapEdgeCase(currentLocation.getRowNum(),currentLocation.getColumnNum()+1)==false){
                    return 1; 
                }
                newLocation = map[currentLocation.getRowNum()][currentLocation.getColumnNum()+1];
                break;
            case 3: //move South ~ (move down one row)
                if(mapEdgeCase(currentLocation.getRowNum()+1,currentLocation.getColumnNum())==false){
                    return 1; 
                }
                newLocation = map[currentLocation.getRowNum()+1][currentLocation.getColumnNum()];
                break; 
            case 4: //move West ~ (move left one column) 
                if(mapEdgeCase(currentLocation.getRowNum(),currentLocation.getColumnNum()-1)==false){
                    return 1; 
                }
                newLocation = map[currentLocation.getRowNum()][currentLocation.getColumnNum()-1];
                break; 
        }
        //check to make sure that newLocation is not a water tile and is in bounds of board
        if(newLocation.getType()=="w"){
            cout << "You cannot move to that spot because there is water! Choose a different direction to travel:" << endl;
            cout << "1. North" << endl << "2. East" << endl << "3. South" << endl << "4. West" << endl; 
            return 1; 
        }
        else if(newLocation.getType()!="p"&&newLocation.getType()!="G"&&newLocation.getType()!="C"){
            cout << "You have reached the edge of the map and cannot move that direction. Choose a different direction to travel:" << endl; 
            cout << "1. North" << endl << "2. East" << endl << "3. South" << endl << "4. West" << endl; 
            return 1; 
        }
        else{ //setLocation for player
            player.setLocation(newLocation.getRowNum(),newLocation.getColumnNum()); 
            return 0; //success in moving player location 
        }
}
void Game::restPlayer(){
    //+1 hp for every pokemon in player's party
    //player's pokeballs goes down by 1 
    player.setPokeballs(player.getPokeballs() -1); 
    for(int n=0; n<player.getActiveCount();n++){
        player.activePokemon.at(n).setHitPoints(player.activePokemon.at(n).getHitPoints() + 1); 
    }
}
int Game::checkLocationTypeByRange(int rowRange, int columnRange, vector<Tile> tileType){
    //returns index in tileType vector 
    //e.g. checkLocationTypeByRange(2,2,"C") //this would return the first Center tile found in a 4*4 range surrounding the player (2 in every direction)  

    for(int i=0; i<tileType.size();i++){ //for looping thru getLocationOfType vector 
        for(int r=0; r<rowRange; r++){ //for looping thru rows
            for(int c=0; c<columnRange; c++){ //for looping thru columns 
                if(tileType.at(i).getRowNum()==(player.getLocation().getRowNum()-(rowRange/2))+r&&tileType.at(i).getRowNum()==player.getLocation().getColumnNum()-(columnRange/2)+c){
                    //loops thru specificed range around player and check at each tile to see if rows and columns match between a tile of specified type and a tile w/in range of player 
                    return i; 
                }
            }
        }
    }
    //if no Tile of specified type found in range 
    return -1; 
}
int Game::checkWildPokeByRange(int rowRange,int columnRange){ 
//returns index of pokemon in wildPokemon vector that is w/in range of player
    //check for wild poke inn 7*7 area (equal to mapView)
    //set range to look for wildPoke: 
    //Tile checkRange[7][7]; //tiles in the mapView range 
    for(int wp=0;wp<20;wp++){//for looping thru all 20 pokemon 
        int wpRow = wildPokemon.at(wp).getLocation().getRowNum(); 
        int wpColumn = wildPokemon.at(wp).getLocation().getColumnNum(); 
        for(int r=0;r<rowRange;r++){
            for(int c=0;c<columnRange;c++){
                if(wpRow==player.getLocation().getRowNum()-(rowRange/2)+r&&wpColumn==player.getLocation().getColumnNum()-(columnRange/2)+c){
                    return wp; 
                }
            }
        }
    }
    //if no pokemon in range: 
    return -1; 
}
                    
void Game::tryLuck(){
    int index = checkWildPokeByRange(7,7);
    if(index<0){
        //no wildPoke in range 
        cout << "There are not any wild pokémon in this area right now." << endl; 
    }else{
        cout << "There was a wild pokémon found nearby, "; 
        int num=rand()%2; //rand num between 0 and 1
        if(num==0){ //wild pokemon caught
            //add pokemon to either player's pokemon collection and remove wild pokemon from wildPokemon vector 
            cout << "and you caught it! " << wildPokemon.at(index).getName() << " has been added to your Pokémon." << endl; 
            player.addPokemon(wildPokemon.at(index)); //adds to active or pokedex(if active full)
            wildPokemon.erase(wildPokemon.begin()+index);
        }else{
            cout << "but unfortunately, it got away. Better luck next time." << endl; 
        }
    }
}

bool Game::mapEdgeCase(int rowVal, int columnVal){
    //checks if rowVal and columnVal exist in map[][] Tiles 
    if(rowVal>24||rowVal<0||columnVal>15||columnVal<0){
        return false; 
    }
    return true; 
}

bool Game::checkWildPokeByTile(Tile mapTile){
    //checks a single tile for if a wild pokemon is @ that location. 
    for(int n=0;n<wildPokemon.size();n++){//for looping thru all the wildPokemon on map 
        if(mapTile.getRowNum()==wildPokemon.at(n).getLocation().getRowNum()&&mapTile.getColumnNum()==wildPokemon.at(n).getLocation().getColumnNum()){
            return false; 
        }
    }
    return true; 
}
void Game::scatterWildPokemon(){
    //vector<Pokemon> errorCases; //for pokemon that cannot move in any direction, to try again after other wildpoke have been moved 
    for(int wp=0;wp<wildPokemon.size();wp++){//for looping thru all wildPokemon on board 
        Tile currentLocation = wildPokemon.at(wp).getLocation(); //returns Tile: location of pokemon //cause pokemon has no member fucntion .getRowNum or .getColumnNum
        Tile newLocation; //for finding new x-y coordinates of move, then will be used to retreive Tile from map[y][x] 
        int numDirection = rand()%4+1; //randNum between 1 and 4
        //run loop max 4 times, and change it so the first numDirection is random, 
        //but following that it just adds one so it tries all 4 directions the first 4 iterations of the loop . 
        int errorCheck=0; //to check if it makes it thru if statements at bottom of loop
        while(errorCheck<4){ //loop runs max 4 times(once in every direction)
            numDirection++; 
            switch(numDirection){
                case 1: //move North ~ (move up one row)
                    //if(currentLocation.getRowNum)
                    if(mapEdgeCase(currentLocation.getRowNum()-1,currentLocation.getColumnNum())==false){
                        errorCheck++;
                        break; 
                    }
                    newLocation = map[currentLocation.getRowNum()-1][currentLocation.getColumnNum()];
                    break; 
                case 2: //move East ~ (move over one column)
                    if(mapEdgeCase(currentLocation.getRowNum(),currentLocation.getColumnNum()+1)==false){
                        errorCheck++;
                        break; 
                    }
                    newLocation = map[currentLocation.getRowNum()][currentLocation.getColumnNum()+1];
                    break;
                case 3: //move South ~ (move down one row)
                    if(mapEdgeCase(currentLocation.getRowNum()+1,currentLocation.getColumnNum())==false){
                        errorCheck++;
                        break; 
                    }
                    newLocation = map[currentLocation.getRowNum()+1][currentLocation.getColumnNum()];
                    break; 
                case 4: //move West ~ (move left one column) 
                    if(mapEdgeCase(currentLocation.getRowNum(),currentLocation.getColumnNum()-1)==false){
                        errorCheck++;
                        break; 
                    }
                    newLocation = map[currentLocation.getRowNum()][currentLocation.getColumnNum()-1];
                    break; 
            }
            if(newLocation.getType()=="w"||newLocation.getType()=="G"||newLocation.getType()=="C"){
                errorCheck++;  
            }
            //check to make sure that tile is not already occupied by a diff. wild pokemon 
            else if(checkWildPokeByTile(newLocation)==false){
                errorCheck++; 
            }

            else{ //setLocation for wild poke
                wildPokemon.at(wp).setLocation(newLocation);
                //only occurs if other two if statements are false, meaning newLocation is okay to move to.
                errorCheck=10; 
            }
        }//end while loop(running max 4 times)
    }//end wp loop (20 iterations)
}//end scatterWildPokmon function

int Game::fightWildPokemon(int index){//pass index of wild pokemon that player will battle 
//returns 0 when turn has ended, and 1 if further action needs to be taken, so main battle menu should be displayed (fight, switch, or run options) 
    //players active pokemon battles wild pokemon 
    //if first or second wild pokemon encounter, player automatically gets the wild pokemon 
    //in all other cases theres a 60% change the wild pokemon will attack 
    //player.getActivePokemon(); 
    fightCount = fightCount+1;
    int fleeAttempts=0; 
    if(fightCount==1||fightCount==2){ //if 1st or 2nd fight player automatically gains wild Pokemon 
        cout << "You won your "; 
        if(fightCount==1){
            cout << "1st"; 
        }else{
            cout << "2nd"; 
        }
        cout << " fight! You gained " << wildPokemon.at(index).getName() << "in your Pokémon collection which can be accessed at a Pokémon center." << endl; 
        player.addPokemon(wildPokemon.at(index)); 
        wildPokemon.erase(wildPokemon.begin()+index); 
    }else{ //if fightCount>2
        int randNum=rand()%10+1;
        
        //WILD POKEMON ATTACKS BACK: 
        if(randNum<=6){ //60%chance: WILD POKEMON ATTACKS BACK 
            cout << wildPokemon.at(index).getName() << " is attacking back!"; 
            //wild pokemon attacks player.activePokemon back 
            //speed determines who attacks first; higherSpeedPokemon = attacker, lowerSpeedPokemon = defendant 
            int fightLoop=0;
            while(fightLoop<2||wildPokemon.at(index).getHitPoints()!=0||player.getActivePokemon().getHitPoints()!=0){
                //fight loops twice unless either pokemon's HP val reaches 0
                fightLoop++;
                Pokemon* attacker = &player.activePokemon.at(0); 
                Pokemon* defendant = &wildPokemon.at(index); 
                if(player.getActivePokemon().getSpeed()>wildPokemon.at(index).getSpeed()){ //player's active pokemon has higher speed score 
                    attacker = &player.activePokemon.at(0); //pass by reference (changes made to attacker make changes to object instance player.activePokemon)
                    defendant = &wildPokemon.at(index); 
                }else{ //wildPokemon's speed is higher than active pokemon's speed score 
                    attacker = &wildPokemon.at(index); //pass by reference
                    defendant = &player.activePokemon.at(0); 
                }
                cout << attacker->getName() << " attacks first: " << endl; 
                //first attack: 
                int aVal = rand()%attacker->getAttack(); //rand num between 0 and attacker's Attack Strength 
                int dVal = rand()%defendant->getDefense(); //rand num between 0 and defendant's Defense Strength 
                if(aVal>dVal){
                    defendant->setHitPoints(defendant->getHitPoints()-(aVal-dVal));  
                    cout << attacker->getName() << " deals " << aVal << " damage" << endl; 
                    cout << "Name: " << attacker->getName() << ", HP: " <<attacker->getHitPoints() << ", A: " <<attacker->getAttack() << ", D: " << attacker->getDefense() << ", S: " << attacker->getSpeed() << ", M: " << attacker->getMaxStrength() << endl; 
                    cout << "Name: " << defendant->getName() << ", HP: " <<defendant->getHitPoints() << ", A: " <<defendant->getAttack() << ", D: " << defendant->getDefense() << ", S: " << defendant->getSpeed() << ", M: " << defendant->getMaxStrength() << endl; 
                }//else, nothing happens 
            }//end fight loop for the 2 attack phases (or one of the pokemon reaches HP val of 0)
            if(wildPokemon.at(index).getHitPoints()==0){ //if wild pokemon fainted
                //HP points restored and added to player's pokedex 
                cout << wildPokemon.at(index).getName() << " has fainted! This pokémon has been added to your collection, and your active pokémon, " << player.getActivePokemon().getName() << " has moved up to level " << player.getActivePokemon().getLevel() << "." << endl; 
                Pokemon originalPoke = stoPokemon(wildPokemon.at(index).getName()); 
                //reset stats for wildPoke: 
                wildPokemon.at(index).setHitPoints(originalPoke.getHitPoints()); 
                //add wildPoke to player array, and erase it from wildPoke array 
                player.addPokemon(wildPokemon.at(index)); 
                wildPokemon.erase(wildPokemon.begin()+index); 
                //level up active pokemon: 
                player.getActivePokemon().levelUp(); 
                return 0; //turn ends 
            }
            else if(player.getActivePokemon().getHitPoints()==0){ //if player's active pokemon fainted 
                //this pokemon can't be sent to battle until its HitPoints get restored @ a pokemon center 
                //wild pokemon levels up 
                cout << "Your pokémon, " << player.getActivePokemon().getName() << ", has fainted. You are not able to use this pokémon until its hit points are restored at a pokémon center." << endl; 
                player.setDeadPokemon(player.getActivePokemon());
                player.activePokemon.erase(player.activePokemon.begin()+0); //idx0=activePokemon 
                //level up wild poke: 
                wildPokemon.at(index).levelUp(); 
                //if player has no more awake pokemon after pokemon faints: 
                if(player.activePokemon.size()==0){
                    cout << "That was your last awake pokémon in your party. You have been transported to the nearest pokémon center to revive at least one of your pokémon before continuing." << endl;  
                    //teleport player to nearest pokemon center 
                    vector<Tile> centerLocations = getLocationsOfType("C");
                    for(int n=0; n<10; n++){
                        int nearestCenterIdx = checkLocationTypeByRange(n,n,centerLocations); //increases range by 1 every loop 
                        if(nearestCenterIdx>0){ //tile found
                            //set player location to this tile 
                            player.setLocation(centerLocations.at(nearestCenterIdx).getRowNum(), centerLocations.at(nearestCenterIdx).getColumnNum());
                            return 0; //turn over  
                        }
                    }
                    //if it reaches this point, can't find center in the 200 tiles (10*10 range) around it 
                    player.setLocation(centerLocations.at(0).getRowNum(), centerLocations.at(0).getColumnNum()); //fail safe option 
                    return 0; //turn over  
                }//end if no more activePoke left in player's pokemon 
                else{ //if pokemon faints but player has more pokemon in party 
                    return -1; //player gets option to fight, switch pokemon, or run which will allow player to send out another pokemon to take its place, drawn from his or her party  
                }
            } //end if(player's active pokemon fainted) statement
            else{ //both pokemon are still alive 
                //go back to main battle menu w/ fight, switch, or run options 
                return -1; 
            }
            
        }//end if(wildPoke attacks back) statement 
        
        
        //WILD POKEMON FLEES: 
        else{ //40%chance wildPoke FLEES
            cout << wildPokemon.at(index).getName() << " chose to flee the scene, "; 
            //wild pokemon flees 
            //calculations decide if wildPoke fleeing is sucessful 
                //fleeSuccess=(wildPokeSpeed*32)/((activePokemonSpeed/4)%256)+30*fleeAttempts
            fleeAttempts=fleeAttempts+1; //times wildPoke has attempted to flee, including current attempt 
            int fleeSuccess; 
            fleeSuccess = ((wildPokemon.at(index).getSpeed()*30)/((player.getActivePokemon().getSpeed()/4)%256))+(fleeAttempts*30); 
            if(fleeSuccess>255){
                cout << "and was successful in getting away. Better luck next time!" << endl; 
                //wildPokemon escapes automatically: set new random location 
                assignWildPokemonRandomLocation(index); 
                return 0; //turn ends  
            }
            else{//fleeSuccess<255; randNum determines if flee is successful or not. 
                if((rand()%256)<fleeSuccess){ //if rand num is less than fleeSuccess
                    cout << "and was successful in getting away. Better luck next time!" << endl; 
                    assignWildPokemonRandomLocation(index); //wild pokemon flee is successful 
                    return 0; //turn ends  
                }else{ //flee NOT successful
                    //player gets new pokemon, wildPoke removed from wildPokemon array 
                    cout << "but was not successful. You have captured this pokémon! You may now access this pokémon at a pokémon center."; 
                    player.addPokemon(wildPokemon.at(index)); 
                    wildPokemon.erase(wildPokemon.begin()+index); 
                    return 0; //turn ends 
                }
            }
        }//end else(wildPoke flee) statement 
    }//end else loop for if(fightAttempt>2) 
}//end function fightWildPokemon


int Game::runFromWildPokemon(int index){ //pass index of wildPokemon that player is running from 
//returns true if escape successful, returns false if escape was not successful. 
    //calculation determines if running away from battle is successful or not 
    //if escape is successful , player moves to nearest pokemon center
    runCount = runCount+1; 
    int fleeSuccess; 
    fleeSuccess = ((player.getActivePokemon().getSpeed()*32)/((wildPokemon.at(index).getSpeed()/4)%256)+runCount*30); 
    if(fleeSuccess>255){//player escape successful 
        cout << "You successfully ran away from the wild pokémon." << endl; 
        //teleport player to nearest pokemon center 
        vector<Tile> centerLocations = getLocationsOfType("C");
        for(int n=0; n<10; n++){
            int nearestCenterIdx = checkLocationTypeByRange(n,n,centerLocations); //increases range by 1 every loop 
            if(nearestCenterIdx>0){ //tile found
                //set player location to this tile 
                player.setLocation(centerLocations.at(nearestCenterIdx).getRowNum(), centerLocations.at(nearestCenterIdx).getColumnNum());
                return 0; //end turn   
            }
        }
        //fail safe option: 
        player.setLocation(centerLocations.at(0).getRowNum(),centerLocations.at(0).getColumnNum());
        return 0; //end turn 
    }else{
        if(rand()%256<fleeSuccess){
            cout << "You successfully ran away from the wild pokémon." << endl; 
            vector<Tile> centerLocations = getLocationsOfType("C");
            for(int n=0; n<10; n++){
                int nearestCenterIdx = checkLocationTypeByRange(n,n,centerLocations); //increases range by 1 every loop 
                if(nearestCenterIdx>0){ //tile found
                    //set player location to this tile 
                    player.setLocation(centerLocations.at(nearestCenterIdx).getRowNum(), centerLocations.at(nearestCenterIdx).getColumnNum());
                    return 0; //end turn   
                }
            }
             //fail safe option: 
            player.setLocation(centerLocations.at(0).getRowNum(),centerLocations.at(0).getColumnNum());
            return 0; //end turn 
        }else{
            cout << "You were not able to escape the wild pokémon."; 
            return -1; //go back to menu display  
        }
    }
}//end runFromWildPokemon function

void Game::switchSuiteFromPokedex(string numbers){
    //split up numbers entered with 'space' as delimiter 
    //convert string to integer 
    //swap the corresponding pokemon from pokedex into suite 
    int intVersion; 
    string numStrArr[7]; 
    vector<int> numArr;
        //numArr.resize(8); 
    vector<Pokemon> pokeArr; 
        //pokeArr.resize(8); 
    split(numbers, ' ', numStrArr, 7); 
    int i=0; 
    while(numStrArr[i]!="Q"&&numStrArr[i]!="q"){//run loop until Quit position is reached 
        intVersion = stoi(numStrArr[i]);
        numArr.insert(numArr.begin()+i,intVersion-1);//insert int version of number into number vector
        //make new array w/ Pokemon versions of what player wants to add 
        //delete these pokemon from pokedex (can't use indexes really since as they are getting erased the index will keep changing)(separate loop for erasing)
        pokeArr.insert(pokeArr.end(), player.pokedex.at(numArr.at(i))); //use index to get new poke from pokedex, and add to poke arr 
        i++; 
    }
    //erase from pokedex 
    for(int n=0;n<pokeArr.size();n++){//for looping thru new array of pokemon, duplicated from pokedex ~~ now need to erase the pokedex versions
        string findName; 
        findName = pokeArr.at(n).getName(); //finding by matching the names of the pokemons
        //findNames: CORRECT //cout << findName << endl; 
        for(int n=0;n<player.pokedex.size();n++){ //loop thru remaining pokedex vector (gets smaller cuz erasing from it)
            if(findName==player.pokedex.at(n).getName()){
                player.pokedex.erase(player.pokedex.begin()+n); //if names match, erase that pokemon from the pokedex 
            }
        }
    }//end erasing from pokedex for loop 
    //add the newArray pokemon to the activePokemon 
    for(int n=0; n<pokeArr.size();n++){
        Pokemon swapActive = player.activePokemon.at(player.activePokemon.size()-1); //gets pokemon from last position in activePokemon to move to pokedex to make space for new activePokemon 
        player.pokedex.insert(player.pokedex.end(), swapActive); //adds old activePokemon to pokedex 
        player.activePokemon.erase(player.activePokemon.end()-1);//erases activePokemon that now exists in pokedex instead 
        player.activePokemon.insert(player.activePokemon.begin(), pokeArr.at(n)); //replaces open spot in activePokemon w/ newly chosen pokemon  
    }//end swapping in new active pokemon for loop 
    return; 
}//end function switchSuiteFromPokedex() 


//------------------TRAINER FUNCTIONS----------------------------------------
/**Checks single tile to see if trainer is @ that tile**/
int Game::checkTrainerByTile(Tile mapTile){ //returns index of trainer that exists @ maptile, else returns -1 if no trainer exists @ mapTile. 
    //15 trainers stored in vector<Player> trainers of Game class
    Tile trainerLocation; 
    for(int t=0;t<trainers.size();t++){
        trainerLocation = trainers.at(t).getLocation(); 
        if(mapTile.getRowNum()==trainerLocation.getRowNum()&&mapTile.getColumnNum()==trainerLocation.getColumnNum()){
            return t; 
        }
    } 
    //after looping thru all of the trainer locations, if there is no location matching the location of 'mapTile', then no trainer @ that location so return -1 
    return -1; 
} 

/**if player runs into unbattled trainer, this function is called so player can battle this trainer**/ 
int Game::fightTrainer(int trainerIndex){ //pass index of wild pokemon in trainer's activePokemon vector that player will battle 
//returns 0 when turn has ended, and 1 if further action needs to be taken, so main battle menu should be displayed (fight, switch, or run options) 
    //same rules as fightWildPokemon, except: fleeing from trainer is not an option, opposing pokemon will always attack back 
    //if player's pokemon faints, go back to battle menu (fight or switch), and trainer's pokemon levels up 
    //if after one of the phases of the attack the trainer's pokemon faints, the next pokemon in line will become the active pokemon for the trainer, and player's pokemon levels up 
    //use same pokemon in fight until it faints?? same rules as wild pokemon battle for end turn i guess?? 

    int fightLoop=0; 
    Pokemon trainerPokemon; 
    trainerPokemon = trainers.at(trainerIndex).getActivePokemon(); 
    //only way trainer fight ends is if either all of trainers or all of player's pokemon faint??? 
    //THIS FUNCTION IS NOT DONE
    //LEFT OFF HERE!!! 
    
    while(trainerPokemon.getHitPoints()!=0||player.getActivePokemon().getHitPoints()!=0){ //loop until either pokemon's HP val reaches 0
        fightLoop++; 
        Pokemon* attacker = &player.activePokemon.at(0); 
        Pokemon* defendant = &trainerPokemon; 
        if(player.getActivePokemon().getSpeed()>trainerPokemon.getSpeed()){ //player's active pokemon has higher speed score 
            attacker = &player.activePokemon.at(0); //pass by reference (changes made to attacker make changes to object instance player.activePokemon)
            defendant = &trainerPokemon; 
        }else{ //trainePokemon's speed is higher than active pokemon's speed score 
            attacker = &trainerPokemon; //pass by reference
            defendant = &player.activePokemon.at(0); 
        }
        cout << attacker->getName() << " attacks first: " << endl; 
        //first attack: 
        int aVal = rand()%attacker->getAttack(); //rand num between 0 and attacker's Attack Strength 
        int dVal = rand()%defendant->getDefense(); //rand num between 0 and defendant's Defense Strength 
        if(aVal>dVal){ //if attacker wins
            defendant->setHitPoints(defendant->getHitPoints()-(aVal-dVal));  
            cout << attacker->getName() << " deals " << aVal << " damage" << endl; 
            cout << "Name: " << attacker->getName() << ", HP: " <<attacker->getHitPoints() << ", A: " <<attacker->getAttack() << ", D: " << attacker->getDefense() << ", S: " << attacker->getSpeed() << ", M: " << attacker->getMaxStrength() << endl; 
            cout << "Name: " << defendant->getName() << ", HP: " <<defendant->getHitPoints() << ", A: " <<defendant->getAttack() << ", D: " << defendant->getDefense() << ", S: " << defendant->getSpeed() << ", M: " << defendant->getMaxStrength() << endl; 
        }//else, defender wins and nothing happens 
    //check if turn has ended 
        if(trainerPokemon.getHitPoints()==0){ //if trainer pokemon fainted
            //HP points restored and added to player's pokedex 
            cout << trainerPokemon.getName() << " has fainted! This pokémon has been added to your collection, and your active pokémon, " << player.getActivePokemon().getName() << " has moved up to level " << player.getActivePokemon().getLevel() << "." << endl; 
            Pokemon originalPoke = stoPokemon(trainerPokemon.getName()); 
            //reset stats for trainerPoke: 
            trainerPokemon.setHitPoints(originalPoke.getHitPoints()); 
            //add trainerPoke to player array, and erase it from trainerPoke vector 
            player.addPokemon(trainerPokemon); 
            //level up active pokemon: 
            player.getActivePokemon().levelUp(); 
            //erase pokemon from trainer's active pokemon 
            trainers.at(trainerIndex).activePokemon.erase(trainers.at(trainerIndex).activePokemon.begin()); //erases activePokemon, new activePokemon automatically set 
            if(trainers.at(trainerIndex).activePokemon.size()==0){//if all of trainer's pokemon have fainted 
                cout << "That was the trainer's last awake pokémon. You earn 1 badge, 5 pokéballs, and 60 points!" << endl; 
                player.setBadges(player.getBadges()+1); 
                player.setPokeballs(player.getPokeballs()+5); 
                player.setPoints(player.getPoints()+60); 
                trainers.erase(trainers.begin()+trainerIndex); //removes trainer so trainer cannot be battled again: 
                return 0; //turn is over 
            }
        }//end if (trainer's pokemon fainted) statement 
        else if(player.getActivePokemon().getHitPoints()==0){ //if player's active pokemon fainted 
            //this pokemon can't be sent to battle until its HitPoints get restored @ a pokemon center 
            //wild pokemon levels up 
            cout << "Your pokémon, " << player.getActivePokemon().getName() << ", has fainted. You are not able to use this pokémon until its hit points are restored at a pokémon center." << endl; 
            player.setDeadPokemon(player.getActivePokemon());
            player.activePokemon.erase(player.activePokemon.begin()+0); //idx0=activePokemon 
            //level up wild poke: 
            trainerPokemon.levelUp(); 
            if(player.activePokemon.size()==0){ //if player has no more awake pokemon after pokemon faints: 
                cout << "That was your last awake pokémon in your party. You have been transported to the nearest pokémon center to revive at least one of your pokémon before continuing." << endl;  
                //teleport player to nearest pokemon center 
                vector<Tile> centerLocations = getLocationsOfType("C");
                for(int n=0; n<10; n++){
                    int nearestCenterIdx = checkLocationTypeByRange(n,n,centerLocations); //increases range by 1 every loop 
                    if(nearestCenterIdx>0){ //tile found
                        //set player location to this tile 
                        player.setLocation(centerLocations.at(nearestCenterIdx).getRowNum(), centerLocations.at(nearestCenterIdx).getColumnNum());
                        return 0; //turn over  
                    }
                }
                //if it reaches this point, can't find center in the 200 tiles (10*10 range) around it 
                player.setLocation(centerLocations.at(0).getRowNum(), centerLocations.at(0).getColumnNum()); //fail safe option 
                trainers.erase(trainers.begin()+trainerIndex); //removes trainer so trainer cannot be battled again: 
                return 0; //turn over  
            }//end if no more activePoke left in player's pokemon 
        } //end if(player's active pokemon fainted) statement
    }//end run fight loop while statement 
}//end function fightTrainer


//-----------Random Events----------------------------------
Pokemon Game::getSpawnPokemon(){ //returns random pokemon from index 
    return pokemonIndex[rand()%152]; 
}

//------------private member function: split function------------
int Game::split(string words, char delimiter, string arr[], int lengthArr){
 //invalid variable test: 
     if(words==""){
       return 0; 
     }
     
     int delimiterCount = 0; //return value: number of groups words is split into
     int piecesSplit = 0; //array index of groups words is split into 
     int startPos = 0; //starting position for the NEXT array (makes sure it skips over the delimiter)
     int interval = 0; //which number character in the string 'words' we are on. 
     std::string strDelimiter(1,delimiter); 
     for(int interval=0; interval <= words.length(); interval++){ //run loop for length = number of characters entered into the string 'words'
         char wordsChar = (char)words[interval]; //casting one character at a time (determined by interval) to a character named wordsChar
         if(wordsChar == delimiter||interval==words.length()){                                                                //if wordsChar == delimiter
             arr[piecesSplit] = words.substr(startPos, (interval-startPos));   //in the position of [piecesSplit] (which element in the array we are on), add the substring from 'words' that begins in the position where the previous delimiter ended, run for the length of the difference between the current interval and the previous delimiter. 
             startPos = interval+1;
             
             if((arr[piecesSplit] != "")&&(arr[piecesSplit] != strDelimiter)){ //this is if it is on SECOND dilimiter in a row 
              delimiterCount = delimiterCount + 1; 
              piecesSplit = piecesSplit + 1; 
              //arr[piecesSplit] = words.substr(startPos, (words.length()-startPos)); //covers last interval of the string and places it in last position of an array.
             }
         }
     }
     if(piecesSplit == 0){
         arr[0] = words;
     }
     return delimiterCount; 
}


void Game::assignWildPokemonRandomLocation(int index){ 
    int randIdx; //index for setting location of wildPokemon
    vector<Tile> plainTiles = getLocationsOfType("p");
    Tile newTile = plainTiles.at(index); 
    for(int wp=0; wp<20; wp++){
        //if(wildPokemon.at(wp).getLocation().equal(newTile)){//if tile already occupied by wildPokemon
        if(wildPokemon.at(wp).getLocation().getRowNum()==newTile.getRowNum()&&wildPokemon.at(wp).getLocation().getColumnNum()==newTile.getColumnNum()){ //if tile already occupied by wildPokemon
            randIdx = rand()%(plainTiles.size()); //get new random index
            newTile = plainTiles.at(randIdx); //get new random tile
            wp==0; //start loop over 
        }
    } //@exitLoop, plainTile.at(randIdx) is okay to move to because it is not occupied by a wildPoke
    wildPokemon.at(index).setLocation(newTile);
}



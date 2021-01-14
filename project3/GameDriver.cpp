#include <iostream>
#include <istream>
using namespace std;
#include "Tile.h"
#include "Game.h"
#include "Player.h"
#include "Pokemon.h" 
//é


//~~~~~initializers~~~~~
string convertStr; 
int starterPokeNum; 
Game game1;
string username; 
//~~~~~~~~~~~~~~~~~~~~~~
//reads both the map txt file and the pokemon txt file 
void readFiles(){
    game1.readMap("mapPoke.txt"); 
    //display map function? 
    game1.readPokemon("pokemon.txt"); 
    //add starterPokemon to activePokemon array 
}
void welcomePlayer(){
//welcome statements: creates new player instance and new game instance, set username and choose starting pokemon
   //Set Username: 
   cout << "Welcome to Pokémon! " << endl << "Please state your name: "; 
   //use getline for username cin so it doesn't get error from more than one word entered. 
   getline(cin, username); 
   game1.player.setUsername(username); 
   cout << endl; 
   //Choose Starter Pokemon: 
   cout << "Welcome, " << username << "! Before you can begin your Pokémon adventure, you must choose a starting Pokémon, courtesy of the Professor. Please choose from the following Pokémon:" << endl; 
   cout << "1. Bulbasaur" << endl << "2. Charmander" << endl << "3. Squirtle" << endl << "4. Pikachu" << endl; 
   cin >> convertStr;
   
   while(starterPokeNum!=1&&starterPokeNum!=2&&starterPokeNum!=3&&starterPokeNum!=4){
       cout << "Invalid entry, please choose a number between 1 and 4!" << endl; 
       cin >> starterPokeNum; 
   }
   Pokemon starterPoke;
   switch(starterPokeNum){ //add starting locations on map to each of these case statements. 
        case 1: 
            starterPoke = game1.stoPokemon("Bulbasaur");
            game1.player.setLocation(13,7);
            break; 
        case 2: 
            starterPoke = game1.stoPokemon("Charmander"); 
            game1.player.setLocation(13,8); 
            break; 
        case 3: 
            starterPoke = game1.stoPokemon("Squirtle");
            game1.player.setLocation(13,9);
            break;
        case 4: 
            starterPoke = game1.stoPokemon("Pikachu"); 
            game1.player.setLocation(13,10); 
            break; 
   }
   game1.player.addPokemon(starterPoke); 
}
void startGame(){
    game1.createTrainers(); //places trainers on map
    game1.createWildPokemon(); //places wild poke on map
}
int newTurn(){
    game1.printMap(); //displays map on screen 
    cout << "Hello, " << game1.player.getUsername() <<"! You have " << game1.player.getPokeballs() << " Pokéball left and your Pokémon are strong." << endl; 
    cout << "Your Active Pokémon is: " << endl; 
    game1.player.printActivePokemon(); //displays player's active pokemon and stats 
    
    cout << "Please choose from the following options: " << endl; 
    cout << "1. Travel" << endl << "2. Rest" << endl << "3. Try your luck" << endl << "4. Quit the game" << endl; 
    int num; 
    cin >> num; 
    while(num>4||num<1){
        cout << "Invalid entry. Please choose a number between 1 and 4!" << endl; 
        cin >> num; 
    }
    switch(num){
        case 1: //travel 
            cout << "Which direction would you like to travel? " << endl; 
            cout << "1. North" << endl << "2. East" << endl << "3. South" << endl << "4. West" << endl; 
            int numDir; 
            cin >> numDir;
            while(numDir>4||numDir<1){
                cout << "Invalid entry. Please choose a number between 1 and 4!" << endl; 
                cin >> numDir; 
            }
            int checkMove; 
            checkMove = game1.movePlayer(numDir); //checks that tile is ok to move to, and automatically updates player location info 
            //will automatically print error message to screen if player can't move to chosen tile 
            //returns 0 if tile is ok to move to (meaning player location has been updated)
            //returns 1 if new direction needs to be chosen (and prints message to screen also) 
            while(checkMove==1){
                cin >> numDir; 
                checkMove = game1.movePlayer(numDir);
            }
            break; 
        case 2: //rest
            //+1 hp for every pokemon in player's party
            //player's pokeballs goes down by 1 
            game1.restPlayer();  
            break; 
        case 3: //try your luck
            //if wildPoke located w/in 7*7 (mapView) are around player, 50% chance of cating it for free (number of pokeballs does not change like normal fights)
            game1.tryLuck(); 
            break; 
        case 4: //quit game
            cout << "You have chosen to quit the game.";
            return 1; 
    }
    game1.scatterWildPokemon(); //getting segFault for scatter 
    return 0; //meaning player didn't choose 'quit game' option and game should continue  
}

void wildPokeEncounter(){
    //1st check = wild pokemon w/in 2 tiles in every direction (5*5 square around player location)
    int index = game1.checkWildPokeByRange(5,5); //returns index of pokemon in wildPokemon vector that is w/in range of player
    //negNumber = no poke in range, posNumber = index of pokemon in wildPokemon vector 
    if(index<0){
        //no wild pokemon in range
        return; 
    }
    //if(index>0){
    else{ //player has encountered a wild pokemon 
        cout << endl; 
        cout << "You ran into a wild Pokémon!" << endl; 
        cout << "Name: " << game1.wildPokemon.at(index).getName() << ", HP: " << game1.wildPokemon.at(index).getHitPoints() << ", A: " << game1.wildPokemon.at(index).getAttack() << ", D: " << game1.wildPokemon.at(index).getDefense() << ", S: " << game1.wildPokemon.at(index).getSpeed() << ", M: " << game1.wildPokemon.at(index).getMaxStrength() << endl; 
        cout << endl; 
        cout << "Your ACTIVE Pokémon is: " << endl; 
        game1.player.printActivePokemon(); 
        cout << endl; 
        
        int checkEndTurn=-1; 
        while(checkEndTurn==-1){
            cout << "What do you want to do? (pick 1,2, or 3)" << endl ;
            cout << "  1. Fight" << endl << "  2. Switch Active Pokémon" << endl << "  3. Run" << endl; 
            int num; 
            cin >> num; 
            while(num>3||num<1){
                cout << "Invalid entry, please choose a number betweeen 1 and 3" << endl;
                cin >> num; 
            }
            bool suiteContains; 
            switch(num){
                case 1: //fight 
                    checkEndTurn = game1.fightWildPokemon(index); //returns -1 if menu should be re-displayed, returns 0 if turn is over 
                    break; 
                case 2: //switch active pokemon 
                    if(game1.player.activePokemon.size()<2){
                        cout << "Doesn't look like you have any other Pokémon to replace your current Active Pokémon! Once you defeat other pokémon you will be able to use them in battle." << endl; 
                        checkEndTurn=-1; 
                        break; 
                    }
                    cout << "Pick another Active Pokémon: " << endl; 
                    suiteContains = game1.player.printPokemonSuite(); 
                    if(suiteContains==true){
                        int num1; 
                        cin >> num1; 
                        while(num1<1||num1>game1.player.activePokemon.size()-1){
                            cout << "Invalid entry, please choose a number between 1 and " << game1.player.activePokemon.size()-1 << endl; 
                            cin >> num1; 
                        }
                        game1.player.switchActivePokemon(num1); 
                        //set new active Pokemon(set to index 0 in activePokemon vector)
                        cout << "Your new active pokémon is: "; 
                        game1.player.printActivePokemon(); 
                    }
                    break; 
                case 3: //run
                    checkEndTurn = game1.runFromWildPokemon(index); //returns -1 if menu should be displayed again
                    //if 0 returned, turn over, and player relocated @ a pokemon center 
                    break; 
            }//end switch statement 
        }//end while(checkEndTurn==-1) statement
        //if player was transported to a pokemon center because all their pokemon fainted and they lost the batttle:     
        //check to make sure that return statments in game.cpp functions are correct; specifically the one 
    }//end if(wildPokemonEncounter Menu/Functions) statement
}//end wildPokeEncounter function 

void pokemonCenter(){        
    if(game1.player.getLocation().getType()=="C"){ //if player travled or was transported to pokemon center 
        for(int i=0; i<game1.player.activePokemon.size();i++){
            //restore HP of all player's active Pokemon 
            Pokemon originalPoke; 
            originalPoke = game1.stoPokemon(game1.player.activePokemon.at(i).getName()); //finds pokemon in pokemon index 
            game1.player.activePokemon.at(i).setHitPoints(originalPoke.getHitPoints()); //resets HP points 
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
            game1.player.printPokedex(); 
            string numbers;
            cin.ignore(); 
            getline(cin, numbers);
            game1.switchSuiteFromPokedex(numbers); 
            cout << "Here are your new 6 Pokémon you've chosen. Please choose which one should be the Active pokémon: " << endl; 
            game1.player.printPokemonSuite(); //prints all 6 pokemon 
            int num; 
            cin >> num; 
            game1.player.switchActivePokemon(num);
            cout << "Your new active Pokémon is: " << endl; 
            game1.player.printActivePokemon(); 
            return; 
        }
    }else{//trainer not at pokemon center
        //move onto next function in main() 
        return;
    }
}

void trainerEncounter(){
    //2nd check = trainers (exist @ gym tiles)
    //if player is @ a gym and a trainer is there, they have to battle trainer 
    //once player battles trainer @ gym, they cannot battle that trainer again. 
    if(game1.player.getLocation().getType()=="G"){
        cout << "You have arrived at a Gym ";
        int trainerIndex; 
        trainerIndex = game1.checkTrainerByTile(game1.player.getLocation()); //returns index of trainer in trainers vector (returns -1 if no trainer exists @ this location)
        if(trainerIndex<0){//no trainer @ Gym meaning player has already battled this trainer 
            cout << "with a trainer you have already battled." << endl; 
            return; 
        }else{ //unbattled trainer @ gym where player is 
                //trainers.at(trainerIndex) == trainer player will battle 
            cout << "and a trainer is there. They want to fight." << endl << "Their active Pokémon is: " << endl; 
            game1.fightTrainer(trainerIndex);
            cout << "Name: "; 
            game1.trainers.at(trainerIndex).printActivePokemon();
            cout << endl; 
            cout << "Your ACTIVE Pokémon is: " << endl; 
            game1.player.printActivePokemon(); 
            cout << endl; 
            int checkEndTurn=-1; 
            while(checkEndTurn==-1){
                cout << "What do you want to do? (pick 1,2, or 3)" << endl ;
                cout << "  1. Fight" << endl << "  2. Switch Active Pokémon" << endl << "  3. Run" << endl; 
                int num; 
                cin >> num; 
                while(num>3||num<1){
                    cout << "Invalid entry, please choose a number betweeen 1 and 3" << endl;
                    cin >> num; 
                }
                bool suiteContains;
                int checkEndTurn; 
                switch(num){
                    case 1: //fight 
                        //same rules as wild pokemon fight 
                        checkEndTurn = game1.fightTrainer(trainerIndex); //returns -1 if menu should be re-displayed
                            //returns 0 if turn is over, and will therefore exit while(checkEndTurn==-1) loop 
                        break; 
                    case 2: //switch active pokemon 
                        cout << "Pick another Active Pokémon: " << endl; 
                        suiteContains = game1.player.printPokemonSuite(); 
                        if(suiteContains==true){
                            int num1; 
                            cin >> num1; 
                            while(num1<1||num1>game1.player.activePokemon.size()-1){
                                cout << "Invalid entry, please choose a number between 1 and " << game1.player.activePokemon.size()-1 << endl; 
                                cin >> num1; 
                            }
                            game1.player.switchActivePokemon(num1); 
                            //set new active Pokemon(set to index 0 in activePokemon vector)
                            cout << "Your new active pokémon is: "; 
                            game1.player.printActivePokemon(); 
                        }
                        break;
                }//end switch statement 
            }//end while(checkEndTurn==-1)statement
        }//end if(unbattled trainer exists at tile) statement 
    }//end if(if trainer @ gym tile) statement 
}//end trainerEncounter() function

void randomEvents(){
    int enterNum; //used repeatedly for cin statement
    int randNum; //used repeatedly for generating random number
    //Random Event 1 
        //wild pokemon spawns in player's path  //30% chance another wild pokemon spawns in player's path; ask player if they want to catch or release 
        //if player chooses to catch it, pokeballs-1, player gets new pokemon
    randNum = rand()%10+1; 
    if(randNum<=3){ //30% chance 
        Pokemon spawnPokemon; 
        spawnPokemon = game1.getSpawnPokemon();
        cout << "Suddenly, " << spawnPokemon.getName() << " appears in your path. Do you want to:" << endl; 
        cout << "   1. Catch it" << endl << "   2. Release it" << endl; 
        cin >> enterNum; 
        while(enterNum>2||enterNum<1){
            cout << "Invalid entry, please choose between the numbers 1 and 2." << endl; 
            cin >> enterNum; 
        }
        switch(enterNum){
            case 1: //catch pokemon 
                game1.player.addPokemon(spawnPokemon); //add pokemon 
                game1.player.setPokeballs(game1.player.getPokeballs()-1); //subtract 1 pokeball
                cout << "Awesome! " << spawnPokemon.getName() << " was added to your Pokémon." << endl; 
                break; 
            case 2: //release pokemon
                //nothing happens 
                break; 
        }
    }
    //Random Event 2 
        //25% chance player discovers hidden treasure
        //if treasure found, 50-50 chance that treasure is either +2 pokeballs or magic food that makes one pokemon levelUp. 
    randNum = rand()%4+1; 
    if(randNum==1){ //25% chance
        randNum = rand()%2+1; 
        if(randNum==1){ //pokeball treasure
            cout << "Great news! You have stumbled upon a hidden stash of Pokéballs."; 
            game1.player.setPokeballs(game1.player.getPokeballs()+2); 
            cout << "Your reserves increased to " << game1.player.getPokeballs() << " pokéballs." << endl; 
        }else{ //randNum==2, and treasure is magic food for levelUp
            cout << "Great news! You have stumbled upon a hidden stash of Poffins. Your Pokémon are delighted. Choose one of them to feast on the Poffins and Level Up: " << endl; 
            game1.player.printPokemonSuite(); 
            cin >> enterNum; 
            game1.player.activePokemon.at(enterNum-1).levelUp(); //levels up the pokemon chosen thru cin statement 
            cout << game1.player.activePokemon.at(enterNum-1).getName() << " is now at level " << game1.player.activePokemon.at(enterNum-1).getLevel(); 
        }
    }
    //Random Event 3
        //20% chance one of player's pokemon ages out and dies; pokemon removed from player's party 
    randNum = rand()%5+1; 
    if(randNum==1){ //20% chance
        randNum = rand()%(game1.player.activePokemon.size()); //randNum between 0 and (size-1)
        cout << "Oh no! After years of legendary battles, " << game1.player.activePokemon.at(randNum).getName() << " died of old age. Thank you for your companionship, dear friend." << endl; 
        game1.player.activePokemon.erase(game1.player.activePokemon.begin()+randNum); //erase from player's pokemon suite
    }
}//end randomEvents() function

int endGame(){ //return 1 if player wins and game is over 
    if(game1.player.getBadges()>=6){ //if player aquires 6 badges
        cout << "You have aquired 6 badges and have won the game!" << endl; 
        return 1; //game over 
    }
    else if(game1.player.activePokemon.size()==6&&game1.player.pokedex.size()>=2){ //if player has at least 8 pokemon
        //count DIFFERENT pokemon in player's collected pokemon (includes pokedex) 
        int diffPokeCount=game1.player.activePokemon.size()+game1.player.pokedex.size(); //set pokeNum to total pokemon 
        //check that all are different: 
        bool duplicate; 
        vector<Pokemon> diffPoke; //if pokemon doesn't already exist, add to vector 
        for(int a=0; a<game1.player.activePokemon.size();a++){ //for loopping thru activePokemon vector 
            duplicate = false; //resets duplicate check to false every time it moves to new active Pokemon 
            for(int i=0; i<diffPoke.size(); i++){ //for looping thru diffPoke vector 
                if(game1.player.activePokemon.at(a).getName()==diffPoke.at(i).getName()){
                    //there is a duplicate, so don't add this activePokemon to the diffPoke vector  
                    duplicate = true; 
                }
            }
            if(duplicate==false){
                diffPoke.insert(diffPoke.end(), game1.player.activePokemon.at(a)); 
            }
        }
        //repeat above steps for pokedex
        for(int p=0; p<game1.player.pokedex.size();p++){ //for looping thru pokedex vector 
            duplicate = false; //resets duplicate check for every new pokemon check 
            for(int i=0;i<diffPoke.size();i++){ //for looping thru diffPokevector
                if(game1.player.pokedex.at(p).getName()==diffPoke.at(i).getName()){
                    //there is a duplicate, so don't add this pokemon to the diffPoke vector 
                    duplicate = true; 
                }
            }
            if(duplicate==false){
                diffPoke.insert(diffPoke.end(), game1.player.pokedex.at(p)); 
            }
        }
        //size of diffPoke vector = number of different pokemon player has aquired. if number>=8, then player wins game 
        if(diffPoke.size()>=8){
            cout << "You have aquired 8 different pokemon and have won the game!" << endl; 
            return 1; //game over 
        }else{ //player doesn't have enough different pokemon to win the game 
            return 0; //continue playing
        }
    }//end 2nd win check: if player has 8 diff pokemon 
    else{ //did not meet any previous criteria to win the game 
        return 0; //continue playing 
    }
}
    



int main(){
    int endCheck = 0; //when game ends, set endCheck=1
     //start game stuff: 
    readFiles();
    welcomePlayer();
    startGame(); 
    
    while(endCheck==0){
        //begin a new turn: 
        int continueGame = newTurn();
        if(continueGame==1){
            //call endGame function
            cout << " Better luck next time!" << endl; 
            endCheck = 1; //player chose 'quit game' option 
        }else{
            cout << endl;
            cout << game1.player.getLocation().getType(); 

            //Check For Encounters
            wildPokeEncounter();
            cout << game1.player.getLocation().getType(); 
            pokemonCenter();
            trainerEncounter(); 
            pokemonCenter(); 
            
            //Random Events 
            //randomEvents(); 
            //need to go over fight wild pokemon function.... not sure if while loop is correct! read thru directions
             
            //End Game
            endCheck = endGame(); //returns 1 when player wins 
            
            //game1.printMap(); 
            //getting seg fault from Game::movePlayer() if player tries to move out of bounds... fix this! 
        }
    }
}

 

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>


using namespace std;


/*Each of the obstacles has a value(coordinate),
Also to create a binary array of if the value is at grid point
we give each obstacle a digit in 4 bit number
*/
static int Monster; //0001 (1)
static int pit1; //0010 (2)
static int pit2; // 0100 (4)
static int pit3; // 1000 (8)
static int occupied[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int pitP[25] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}; // All spots start with prob of 4 %
static int monsterP[25] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

struct hunter{
	int x;// only need one value because there are only 16 possible places
	//int y;

	int arrows; // Number of arrows left;

	char* name;
};

int randomNumbers(int min, int max)
{
    srand(time(0));
    // rand() % (max-min+1) + min
    return (rand() % (max-min+1)) + min;
}

void move(struct hunter *Hero){
	printf("Would you like to shoot North (N), South (S), East (E), or West (W)?\n");

	string dir;

	getline(cin, dir);

	while(dir != "N" && dir != "E" && dir != "S" && dir != "W"){
		printf("Please type either 'N', 'E', 'S', or 'W'\n");
		getline(cin, dir);
	}

	if(dir == "N"){ //Shooting "North"
		if(Hero->x > 19)
		{
			printf("You are already at the top of the map, you can't move North.\n");
			return;
		}else if(occupied[(Hero->x) + 5] == 1){
			printf("You have been eaten by the Crocotta!!\nGAME OVER!!\n");
			exit(0);
		}else if(occupied[(Hero->x) + 5] & 14)
		{
			printf("You have fallen into a pit!!\nGAME OVER!!\n");
			exit(0);
		}
		else{
			occupied[Hero->x] = 0;
			Hero->x = Hero->x + 5;
			occupied[Hero->x] = 1;
			pitP[Hero->x] = 0; // We didn't die traveling here, so prob of monster or pit is 0
			monsterP[Hero->x] = 0;
			return;
		}
	}else if(dir == "S"){ //Shooting "North"
		if(Hero->x < 5)
		{
			printf("You are already at the bottom of the map, you can't move South.\n");
			return;
		}else if(occupied[(Hero->x) - 5] == 1){
			printf("You have been eaten by the Crocotta!!\nGAME OVER!!\n");
			exit(0);
		}else if(occupied[(Hero->x) - 5] & 14)
		{
			printf("You have fallen into a pit!!\nGAME OVER!!\n");
			exit(0);
		}
		else{
			occupied[Hero->x] = 0;
			Hero->x = Hero->x - 5;
			occupied[Hero->x] = 1;
			pitP[Hero->x] = 0;
			monsterP[Hero->x] = 0;
			return;
		}
	}else if(dir == "W"){ //moving west
		if((Hero->x)%5 == 0)
		{
			printf("You are already at the left edge of the map, you can't move West.\n");
			return;
		}else if(occupied[(Hero->x) - 1] == 1){
			printf("You have been eaten by the Crocotta!!\nGAME OVER!!\n");
			exit(0);
		}else if(occupied[(Hero->x) - 1] & 14)
		{
			printf("You have fallen into a pit!!\nGAME OVER!!\n");
			exit(0);
		}
		else{
			occupied[Hero->x] = 0;
			Hero->x = Hero->x - 1;
			occupied[Hero->x] = 1;
			pitP[Hero->x] = 0;
			monsterP[Hero->x] = 0;
			return;
		}
	}else if(dir == "E"){ //Shooting "North"
		if((Hero->x)%5 == 4)
		{
			printf("You are already at the right edge of the map, you can't move East.\n");
			return;
		}else if(occupied[(Hero->x) + 1] == 1){
			printf("You have been eaten by the Crocotta!!\nGAME OVER!!\n");
			exit(0);
		}else if(occupied[(Hero->x) + 1] & 14) //check if its one of pits (1110)
		{
			printf("You have fallen into a pit!!\nGAME OVER!!\n");
			exit(0);
		}
		else{
			occupied[Hero->x] = 0;
			Hero->x = Hero->x + 1;
			occupied[Hero->x] = 1;
			pitP[Hero->x] = 0;
			monsterP[Hero->x] = 0;
		}
	}
}

void shootArrow(struct hunter* Hero){
	printf("You chose to fire an arrow!\nIf you hit the Crocatta you win!\nIf you miss he will run away to somewhere else.\nWould you like to shoot North (N), South (S), East (E), or West (W)?\n");

	string aim;

	getline(cin, aim);

	while(aim != "N" && aim != "E" && aim != "S" && aim != "W"){
		printf("Please type either 'N', 'E', 'S', or 'W'\n");
		getline(cin, aim);
	}

	if(aim == "N"){ //Shooting "North"
		if(Hero->x > 19)
		{
			printf("You are already at the top of the map, you shot at nothing.\n");
		}else if(occupied[(Hero->x)+5] == 1){
			printf("You shot the Crocotta!\nCongratulations you have won the game!\n");
			exit(0);
		}else{
			printf("You missed the Crocotta!\n");
		}
	}else if(aim == "S"){
		if(Hero->x < 5)
		{
			printf("You are already at the bottom of the map, you shot at nothing.\n");
		}else if(occupied[(Hero->x)-5] == 1){
			printf("You shot the Crocotta!\nCongratulations you have won the game!\n");
			exit(0);
		}else{
			printf("You missed the Crocotta!\n");
		}
	}else if(aim == "E"){
		if((Hero->x)%5 == 4)
		{
			printf("You are already at the right edge of the map, you shot at nothing.\n");
		}else if(occupied[(Hero->x)+1] == 1){
			printf("You shot the Crocotta!\nCongratulations you have won the game!\n");
			exit(0);
		}else{
			printf("You missed the Crocotta!\n");
		}
	}else{ // West
		if((Hero->x)%5 == 0)
		{
			printf("You are already at the left edge of the map, you shot at nothing.\n");
		}else if(occupied[(Hero->x)-1] == 1){
			printf("You shot the Crocotta!\nCongratulations you have won the game!\n");
			exit(0);
		}else{
			printf("You missed the Crocotta!\n");
		}
	}

	if(Hero->arrows == 1){
		printf("You have run out of arrows...\nGAME OVER!!\n");
		exit(0);
	}else{
		printf("The Crocotta has run away to a new coordinate\n");
		Hero->arrows = Hero->arrows - 1;

		printf("You have %d arrow left.\n", Hero->arrows);

		int tmp = Monster; //this helps ensure monster doesnt' end up at same place
		bool leave = false;
		while(!leave){
			Monster = randomNumbers(0, 24);

			//Monster.y = rand() % 5;

			if(!occupied[Monster]){
				leave = true;
				occupied[Monster] = 1; // Monster now occupies this space
			}
		}

		occupied[tmp] = 0;
		cout<<"Monster coordinates : "<< Monster << endl;
		return;
	}
}

int printSurroundings(int x){
	if(x == 1){
		printf("I hear panting\n");
		return x;
	}else if(x & 14){ // will be not 0 if has any 1110
		printf("I feel a breeze\n");
		return x;
	}
	return x;
}

int checkSurroundings(int x){
	/*Using a 4-bit number we can use to check if there is a 
	monster: 0001 (1)
	pit1: 0010 (2)
	pit2: 0100 (4)
	pit3: 1000 (8)
	*/


	int clear = 0; // start with 0 and use inclusive or to add to array

	if(x> 4){ // if less than 4 we don't need to check below
		clear = clear | printSurroundings(occupied[x - 5]);
	}
	if(x < 20){ //if not on top edge, check top
		clear = clear | printSurroundings(occupied[x + 5]);
	}
	if((x % 5) != 0){ //if it's not on the left edge check left
		clear = clear | printSurroundings(occupied[x - 1]);
	}
	if((x % 5) != 4){ // If it's not on the right edge, check right
		clear = clear | printSurroundings(occupied[x + 1]);
	}
	//printf("Clear: %d\n", clear);
	if(clear == 0){
		printf("Silence\n");
	}
	printf("Clear: %d\n", clear);

	return clear;
}

void printCoordinates(int i){
	int y = i / 5;

	int x = (i % 5);

	cout<<"You are now located at the coordinates: ("<< x<<", "<<y<<")\n";
	return;
}

void adjustProb(int status, int loc){
	printf("Adjust Prob\n");
	if(status == 0){ // If the status = 0 all nearby blocks prob equals 0
		if(loc > 4){
			pitP[loc - 5] = 0;
			monsterP[loc - 5] = 0;
		}
		if(loc < 20){
			pitP[loc + 5] = 0;
			monsterP[loc + 5] = 0;
		}
		if((loc % 5) != 0){
			pitP[loc - 1] = 0;
			monsterP[loc - 1] = 0;
		}
		if((loc % 5) != 4){
			pitP[loc + 1] = 0;
			monsterP[loc + 1] = 0;
		}
		return;
	}
	if(status & 1){ //If the monster is near
		/* Count how many of the nearby blocks are 0
		those blocks can be eliminates
		*/
		//printf("Monster near\n");

		int count = 0;
		int possible = 0;
		if(loc > 4){
			if(monsterP[loc - 5] != 0){ // If the prob != 0 it is possible
				possible++;
			}
			//count++;
		}
		if(loc < 20){
			if(monsterP[loc + 5] != 0){
				possible++;
			}
			//count++;
		}
		if((loc % 5) != 0){
			if(monsterP[loc - 1] != 0){
				possible++;
			}
			//count++;
		}
		if((loc % 5) != 4){
			if(monsterP[loc + 1] != 0){
				possible++;
			}
			//count++;
		}
		int prob = 100 / possible;

		// Now we have to go back through and assign this probability
		if(loc > 4){
			if(monsterP[loc - 5] != 0){ // If the prob != 0 it is possible
				monsterP[loc - 5] = prob;
			}
		}
		if(loc < 20){
			if(monsterP[loc + 5] != 0){
				monsterP[loc + 5] = prob;
			}
		}
		if((loc % 5) != 0){
			if(monsterP[loc - 1] != 0){
				monsterP[loc - 1] = prob;
			}
		}
		if((loc % 5) != 4){
			if(monsterP[loc + 1] != 0){
				monsterP[loc + 5] = prob;
			}
		}

		//This is a super important part, we need to assing 0 to all other blocks not near

		for(int i = 0; i< 25; i++){
			if(monsterP[i] != prob){
				monsterP[i] = 0;
			}
		}
		//return;
	}
	if((status & 14) == 0){ // if no pits, we can return
		return;
	}

	int pitNum = ((status & 8) >> 3) + ((status & 4) >> 2) + ((status & 2) >> 1);
	printf("pitNum: %d\n", pitNum);

	int possible = 0;

	if(loc > 4){
		if(pitP[loc - 5] != 0){ // If the prob != 0 it is possible
			possible++;
		}
		//count++;
	}
	if(loc < 20){
		if(pitP[loc + 5] != 0){
			possible++;
		}
		//count++;
	}
	if((loc % 5) != 0){
		if(pitP[loc - 1] != 0){
			possible++;
		}
		//count++;
	}
	if((loc % 5) != 4){
		if(pitP[loc + 1] != 0){
			possible++;
		}
	}
	int pitProb = (100 * pitNum) / possible;

	if(loc > 4){
		if(pitP[loc - 5] != 0){ // If the prob != 0 it is possible
			pitP[loc - 5] = pitProb;
		}
	}
	if(loc < 20){
		if(pitP[loc + 5] != 0){
			pitP[loc + 5] = pitProb;
		}
	}
	if((loc % 5) != 0){
		if(pitP[loc - 1] != 0){
			pitP[loc - 1] = pitProb;
		}
	}
	if((loc % 5) != 4){
		if(pitP[loc + 1] != 0){
			pitP[loc + 5] = pitProb;
		}
	}


	return;
}

void printProb(){
	for (int i = 0; i < 25; i++){
		printf("Location %d: pitP: %d monsterP: %d\n", i, pitP[i], monsterP[i]);
	}
}

void printOptions(int loc){
	if(loc > 4){
		printf("Moving down to location %d has pitP: %d and monsterP %d\n", (loc-5), pitP[loc-5], monsterP[loc-5]);
	}
	if(loc < 20){
		printf("Moving up to location %d has pitP: %d and monsterP %d\n", (loc+5), pitP[loc+5], monsterP[loc+5]);
	}
	if((loc % 5) != 0){
		printf("Moving left to location %d has pitP: %d and monsterP %d\n", (loc-1), pitP[loc-1], monsterP[loc-1]);
	}
	if((loc % 5) != 4){
		printf("Moving right to location %d has pitP: %d and monsterP %d\n", (loc+1), pitP[loc+1], monsterP[loc+1]);
	}
}
/*struct obstacle{ // Monster and pits only need coordinates
	int x;
	//int y; //Coordinates of the Crocotta
};*/

int main()
{
	//occupied = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	string name;

	printf("Welcome to Track the Crocotta!!\n");

	printf("Please enter the name of your Hunter:\n");

	getline(cin, name);

	cout<< "Welcome "<< name<<" your mission, should you choose to accept it, is to find the vicous Crocotta monster and kill it!" <<endl;

	struct hunter Hero;
	Hero.arrows = 2;

	Hero.x = randomNumbers(0, 24);

	//cout<< "Hero coordinates: "<< Hero.x<<endl;
	occupied[Hero.x] = 1;
	//Hero.y = rand() % 5;

	//cout<< "You will start your mission at the coordinates ("<< Hero.x<<", "<<Hero.y<<")\n";

	bool leave = false;
	while(!leave){
		Monster = randomNumbers(0, 24);

		//Monster.y = rand() % 5;

		if(!occupied[Monster]){
			leave = true;
			occupied[Monster] = 1; // Monster now occupies this space
		}
	}
	//cout<<"Monster coordinates : "<< Monster << endl;
	leave = false;
	while(!leave){
		pit1 = randomNumbers(0, 24);

		//Monster.y = rand() % 5;

		if(!occupied[pit1]){
			leave = true;
			occupied[pit1] = 2;
		}
	}
	leave = false;
	while(!leave){
		pit2 = randomNumbers(0, 24);

		//Monster.y = rand() % 5;

		if(!occupied[pit2]){
			leave = true;

			occupied[pit2] = 4;
		}
	}
	leave = false;
	while(!leave){
		pit3 = randomNumbers(0, 24);

		//Monster.y = rand() % 5;

		if(!occupied[pit3]){
			leave = true;
			occupied[pit3] = 8;
		}
	}
	printf("Monster: %d\nPit1: %d\nPit2: %d\nPit3: %d\n", Monster, pit1, pit2, pit3);
	//printCoordinates(Hero.x);

	//bool gameOver = false;

	pitP[Hero.x] = 0; // Obviously wherever we start has a 0% chance of having pit or monster
	monsterP[Hero.x] = 0;


	int turns = 0; // Keep track of turns 
	while(1){
		int surroundings = 0;
		printCoordinates(Hero.x);
		surroundings = checkSurroundings(Hero.x);

		adjustProb(surroundings, Hero.x);

		printProb();

		printOptions(Hero.x);

		printf("Would you like to keep moving (m) or fire an arrow (f)?\n");
		string choice;
		getline(cin, choice);
		while(choice != "m" && choice != "f" && choice != "q"){
			printf("Please type either 'm' or 'f'\n");
			getline(cin, choice);
		}
		if(choice == "q"){ //Type q to quit
			exit(0);
		}else if(choice == "f"){ // Handling firing arrow
			shootArrow(&Hero);
		}else
		{
			move(&Hero); //Handling moving
		}

		turns++;
	}
}
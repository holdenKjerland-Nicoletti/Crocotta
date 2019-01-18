#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>


using namespace std;

static int Monster;
static int pit1;
static int pit2;
static int pit3; // Declare Monster and 3 pits
static int occupied[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
		}else if(occupied[(Hero->x) + 5] == 2)
		{
			printf("You have fallen into a pit!!\nGAME OVER!!\n");
			exit(0);
		}
		else{
			occupied[Hero->x] = 0;
			Hero->x = Hero->x + 5;
			occupied[Hero->x] = 1;
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
		}else if(occupied[(Hero->x) - 5] == 2)
		{
			printf("You have fallen into a pit!!\nGAME OVER!!\n");
			exit(0);
		}
		else{
			occupied[Hero->x] = 0;
			Hero->x = Hero->x - 5;
			occupied[Hero->x] = 1;
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
		}else if(occupied[(Hero->x) - 1] == 2)
		{
			printf("You have fallen into a pit!!\nGAME OVER!!\n");
			exit(0);
		}
		else{
			occupied[Hero->x] = 0;
			Hero->x = Hero->x - 1;
			occupied[Hero->x] = 1;
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
		}else if(occupied[(Hero->x) + 1] == 2)
		{
			printf("You have fallen into a pit!!\nGAME OVER!!\n");
			exit(0);
		}
		else{
			occupied[Hero->x] = 0;
			Hero->x = Hero->x + 1;
			occupied[Hero->x] = 1;
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
		//cout<<"Monster coordinates : "<< Monster << endl;
		return;
	}
}

int printSurroundings(int x){
	if(x == 1){
		printf("I hear panting\n");
		return 1;
	}else if(x == 2){
		printf("I feel a breeze\n");
		return 1;
	}
	return 0;
}

void checkSurroundings(int x){
	int clear = 0;
	if(x> 4){ // if less than 4 we don't need to check below
		clear = clear + printSurroundings(occupied[x - 5]);
	}
	if(x < 20){ //if not on top edge, check top
		clear = clear +printSurroundings(occupied[x + 5]);
	}
	if((x % 5) != 0){ //if it's not on the left edge check left
		clear = clear + printSurroundings(occupied[x - 1]);
	}
	if((x % 5) != 4){ // If it's not on the right edge, check right
		clear = clear + printSurroundings(occupied[x + 1]);
	}
	//printf("Clear: %d\n", clear);
	if(clear == 0){
		printf("Silence\n");
	}
}

void printCoordinates(int i){
	int y = i / 5;

	int x = (i % 5);

	cout<<"You are now located at the coordinates: ("<< x<<", "<<y<<")\n";
	return;
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

			occupied[pit2] = 2;
		}
	}
	leave = false;
	while(!leave){
		pit3 = randomNumbers(0, 24);

		//Monster.y = rand() % 5;

		if(!occupied[pit3]){
			leave = true;
			occupied[pit3] = 2;
		}
	}
	//printf("Monster: %d\nPit1: %d\nPit2: %d\nPit3: %d\n", Monster, pit1, pit2, pit3);
	//printCoordinates(Hero.x);

	//bool gameOver = false;

	while(1){
		printCoordinates(Hero.x);

		checkSurroundings(Hero.x);

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

		//gameOver = true;
	}
}

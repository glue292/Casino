#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <utility>
#include <unistd.h>
#include <fstream>
using namespace std;

void saveGame(int money) {
    ofstream saveFile("casino_save.txt");
    if (saveFile.is_open()) {
        saveFile << money << endl;
        saveFile.close();
        cout << "Game saved successfully!" << endl;
    } else {
        cout << "Unable to save game." << endl;
    }
}

int loadGame() {
    ifstream saveFile("casino_save.txt");
    int savedMoney = 300;  // Default starting money
    if (saveFile.is_open()) {
        saveFile >> savedMoney;
        saveFile.close();
        cout << "Game loaded successfully!" << endl;
    } else {
        cout << "No save file found. Starting new game." << endl;
    }
    return savedMoney;
}








string Drawcard( int& score, string card){
	int cardval = rand() % 13;
	cardval = cardval + 1; 
	card = "nil";
	if(cardval < 11 && cardval > 1){
		card = to_string(cardval);
	} 
	else if (cardval == 11){
		card = "Jack";
	}
	else if (cardval == 12){
		card = "Queen";
	}
	else if (cardval == 1){
		card = "Ace";
	}
	else if (cardval == 13){
		card = "King";
	}
	else{
		cout << "fatal error, what are you doing";
		exit(0); 
	}

	string suits[4] = {"spades","hearts","diamonds","clubs",};
	string suit = suits[rand() % 4];
	//card = card + " of " + suit;
	if (cardval > 10){
		cardval = 10;
	}
	else if (cardval == 1){
		if (score + 11 > 21){
			cardval = 1;
		}
		else{
			cardval = 11;
		}
	}
	score = score + cardval;
	return card;
}



int Money = loadGame();

void Blackjack() {
	int aces = 0;
	bool play = true;
	while (play == true) {
		bool win = true;
		int bet = 0;
		bool betting = true;
		int start$ = Money;
		//!!!!!IMPORTANT!!!!!! fix bug with invalid input before releasing
		while (betting == true) {
			cout << "how much would you like to bet? you have $" << Money <<".";
			cin >> bet;

			if (bet > Money + 1){
				betting = true;
				cout << "Not enough money! Broke.\n ";}
			else{ Money = Money - bet;
				betting = false;}}
		betting = true;


		int score = 0; 
		int dealerscore = 0;
		string card1 = "0";
		string card2 = "0";
		card1 = Drawcard(score, card1);
		card2 = Drawcard(score, card2);
		cout << " You got a " << card1 << " and a " << card2 << "\n";
		string dealercard1 = "0";
		string dealercard2 = "0";
		dealercard1 = Drawcard(dealerscore, dealercard1);
		dealercard2 = Drawcard(dealerscore, dealercard2);
		cout << "Dealer got " << dealercard1 << " and a " << "[hidden card]\n";
		bool active = true;
		string card = "nil";
		while (active == true) {
			cout << "Hit(x) or stand(o)\n";
			string move = "0";
			cin >> move;
			if (move == "x" || move == "X"){
				card = Drawcard(score, card);
				cout << "you got a " << card << "\n";
				if (score > 21){
					cout << "bust! you lost\n";
					win = false;
					active = false;
				}

			}
			else if (move == "o" || move == "O") {
				active = false;

			}
			else{
				cout << "thats not a bet\n";
			} 

		}
		if (score < 21) {
			active = true;
		}

		if (win == true){
			cout << "dealer's hidden card is " << dealercard2 << "\n";
			while (active == true) {
				if (score > dealerscore) {
					usleep(2000000);
					card = Drawcard(dealerscore,card);
					cout << "Dealer got a " << card << "\n";
				}
				else {active = false;}
			}
			win = false;
			if (dealerscore > 21) {
				cout << "dealer bust, you win!";
				win = true;
				dealerscore = 0;
			}
			else {
				if (score > dealerscore ) {
					cout << "you win!\n";
					win = true;
				}
				else { 
					cout << "you lose\n";
					win = false;
				}
			}
			if (win == true){

				Money = Money + bet * 2;

			}

		}
		int won = Money - start$;
		cout << "you won " << won << " would you like to play again?(yes/no)";
		string choice = "o";
		cin >> choice; 
		if (choice == "n" || choice == "N" || choice == "no" || choice == "No"){
			play = false;
		}
	}

}



bool checkvalid(string var){
	if (var == "r"){
		return true;
	}
	else if (var == "b"){
		return true;
	}
	else if (var == "e"){
		return true;
	}
	else if (var == "o"){
		return true;
	}
	else if (var == "t"){
		return true;
	}
	else if (var == "y"){
		return true;
	}
	else if (var == "h"){
		return true;
	}
	else if (var == "j"){
		return true;
	}
	else if (var == "k"){
		return true;
	}
	else if (var == "q"){
		return true;
	}
	else if (var == "a"){
		return true;
	}
	else if (var == "z"){
		return true;
	}
	else if (stoi(var) < 37){
		return true;
	}
	else {
		return false;
	}
}


void Roulette() {
	bool playing = true;
	while (playing == true) {
		char Colors[37] = {'g',
			'r','b','r',
			'b','r','b',
			'r','b','r',
			'b','b','r',
			'b','r','b',
			'r','b','r',
			'b','b','r',
			'b','r','b',
			'r','b','r',
			'r','b','r',
			'b','r','b',
			'r','b','r'};



		//bet amount definitions
		int betam = 0;
		bool betting = true;


		int start$ = Money;
		//!!!!!IMPORTANT!!!!!! fix bug with invalid input before releasing
		while (betting == true) {
			cout << "how much would you like to bet? you have $" << Money <<".";
			cin >> betam;

			if (betam > Money + 1){
				betting = true;
				cout << "Not enough money! Broke.\n ";}
			else{ Money = Money - betam;
				betting = false;}} 
		betting = true;


		//bet type definition
		cout << "what would you like to bet on\n"
			"[ 1][ 4][ 7][10][13][16][18][22][25][28][31][34]	[3rd row]\n"
			"[ 0][ 2][ 5][ 8][11][14][17][20][23][26][29][32][35]	[2nd row]\n"
			"[ 3][ 6][ 9][12][15][18][21][24][27][30][33][36]	[1st row]\n"
			"[   1st 12  ][    2nd 12    ][    3rd 12    ]\n"
			"[1-18][Even][Red][Black][Odd][18-36]\n"


			"Red-(r)\n"
			"Black-(b)\n"
			"Even-(e)\n"
			"Odd(o)\n"
			"1st 18-(t)\n"
			"2nd 18(y)\n"
			"1-12(h)\n"
			"13-24(j)\n"
			"25-36(k)\n"
			"3rd row(q)\n"
			"2nd row(a)\n"
			"1st row(z)\n"
			"Any number\n";
		string bet = "x";

		while (betting == true){
			cin >> bet;
			if (checkvalid(bet) == true){
				betting = false;
			} else {
				betting = true;
				cout<< "That's not a bet";
			}
		}

		//determine numbers
		int roll = 0;

		roll = rand() % 37;

		string Color = "Green";
		if (Colors[roll] == 'r') {
			Color = "Red ";
		} else if (Colors[roll] == 'b') {
			Color = "Black ";
		}
		cout << "you rolled "<<  Color << " " << roll << "\n";


		int won = 0;
		if (bet == "r" && Color == "Red "){
			Money = Money + betam * 2;
			won = won + betam * 2;   
		}

		if (bet == "b" && Color == "Black "){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == "e" && roll % 2 == 0 ){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == "o" && roll % 2 == 1){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == "t" && roll <= 18){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == "y" && roll > 18){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == "h" && roll <= 12){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == "j" && roll > 12 && roll <= 24){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == "k" && roll > 24){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == "q" && roll % 3 == 0){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == "a" && roll % 3 == 2){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == "z" && roll % 3 == 1){
			Money = Money + betam * 3; 
			won = won + betam * 3; 
		}

		try{
			if  (stoi(bet) == roll  ){
				Money = Money + betam * 36;
				won = won + betam * 36; 
			}
		}
		catch(...){}

		won = Money -  start$;	
		cout << "you won " << won << " would you like to play again?(yes/no)\n";
		string response = "nil";
		cin >> response;

		if (response == "no" || response == "No"|| response == "n") {
			playing = false;
		}else {
			playing = true;
		} 


	}
}



int main() {
	srand(time(0)+1000);
	bool game = true;
	string choi = "0";
	while (game == true) {
		cout << "what would you like to do?, balance is $"<< Money << ".\n"
			"1. Play Blackjack\n"
			"2. Play Roulette\n"
			"3. Reset balance\n"
			"4. Quit\n";
		cin >> choi;
		if(choi == "1"){
			Blackjack();
		}
		else if (choi == "2"){
			Roulette();
		}
		else if (choi == "3"){
			Money = 100;
		}
		else if (choi == "4") {
			saveGame(Money);
			game = false;
		}
		else {
			cout << "That's not an option\n";
		}

	}

}



#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <utility>
#include <unistd.h>
#include <fstream>
#include <ncurses.h>
using namespace std;

void saveGame(int money) {
    ofstream saveFile("casino_save.txt");
    if (saveFile.is_open()) {
        saveFile << money << endl;
        saveFile.close();
       // cout << "Game saved successfully!" << endl;
    } else {
        //cout << "Unable to save game." << endl;
    }
}

int loadGame() {
    ifstream saveFile("casino_save.txt");
    int savedMoney = 300;  // Default starting money
    if (saveFile.is_open()) {
        saveFile >> savedMoney;
        saveFile.close();
       //cout << "Game loaded successfully!" << endl;
    } else {
       // cout << "No save file found. Starting new game." << endl;
    }
    return savedMoney;
}

void sbox(WINDOW* win, int y,int x, int height,int width){

	wattron(win,A_ALTCHARSET);
	string horz = "";
	for (int i = 0; i < width; i++){
		horz = horz + "q";
	}
	wattron(win,A_ALTCHARSET);
	mvwprintw(win,y,x + 1,horz.c_str());
	mvwprintw(win,y + height,x + 1,horz.c_str());
	for (int i = 0; i < (height - 1); i++){
	mvwprintw(win,y + i + 1,x,"x");
	}
	for (int i = 0; i < (height - 1); i++){
	mvwprintw(win,y + i + 1,x + width + 1,"x");
	}
	mvwprintw(win,y,x,"l");
	mvwprintw(win,y + height,x,"m");
	mvwprintw(win,y,x + width + 1,"k");
	mvwprintw(win,y + height,x + width + 1,"j");
	wattroff(win,A_ALTCHARSET);

}




int aces = 0;
int counter = 0;
int dcounter = 0;
string hsuit = " ";
string Drawcard( int& score, string card, int type){
	
	int xs[11] = {110,120,100,130,90,140,80,150,70,160,60};
	
	int cardval = rand() % 13;
	cardval = cardval + 1; 
	card = "nil";
	if(cardval < 11 && cardval > 1){
		card = to_string(cardval);
	} 
	else if (cardval == 11){
		card = "J";
	}
	else if (cardval == 12){
		card = "Q";
	}
	else if (cardval == 1){
		card = "A";
		if (type == 1){
		aces = aces + 1;
		}
	}
	else if (cardval == 13){
		card = "K";
	}
	else{
		cout << "fatal error, what are you doing";
		exit(0); 
	}

	string suits[4] = {"♤", "❤", "♢", "♧"};
	string suit = suits[rand() % 4];
	if (type == 1){
		hsuit = suit;
	}
	if (cardval > 10){
		cardval = 10;
	}
	else if (cardval == 1){

			cardval = 11;
		
	}
	score = score + cardval;
int y;
int x;
if(type == 1){
	y = 45;
	x = xs[counter];
	counter = counter + 1;
}
else  {
	y = 20;
	x = xs[dcounter];
	dcounter = dcounter + 1;
	
}

if (type != 3){
	WINDOW* cardwin = newwin(7,10,y,x);
	box (cardwin,0,0);
	mvwprintw(cardwin,1,1,"%s",suit.c_str());
	mvwprintw(cardwin,3,4,"%s",card.c_str());
	mvwprintw(cardwin,5,8,"%s",suit.c_str());
	wrefresh(cardwin);
}
	return card;
	
}



int Money = loadGame();
void Blackjack() {
	bool play = true;
	WINDOW *blackjack = newwin(61,163,1,40);
	while (play == true) {
		box(blackjack,0,0);
		bool win = true;
		int betam = 0;
		bool betting = true;
		int start$ = Money;
		//!!!!!IMPORTANT!!!!!! fix bug with invalid input before releasing
			mvwprintw(blackjack, 1,1,"%s", ("how much would you like to bet? you have $" + to_string(Money)).c_str());
			mvwprintw(blackjack, 2,1,"use arrow keys to Select amount, enter to confirm");
			mvwprintw(blackjack, 3,1,"Bet: $0");
			wrefresh(blackjack);
		while (betting == true) {
			
			
			int ch = getch();
			if (ch == '='){
				betam = betam + 1000;
			}
			else if (ch == '-'){
				betam = betam - 1000;
			}
			else if (ch == KEY_UP){
				betam = betam + 100;
			}
			else if (ch == KEY_DOWN){
				betam = betam - 100;
			}
			else if (ch == KEY_RIGHT){
				betam = betam + 10;
			}
			else if (ch == KEY_LEFT){
				betam = betam - 10;
			}
			else if (ch == KEY_ENTER || ch =='\n'){
				betting = false;
			}
			if (betam > Money){
				betam = Money;
			} 
			else if (betam < 0) {
				betam = 0;
			}
			
			string displayed = to_string(betam);
			mvwprintw(blackjack, 3,1,"Bet: $0");
			mvwprintw(blackjack, 3,7,"%s",(displayed + "    ").c_str());
			wrefresh(blackjack);
		}
		betting = true;
		Money = Money - betam;
		mvprintw(61,2,"%s",to_string(Money).c_str());
		wclear(blackjack);
		box(blackjack,0,0);
		mvwprintw(blackjack,1,150,"%s",("Bet: $" + to_string(betam) + " ").c_str());
		wrefresh(blackjack);
		int score = 0; 
		int dealerscore = 0;
		string card1 = "0";
		string card2 = "0";
		card1 = Drawcard(score, card1,1);
		card2 = Drawcard(score, card2,1);
		string dealercard1 = "0";
		string dealercard2 = "0";
		dealercard1 = Drawcard(dealerscore, dealercard1,2);
		WINDOW* hwin = newwin(7,10,20,120);
		box (hwin,0,0);
		wrefresh(hwin);

		int ch;
		bool active = true;
		string card = "nil";
		while (active == true) {
			mvwprintw(blackjack,1,71,"Hit(a) or stand(b)");
			mvwprintw(blackjack,17,77,"Dealer");
			mvwprintw(blackjack,52,78,"You");
			wrefresh(blackjack);
			ch = getch();
			if (ch == 'a' || ch == 'A'){
				card = Drawcard(score, card,1);
				if (score > 21 && aces < 1){
					mvwprintw(blackjack,29,74,"bust! you lost");
					win = false;
					active = false;
				}
				else if (score > 21 && aces > 0){
					score = score - 10;
					aces = aces - 1;

				}

			}
			else if (ch == 'b' || ch == 'B') {
				active = false;

			}
			else{
				
			} 

		}
		if (score < 21) {
			active = true;
		}

		if (win == true){
			while (active == true) {
				if (score > dealerscore) {
					usleep(1000000);
					card = Drawcard(dealerscore,card,2);
				}
				else {active = false;}
			}
			win = false;
			if (dealerscore > 21) {
				mvwprintw(blackjack,29,68,"dealer bust, you win!");
				win = true;
				dealerscore = 0;
			}
			else {
				if (score > dealerscore ) {
					mvwprintw(blackjack,29,75,"you win!");
					win = true;
				}
				else { 
					mvwprintw(blackjack,29,76,"you lose");
					win = false;
				}
			}
			if (win == true){

				Money = Money + betam * 2;

			}

		}
		mvwprintw(hwin,1,1,"%s",hsuit.c_str());
	mvwprintw(hwin,3,4,"%s",dealercard2.c_str());
	mvwprintw(hwin,5,8,"%s",hsuit.c_str());
		int won = Money - start$;
		bool picking;
		picking = true;
		int choi = 0;
		string choices[2] = {"yes","no"};
		if (win == true){
		mvwprintw(blackjack,66,120,"%s", ("You won $" + to_string(won)).c_str());
		}
		mvprintw(61,2,"%s",to_string(Money).c_str());
		if (Money != 0){
		mvwprintw(blackjack,33,65,"would you like to play again?");
		while (picking == true){
		mvwprintw(blackjack,35,75,"yes");
		mvwprintw(blackjack,35,79,"no");
		wattron(blackjack,A_REVERSE);
		mvwprintw(blackjack,35,(75 + choi * 4),"%s",(choices[choi]).c_str());
		wattroff(blackjack,A_REVERSE);
		wrefresh(blackjack);
		int ch = getch();

		if (ch == KEY_LEFT){
			choi = choi - 1;
		}
		if (ch == KEY_RIGHT){
			choi = choi + 1;
		}
		if (ch == KEY_ENTER || ch == '\n'){
			picking = false;
		}
		if (choi < 0){
			choi = 0;
		}
		if (choi > 1){
			choi = 1;
		}
		}
		if (choi == 1){
		play = false;
		}
	}
		else {
			play = false;
		}	
	wclear(blackjack);
	saveGame(Money);
	counter = 0;
	dcounter = 0; 
	aces = 0;
	}
	delwin(blackjack);
	}








void Roulette() {
	bool playing = true;
	WINDOW *roulette = newwin(61,163,1,40);
	while (playing == true) {
		box(roulette,0,0);
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
			mvwprintw(roulette, 1,1,"how much would you like to bet? you have $");
			mvwprintw(roulette, 2,1,"use arrow keys to Select amount, enter to confirm");
			mvwprintw(roulette, 3,1,"Bet: $0");
			wrefresh(roulette);
		while (betting == true) {
			
			
			int ch = getch();
			if (ch == '='){
				betam = betam + 1000;
			}
			else if (ch == '-'){
				betam = betam - 1000;
			}
			else if (ch == KEY_UP){
				betam = betam + 100;
			}
			else if (ch == KEY_DOWN){
				betam = betam - 100;
			}
			else if (ch == KEY_RIGHT){
				betam = betam + 10;
			}
			else if (ch == KEY_LEFT){
				betam = betam - 10;
			}
			else if (ch == KEY_ENTER || ch =='\n'){
				betting = false;
			}
			if (betam > Money){
				betam = Money;
			} 
			else if (betam < 0) {
				betam = 0;
			}
			
			string displayed = to_string(betam);
			mvwprintw(roulette, 3,1,"Bet: $0");
			mvwprintw(roulette, 3,7,"%s",(displayed + "    ").c_str());
			wrefresh(roulette);
		}
		
		Money = Money - betam;
		mvprintw(61,2,"%s",to_string(Money).c_str());
		refresh();
		wclear(roulette);
		box(roulette,0,0);
		//bet type definition
		mvwprintw(roulette,1,1,"what would you like to bet on");
		int bet = 0;
		int menur = 1;
		int number = 0;
		betting = true;
		while (betting == true){
			string optionsr[14] = {"nil","Red","Black","Even","Odd","1st 18","2nd 18","1-12","13-24","25-36","1st row","2nd row","3rd row", "number:"};
		wclear(roulette);
		box (roulette,0,0);
		mvwprintw(roulette,40,30,"[ 1][ 4][ 7][10][13][16][18][22][25][28][31][34]	[3rd row]");
		mvwprintw(roulette,41,26,"[ 0][ 2][ 5][ 8][11][14][17][20][23][26][29][32][35]	[2nd row]");
		mvwprintw(roulette,42,30,"[ 3][ 6][ 9][12][15][18][21][24][27][30][33][36]	[1st row]");
		mvwprintw(roulette,43,30,"[   1st 12  ][    2nd 12    ][    3rd 12    ]");
		mvwprintw(roulette,44,30,"[ 1-18 ][ Even ][ Red ][ Black ][ Odd ][ 18-36 ]");	
		mvwprintw(roulette,1,150,"%s",("Bet: $" + to_string(betam) + " ").c_str());
		mvwprintw(roulette,1,1,"Red");
		mvwprintw(roulette,2,1,"Black");
		mvwprintw(roulette,3,1,"Even");
		mvwprintw(roulette,4,1,"Odd");
		mvwprintw(roulette,5,1,"1st 18");
		mvwprintw(roulette,6,1,"2nd 18");
		mvwprintw(roulette,7,1,"1-12");
		mvwprintw(roulette,8,1,"13-24");
		mvwprintw(roulette,9,1,"25-36");
		mvwprintw(roulette,10,1,"1st row");
		mvwprintw(roulette,11,1,"2nd row");
		mvwprintw(roulette,12,1,"3rd row");
		mvwprintw(roulette,13,1,"number:");
		mvwprintw(roulette,13,8,"%s",to_string(number).c_str());
		wattron(roulette,A_REVERSE);
		mvwprintw(roulette,menur,1,optionsr[menur].c_str());
		if (menur == 13){
			mvwprintw(roulette,13,8,"%s",to_string(number).c_str());
		}
		wattroff(roulette,A_REVERSE);
		wrefresh(roulette);
		int ch = getch();
		
		
		if (ch == KEY_UP) {
		menur = menur - 1;
		}
		else if (ch == KEY_DOWN){
		menur = menur + 1;
		}
		else if (ch == KEY_ENTER || ch == '\n') {
			bet = menur;
			betting = false;
		
			
		}
		else if (ch == KEY_RIGHT && menur == 13){
			number = number + 1;
		}
		else if (ch == KEY_LEFT && menur == 13){
			number = number - 1;
		}

		
		if (menur > 13){
			menur = 13;
		}
		else if (menur < 1) {
			menur = 1;
		}
		
		if (number > 36){
			number = 36;
		}
		else if (number < 0){
			number = 0;
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
		sleep(2);
		mvwprintw(roulette,5,120,"%s",("Rolled " + Color + " " + to_string(roll)).c_str());
		wrefresh (roulette);
		sleep(2);

		int won = 0;
		if (bet == 1 && Color == "Red "){
			Money = Money + betam * 2;
			won = won + betam * 2;   
		}

		if (bet == 2 && Color == "Black "){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == 3 && roll % 2 == 0 ){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == 4 && roll % 2 == 1){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == 5 && roll <= 18){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == 6 && roll > 18){
			Money = Money + betam * 2;
			won = won + betam * 2;  
		}

		if (bet == 7 && roll <= 12){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == 8 && roll > 12 && roll <= 24){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == 9 && roll > 24){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == 10 && roll % 3 == 0){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == 11 && roll % 3 == 2){
			Money = Money + betam * 3;
			won = won + betam * 3;  
		}

		if (bet == 12 && roll % 3 == 1){
			Money = Money + betam * 3; 
			won = won + betam * 3; 
		}
		if (bet == 13 && roll == number){
			Money = Money + betam * 36;
			won = won + betam * 36;
		}		
		won = Money -  start$;	
		bool picking;
		picking = true;
		int choi = 0;
		string choices[2] = {"yes","no"};
		mvwprintw(roulette,10,120,"%s", ("You won $" + to_string(won)).c_str());
		mvprintw(61,2,"%s",to_string(Money).c_str());
		if (Money != 0){
		mvwprintw(roulette,15,120,"would you like to play again?");
		while (picking == true){
		mvwprintw(roulette,17,125,"yes");
		mvwprintw(roulette,17,129,"no");
		wattron(roulette,A_REVERSE);
		mvwprintw(roulette,17,(125 + choi * 4),"%s",(choices[choi]).c_str());
		wattroff(roulette,A_REVERSE);
		wrefresh(roulette);
		int ch = getch();

		if (ch == KEY_LEFT){
			choi = choi - 1;
		}
		if (ch == KEY_RIGHT){
			choi = choi + 1;
		}
		if (ch == KEY_ENTER || ch == '\n'){
			picking = false;
		}
		if (choi < 0){
			choi = 0;
		}
		if (choi > 1){
			choi = 1;
		}
		}
		if (choi == 1){
		playing = false;
		}
		}
		else {
			playing = false;
		}	
	wclear(roulette);
	saveGame(Money);
	}
	delwin(roulette);
	}


void ChickenRoad() {
WINDOW* chick = newwin(61,163,1,40);
box(chick,0,0);
bool game = true; 
while (game == true){
box(chick,0,0);
int betting = true;
int betam = 0;
mvwprintw(chick, 1,1,"how much would you like to bet? you have $");
			mvwprintw(chick, 2,1,"use arrow keys to Select amount, enter to confirm");
			mvwprintw(chick, 3,1,"Bet: $0");
			wrefresh(chick);
		while (betting == true) {
			
			
			int ch = getch();
			if (ch == '='){
				betam = betam + 1000;
			}
			else if (ch == '-'){
				betam = betam - 1000;
			}
			else if (ch == KEY_UP){
				betam = betam + 100;
			}
			else if (ch == KEY_DOWN){
				betam = betam - 100;
			}
			else if (ch == KEY_RIGHT){
				betam = betam + 10;
			}
			else if (ch == KEY_LEFT){
				betam = betam - 10;
			}
			else if (ch == KEY_ENTER || ch =='\n'){
				betting = false;
			}
			if (betam > Money){
				betam = Money;
			} 
			else if (betam < 0) {
				betam = 0;
			}
			string displayed = to_string(betam);
			mvwprintw(chick, 3,1,"Bet: $0");
			mvwprintw(chick, 3,7,"%s",(displayed + "    ").c_str());
			wrefresh(chick);
		}
		
		Money = Money - betam;
		mvprintw(61,2,"%s",(to_string(Money) + "    ").c_str());
		refresh();
		wclear(chick);
		box(chick,0,0);

//int added = ceil(betamount * 0.01);
int payout = betam;
bool playing = true;
int death = rand() % 24;
death = death + 1;
int pos = 0;
int prevpayout = 1;
int pprevpayout = 1;
string message;
bool cashout = false;
const double added[25] = {0.04, 0.05, 0.05, 0.06, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,
        0.14, 0.15, 0.18, 0.22, 0.27, 0.33, 0.43, 0.57, 0.80, 1.20,
        2.00, 4.00, 12.00};

while (playing == true) {
	wclear(chick);
	box(chick,0,0);
		mvwprintw(chick,1,62,"Continue(a) or Cash out(b)");
	


	int nextpayout = 1;
	int nnextpayout = 1;


	//if (pos == 0) {
nextpayout = payout + (betam * added[pos]);
nnextpayout = nextpayout + (betam * added[(pos + 1)]);
//}
//cout << "current payout: " << payout << "\n\n next payout: " << nextpayout << "\n\n pos: " << pos << " \n\n continue(a) cash out(b)";
int x = 75;
int px = x;
int pl = (to_string(payout)).length();
int plx = px - floor(pl / 2);
int ppx = x;
int ppl = (to_string(prevpayout)).length();
int pplx = ppx - floor(ppl / 2);
int pppx = x;
int pppl = (to_string(pprevpayout)).length();
int ppplx = pppx - floor(pppl / 2);
int nx = x;
int nl = (to_string(nextpayout)).length();
int nlx = nx - floor(pl / 2);
int nnx = x;
int nnl = (to_string(nnextpayout)).length();
int nnlx = nnx - floor(pl / 2);
if (pprevpayout != 1){
	sbox(chick,19,ppplx - 1,2,pppl);
mvwprintw(chick,20,ppplx,"%s",to_string(pprevpayout).c_str());
}
if (prevpayout != 1){
	sbox(chick,24,pplx - 1,2,ppl);
mvwprintw(chick,25,pplx,"%s",to_string(prevpayout).c_str());
}
mvwprintw(chick,29,plx,"current");
mvwprintw(chick,50,plx - 4,"%s", ("Position " + to_string(pos)).c_str());
sbox(chick,30,plx - 1,2,pl);
wattron(chick, A_REVERSE);
mvwprintw(chick,31,plx,"%s",to_string(payout).c_str());
wattroff(chick,A_REVERSE);
if (pos + 1 < 24){
	sbox(chick,35,nlx - 1,2,nl);
mvwprintw(chick,36,nnlx,"%s",to_string(nextpayout).c_str());
}
if (pos + 2 < 24){
sbox(chick,40,nnlx - 1,2,nnl);
mvwprintw(chick,41,nnlx,"%s",to_string(nnextpayout).c_str());
}
wrefresh(chick);
int ch = getch();
if (ch == 'b') {
	playing = false;
	message = "you won $" + to_string(payout);
	cashout = true; 
	Money = Money + payout;
}
pprevpayout = prevpayout;
prevpayout = payout;
payout = nextpayout;
pos = pos + 1;
if (pos == death && pos != 24) {
	message = "you died and lost it all.";
	playing = false;
}
else if (pos == 24) {
message = "you made it across! you win $" + to_string(payout);
Money = Money + payout;
playing = false;

}
}
bool picking;
		picking = true;
		int choi = 0;
		string choices[2] = {"yes","no"};
		mvwprintw(chick,10,120,"%s",message.c_str());
		if (cashout == true)
		mvwprintw(chick,12,120,"%s",("you would've died at " + to_string(death) + ".").c_str());
		mvprintw(61,2,"%s",to_string(Money).c_str());
		if (Money != 0){
		mvwprintw(chick,15,120,"would you like to play again?");
		while (picking == true){
		mvwprintw(chick,17,125,"yes");
		mvwprintw(chick,17,129,"no");
		wattron(chick,A_REVERSE);
		mvwprintw(chick,17,(125 + choi * 4),"%s",(choices[choi]).c_str());
		wattroff(chick,A_REVERSE);
		wrefresh(chick);
		int ch = getch();

		if (ch == KEY_LEFT){
			choi = choi - 1;
		}
		if (ch == KEY_RIGHT){
			choi = choi + 1;
		}
		if (ch == KEY_ENTER || ch == '\n'){
			picking = false;
		}
		if (choi < 0){
			choi = 0;
		}
		if (choi > 1){
			choi = 1;
		}
		}
		if (choi == 1){
		game = false;
		}
		}
		else {
			game = false;
		}	
	wclear(chick);
	saveGame(Money);


}
delwin (chick);
}



int main() {
	srand(time(0)+1000);
	    setlocale(LC_ALL, "");
	initscr();
keypad(stdscr, TRUE);
noecho();
curs_set(0);
	box(stdscr, 0, 0);

  refresh();

	bool game = true;
	int choi = 1;




	int menu = 1;
	while (game == true) {
	bool picking = true;
	
	string options[6] = {"nil","1.)Play Blackjack","2.)Play Roulette","3.)Play Chicken road game","4.)Reset balance","5.)Quit"};
	while (picking == true) {
		clear();
		box (stdscr,0,0);
		mvprintw(1,1,"1.)Play Blackjack");
		mvprintw(2,1,"2.)Play Roulette");
		mvprintw(3,1,"3.)Play Chicken road game");
		mvprintw(4,1,"4.)Reset balance");
		mvprintw(5,1,"5.)Quit");
		attron(A_ALTCHARSET);
		//mvprintw(20,3,"a b c d e f g h i j k l m n o p q r s t u v w x y z");
		attroff(A_ALTCHARSET);
		//mvprintw(21,3,"a b c d e f g h i j k l m n o p q r s t u v w x y z");
			attron(A_REVERSE);
		mvprintw(menu,1,options[menu].c_str());
		attroff(A_REVERSE);
		mvprintw(61,2,"%s",to_string(Money).c_str());
		refresh();
		int ch = getch();
		if (ch == KEY_UP) {
		menu = menu - 1;
		}
		else if (ch == KEY_DOWN){
		menu = menu + 1;
		}
		else if (ch == KEY_ENTER || ch == '\n') {
			choi = menu;
			picking = false;
		}
		if (menu > 5){
			menu = 5;
		}
		else if (menu < 1) {
			menu = 1;
		}
	
	
	}

	


		if(choi == 1){
			Blackjack();
			saveGame(Money);
		}
		else if (choi == 2){
			Roulette();
			saveGame(Money);
		}
		else if (choi == 3){
			ChickenRoad();
			saveGame(Money);
		}
		else if (choi == 4){
			Money = 100;
			saveGame(Money);
		}
		else if (choi == 5) {
			saveGame(Money);
			
			game = false;
		}
		else {
			//cout << "That's not an option\n";
		}

	}



endwin();
return 0;
}

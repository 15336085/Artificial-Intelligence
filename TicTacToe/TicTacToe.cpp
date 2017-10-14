#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

int turn = 0;
//int turn = 5;
int fir = 0;
//int fir = 1;

struct State{
	char board[9];
	int score;
	int next;
};

struct Step{
	int score;
	int next;
};

void initialize(State &ini);					//将棋盘初始化
int isterminal(State &cur, int fir, int turn);  //判断是否达到终止状态
void aiturn(State &cur);						//AI四咸操作步
void myturn(State &cur);						//玩家操作步
Step minimax(State &cur, int turn);				//探索下一步


int main(){
	State ini;
	initialize(ini);
	cout << "************** Tic Tac Toe Game *************" << endl;
	cout << "*                                           *" << endl;
	cout << "*       Who will take the first step?       *" << endl;
	cout << "*       [1] You;                            *" << endl;
	cout << "*       [2] AI Foursalt;                    *" << endl;
	cout << "*                                           *" << endl;
	cout << "*********************************************" << endl;
	cout << "Your choice:";
	cin >> fir;
	if(fir == 1){turn = 0;}
	if(fir == 2){turn = 1;}
	cout << "The game is on!" << endl;
	for(int i = 0; i < 9; i++){
		cout << ini.board[i] << " ";
		if(i==2 || i==5 || i==8) cout << endl;
	}
	cout << endl;
	int end;
	while(1){
		if(fir == 2 && turn == 1) {
			srand((unsigned)time(NULL));
			int ind = rand()%9;
			ini.board[ind] = 'x';
			cout << "It's Foursalt's turn!" << endl;
			for(int i = 0; i < 9; i++){
				cout << ini.board[i] << " ";
				if(i==2 || i==5 || i==8) cout << endl;
			}
			cout << endl;
			turn++;
			continue;
		}
		if(turn%2==0) {
			myturn(ini); 
			end = isterminal(ini, fir, turn);
			if(end != -2){
				if(end == 1){cout << "AI Foursalt win!" << endl; break;}
				if(end == -1){cout << "You win!" <<endl; break;}
				if(end == 0) {cout << "You tied!" << endl; break;}
			}
			turn++;
			continue;
		}
		else if(turn%2==1) {
			aiturn(ini); 
			end = isterminal(ini, fir, turn);
			if(end != -2){
				if(end == 1){cout << "AI Foursalt win!" << endl; break;}
				if(end == -1){cout << "You win!" <<endl; break;}
				if(end == 0) {cout << "You tied!" << endl; break;}
			}
			turn++;
			continue;
		}
	}
	system("pause");
	return 0;
}


void initialize(State &ini){
	for(int i=0; i<9; i++){
		ini.board[i]= '_';
	}
	ini.score=0;
	ini.next=0;
}

int isterminal(State &cur, int fir, int turn){
	int a, b, i, j, k, l, m, n;
	for(i = 0; i < 2; i++){
		if(cur.board[i] != cur.board[i+1]) break;
	}
	if(i == 2 && cur.board[0] == 'x') {cur.score += 10; return 1;}
	if(i == 2 && cur.board[0] == 'o') {cur.score -= 10; return -1;}
	for(j = 3; j < 5; j++){
		if(cur.board[j] != cur.board[j+1]) break;
	}
	if(j == 5 && cur.board[3] == 'x') {cur.score += 10; return 1;}
	if(j == 5 && cur.board[3] == 'o') {cur.score -= 10; return -1;}
	for(k = 6; k < 8; k++){
		if(cur.board[k] != cur.board[k+1]) break;
	}
	if(k == 8 && cur.board[6] == 'x') {cur.score += 10; return 1;}
	if(k == 8 && cur.board[6] == 'o') {cur.score -= 10; return -1;}
	for(l = 0; l < 6; l=l+3){
		if(cur.board[l] != cur.board[l+3]) break;
	}
	if(l == 6 && cur.board[0] == 'x') {cur.score += 10; return 1;}
	if(l == 6 && cur.board[0] == 'o') {cur.score -= 10; return -1;}
	for(m = 1; m < 7; m+=3){
		if(cur.board[m] != cur.board[m+3]) break;
	}
	if(m == 7 && cur.board[1] == 'x') {cur.score += 10; return 1;}
	if(m == 7 && cur.board[1] == 'o') {cur.score -= 10; return -1;}
	for(n = 2; n < 8; n+=3){
		if(cur.board[n] != cur.board[n+3]) break;
	}
	if(n == 8 && cur.board[2] == 'x') {cur.score += 10; return 1;}
	if(n == 8 && cur.board[2] == 'o') {cur.score -= 10; return -1;}
	for(a = 2; a < 6; a+=2){
		if(cur.board[a] != cur.board[a+2]) break;
	}
	if(a == 6 && cur.board[2] == 'x') {cur.score += 10; return 1;}
	if(a == 6 && cur.board[2] == 'o') {cur.score -= 10; return -1;}
	for(b = 0; b< 8; b+=4){
		if(cur.board[b] != cur.board[b+4]) break;
	}
	if(b == 8 && cur.board[0] == 'x') {cur.score += 10; return 1;}
	if(b == 8 && cur.board[0] == 'o') {cur.score -= 10; return -1;}
	bool full = true;
	for(int i = 0; i < 9; i++){
		if(cur.board[i] == '_'){
			full = false;
			break;
		}
	}
	if(full) return 0;
	return -2;
}

Step minimax(State &cur, int turn){
	State curt = cur;
	int judge = isterminal(curt, fir, turn);
	if(judge==-1){
		Step temp;
		temp.next = 0;
		temp.score = -10;
		return temp;
	}
	if(judge== 1){
		Step temp;
		temp.next = 0;
		temp.score = 10;
		return temp;
	}
	if(judge== 0){
		Step temp;
		temp.next = 0;
		temp.score = 0;
		return temp;
	}
	vector<int> empty;
	for(int i = 0 ; i < 9; i++){
		if(curt.board[i] == '_') {
			empty.push_back(i);
		}
	}
	vector<Step> moves;
	for(int i = 0; i < empty.size(); i++){
		Step move;
		move.next = empty[i];
		if(turn%2 == 0) curt.board[empty[i]] = 'o';
		if(turn%2 == 1) curt.board[empty[i]] = 'x';
		int turnt = turn + 1;
		Step result = minimax(curt, turnt);
		move.score = result.score;
		curt.board[empty[i]] = '_';
		moves.push_back(move);
	}
	int bestmove = 0;
	if(turn%2==1){
		int max = -500;
		for(int i = 0; i < moves.size(); i++){
			if(moves[i].score > max){
				max = moves[i].score;
				bestmove = i;
			}
		}
	}
	else{
		int min = 500;
		for(int i = 0; i < moves.size(); i++){
			if(moves[i].score < min){
				min = moves[i].score;
				bestmove = i;
			}
		}
	}
	return moves[bestmove];
}

void aiturn(State &cur){
	cout << "It's Foursalt's turn!" << endl;
	Step temp = minimax(cur, turn);
	cout << endl;
	cur.board[temp.next]='x';
	for(int i = 0; i < 9; i++){
		cout << cur.board[i] << " ";
		if(i==2 || i==5 || i==8) cout << endl;
	}
	cout << endl;
}

void myturn(State &cur){
	cout << "It's your turn!" << endl;
	while(1){
		cout << "Please input the 'x'(0-2) and 'y'(0-2) of your move:" << endl;
		int x, y;
		cin >> x >> y;
		if(0<=x && x<=2 && 0<=y && y<=2){
			if(cur.board[3*x+y] == '_') {
				cur.board[3*x+y] = 'o'; 
				break;
			}
		}
		cout << "Invalid input!" << endl;
	}
	cout << endl;
	for(int i = 0; i < 9; i++){
		cout << cur.board[i] << " ";
		if(i==2 || i==5 || i==8) cout << endl;
	}
	cout << endl;
}
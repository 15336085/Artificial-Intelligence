#include <bits/stdc++.h>
#include <cmath>
#include <queue>
using namespace std;
class nodes{
	public: 
		pair<int,int> p;
		int fval;
		int depth;
		string s;
		bool operator<(const nodes &s) const{
			return fval > s.fval;
		}
		bool operator>(const nodes &s)const{
			return fval < s.fval;
		}
		bool operator==(const nodes &s)const{
			return fval == s.fval;
		}
};

string makestring(int a,int b){
	std::stringstream out1;
	std::stringstream out2;
	string t1,t2,str;
    out1 << a;
    t1 = out1.str();
    out2 << b;
    t2 = out2.str();
    str = "("+t1+","+t2+")";
    return str;
}

int gcd(int x, int y){
	return y == 0? x: gcd(y, x % y);
}

bool soluble(int fir, int sec, int tar){
	return tar == 0 || (fir + sec > tar && tar % gcd(fir, sec) == 0);
}

int getf(nodes temp, int s, int e){
	int g = abs(temp.p.first - s) + abs(temp.p.second - e);
	int h = temp.depth;
	return g + h;
}

int main()
{
	//int counter = 0;
    ios::sync_with_stdio(false);
    //pair<int,int> cap,ini,final;
    nodes cap,ini,final;
    ini.p.first=0,ini.p.second=0,ini.fval=0,ini.depth=0;
    ini.s = makestring(ini.p.first,ini.p.second);
    //Input initial values
    cout<<"Enter the capacity of 2 jugs\n";
    cin>>cap.p.first>>cap.p.second;
    //input final values
    cout<<"Enter the required jug config\n";
    cin>> final.p.first >>final.p.second;
    bool sol;
    sol = soluble(cap.p.first, cap.p.second, final.p.first);
    if(sol == 0){
    	cout << "No Solution.\n" ;
    	return 0;
    }
    //Using A* to find the answer
    priority_queue<nodes> open;
    queue<nodes> close;
    open.push(ini);
    nodes jug;
    while(!open.empty()){
    	jug = open.top();
    	open.pop();
    	close.push(jug);
    	if(jug.p.first == final.p.first && jug.p.second == final.p.second){
    		cout<<jug.s<<endl;
	  		break;
    	}
    	nodes temp = jug;
    	//Fill 1st Jug
    	if(jug.p.first<cap.p.first){
			temp.p = make_pair(cap.p.first,jug.p.second);
			temp.s = jug.s + makestring(temp.p.first,temp.p.second);
			temp.depth = jug.depth + 1;
			temp.fval = getf(temp, final.p.first, final.p.second);
			open.push(temp);
    	}
    	//Fill 2nd Jug
    	if(jug.p.second<cap.p.second){
			temp.p = make_pair(jug.p.first,cap.p.second);
			temp.s = jug.s + makestring(temp.p.first,temp.p.second);
			temp.depth = jug.depth + 1;
			temp.fval = getf(temp, final.p.first, final.p.second);
			open.push(temp);
    	}
    	//Empty 1st Jug
    	if(jug.p.first>0){
			temp.p = make_pair(0,jug.p.second);
			temp.s = jug.s + makestring(temp.p.first,temp.p.second);
			temp.depth = jug.depth + 1;
			temp.fval = getf(temp, final.p.first, final.p.second);
			open.push(temp);
    	}
    	//Empty 2nd Jug
    	if(jug.p.second>0){
			temp.p = make_pair(jug.p.first,0);
			temp.s = jug.s + makestring(temp.p.first,temp.p.second);
			temp.depth = jug.depth + 1;
			temp.fval = getf(temp, final.p.first, final.p.second);
			open.push(temp);
    	}
    	//Pour from 1st jug to 2nd until its full
    	if(jug.p.first>0 && (jug.p.first+jug.p.second)>=cap.p.second){
    		temp.p = make_pair((jug.p.first-(cap.p.second-jug.p.second)),cap.p.second);
    		temp.s = jug.s + makestring(temp.p.first,temp.p.second);
    		temp.depth = jug.depth + 1;
			temp.fval = getf(temp, final.p.first, final.p.second);
			open.push(temp);
    	}
    	//Pour from 2nd jug to 1st until its full
    	if(jug.p.second>0 && (jug.p.first+jug.p.second)>=cap.p.first){
    		temp.p = make_pair(cap.p.first,(jug.p.second-(cap.p.first-jug.p.first)));
    		temp.s = jug.s + makestring(temp.p.first,temp.p.second);
    		temp.depth = jug.depth + 1;
			temp.fval = getf(temp, final.p.first, final.p.second);
			open.push(temp);
    	}
    	//Pour all water from 1st to 2nd
    	if(jug.p.first>0 && (jug.p.first+jug.p.second)<=cap.p.second){
    		temp.p = make_pair(0,jug.p.first+jug.p.second);
    		temp.s = jug.s + makestring(temp.p.first,temp.p.second);
    		temp.depth = jug.depth + 1;
			temp.fval = getf(temp, final.p.first, final.p.second);
			open.push(temp);
    	}
    	//Pour from 2nd jug to 1st until its full
    	if(jug.p.second>0 && (jug.p.first+jug.p.second)<=cap.p.first){
    		temp.p = make_pair(jug.p.first+jug.p.second,0);
    		temp.s = jug.s + makestring(temp.p.first,temp.p.second);
    		temp.depth = jug.depth + 1;
			temp.fval = getf(temp, final.p.first, final.p.second);
			open.push(temp);
    	}
    }
	return 0;
}

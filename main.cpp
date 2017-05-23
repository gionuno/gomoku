#include <iostream>

#include "negamax.hpp"

using namespace std;

int main()
{
    srand(time(nullptr));
    vector< vector<int> > B(15,vector<int>(15,0));
    map<int,map<int,int> > C;
    int d = 3;
    int n = 2;
    bool done = false;

    state m;
    double s;
    while(!done)
    {
        print(B,C);
        cin >> m.x >> m.y;
        set_pos(B,C,n,m.x,m.y,1);
        print(B,C);
        done = checkgame(B);
        if(done) break;
        s = negamax(B,C,m,d,n,-1,-inf,inf);
        set_pos(B,C,n,m.x,m.y,-1);
        done = checkgame(B);
        cout << s << endl;
    }
    print(B,C);
    return 0;
}

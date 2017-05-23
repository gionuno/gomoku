#ifndef NEGAMAX_HPP_INCLUDED
#define NEGAMAX_HPP_INCLUDED

#include <vector>
#include <map>

using namespace std;

void print(vector<vector<int> > & B,map<int,map<int,int> > & C)
{
    int N = B.size();
    int M = B[0].size();

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++)
        {
            switch(B[i][j])
            {
                case -1:
                    cout << "O";
                break;
                case  0:
                    cout << ".";
                break;
                case  1:
                    cout << "X";
                break;
            }
        }
        cout << " ";
        for(int j=0;j<M;j++)
        {
            cout << (C.count(i)>0 && C[i].count(j)>0? "*" : ".");
        }
        cout << endl;
    }
    cout << endl;
}

const double inf = 1e10;
bool checkgame(const vector<vector<int> > & B)
{
    int N = B.size();
    int M = B[0].size();
//rows
    int L = 5;

    int c = 0;

    for(int i=0;i<N    ;i++)
    for(int j=0;j<M-L+1;j++)
    {
        int sum = 0;
        for(int k=0;k<L;k++)
            sum += B[i][j+k];
        if(sum ==  L || sum == -L) return true;
    }
    //columns
    for(int j=0;j<M    ;j++)
    for(int i=0;i<N-L+1;i++)
    {
        int sum = 0;
        for(int k=0;k<L;k++)
            sum += B[i+k][j];
        if(sum ==  L || sum == -L) return true;
    }
    //diags
    for(int i=0;i<N-L+1;i++)
    for(int j=0;j<M-L+1;j++)
    {
        int sum_1 = 0;
        int sum_2 = 0;
        for(int k_1=0,k_2=L-1;k_1<L;k_1++,k_2--)
        {
            sum_1 += B[i+k_1][j+k_1];
            sum_2 += B[i+k_1][j+k_2];
        }
        if(sum_1 ==  L || sum_1 == -L) return true;
        if(sum_2 ==  L || sum_2 == -L) return true;
    }
    for(int i=0;i<N;i++)
    for(int j=0;j<M;j++)
        c += (B[i][j] != 0);
    return c == N*M ? true : false;
}

vector<vector<int> > F =
{
    //2to3
    { 0, 1, 1,-1},
    { 0, 1, 1, 0},

    //3to4
    { 0, 1, 1, 1,-1},
    { 0, 1, 1, 1, 0},
    //4to5
    { 0, 1, 1, 1, 1,-1},
    { 0, 1, 1, 1, 1, 0},

    //5s
    { 1, 1, 1, 1, 1}
};

vector<double> W
{
    1.0,
    5e1,

    1e3,
    5e4,

    1e5,
    5e6,

    1e8
};

double gameover(const vector<vector<int> > & B,bool & c)
{
    int N = B.size();
    int M = B[0].size();
    c = false;
    double score = 0.0;
    for(int f=0;f<F.size();f++)
    {
        //rows
        int L = F[f].size();
        for(int i=0;i<N    ;i++)
        for(int j=0;j<M-L+1;j++)
        {
            bool exact_1 = true;
            bool exact_2 = true;

            bool exact_3 = true;
            bool exact_4 = true;

            for(int l=0;l<L;l++)
            {
                exact_1 = exact_1 && (B[i][j+l] == F[f][l]);
                exact_2 = exact_2 && (B[i][j+l] == F[f][L-1-l]);

                exact_3 = exact_3 && (B[i][j+l] == -F[f][l]);
                exact_4 = exact_4 && (B[i][j+l] == -F[f][L-1-l]);
            }
            score += W[f]*((exact_1||exact_2)-(exact_3||exact_4));
            if(f == F.size()-1)
                c = c || exact_1 || exact_2 || exact_3 || exact_4;
        }
        //columns
        for(int j=0;j<M    ;j++)
        for(int i=0;i<N-L+1;i++)
        {
            bool exact_1 = true;
            bool exact_2 = true;

            bool exact_3 = true;
            bool exact_4 = true;

            for(int l=0;l<L;l++)
            {
                exact_1 = exact_1 && (B[i+l][j] == F[f][l]);
                exact_2 = exact_2 && (B[i+l][j] == F[f][L-1-l]);

                exact_3 = exact_3 && (B[i+l][j] == -F[f][l]);
                exact_4 = exact_4 && (B[i+l][j] == -F[f][L-1-l]);
            }
            score += W[f]*((exact_1||exact_2)-(exact_3||exact_4));
            if(f == F.size()-1)
                c = c || exact_1 || exact_2 || exact_3 || exact_4;
        }
        //diags
        for(int i=0;i<N-L+1;i++)
        for(int j=0;j<M-L+1;j++)
        {
            bool exact_1 = true;
            bool exact_2 = true;

            bool exact_3 = true;
            bool exact_4 = true;

            for(int l=0;l<L;l++)
            {
                exact_1 = exact_1 && (B[i+l][j+l] == F[f][l]);
                exact_2 = exact_2 && (B[i+l][j+l] == F[f][L-1-l]);

                exact_3 = exact_3 && (B[i+l][j+l] == -F[f][l]);
                exact_4 = exact_4 && (B[i+l][j+l] == -F[f][L-1-l]);
            }
            score += W[f]*((exact_1||exact_2)-(exact_3||exact_4));
            if(f == F.size()-1)
                c = c || exact_1 || exact_2 || exact_3 || exact_4;

            exact_1 = true;
            exact_2 = true;

            exact_3 = true;
            exact_4 = true;

            for(int l=0;l<L;l++)
            {
                exact_1 = exact_1 && (B[i+l][j+L-l-1] == F[f][l]);
                exact_2 = exact_2 && (B[i+l][j+L-l-1] == F[f][L-1-l]);

                exact_3 = exact_3 && (B[i+l][j+L-l-1] == -F[f][l]);
                exact_4 = exact_4 && (B[i+l][j+L-l-1] == -F[f][L-1-l]);
            }
            score += W[f]*((exact_1||exact_2)-(exact_3||exact_4));
            if(f == F.size()-1)
                c = c || exact_1 || exact_2 || exact_3 || exact_4;
        }
    }
    int h = 0;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            h += (B[i][j]!=0);
    c = c || (h == N*M);
    return score;
}


struct state
{
    int x;
    int y;
    state(int x_=-1,int y_=-1) : x(x_),y(y_)
    {
    }
    state(const state & s_) : x(s_.x),y(s_.y)
    {
    }
};

void set_pos(vector<vector<int> > & B,map<int,map<int,int> > & C,int n,int x,int y,int p)
{
    int N = B.size();
    int M = B[0].size();

    B[x][y] = p;
    int u_l = x>=n?x-n:0;
    int u_h = x+n<N?x+n:N-1;
    int v_l = y>=n?y-n:0;
    int v_h = y+n<M?y+n:M-1;

    for(int u=u_l;u<=u_h;u++)
        for(int v=v_l;v<=v_h;v++)
            C[u][v]++;
}
void unset_pos(vector<vector<int> > & B,map<int,map<int,int> > & C,int n,int x,int y)
{
    int N = B.size();
    int M = B[0].size();

    B[x][y] = 0;
    int u_l = x>=n?x-n:0;
    int u_h = x+n<N?x+n:N-1;
    int v_l = y>=n?y-n:0;
    int v_h = y+n<M?y+n:M-1;

    for(int u=u_l;u<=u_h;u++)
        for(int v=v_l;v<=v_h;v++)
        {
            C[u][v]--;
            if(C[u][v] == 0)
                C[u].erase(v);
        }
}


double negamax(vector<vector<int> > & B,map<int,map<int,int> > & C,state & r,int d,int n,int p,double a,double b)
{
    bool c = true;
    double s = p*gameover(B,c);
    if(c || d == 0)  return s;

    state aux;
    state q_a;

    for(auto & it : C)
    for(auto & jt : it.second)
    {
        if(B[it.first][jt.first] == 0 && jt.second > 0)
        {
            set_pos(B,C,n,it.first,jt.first,p);
            double s = -negamax(B,C,aux,d-1,n,-p,-b,-a);
            state q(it.first,jt.first);
            unset_pos(B,C,n,it.first,jt.first);

            if(s > a)
            {
                a = s;
                r = q;
            }
            if(s >= b)
                return s;
        }
    }
    return a;
}
#endif // NEGAMAX_HPP_INCLUDED


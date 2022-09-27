#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

class TRI
{
public:
    int a,b,w;
};

class PQ
{
public:
    int n;
    TRI Arr[1000];
    PQ();
    void Insert(TRI x);
    TRI Delete();
    int IsEmpty();
};

PQ::PQ()
{
    n = 0;
}

void PQ::Insert(TRI x)
{
    int i;
    n += 1;
    i = n;
    Arr[i] = x;
    while(i > 1 && Arr[i].w < Arr[i/2].w)
    {
        swap(Arr[i],Arr[i/2]);
        i = i/2;
    }
}

TRI PQ::Delete()
{
    TRI ret;
    int i,j;
    ret = Arr[1];
    Arr[1] = Arr[n];
    n -= 1;
    i = 1;

    while(true)
    {
        if(i*2 > n)
        {
            break;
        }
        else if(i*2+1 > n)
        {
            if(Arr[i*2].w < Arr[i].w)
            {
                swap(Arr[i],Arr[i*2]);
                i = i*2;
            }
            else
                break;
        }
        else
        {
            if(Arr[i].w > Arr[i*2].w && Arr[i].w > Arr[i*2+1].w)
            {
                if(Arr[i*2].w > Arr[i*2+1].w)
                    j = i*2+1;
                else
                    j = i*2;
                swap(Arr[i],Arr[j]);
                i = j;
            }
            else if(Arr[i].w > Arr[i*2].w && Arr[i].w <=Arr[i*2+1].w)
            {
                j = i*2;
                swap(Arr[i],Arr[j]);
                i = j;
            }
            else if(Arr[i].w <= Arr[i*2].w && Arr[i].w > Arr[i*2+1].w)
            {
                j = i*2+1;
                swap(Arr[i],Arr[j]);
                i = j;
            }
            else
                break;
        }
    }

    return ret;
}

int PQ::IsEmpty()
{
    return n == 0;
}

PQ Q;
int n,m;

vector<pair<int,int>> Edges[1000];
vector<int> Path[1000];
int Mark[1000];

int main()
{
    int a,b,w,c;
    TRI x,y;
    scanf(" %d %d",&n,&m);

    for(int i=0;i<m;i++)
    {
        scanf(" %d %d %d",&a,&b,&w);
        Edges[a].push_back(make_pair(b,w));
        Edges[b].push_back(make_pair(a,w));
    }

    for(int i=1;i<=n;i++)
    {
        Mark[i] = 1000000;
    }

    c = 1; 
    Mark[c] = 0;

    for(int i=0;i<Edges[c].size();i++)
    {
        x.a = c;
        x.b = Edges[c][i].first;
        x.w = Mark[c] + Edges[c][i].second;
        Q.Insert(x);
    }

    while(!Q.IsEmpty())
    {
        y = Q.Delete();
        if(Mark[y.b] == 1000000)
        {
            printf("Edges from Node %d to %d of Total Length %d Selected, Previous node %d\n",y.a,y.b,y.w,y.a);
            
            c = y.b;
            Mark[c] = y.w;
            Path[c].push_back(y.a);

            for(int i=0;i<Edges[c].size();i++)
            {
                x.a = c;
                x.b = Edges[c][i].first;
                x.w = Mark[c] + Edges[c][i].second;
                Q.Insert(x);
            }

        }
        else
        {
            if(Mark[y.b] == y.w)
            {
                printf("Edges from Node %d to %d of Total Length %d ADDED, Previous node %d\n",y.a,y.b,y.w,y.a);
                Path[y.b].push_back(y.a);
            }
            else
                printf("Edges from Node %d to %d of Total Length %d Ignored\n",y.a,y.b,y.w);
        }
    }

    return 0;
}

/*
3 3
1 2 1
2 3 4
1 3 2

5 10
1 2 10
2 3 1
1 5 7
1 4 5
2 4 4
2 4 3
4 5 2
3 4 9
3 5 2
5 3 6
*/
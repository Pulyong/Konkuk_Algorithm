#include <bits/stdc++.h>
#include <vector>

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
    TRI arr[1000];
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
    arr[i] = x;

    while(n>1 && arr[n].w < arr[n/2].w)
    {
        swap(arr[i],arr[i/2]);
        i = i/2;
    }
}

TRI PQ::Delete()
{
    int i,j;
    TRI ret;
    ret = arr[1];
    if(n == 1)
    {
        n = 0;
        return ret;
    }
    arr[1] = arr[n];
    n -= 1;
    i = 1;

    while(true)
    {
        // 자식이 없다
        if(i*2 > n)
        {
            break;
        }
        // 왼쪽 자식만 존재
        else if(i*2+1>n)
        {
            if(arr[i].w > arr[i*2].w)
            {
                swap(arr[i],arr[i*2]);
                i = i*2;
            }
            else
                break;
        }
        //둘다 존재
        else
        {
            if(arr[i].w > arr[i*2].w && arr[i].w > arr[i*2+1].w)
            {
                if(arr[i*2].w > arr[i*2+1].w)
                    j = i*2+1;
                else
                    j = i*2;

                swap(arr[i],arr[j]);
                i = j;
            }
            else if(arr[i].w > arr[i*2].w && arr[i].w <= arr[i*2+1].w)
            {
                j = i*2;
                swap(arr[i],arr[j]);
                i = j;
            }
            else if(arr[i].w <= arr[i*2].w && arr[i].w > arr[i*2+1].w)
            {
                j = i*2+1;
                swap(arr[i],arr[j]);
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
int Mark[1000];

int main()
{
    int a,b,w,c;
    TRI x, y;

    scanf("%d %d",&n,&m);

    for(int i=0;i<m;i++)
    {
        scanf("%d %d %d",&a,&b,&w);
        Edges[a].push_back(make_pair(b,w));
        Edges[b].push_back(make_pair(a,w));
    }

    c = 1;
    Mark[c] = 1;
    for(int i=0;i<Edges[c].size();i++)
    {
        x.a = c;
        x.b = Edges[c][i].first;
        x.w = Edges[c][i].second;
        Q.Insert(x);
    }

    while(Q.IsEmpty() == 0)
    {
        y = Q.Delete();
        if(Mark[y.b] == 1)
        {
            continue;
        }
        else
        {
            printf("Edges from Node %d to %d of Weight %d Selected\n",y.a,y.b,y.w);
            c = y.b;
            Mark[c] = 1;
            for(int i=0;i<Edges[c].size();i++)
            {
                x.a = c;
                x.b = Edges[c][i].first;
                x.w = Edges[c][i].second;
                Q.Insert(x);
            }
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
1 5 6
1 4 5
2 4 4
2 4 3
4 5 2
3 4 9
3 5 4
5 3 6
*/
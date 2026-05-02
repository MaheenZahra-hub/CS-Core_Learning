#include <iostream>
#include <queue>
using namespace std;

enum Color { WHITE, GRAY, BLACK };

class Graph 
{
private:
    int size;
    int adj[10][10];
    Color used[10];
    int distanceArr[10];
    int parent[10];

public:

    
    Graph(int s) 
	{
        size = s;

        
        for (int i = 0; i < size; i++) 
		{
            for (int j = 0; j < size; j++) 
			{
                adj[i][j] = 0;
            }
        }

        
        for (int i = 0; i < size; i++) 
		{
            used[i] = WHITE;
            distanceArr[i] = -1;
            parent[i] = -1;    
        }
    }

    
    void addEdge(int u, int v) 
	{
        if (u >= 0 && u < size && v >= 0 && v < size) 
		{
            adj[u][v] = 1;
            adj[v][u] = 1;    
        }
    }

    
    void BFS(int s) 
	{
        for (int i = 0; i < size; i++) 
		{
            used[i] = WHITE;
            distanceArr[i] = -1;
            parent[i] = -1;
        }

        queue<int> Q;

        used[s] = GRAY;
        distanceArr[s] = 0;
        parent[s] = -1;

        Q.push(s);

        while (!Q.empty()) 
		{
            int u = Q.front();
            Q.pop();

            for (int v = 0; v < size; v++) 
			{
                if (adj[u][v] == 1 && used[v] == WHITE) 
				{
                    used[v] = GRAY;
                    distanceArr[v] = distanceArr[u] + 1;
                    parent[v] = u;
                    Q.push(v);
                }
            }

            used[u] = BLACK;
        }
    }

    
    void printResult() 
	{
        cout << "\nVertex   Color    Distance    Parent\n";
        for (int i = 0; i < size; i++) 
		{
            cout << "   " << i << "      ";

            if (used[i] == WHITE)
			{
			 cout << "WHITE";
		    }
		    
		    else if(used[i]==GRAY)
			{
			 cout << "GRAY ";
		    }
		    
            else 
			{
				cout << "BLACK";
			}

            cout<<"     "<<distanceArr[i]<<"       "<<parent[i]<<"\n";
        }
    }
};


int main() 
{
    Graph g(5);

    g.addEdge(0,1);
    g.addEdge(0,4);
    g.addEdge(0,2);
    g.addEdge(1,3);

    g.BFS(3);
    g.printResult();
}
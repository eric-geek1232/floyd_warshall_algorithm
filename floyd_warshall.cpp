/*By Eric 18-01-2021 -floyd_warshall implementation- */
#include <iostream>

using namespace std;
 
#define CONVERT_INT_TO_CHAR(integer) (char(integer))
#define INFINITE (1000000)

class Graph
{
	private:
		int **graph;
		int **distance;
		int nVertices;
			
	public:
		Graph();
		Graph(int nVertices);
		void setGraph();
		void showGraph();
		void floydWarshall();
		void showDistances();
		bool isEmpty();	
};

Graph::Graph()
{
	nVertices = 0; 
}

Graph::Graph(int nVertices)
{
	this->nVertices = nVertices;
	
	graph = new int*[nVertices];
	distance = new int*[nVertices];
	
	for (int col = 0; col < nVertices; col++) {
		graph[col] = new int [nVertices];
		distance[col] = new int [nVertices];
	}
}

void Graph::setGraph()
{	
	char noPath;
	
	cout<< "\n\n\t Adding Distances...\n"<< endl;
	
	for (int row = 0; row < nVertices; row++) {
		for (int col = 0; col < nVertices; col++) {
			char destine = CONVERT_INT_TO_CHAR(col + 65);
			char origin = CONVERT_INT_TO_CHAR(row + 65);
			
			if (origin == destine) {
				graph[row][col] = 0;
				continue;
			}
			
			cout<< "\n Is there any route "<< origin<< " TO "<< destine<< "? [s/n]: ";
			cin>> noPath;
			
			if (noPath == 'n' || noPath == 'N') {
				graph[row][col] = INFINITE;
				continue;
			}
			
			cout<< "\n Type the distance from "<< origin<< " TO "<< destine<< ": ";
			cin>> graph[row][col];
		}
	}
	
	cout<< endl;
}

void Graph::showGraph() 
{
	cout<< "\n\n\t\tShowing Adjacency Matrix...\n"<< endl;
	
	// PRINT COLUMNS
	for	(int col = 0; col < nVertices; col++) {
		cout<< "\t("<< CONVERT_INT_TO_CHAR(col + 65)<< ")";
	}
	
	cout<< "\n"<< endl;
	
	for (int row = 0; row < nVertices; row++) {
		// PRINT ROWS
		cout<< " ("<< CONVERT_INT_TO_CHAR(row + 65)<< ")\t";
		
		// PRINT CONTENT 
		for (int col = 0; col < nVertices; col++) {
			if (graph[row][col] == INFINITE) {
				cout<< " -"<< "\t";
			} else {
				cout<< " "<< graph[row][col]<< "\t";	
			}
		}
		
		cout<< "\n"<< endl;
	}
}

void Graph::floydWarshall()
{
	// COPY ALL VALUES FROM GRAPH TO DISTANCE
	for (int row = 0; row < nVertices; row++) {
		for (int col = 0; col < nVertices; col++) {
			distance[row][col] = graph[row][col];		
		}
	}

	// FIND ALL PAIRS OF THE SHORTEST PATH
	for (int pivot = 0; pivot < nVertices; pivot++) {
		for (int origin = 0; origin < nVertices; origin++) {
			for (int destine = 0; destine < nVertices; destine++) {
				int newDistance = distance[origin][pivot] + distance[pivot][destine];
				
				if (newDistance < distance[origin][destine]) {
					distance[origin][destine] = newDistance;
				}
			}
		}
	}
}

void Graph::showDistances()
{	
	cout<< "\n\n\t\tShowing The Shortest Paths..."<< endl;
	cout<< "\n=================================\n";
	
	for (int o = 0 ; o < nVertices; o++) {
		for (int d = 0; d < nVertices; d++) {
			char destine = CONVERT_INT_TO_CHAR(d + 65);
			char origin = CONVERT_INT_TO_CHAR(o + 65);
			
			if (distance[o][d] == INFINITE) {
				cout<< origin<< " To "<< destine<< " Distance Is "<< "-\n";
			} else {
				cout<< origin<< " To "<< destine<< " Distance Is "<< distance[o][d]<< "\n";	
			}	
		}
		
		cout<<"=================================\n";
	}
	
	cout<< endl;
}

bool Graph::isEmpty() 
{
	return nVertices == 0 ? true : false;
}

int main()
{
	Graph *graph = new Graph();
	int option;
	int nVertices;
	
	do {
		cout<< "\t FLOYD WARSHALL ALGORITHM\n"<< endl;
		cout<< "\t.::MENU::.\n"<< endl;
		cout<< " [1] Create Graph"<< endl;
		cout<< " [2] Show Paths"<< endl;
		cout<< " [3] Exit"<< endl;
		cout<< "\n Choose: ";
		cin>>option;
		
		switch(option) {
			case 1:
				delete graph;
				
				cout<< "\n\n Type the number of vertices ";
				cin>> nVertices;
				
				graph = new Graph(nVertices);
				
				graph->setGraph();
				graph->floydWarshall();
				break;
				
			case 2:
				if (!graph->isEmpty()) {
					graph->showGraph();	
					graph->showDistances();
				} else {
					cout<< "\n\n [Warning]-there's no a graph\n"<< endl;
				}
				break;
				
			case 3:
				cout<< "\n\n\t**Big thanks for using this program**\n"<< endl;
				break;
				
			default:
				cout<< "\n\n\tWrong option... try again!\n"<< endl;
		}
		
		system("pause");
		system("cls");
	} while (option != 3);
	
	return 0;
}

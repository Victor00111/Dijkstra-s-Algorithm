#include "Dijkstra.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


Dijkstra::Dijkstra(string fname) {
	readFile(fname);
	Interface();
    runDijkstra();
    printPath();
}


void Dijkstra::runDijkstra(){
//Set the distance to the starting
//vertex to 0 (the starting vertex is the index in the start 
//field)and set the visited array to true for the start index.
//Then initialize the distances of the cost of going to each node 
//from the start index (this is done using the adjacency  matrix 
// - matrixGraph.  
//Then initialized the starting values based on the start
//index, loop until every vertex has been visited, calling the 
//methods minDistance to find the next unvisited vertex with the 
//minimum distance, and then calling setDistances method for 
//every vertex to update distances for the unvisited vertices.
	distances[start] = 0;
	visited[start] = true;
	for (int i = 0; i < numOfCities; i++) {
		distances[i] = matrixGraph[start][i];
		if (i != start) {
			prev[i] = start;
		}
	}
	printInfoSoFar();
	bool done = false;
	while (!done) {
		setDistances(minDistance());
		printInfoSoFar();
		done = true;
		for (int i = 0; i < numOfCities; i++) {
			if (!visited[i]) {
				done = false;
			}
		}
	}
}

void Dijkstra::setDistances(int latestVert) {
// This method updates the distances array with the costs being
//updated to either their cost so far, or the cost of
//traveling through the recently visited vertex + the cost of
//traveling from that vertex to the new vertex (whichever is the
//minimum). If the minimum is through the recently visited 
//vertex, then update the previous array so that it holds the 
//latest visited vertex's index number
	for (int i = 0; i < numOfCities; i++) {
		if (distances[latestVert] + matrixGraph[latestVert][i] < distances[i]) {
			distances[i] = distances[latestVert] + matrixGraph[latestVert][i];
			prev[i] = latestVert;
		}
	}
}


int Dijkstra::minDistance( ) {
//This method finds the next unvisited vertex with the minimum
//distance.
//Once the minimum is found (along with its index in the distance
//array), the visited array at that index is set to True and that 
//index is returned from this method.
	int min = 100000;
	int minIndex;
	for (int i = 0; i < numOfCities; i++) {
		if (distances[i] < min && !visited[i] && distances[i] != 0) {
			min = distances[i];
			minIndex = i;
		}
	}
	visited[minIndex] = true;
	return minIndex;
}


void Dijkstra::printPath() {
// Gives the final shortest path from the start
// index (aka city) to the end index (aka city).
	int temp[numOfCities];
	int i = 0;
	int index = end;
	cout << Cities[start];
	while (index != start) {
		temp[i] = index;
		index = prev[index];
		i++;
	}
	i--;
	for (int j = i; j >= 0; j--) {
		cout << "->" << Cities[temp[j]];
	}
	cout << endl << endl << endl;
}

// A utility function to print the constructed distance array
void Dijkstra::printMatrix() {
	cout <<"********************************************" << endl << "Adjacency Matrix (of Cities and Distances):"<<endl;
	for (int i = 0; i< numOfCities;i++) {
		for (int j = 0; j < numOfCities; j++) {
			cout << matrixGraph[i][j] << "\t";
		}
		cout << endl;
	}
	cout <<"********************************************" << endl;
}

//Another utility method to print out the different arrays so far
//so you can see their content
void Dijkstra::printInfoSoFar() {
	cout <<"\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<i;
	}
	cout << endl;
	cout << "Dist:\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<distances[i];
	}
	cout << endl;
	cout << "Prev:\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<prev[i];
	}
	cout << endl;
	cout << "Visited:";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<visited[i];
	}
	cout << endl;
	cout << endl;
}





void Dijkstra::Interface() {
	cout << "Choose from the following: "<<endl;
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t" << i << ": " << Cities[i] << endl;
	}
	cout << endl;
	cout << "Choose your starting city (with the city's corresponding number"<<endl;
	cin >> start;
	cout << "Choose your end destination (with the city's corresponding number"<< endl;
	cin >> end;
}


void Dijkstra::readFile(string fn) {
	ifstream file(fn.c_str());
	int numcities;
	file>>numcities;
	//cout << numcities<<endl;
	numOfCities = numcities;
	Cities = new string[numOfCities];
	visited = new bool[numOfCities];
	prev = new int[numOfCities];
	distances = new int[numOfCities];
	matrixGraph = new int*[numOfCities];
	for (int i = 0; i < numOfCities; i++) {
		matrixGraph[i] = new int[numOfCities];
        distances[i] = 100000;
    	visited[i] = false;
    	prev[i] = -1;
	}
	string abbr;
	string city;
	string abbrCity;
	for (int i = 0; i < numOfCities; i++) {
		file >> abbr;
		file >> city;
		abbrCity = abbr + " "+city;
		//cout << abbrCity << ", ";
		Cities[i] = abbrCity;
	}
	//cout << endl;
	for (int ct = 0; ct < numOfCities; ct++)  {
		file >> abbr;
		//cout << abbr << ", ";
		file>>city;
		//cout << city << ": ";
		for (int i = 0; i < numOfCities; i++) {
			int x;
			file >> x;
			//cout << x << ", ";
			if (x == -1) {
				matrixGraph[ct][i] = 100000;
			}
			else matrixGraph[ct][i] = x;
		}
		//cout << endl;
	}
	//cout << "here" << endl;
    printMatrix();
	return;
}








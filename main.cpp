#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;

class AdjacencyList {
private:
	map<string, map<string, double>> graph;
	map<string, double> ranking;
public:
	void PageRank(int n);
	void insertEdge(string from, string to);
	string printForCatch();
};

void AdjacencyList::PageRank(int n)
{
	auto ind = graph.begin();
	while (ind != graph.end()) {
		ranking[ind->first] = static_cast<double>(1.0f) / static_cast<double>(graph.size());
		ind++;
	}

	// power iterations
	int i = 1;
	while (i < n) {
		map<string, double> rankTemp;
		
		// new rank calculated from incoming rank
		auto ind = graph.begin();
		while (ind != graph.end()) {
			string pageCurrent = ind->first;
			double rankUpdate = 0.0f;

			auto ind2 = graph.begin();
			while (ind2 != graph.end()) {
				string pageOther = ind2->first;
				size_t outDeg = ind2->second.size();

				rankUpdate += (!(outDeg <= 0) && !(ind2->second.count(pageCurrent) <= 0)) ? ranking[pageOther] / outDeg : 0;
				ind2++;
			}
			// update ranks
			rankTemp[pageCurrent] = rankUpdate;
			ind++;
		}
		ranking = rankTemp;
		i++;
	}

	// https://stackoverflow.com/questions/22515592/how-to-use-setprecision-in-c
	auto rInd = ranking.begin();
	while (rInd != ranking.end()) {
		cout << rInd->first << " " << fixed << setprecision(2) << rInd->second << endl;
		rInd++;
	}
}

void AdjacencyList::insertEdge(string from, string to)
{
	graph[from].insert({ to, 1 });
	graph[to] = (graph.find(to) == graph.end()) ? map<string, double>() : graph[to];
}

// used purely for catch2 testing, not required for program
string AdjacencyList::printForCatch()
{
	stringstream output;
	auto rInd = ranking.begin();
	while (rInd != ranking.end()) {
		output << rInd->first + " " << fixed << setprecision(2) << rInd->second << endl;
		rInd++;
	}
	return output.str();
}

int main() {

	AdjacencyList list;
	// main taken directly from template

	int no_of_lines, power_iterations;
	string from, to;
	cin >> no_of_lines;
	cin >> power_iterations;
	for (int i = 0; i < no_of_lines; i++)
	{
		cin >> from;
		cin >> to;
		// Do Something
		list.insertEdge(from, to);
	}
	//Create a graph object
	list.PageRank(power_iterations);
}
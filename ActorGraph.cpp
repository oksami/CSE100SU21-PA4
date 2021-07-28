/**
 * TODO: Samhita Kadali
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

struct vertex{
    string name;        //actor name
    unordered_map <string,edge*> adj;   //adjacency list OF CONNECTIONS/ moonlighting as list of nodes to which there are edges; the edges are metaphysical
    int dist;           //distance from source
    int index;          //index of vertex
    int prev;           //index of previous vertex in path
    vertex(string name): name(name) {};
};

struct edge{
    vertex actor;
    int year;
};

/* TODO */
ActorGraph::ActorGraph() {}

vector<vertex*> createGraph(){

}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraphFromFile(const char* filename) {
    ifstream infile(filename);
    bool readHeader = false;

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);

        //create vector<Vertex*> of graph
        vector <vertex*> v;

        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

        // TODO: we have an actor/movie relationship to build the graph
        if (vertexMap.find(actor) == false)         //if no actor exists yet
            vertexMap[actor] = new vertex(actor);   //make new vertex and add to map
        pair<string, int> movie = make_pair(title, year);   //insert actor into cast list of movie
        casts[movie].insert(actor);
    }

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();

    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {}

/* TODO */
void Dijkstra(const string& fromActor, const string& toActor,
                  string& shortestPath);

/* TODO */
ActorGraph::~ActorGraph() {}

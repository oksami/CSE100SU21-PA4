/**
 * TODO: Samhita Kadali
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <limits.h>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

struct vertex{
    string name;        //actor name
    unordered_map <string,edge*> adj;   //adjacency list OF CONNECTIONS/ moonlighting as list of nodes to which there are edges; the edges are metaphysical
    int dist;           //distance from source
    int index;          //index of vertex
    vertex* prev;           //pointer of previous vertex in path
    vertex(string name): name(name) {};
};

struct edge{
    vertex actor;
    int year;
    edge(vertex* actor, int year){};
};

/* TODO */
ActorGraph::ActorGraph() {}


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

    //loop through casts for each movie and create edges between each actor
    for(auto it = casts.begin(); it!=casts.end(); it++){    //iterates through casts
        for (auto actor1=it->second.begin(); actor1!=it->second.end(); actor1++) {      //iterates through all actors for each movie
            for (auto actor2=it->second.begin(); actor2!=it->second.end(); actor2++) {  //adds each actor to each others adjacency list
                if (actor1 != actor2){
                    edge* ed = new edge(vertexMap[actor2], it->first->second);
                    vertexMap[actor1]->adj[vertexMap[actor2]->name] = ed;
                }
            }
        }
    }

    //add each vertex to a vector
    for(auto it = vertexMap.begin(); it!=vertexMap.end(); it++){
            graph.push_back(it->second);
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
                     string& shortestPath) {
    queue<vertex*> toExplore;
    vertex* start = vertexMap[fromActor];
    start->dist = 0;
    toExplore.push(start);
    while( !toExplore.empty() ){
        vertex* next = toExplore.front();
        toExplore.pop();
        for(auto it = next->adj.start(); it != next->adj.end(); ++it){
            vertex* neighbor = vertexMap[*it];
            if(neighbor->dist == INT_MAX){
                neighbor->dist = next->dist+1;
                neighbor->prev = next->index;
                toExplore.push(neighbor);
            }
        }
    }
    vertex* v = vertexMap[toActor];
    while (v->name != fromActor){
        shortestPath += "(" + v->name + ")--";
        v = v->prev;
        shortestPath += "[" + v->prev->adj[v->name]->title + "@" + v->prev->adj[v->name]->year + "]--";
        v = v->prev;
    }
    shortestPath += fromActor;
}

/* TODO */
void Dijkstra(const string& fromActor, const string& toActor,
                  string& shortestPath);

/* TODO */
ActorGraph::~ActorGraph() {}

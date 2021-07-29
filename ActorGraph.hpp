/**
 * TODO: add file header
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // TODO: add data structures used in actor graph
    unordered_map<string, vertex*> vertexMap;                     //to be able to search for existing actors and their corresponding vertices
    unordered_map< pair<string, int>, vector<string> > casts;    //pair<movie, year> and list of actors
    vector <vertex*> graph;
    bool weighted;

  public:
    /* TODO */
    ActorGraph();
    /* TODO */
    bool buildGraphFromFile(const char* filename);

    /* TODO */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

   /* TODO */
    void Dijkstra(const string& fromActor, const string& toActor,
                  string& shortestPath);

    /* TODO */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP

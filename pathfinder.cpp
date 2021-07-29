#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "ActorGraph.hpp"
#include "ActorGraph.cpp"


using namespace std;

vector<string> buildPairs(const char* filename){
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

        return record;
    }
}

int main(int argc, char *argv[]){
    ActorGraph* graph = new ActorGraph();
    graph->buildGraphFromFile(argv[1]);
    bool weighted = false;
    if (argv[2]=="w") {
        weighted = true;
}
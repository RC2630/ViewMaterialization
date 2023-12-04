#ifndef NODE_DOT_H
#define NODE_DOT_H

#include "general/stringUtility.h"
#include "general/vectorUtility.h"

struct Node {

    string name;
    int numTuples;
    int currWork;
    int layer;
    vector<string> connections;
    bool isMaterialized;

    static void initializeWork(vector<Node>& nodes);

    Node(const string& raw);

};

#endif
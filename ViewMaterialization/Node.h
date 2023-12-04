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
    static string getSchema();
    static void writeToFile(const vector<Node>& nodes, const string& filename);
    static vector<string> getNodeNames(const vector<Node>& nodes, bool onlyNotMaterialized = true);
    static Node getNode(const vector<Node>& nodes, const string& nodeName);
    static Node& findNode(vector<Node>& nodes, const string& nodeName);
    static vector<string> getNodesBelow(const vector<Node>& nodes, const string& currNode);

    Node(const string& raw);
    string toString() const;

};

#endif
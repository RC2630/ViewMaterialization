#ifndef ALGORITHM_DOT_H
#define ALGORITHM_DOT_H

#include "Node.h"

struct SavingTable {

    vector<pair<string, int>> savings;

    SavingTable(const vector<string>& nodeNames);
    void writeToFile(const string& filename) const;
    void calculateSavings(const vector<Node>& nodes);
    string updateNodes(vector<Node>& nodes);

};

vector<string> findViewsToMaterialize(vector<Node>& nodes, int numViewsToMaterialize, const string& logFileName);

#endif
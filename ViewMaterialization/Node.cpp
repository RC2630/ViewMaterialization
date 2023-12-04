#include "Node.h"

#include "general/parseArguments.h"

void Node::initializeWork(vector<Node>& nodes) {

    int mostTuples = max_element(nodes.begin(), nodes.end(), [] (const Node& a, const Node& b) {
        return a.numTuples < b.numTuples;
    })->numTuples;

    for (Node& node : nodes) {
        node.currWork = mostTuples;
    }
    
}

Node::Node(const string& raw) {

    this->name = parse::parseArgument(raw, 0);
    this->numTuples = parse::parseNumericalArgument(raw, 1);
    this->layer = parse::parseNumericalArgument(raw, 2);

    if (parse::numArguments(raw) >= 3) {
        for (int i = 3; i <= parse::numArguments(raw); i++) {
            this->connections.push_back(parse::parseArgument(raw, i));
        }
    } else {
        this->connections = {};
    }

    this->isMaterialized = (this->layer == 1);
    this->currWork = -1;

}
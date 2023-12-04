#include "Node.h"

#include "general/parseArguments.h"
#include "general/file.h"

void Node::initializeWork(vector<Node>& nodes) {

    int mostTuples = max_element(nodes.begin(), nodes.end(), [] (const Node& a, const Node& b) {
        return a.numTuples < b.numTuples;
    })->numTuples;

    for (Node& node : nodes) {
        node.currWork = mostTuples;
    }
    
}

string Node::getSchema() {
    return "node tuples work layer is_materialized connections";
}

void Node::writeToFile(const vector<Node>& nodes, const string& filename) {
    vector<string> lines = {getSchema()};
    for (const Node& node : nodes) {
        lines.push_back(node.toString());
    }
    file::outputStrVecAddTo(lines, filename);
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

string Node::toString() const {

    string s =
        this->name + " " +
        to_string(this->numTuples) + " " +
        to_string(this->currWork) + " " +
        to_string(this->layer) + " " +
        strUtil::boolval(this->isMaterialized);

    for (string conn : vecUtil::sort(this->connections)) {
        s += " " + conn;
    }

    return s;

}
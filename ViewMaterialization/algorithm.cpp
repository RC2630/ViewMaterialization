#include "algorithm.h"

#include "general/abstractFunctions.h"
#include "general/file.h"

SavingTable::SavingTable(const vector<string>& nodeNames) {
    this->savings = absFunc::map<string, pair<string, int>>(nodeNames, [] (const string& nodeName) -> pair<string, int> {
        return {nodeName, 0};
    });
}

void SavingTable::writeToFile(const string& filename) const {
    vector<string> lines = vecUtil::concatenate<string>({
        {"if_we_materialized saving"},
        absFunc::map<pair<string, int>, string>(this->savings, [] (const pair<string, int>& entry) {
            return entry.first + " " + to_string(entry.second);
        })
    });
    file::outputStrVecAddTo(lines, filename);
}

void SavingTable::calculateSavings(const vector<Node>& nodes) {

    auto calculateSaving = [] (const vector<Node>& nodes, const string& currNode) {

        int saving = 0;
        Node currNodeObj = Node::getNode(nodes, currNode);

        for (const string& belowNode : Node::getNodesBelow(nodes, currNode)) {
            saving += max(0, Node::getNode(nodes, belowNode).currWork - currNodeObj.numTuples);
        }

        return saving;

    };

    for (auto& [currNode, currSaving] : this->savings) {
        currSaving = calculateSaving(nodes, currNode);
    }

}

string SavingTable::updateNodes(vector<Node>& nodes) {
    
    string maxSavingNodeName = max_element(this->savings.begin(), this->savings.end(), [] (
        const pair<string, int>& entry1, const pair<string, int>& entry2
    ) {
        return entry1.second < entry2.second;
    })->first;

    Node::findNode(nodes, maxSavingNodeName).isMaterialized = true;
    int maxSavingNodeTuples = Node::getNode(nodes, maxSavingNodeName).numTuples;

    for (const string& belowNode : Node::getNodesBelow(nodes, maxSavingNodeName)) {
        int& currWork = Node::findNode(nodes, belowNode).currWork;
        currWork = min(maxSavingNodeTuples, currWork);
    }

    return maxSavingNodeName;

}

vector<string> findViewsToMaterialize(vector<Node>& nodes, int numViewsToMaterialize, const string& logFileName) {

    vector<string> viewsToMaterialize;
    file::clearFile(logFileName);
    file::outputStrVecAddTo({"ORIGINAL NODES:\n"}, logFileName);
    Node::writeToFile(nodes, logFileName);

    for (int i = 1; i <= numViewsToMaterialize; i++) {

        file::outputStrVecAddTo({"\n" + string(100, '-') + "\n", "ITERATION #" + to_string(i) + ":\n"}, logFileName);
        SavingTable table(Node::getNodeNames(nodes, true));
        table.calculateSavings(nodes);
        table.writeToFile(logFileName);

        string maxSavingNode = table.updateNodes(nodes);
        viewsToMaterialize.push_back(maxSavingNode);
        file::outputStrVecAddTo({"\nTHE OPTIMAL VIEW TO MATERIALIZE RIGHT NOW IS NODE \"" + maxSavingNode + "\".\n"}, logFileName);
        Node::writeToFile(nodes, logFileName);

    }

    file::outputStrVecAddTo({"\nALL DONE!"}, logFileName);
    return viewsToMaterialize;

}
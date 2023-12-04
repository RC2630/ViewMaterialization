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
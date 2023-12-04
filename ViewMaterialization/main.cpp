#include "Node.h"
#include "algorithm.h"

#include "general/file.h"
#include "general/ansi_codes.h"

vector<Node> nodes;

void initializeNodes() {
    vector<string> raw;
    file::inputStrVecFrom(raw, "input/nodes.txt");
    for (int i = 1; i < raw.size(); i++) {
        nodes.push_back(Node(raw.at(i)));
    }
    Node::initializeWork(nodes);
}

void run() {
    
    initializeNodes();

    Node::writeToFile(nodes, "output/result.txt");
    SavingTable table(Node::getNodeNames(nodes));
    table.calculateSavings(nodes);
    table.writeToFile("output/result.txt");

}

int main() {
    try {
        run();
    } catch (...) {
        cout << ANSI_RED << "\nOops, something went wrong. Sorry!\n" << ANSI_NORMAL;
    }
}
#include "Node.h"
#include "algorithm.h"

#include "general/file.h"
#include "general/ansi_codes.h"

using vecUtil::operator<<;

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

    cout << "\nEnter the number of views that you would like to materialize: " << ANSI_GREEN;
    int numViewsToMaterialize; cin >> numViewsToMaterialize;
    cout << ANSI_NORMAL;

    vector<string> viewsToMaterialize = findViewsToMaterialize(nodes, numViewsToMaterialize, "output/result.txt");
    cout << "\nThe " << numViewsToMaterialize << " views that you should materialize are " << viewsToMaterialize << ".\n";

}

int main() {
    try {
        run();
    } catch (...) {
        cout << ANSI_RED << "\nOops, something went wrong. Sorry!\n" << ANSI_NORMAL;
    }
}
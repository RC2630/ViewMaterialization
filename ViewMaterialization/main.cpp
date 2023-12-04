#include "Node.h"

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

}

int main() {
    try {
        run();
    } catch (...) {
        cout << ANSI_RED << "\nOops, something went wrong. Sorry!\n" << ANSI_NORMAL;
    }
}
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

struct node {
    node() {
        node("");
    }

    node(const std::string& n) : name(n) {}

    void addchild(node& child) {
        children.push_back(&child);
        child.parent = this;
    }

    void setlevel(int lev) {
        level = lev;
    }

    std::string name;
    std::vector<node*> children;
    node* parent;
    int level = 0;
};

void dfs(node* n, int level) {
    n->setlevel(level);
    for (auto& child : n->children) {
        dfs(child, level + 1);
    }
}

int bfs(node* src, node* dest) {
    std::queue<node*> q;
    std::unordered_map<std::string, int> dists;
    dists[src->name] = 0;
    node* cur = src;
    while (cur->name.compare(dest->name) != 0) {
        if (cur->parent != nullptr && dists.find(cur->parent->name) == dists.end()) {
            q.push(cur->parent);
            dists[cur->parent->name] = dists[cur->name] + 1;
        }

        for (const auto& child : cur->children) {
            if (dists.find(child->name) == dists.end()) {
                q.push(child);
                dists[child->name] = dists[cur->name] + 1;
            }
        }

        cur = q.front();
        q.pop();
    }

    return dists[dest->name];
}

int main() {
    std::unordered_map<std::string, node> nodes;
    for (int i = 0; i < 1868; i++) {
        std::string x, y, line;
        std::cin >> line;
        x = line.substr(0, 3);
        y = line.substr(4);


        if (nodes.find(x) == nodes.end())
            nodes[x] = node(x);
        if (nodes.find(y) == nodes.end())
            nodes[y] = node(y);

        nodes[x].addchild(nodes[y]);
    }

    dfs(&(nodes["COM"]), 0);
    unsigned int res = 0;
    for (auto& n : nodes) {
        res += nodes[n.first].level;
    }

    printf("%u\n", res);

    int distance = bfs(&(nodes["YOU"]), &(nodes["SAN"]));
    printf("%d\n", distance - 2);
}
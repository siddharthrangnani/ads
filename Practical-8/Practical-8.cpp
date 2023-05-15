#include <bits/stdc++.h>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> size;
public:
    UnionFind(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }
    bool connected(int p, int q) {
        return find(p) == find(q);
    }
    void unite(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) {
            return;
        }
        if (size[rootP] < size[rootQ]) {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        } else {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
    }
    void printSet(int p) {
        int rootP = find(p);
        cout << "Set containing " << p << ":\n";
        for (int i = 0; i < parent.size(); i++) {
            if (find(i) == rootP) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    int n = 10;
    UnionFind uf(n);

    uf.unite(4, 3);
    uf.unite(3, 8);
    uf.unite(6, 5);
    uf.unite(9, 4);
    uf.unite(2, 1);
    uf.unite(5, 0);
    uf.unite(7, 2);
    uf.unite(6, 1);
    uf.printSet(3);

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    static constexpr int NMAX = (int)1e5 + 5;
    const int MOD = (int)1e9 + 7;
    int n, m;

    // in_degree[node] = the in_degree of node "node"
    vector<int> in_degree;

    /* adj - adjacent list of graph 1
     * common_adj - adjacent list of common graph
     * (graph containing the edges that appear in both graphs)
     */
    vector<int> adj[NMAX], common_adj[NMAX];

    void read_input() {
        ifstream fin("numarare.in");
        fin >> n >> m;

        // Initializing the in_degree of each node with 0
        in_degree = vector<int>(n + 1, 0);

        // Reading the edges of the first graph
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y);
        }

        /* Reading the edges of the second graph and
        keeping only the common ones */
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            if (find(adj[x].begin(), adj[x].end(), y) != adj[x].end()) {
                common_adj[x].push_back(y);
                ++in_degree[y];  // Increment the in_degree of node y
            }
        }
        fin.close();
    }

    // Function that sorts the graph topologically
    vector<int> solve_bfs() {
        vector<int> topsort;
        queue<int> q;

        // Puts all nodes with in_degree = 0 in queue
        for (int node = 1; node <= n; ++node) {
            if (in_degree[node] == 0) {
                q.push(node);
            }
        }

        // Apply BFS on the graph and fill in topsort vector
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            topsort.push_back(node);

            // Iterate through all neighbors of node
            for (auto neigh : common_adj[node]) {
                // Delete the node->neigh edge by decreasing the in_degree by 1
                --in_degree[neigh];

                // If neigh has in_degree = 0, add it to the queue
                if (in_degree[neigh] == 0) {
                    q.push(neigh);
                }
            }
        }

        // The graph is acyclic so the topsort is correct
        return topsort;
    }

    int get_result() {
        /* Using dynamic programming to count the
        number of paths from 1 to any node */
        vector<int> dp(n + 1, 0);

        // Sort the common graph topologically
        vector<int> topsort = solve_bfs();

        // We start from 1 so there is only one path to node 1
        dp[1] = 1;

        // Iterate through the nodes in topological order
        for (int node : topsort) {
            // Update the number of paths to each neighbor
            for (int neigh : common_adj[node]) {
                dp[neigh] = (dp[node] + dp[neigh]) % MOD;
            }
        }

        return dp[n];
    }

    void print_output(const int d) {
        ofstream fout("numarare.out");
        fout << d;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}

/**
 * Author: Aaryan Prakash
 * Date: 2024-11-11
 * License: Unknown
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Takes as input the full adjacency list. op_edges being true 
 * means that values are stored in the edges, as opposed to the nodes.
 * Time: O(\log N) * op
 * Status: Used before
 */
#pragma once

template<bool op_edges = false>
struct hld {
    vector<vector<int>> adj;
    vector<int> par;
    vector<int> size;
    vector<int> in;
    vector<int> head;
    vector<int> d;

    hld(int n) : adj(n), par(n), size(n), in(n), head(n), d(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs_size(int v = 0, int p = 0) {
        size[v] = 1;
        for (int &e : adj[v]) {
            if (e != p) {
                d[e] = d[v] + 1;
                par[e] = v;
                dfs_size(e, v);
                size[v] += size[e];
                if (size[e] > size[adj[v][0]] || adj[v][0] == p) swap(e, adj[v][0]);
            }
        }
    }

    void dfs_hld(int v = 0, int p = 0) {
        static int t = 0;
        in[v] = t++;
        for (int e : adj[v]) {
            if (e != p) {
                if (e == adj[v][0]) {
                    head[e] = head[v];
                } else {
                    head[e] = e;
                }
                dfs_hld(e, v);
            }
        }
    }

    template<typename F>
    void op_path(int x, int y, F op) {
        while (head[x] != head[y]) {
            if (d[head[x]] > d[head[y]]) swap(x, y);
            op(in[head[y]], in[y] + 1);
            y = par[head[y]];
        }
        if (d[x] > d[y]) swap(x, y);
        op(in[x] + (op_edges ? 1 : 0), in[y] + 1);
    }

    template<typename F>
    void op_subtree(int x, F op) { 
        op(in[x] + (op_edges ? 1 : 0), in[x] + size[x]);
    }
};

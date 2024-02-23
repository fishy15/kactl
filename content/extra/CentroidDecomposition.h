/**
 * Author: fishy15
 * Date: 2024-02-23
 * Source: Unknown
 * Description: Centroid decomposition on tree
 * License: Unknown
 * Time: O(n log n)
 * Status: not tested
 */
#pragma once

vector<int> adj[MAXN];
int sz[MAXN];
bool vis[MAXN];

int dfs_sz(int v, int p) {
    sz[v] = 1;
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            sz[v] += dfs_sz(e, v);
        }
    }
    return sz[v];
}

int dfs_root(int v, int p, int n) {
    for (int e : adj[v]) {
        if (e != p && !vis[e] && 2 * sz[e] > n) {
            return dfs_root(e, v, n);
        }
    }
    return v;
}

void centroid(int v, int p) {
    dfs_sz(v, -1);
    int c = dfs_root(v, -1, sz[v]);
    vis[c] = true;

    // do processing here
    // make sure to ignore visited nodes 

    for (int e : adj[c]) {
        if (!vis[e]) {
            centroid(e, c);
        }
    }
}

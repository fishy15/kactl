/**
 * Author: ???
 * Date: ???
 * Source: ???
 * Description: Min-cost max-flow.
 * Status: Tested on kattis:mincostmaxflow, https://codeforces.com/gym/105677/problem/J
 * Time: $O(F * SPFA)$, $F$ is flow, $SPFA$ is the cost to run SPFA (usually $O(E)$)
 */
#pragma once

struct MCMF{
        const ll inf = LLONG_MAX >> 2;
        struct edge{ int v; ll cap,flow,cost; };
        int n;
        vector<edge> edges;
        vector<vector<int>> adj; vector<pair<int,int>> par; vector<int> in_q;
        vector<ll> dist;
        MCMF( int n ) : n(n), adj(n), dist(n), par(n), in_q(n) {}
        void add_edge(int u,int v, ll c,ll f){
                int idx = edges.size();
                edges.push_back({v,f,0,c});
                edges.push_back({u,f,f,-c});
                adj[u].push_back(idx);
                adj[v].push_back(idx^1);
        }
        bool find_path(int s,int t){
                for( auto& e: dist ) e = inf;
                for( auto& e: in_q ) e = 0;
                queue<int> q; q.push(s);
                dist[s] = 0; in_q[s] = 1;
                while( !q.empty() ){
                        int cur = q.front(); q.pop();
                        in_q[cur] = 0;
                        for( int idx: adj[cur] ){
                                auto [nxt,cap,fl,wt] = edges[idx];
                                ll nxtD = dist[cur] + wt;
                                if( fl >= cap || nxtD >= dist[nxt] ) continue;
                                dist[nxt] = nxtD;
                                par[nxt] = {cur,idx};
                                if( in_q[nxt] ) continue;
                                q.push(nxt); in_q[nxt] = 1;
                        }
                }
                return dist[t] < inf;
        }
        pair<ll,ll> calc(int s,int t){
                ll flow = 0, cost = 0;
                while( find_path(s,t) ){
                        ll f = inf;
                        for( int i,u,v=t; tie(u,i)=par[v],v != s; v = u )
                                f = min(f,edges[i].cap - edges[i].flow );
                        flow += f;
                        for( int i,u,v=t; tie(u,i)=par[v],v!=s; v = u  )
                                edges[i].flow += f, edges[i^1].flow -= f;
                }
                rep(i,0,edges.size()/2)
                        cost += edges[i<<1].cost * edges[i<<1].flow;
                return {flow,cost};
        }
};

/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: the cf blog kind of
 * Description: Min Deque, useful for implementing min queue w/ rollback
 * push() is for applying an element to a running sum
 * merge() is for merging both sides of the ds (i.e. when querying)
 * Time: Amortized $O(p)$ for non-query ops where p is the runtime of push()
 * $O(m)$ for query ops where m is the runtime of merge()
 * Status: Used on https://codeforces.com/contest/2026/problem/F
 */
#pragma once

template <typename Node, typename Item, typename Query, typename Result> 
struct MinDeque {
	Node push(Node n, Item k) {
		
	}
	Result merge(Node a, Node b, Query q) {
		
	}
	Node empty;
	stack<pair<Item, Node>> left, right;
	void push_front(Item k) {
		Node &n = left.empty() ? empty : left.top().second;
		left.push({k, push(n, k)});
	}
	void push_back(Item k) {
		swap(left, right);
		push_front(k);
		swap(left, right);
	}
	Item pop_front() {
		if (left.empty()) {
			int h = sz(right) / 2;
			stack<Item> tmp;
			for (int i = 0; i < h; i++) {
				tmp.push(right.top().first);
				right.pop();
			}
			while (!right.empty()) {
				push_front(right.top().first);
				right.pop();
			}
			while (!tmp.empty()) {
				push_back(tmp.top());
				tmp.pop();
			}
		}
		Item res = left.top().first;
		left.pop();
		return res;
	}
	Item pop_back() {
		swap(left, right);
		Item res = pop_front();
		swap(left, right);
		return res;
	}
	Result query(Query q) {
		Node &l = left.empty() ? empty : left.top().second;
		Node &r = right.empty() ? empty : right.top().second;
		return merge(l, r, q);
	}
};

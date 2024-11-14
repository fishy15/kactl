/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: my head
 * Description: Area of union of rectangles (does compression internally)
 * Time: $O(n \log(n))$
 * Status: Tested on Library Checker
 */
#pragma once

struct OfflineRectangleUnionArea {
	struct Update {
		int row, l, r, k;
	};
	vector<Update> updates;
	void addRect(int r1, int r2, int c1, int c2) {
		updates.pb({r1, c1, c2, 1});
		updates.pb({r2 + 1, c1, c2, -1});
	}
	ll area() {
		vector<int> compressR, compressC;
		for (auto &update : updates) {
			compressR.pb(update.row - 1);
			compressR.pb(update.row);
			compressC.pb(update.l - 1);
			compressC.pb(update.l);
			compressC.pb(update.r);
		}
		sort(all(compressR));
		sort(all(compressC));
		int R = sz(compressR), C = sz(compressC);
		vector<vector<Update>> compressedUpdates(R);
		for (auto &update : updates) {
			update.row = lb(compressR, update.row);
			update.l = lb(compressC, update.l);
			update.r = lb(compressC, update.r);
			compressedUpdates[update.row].pb(update);
		}
		vector<SegTree::Node> start(C);
		for (int i = 0; i < C; i++) start[i].mnCnt = compressC[i] - (i == 0 ? -1 : compressC[i - 1]);
		SegTree st(start);
		ll res = 0;
		for (int i = 0; i < R; i++) {
			int h = compressR[i] - (i == 0 ? -1 : compressR[i - 1]);
			for (auto &update : compressedUpdates[i]) {
				st.rangeUpdate(update.l, update.r, {update.k});
			}
			SegTree::Node full = st.rangeQuery(0, C - 1);
			int outside = full.mn == 0 ? full.mnCnt : 0;
			res += (ll)h * (compressC[C - 1] + 1 - outside);
		}
		return res;
	}
};

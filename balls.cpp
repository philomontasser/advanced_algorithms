#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

class Stack {
public:
    vector<int> balls;

    void read(int idx) {
        int m;
        cout << "Enter number of elements for stack " << idx << ": ";
        cin >> m;
        balls.resize(m);
        for (int i = 0; i < m; i++) {
            cout << "Enter element " << i << " (bottom to top) for stack " << idx << ": ";
            cin >> balls[i];
        }
    }

    int size() const { return balls.size(); }
    bool empty() const { return balls.empty(); }
    int top() const { return balls.back(); }
    void push(int x) { balls.push_back(x); }
    void pop() { balls.pop_back(); }
};

int n, h;
vector<Stack> st;
vector<pair<int,int>> ans;
set<string> vis;

string encode() {
    string s;
    for (auto &stk : st) {
        s.push_back('|');
        for (int x : stk.balls)
            s.push_back(char('a' + x));
    }
    return s;
}

bool ok() {
    for (auto &stk : st) {
        if (stk.empty()) continue;
        int first = stk.balls[0];
        for (int x : stk.balls)
            if (x != first) return false;
    }
    return true;
}

bool dfs(int d) {
    if (ok()) return true;

    string e = encode();
    if (vis.count(e)) return false;
    vis.insert(e);

    for (int i = 0; i < n; i++) {
        if (st[i].empty()) continue;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (st[j].size() == h) continue;
            if (!st[j].empty() && st[j].top() != st[i].top()) continue;

            int x = st[i].top();
            st[i].pop();
            st[j].push(x);
            ans.push_back({i, j});

            if (dfs(d + 1)) return true;

            ans.pop_back();
            st[j].pop();
            st[i].push(x);
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter number of stacks (n): ";
    cin >> n;
    cout << "Enter maximum stack height (h): ";
    cin >> h;

    st.resize(n);
    for (int i = 0; i < n; i++)
        st[i].read(i);

    cout << "Starting DFS to solve puzzle...\n";
    dfs(0);

    cout << "Moves to solve the puzzle:\n";
    for (auto &p : ans)
        cout << "Move top of stack " << p.first << " to stack " << p.second << "\n";
}

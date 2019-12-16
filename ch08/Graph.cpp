//
// Created by sxguoli on 2019/12/11.
//
// 图结构的实现

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include<queue>
#include<set>
using namespace std;

class Graph {
protected:
    int nv; // 顶点个数
    vector<string> vertices; // 存储顶点
    map<string, int> iov; // index of value 值的下标
    bool directed; // 是否是有向图
    vector<bool> visited;
    virtual void dfs(int v) = 0;

public:
    Graph(bool dir=false) { // C++ 支持默认参数
        directed = dir;
        nv = 0;
    }

    Graph(vector<string> v, bool dir=false) {
        directed = dir;
        nv = (int)v.size(); // 否则会损失精度
        vertices = v;
        for (int i = 0; i < nv; i++) {
            iov[v[i]] = i;
        }
    }

    Graph(int n, bool dir=false) {
        directed = dir;
        nv = n;
        vertices.resize(n);
        for (int i = 0; i < n; i++) {
            vertices[i] = to_string(i);
            iov[to_string(i)] = i;
        }
    }

    virtual void print() = 0;
    virtual void insertV() {
        insertV(to_string(nv));
    }

    virtual bool insertV(string v) {
        if (iov.find(v) != iov.end()) {
            return false;
        } else {
            vertices.push_back(v);
            iov[v] = nv;
            nv++;
            return true;
        }
    }

    virtual bool insertE(string src, string dst, int weight=1) {
        insertV(src);
        insertV(dst);
        return insertE(iov[src], iov[dst], weight);
    }

    virtual bool insertE(int src, int dst, int weight=1) = 0;

    // 删除边
    virtual bool removeE(string src, string dst) {
        if (iov.find(src) == iov.end() || iov.find(dst) == iov.end()) return false;
        return removeE(iov[src], iov[dst]);
    }
    virtual bool removeE(int src, int dst) = 0;

    virtual void dfs(string v) {
        if (iov.find(v) == iov.end()) return;
        visited.resize(nv);
        for (int i = 0; i < nv; i++) {
            visited[i] = false;
        }

        dfs(iov[v]);
    }
};


// 邻接矩阵表示的图
class MGraph : public Graph {
protected:
    vector<vector<int>> adjM;
    void setAdjM() {
        adjM.resize(nv);
        for (int i = 0; i < nv; i++) {
            adjM[i].resize(nv);
            for (int j = 0; j < nv; j++) {
                adjM[i][j] = INT_MAX;
            }
        }
    }

    void dfs(int v) {
        cout << vertices[v] << " ";
        visited[v] = true;
        for (int i = 0; i < nv; i++) {
            if (!visited[i] && adjM[v][i] != INT_MAX) {
                dfs(i);
            }
        }
    }
public:
    MGraph(bool dir=false) : Graph(dir) {

    }

    MGraph(vector<string> v, bool dir=false) : Graph(v, dir) {
        setAdjM();
    }

    MGraph(int n, bool dir=false) : Graph(n, dir) {
        setAdjM();
    }

    void print() {
        cout << "\t";
        for (int i = 0; i < nv; i++) cout << vertices[i] << "\t";
        cout << endl;
        for (int i = 0; i < nv; i++) {
            cout << vertices[i] << ":\t";
            for (int j = 0; j < nv; j++) {
                if (adjM[i][j] == INT_MAX) cout << "-\t";
                else cout << adjM[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    void insertV() {
        insertV(to_string(nv));
    }

    bool insertV(string v) {
        bool r = Graph::insertV(v);
        if (!r) return false;
        // 给邻接矩阵增加一行一列
        for (int i = 0; i < nv - 1; i++) {
            adjM[i].push_back(INT_MAX);
        }
        adjM.push_back((vector<int>(nv, INT_MAX)));
        return true;
    }

    virtual bool insertE(string src, string dst, int weight=1) {
        return Graph::insertE(src, dst, weight);
    }

    virtual bool insertE(int src, int dst, int weight=1) {
        if (src < 0 || dst < 0 || src >= nv || dst >= nv) {
            return false;
        }

        // 边已经存在
        if (adjM[src][dst] != INT_MAX) return false;
        adjM[src][dst] = weight;
        if (!directed) adjM[dst][src] = weight;
        return true;
    }

    // 删除边
    virtual bool removeE(string src, string dst) {
        return Graph::removeE(src, dst);
    }
    virtual bool removeE(int src, int dst) {
        if (src < 0 || dst < 0 || src >= nv || dst >= nv) {
            return false;
        }

        // 如果边不存在， 直接返回删除边失败
        if (adjM[src][dst] == INT_MAX) {
            return false;
        }

        // 边存在，则删除
        adjM[src][dst] = INT_MAX;

        // 无向图
        if (!directed) adjM[dst][src] = INT_MAX;

        return true;// 删除成功
    }

    void dfs(string v) {
        Graph::dfs(v);
    }

    // 利用队列实现
    void bfs(string v) {
        if (iov.find(v) == iov.end()) return;
        int iv = iov[v];
        visited.resize(nv);
        for (int i = 0; i < nv; i++) visited[i] = false;
        queue<int> q;
        cout << v << " ";
        visited[iv] = true;
        q.push(iv);
        int w;
        while (!q.empty()) {
            w = q.front();
            q.pop();
            for (int i = 0; i < nv; i++) {
                if (!visited[i] && adjM[w][i] != INT_MAX) {
                    cout << vertices[i] << " ";
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
};

// 邻接表表示的图
class LGraph : public Graph {
protected:
    vector<map<int, int >> adjL;
    void setAdjL() {
        adjL.resize(nv);
        for (auto x : adjL) {
            x.clear();
        }
    }

    void dfs(int v) override {
        cout << vertices[v] << " ";
        visited[v] = true;
        for (auto x : adjL[v]) {
            if (!visited[x.first]) {
                dfs(x.first);
            }
        }
    }
public:
    LGraph(bool dir=false) : Graph(dir) {}
    LGraph(vector<string> v, bool dir=false) : Graph(v, dir) {
        setAdjL();
    }
    LGraph(int n, bool dir=false) : Graph(n, dir) {
        setAdjL();
    }

    void print() {
        for (int i = 0; i < nv; i++) {
            cout << vertices[i] <<"[" << i << "]---->";
            for (auto x : adjL[i]) {
                cout << vertices[x.first] << "(" << x.second << ")  ";
            }
            cout << endl;
        }
    }

    void insertV() {
        insertV(to_string(nv));
    }

    bool insertV(string v) {
        bool r = Graph::insertV(v);
        if (!r) return false;
        // 给邻接表增加一行
        adjL.push_back(map<int, int> ());
        return true;
    }

    virtual bool insertE(string src, string dst, int weight=1) {
        return Graph::insertE(src, dst, weight);
    }

    virtual bool insertE(int src, int dst, int weight=1) {
        if (src < 0 || dst < 0 || src >= nv || dst >= nv) {
            return false;
        }

        // 边已经存在
        if (adjL[src].find(dst) != adjL[src].end()) return false;
        adjL[src].insert(pair<int, int>(dst, weight));
        if (!directed) adjL[dst].insert(pair<int, int>(src, weight));
        return true;
    }

    // 删除边
    virtual bool removeE(string src, string dst) {
        return Graph::removeE(src, dst);
    }
    virtual bool removeE(int src, int dst) {
        if (src < 0 || dst < 0 || src >= nv || dst >= nv) {
            return false;
        }

        // 如果边不存在， 直接返回删除边失败
        if (adjL[src].find(dst) == adjL[src].end()) {
            return false;
        }

        // 边存在，则删除
        adjL[src].erase(dst);

        // 无向图
        if (!directed) adjL[dst].erase(src);

        return true;// 删除成功
    }

    // 函数指针，将要做的是通过函数指针传递进去
//    void dfs(void (*visit(string))) {
//
//    }

    void dfs(string v) override {
        Graph::dfs(v);
    }

    void bfs(string v) {
        // 判断点v是否存在
        if (iov.find(v) == iov.end())return;
        int iv = iov[v];
        visited.resize(nv);
        for (int i = 0; i < nv; i++)  visited[i] = 0;
        queue<int> q;
        cout << v << " ";
        visited[iv] = true;
        q.push(iv);
        int w;
        while (!q.empty()) {
            w = q.front();
            q.pop();
            for (auto x : adjL[w]) {
                if (!visited[x.first]) {
                    cout << vertices[x.first] << " ";
                    visited[x.first] = true;
                    q.push(x.first);
                }
            }
        }
    }

    void dfs(int v, set<int>& school) {
        visited[v] = true;
        school.insert(v);
        for (auto x : adjL[v]) {
            if (!visited[x.first]) dfs(x.first, school);
        }
    }

    // 深度优先遍历
    void findSchool() {
        set<int> school;
        vector<set<int>> schoolList;
        visited.resize(nv);
        for (int i = 0; i < nv; i++) {
            visited[i] = false;
        }
        for (int i = 0; i < nv; i++) {
            school.clear();
            if (!visited[i]) dfs(i, school);
            schoolList.push_back(school);
        }

        int max = schoolList[0].size();
        int maxi = 0;
        for (int i = 1; i < schoolList.size(); i++) {
            if (max < schoolList[i].size()) {
                max = schoolList[i].size();
                maxi = i;
            }
        }
        cout << max << endl;
        for (auto x : schoolList[maxi]) {
            cout << vertices[x] << " ";
        }
    }

    // 广度优先遍历
    void findSchoolBFS() {
        queue<int> q;
        vector<int> inschool(nv, -1); // 人所属的学校
        int school, count, max, maxschool;
        maxschool = max = count = school = 0;
        for (int i = 0; i < nv; i++) {
            if (inschool[i] != -1) continue;
            school++;
            count = 1;
            inschool[i] = school;
            q = queue<int>();
            q.push(i);
            int w;
            while (!q.empty()) {
                w = q.front();
                q.pop();
                for (auot x : adjL[w]) {
                    if (inschool[x.first] == -1) {
                        inschool[x.first] = school;
                        count++;
                        q.push(x.first);
                    }
                }
            }

            if (max < count) {
                max = count;
                maxschool = school;
            }
        }

        cout << max << endl;
        for (int i = 0; i < nv; i++) {
            if (inschool[i] == maxschool) {
                cout << vertices[i] << " ";
            }
        }
        cout << endl;
    }


};

/**
 0   1    2    3
 jan Feb  Mar  Apr
 */

int main() {
    vector<string> v = {"AA", "BB", "CC", "DD", "EE"};
    //Graph g(v);
//    Graph g(5);
//    g.test();
//    MGraph g(5);
//    LGraph g(v);
//    g.insertV("X");
    LGraph g(v);
    g.insertE("AA", "CC");
    g.insertE(1, 3);
    g.insertE("DD", "EE", 6);
    g.insertE("X", "EE");
    g.insertE("P", "Q");
    g.insertE("CC", "X");
    g.insertE("EE", "BB");
    g.print();

    // 深度优先遍历
    g.dfs("AA");

    cout << endl;
    cout << "===================" << endl;
    // 广度优先遍历
    g.bfs("AA");
    return 0;
}
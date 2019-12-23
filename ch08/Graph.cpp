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

    // 单源最短路径
    void dijkstra(string src) {
        if (iov.find(src) == iov.end()) return;
        vector<int> d(nv, INT_MAX);
        vector<int> from(nv, -1);
        vector<bool> known(nv, false);
        d[iov[src]] = 0;
        int minDis, v;
        for (int t = 0; t < nv; t++) {
            minDis = INT_MAX;
            v = -1;
            for (int i = 0; i < nv; i++) {
                if (known[i] == false && d[i] < minDis) {
                    minDis = d[i];
                    v = i;
                }
            }

            if (v == -1) break; // 无路可走
            known[v] = true;
            for (int w = 0; w < nv; w++) {
                if (adjM[v][w] != INT_MAX && !known[w] && d[v] + adjM[v][w] < d[w]) {
                    d[w] = d[v] + adjM[v][w];
                    from[w] = v;
                }
            }
        }

        for (int i = 0; i < nv; i++) cout << i << '\t';
        cout << endl;
        for (int i = 0; i < nv; i++) cout << vertices[i] << '\t';
        cout << endl;
        for (int i = 0; i < nv; i++) cout << d[i] << '\t';
        cout << endl;
        for (int i = 0; i < nv; i++) cout << (from[i] >= 0?vertices[from[i]] : "-") << '\t';
        cout << endl;
    }

    void weightedShortest(string src) {
        if (iov.find(src) == iov.end()) return;
        vector<int> d(nv, INT_MAX);
        vector<int> from(nv, -1);

        queue<int> q;
        vector<bool> inqueue(nv, false);
        d[iov[src]] = 0;

        q.push(iov[src]);
        inqueue[iov[src]] = true;

        int v;
        while (!q.empty()) {
            v = q.front();
            q.pop();
            inqueue[v] = false;
            for (int w = 0; w < nv; w++) {
                if (adjM[v][w] != INT_MAX && d[v] + adjM[v][w] < d[w]) {
                    d[w] = d[v] + adjM[v][w];
                    from[w] = v;
                    if (!inqueue[w]) {
                        q.push(w);
                        inqueue[w] = true;
                    }
                }
            }
        }

        for (int i = 0; i < nv; i++) cout << i << '\t';
        cout << endl;
        for (int i = 0; i < nv; i++) cout << vertices[i] << '\t';
        cout << endl;
        for (int i = 0; i < nv; i++) cout << d[i] << '\t';
        cout << endl;
        for (int i = 0; i < nv; i++) cout << (from[i] >= 0?vertices[from[i]] : "-") << '\t';
        cout << endl;
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
                for (auto x : adjL[w]) {
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

    bool topSort() { // 有环则会出错
        vector<int> inDegree(nv, 0);
        for (const auto& vl : adjL) {
            for (auto w : vl) { // <x,y>
                inDegree[w.first]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < nv; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        int cnt = 0;
        int v;
        while (!q.empty()) {
            v = q.front();
            q.pop();
            cout << vertices[v] << " ";
            cnt++;
            for (auto w : adjL[v]) {
                inDegree[w.first]--;
                if (inDegree[w.first] == 0) {
                    q.push(w.first);
                }
            }
        }

        cout << endl;
        if (cnt != nv) return false; // 表示有环
        return true;
    }

    void shortest(string src) {
        if (iov.find(src) == iov.end()) return;
        vector<int> d(nv, INT_MAX);
        vector<int> from(nv, -1);
        d[iov[src]] = 0;
        queue<int> q;
        q.push(iov[src]);
        int v;
        while (!q.empty()) {
            v = q.front();
            q.pop();
            for (auto w : adjL[v]) {
                if (d[w.first] == INT_MAX) {
                    d[w.first] = d[v] + 1;
                    from[w.first] = v;
                    q.push(w.first);
                }
            }
        }

        for (int i = 0; i < nv; i++) {
            cout << vertices[i] << "(" << d[i] << ", " << (from[i] >= 0 ? vertices[from[i]] : "-") << ") ";
        }
        cout << endl;
    }

};

/**
 0   1    2    3
 jan Feb  Mar  Apr
 */

int main() {
//    vector<string> v = {"AA", "BB", "CC", "DD", "EE"};
//    //Graph g(v);
////    Graph g(5);
////    g.test();
////    MGraph g(5);
////    LGraph g(v);
////    g.insertV("X");
//    LGraph g(v);
//    g.insertE("AA", "CC");
//    g.insertE(1, 3);
//    g.insertE("DD", "EE", 6);
//    g.insertE("X", "EE");
//    g.insertE("P", "Q");
//    g.insertE("CC", "X");
//    g.insertE("EE", "BB");
//    g.print();
//
//    // 深度优先遍历
//    g.dfs("AA");
//
//    cout << endl;
//    cout << "===================" << endl;
//    // 广度优先遍历
//    g.bfs("AA");


    // 拓扑排序
    /*
输入示例:
5
C03 C04
C04 C05
C01 C02
C05 C06
C02 C06


//*/
//    LGraph g(true);
//    string n1, n2;
//    int M;
//    cin >> M;
//    for (int i = 0; i < M; i++) {
//        cin >> n1 >> n2;
//        g.insertE(n1, n2);
//    }
////    g.topSort();
//    g.shortest("C");
    MGraph g(true);
    string n1, n2;
    int weight;
    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> n1 >> n2 >> weight;
        g.insertE(n1, n2, weight);
    }
//    g.dijkstra("A");
    g.weightedShortest("A");
    return 0;
}

// 无权图最短路径输入
/**
12
A B
C A
A D
B D
B E
D C
D E
C F
D F
D G
E G
G F
*/

// 有权图最短路径输入
/**
12
A B 2
C A 4
A D 1
B D 3
B E 10
D C 2
D E 2
C F 5
D F 8
D G 4
E G 6
G F 1

*/
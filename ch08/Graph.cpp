//
// Created by sxguoli on 2019/12/11.
//
// 图结构的实现

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Graph {
protected:
    int nv; // 顶点个数
    vector<string> vertices; // 存储顶点
    map<string, int> iov; // index of value 值的下标
    bool directed; // 是否是有向图

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
public:
    LGraph(bool dir=false) : Graph(dir) {}
    LGraph(vector<string> v, bool dir=false) : Graph(v, dir) {
        setAdjL();
    }
    LGraph(int n, bool dir=false) : Graph(n, dir) {
        setAdjL();
    }

    void print() {
        adjL[0].insert(pair<int, int>(1, 90));
        adjL[0].insert(pair<int,int>(2, 30));
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
        if (!directed) adjL.erase(src);

        return true;// 删除成功
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
    LGraph g(v, true);
    g.insertE("AA", "CC");
    g.insertE(1, 3);
    g.insertE("DD", "EE", 6);
    g.insertE("x", "EE");
    g.insertE("P", "Q");
    g.print();
    return 0;
}
#ifndef __MIN_COST_MAX_FLOW_H__
#define __MIN_COST_MAX_FLOW_H__

#include <queue>
using namespace std;
#define INF 10000000.F

struct Edge {
    int a;
    float c;
    Edge *nxt, *rev;
    Edge(int to, float cost, Edge *Next) : a(to), c(cost), nxt(Next), rev(nullptr)
    {
    }
    Edge()
    {
    }
};

class MinCostMaxFlow
{
    private:
    int nodes;
    std::vector<Edge *> *G;

    public:
    MinCostMaxFlow()
    {
        G = new std::vector<Edge *>();
        nodes = 0;
    }
    void free()
    {
        for (size_t i = 0; i < G->size(); ++i) {
            freeEdge((*G)[i]);
        }
        G->clear();
        nodes = 0;
    }
    void setNodes(int cnt1, int cnt2)
    {
        int cnt = cnt1 + cnt2;
        if (cnt <= 0) {
            return;
        }
        nodes = cnt;
        G->resize(nodes + 2);
        for (size_t i = 0; i < G->size(); ++i) {
            (*G)[i] = nullptr;
        }
        for (int i = 1; i <= cnt1; ++i) {
            Edge *tmp = new Edge(i, 0, (*G)[0]);
            (*G)[0] = tmp;
            Edge *rtmp = new Edge(0, INF, (*G)[i]);
            (*G)[i] = rtmp;
            tmp->rev = rtmp;
            rtmp->rev = tmp;
        }
        for (int i = cnt1 + 1; i <= cnt1 + cnt2; ++i) {
            Edge *tmp = new Edge(i, INF, (*G)[nodes + 1]);
            (*G)[nodes + 1] = tmp;
            Edge *rtmp = new Edge(nodes + 1, 0, (*G)[i]);
            (*G)[i] = rtmp;
            tmp->rev = rtmp;
            rtmp->rev = tmp;
        }
    }
    int addEdge(int a, int b, float c)
    {
        int n = nodes;
        if (a < 1 || a > n || b < 1 || b > n || a == b) {
            return -1;
        }
        Edge *tmp = new Edge(b, c, (*G)[a]);
        (*G)[a] = tmp;
        Edge *rtmp = new Edge(a, INF, (*G)[b]);
        (*G)[b] = rtmp;
        tmp->rev = rtmp;
        rtmp->rev = tmp;
        return 0;
    }
    void freeEdge(Edge *ptr)
    {
        Edge *pre;
        for (; ptr != nullptr; ptr = pre) {
            pre = ptr->nxt;
            delete ptr;
        }
    }
    int spfa(std::vector<int> &mt)
    {
        int n = nodes + 2;
        std::queue<int> q;
        std::vector<float> d(n);
        std::vector<bool> inq(n);
        std::vector<int> pre(n);
        std::vector<Edge *> ped(n);
        for (int i = 0; i < n; ++i) {
            d[i] = INF;
            inq[i] = false;
        }
        q.push(0);
        inq[0] = true;
        d[0] = 0;
        pre[0] = -1;
        ped[0] = nullptr;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            inq[x] = false;
            for (Edge *p = (*G)[x]; p != nullptr; p = p->nxt) {
                int y = p->a;
                float c = p->c;
                if (c != INF && d[x] + c < d[y]) {
                    d[y] = d[x] + c;
                    pre[y] = x;
                    ped[y] = p;
                    if (!inq[y]) {
                        q.push(y);
                        inq[y] = true;
                    }
                }
            }
        }
        if (d[n - 1] < INF) {
            int nw = n - 1;
            while (pre[nw] >= 0) {
                ped[nw]->rev->c = -ped[nw]->c;
                ped[nw]->c = INF;
                mt[pre[nw]] = nw;
                nw = pre[nw];
            }
            return 1;
        }
        return 0;
    }
    std::vector<int> flow()
    {
        std::vector<int> res;

        res.resize(nodes + 2, -1);
        while (spfa(res))
            ;
        return res;
    }
    ~MinCostMaxFlow()
    {
        free();
        delete G;
    };
};

std::vector<int> runMatch(std::vector<std::vector<float>> &mat)
{
    const size_t row_num = mat.size();
    const size_t col_num = mat[0].size();
    MinCostMaxFlow graph;
    graph.setNodes(row_num, col_num);

    for (size_t j = 0; j < col_num; j++) {
        for (size_t i = 0; i < row_num; i++) {
            graph.addEdge(i + 1, row_num + j + 1, mat[i][j]);
        }
    }
    auto graph_result = graph.flow();
    std::vector<int> ret(row_num);
    for (size_t i = 0; i < ret.size(); i++) {
        ret[i] = graph_result[i + 1] - row_num - 1;
        // 未匹配
        if (ret[i] < 0 || ret[i] >= col_num) {
            ret[i] = -1;
        }
    }
    return ret;
}

#endif

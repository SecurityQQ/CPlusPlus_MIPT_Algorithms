#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory>
#include <limits>

#define INF std::numeric_limits<long long>::max();

using namespace std;

struct Edge {
    Edge(size_t inFrom, size_t inTo, long long inCapacity) : from(inFrom), to(inTo), posFrom(0), posTo(0), capacity(inCapacity), resCapacity(inCapacity), addCapacity(0){};
    size_t from;
    size_t to;
    size_t posFrom;
    size_t posTo;
    long long capacity;
    long long resCapacity;
    long long addCapacity;
};

bool layeredNetwork(vector< shared_ptr<Edge> >& edges, vector< vector< shared_ptr <Edge> > >& graph, vector< vector< shared_ptr <Edge> > >& lNetwork){
    for(size_t i = 0 ; i < graph.size(); ++i)
        lNetwork[i].clear();
    vector<long long> levels(graph.size(), -1);
    levels[0] = 0;
    queue<size_t> q;
    q.push(0);
    bool flag = false;
    while(!q.empty()){
        size_t cur = q.front();
        q.pop();
        for(size_t i = 0 ; i < graph.size(); ++i){
            if(graph[cur][i].get() != NULL) {
                if (graph[cur][i]->from == cur && graph[cur][i]->resCapacity > 0) {
                    size_t to = graph[cur][i]->to;
                    if (to == (graph.size() - 1))
                        flag = true;
                    if (levels[to] == -1 || levels[to] == (levels[cur] + 1)) {
                        lNetwork[cur].push_back(graph[cur][i]);
                        lNetwork[to].push_back(graph[cur][i]);
                        graph[cur][i]->posFrom = (lNetwork[cur].size() - 1);
                        graph[cur][i]->posTo = (lNetwork[to].size() - 1);
                        if(levels[to] == -1)
                            q.push(to);
                        levels[to] = levels[cur] + 1;
                    }
                }
            }
        }
    }
    return flag;
}

void delVertex(vector< shared_ptr<Edge> >& edges, vector< vector< shared_ptr <Edge> > >& graph, vector< vector< shared_ptr <Edge> > >& lNetwork,
               vector<long long>& inpotential, vector<long long>& outpotential, vector<long long>& potential, size_t vertex){
    if(potential[vertex] == -1)
        return;
    queue<size_t> delQueue;
    for(size_t i = 0; i < lNetwork[vertex].size(); ++i){
        size_t from = lNetwork[vertex][i]->from;
        size_t to = lNetwork[vertex][i]->to;
        if(from == vertex){
            inpotential[to] -= lNetwork[vertex][i]->resCapacity;
            potential[to] = min(inpotential[to], outpotential[to]);
            size_t posTo = lNetwork[vertex][i]->posTo;
            if(lNetwork[to].back()->from == to)
                lNetwork[to].back()->posFrom = posTo;
            else
                lNetwork[to].back()->posTo = posTo;
            swap(lNetwork[to][posTo], lNetwork[to].back());
            lNetwork[to].pop_back();
            if(potential[to] == 0)
                delQueue.push(to);
        }else{
            outpotential[from] -= lNetwork[vertex][i]->resCapacity;
            potential[from] = min(inpotential[from], outpotential[from]);
            size_t posFrom = lNetwork[vertex][i]->posFrom;
            if(lNetwork[from].back()->from == from)
                lNetwork[from].back()->posFrom = posFrom;
            else
                lNetwork[from].back()->posTo = posFrom;
            swap(lNetwork[from][posFrom], lNetwork[from].back());
            lNetwork[from].pop_back();
            if(potential[from] == 0)
                delQueue.push(from);
        }
    }
    lNetwork[vertex].clear();
    inpotential[vertex] = outpotential[vertex] = potential[vertex] = -1;
    while(!delQueue.empty()) {
        delVertex(edges, graph, lNetwork, inpotential, outpotential, potential, delQueue.front());
        delQueue.pop();
    }
}

void nullPotentials(vector< shared_ptr<Edge> >& edges, vector< vector< shared_ptr <Edge> > >& graph, vector< vector< shared_ptr <Edge> > >& lNetwork,
                    vector<long long>& inpotential, vector<long long>& outpotential, vector<long long>& potential){
    for(size_t i = 0; i < graph.size(); ++i){
        if(potential[i] == 0)
            delVertex(edges, graph, lNetwork, inpotential, outpotential, potential, i);
    }
}

void blockFlow(vector< shared_ptr<Edge> >& edges, vector< vector< shared_ptr <Edge> > >& graph, vector< vector< shared_ptr <Edge> > >& lNetwork){
    vector<long long> inpotential(graph.size(), -1), outpotential(graph.size(), -1), potential(graph.size(), -1);
    for(size_t i = 0; i < graph.size(); ++i){
        if(lNetwork[i].size() > 0)
            inpotential[i] = outpotential[i] = potential[i] = 0;
        for(size_t j = 0; j < lNetwork[i].size(); ++j){
            size_t from = lNetwork[i][j]->from;
            if(from == i) {
                outpotential[i] += lNetwork[i][j]->resCapacity;
                potential[i] = min(inpotential[i], outpotential[i]);
            }else{
                inpotential[i] += lNetwork[i][j]->resCapacity;
                potential[i] = min(inpotential[i], outpotential[i]);
            }
        }
    }
    inpotential[0] = INF;
    outpotential[graph.size() - 1] = INF;
    potential[0] = min(inpotential[0], outpotential[0]);
    potential[graph.size() - 1] = min(inpotential[graph.size() - 1], outpotential[graph.size() - 1]);
    while(1) {
        nullPotentials(edges, graph, lNetwork, inpotential, outpotential, potential);
        long long minPot = INF;
        long long curminpos = -1;
        for (size_t i = 0; i < graph.size(); ++i)
            if (potential[i] != -1) if (potential[i] < minPot) {
                curminpos = i;
                minPot = potential[i];
            }
        if (curminpos == -1)
            return;
        queue<pair<long long, long long> > flowQueue;
        flowQueue.push(make_pair(minPot, curminpos));
        while (!flowQueue.empty()) {
            long long curPotential = flowQueue.front().first;
            long long curpos = flowQueue.front().second;
            flowQueue.pop();
            for (size_t i = 0; i < lNetwork[curpos].size(); ++i) {
                size_t from = lNetwork[curpos][i]->from;
                size_t to = lNetwork[curpos][i]->to;
                if (from == curpos) {
                    long long curcap = min(potential[to], lNetwork[curpos][i]->resCapacity);
                    if (curcap >= curPotential) {
                        lNetwork[curpos][i]->resCapacity -= curPotential;
                        inpotential[to] -= curPotential;
                        potential[to] = min(inpotential[to], outpotential[to]);
                        outpotential[from] -= curPotential;
                        potential[from] = min(inpotential[from], outpotential[from]);
                        if (graph[to][from].get() == NULL) {
                            edges.push_back(shared_ptr<Edge>(new Edge(to, from, 0)));
                            graph[to][from] = edges.back();
                            edges.back()->resCapacity = curPotential;
                        } else
                            graph[to][from]->resCapacity += curPotential;
                        flowQueue.push(make_pair(curPotential, to));
                        curPotential = 0;
                        break;
                    } else {
                        lNetwork[curpos][i]->resCapacity -= curcap;
                        inpotential[to] -= curcap;
                        curPotential -= curcap;
                        potential[to] = min(inpotential[to], outpotential[to]);
                        outpotential[from] -= curcap;
                        potential[from] = min(inpotential[from], outpotential[from]);
                        if (graph[to][from].get() == NULL) {
                            edges.push_back(shared_ptr<Edge>(new Edge(to, from, 0)) );
                            graph[to][from] = edges.back();
                            edges.back()->resCapacity = curcap;
                        } else
                            graph[to][from]->resCapacity += curcap;
                        flowQueue.push(make_pair(curcap, to));
                    }
                }
            }
        }
        flowQueue.push(make_pair(minPot, curminpos));
        while (!flowQueue.empty()) {
            long long curPotential = flowQueue.front().first;
            long long curpos = flowQueue.front().second;
            flowQueue.pop();
            for (size_t i = 0; i < lNetwork[curpos].size(); ++i) {
                size_t from = lNetwork[curpos][i]->from;
                size_t to = lNetwork[curpos][i]->to;
                if (to == curpos) {
                    long long curcap = min(potential[from], lNetwork[curpos][i]->resCapacity);
                    if (curcap >= curPotential) {
                        lNetwork[curpos][i]->resCapacity -= curPotential;
                        outpotential[from] -= curPotential;
                        potential[from] = min(inpotential[from], outpotential[from]);
                        inpotential[to] -= curPotential;
                        potential[to] = min(inpotential[to], outpotential[to]);
                        if (graph[to][from].get() == NULL) {
                            edges.push_back(shared_ptr<Edge>(new Edge(to, from, 0)));
                            graph[to][from] = edges.back();
                            edges.back()->resCapacity = curPotential;
                        } else
                            graph[to][from]->resCapacity += curPotential;
                        flowQueue.push(make_pair(curPotential, from));
                        curPotential = 0;
                        break;
                    } else {
                        lNetwork[curpos][i]->resCapacity -= curcap;
                        outpotential[from] -= curcap;
                        potential[from] = min(inpotential[from], outpotential[from]);
                        inpotential[to] -= curcap;
                        potential[to] = min(inpotential[to], outpotential[to]);
                        curPotential -= curcap;
                        if (graph[to][from].get() == NULL) {
                            edges.push_back(shared_ptr<Edge>(new Edge(to, from, 0)));
                            graph[to][from] = edges.back();
                            edges.back()->resCapacity = curcap;
                        } else
                            graph[to][from]->resCapacity += curcap;
                        flowQueue.push(make_pair(curcap, from));
                    }
                }
            }
        }
    }
}

void dinic(vector< shared_ptr<Edge> >& edges, vector< vector< shared_ptr <Edge> > >& graph, vector< vector< shared_ptr <Edge> > >& lNetwork, long long numEdge){
    while(1) {
        bool flag = layeredNetwork(edges, graph, lNetwork);
        if (!flag) {
            long long answ = 0;
            for(size_t i = 0; i < graph[0].size(); ++i)
                if(graph[0][i].get() != NULL)
                    if(graph[0][i]->from == 0 && (graph[0][i]->capacity >= graph[0][i]->resCapacity) )
                        answ += graph[0][i]->capacity - graph[0][i]->resCapacity;
            cout << answ << '\n';
            vector<vector<long long> > resFlow(graph.size(), vector<long long>(graph.size(), 0));
            for(size_t i = 0; i < numEdge; ++i) {
                long long flow = (edges[i]->capacity - edges[i]->resCapacity);
                size_t from = edges[i]->from;
                size_t to = edges[i]->to;
                if(flow >= 0) {
                    resFlow[from][to] += flow;
                }
                edges[i]->capacity -= edges[i]->addCapacity;
            }
            for( size_t i = 0; i < numEdge; ++i){
                size_t from = edges[i]->from;
                size_t to = edges[i]->to;
                if( resFlow[from][to] >  edges[i]->capacity ){
                    cout << edges[i]->capacity << '\n';
                    resFlow[from][to] -= edges[i]->capacity;
                }else{
                    if(resFlow[from][to] >= 0)
                        cout << resFlow[from][to] << '\n';
                    else
                        cout << 0 << '\n';
                    resFlow[from][to] = 0;
                }
            }
            return;
        } else
            blockFlow(edges, graph, lNetwork);
    }
}

int main() {
    long long numVertex, numEdges;
    cin >> numVertex >> numEdges;
    vector< shared_ptr<Edge> > edges;
    vector< vector< shared_ptr <Edge> > > graph(numVertex, vector< shared_ptr<Edge> >(numVertex));
    vector< vector< shared_ptr <Edge> > > lNetwork(numVertex);
    for(size_t i = 0; i < numEdges; ++i){
        size_t from, to;
        long long capacity;
        cin >> from >> to >> capacity;
        --from;
        --to;
        edges.push_back(shared_ptr<Edge>(new Edge(from , to , capacity)));
        if(graph[from][to].get() == NULL)
            graph[from][to] = edges.back();
        else {
            graph[from][to]->capacity += edges.back()->capacity;
            graph[from][to]->resCapacity += edges.back()->capacity;
            graph[from][to]->addCapacity += edges.back()->capacity;
        }
    }
    dinic(edges, graph, lNetwork, numEdges);
    return 0;
}
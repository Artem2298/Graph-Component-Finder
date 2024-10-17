#include "Graph.h"

Edge::Edge() : from(0), to(0) {}

Edge::Edge(int from, int to) : from(from), to(to) {}

int Edge::GetFrom()
{
    return this->from;
}

int Edge::GetTo()
{
    return this->to;
}

void Edge::SetFrom(int from)
{
    this->from = from;
}

void Edge::SetTo(int to)
{
    this->to = to;
}

int Edge::LoadData(int numberOfNodes, vector<Edge>& edges) {
    ifstream file("file.txt");
    if (!file.is_open()) {
        throw runtime_error("File not found");
    }
    string line;
    while (getline(file, line)) {
        istringstream tokenStream(line);
        string token;
        int from, to;
        getline(tokenStream, token, ' ');
        from = std::stoi(token);
        getline(tokenStream, token, ' ');
        to = std::stoi(token);
        edges.push_back(Edge{ from,to });
        numberOfNodes++;
    }
    file.close();
    int max = 0;
    for (int i = 0; i < numberOfNodes; i++) {
        if (edges[i].GetFrom() > max) {
            max = edges[i].GetFrom();
        }
        if (edges[i].GetTo() > max) {
            max = edges[i].GetTo();
        }
    }
    numberOfNodes = max + 1;
    return numberOfNodes;
}

Graph::Graph(vector<Edge>& edges, int numberOfNodes) {
    this->adjacencyList.resize(numberOfNodes);
    this->visited.resize(numberOfNodes);

    for (Edge& edge : edges) {
        this->adjacencyList[edge.GetFrom()].push_back(edge.GetTo());
        this->adjacencyList[edge.GetTo()].push_back(edge.GetFrom());
    }
}

void Graph::FindBigComponent(int numberOfNodes, vector<int>& BigComp, vector<int>& BigCompHelp) {
    for (int i = 0; i < numberOfNodes; i++) {
        if (!this->visited[i]) {
            DFS(i, BigCompHelp);

            if (BigComp.size() <= BigCompHelp.size()) {
                BigComp = move(BigCompHelp);
                sort(BigComp.begin(), BigComp.end());
            }
            BigCompHelp.clear();
        }
    }
}

void Graph::DFS(int index, vector<int>& BigCompHelp) {
    stack<int> help;
    help.push(index);
    this->visited[index] = true;

    while (!help.empty()) {
        int last = help.top();
        help.pop();
        BigCompHelp.push_back(last);

        for (int elem : this->adjacencyList[last]) {
            if (!visited[elem]) {
                visited[elem] = true;
                help.push(elem);
            }
        }
    }
}

vector<int> Graph::BFS(int elem, int numberOfNodes) {
    vector<int> dist(numberOfNodes, numberOfNodes);
    unordered_map<int, vector<int>> tabulka = this->gate;
    dist[elem] = 0;
    queue<int> q;
    q.push(elem);

    while (!q.empty()) {
        int first = q.front();
        q.pop();

        for (int element : tabulka[first]) {
            if (dist[element] > dist[first] + 1) {
                dist[element] = dist[first] + 1;
                q.push(element);
            }
        }
    }
    for (int i = 0; i < numberOfNodes; i++) {
        if (dist[i] == numberOfNodes) {
            dist[i] = 0;
        }
    }
    return dist;
}

void Graph::Centralita(vector<int> dist, int prvek, int numberOfNodes, int citatel) {
    int sum = 0;
    for (int i = 0; i < numberOfNodes; i++) {
        if (dist[i] != 0) {
            sum = sum + dist[i];
        }
    }
    float delenie = (float)citatel / sum;
    printf("%d\t%d/%d\t\t%f\n", prvek, citatel, sum, delenie);
}

int Graph::MoovDoTabulce(vector<int> BigComp) {
    for (int item : BigComp) {
        this->gate.emplace(item, this->adjacencyList[item]);
    }
    return this->gate.size();
}

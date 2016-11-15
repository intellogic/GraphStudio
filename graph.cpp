#include <graph.h>
#include <node.h>
#include <edge.h>
#include <QDebug>
#include <QTime>
#include <QMainWindow>
#include <windows.h>

Graph::Graph(){
}
Graph::Graph(int n){
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    for (int i = 0; i < n; i++){
        int x = qrand()%500+250, y = qrand()%500+250;
        Node *A = new Node(x, y, 1);
        ListOfNodes.push_back(A);
    }
    qsrand(midnight.secsTo(QTime::currentTime()));
    for (int i = 0; i < (n); i++){
        int x = qrand()%n, y = qrand()%n;
        while (x == y)
            x = qrand()%n, y = qrand()%n;
        //Edge *B = new Edge(x, y, 1);
        //ListOfEdges.append(B);
        //qDebug() << "EDGES" << ListOfEdges[ListOfEdges.size()-1]->NodeA << " "<< ListOfEdges[ListOfEdges.size()-1]->NodeB;
    }
}


bool Graph::FordBellman(Node *s, QMainWindow *Window){
    bool IfNegativeCycle = 1;
    for (int i = 0; i < ListOfNodes.size() - 1; i++){
        for (int j = 0; j < ListOfEdges.size(); j++){
            //ListOfEdges[j]->color = Qt::red;
            if (ListOfEdges[j]->NodeB->distance > ListOfEdges[j]->NodeA->distance + ListOfEdges[j]->weight && (ListOfEdges[j]->NodeB->distance + ListOfEdges[j]->NodeA->distance != 2000)){
                ListOfEdges[j]->NodeB->distance = ListOfEdges[j]->NodeA->distance + ListOfEdges[j]->weight;
                ListOfEdges[j]->NodeB->parent = ListOfEdges[j]->NodeA;

            }
           // Window->repaint();
           // Sleep(700);
           // ListOfEdges[j]->color = Qt::black;
        }
    }
    for (int i = 0; i < ListOfEdges.size(); i++)
        if (ListOfEdges[i]->NodeB->distance > ListOfEdges[i]->NodeA->distance + ListOfEdges[i]->weight)
            IfNegativeCycle = 0;
    return IfNegativeCycle;
}
void Graph::Dijkstra(Node *s, QMainWindow *Window, bool fast){
    QVector <Node *> Copy = ListOfNodes;
    //qDebug() << Copy.size();
    Heapify(Copy, Copy.size());
    for (int i = 0; i < ListOfNodes.size(); i++){
        Node *current = Copy[0];
        Copy.erase(Copy.begin());
        MaxHeapify(Copy, Copy.size(), 0);
        for (int j = 0; j < current->Adj.size(); j++)
            if (current->Adj[j].first->distance > current->Adj[j].second + current->distance){
                current->Adj[j].first->distance = current->Adj[j].second + current->distance;
                current->Adj[j].first->parent = current;
                Edge *currentEdge = 0;
                if (!fast){
                    for (int q = 0; q < ListOfEdges.size(); q++)
                        if (ListOfEdges[q]->NodeA == current & ListOfEdges[q]->NodeB == current->Adj[j].first)
                            currentEdge = ListOfEdges[q];
                    currentEdge->color = Qt::red;
                    Window->repaint();
                    Sleep(700);
                }
                for (int k = 0; k < Copy.size(); k++){
                    if (Copy[k] == current->Adj[j].first)
                    {
                        DecreaseKey(Copy, k);
                        break;
                    }
                }
                if (!fast) currentEdge->color = Qt::black;

            }
    }
}
void Graph::TopologicalOrder(){
    for (int i = 0; i < ListOfNodes.size(); i++)
        if (!ListOfNodes[i]->used)
            DFS(ListOfNodes[i]);
}
void Graph::DFS(Node *s){
    s->used = 1;
    for (int i = 0; i < s->Adj.size(); i++)
        if (!s->Adj[i].first->used){
            DFS(s->Adj[i].first);
    }
    TopOrder.insert(TopOrder.begin(), s);
}
void Graph::DAG_SP(){
    this->TopologicalOrder();
    //qDebug() << "TOP ORDER SIZE "<< TopOrder.size();
    for (int i = 0; i < TopOrder.size(); i++)
       // qDebug() << "CP " << i << " " << TopOrder[i]->distance;
    for (int i = 0; i < TopOrder.size(); i++){
        for (int j = 0; j < TopOrder[i]->Adj.size(); j++){
            if (TopOrder[i]->Adj[j].first->distance < TopOrder[i]->Adj[j].second + TopOrder[i]->distance){
                TopOrder[i]->Adj[j].first->distance = TopOrder[i]->Adj[j].second + TopOrder[i]->distance;
                TopOrder[i]->Adj[j].first->parent = TopOrder[i];
            }
        }
    }
}
void Graph::MaxHeapify(QVector <Node *> heap, long int n, long int i){
        long int left = 2*i + 1, right = 2*i + 2, min;
        if (left < n && heap[left]->distance < heap[i]->distance)
            min = 2*i+1; else min = i;
        if (right < n && heap[right]->distance < heap[min]->distance)
            min = 2*i + 2;
        if (min != i){
                std::swap(heap[i],heap[min]);
                MaxHeapify(heap, n, min);
        }
}
void Graph::Heapify(QVector <Node *> heap, long int n){
    for (long int i = ((n-1)/2-1); i >=0 ; i--){
       // qDebug() << i;
        MaxHeapify(heap, n, i);
    }
}
void Graph::DecreaseKey(QVector <Node *> heap, long int i){
    while (i >= 0 && heap[i/2]->distance > heap[i]->distance)
    {
        std::swap(heap[i/2], heap[i]);
        i = i/2;
    }
}

void Graph::Preprocessing(Node *Source, QMainWindow *Window, bool fast){
    for (int i = 0; i < ListOfNodes.size(); i++){
        ListOfNodes[i]->distance = 1000;
        ListOfNodes[i]->parent = 0;
    }
    Source->distance = 0;
    if (!fast){
        Window->repaint();
        Sleep(2000);
    }
}
void Graph::CPPreprocessing(Node *Source){
    for (int i = 0; i < ListOfNodes.size(); i++){
        ListOfNodes[i]->distance = -1000;
        ListOfNodes[i]->parent = 0;
    }
    Source->distance = 0;
}

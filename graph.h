#ifndef GRAPH
#define GRAPH
#include <edge.h>
#include <node.h>
#include <QVector>
#include <QGraphicsItem>
#include <QMainWindow>

class Graph{

public:
    QVector <Edge *> ListOfEdges;
    QVector <Node *> ListOfNodes;
    QVector <Node *> TopOrder;
    Graph();
    Graph(int n);
    void Preprocessing(Node *Source, QMainWindow *Window, bool fast);
    bool FordBellman(Node *s, QMainWindow *Window);
    void Dijkstra(Node *s, QMainWindow *Window, bool fast);
    void TopologicalOrder();
    void DFS(Node *s);
    void DAG_SP();
    void MaxHeapify(QVector <Node *>, long int n, long int i);
    void Heapify(QVector <Node *>, long int n);
    void DecreaseKey(QVector <Node *>, long int i);
    void CPPreprocessing(Node *s);



};

#endif // GRAPH


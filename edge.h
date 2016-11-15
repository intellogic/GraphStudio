#ifndef EDGE
#define EDGE
#include <QGraphicsItem>
#include <QFont>
#include <node.h>
#include <math.h>
#define PI 3.14159265358979323846264338327950288419717

class Edge {
public:
    Node *NodeA;
    Node *NodeB;
    QColor color;
    int weight;

    Edge();
    Edge(Node *NodeA, Node *NodeB, int color);

    void paint(QPainter *painter, bool iftree, bool Directed, bool planaritytest);
};

#endif // EDGE


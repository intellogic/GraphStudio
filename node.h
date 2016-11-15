#ifndef NODE
#define NODE
#include <QGraphicsItem>
#include <QPainter>
class Node{
public:
    int x;
    int y;
    int color;
    int distance;
    Node *parent;
    int number;
    bool used = 0;

    Node();
    Node (int x, int y, int color);
    QVector <QPair < Node *, int> > Adj;
    void paint(QPainter *painter, int i);
};

#endif // NODE


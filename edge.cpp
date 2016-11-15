#include <edge.h>
#include <QDebug>
Edge::Edge(Node* NodeA, Node* NodeB, int color){
    this->NodeA = NodeA;
    this->NodeB = NodeB;
    this->color = color;
}

Edge::Edge(){
}

void Edge::paint(QPainter *painter, bool iftree, bool Directed, bool planaritytest){
    QFont Font;
    Font.setPointSize(10);
    Node *x = this->NodeA, *y = this->NodeB;
    int w = 1;
    if (iftree)
        w = 4;
    painter->setPen(QPen(color, w));
    painter->drawLine(QPoint(x->x, x->y),QPoint(y->x, y->y));
    QString str;
    str.setNum(this->weight);
    painter->setFont(Font);
    //qDebug() << planaritytest;
    if (!planaritytest) painter->drawText(QPoint((x->x + y->x)/2,(x->y + y->y)/2 - 10),str);
    double angle = atan2((y->y - x->y),(y->x - x->x));
    //painter->setPen(QPen(Qt::black, w, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(QBrush(Qt::black));
    if (Directed){
        QPoint P1(y->x - 15*cos(angle), y->y - 15*sin(angle));
        QPoint P2(P1.x() - 9*cos(angle - PI/6), P1.y() - 9*sin(angle - PI/6));
        QPoint P3(P1.x() - 9*cos(angle + PI/6), P1.y() - 9*sin(angle + PI/6));
        painter->drawPolygon(QPolygonF() << P1 << P2 << P3);
    }
}

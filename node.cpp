#include <node.h>
Node::Node(int x, int y, int color){
    this->x = x;
    this->y = y;
    this->color = color;
    this->distance = 0;
    this->parent = 0;
}
Node::Node(){

}
void Node::paint(QPainter *painter, int i){
    QFont Font;
    Font.setPointSize(10);
    painter->drawEllipse(QPoint(this->x, this->y), 15, 15);
    QString str;
    str.setNum(i);
    painter->setFont(Font);
    painter->drawText(QRect(QPoint(this->x - 15, this->y - 15),
                     QPoint(this->x + 15, this->y + 15)), Qt::AlignCenter, str);
}


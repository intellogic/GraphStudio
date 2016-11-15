#include "graphwidget.h"
#include "edge.h"
#include <QDebug>
#include "node.h"

#include <math.h>

#include <QKeyEvent>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));
    scene->addEllipse(200, 200, 200, 200);
    qDebug() << "WIDGET";
    scene->addItem(new Node(50,50,0));
}

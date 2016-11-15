#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QDebug>
#include <QString>
#include <algorithm>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    A = new Graph();
    QFont Font;
    Font.setPointSize(14);
    ui->label->setFont(Font);

}
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){
    for (int i = 0; i < A->ListOfNodes.size(); i++){
        double Dist = sqrt((event->x() - A->ListOfNodes[i]->x)*(event->x() - A->ListOfNodes[i]->x)+(event->y() - A->ListOfNodes[i]->y)*(event->y() - A->ListOfNodes[i]->y));
        //qDebug() << event->x() << " " << event->y() << " " <<  A->ListOfNodes[i]->x << " " <<  A->ListOfNodes[i]->y << " " << Dist;
        if (Dist < 20){
            A->ListOfNodes.erase(A->ListOfNodes.begin() + i);
            this->repaint();
            break;
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    current = -1;
    ifRelease = 0;
    for (int i = 0; i < A->ListOfNodes.size(); i++){
        double Dist = sqrt((event->x() - A->ListOfNodes[i]->x)*(event->x() - A->ListOfNodes[i]->x)+(event->y() - A->ListOfNodes[i]->y)*(event->y() - A->ListOfNodes[i]->y));
        if (Dist < 20){
            current = i;
            break;
        }
    }
    if (current < 0 && Field->contains(QPoint(event->x(), event->y()))) {
        Node *q = new Node(event->x(), event->y(), 1);
        q->number = A->ListOfNodes.size();
        A->ListOfNodes.push_back(q);
    }
    this->repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    ifMove = 1;
    if (!ifRelease  && current >=0 ){
        A->ListOfNodes[current]->x = event->x();
        A->ListOfNodes[current]->y = event->y();
    }
    this->update();

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    ifRelease = 1;
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);
    painter.setClipRegion(QRegion(20,20,1236,801),Qt::ReplaceClip);
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.setPen(QPen(Qt::black,1));
    painter.drawRect(QRect(20,20,1235,800));
    painter.fillRect(QRect(21,21,1234,799),QBrush(Qt::white,Qt::SolidPattern));
    painter.setRenderHint(QPainter::Antialiasing);
    if (A->ListOfEdges.size() == 0){
        painter.setPen(QPen(Qt::black, 0));
        painter.setBrush(QBrush(Qt::white));
        for (int i = 0; i <  A->ListOfNodes.size(); i++){
            A->ListOfNodes[i]->paint(&painter, i);
        }
        painter.end();
    } else {
        if (FordBellmanProcessingDone || DijkstraProcessingDone){
            for (int i = 0; i < A->ListOfNodes.size(); i++){
                if (A->ListOfNodes[i]->parent != 0){
                     for (int j = 0; j < A->ListOfEdges.size(); j++){
                         if (A->ListOfEdges[j]->NodeA == A->ListOfNodes[i]->parent && A->ListOfEdges[j]->NodeB == A->ListOfNodes[i]) {
                             A->ListOfEdges[j]->color = Qt::black;
                             A->ListOfEdges[j]->paint(&painter, 1, IfDirected, PlanarityTest);
                         }
                     }
                }
            }
        }
        if (ShortestPathProcessingDone)
            if (A->ListOfNodes[ShortestPathFinish]->distance != 1000){
                Node *i = A->ListOfNodes[ShortestPathFinish];
                while (i->parent!= 0){
                    for (int j = 0; j < A->ListOfEdges.size(); j++){
                        if (A->ListOfEdges[j]->NodeA == i->parent && A->ListOfEdges[j]->NodeB == i) {
                            A->ListOfEdges[j]->color = Qt::green;
                            A->ListOfEdges[j]->paint(&painter, 1, IfDirected, PlanarityTest);
                            A->ListOfEdges[j]->color = Qt::black;
                            i = A->ListOfEdges[j]->NodeA;
                            break;
                        }
                    }
                }
                ShortestPathProcessingDone = 0;
                QString distance;
                distance.setNum(A->ListOfNodes[ShortestPathFinish]->distance);
                ui->label->setText(">> Path weight is " + distance);
        }
            else
                ui->label->setText(">> No path");
        if (CriticalPathProcessingDone){
                //qDebug() << "OK";
                Node *i = A->ListOfNodes[CriticalPathFinish];
                while (i->parent!= 0){
                    for (int j = 0; j < A->ListOfEdges.size(); j++){
                        if (A->ListOfEdges[j]->NodeA == i->parent && A->ListOfEdges[j]->NodeB == i) {
                            A->ListOfEdges[j]->color = Qt::magenta;
                            A->ListOfEdges[j]->paint(&painter, 1, IfDirected, PlanarityTest);
                            A->ListOfEdges[j]->color = Qt::black;
                            i = A->ListOfEdges[j]->NodeA;
                            break;
                        }
                    }
                }
                CriticalPathProcessingDone = 0;
                QString distance;
                distance.setNum(A->ListOfNodes[CriticalPathFinish]->distance);
                ui->label->setText(">> Critical path weight is " + distance);
        }
        for (int i = 0; i < A->ListOfEdges.size(); i++){
            A->ListOfEdges[i]->paint(&painter, 0, IfDirected, PlanarityTest);
        }
        painter.setBrush(QBrush(Qt::white));
        painter.setPen(QPen(Qt::black, 0));
        for (int i = 0; i <  A->ListOfNodes.size(); i++){
           A->ListOfNodes[i]->paint(&painter, i);
           QString str;
           if (FordBellmanProcessing || DijkstraProcessing|| FordBellmanProcessingDone || DijkstraProcessingDone || IfDAGSP){
               QFont Font;
               Font.setPointSize(10);
               painter.setFont(Font);
               if (A->ListOfNodes[i]->distance == 1000)
                   str = "∞";
               else
                   str.setNum(A->ListOfNodes[i]->distance);
               painter.drawText(QRect(QPoint(A->ListOfNodes[i]->x + 5, (A->ListOfNodes[i]->y + 5)),
                                QPoint(A->ListOfNodes[i]->x + 30, (A->ListOfNodes[i]->y + 20))), Qt::AlignCenter, str);

           }
        }
        painter.end();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{   NegativeCycleExist = 0;
    QStringList List = ui->textEdit->toPlainText().split('\n');
    A->ListOfEdges.erase(A->ListOfEdges.begin(), A->ListOfEdges.end());
    for (int i = 0; i < A->ListOfNodes.size(); i++){
        A->ListOfNodes[i]->Adj.erase(A->ListOfNodes[i]->Adj.begin(), A->ListOfNodes[i]->Adj.end());
    }
    for (int i = 0; i < List.size(); i++){
        if (List[i].size() >=3) {
            QStringList SubList = List[i].split(' ');
            if (SubList.size() == 3){
                bool ok1, ok2, ok3;
                int a = SubList[0].toInt(&ok1, 10);
                int b = SubList[1].toInt(&ok2, 10);
                int c = SubList[2].toInt(&ok3, 10);
                bool ifEx = 0;

                if (ok1 && ok2 && ok3 && a < A->ListOfNodes.size() && b < A->ListOfNodes.size()){
                    Edge *NewEdge = new Edge(A->ListOfNodes[a], A->ListOfNodes[b], 0);
                    NewEdge->weight = c;
                    if (c < 0)
                        NegativeCycleExist = 1;
                    NewEdge->color = Qt::black;
                    for (int j = 0; j < A->ListOfEdges.size(); j++)
                        if (A->ListOfEdges[j]->NodeA == A->ListOfNodes[a] && A->ListOfEdges[j]->NodeB == A->ListOfNodes[b])
                            ifEx = 1;
                    if (!ifEx){
                        A->ListOfEdges.append(NewEdge);
                        A->ListOfNodes[a]->Adj.push_back(QPair <Node *, int>(A->ListOfNodes[b], c));

                    }
                }


            }
        }
    }
    this->repaint();
}

void MainWindow::on_radioButtonDirected_clicked()
{
    IfDirected = 1;
    this->repaint();
}

void MainWindow::on_radioButtonNonDirected_clicked()
{
    IfDirected = 0;
    this->repaint();
}
void MainWindow::on_FordBellmanButton_clicked()
{
    FordBellmanProcessing = 1;
    ui->label->setText(">> Ford-Bellman Algorithm Processing");
    QString SourceNode = ui->SorceNode->text();
    bool ok, processing;
    int SN = SourceNode.toInt(&ok, 10);
    if (ok && SN < A->ListOfNodes.size()){
        A->Preprocessing(A->ListOfNodes[SN],this, 1);
        processing = A->FordBellman(A->ListOfNodes[SN], this);
        this->repaint();
    }
    if (processing){
    FordBellmanProcessing = 0;
    FordBellmanProcessingDone = 1;

    ui->label->setText(">> Ford-Bellman algorithm've been done");
    }
    else{
        FordBellmanProcessing = 0;
        FordBellmanProcessingDone = 0;
        ui->label->setText(">> Graph can't have negative cycles");
        this->repaint();
    }

}

void MainWindow::on_RefreshButton_clicked()
{
    FordBellmanProcessingDone = 0;
    DijkstraProcessingDone = 0;
    ShortestPathProcessingDone = 0;
    PlanarityTest = 0;
    ui->label->setText(">> ");
    this->repaint();
}

void MainWindow::on_DijkstraButton_clicked()
{   if (!NegativeCycleExist){
        DijkstraProcessing = 1;
        ui->label->setText(">> Dijkstra algorithm processing");
        QString SourceNode = ui->SorceNode->text();
        bool ok;
        int SN = SourceNode.toInt(&ok, 10);
        if (ok && SN < A->ListOfNodes.size()){
            A->Preprocessing(A->ListOfNodes[SN],this, 1);
            A->Dijkstra(A->ListOfNodes[SN], this, 1);
            this->repaint();
        }
        //qDebug() << "DijkstraDone";
        DijkstraProcessing = 0;
        DijkstraProcessingDone = 1;
        this->repaint();
        ui->label->setText(">> Dijkstra algorithm've been done");
    } else {
        ui->label->setText(">> Graph can't have negative edges");
    }
}

void MainWindow::on_ShortestPath_clicked()
{
    if (!NegativeCycleExist){
        QString SPSt = ui->SPSource->text();
        QString SPFin = ui->SPFinish->text();
        bool ok1, ok2;
        int SPs = SPSt.toInt(&ok1, 10);
        int SPf = SPFin.toInt(&ok2, 10);
        if (ok1 && ok2 && SPs < A->ListOfNodes.size() && SPf < A->ListOfNodes.size()){
            ShortestPathFinish = SPf;
            A->Preprocessing(A->ListOfNodes[SPs], this, 1);
            A->Dijkstra(A->ListOfNodes[SPs], this, 1);
            ShortestPathProcessingDone = 1;
        }
        this->repaint();
    } else {
        ui->label->setText(">> Graph can't have negative edges");
    }
}

void MainWindow::on_ShowCriticalPathButton_clicked()
{   if (!NegativeCycleExist){
        CriticalPathFinish = -1;
        int CPS = -1;
        for (int i = 0; i < A->ListOfNodes.size(); i++){
            if (A->ListOfNodes[i]->Adj.size() == 0)
                CriticalPathFinish = i;
            for(int j = 0; j < A->ListOfNodes[i]->Adj.size(); j++)
                A->ListOfNodes[i]->Adj[j].first->used = 1;
        }

        for (int i = 0; i < A->ListOfNodes.size(); i++){
            if (!A->ListOfNodes[i]->used)
               CPS = i;
        }
        for (int i = 0; i < A->ListOfNodes.size(); i++)
            A->ListOfNodes[i]->used = 0;
            if (CPS >= 0 && CriticalPathFinish >= 0){
            //qDebug() << "CM "<< CPS << " " << CriticalPathFinish;
            A->CPPreprocessing(A->ListOfNodes[CPS]);
            A->DAG_SP();
            CriticalPathProcessingDone = 1;
            //qDebug() << "CPP DONE";
            A->TopOrder.erase(A->TopOrder.begin(), A->TopOrder.end());
            this->repaint();
        } else {
                ui->label->setText(">> This graph doesn't look like PERT diagram");
            }
    } else {
        ui->label->setText(">> Graph can't have negative edges");
    }
}

void MainWindow::on_pushButton_clicked()
{
    int n = A->ListOfNodes.size();

    int **D = new int *[n];
    for (int i = 0; i < n; i++)
        D[i] = new int [n];
    int **P = new int *[n];
    for (int i = 0; i < n; i++)
        P[i] = new int [n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            if (j == i)
                D[i][j] = 0;
            else
            D[i][j] = 1000;
            P[i][j] = -1;
    }
    for (int i = 0; i < A->ListOfEdges.size(); i++){
        D[A->ListOfEdges[i]->NodeA->number][A->ListOfEdges[i]->NodeB->number] = A->ListOfEdges[i]->weight;
        P[A->ListOfEdges[i]->NodeA->number][A->ListOfEdges[i]->NodeB->number] = A->ListOfEdges[i]->NodeA->number;
    }

    for (int k = 0; k  < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (D[i][j] <= D[i][k] + D[k][j])
                    P[i][j] = P[i][j];
                else
                    P[i][j] = P[k][j];
                if (D[i][k] != 1000 && D[k][j] != 1000)
                    D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
            }
        }

    }
    FloydWarshall *q = new FloydWarshall;
    q->DrawWeightsMatrix(D, n);
    q->DrawPathsMatrix(P, n);
    q->show();

}

void MainWindow::on_ClearButton_clicked()
{
    A->ListOfEdges.clear();
    A->ListOfNodes.clear();
    ui->textEdit->clear();
    ui->label->setText(">> ");
    FordBellmanProcessing = 0;
    FordBellmanProcessingDone = 0;
    DijkstraProcessing = 0;
    DijkstraProcessingDone = 0;
    ShortestPathProcessingDone = 0;
    CriticalPathProcessingDone = 0;
    IfDAGSP = 0;
    IfDirected = 1;
}

void MainWindow::on_PlanarityTestButton_clicked()
{   PlanarityTest = 1;
    if (A->ListOfEdges.size() > 3*A->ListOfNodes.size() - 6)
        ui->label->setText(">> Graph isn't planar");
    else
         ui->label->setText(">> Graph is planar");
    this->repaint();
}

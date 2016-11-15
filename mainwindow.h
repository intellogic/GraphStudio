#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets>
#include <QtGui>
#include <QVector>
#include <graph.h>
#include <floydwarshall.h>
#include <QGraphicsItem>
#include <graphwidget.h>
#define PI 3.14159265358979323846264338327950288419717
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int current;
    GraphWidget *Q;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    Graph *A;
    int x1, y1;
    bool k = 0;
    bool ifMove;
    bool ifRelease = 0;
    QVector <int> Transform;
    QRect *Field = new QRect(20, 20, 1235, 800);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    bool FordBellmanProcessing = 0;
    bool FordBellmanProcessingDone = 0;
    bool DijkstraProcessing = 0;
    bool DijkstraProcessingDone = 0;
    bool ShortestPathProcessingDone = 0;
    bool CriticalPathProcessingDone = 0;
    bool PlanarityTest = 0;
    bool IfDAGSP = 0;
    bool IfDirected = 1;
    bool NegativeCycleExist;
    int ShortestPathFinish;
    int CriticalPathFinish;


private slots:
    void on_textEdit_textChanged();
    void on_radioButtonDirected_clicked();
    void on_radioButtonNonDirected_clicked();
    void on_FordBellmanButton_clicked();

    void on_RefreshButton_clicked();

    void on_DijkstraButton_clicked();

    void on_ShortestPath_clicked();

    void on_ShowCriticalPathButton_clicked();

    void on_pushButton_clicked();

    void on_ClearButton_clicked();

    void on_pushButton_2_clicked();

    void on_PlanarityTestButton_clicked();

public:
    void on_plainTextEdit_textChanged();

private:
    Ui::MainWindow *ui;\

};

#endif // MAINWINDOW_H

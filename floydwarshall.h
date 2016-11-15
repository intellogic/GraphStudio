#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include <QWidget>

namespace Ui {
class FloydWarshall;
}

class FloydWarshall : public QWidget
{
    Q_OBJECT

public:
    explicit FloydWarshall(QWidget *parent = 0);
    ~FloydWarshall();
    void DrawWeightsMatrix(int **D, int n);
    void DrawPathsMatrix(int **P, int n);

private:
    Ui::FloydWarshall *ui;
};

#endif // FLOYDWARSHALL_H

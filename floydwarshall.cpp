#include "floydwarshall.h"
#include "ui_floydwarshall.h"

FloydWarshall::FloydWarshall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloydWarshall)
{
    ui->setupUi(this);
}

FloydWarshall::~FloydWarshall()
{
    delete ui;
}
void FloydWarshall::DrawWeightsMatrix(int **D, int n){
    QString Text;
    QString space = " ";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            QString W;
            if (D[i][j] == 1000)
                W = "∞";
            else
                W.setNum(D[i][j]);
            Text += W + ' ';
        }
        Text += '\n';
    }
    ui->WeightsMatrix->setText(Text);
}
void FloydWarshall::DrawPathsMatrix(int **D, int n){
    QString Text;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            QString W;
            if (D[i][j] == 1000)
                W = "∞";
            else
                W.setNum(D[i][j]);
            Text += W + ' ';
        }
        Text += '\n';
    }
    ui->PathsMatrix->setText(Text);
}

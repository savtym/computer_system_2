#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateA_clicked()
{
    matrixA = IntMatrix(ui->rowsA->value(), ui->columnsA->value());
    matrixA.RandomMatrixGeneration();

    if(matrixA.GetRowCount() < 500 && matrixA.GetColCount() < 500){
        ui->matrixAView->setText(QString::fromStdString(matrixA.ToString()));
    }else{
        ui->matrixAView->setText("Матриця завелика для відображення!");
    }
}

void MainWindow::on_clearA_clicked()
{
    matrixA.Clear();
    ui->rowsA->setValue(matrixA.GetRowCount());
    ui->columnsA->setValue(matrixA.GetColCount());
    ui->matrixAView->setText(QString::fromStdString(matrixA.ToString()));
}

void MainWindow::on_generateB_clicked()
{
    matrixB = IntMatrix(ui->rowsB->value(), ui->columnsB->value());
    matrixB.RandomMatrixGeneration();

    if(matrixB.GetRowCount() < 500 && matrixB.GetColCount() < 500){
        ui->matrixBView->setText(QString::fromStdString(matrixB.ToString()));
    }else{
        ui->matrixBView->setText("Матриця завелика для відображення!");
    }
}

void MainWindow::on_clearB_clicked()
{
    matrixB.Clear();
    ui->rowsB->setValue(matrixB.GetRowCount());
    ui->columnsB->setValue(matrixB.GetColCount());
    ui->matrixBView->setText(QString::fromStdString(matrixB.ToString()));
}

void MainWindow::on_start_clicked()
{

    switch(taskType)
        case Addition:{
            matrixC1 = singleUnitSystem.Add(matrixA, matrixB);
            matrixC2 = unitsWithLocalMemory.Add(matrixA, matrixB);
            matrixC3 = unitsWithSharedMemory.Add(matrixA, matrixB);
            break;

        case Multiplication:
            matrixC1 = singleUnitSystem.Multiplicate(matrixA, matrixB);
            matrixC2 = unitsWithLocalMemory.Multiplicate(matrixA, matrixB);
            matrixC3 = unitsWithSharedMemory.Multiplicate(matrixA, matrixB);
            break;

        case Transposition:
            matrixC1 = singleUnitSystem.Transpose(matrixA);
            matrixC2 = unitsWithLocalMemory.Transpose(matrixA);
            matrixC3 = unitsWithSharedMemory.Transpose(matrixA);
            break;
    }


    ui->singleTime->setText(QString("%1").arg(singleUnitSystem.time.getTime()));
    ui->localTime->setText(QString("%1").arg(singleUnitSystem.time.getTime()/(float)unitsWithLocalMemory.time.getTime()));
    ui->sharedTime->setText(QString("%1").arg(singleUnitSystem.time.getTime()/(float)unitsWithSharedMemory.time.getTime()));


    ui->localTime_2->setText(QString("%1").arg(singleUnitSystem.time.getTime()/(float)(unitsWithLocalMemory.time.getTime() * countOfUnits)));
    ui->sharedTime_2->setText(QString("%1").arg(singleUnitSystem.time.getTime()/(float)(unitsWithSharedMemory.time.getTime() * countOfUnits)));

    if(matrixC1.GetRowCount() < 500 && matrixC1.GetColCount() < 500){
        ui->matrixCView->setText(QString::fromStdString(matrixC1.ToString()));
    }else{
        ui->matrixCView->setText("Матриця завелика для відображення!");
    }

}

void MainWindow::on_clearC_clicked()
{
    matrixC1.Clear();
    ui->rowsC->setText(QString::fromStdString(to_string(matrixC1.GetRowCount())));
    ui->columnsC->setText(QString::fromStdString(to_string(matrixC1.GetColCount())));
    ui->matrixCView->setText(QString::fromStdString(matrixC1.ToString()));
}

void MainWindow::on_addition_toggled(bool checked)
{
    if(checked){
        taskType = Addition;
    }
}

void MainWindow::on_multiplication_toggled(bool checked)
{
    if(checked){
        taskType = Multiplication;
    }
}

void MainWindow::on_transposition_toggled(bool checked)
{
    if(checked){
        taskType = Transposition;
    }
}


void MainWindow::on_ticksPerAddition_valueChanged(int arg1)
{
    countOfUnits = arg1;
    unitsWithLocalMemory.SetCountOfUnits(arg1);
    unitsWithSharedMemory.SetCountOfUnits(arg1);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    scene = new QGraphicsScene();
    scene->setSceneRect(-600/2,-600/2,600,600);
    ui->graphicsView->setScene(scene);
    connect(timer, SIGNAL(timeout()),this,SLOT(Actualizar()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_Agregar_clicked()
{
    double pX, pY, velX, velY, m, r;

    pX = ui->le_posX->text().toDouble();
    pY = ui->le_posY->text().toDouble();
    velX = ui->le_velX->text().toDouble();
    velY = ui->lbl_velY->text().toDouble();
    m = ui->le_masa->text().toDouble();
    r = ui->le_radio->text().toDouble();
    cuerpos.push_back(new cuerpo(pX, pY, m, r, velX, velY));
    scene->addItem(cuerpos.back());

    ui->label->setText("Se agrego");
}

void MainWindow::on_btn_simular_clicked()
{
    timer->start(10);
}

void MainWindow::Actualizar()
{
    //actualizar los metodos para cada cuerpo
    for(const auto& itP : cuerpos)
    {
        double AFx = 0, AFy = 0;
        for(const auto& itO : cuerpos)
        {
            if(itP != itO)
            {
                itP->A(itO->getPX(), itO->getPY());
                itP->CalA(itO->getM(), itO->getPX(), itO->getPY());
                AFx += itP->getAX();
                AFy += itP->getAY();
            }
        }
        itP->setAX(AFx);
        itP->setAY(AFy);
        itP->CalVel();
        itP->CalP();
    }
}

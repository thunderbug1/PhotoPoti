#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::DrawMillimeterRaster(int gradientOffsetY, int gradientwidth, int gradientOffsetX, float PixelProMillimeter, int gradientheigth, int sideRectWidth)
{
    int linelenght = 0;
    int mill = 0;
    QGraphicsTextItem *number;
    bool addNumber = false;

    while(mill < (int)(gradientwidth / PixelProMillimeter))
    {
        if(mill%10 == 0)
        {
           linelenght = 8;
           addNumber = true;
        }
        else if(mill%2 == 0)
        {
           linelenght = 2;
        }
        else if(mill%5 == 0)
        {
           linelenght = 5;
        }
        else
        {
           linelenght = 3;
        }
        float xval = gradientOffsetX+mill*PixelProMillimeter+sideRectWidth;
        float y1val = gradientOffsetY+gradientheigth;
        float y2val = gradientOffsetY+gradientheigth+linelenght*PixelProMillimeter;
        scene->addLine(xval,y1val,xval,y2val);
        if(addNumber)
        {
            number = new QGraphicsTextItem;
            number->setPlainText(QString::number(mill/10));
            number->setPos(xval-10,y2val + 10);
            scene->addItem(number);
            addNumber = false;
        }
        mill++;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    width = 1131;
    heigth = width /1.414213562;

    float PixelProMillimeter = 4.222181091;
    qDebug()<<QString("PixelProMillimeter: ")<<QString::number(PixelProMillimeter);

    int gradientwidth = width - 150;
    int gradientheigth = 40;

    int gradientOffsetX = 50;
    int gradientOffsetY = 20;

    int sideRectWidth = 30;

    //The linear Gradient
     QLinearGradient linearGrad(QPointF(0, 0), QPointF(gradientwidth, 0));
     linearGrad.setColorAt(0.05, Qt::black);
     int colorval = 28;
     linearGrad.setColorAt(1, QColor(colorval,colorval,colorval,255));

     //ui->graphicsView->setFixedSize(2970,2100);
     ui->graphicsView->setFixedSize(width+20,heigth+20);
     ui->graphicsView->setSceneRect(0,0,width,heigth);
     //scene->addRect(0,0,1326,962,QPen(Qt::white));
     scene->addRect(gradientOffsetX+sideRectWidth,gradientOffsetY,gradientwidth,gradientheigth, QPen(Qt::transparent), QBrush(linearGrad));
     scene->addRect(gradientOffsetX,gradientOffsetY,sideRectWidth,gradientheigth, QPen(Qt::transparent), QBrush(Qt::black));
     scene->addRect(0,0,width,heigth,QPen(Qt::transparent));

     //millimeter grid
     DrawMillimeterRaster(gradientOffsetY, gradientwidth, gradientOffsetX, PixelProMillimeter, gradientheigth, sideRectWidth);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PrintScene()
{
    QPrinter printer(QPrinter::HighResolution);
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
       // Configure a painter with local coordinate system in millimeter based on an A4 landscape page
        QPainter painter(&printer);
        printer.setOrientation(QPrinter::Landscape);
        printer.setPaperSize(QPrinter::A4);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
           //painter.begin(*printer);
            int aLogicalWidth  = width;
            int aLogicalHeight = heigth;
            int aPhysicalWidth  = printer.width();
            int aPhysicalHeight = printer.height();
            painter.setWindow(0, 0, aPhysicalWidth, aPhysicalHeight);
            //painter.setViewport(0, 0, aLogicalWidth, aLogicalHeight);
        scene->render(&painter);
    }
}

void MainWindow::on_printButton_clicked()
{
    PrintScene();
}

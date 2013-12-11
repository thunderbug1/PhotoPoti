#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/qprintdialog.h>
#include <QtPrintSupport/qprinter.h>
#include <QGraphicsScene>
#include<QGraphicsView>
#include<QPainter>
#include <QGradient>
#include <QGraphicsView>
#include <QtCore>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QDebug.h>

#include <Defines.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DrawMillimeterRaster(int gradientOffsetY, int gradientwidth, int gradientOffsetX, float PixelProMillimeter, int gradientheigth, int sideRectWidth);
    void PrintScene();
private slots:
    void on_printButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    int width;
    int heigth;
};

#endif // MAINWINDOW_H

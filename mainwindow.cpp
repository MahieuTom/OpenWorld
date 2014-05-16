#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("OpenWorld · OpenGL project");
    resize(640, 480);
    initView();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initView()
{
    //view=new PlanetsView(this);
    //setCentralWidget(view);
}

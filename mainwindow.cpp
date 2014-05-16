#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("OpenWorld · OpenGL project");
    resize(640, 480);
    initView();
}

//-------------------------------------------------------------

MainWindow::~MainWindow()
{
}

//-------------------------------------------------------------

void MainWindow::initView()
{
    view = new View(this);
    setCentralWidget(view);
}

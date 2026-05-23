#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Screen Recorder");
    this->resize(300,100);

    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // Some kinda title - don't know why!
    titleLabel = new QLabel("Screen Recorder");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 22px; color: white");
    mainLayout->addWidget(titleLabel);

    // Record Button in layout
    recordButton = new QPushButton("Record");
    recordButton->setStyleSheet("font-size: 16px; color:white; background-color: green");
    mainLayout->addWidget(recordButton);

    // Sets centralWidget as the mainWindow's central widget - if that makes sense! LMAO!
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

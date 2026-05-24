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
    QString buttonLabel = "Record";
    recordButton = new QPushButton(buttonLabel);
    recordButton->setStyleSheet("font-size: 16px; color:white; background-color: green");
    mainLayout->addWidget(recordButton);

    // Record functionality
    connect(recordButton, &QPushButton::clicked, this, [&](){
        if(recordButton->text() == "Record") {
            outputFilePath = QFileDialog::getSaveFileName(this, "Save Recording","","Video Files (*.mp4 *.wav)");
            if(!outputFilePath.isEmpty()) {
                startRecording(recordProcess, recordButton, outputFilePath, this);
            }
        }
        //else {
          //  stopRecording(recordProcess, recordButton, outputFilePath, this);
        //}
    });

    // Sets centralWidget as the mainWindow's central widget - if that makes sense! LMAO!
    setCentralWidget(centralWidget);
}

void MainWindow::startRecording(QProcess &recordProcess, QPushButton *recordButton, QString &outputFilePath, QWidget *mainWindow) {
    recordButton->setText("Stop");
    recordButton->setStyleSheet("font-size:16px; color:white; background-color:red");

    QString command = ffmpeg;

    QStringList arguments;

    arguments << "-y"
              << "-f" << "gdigrab"
              << "-i" << "desktop"
              << "-f" << "dshow"
              << "-i" << "audio=Microphone Array (Realtek(R) Audio)"
              << "-c:v" << "libx264"
              << "preset" << "ultrafast"
              << "-c:a" << "aac"
              << "-pix_fmt" << "yuv420p"
              << outputFilePath;

    recordProcess.start(command, arguments);

    if(!recordProcess.waitForStarted()) {
        qDebug() << "Failed to start recording";
        recordButton->setText("Record");
        recordButton->setStyleSheet("font-size: 16px; color:white; background-color: green");

    } else {
        qDebug() << "Recording Started...";
        this->showMinimized();
    }
}
//void stopRecording(QProcess &recordProcess, QPushButton *recordButton, const QString &outputFilePath, QWidget *mainWindow);

MainWindow::~MainWindow()
{
    delete ui;
}

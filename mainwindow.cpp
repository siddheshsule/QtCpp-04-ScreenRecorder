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
    setCentralWidget(centralWidget);

    // Record functionality
    connect(recordButton, &QPushButton::clicked, this, &MainWindow::toggleRecording);

    // Sets centralWidget as the mainWindow's central widget - if that makes sense! LMAO!
}

void MainWindow::startRecording()
{
    outputFilePath = QFileDialog::getSaveFileName(
        this,
        "Save Recording",
        "",
        "Video Files (*.mp4)"
        );

    if (outputFilePath.isEmpty()) {
        return;
    }

    QString program = ffmpeg;

    QStringList arguments;
    arguments << "-y"
              << "-f" << "gdigrab"
              << "-i" << "desktop"
              << "-f" << "dshow"
              << "-i" << "audio=Microphone Array (Realtek(R) Audio)"
              << "-c:v" << "libx264"
              << "-preset" << "ultrafast"
              << "-c:a" << "aac"
              << "-pix_fmt" << "yuv420p"
              << outputFilePath;

    recordProcess.start(program, arguments);

    if (!recordProcess.waitForStarted()) {
        QMessageBox::critical(this,
                              "Error",
                              "Failed to start recording.");

        return;
    }

    qDebug() << "Recording started...";

    recordButton->setText("Stop");
    recordButton->setStyleSheet(
        "font-size: 16px;"
        "color: white;"
        "background-color: red;"
        );

    showMinimized();
}

void MainWindow::stopRecording()
{
    if (recordProcess.state() == QProcess::Running) {
        recordProcess.write("q\n");
        recordProcess.waitForFinished();

        qDebug() << "Recording stopped. Saved to " << outputFilePath;
    }
    recordButton->setText("Record");
    recordButton->setStyleSheet(
        "font-size: 16px;"
        "color: white;"
        "background-color: green;"
        );
    showNormal();
}

void MainWindow::toggleRecording() {
    if(recordProcess.state() == QProcess::Running) {
        stopRecording();
    } else {
        startRecording();
    }
}
MainWindow::~MainWindow()
{
    if(recordProcess.state() == QProcess::Running) {
        stopRecording();
    }
    delete ui;
}

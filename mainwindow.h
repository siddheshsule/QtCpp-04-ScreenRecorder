#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QProcess>
#include<QFileDialog>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    const QString ffmpeg = "C:/Users/siddh/ffmpeg-8.1.1-essentials_build/bin/ffmpeg.exe";

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QWidget *centralWidget;
    QPushButton *recordButton;
    QProcess recordProcess;
    QString outputFilePath;

private slots:
    void startRecording();
    void stopRecording();
    void toggleRecording();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVBoxLayout>
#include<QLabel>
#include<QPushButton>

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
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QWidget *centralWidget;
    QPushButton *recordButton;

};
#endif // MAINWINDOW_H

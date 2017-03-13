#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QTabWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_actionUpdateCOMPortsList_triggered();
    void on_addTabButton_clicked();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QToolButton *addTabButton;
};

#endif // MAINWINDOW_H

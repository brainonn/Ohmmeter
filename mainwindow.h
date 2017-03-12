#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_buttonAction_clicked();
    void on_buttonRemote_clicked();
    void on_buttonScan_clicked();
    void on_buttonSave_clicked();
    void on_buttonZero_clicked();
    void on_comboBoxRate_currentIndexChanged(const QString &text);
    void on_comboBoxRange_currentIndexChanged(const QString &text);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

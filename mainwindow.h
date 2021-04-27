#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include<QtWidgets/QDialog>
#include<qfiledialog.h>
#include<qdialog.h>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *watched, QEvent *event);
    void Folder2ImgPrint(QVector<QString> *Folder2FileArr, int *suffledIdx, int iter);
    void Folder1ImgPrint(QVector<QString> *Folder1FileArr, int idx);
private slots:
    void on_pushButton_Folder1_clicked();

    void on_pushButton_Folder2_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_X_clicked();

    void on_pushButton_O_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// QT
#include <QMainWindow>
#include <QMouseEvent>
#include <QDebug>
#include <QtWidgets/QDialog>
#include <QFile>
#include <QTimer>
#include <qfiledialog.h>
#include <qdialog.h>
#include <qmessagebox.h>

// opencv
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

// cpp
#include <iostream>
#include <algorithm>


using namespace cv;
using namespace std;

// color component
struct lessVec3b
{
    bool operator()(const Vec3b& lhs, const Vec3b& rhs) const {
        return (lhs[0] != rhs[0]) ? (lhs[0] < rhs[0]) : ((lhs[1] != rhs[1]) ? (lhs[1] < rhs[1]) : (lhs[2] < rhs[2]));
    }
};

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
    int ColorExtract(QString filePath);
    void Folder2ImageColorClassification(QVector<QString> *Folder2FileArr);
    void initImageLabelBorder();

private slots:
    void on_pushButton_Folder1_clicked();
    void on_pushButton_Folder2_clicked();
    void on_pushButton_Start_clicked();
    void on_pushButton_X_clicked();
    void on_pushButton_O_clicked();
    void on_pushButton_Next_clicked();
    void OnTimerCallbackFunc();


private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H

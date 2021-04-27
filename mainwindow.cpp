#include "mainwindow.h"
#include "ui_mainwindow.h"

int _iter = 0;
int _curr_img = 0;
QVector<QString> Folder1FileArr;
QVector<QString> Folder2FileArr;
int Folder1FileCnt = 0;
int Folder2FileCnt = 0;
int *ShuffleIdx;
QString CurrFileName1;
QString CurrFileName2[10];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_img01->installEventFilter(this);
    ui->label_img02->installEventFilter(this);
    ui->label_img03->installEventFilter(this);
    ui->label_img04->installEventFilter(this);
    ui->label_img05->installEventFilter(this);
    ui->label_img06->installEventFilter(this);
    ui->label_img07->installEventFilter(this);
    ui->label_img08->installEventFilter(this);
    ui->label_img09->installEventFilter(this);
    ui->label_img10->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void ShufflingNumberTAOCP(int cnt, int *suffledIdx)
{
    for( int i=0; i < cnt; ++i )
        suffledIdx[i] = i+1;

    for( int i=0; i < cnt; ++i )
    {
        int dest =  rand() % cnt;

        int temp = suffledIdx[i];
        suffledIdx[i] = suffledIdx[dest];
        suffledIdx[dest] = temp;
    }
//    for(int i=0; i < cnt; ++i )
//        printf( "%d ", suffledIdx[i] );

    printf("\n");
}

void MainWindow::on_pushButton_Folder1_clicked()    // 폴더1 선택 및 경로 출력
{
    QString QFolderLocation = QFileDialog::getExistingDirectory(this, "select folder", QDir::homePath(), QFileDialog::ShowDirsOnly);
    ui->lineEdit_Folder1->setText(QFolderLocation);
}

void MainWindow::on_pushButton_Folder2_clicked()    // 폴더2 선택 및 결로 출력
{
    QString QFolderLocation = QFileDialog::getExistingDirectory(this, "select folder", QDir::homePath(), QFileDialog::ShowDirsOnly);
    ui->lineEdit_Folder2->setText(QFolderLocation);
}
bool MainWindow::eventFilter(QObject *watched, QEvent *event)   // 폴더2 이미지 선택시 굵게 표시
{
    if(watched == ui->label_img01 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img01->lineWidth() == 1)
            ui->label_img01->setLineWidth(4);
        else
            ui->label_img01->setLineWidth(1);
    }
    if(watched == ui->label_img02 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img02->lineWidth() == 1)
            ui->label_img02->setLineWidth(4);
        else
            ui->label_img02->setLineWidth(1);
    }
    if(watched == ui->label_img03 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img03->lineWidth() == 1)
            ui->label_img03->setLineWidth(4);
        else
            ui->label_img03->setLineWidth(1);
    }
    if(watched == ui->label_img04 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img04->lineWidth() == 1)
            ui->label_img04->setLineWidth(4);
        else
            ui->label_img04->setLineWidth(1);
    }
    if(watched == ui->label_img05 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img05->lineWidth() == 1)
            ui->label_img05->setLineWidth(4);
        else
            ui->label_img05->setLineWidth(1);
    }
    if(watched == ui->label_img06 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img06->lineWidth() == 1)
            ui->label_img06->setLineWidth(4);
        else
            ui->label_img06->setLineWidth(1);
    }
    if(watched == ui->label_img07 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img07->lineWidth() == 1)
            ui->label_img07->setLineWidth(4);
        else
            ui->label_img07->setLineWidth(1);
    }
    if(watched == ui->label_img08 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img08->lineWidth() == 1)
            ui->label_img08->setLineWidth(4);
        else
            ui->label_img08->setLineWidth(1);
    }
    if(watched == ui->label_img09 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img09->lineWidth() == 1)
            ui->label_img09->setLineWidth(4);
        else
            ui->label_img09->setLineWidth(1);
    }
    if(watched == ui->label_img10 && event->type() == QMouseEvent::MouseButtonPress)
    {
        if (ui->label_img10->lineWidth() == 1)
            ui->label_img10->setLineWidth(4);
        else
            ui->label_img10->setLineWidth(1);
    }
    return QWidget::eventFilter(watched, event);
}

// START 버튼
void MainWindow::on_pushButton_Start_clicked()  // 작업 시작
{
    // init
    _curr_img = 0;
    _iter = 0;
    Folder1FileArr.clear();
    Folder2FileArr.clear();
    free(ShuffleIdx);

    // 폴더 1 파일 목록 읽기
    QDir Folder1Dir(ui->lineEdit_Folder1->text());
    foreach(QFileInfo item, Folder1Dir.entryInfoList())
    {
        if (item.isFile()) // 아이템이 파일인 경우 파일 경로 벡터에 푸쉬
            Folder1FileArr.push_back(item.absoluteFilePath());
    }
    Folder1FileCnt = Folder1FileArr.length();

    // 폴더 2 파일 목록 읽기
    QDir Folder2Dir(ui->lineEdit_Folder2->text());
    foreach(QFileInfo item, Folder2Dir.entryInfoList())
    {
        if (item.isFile()) // 아이템이 파일인 경우 파suffledIdx일 경로 벡터에 푸쉬
            Folder2FileArr.push_back(item.absoluteFilePath());
    }
    Folder2FileCnt = Folder2FileArr.length();

    // 폴더 2 파일 목록 셔플
    ShuffleIdx = (int *)malloc(sizeof(int *)*Folder2FileCnt);        // 파일 리스트의 인덱스를 셔플할 int 배열
    //qDebug() << Folder2FileCnt;
    ShufflingNumberTAOCP(Folder2FileCnt, ShuffleIdx);  // 인덱스 셔플

    // 폴더 1 이미지 출력
    Folder1ImgPrint(&Folder1FileArr, _curr_img);
    // 폴더 2 이미지 출력
    Folder2ImgPrint(&Folder2FileArr, ShuffleIdx, _iter);

}

// 폴더1의 이미지 출력
void MainWindow::Folder1ImgPrint(QVector<QString> *Folder1FileArr, int idx)
{
    QVector<QString> tmp = *Folder1FileArr;
    QPixmap img;

    img.load(tmp[idx]);
    CurrFileName1 = tmp[idx].section("/", -1);
    ui->label_img->setPixmap(img);
    ui->label_img->setScaledContents(true);
    ui->label_img->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

}

// 폴더2의 이미지 출력
void MainWindow::Folder2ImgPrint(QVector<QString> *Folder2FileArr, int *suffledIdx, int iter)
{
    int N = 10;
    int offset = iter * N;
    QVector<QString> tmp = *Folder2FileArr;
    QPixmap img[N];
    QString fileName[N];

    for (int i = 0; i < N; i++)
    {
        img[i].load(tmp[suffledIdx[offset + i]]);
        CurrFileName2[i] = tmp[suffledIdx[offset + i]].section("/", -1);
    }
    ui->label_img01->setPixmap(img[0]);
    ui->label_img02->setPixmap(img[1]);
    ui->label_img03->setPixmap(img[2]);
    ui->label_img04->setPixmap(img[3]);
    ui->label_img05->setPixmap(img[4]);
    ui->label_img06->setPixmap(img[5]);
    ui->label_img07->setPixmap(img[6]);
    ui->label_img08->setPixmap(img[7]);
    ui->label_img09->setPixmap(img[8]);
    ui->label_img10->setPixmap(img[9]);
    ui->label_img01->setScaledContents(true);
    ui->label_img02->setScaledContents(true);
    ui->label_img03->setScaledContents(true);
    ui->label_img04->setScaledContents(true);
    ui->label_img05->setScaledContents(true);
    ui->label_img06->setScaledContents(true);
    ui->label_img07->setScaledContents(true);
    ui->label_img08->setScaledContents(true);
    ui->label_img09->setScaledContents(true);
    ui->label_img10->setScaledContents(true);
    ui->label_img01->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img02->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img03->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img04->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img05->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img06->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img07->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img08->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img09->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_img10->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

// 화면상 매칭되는 이미지가 없는 경우 X를 눌러 다음 iter로 진행
void MainWindow::on_pushButton_X_clicked()
{
    _iter++;
    Folder2ImgPrint(&Folder2FileArr, ShuffleIdx, _iter);
    qDebug() << _iter;
}

void MainWindow::on_pushButton_O_clicked()
{
    if (ui->label_img01->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[0];
    if (ui->label_img02->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[1];
    if (ui->label_img03->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[2];
    if (ui->label_img04->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[3];
    if (ui->label_img05->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[4];
    if (ui->label_img06->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[5];
    if (ui->label_img07->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[6];
    if (ui->label_img08->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[7];
    if (ui->label_img09->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[8];
    if (ui->label_img10->lineWidth() != 1)
        qDebug() << CurrFileName1 << "," << CurrFileName2[9];

    _iter++;
    Folder2ImgPrint(&Folder2FileArr, ShuffleIdx, _iter);
    qDebug() << _iter;
}

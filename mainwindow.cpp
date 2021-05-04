#include "mainwindow.h"
#include "ui_mainwindow.h"

// global variable
int _iter = 0;
int _curr_img = 0;
QVector<QString> Folder1FileArr;
QVector<QString> Folder2FileArr;
QVector<QString> Folder2FileArrCls[15];
int Folder1FileCnt = 0;
int Folder2FileCnt = 0;
int *ShuffleIdx;
QString CurrFileName1;
QString CurrFileName2[10];
int CurrImgCls;
bool isNext = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *label_imgs[10] = {ui->label_img01, ui->label_img02, ui->label_img03, ui->label_img04, ui->label_img05,
                             ui->label_img06, ui->label_img07, ui->label_img08, ui->label_img09, ui->label_img10};
    for (auto label : label_imgs)
        label->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void ShufflingNumberTAOCP(int cnt, int *suffledIdx)
{
    for( int i=0; i < cnt; ++i )
        suffledIdx[i] = i;

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

void MainWindow::on_pushButton_Folder2_clicked()    // 폴더2 선택 및 경로 출력
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
    _curr_img = -1;
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
    Folder2FileCnt = Folder2FileArr.length(); // 폴더2 내 파일 개수

    // 폴더 2 전처리
    for (int i = 0; i < Folder2FileCnt; i++)
    {
        int idx = ColorExtract(Folder2FileArr[i]);
        Folder2FileArrCls[idx].push_back(Folder2FileArr[i]);
        ui->progressBar_loading->setValue(100*(i+1)/Folder2FileCnt);
    }

    on_pushButton_Next_clicked();

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
    QLabel *label_imgs[10] = {ui->label_img01, ui->label_img02, ui->label_img03, ui->label_img04, ui->label_img05,
                             ui->label_img06, ui->label_img07, ui->label_img08, ui->label_img09, ui->label_img10};
    int N = 10;
    int offset = iter * N - 1;
    QVector<QString> tmp = *Folder2FileArr;
    QPixmap img[N];
    QString fileName[N];
    int tempLength = Folder2FileArrCls[CurrImgCls].length();
    int showIdx = 10;

    for (int i = 0; i < N; i++)
    {
        if (offset + i >= tempLength)
        {
            showIdx = i;
            isNext = true;
            break;
        }
    }

    for (int i = 0; i < showIdx; i++)
    {
        img[i].load(tmp[suffledIdx[offset + i]]);
        CurrFileName2[i] = tmp[suffledIdx[offset + i]].section("/", -1);
    }

    for (int i = 0; i < N; i++)
    {
        if (showIdx <= i)
            label_imgs[i]->setText("");
        else
        {
            label_imgs[i]->setPixmap(img[i]);
            label_imgs[i]->setScaledContents(true);
            label_imgs[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        }
    }
}

// 화면상 매칭되는 이미지가 없는 경우 X를 눌러 다음 iter로 진행
void MainWindow::on_pushButton_X_clicked()
{
    if (isNext)
        on_pushButton_Next_clicked();
    _iter++;
    Folder2ImgPrint(&Folder2FileArrCls[CurrImgCls], ShuffleIdx, _iter);

 //   qDebug() << _iter;
    initImageLabelBorder();
}

// O 버튼 클릭 동작
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

    if (isNext)
        on_pushButton_Next_clicked();

    _iter++;
    Folder2ImgPrint(&Folder2FileArrCls[CurrImgCls], ShuffleIdx, _iter);

  //  qDebug() << _iter;
    initImageLabelBorder();
}

// 이미지 컬러 추출 (0-14 12 classes + 무채색 3)
int MainWindow::ColorExtract(QString filePath)
{    
    int idx = 0;
    Mat dst;
    Mat3b src = imread(filePath.toStdString());

    cv::resize(src, src, Size(32,32));

    int K = 4;
    int n = src.rows * src.cols;
    Mat data = src.reshape(1, n);
    data.convertTo(data, CV_32F);

    // Kmean 이용 레이블링
    vector<int> labels;
    Mat1f colors;
    kmeans(data, K, labels, cv::TermCriteria(), 1, cv::KMEANS_PP_CENTERS, colors);

    for (int i = 0; i < n; ++i)
    {
        data.at<float>(i, 0) = colors(labels[i], 0);
        data.at<float>(i, 1) = colors(labels[i], 1);
        data.at<float>(i, 2) = colors(labels[i], 2);
    }

    Mat3b reduced = data.reshape(3, src.rows);
    reduced.convertTo(dst, CV_8U);

 //   imshow("reduced color image", dst);

    // Get palette -> 레이블링 값을 RGB로
    map<Vec3b, int, lessVec3b> palette;
    for (int r = 0; r < src.rows; ++r)
    {
        for (int c = 0; c < src.cols; ++c)
        {
            Vec3b color = reduced(r, c);
            if (palette.count(color) == 0)
            {
                palette[color] = 1;
            }
            else
            {
                palette[color] = palette[color] + 1;
            }
        }
    }

    // 가장 빈도수 높은 RGB 색상 추출 (흰색에 근접한 배경은 제외)
//    int area = src.rows * src.cols;
    int firstColorIdx, secondColorIdx;
    vector<int> colorCnt, sortColorCnt;
    vector<Vec3f> colorVal;
    Vec3f mainRGB;
    Vec3f mainHSV;
    for (auto color : palette)
    {
        colorCnt.push_back(color.second);
        colorVal.push_back(color.first);
   //     cout << "Color: " << color.first << " \t - Area: " << 100.f * float(color.second) / float(area) << "%" << endl;
    }
    sortColorCnt = colorCnt;
    sort(sortColorCnt.begin(), sortColorCnt.end(), greater<int>());
    for (int i = 0; i < K; i++)
    {
        if (sortColorCnt[0] == colorCnt[i])
            firstColorIdx = i;
        else if (sortColorCnt[1] == colorCnt[i])
            secondColorIdx = i;
    }
    if (colorVal[firstColorIdx][0] > 235 && colorVal[firstColorIdx][1] > 235 && colorVal[firstColorIdx][2] > 235)
        mainRGB = colorVal[secondColorIdx];
    else
        mainRGB = colorVal[firstColorIdx];

    // 무채색인 경우
    int thres = 16;
    if (abs(mainRGB[0] - mainRGB[1]) < thres && abs(mainRGB[0] - mainRGB[2]) < thres && abs(mainRGB[2] - mainRGB[1]) < thres) // 무채색 조건
    {
        if (mainRGB[0] > 191) // white
            idx = 12;
        else if (mainRGB[0] > 63) // gray
            idx = 13;
        else    // black;
            idx = 14;
   //     cout << idx << mainRGB << endl;
        return idx;
    }
    else    // 주 색상을 HSV
    {
        Mat_<Vec3f> RGB(mainRGB);
        Mat_<Vec3f> HSV;
        cvtColor(RGB, HSV, COLOR_BGR2HSV);

        idx = HSV.at<Vec3f>(0,0)[0] / 30;
   //     cout << idx << " " << HSV.at<Vec3f>(0,0)[0] << endl;
        RGB.release();
        HSV.release();
        return idx;
    }
    dst.release();
    src.release();
    data.release();
    colors.release();
    reduced.release();
}

void MainWindow::Folder2ImageColorClassification(QVector<QString> *Folder2FileArr)
{
    QVector<QString> Arr = *Folder2FileArr;
    int cnt = Arr.length();
    int cls;
    for (int i = 0; i < cnt; i++)
    {
        cls = ColorExtract(Arr[i]);
        Folder2FileArrCls[cls].push_back(Arr[i]);
    }
}

void MainWindow::on_pushButton_Next_clicked()
{
    isNext = false;
    _iter = 0;
    initImageLabelBorder();
    _curr_img++;
    // _curr_img 색상 인덱스 검출
    CurrImgCls = ColorExtract(Folder1FileArr[_curr_img]);
    // 같은 색상 이미지인 파일목록 크기
    int Folder2FileCntCls = Folder2FileArrCls[CurrImgCls].length();

    // 폴더 2 파일 목록 셔플
    ShuffleIdx = (int *)malloc(sizeof(int *)*Folder2FileCntCls);        // 파일 리스트의 인덱스를 셔플할 int 배열
    //qDebug() << Folder2FileCnt;
    ShufflingNumberTAOCP(Folder2FileCntCls, ShuffleIdx);  // 인덱스 셔플

    // 폴더 1 이미지 출력
    Folder1ImgPrint(&Folder1FileArr, _curr_img);
    // 폴더 2 이미지 출력
    Folder2ImgPrint(&Folder2FileArrCls[CurrImgCls], ShuffleIdx, _iter);
}

void MainWindow::initImageLabelBorder()
{
    ui->label_img01->setLineWidth(1);
    ui->label_img02->setLineWidth(1);
    ui->label_img03->setLineWidth(1);
    ui->label_img04->setLineWidth(1);
    ui->label_img05->setLineWidth(1);
    ui->label_img06->setLineWidth(1);
    ui->label_img07->setLineWidth(1);
    ui->label_img08->setLineWidth(1);
    ui->label_img09->setLineWidth(1);
    ui->label_img10->setLineWidth(1);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bool isok = NET_DVR_Init();
    if(isok == false)
    {
        qDebug()<< "NET_DVR_Init error;error number is " <<NET_DVR_GetLastError();
        QMessageBox::warning(this,"error","NET_DVR_Init error;error number is "+QString::number(NET_DVR_GetLastError()));
    }
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
    //用于初始化SDK
    NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
    userID=NET_DVR_Login_V30("192.168.10.102",8000,"admin","1234536asd",&DeviceInfoTmp);//参数依次为IP地址、服务端口、账号、密码，最后一个参数是为了获得硬件信息的
    if(userID<0)
    {
        qDebug() << "NET_DVR_Login_V30 error;" << "error number is " << NET_DVR_GetLastError();
        QMessageBox::warning(this,"error",
                             "NET_DVR_Login_V30 error;error number "+QString::number(NET_DVR_GetLastError()));
        return;
    }
    qDebug()<<"Login Success,userID:" << userID<<endl;
    this->inSocket=new QTcpSocket;
    this->outSocket=new QTcpSocket;
    this->timer=new QTimer;
    this->IPAddress="127.0.0.1";//先使用本机地址
    inPort=6666,outPort=6666;//为输入端口和输出端口
    inSocket->abort();
    outSocket->connectToHost(IPAddress,inPort);
    inSocket->abort();
    outSocket->connectToHost(IPAddress,outPort);//进行连接
    inSocket->setSocketOption(QAbstractSocket::KeepAliveOption,"1"); //设置保持连接状态
    outSocket->setSocketOption(QAbstractSocket::KeepAliveOption,"1"); //设置保持连接状态
    connect(inSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(outSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(timer,SIGNAL(QTimer::timeout()),this,SLOT(MainWindow::OnClickedCapture()));
    connect(ui->pushButton,SIGNAL(QPushButton::clicked()),this,SLOT(MainWindow::play()));
    connect(inSocket,SIGNAL(readyRead()),this,SLOT(ReceiveJson()));
}

MainWindow::~MainWindow()
{
    uninitSDK();
    delete ui;
}

bool MainWindow::uninitSDK()
{
    bool isok = NET_DVR_Cleanup();
    if(isok == false)
    {
        qDebug()<< "NET_DVR_Cleanup error;error number is " <<NET_DVR_GetLastError();
        QMessageBox::warning(this,"error","NET_DVR_Cleanup error;error number "+QString::number(NET_DVR_GetLastError()));
        return isok;
    }
    return isok;
}

void MainWindow::OnClickedCapture()
{
    if(userID!=-1)
    {
        NET_DVR_JPEGPARA IpJpegPara2;
        IpJpegPara2.wPicQuality=0;
        IpJpegPara2.wPicSize=0xff;

        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyy-MM-dd_hh-mm-ss_zzz");
        current_date="C:\\Picture\\"+current_date+".jpg";
        char *fileName;
        QByteArray ba = current_date.toLatin1(); // must
        fileName=ba.data();
        if(NET_DVR_CaptureJPEGPicture(userID,1,&IpJpegPara2,fileName)==false)
        {
            qDebug() << "NET_DVR_CaptureJPEGPicture error;" << "error number is " << NET_DVR_GetLastError();
            QMessageBox::warning(this,"error","NET_DVR_CaptureJPEGPicture error;error number "+QString::number(NET_DVR_GetLastError()));
            return;
        }
        qDebug() <<"Capture Success!"<<endl;
        SendPic(current_date);//将保存的图片发送
    }
}

long MainWindow::play(HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo)
{
    struPlayInfo={0};
    struPlayInfo.hPlayWnd = hWnd;//需要 SDK 解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel = 1;//预览通道号
    struPlayInfo.dwStreamType = 0;//码流类型：0-主码流，1-子码流，2-三码流，3-虚拟码流，以此类推
    struPlayInfo.dwLinkMode = 0;//0- TCP 方式，1- UDP 方式，2- 多播方式，3- RTP 方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo.bBlocked = 1;//0- 非阻塞取流，1- 阻塞取流

    long IRealPlayHandle = NET_DVR_RealPlay_V40(userID,&struPlayInfo,NULL,NULL);

    if(IRealPlayHandle <0)
    {
        qDebug() << "NET_DVR_RealPlay_V40 error;error number " <<NET_DVR_GetLastError();
        QMessageBox::warning(this,"error","NET_DVR_RealPlay_V40 error;error number "+QString::number(NET_DVR_GetLastError()));
        NET_DVR_Logout(userID);
        userID=-1;
        return -1;
    }
    return IRealPlayHandle;
}

void MainWindow::SendPic(QString picPath){
    QPixmap picture(picPath);
    QByteArray img=QByteArray();
    QByteArray img64=QByteArray();
    QJsonDocument imgJD;
    QJsonObject imgJO;
    QBuffer buffer(&img);
    buffer.open(QIODevice::WriteOnly);
    picture.save(&buffer,"jpg",0);
    img64=img.toBase64();
    imgJO.insert("img",QJsonValue::fromVariant(img64));
    imgJD.setObject(imgJO);
    QByteArray dataArray=imgJD.toJson();
    outSocket->write(dataArray);
}

void MainWindow::ReceiveJson(){
      QByteArray json;
      json=inSocket->read(inSocket->readBufferSize());  //读取json数据
      QJsonParseError parseError;
      QJsonDocument jsonDoc(QJsonDocument::fromJson(json,&parseError));
      if(parseError.error==QJsonParseError::NoError)  //json格式是否正确
        {
            emit newJsonData(jsonDoc); //发送json数据信号
        }
      else
            qDebug()<<"json format error:"<<parseError.errorString();
}

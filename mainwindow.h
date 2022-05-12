#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTcpSocket>
#include <QDebug>
#include <QtCharts>
#include <QLineSeries>
#include <QPieSeries>
#include <QPolarChart>
#include <QPainter>
#include <QMessageBox>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <include/HCNetSDK.h>
#include <QBuffer>
#include <QByteArray>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void LineChart1();
    void LineChart2();
    void LineChart3();
    void show_time();
signals:
    void newJsonData(QJsonDocument);
private slots:
    void OnClickedCapture();
    void ReceiveJson();
private:
    Ui::MainWindow *ui;
    bool uninitSDK();
    long play(HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo);
    void SendPic(QString);
    long userID;
    long previewID;
    QTimer *picTimer;
    QTimer m_timer;
    QTimer *pTimer;
    QString  IPAddress;
    quint16 inPort;
    quint16 outPort;
    QTcpSocket *inSocket;
    QTcpSocket *outSocket;

    int picNum;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTcpSocket>
#include <QDebug>
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
private slots:
    void OnClickedCapture();
    void SendPic(QString);

private:
    Ui::MainWindow *ui;
    bool uninitSDK();
    long play(HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo);
    long userID;
    long previewID;
    QTimer *timer;
    QString  IPAddress;
    quint16 inPort;
    quint16 outPort;
    QTcpSocket *inSocket;
    QTcpSocket *outSocket;
};

#endif // MAINWINDOW_H

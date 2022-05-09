#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTcpSocket>
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
    void OnClickedPreview();
    void OnClickedStopPreview();
    void OnClickedCapture();
private:
    Ui::MainWindow *ui;
    bool uninitSDK();
    long play(HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo);
    long userID;
    long previewID;
    Qtcp
};

#endif // MAINWINDOW_H

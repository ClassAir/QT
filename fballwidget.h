#ifndef FBALLWIDGET_H
#define FBALLWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QMenu>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>
class MainWindow;
class FBallWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FBallWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void contextMenuEvent(QContextMenuEvent * e);
    void paintEvent(QPaintEvent *event);

signals:
    void notifyExitSoftSig();

public slots:
    void OnBallHideSlot();
    void OnCloseSlot();
    void OnCountSlot();

private:
    QCursor* m_handle;
    QCursor* m_handlePress;
private:
    QPoint m_point;
    QPixmap m_bg;
    bool m_press;
    bool m_over;
    bool isHide;
    QTimer* m_timer;
    int m_nMemOcc;  //记录的人数
    MainWindow * m_mainWindow{nullptr};
};

#endif // FBALLWIDGET_H

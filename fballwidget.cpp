#include "fballwidget.h"
#include "widget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QMenu>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>
//#define App (static_cast<application*>(QCoreApplication::instance()))
FBallWidget::FBallWidget(QWidget *parent)
    : QWidget(parent)
    ,m_nMemOcc(20)
{//无边界窗口|在所有窗口顶部
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);//半透明

    m_press = false;
    m_bg.load(":/images/background.png");

    QPixmap handle;
    handle.load(":/images/handle.png");

    QPixmap handlePress;
    handlePress.load(":/images/handlePress.png");

    m_handle = new QCursor(handle, 0, 0);
    m_handlePress = new QCursor(handlePress, 0, 0);
    this->setFixedSize(150, 62);

    setCursor(*m_handle);

    int screenWidth = QApplication::desktop()->screenGeometry().width();
    int screenHeight = QApplication::desktop()->screenGeometry().height();
    this->move(screenWidth - 42, screenHeight * 0.618);

    connect(this, SIGNAL(notifyExitSoftSig()), this, SLOT(OnCloseSlot()));

    //动画延迟，否则会有抖动
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(OnBallHideSlot()));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(OnCountSlot()));
    timer->start(500);
    //m_mainWindow = new MainWindow();
    //m_mainWindow->move(App->desktop()->screen()->rect().center() - m_mainWindow->rect().center());
   // m_mainWindow->showNormal();

}

void FBallWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_press = true;
        setCursor(*m_handlePress);
    }

    m_point = event->globalPos() - pos();
}

void FBallWidget::mouseReleaseEvent(QMouseEvent *)
{
    setCursor(*m_handle);
    m_press = false;
}

void FBallWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_press)
    {
        int screenWidth = QApplication::desktop()->screenGeometry().width();
        QPoint move_pos = event->globalPos();
        QPoint tarPos = move_pos - m_point;

        if(tarPos.x() + this->width() > screenWidth)
        {
            tarPos.setX(screenWidth - this->width());
        }
        move(tarPos);
    }
}

void FBallWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
    //if (m_mainWindow) {
    //    m_mainWindow->show();
    //    m_mainWindow->activateWindow();
   // }

}

void FBallWidget::enterEvent(QEvent *event)             //好东西
{
    int screenWidth = QApplication::desktop()->screenGeometry().width();
    if(this->geometry().x() + this->width() > screenWidth)
    {
        QRect rect = this->geometry();
        rect.setX(screenWidth - this->width());

        QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "geometry");
        pAnimation->setStartValue(this->geometry());
        pAnimation->setEndValue(rect);
        pAnimation->setEasingCurve(QEasingCurve::Linear);
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    isHide = true;
    m_over = true;
    update();
}

void FBallWidget::leaveEvent(QEvent *event)
{
//    int screenWidth = QApplication::desktop()->screenGeometry().width();
//    if(this->geometry().x() + this->width() > screenWidth - 2)
//    {
//        QRect rect = this->geometry();
//        rect.setX(screenWidth - 42);

//        QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "geometry");
//        pAnimation->setStartValue(this->geometry());
//        pAnimation->setEndValue(rect);
//        pAnimation->setEasingCurve(QEasingCurve::Linear);
//        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
//        isHide = false;
//    }
//    m_over = false;
//    update();
    Q_UNUSED(event);
    //this->hide();
    m_timer->start(1000);
}

void FBallWidget::contextMenuEvent(QContextMenuEvent * e)
{
    QMenu menu;
    menu.addAction(QStringLiteral("exit"));

    QAction *act = menu.exec(QCursor::pos());
    //QAction *act = menu.exec(event->screenPos());

    if(!act)
    {
        qDebug() << "if(!act)";
        return;
    }

    qDebug() << "notifyExitSoftSig";

    emit notifyExitSoftSig();
}

void FBallWidget::OnCloseSlot()
{
    qDebug() << "OnCloseSlot";
//    close();
    qApp->exit();
}

void FBallWidget::OnCountSlot()
{
    m_nMemOcc += 2;
    if(m_nMemOcc >= 100)
    {
        m_nMemOcc = 0;
    }
    update();
    //qDebug() << "m_nMemOcc:" << m_nMemOcc;
}

void FBallWidget::OnBallHideSlot()
{
    QPoint cursorPoint = cursor().pos();
//    qDebug() << "cursorPoint: " << cursorPoint;
    QPoint thisPos = this->pos();
//    qDebug() << "this point: " << thisPos << " " << thisPos + QPoint(this->width(),this->height());

    QPoint offsetPoint = cursorPoint - thisPos - QPoint(this->width(),this->height());
    if(offsetPoint.x() <= -140 || offsetPoint.y() >= 0 || offsetPoint.y() <= -80)
    {
        qDebug() << "offsetPoint:" << offsetPoint;
    }
    else
    {
        return;
    }

    m_timer->stop();
    int screenWidth = QApplication::desktop()->screenGeometry().width();
    if(this->geometry().x() + this->width() > screenWidth - 2)
    {
        QRect rect = this->geometry();
        rect.setX(screenWidth - 42);

        QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "geometry");
        pAnimation->setStartValue(this->geometry());
        pAnimation->setEndValue(rect);
        pAnimation->setEasingCurve(QEasingCurve::Linear);
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        isHide = false;
    }
    m_over = false;
    update();
}

void FBallWidget::paintEvent(QPaintEvent *e)
{
    QPainterPath pathFill;
    pathFill.setFillRule(Qt::WindingFill);
    int startX = 22;
    int startY = 1;
    pathFill.addEllipse(startX ,startY,50,50);
    pathFill.addRect(25 + startX, 8 + startY, 86, 37);
    QPainterPath pathFill1;
    pathFill1.addEllipse(92 + startX, 7 + startY, 34, 38);

    QPainter painter(this);
    painter.setPen(QPen(QColor(178, 178, 178)));

    QPainterPath pathLine;
    pathLine.addEllipse(92 + startX, 7 + startY, 34, 38);
    painter.drawRect(25 + startX, 6 + startY, 86, 39);

    //绘制渐变的底色
    QLinearGradient linearGradient(0,startY,0,startY + 50);
    linearGradient.setColorAt(0.0,QColor(252,252,252));
    linearGradient.setColorAt(1.0,QColor(200,200,200));
    painter.fillPath(pathFill1, QBrush(linearGradient));

    painter.setRenderHint(QPainter::Antialiasing, true);
    //右边的半圆 线
    painter.drawPath(pathLine);
    painter.setRenderHint(QPainter::Antialiasing, false);


    painter.fillPath(pathFill, QBrush(linearGradient));
    painter.setPen(QPen(Qt::white));
    painter.drawLine(30 + startX, 7 + startY, 108 + startX, 7 + startY);
    QLinearGradient linearGradient1(109 + startX,0,113 + startX,0);
    linearGradient1.setColorAt(0.0,QColor(251,251,251));
    linearGradient1.setColorAt(1.0,QColor(182,182,182));
    painter.setPen(QPen(QBrush(linearGradient1),1));

    painter.drawLine(109 + startX, 7 + startY, 113 + startX, 7 + startY);

    QLinearGradient linearGradient2(109 + startX,0,112 + startX,0);
    linearGradient2.setColorAt(0.0,QColor(182,182,182));
    linearGradient2.setColorAt(1.0,QColor(185,185,185,64));
    painter.setPen(QPen(QBrush(linearGradient2),1));
    painter.drawLine(109 + startX, 6 + startY, 112 + startX, 6 + startY);
    painter.drawLine(109 + startX, 45 + startY, 112 + startX, 45 + startY);
    painter.setPen(QPen(QColor(178, 178, 178)));

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawEllipse(startX ,startY,50,50);//外圈
    painter.drawPixmap(3 + startX , 3 + startY, m_bg);//底色

    QRectF rectangle1(3 + startX , 3 + startY, 44, 44);
//    int m_nMemOcc = 30;
    int nMemDrawV = 360/100*m_nMemOcc;
    int startAngle = (0 - (90 + nMemDrawV/2)) * 16;
    int spanAngle = nMemDrawV * 16;

    //绘制内存使用半圆图形
    painter.setBrush(QColor(255-m_nMemOcc*2,m_nMemOcc*1.8,0));
    painter.drawChord(rectangle1, startAngle, spanAngle);
//    painter.drawChord(rectangle1, -90*16, -90*16);
    painter.setRenderHint(QPainter::Antialiasing, false);
   // qDebug() << "startAngle:" << startAngle << "spanAngle:" << spanAngle;

    painter.setBrush(QBrush(Qt::green));//这里是箭头
    painter.setPen(Qt::NoPen);
    painter.drawRect(this->width()/2+7,30,4,5);
    painter.drawPolygon(QPolygonF() << QPointF(this->width()/2+5,35) << QPointF(this->width()/2+13,35) << QPointF(this->width()/2+9,40));

    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(this->width()/2+7,20,4,5);
    painter.drawPolygon(QPolygonF() << QPointF(this->width()/2+5,20) << QPointF(this->width()/2+13,20) << QPointF(this->width()/2+9,15));

    QString strNetUpL = "应到50人";
    QString strNetDownL = "实到"+QString::number(m_nMemOcc/2)+"人";
    QString strMemOcc = "";  //aa和bb
    QString strCpuOcc = QString::number(m_nMemOcc/2)+"/50";
    int m_nCpuOcc = 10;

    QPen pen(Qt::black);
    QFont font;
    font.setPointSize(6);
    pen.setWidthF(0.5);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(QRectF(this->width()/2+17,15,40,18), strNetUpL);
    painter.drawText(QRectF(this->width()/2+17,30,40,18), strNetDownL);

    font.setPointSize(10);
    pen.setWidthF(6);
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.setFont(font);

    static bool flag = false;
    if(flag)
    {
        if(50 < m_nMemOcc && m_nMemOcc < 80)
        {
            pen.setColor(Qt::yellow);
            painter.setPen(pen);
        }
        else if(m_nMemOcc >= 80)
        {
            pen.setColor(Qt::green);
            painter.setPen(pen);
        }else if(m_nMemOcc<=50&&m_nMemOcc>0){
            pen.setColor(Qt::red);
            painter.setPen(pen);
        }

        painter.drawText(QRectF(33,12,60,40), strMemOcc);
    }
    else
    {
        if(50 < m_nMemOcc && m_nMemOcc < 80)
        {
            pen.setColor(Qt::yellow);
            painter.setPen(pen);
        }
        else if(m_nCpuOcc >= 80)
        {
            pen.setColor(Qt::green);
            painter.setPen(pen);
        }else if(m_nMemOcc<=50&&m_nMemOcc>0){
            pen.setColor(Qt::red);
            painter.setPen(pen);
        }
        painter.drawText(QRectF(25,15,53,38), strCpuOcc);
    }
   // flag = !flag;
}


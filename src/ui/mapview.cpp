#include "mapview.h"
#include <QDebug>
#include <QScrollBar>

MapView::MapView(QWidget *parent) : QGraphicsView(parent), m_isDragging(false)
{
    m_hasReference = false;
    m_refLat = 0.0;
    m_refLon = 0.0;

    // 1. 创建场景
    m_scene = new QGraphicsScene(this);
    this->setScene(m_scene);

    // 2. 开启抗锯齿，让画出来的圆点边缘更平滑
    this->setRenderHint(QPainter::Antialiasing, true);

    // 3. 隐藏滚动条 (像百度地图那样，直接鼠标拖，不要滚动条)
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 4. 设置拖拽模式
    this->setDragMode(QGraphicsView::NoDrag);
}

void MapView::addTrajectoryPoint(const SensorData data)
{
    if(!m_hasReference)
    {
        m_refLat = data.lat;
        m_refLon = data.lon;
        m_hasReference = true;
        qDebug() << "地图原点_" << m_refLon << "," << m_refLat;
    }

    double screenX = (data.lat - m_refLat) * 10000;
    double screenY = -(data.lon - m_refLon) * 10000;

    QColor pointColor;
    if (data.n < 12.0)
    {
        pointColor = Qt::green;
    }
    else if (data.n < 14.0)
    {
        pointColor = Qt::yellow;
    }
    else
    {
        pointColor = Qt::red;
    }

    double pointSize = 8.0;
    m_scene->addEllipse(screenX - pointSize/2, screenY - pointSize/2, pointSize, pointSize, QPen(Qt::NoPen), QBrush(pointColor));

    this->centerOn(screenX, screenY);
}

void MapView::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
    this->scale(scaleFactor, scaleFactor);
}

void MapView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isDragging = true;
        m_lastPointPos = event->pos();
        this->setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void MapView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging)
    {
        QPoint delta = event->pos() - m_lastPointPos;
        m_lastPointPos = event->pos();

        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - delta.x());
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - delta.y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void MapView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isDragging = false;
        this->setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}


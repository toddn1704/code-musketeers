/*layoutgraphicsitem.h

This file contains the LayoutGraphicsItem class.
This class is a custom subclass of QGraphicsItem.
It contains a polygon and has support for adding points.


*/
#ifndef LAYOUTGRAPHICSITEM_H
#define LAYOUTGRAPHICSITEM_H

#include <qgraphicsitem.h>
#include <qpolygon.h>
#include <qpainter.h>
#include <qdebug.h>

class LayoutGraphicsItem : public QGraphicsItem
{
public:

	LayoutGraphicsItem(int pen_flag)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsSelectable);
		pen_flag_ = pen_flag;
	}

	LayoutGraphicsItem(QVector<QPointF> & points,int pen_flag)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsSelectable);
		pen_flag_ = pen_flag;
		polygon = points;
	}

	QRectF boundingRect() const
	{
		return polygon.boundingRect();
	}

	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
	{
		QPen pen;
		pen.setWidth(5);
		if (isSelected())
		{
			qDebug() << "Hello";
			pen.setColor(Qt::red);
		}
		else if (pen_flag_ < 0)//room
		{
			pen.setColor(Qt::black);
		}
		else if (pen_flag_ >= 0)//container
		{
			pen.setColor(Qt::blue);
			pen.setWidth(3);
		}
		painter->setPen(pen);

		if (!polygon.isEmpty())
		{
			if (pen_flag_ >= 0)
			{
				QBrush brush;
				brush.setColor(Qt::blue);
				brush.setStyle(Qt::SolidPattern);
				QPainterPath path;
				path.addPolygon(polygon);
				painter->fillPath(path, brush);
				painter->drawPolygon(polygon);
			}
			else
			{
				painter->drawPolygon(polygon);
			}
		}
	}
	// Adds point to the polygon then updates parent scene
	void AddPointToPolygon(QPointF point)
	{
		polygon.append(point);
		scene()->update();
	}

	void PopPointFromPolygon()
	{
		polygon.pop_back();
		scene()->update();
	}

	// Does nothing right now
	void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
	{
		qDebug() << "GOT IT";
		scene()->update();
		
	}

	int size()
	{
		return polygon.size();
	}

	QVector<QPointF> get_polygon()
	{
		return polygon;
	}
private:
	QPolygonF polygon;
	int pen_flag_;//used to determine pen color for rooms and containers
};

#endif
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

	LayoutGraphicsItem()
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsSelectable);
	}

	LayoutGraphicsItem(QVector<QPointF> & points)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsSelectable);
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
		else
		{
			pen.setColor(Qt::black);
		}
		painter->setPen(pen);

		if (!polygon.isEmpty())
		{
			painter->drawPolygon(polygon);
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
};

#endif
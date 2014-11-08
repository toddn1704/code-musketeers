#ifndef LAYOUTGRAPHICSITEM_H
#define LAYOUTGRAPHICSITEM_H

#include <qgraphicsitem.h>
#include <qpolygon.h>
#include <qpainter.h>

class LayoutGraphicsItem : public QGraphicsItem
{
public:

	LayoutGraphicsItem()
	{
		setFlag(ItemIsMovable);
	}

	QRectF boundingRect() const
	{
		return polygon.boundingRect();
	}

	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
	{
		QPen pen;
		pen.setWidth(5);
		painter->setPen(pen);

		if (!polygon.isEmpty())
		{
			painter->drawPolygon(polygon);
		}
	}

	void AddPointToPolygon(QPoint point)
	{
		polygon.append(point);
	}

private:
	QPolygon polygon;

};

#endif
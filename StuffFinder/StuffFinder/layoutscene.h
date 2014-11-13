/*layoutscene.h

This file contains the LayoutScene class.
This class is a custom subclass of QGraphicsScene

*/
#ifndef LAYOUTSCENE_H
#define LAYOUTSCENE_H

#include <qgraphicsscene.h>
#include <layoutgraphicsitem.h>
#include <qgraphicssceneevent.h>
#include<QKeyEvent>
#include <qtransform.h>
#include <qdebug.h>

class LayoutScene : public QGraphicsScene
{
Q_OBJECT

protected:
	// Handle a mouse press
	void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
	{
		
		if (drawing)
		{
		
			current_item_->AddPointToPolygon(mouseEvent->buttonDownScenePos(mouseEvent->button()));
			current_item_->AddPointToPolygon(mouseEvent->scenePos());
		}
		
		// Checks if clicking on an item and if so sends the event to it
		else if (QGraphicsItem * selected_item = itemAt(mouseEvent->buttonDownScenePos(mouseEvent->button()), QTransform()))
		{

			update();
		}
		else
		{
			clearSelection();
			current_item_ = NULL;
		}
	
		
	}
	// Called when the mouse moves, if user is drawing pops previous point 
	// and adds new point to current drawing
	void mouseMoveEvent(QGraphicsSceneMouseEvent * mouse_event)
	{
		if (drawing)
		{
			current_item_->PopPointFromPolygon();
			current_item_->AddPointToPolygon(mouse_event->scenePos());
		}
	}
	/*
	// On pressing enter sets drawing false
	void keyPressEvent(QKeyEvent * e)
	{
		if (e->key() == Qt::Key_Return)
		{
			if (drawing && current_item_->size() > 1)
			{
				current_item_->PopPointFromPolygon();
				drawing = false;
				current_item_ = NULL;
			}
		}
	}*/

public:
	QVector<QPointF> StopDrawing()
	{
		if (drawing && current_item_->size() > 1)
		{
			current_item_->PopPointFromPolygon();
			drawing = false;
			return current_item_->get_polygon();
		}
		
		return QVector<QPointF>();
	}
	void NewContainer(int id)
	{ 
		drawing = true;
		current_item_ = new LayoutGraphicsItem;

		addItem(current_item_);
		current_item_->AddPointToPolygon(QPointF(0, 0));
		current_item_->setData(Qt::UserRole, id);
	}
	void NewContainer(int id, QVector<QPointF> &points)
	{
		current_item_ = new LayoutGraphicsItem(points);
		current_item_->setData(Qt::UserRole, id);
		addItem(current_item_);
	}
	int CurrentContainerId()
	{
		return current_item_->data(Qt::UserRole).toInt();
	}
private:
	bool drawing = false;
	LayoutGraphicsItem * current_item_;
};

#endif
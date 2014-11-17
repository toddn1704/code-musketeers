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
	

public:
	// Removes last point from polygon and returns created item only if
	// currently drawing and item has enough points
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
	// Creates a new empty graphicsitem and enables drawing
	void NewContainer(int id,int parent_id)
	{ 
		drawing = true;
		current_item_ = new LayoutGraphicsItem(parent_id);
		current_item_->setData(Qt::UserRole, id);
		current_item_->setData(Qt::DisplayRole, parent_id);
		addItem(current_item_);
		current_item_->AddPointToPolygon(QPointF(0, 0));
	}
	// Builds a new graphics item from a vector
	void NewContainer(int id, QVector<QPointF> &points,int parent_id)
	{
		current_item_ = new LayoutGraphicsItem(points,parent_id);
		current_item_->setData(Qt::UserRole, id);
		current_item_->setData(Qt::DisplayRole,parent_id);
		addItem(current_item_);
	}
	
	int CurrentContainerId()
	{
		return current_item_->data(Qt::UserRole).toInt();
	}
	// Finds the item with given id and removes it from scene
	void DeleteContainer(int id)
	{
		QList<QGraphicsItem *> all_items = items();
		QList<QGraphicsItem *>::iterator i;
		for (i = all_items.begin(); i != all_items.end(); i++)
		{
			if ((*i)->data(Qt::UserRole) == id)
			{
				removeItem((*i));
			}
			else if ((*i)->data(Qt::DisplayRole) == id)
			{
				qDebug() << "found subcontainer_parent id: " << id << "\n";
				removeItem((*i));
			}
		}
	}

	void HighlightItem(int id)
	{
		QList<QGraphicsItem *> all_items = items();
		QList<QGraphicsItem *>::iterator i;
		clearSelection();
		for (i = all_items.begin(); i != all_items.end(); i++)
		{
			if ((*i)->data(Qt::UserRole) == id)
			{
				(*i)->setSelected(true);
			}
		}
	}

	void UnHighlightItem()
	{
		QList<QGraphicsItem *> all_items = items();
		QList<QGraphicsItem *>::iterator i;
		clearSelection();
		for (i = all_items.begin(); i != all_items.end(); i++)
		{
			(*i)->setSelected(false);
		}
	}
	bool get_drawing(){ return drawing; }
private:
	bool drawing = false;
	LayoutGraphicsItem * current_item_;
};

#endif
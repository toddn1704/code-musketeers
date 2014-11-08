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
			current_item->AddPointToPolygon(mouseEvent->buttonDownScenePos(mouseEvent->button()));
			current_item->AddPointToPolygon(mouseEvent->scenePos());
		}
		// Checks if clicking on an item and if so sends the event to it
		else if (QGraphicsItem * selected_item = itemAt(mouseEvent->buttonDownScenePos(mouseEvent->button()), QTransform()))
		{
			sendEvent(selected_item, mouseEvent);
		}
		else
		{
			drawing = true;
			current_item = new LayoutGraphicsItem;
			addItem(current_item);
			current_item->AddPointToPolygon(mouseEvent->buttonDownScenePos(mouseEvent->button()));		
		}
	
		
	}
	// Called when the mouse moves, if user is drawing pops previous point 
	// and adds new point to current drawing
	void mouseMoveEvent(QGraphicsSceneMouseEvent * mouse_event)
	{
		if (drawing)
		{
			current_item->PopPointFromPolygon();
			current_item->AddPointToPolygon(mouse_event->scenePos());
		}
	}
	// On pressing enter sets drawing false
	void keyPressEvent(QKeyEvent * e)
	{
		if (e->key() == Qt::Key_Return)
		{
			current_item->PopPointFromPolygon();
			drawing = false;
		}
	}
private:
	bool drawing = false;
	LayoutGraphicsItem * current_item;
	
};

#endif
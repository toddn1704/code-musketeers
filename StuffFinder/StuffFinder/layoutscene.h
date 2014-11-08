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
		// Checks if clicking on an item and if so sends the event to it
		if (QGraphicsItem * selected_item = itemAt(mouseEvent->buttonDownScenePos(mouseEvent->button()), QTransform()))
		{
			sendEvent(selected_item, mouseEvent);
		}
		else if (!drawing)
		{
			drawing = true;
			current_item = new LayoutGraphicsItem;
			addItem(current_item);
			current_item->AddPointToPolygon(mouseEvent->buttonDownScenePos(mouseEvent->button()));		
		}
		else
		{
			current_item->AddPointToPolygon(mouseEvent->buttonDownScenePos(mouseEvent->button()));
		}
		
	}
	// On pressing enter sets drawing false
	void keyPressEvent(QKeyEvent * e)
	{
		if (e->key() == Qt::Key_Return)
		{
			drawing = false;
		}
	}
private:
	bool drawing = false;
	LayoutGraphicsItem * current_item;
	
};

#endif
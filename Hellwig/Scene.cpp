#include "Scene.h"
#include <QPainter>

CScene::CScene(QObject* parent /*= nullptr*/)
	: QGraphicsScene(parent)
{
}

CScene::CScene(const QRectF& sceneRect, QObject* parent /*= nullptr*/)
	: QGraphicsScene(sceneRect, parent)
{
}

void CScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	QGraphicsScene::drawBackground(painter, rect);
	const int gridSize = 25;

	qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
	qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

	QVarLengthArray<QLineF, 100> lines;

	for (qreal x = left; x < rect.right(); x += gridSize)
		lines.append(QLineF(x, rect.top(), x, rect.bottom()));
	for (qreal y = top; y < rect.bottom(); y += gridSize)
		lines.append(QLineF(rect.left(), y, rect.right(), y));

	painter->setPen(QPen(QColor(0, 0, 0, 80)));
	painter->drawLines(lines.data(), lines.size());
}

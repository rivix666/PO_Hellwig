#pragma once
#include <QGraphicsScene>

class CScene : public QGraphicsScene
{
	Q_OBJECT

public:
	CScene(QObject* parent = nullptr);
	CScene(const QRectF& sceneRect, QObject* parent = nullptr);
	~CScene() = default;

protected:
	virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
};
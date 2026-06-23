#ifndef GRIDDRAGCONTROLLER_H
#define GRIDDRAGCONTROLLER_H

#include <QObject>
#include <QPoint>

class QWidget;

class GridDragController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(GridDragController)

public:
    explicit GridDragController(QObject *parent = nullptr);

    void beginDrag(QWidget *widget, const QPoint &pointOffset);
    void updateDragPosition(const QPoint &widgetPos);
    void endDrag();

    bool isDragging() const;
    QWidget *draggedWidget() const;
    QPoint dragPointOffset() const;

private:
    QWidget *m_draggedWidget = nullptr;
    QPoint m_dragPointOffset;
};

#endif // GRIDDRAGCONTROLLER_H

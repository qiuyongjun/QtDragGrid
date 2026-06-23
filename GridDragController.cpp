#include "GridDragController.h"

#include <QWidget>
#include <QtGlobal>

GridDragController::GridDragController(QObject *parent)
    : QObject(parent)
{
}

void GridDragController::beginDrag(QWidget *widget, const QPoint &pointOffset)
{
    if (!widget) {
        return;
    }

    m_draggedWidget = widget;
    m_dragPointOffset = pointOffset;
}

void GridDragController::updateDragPosition(const QPoint &widgetPos)
{
    if (!m_draggedWidget) {
        return;
    }

    m_draggedWidget->move(widgetPos);
}

void GridDragController::endDrag()
{
    m_draggedWidget = nullptr;
    m_dragPointOffset = QPoint();
}

bool GridDragController::isDragging() const
{
    return m_draggedWidget != nullptr;
}

QWidget *GridDragController::draggedWidget() const
{
    return m_draggedWidget;
}

QPoint GridDragController::dragPointOffset() const
{
    return m_dragPointOffset;
}

#include <QtDragGrid/DragGridWidget.h>

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QtDragGrid::DragGridWidget grid;
    QObject::connect(&grid, &QtDragGrid::DragGridWidget::orderChanged, []() {});
    QObject::connect(&grid, &QtDragGrid::DragGridWidget::orderUpdated,
                     [](const QList<QWidget *> &) {});
    grid.setColumnCount(2);
    return grid.columnCount() == 2 ? 0 : 1;
}

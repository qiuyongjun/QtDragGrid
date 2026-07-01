#include <YJDragGrid/DragGridWidget.h>

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    YJDragGrid::DragGridWidget grid;
    QObject::connect(&grid, &YJDragGrid::DragGridWidget::orderChanged, []() {});
    QObject::connect(&grid, &YJDragGrid::DragGridWidget::orderUpdated,
                     [](const QList<QWidget *> &) {});
    grid.setColumnCount(2);
    return grid.columnCount() == 2 ? 0 : 1;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SendRequest();
    void toggleTree();

private:
    void closeTab(int index);
    QSplitter *splitter; //splitter как член класса
    QFileSystemModel *fileModel;
     void FileClicked(const QModelIndex &index);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Сетап Ui
    ui->setupUi(this);

    // Закрытие вкладок
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);

    // Сплитер (не нашёл как в дизайнере это сделать)
    splitter = ui->splitter;
    splitter->setSizes({600,200});
}

void MainWindow::closeTab(int index)
{
    // Получение индекса вкладки
    QWidget *tab = ui->tabWidget->widget(index);
    // Удаляем вкладку
    ui->tabWidget->removeTab(index);
    delete tab;

    // Перемещаем сплитер влево если вкладок нет
    if(ui->tabWidget->count()==0) splitter->setSizes({0,800});
}
void MainWindow::SendRequest()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkRequest request(QUrl(""));
}
MainWindow::~MainWindow()
{
    delete ui;
}

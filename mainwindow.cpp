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

    splitter = ui->splitter;
    splitter->setSizes({600, 200});
    // Обработка нажатие кнопки, вызов функции
    connect(ui->pushButton, &QPushButton::clicked,this,&MainWindow::toggleTree);
}

void MainWindow::closeTab(int index)
{
    // Получение индекса вкладки
    QWidget *tab = ui->tabWidget->widget(index);
    // Удаляем вкладку
    ui->tabWidget->removeTab(index);
    delete tab;

    // Перемещаем сплитер влево если вкладок нет
    if (ui->tabWidget->count()==0)
    {
        ui->tabWidget->hide();
        ui->pushButton->setVisible(false);
        ui->treeView->setVisible(true);
        splitter->setSizes({0,1});
    } else
    {
        ui->pushButton->setVisible(true);
    }
}

void MainWindow::toggleTree()
{
    if(!ui->tabWidget->isVisible()) return;
    bool visible = ui->treeView->isVisible();
    ui->treeView->setVisible(!visible);

    // Двигаем сплитер
    // !visible? splitter->setSizes({600,200}) : splitter->setSizes({800,0});
    visible? splitter->setSizes({800,0}) : splitter->setSizes({600,200});
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

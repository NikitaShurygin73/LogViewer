#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QDir>
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
    // Открываем на весь экран
    this->showMaximized();
    // Удаляем 2 стартовые страницы, прячем tabwidget и кнопку
    ui->tabWidget->clear();
    ui->tabWidget->hide();
    ui->pushButton->setVisible(false);

    // Инициализация дерева файлов
    fileModel = new QFileSystemModel(this);
    QString defaultPath = QDir::homePath();
    fileModel->setRootPath(defaultPath);
    ui->treeView->setModel(fileModel);
    ui->treeView->setRootIndex(fileModel->index(defaultPath));

    // Клик по файлу
    connect(ui->treeView, &QTreeView::doubleClicked,
            this, &MainWindow::FileClicked);

    // Закрытие вкладок
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);

    splitter = ui->splitter;
    splitter->setSizes({600, 200});
    // Обработка нажатие кнопки, вызов функции
    connect(ui->pushButton, &QPushButton::clicked,this,&MainWindow::toggleTree);
}

void MainWindow::FileClicked(const QModelIndex &index)
{
    QString filePath = fileModel->filePath(index);

    // Проверка: является ли это файлом (а не директорией)
    if (!QFileInfo(filePath).isFile())
        return;

    // Открытие файла
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл:" << filePath;
        return;
    }

    QString fileExtension = QFileInfo(filePath).suffix().toLower();
    QStringList allowedExtensions = {"txt", "log", "csv"};

    if (!allowedExtensions.contains(fileExtension)) {
        qWarning() << "Этот тип файла не поддерживается:" << fileExtension;
        return;
    }

    QString content = file.readAll();
    file.close();

    // Открываем tabwidget если был скрыт
    ui->tabWidget->show();
    ui->pushButton->setVisible(true);

    // Создание виджета с текстом лога
    QPlainTextEdit *logViewer = new QPlainTextEdit;
    logViewer->setPlainText(content);
    logViewer->setReadOnly(true);

    // Имя файла как заголовок вкладки
    QString fileName = QFileInfo(filePath).fileName();

    // Добавление новой вкладки
    ui->tabWidget->addTab(logViewer, fileName);
    ui->tabWidget->setCurrentWidget(logViewer);
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
    visible? splitter->setSizes({800,0}) : splitter->setSizes({600,200});
    // Меняем текст на кнопке
    ui->pushButton->setText(visible ? "<<" : ">>");
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

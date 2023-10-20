#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qtime>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Super clock");

    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    ui->lcdNumber->display(currentTime);
    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    ui->trayCheckBox->setChecked(settings.value(SETTINGS_TRAY, false).toBool());


    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setToolTip("Super clock" "\n"
                         "Работа со сворачиванием программы трей");

    QMenu * menu = new QMenu(this);
    QAction * viewWindow = new QAction(("Развернуть окно"), this);
    QAction * quitAction = new QAction(("Выход"), this);

    connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    menu->addAction(viewWindow);
    menu->addAction(quitAction);

    trayIcon->setContextMenu(menu);
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    ui->lcdNumber->display(currentTime);
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if(this->isVisible() && ui->trayCheckBox->isChecked()){
        event->ignore();
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

        trayIcon->showMessage("Tray Program",
                              ("Приложение свернуто в трей. Для того чтобы, "
                                     "развернуть окно приложения, щелкните по иконке приложения в трее"),
                              icon,
                              2000);
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:
        if(ui->trayCheckBox->isChecked()){
            if(!this->isVisible()){
                this->show();
            } else {
                this->hide();
            }
        }
        break;
    default:
        break;
    }
}

void MainWindow::on_saveButton_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    if(ui->trayCheckBox->isChecked()){
        settings.setValue(SETTINGS_TRAY, true);
    } else {
        settings.setValue(SETTINGS_TRAY, false);
    }
    settings.setValue("settings/User_Name", ui->lineEdit->text());
    settings.sync();
    QMessageBox::information(this,
                             ("Сохранение настроек"),
                             ("Сохранение настроек выполнено успешно"));
}

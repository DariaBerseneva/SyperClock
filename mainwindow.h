#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QSettings>
#include <QMessageBox>

#define ORGANIZATION_NAME "EVILEG"
#define ORGANIZATION_DOMAIN "www.evileg.ru"
#define APPLICATION_NAME "QSettings Program"

#define SETTINGS_TRAY "settings/tray"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_saveButton_clicked();
private:
    Ui::MainWindow *ui;
    int second;
    QTimer *timer;
    QSystemTrayIcon *trayIcon;
public slots:
    void updateTime();
};
#endif // MAINWINDOW_H

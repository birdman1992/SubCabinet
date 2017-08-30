#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QButtonGroup>
#include <qstringlist.h>

#include "controldevice.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    QString curId;
    QStringList validUsers;//合法用户列表

    ControlDevice* devices;
    QButtonGroup groupTitleLeft;
    QButtonGroup groupCtrlLock;

    void paintEvent(QPaintEvent *);
    void initDevices();
    void initTitleLeft();
    void initCtrlLock();
    void readUserList();//读取合法用户列表
    void addUser(QString id);//添加合法用户
    void lock();
    void unlock();
    bool isLocked();
    bool checkId(QString id);

private slots:
    void titleLeftClicked(int id);
    void ctrlLockClicked(int id);
    void readIdCard(QByteArray cardId);
};

#endif // MAINWIDGET_H

#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <qpainter.h>
#include <QSettings>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->stack->setCurrentIndex(0);
    this->setWindowFlags(Qt::FramelessWindowHint);

    initDevices();
    initTitleLeft();
    initCtrlLock();
    readUserList();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MainWidget::initDevices()
{
    devices = new ControlDevice(this);

    connect(devices, SIGNAL(cardReaderData(QByteArray)), this, SLOT(readIdCard(QByteArray)));
}

void MainWidget::initTitleLeft()
{
    groupTitleLeft.addButton(ui->save, 0);
    groupTitleLeft.addButton(ui->take, 1);
    groupTitleLeft.addButton(ui->admin, 2);
    groupTitleLeft.addButton(ui->pullOut, 3);
    ui->save->setChecked(true);

    connect(&groupTitleLeft, SIGNAL(buttonClicked(int)), this, SLOT(titleLeftClicked(int)));

}

void MainWidget::initCtrlLock()
{
    groupCtrlLock.addButton(ui->pushButton,0);
    groupCtrlLock.addButton(ui->pushButton_2,1);
    groupCtrlLock.addButton(ui->pushButton_3,2);
    groupCtrlLock.addButton(ui->pushButton_4,3);
    groupCtrlLock.addButton(ui->pushButton_5,4);
    groupCtrlLock.addButton(ui->pushButton_6,5);

    connect(&groupCtrlLock, SIGNAL(buttonClicked(int)), this, SLOT(ctrlLockClicked(int)));
}

void MainWidget::readUserList()
{
    QSettings settings("/home/users.ini",QSettings::IniFormat);
    int i = 0;

    int index = settings.beginReadArray("UserList");
    validUsers.clear();

    for(i=0; i<index; i++)
    {
        settings.setArrayIndex(i);
        QString idStr = settings.value("Id", QVariant(QString())).toString();

        if(idStr.isEmpty())
            continue;
        else
            validUsers<<idStr;
    }
    settings.endArray();

    qDebug()<<"[readUserList]"<<validUsers;
}

void MainWidget::addUser(QString id)
{
    if(id.isEmpty())
        return;

    if(checkId(id))
        return;

    validUsers<<id;
    qDebug()<<"addUser"<<id;

    QSettings settings("/home/users.ini",QSettings::IniFormat);

    int index = settings.beginReadArray("UserList");
    qDebug()<<index;
    settings.endArray();
    settings.beginWriteArray("UserList");
    settings.setArrayIndex(index);
    settings.setValue("Id", QVariant(id));
    settings.endArray();
    settings.sync();
}

void MainWidget::lock()
{
    ui->lock->show();
}

void MainWidget::unlock()
{
    ui->lock->hide();
}

bool MainWidget::isLocked()
{
    return !ui->lock->isHidden();
}

bool MainWidget::checkId(QString id)
{
    if(validUsers.isEmpty())
        return false;

    if(validUsers.indexOf(id) == -1)
        return false;

    return true;
}

void MainWidget::titleLeftClicked(int id)
{
    if(id == 3)
        ui->lock->show();
    else
        ui->stack->setCurrentIndex(0);
}

void MainWidget::ctrlLockClicked(int id)
{
    if(!ui->lock->isHidden())
        return;

    devices->openLock(0, id);
}

void MainWidget::readIdCard(QByteArray cardId)
{
    curId = QString(cardId);
    qDebug()<<"[readIdCard]"<<curId;
    qDebug()<<validUsers.isEmpty();

    if(validUsers.isEmpty())
    {
        unlock();
        addUser(curId);
    }
    else
    {
        if(isLocked())
        {
            if(checkId(curId))
                unlock();
        }
        else
        {
            if(!checkId(curId))
                addUser(curId);
        }
    }
}

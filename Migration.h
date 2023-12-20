#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Migration.h"
#include "channel.h"
#include "basedefine.h"

class Migration : public QMainWindow
{
    Q_OBJECT

public:
    Migration(QWidget *parent = nullptr);
    ~Migration();

private:
    Ui::MigrationClass ui;
};

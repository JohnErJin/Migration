#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets>
#include "RenderArea.h"
class Migration : public QDialog
{
    Q_OBJECT

public:
    Migration(QWidget *parent = nullptr);
    ~Migration();

private:
    RenderArea* renderArea_widget;
    QTabWidget* tabWidget;
    QDoubleSpinBox* lateralRate_spinBox;
    QDoubleSpinBox* forwardRate_spinBox;
    QDoubleSpinBox* verticalRate_spinBox;
    QCheckBox* showRange_checkBox;
    QCheckBox* showRate_checkBox;
    QPushButton* createMidLine_pushButton;
    QPushButton* migrate_pushButton;
    QPushButton* clear_pushButton;

private:
    void initUI();
};


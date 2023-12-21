#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include <QtCharts>
class Migration : public QDialog
{
    Q_OBJECT

public:
    Migration(QWidget *parent = nullptr);
    ~Migration();

private:
    QChart* chart;
    QChartView* chartView;
    QTabWidget* tabWidget;
    QSpinBox* lateralRate_spinBox;
    QSpinBox* forwardRate_spinBox;
    QSpinBox* verticalRate_spinBox;
    QCheckBox* showRange_checkBox;
    QCheckBox* showRate_checkBox;
    QPushButton* createMidLine_pushButton;
    QPushButton* remove_pushButton;
    QPushButton* clear_pushButton;

private:
    void initUI();
};


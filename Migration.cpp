#include "Migration.h"

Migration::Migration(QWidget *parent)
    : QDialog(parent)
{
    initUI();
}

Migration::~Migration()
{}

void Migration::initUI() {
    this->setWindowTitle(tr("Ǩ��"));
    this->resize(800, 600);
    QHBoxLayout* main = new QHBoxLayout;
    QHBoxLayout* h1 = new QHBoxLayout;
    QHBoxLayout* h2 = new QHBoxLayout;
    QHBoxLayout* h3 = new QHBoxLayout;
    QVBoxLayout* v1 = new QVBoxLayout;
    QWidget* basicTabWidget = new QWidget(this);
    basicTabWidget->resize(200, 600);
    lateralRate_spinBox = new QSpinBox();
    forwardRate_spinBox = new QSpinBox();
    verticalRate_spinBox = new QSpinBox();
    showRange_checkBox = new QCheckBox(tr("��ʾ�ӵ���Χ"));
    showRate_checkBox = new QCheckBox(tr("��ʾ���ʴ�С"));
    createMidLine_pushButton = new QPushButton(tr("��������"));
    remove_pushButton = new QPushButton(tr("Ǩ��"));
    clear_pushButton = new QPushButton(tr("���"));
    
    h1->addWidget(new QLabel(tr("����Ǩ����")));
    h1->addWidget(lateralRate_spinBox);
    h2->addWidget(new QLabel(tr("ǰ��Ǩ����")));
    h2->addWidget(forwardRate_spinBox);
    h3->addWidget(new QLabel(tr("����Ǩ����")));
    h3->addWidget(verticalRate_spinBox);
    v1->addLayout(h1);
    v1->addLayout(h2);
    v1->addLayout(h3);
    v1->addStretch(50);
    v1->addWidget(showRange_checkBox);
    v1->addWidget(showRate_checkBox);
    v1->addWidget(createMidLine_pushButton);
    v1->addWidget(remove_pushButton);
    v1->addWidget(clear_pushButton);
    basicTabWidget->setLayout(v1);
    
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(basicTabWidget, tr("����"));
    tabWidget->addTab(new QWidget, tr("����"));
    
    chart = new QChart();
    chartView = new QChartView(this);
    chartView->resize(600, 600);
    chartView->setChart(chart);

    main->addWidget(chartView);
    main->addWidget(tabWidget);
    this->setLayout(main);
}

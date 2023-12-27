#include "Migration.h"

Migration::Migration(QWidget *parent)
    : QDialog(parent)
{
    
    initUI();

    QObject::connect(lateralRate_spinBox, SIGNAL(valueChanged(double)), this, SLOT(renderArea_widget->setMigaLateralRate(double)));
    QObject::connect(forwardRate_spinBox, SIGNAL(valueChanged(double)), this, SLOT(renderArea_widget->setMigaForwardRate(double)));
    QObject::connect(verticalRate_spinBox, SIGNAL(valueChanged(double)), this, SLOT(renderArea_widget->setMigaUpRate(double)));

    QObject::connect(showRange_checkBox, SIGNAL(clicked(bool)), this, SLOT(renderArea_widget->setShowRange(bool)));
    QObject::connect(showRate_checkBox, SIGNAL(clicked(bool)), this, SLOT(renderArea_widget->setShowDir(bool)));

    QObject::connect(createMidLine_pushButton, SIGNAL(clicked()), this, SLOT(renderArea_widget->generalChannel_click()));
    QObject::connect(migrate_pushButton, SIGNAL(clicked()), this, SLOT(renderArea_widget->Migrate()));
    QObject::connect(clear_pushButton, SIGNAL(clicked()), this, SLOT(renderArea_widget->clear()));

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
    lateralRate_spinBox = new QDoubleSpinBox();
    forwardRate_spinBox = new QDoubleSpinBox();
    verticalRate_spinBox = new QDoubleSpinBox();
    showRange_checkBox = new QCheckBox(tr("��ʾ�ӵ���Χ"));
    showRate_checkBox = new QCheckBox(tr("��ʾ���ʴ�С"));
    createMidLine_pushButton = new QPushButton(tr("��������"));
    migrate_pushButton = new QPushButton(tr("Ǩ��"));
    clear_pushButton = new QPushButton(tr("���"));
    
    lateralRate_spinBox->setRange(0.0, 100.0);
    forwardRate_spinBox->setRange(0.0, 100.0);
    verticalRate_spinBox->setRange(0.0, 100.0);
    lateralRate_spinBox->setSingleStep(0.1);
    forwardRate_spinBox->setSingleStep(0.1);
    verticalRate_spinBox->setSingleStep(0.1);

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
    v1->addWidget(migrate_pushButton);
    v1->addWidget(clear_pushButton);
    basicTabWidget->setLayout(v1);
    
    tabWidget = new QTabWidget(this);
    tabWidget->resize(200, 600);
    tabWidget->addTab(basicTabWidget, tr("����"));
    tabWidget->addTab(new QWidget, tr("����"));
    
    renderArea_widget = new RenderArea(this);
    main->addWidget(renderArea_widget);
    main->addWidget(tabWidget);
    this->setLayout(main);
}


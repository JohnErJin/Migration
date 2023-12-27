#pragma once
#include <QtWidgets>
#include "channel.h"
#include "channelex.h"
#include "basedefine.h"
#include "curveinterp.h"
#include "util.h"

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget* parent = nullptr);

public slots:
    void generalChannel_click();
    void Migrate();
    void clear();
    
    //���ò���
    void setShowRange(bool isChecked) {
        if (isChecked == true) {
            this->show_range = true;
        }
        else {
            this->show_range = false;
        }
    }
    void setShowDir(bool isChecked) {
        if (isChecked == true) {
            this->show_dir = true;
        }
        else {
            this->show_dir = false;
        }
    }
    void setNumWidth(int num) {
        this->num_width = num;
    }
    void setMigaUpRate(double rate) {
        this->miga_up_rate = rate;
    }
    void setMigaForwardRate(double rate) {
        this->miga_forward_rate = rate;
    }
    void setMigaLateralRate(double rate) {
        this->miga_lateral_rate = rate;
    }

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QList<channel> channels;
    bool show_range;
    bool show_dir;
    double num_width;//C#: ��һ�� NumericUpDown �ؼ���ʵ����ͨ���������û���������ֵ�����縡������������
    double miga_up_rate;//����Ǩ����
    double miga_lateral_rate;//����Ǩ����
    double miga_forward_rate;//ǰ��Ǩ����
    ChParam* default;
private:
    
    Rect getRange();
    Rect getModeRange();
    void drawLine(QPainter& painter);
    void drawMigration(QPainter& painter);
    channelpar getInternalPar(double y, double zoneWidth, double mainlenth);
    void setChParam();
    
    
};


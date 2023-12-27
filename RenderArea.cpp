#include "RenderArea.h"
#include <QPainter>
#include <QPainterPath>

RenderArea::RenderArea(QWidget* parent)
    : QWidget(parent)
{
    // ���һ�� 0 �� qint64 �����ֵ֮��������
    //qint64 randomValue = QRandomGenerator::global()->generate();
    // ��������ȫ�ֵ����ӿ��ܲ��Ǳ�Ҫ�ġ� 
    //QRandomGenerator::global()�Ѿ���Qt�г�ʼ��������������������Qt���������ʱ���õġ��ڴ��������£�����Ҫ�ֶ��ı�ȫ�����ӡ�
    //QRandomGenerator::global()->seed(randomValue);
    this->resize(600, 600);
    //this->setChParam();//���ز�����ȡ
    QString filePath = QApplication::applicationDirPath() + "/defaultch.par";
    QFile file(filePath);
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray jsonData = file.readAll();
            file.close();

            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

            if (parseError.error == QJsonParseError::NoError && !jsonDoc.isNull())
            {
                QJsonObject jsonObj = jsonDoc.object();

                // Assuming ChParam has setters for each property
                default = new ChParam();
                default->setChWidth(jsonObj["ChWidth"].toDouble());
                default->setChThick(jsonObj["ChThick"].toDouble());
                default->setChWave(jsonObj["ChWave"].toDouble());
                default->setChAmplitude(jsonObj["ChAmplitude"].toDouble());
                default->setNodeMaxDis(jsonObj["NodeMaxDis"].toDouble());
                default->setMaxDis(jsonObj["MaxDis"].toDouble());
                default->setSearchRange(jsonObj["SearchRange"].toDouble());
            }
        }
    }

}

void RenderArea::Migrate() {
    while (true)
    {
        if (channels.size() > 0)
        {            
            for(int i=0;i< channels.size();i++)
            {
                channels[i].center_migration(miga_lateral_rate / 100.0, miga_forward_rate / 100.0, miga_up_rate / 100.0, num_width);            
            }
            this->update();
        }        
    }
}

void RenderArea::clear() {
    channels.clear();
    this->repaint();
}

void RenderArea::setChParam() {
    ChParam* _default = this->default;

    if (_default == nullptr)
    {
        QString filePath = QApplication::applicationDirPath() + "/defaultch.par";
        QFile file(filePath);

        if (file.exists())
        {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QByteArray jsonData = file.readAll();
                file.close();

                QJsonParseError parseError;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

                if (parseError.error == QJsonParseError::NoError && !jsonDoc.isNull())
                {
                    QJsonObject jsonObj = jsonDoc.object();

                    // Assuming ChParam has setters for each property
                    _default = new ChParam();
                    _default->setChWidth(jsonObj["ChWidth"].toDouble());
                    _default->setChThick(jsonObj["ChThick"].toDouble());
                    _default->setChWave(jsonObj["ChWave"].toDouble());
                    _default->setChAmplitude(jsonObj["ChAmplitude"].toDouble());
                    _default->setNodeMaxDis(jsonObj["NodeMaxDis"].toDouble());
                    _default->setMaxDis(jsonObj["MaxDis"].toDouble());
                    _default->setSearchRange(jsonObj["SearchRange"].toDouble());
                }
            }
        }
    }

    this->default = _default;
}
void RenderArea::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // ��ѡ�������
    this->resize(600, 600);
    // ��ͼ�߼�
    drawMigration(painter);
    drawLine(painter);
    // ��󣬿���ѡ����ø���� paintEvent����ȷ������Ļ�ͼ����Ҳ����ִ��
    QWidget::paintEvent(event);
}
Rect RenderArea::getRange() {
    int width = this->width();
    int height = this->height();
    //return new Rect(0, this.pictureEdit1.Width, 0, this.pictureEdit1.Height);
    return Rect(0, width, 0, height);
}
Rect RenderArea::getModeRange() {
    //int width = this.pictureEdit1.DisplayRectangle.Width;
    //int height = this.pictureEdit1.DisplayRectangle.Height;
    int width = this->width();
    int height = this->height();
    return Rect(0, width, 0, height);
}
void RenderArea::drawLine(QPainter & painter)
{
    QPen mainPen(QColor(255, 12, 1));
    painter.setPen(mainPen);

    if (!channels.isEmpty())
    {
        for (int index = 0; index < channels.size(); index++)
        {
            auto item = channels[index];
            auto center = item.get_centerline();
            auto par = item.get_par();
            int centerCount = center->size();//���ߵĵ�ĸ��������ɵ����
            if (centerCount > 1)
            {
                QVector<QPointF> lines(centerCount);

                for (int i = 0; i < centerCount; i++)
                {
                    lines[i].setX(static_cast<float>(center->getX(i)));
                    lines[i].setY(static_cast<float>(center->getY(i)));
                    QRectF rect(static_cast<float>(center->getX(i)) - 2, static_cast<float>(center->getY(i)) - 2, 4, 4);
                    painter.drawPie(rect, 0, 360);
                }
            }
        }
    }
}

void RenderArea::drawMigration(QPainter& painter) {
    QPen bufferPen(Qt::black);
    bufferPen.setStyle(Qt::DashLine);
    bufferPen.setDashPattern({ 5, 10 });

    double width = this->num_width;
    if (width > 0) {
        foreach(const auto & item, channels) {
            // ��ȡ�����ͷ�Χ
            // ���� ymin �� ymax
            const channelpar* par = item.get_par();
            Rect range = getRange();
            auto ymin = std::max(1, static_cast<int>(par->get_zone().get_start_dot().y - width));
            auto ymax = std::min(static_cast<int>(range.getYmax() - 1), static_cast<int>(par->get_zone().get_start_dot().y + width));
            painter.setPen(bufferPen);
            painter.drawLine(QPoint(0, ymin),QPoint(static_cast<int>(range.getXmax()), ymin));
            painter.drawLine(QPoint(0, ymax),QPoint(static_cast<int>(range.getXmax()), ymax));
        }
    }

    if (show_range == true) {
        foreach(const auto & item, channels) {
            // ��ȡ����
            const channelpar* par = item.get_par();
            auto buffercenter = item.buffer_centerline(par->get_width() / 2);
            // �������
            QPolygonF buffer(buffercenter->size());//QPolygonF�̳�����QVector <QPointF>
            for (int i = 0; i < buffercenter->size(); ++i) {
                buffer[i] = QPointF(buffercenter->getX(i), buffercenter->getY(i));
            }
            painter.setBrush(Qt::gray);
            painter.drawPolygon(buffer);
        }
    }

    if (show_dir == true) {
        foreach(const auto & item, channels) {
            // ��ȡ�����ߺ�������Ϣ
            // ���� dirs
            auto center = item.get_centerline();
            auto cur = item.get_curvatures();//����
            QList<QPolygonF> dirs;
            if (center->size() > 2) {
                for (int i = 0; i < center->size(); i++) {
                    auto dir = cur->at(i).get_dir();
                    QPolygonF line(2);
                    line[0] = QPointF(center->getX(i), center->getY(i));
                    line[1] = QPointF(center->getX(i) + cur->at(i).get_p() * 30 * dir.x, center->getY(i) + cur->at(i).get_p() * 30 * dir.y);
                    dirs.append(line);
                }
            }
            painter.setPen(Qt::green);
            foreach(const auto & dir, dirs) {
                painter.drawPolygon(dir);
            }
        }
    }
}
void RenderArea::generalChannel_click() {//��������
    auto range = getRange();
    QList<channelpar> pars;
    auto par = getInternalPar(150, default->getChAmplitude() * 2, (range.getXmax() - range.getXmin()));
    pars.append(par);
    for (int j = 0; j < pars.size(); j++)
    {
        channel ch = pars[j];
        auto wells = new well3d_sequence(nullptr);
        ch.build_center_nodes(wells);
        channels.append(ch);
    }
    this->repaint();
}

channelpar RenderArea::getInternalPar(double y, double zoneWidth, double mainlenth) {
    //auto size = getModeRange();
    auto range = getRange();
    channelzone zone(0, geos::geom::Coordinate::Coordinate(-0.5 * default->getChWidth(), y, 0), mainlenth);//Coordinate Ϊ dot3D
    channelpar channel(zone, modelpar(1, 1, 8, -99), default->getChWidth(), default->getChThick(), default->getChWave(), default->getChAmplitude());
    return channel;
}

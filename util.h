#pragma once
class Rect
{
private:
    double xmin;
    double xmax;
    double ymin;
    double ymax;

public:
    Rect(double xmin, double xmax, double ymin, double ymax)
        : xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {}

    double getXmin() const { return xmin; }
    void setXmin(double v) { xmin = v; }

    double getXmax() const { return xmax; }
    void setXmax(double v) { xmax = v; }

    double getYmin() const { return ymin; }
    void setYmin(double v) { ymin = v; }

    double getYmax() const { return ymax; }
    void setYmax(double v) { ymax = v; }
};

class ChParam
{

private:
    double chWidth;
    double chThick;
    double chWave;
    double chAmplitude;
    double nodeMaxDis;
    double maxDis;
    double searchRange;

public:
    ChParam() : chWidth(0.0), chThick(0.0), chWave(0.0),
        chAmplitude(0.0), nodeMaxDis(0.0), maxDis(0.0), searchRange(0.0) {
    };
    ChParam(double chWidth,
        double chThick,
        double chWave,
        double chAmplitude,
        double nodeMaxDis,
        double maxDis,
        double searchRange)
        : chWidth(0.0), chThick(0.0), chWave(0.0),
        chAmplitude(0.0), nodeMaxDis(0.0), maxDis(0.0), searchRange(0.0) {}

    double getChWidth() const { return chWidth; }
    void setChWidth(double value) { chWidth = value; }

    double getChThick() const { return chThick; }
    void setChThick(double value) { chThick = value; }

    double getChWave() const { return chWave; }
    void setChWave(double value) { chWave = value; }

    double getChAmplitude() const { return chAmplitude; }
    void setChAmplitude(double value) { chAmplitude = value; }

    double getNodeMaxDis() const { return nodeMaxDis; }
    void setNodeMaxDis(double value) { nodeMaxDis = value; }

    double getMaxDis() const { return maxDis; }
    void setMaxDis(double value) { maxDis = value; }

    double getSearchRange() const { return searchRange; }
    void setSearchRange(double value) { searchRange = value; }
};



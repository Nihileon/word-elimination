#ifndef RADIUSPROGRESSBAR_H
#define RADIUSPROGRESSBAR_H

#include <QProgressBar>
#include <QPainter>

class RadiusProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit RadiusProgressBar(QWidget *parent) : QProgressBar(parent){
        setMinimum(0);
        setMaximum(100);
        setValue(0);
    }

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE{
        QPainter p(this);
        QRect rect = QRect(0, 0, width(), height()/2);
    //    QRect textRect = QRect(0, height()/2, width(), height()/2);
        const double k = static_cast<double>(value() - minimum()) / (maximum()-minimum());
        int x = static_cast<int>(rect.width() * k);

        QRect fillRect = rect.adjusted(0, 0, x-rect.width(), 0);

    //    QString valueStr = QString("%1%").arg(QString::number(value()));
        QPixmap buttomMap = QPixmap(":/resource/radius_back.png");
        QPixmap fillMap = QPixmap(":/resource/radius_front.png");

        //画进度条
        p.drawPixmap(rect, buttomMap);
        p.drawPixmap(fillRect, fillMap, fillRect);

        //画文字
        QFont f = QFont("",15, QFont::Bold);
        p.setFont(f);
        p.setPen(QColor("#555555"));
    }
};

#endif // RADIUSPROGRESSBAR_H

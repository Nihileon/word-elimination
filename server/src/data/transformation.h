#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QVector>
#include <QString>
#include <string>

using std::string;
class transformation {
public:
static std::string tableToString(const QVector<QVector<QString>> &table) {
    QString data;
    for (auto i = table.begin(); i < table.end(); i++) {
        for (auto j = i->begin(); j < i->end(); j++) {
            data.append(*j);
            if (j != i->end() - 1) {
                data.append(",");
            }
        }
        if (i != table.end() - 1) {
            data.append("|");
        }
    }
    return data.toStdString();
}


static QVector<QVector<QString>> stringToTable(const string &data) {
    QVector<QVector<QString>> table;
    if (data == "") {
        return table;
    }
    QStringList list = QString::fromStdString(data).split("|");
    for (auto i : list) {
        QVector<QString> tableLine;
        QStringList line = i.split(",");
        for (auto j : line) {
            tableLine.push_back(j);
        }
        table.push_back(tableLine);
    }
    return table;
}

};
#endif // TRANSFORM_H

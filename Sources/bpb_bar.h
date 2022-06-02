#ifndef BPB_BAR_H
#define BPB_BAR_H

#include <QObject>
#include <QQmlProperty>
#include <QVector>
#include <QFile>
#include <QDebug>


#define BPB_LABEL_PATH "Test/test1.txt"

#define BPB_DEFAULT_BACKGROUND_COLOR    "#222222"
#define BPB_DEFAULT_LABEL_COLOR         "#aaaaaa"
#define BPB_DEFAULT_UNDERLINE_COLOR     "#666666"
#define BPB_DEFAULT_ACTION              ""

typedef struct BpbProperty
{
    QString     background_color;
    QString     label_color;
    QString     underline_color;
    bool        have_underline;
    QString     action;
}BpbProperty;

typedef struct BpbLabel
{
    QString     content;
    BpbProperty properties;
}PbLabel;

class BpbBar : public QObject
{
    Q_OBJECT
public:
    explicit BpbBar(QObject *root, QObject *parent = nullptr);

private:
    void loadContent(QObject *list_ui);
    BpbProperty parseProperty(QString property);

private:
    QObject *left_bar_ui;
    QVector<BpbLabel> labels;
};

#endif // BPB_BAR_H

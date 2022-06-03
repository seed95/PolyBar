#ifndef BPB_BAR_H
#define BPB_BAR_H

#include <QObject>
#include <QQmlProperty>
#include <QVector>
#include <QFile>
#include <QDebug>


#define BPB_LEFT_LABEL_PATH     "Test/test1.txt"
#define BPB_RIGHT_LABEL_PATH    "Test/test4.txt"

#define BPB_DEFAULT_BACKGROUND_COLOR    "#000000"
#define BPB_DEFAULT_LABEL_COLOR         "#dfdfdf"
#define BPB_DEFAULT_UNDERLINE_COLOR     "#f3c84a"
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

private slots:
    void executeCommand(QString action);

private:
    void loadLabels(QString path, QObject *list_ui, bool reverse=false);
    void updateProperty(QString rawProperty, BpbProperty *properties);
    void showLabels(QVector<BpbLabel> labels, QObject *list_ui, bool reverse);

private:
    QObject *left_bar_ui;
    QObject *right_bar_ui;
};

#endif // BPB_BAR_H

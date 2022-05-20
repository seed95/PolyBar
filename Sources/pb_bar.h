#ifndef PB_BAR_H
#define PB_BAR_H

#include <QObject>
#include <QQmlProperty>

class PbBar : public QObject
{
    Q_OBJECT
public:
    explicit PbBar(QObject *root, QObject *parent = nullptr);

private:
    void loadContent(QObject *list_ui);

private:
    QObject *left_bar_ui;
};

#endif // PB_BAR_H

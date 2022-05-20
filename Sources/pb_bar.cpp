#include "pb_bar.h"

PbBar::PbBar(QObject *root, QObject *parent) : QObject(parent)
{
    left_bar_ui = root->findChild<QObject*>("LeftBar");



    loadContent(left_bar_ui);
    loadContent(left_bar_ui);
    loadContent(left_bar_ui);
    loadContent(left_bar_ui);


}

void PbBar::loadContent(QObject *list_ui)
{
    QString background = "#222222";
    QString label_color = "#aaaaaa";
    bool have_underline = true;
    QString text = "sajad chetory";
    QString action = "run another cmd";


    QQmlProperty::write(list_ui, "labelBackgroundColor", background);
    QQmlProperty::write(list_ui, "labelHaveUnderline", label_color);
    QQmlProperty::write(list_ui, "labelTextColor", have_underline);
    QQmlProperty::write(list_ui, "labelContent", text);
    QQmlProperty::write(list_ui, "labelActionString", action);
    QMetaObject::invokeMethod(left_bar_ui, "addLabel");
}

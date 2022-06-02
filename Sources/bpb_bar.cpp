#include "bpb_bar.h"

BpbBar::BpbBar(QObject *root, QObject *parent) : QObject(parent)
{
    left_bar_ui = root->findChild<QObject*>("LeftBar");



    loadContent(left_bar_ui);
//    loadContent(left_bar_ui);
//    loadContent(left_bar_ui);
//    loadContent(left_bar_ui);


}

void BpbBar::loadContent(QObject *list_ui)
{
//    QString background = "#222222";
//    QString label_color = "#aaaaaa";
//    bool have_underline = true;
//    QString text = "sajad chetory";
//    QString action = "run another cmd";


//    QQmlProperty::write(list_ui, "labelBackgroundColor", background);
//    QQmlProperty::write(list_ui, "labelHaveUnderline", label_color);
//    QQmlProperty::write(list_ui, "labelTextColor", have_underline);
//    QQmlProperty::write(list_ui, "labelContent", text);
//    QQmlProperty::write(list_ui, "labelActionString", action);
//    QMetaObject::invokeMethod(left_bar_ui, "addLabel");



    labels.clear();
    QFile label_file(BPB_LABEL_PATH);
    if(label_file.open(QIODevice::ReadOnly))
    {
        QString data = label_file.readAll();
        qDebug() << data;

        BpbProperty properties;
        properties.background_color = BPB_DEFAULT_BACKGROUND_COLOR;
        properties.label_color = BPB_DEFAULT_LABEL_COLOR;
        properties.underline_color = BPB_DEFAULT_UNDERLINE_COLOR;
        properties.have_underline = false;
        properties.action = BPB_DEFAULT_ACTION;

        int current_index = 0;
        int start_property_index = 0;
        while (current_index<data.length())
        {
            BpbLabel label;
            label.properties = properties;

            // Find start index of property
            QString start_property_characters = "%{";
            start_property_index = data.indexOf(start_property_characters, current_index);

            // Find end index of property
            QString end_property_characters = "}";
            int end_property_index = data.indexOf(end_property_characters, start_property_index);
            int n;
            if (end_property_index == -1)
            {
                qDebug() << "end of property not found!!!!!";
                n = -1;
            }
            else
            {
                n = end_property_index - start_property_index;
            }

            // Get substring for property data
            QString property_data = data.mid(start_property_index, n);

            // Get substring for label content
            n = (start_property_index==-1) ? start_property_index:(start_property_index - current_index);
            //TODO check midRef method
            label.content = data.mid(current_index, n);
            labels.append(label);

            // Update property
            properties = parseProperty(property_data);

            // Update current index
            current_index = end_property_index + end_property_characters.length();
        }

        foreach (auto label, labels )
        {
            qDebug() << label.content << label.properties.label_color;
        }
    }
    else
    {
        qDebug() << "Cann't open" + QString(BPB_LABEL_PATH);
    }

}

BpbProperty BpbBar::parseProperty(QString property)
{
    QString backround_property = "B";
    QString foreground_property = "F";
    QString action_property = "A";
    QString underline_property = "U";

    BpbProperty properties;
    properties.background_color = BPB_DEFAULT_BACKGROUND_COLOR;
    properties.label_color = BPB_DEFAULT_LABEL_COLOR;
    properties.underline_color = BPB_DEFAULT_UNDERLINE_COLOR;
    properties.have_underline = false;
    properties.action = BPB_DEFAULT_ACTION;

    if (property.startsWith(backround_property, Qt::CaseInsensitive))
    {
        properties.background_color = property.mid(backround_property.length());
    }
    else if (property.startsWith(foreground_property, Qt::CaseInsensitive))
    {
        properties.label_color = property.mid(foreground_property.length());
    }
    else
    {
        qDebug() << "property not implemented";
    }

    return properties;
}


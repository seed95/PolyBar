#include "bpb_bar.h"

BpbBar::BpbBar(QObject *root, QObject *parent) : QObject(parent)
{
    left_bar_ui =   root->findChild<QObject*>("LeftBar");
    right_bar_ui =  root->findChild<QObject*>("RightBar");

    connect(left_bar_ui, SIGNAL(executeAction(QString)), this, SLOT(executeCommand(QString)));
    connect(right_bar_ui, SIGNAL(executeAction(QString)), this, SLOT(executeCommand(QString)));

    loadLabels(BPB_LEFT_LABEL_PATH, left_bar_ui);
    loadLabels(BPB_RIGHT_LABEL_PATH, right_bar_ui, true);
}

/***************** Execute Action Slot *****************/
void BpbBar::executeCommand(QString action)
{
    qDebug() << "execute" << action;
}

/***************** Private Functions *****************/
void BpbBar::loadLabels(QString path, QObject *list_ui, bool reverse)
{
    QFile label_file(path);
    if (label_file.open(QIODevice::ReadOnly))
    {
        QString data = label_file.readAll();
//        qDebug() << data;

        QVector<BpbLabel> labels;
        BpbProperty properties;
        properties.background_color = BPB_DEFAULT_BACKGROUND_COLOR;
        properties.label_color = BPB_DEFAULT_LABEL_COLOR;
        properties.underline_color = BPB_DEFAULT_UNDERLINE_COLOR;
        properties.have_underline = false;
        properties.action = BPB_DEFAULT_ACTION;

        int current_index = 0;

        QString start_property_characters = "%{", end_property_characters = "}";
        int start_property_index, end_property_index;
        while (current_index<data.length())
        {
            BpbLabel label;
            label.properties = properties;

            // Find start index of property
            start_property_index = data.indexOf(start_property_characters, current_index);

            // Get substring for label content
            int n;
            if (start_property_index == -1)
            {
                n = -1;
            }
            else
            {
                n = start_property_index - current_index;
            }
            //TODO check midRef method
            label.content = data.mid(current_index, n);
            labels.append(label);

            // All labels are read
            if (start_property_index == -1)
            {
                break;
            }

            // Find end index of property
            start_property_index = start_property_index + start_property_characters.length();
            end_property_index = data.indexOf(end_property_characters, start_property_index);
            if (end_property_index == -1)
            {
                //TODO invalid file format
                qDebug() << "end of property not found!!!!!";
                n = -1;
            }
            else
            {
                n = end_property_index - start_property_index;
            }

            // Get substring for raw property
            QString raw_property = data.mid(start_property_index, n);

            // Update properties
            updateProperty(raw_property, &properties);

            // Update current index
            current_index = end_property_index + end_property_characters.length();
        }

        showLabels(labels, list_ui, reverse);
    }
    else
    {
        qDebug() << "Cann't open" + path;
    }

}

void BpbBar::updateProperty(QString rawProperty, BpbProperty *properties)
{
//    qDebug() << "property" << rawProperty;

    //Note: unset property must be checked first
    QString unset_backround_property = "B-";
    QString set_backround_property = "B";

    //Note: unset property must be checked first
    QString unset_foreground_property = "F-";
    QString set_foreground_property = "F";

    //Note: set must be checked first
    QString set_action_property = "A1:";
    QString unset_action_property = "A";

    QString set_underline_property = "+U";
    QString unset_underline_property = "-U";
    QString underline_property = "U";

    // Background
    if (rawProperty.startsWith(unset_backround_property, Qt::CaseInsensitive))
    {
        properties->background_color = BPB_DEFAULT_BACKGROUND_COLOR;
    }
    else if (rawProperty.startsWith(set_backround_property, Qt::CaseInsensitive))
    {
        properties->background_color = rawProperty.mid(set_backround_property.length());
    }
    // Foreground
    else if (rawProperty.startsWith(unset_foreground_property, Qt::CaseInsensitive))
    {
        properties->label_color = BPB_DEFAULT_LABEL_COLOR;
    }
    else if (rawProperty.startsWith(set_foreground_property, Qt::CaseInsensitive))
    {
        properties->label_color = rawProperty.mid(set_foreground_property.length());
    }
    // Action
    else if (rawProperty.startsWith(set_action_property, Qt::CaseInsensitive))
    {
        int n = rawProperty.length() - set_action_property.length() - 1;// end of property contain ':'
        properties->action = rawProperty.mid(set_action_property.length(), n);
    }
    else if (rawProperty.startsWith(unset_action_property, Qt::CaseInsensitive))
    {
        properties->action = BPB_DEFAULT_ACTION;
    }
    // Underline
    else if (rawProperty.startsWith(set_underline_property, Qt::CaseInsensitive))
    {
        properties->have_underline = true;
    }
    else if (rawProperty.startsWith(unset_underline_property, Qt::CaseInsensitive))
    {
        properties->have_underline = false;
    }
    else if (rawProperty.startsWith(underline_property, Qt::CaseInsensitive))
    {
        properties->underline_color = rawProperty.mid(underline_property.length());
    }
    else
    {
        qDebug() << "property not implemented" << rawProperty;
    }

}

void BpbBar::showLabels(QVector<BpbLabel> labels, QObject *list_ui, bool reverse)
{
    QMetaObject::invokeMethod(list_ui, "clearLabels");

    if (reverse)
    {
        for(int i=labels.length()-1 ; i>=0 ; i--)
        {
            QQmlProperty::write(list_ui, "labelBackgroundColor", labels[i].properties.background_color);
            QQmlProperty::write(list_ui, "labelHaveUnderline", labels[i].properties.have_underline);
            QQmlProperty::write(list_ui, "labelTextColor", labels[i].properties.label_color);
            QQmlProperty::write(list_ui, "labelContent", labels[i].content);
            QQmlProperty::write(list_ui, "labelActionString", labels[i].properties.action);
            QMetaObject::invokeMethod(list_ui, "addLabel");
        }
    }
    else
    {
        foreach (auto label, labels)
        {
            QQmlProperty::write(list_ui, "labelBackgroundColor", label.properties.background_color);
            QQmlProperty::write(list_ui, "labelHaveUnderline", label.properties.have_underline);
            QQmlProperty::write(list_ui, "labelTextColor", label.properties.label_color);
            QQmlProperty::write(list_ui, "labelContent", label.content);
            QQmlProperty::write(list_ui, "labelActionString", label.properties.action);
            QMetaObject::invokeMethod(list_ui, "addLabel");
        }
    }
}

#ifndef WIDGET_H
#define WIDGET_H

#include "words.h"

#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QStringList wordList;

private slots:

    void on_pushButton_pressed();

    void on_pushButton_letter_pressed(QPushButton &button);

    void updateCounter();

    void setUpWord();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

#include "widget.h"
#include "words.h"
#include <wchar.h>
#include "./ui_widget.h"

#include <QChar>

Word* word;
int falseGuesses = 0;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    setUpWord();
    ui->setupUi(this);
    ui->comboBox->addItems(wordList);
    QPushButton* letterButtons[33] = {
        ui->pushButton_1,
        ui->pushButton_2,
        ui->pushButton_3,
        ui->pushButton_4,
        ui->pushButton_5,
        ui->pushButton_6,
        ui->pushButton_7,
        ui->pushButton_8,
        ui->pushButton_9,
        ui->pushButton_10,
        ui->pushButton_11,
        ui->pushButton_12,
        ui->pushButton_13,
        ui->pushButton_14,
        ui->pushButton_15,
        ui->pushButton_16,
        ui->pushButton_17,
        ui->pushButton_18,
        ui->pushButton_19,
        ui->pushButton_20,
        ui->pushButton_21,
        ui->pushButton_22,
        ui->pushButton_23,
        ui->pushButton_24,
        ui->pushButton_25,
        ui->pushButton_26,
        ui->pushButton_27,
        ui->pushButton_28,
        ui->pushButton_29,
        ui->pushButton_30,
        ui->pushButton_31,
        ui->pushButton_32,
        ui->pushButton_33
    };
    for(QPushButton* button: letterButtons) {
        connect(button, &QPushButton::pressed,
                this, [=](){ this->on_pushButton_letter_pressed(*button);});
    }
    connect(ui->pushButton_back, &QPushButton::pressed, this, [=](){
        for(QPushButton* button: letterButtons) {
            (*button).show();
        }
        ui->stackedWidget->setCurrentIndex(0);
        falseGuesses = 0;
        setUpWord();
        ui->label_5->setText(word->outputMaskedWord());
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    QString selectedWord = ui->comboBox
            ->itemText(ui->comboBox->currentIndex());
    word->setWord(selectedWord);
    ui->label_5->setText(word->outputMaskedWord());
    updateCounter();
    ui->progressBar->setValue(falseGuesses);
}

void Widget::updateCounter()
{
    wchar_t label_4_text[20] = L"Осталось ошибок: ";
    ui->label_4->setText(
        QString::fromWCharArray(label_4_text) + QString::number(6-falseGuesses)
    );
}

void Widget::setUpWord()
{
    word = new Word();
    wordList.clear();
    for(const wchar_t* word : word->list) {
        wordList.append(QString::fromWCharArray(word));
    }
}

void Widget::on_pushButton_letter_pressed(QPushButton &button)
{
    button.hide();
    QString letter = button.text();
    bool success = word->tryGuess(letter[0]);
    if(!success){
        falseGuesses++;
        ui->progressBar->setValue(falseGuesses);
        updateCounter();
        if(falseGuesses > 5) {
            ui->label_7->setText("Игрок 1 выиграл");
            ui->stackedWidget->setCurrentIndex(2);
        }
    }
    else {
        ui->label_5->setText(word->outputMaskedWord());
        if(word->isWordGuessed()){
            ui->label_7->setText("Игрок 2 выиграл");
            ui->stackedWidget->setCurrentIndex(2);
        }
    }
}


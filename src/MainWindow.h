#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QFontDatabase>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = (QWidget*)nullptr, Qt::WindowFlags f = {0});

private:
    QLabel* enteredNumberLabel;
    QLabel* typeOperation;
    QLabel* generalDigitalNumber;
    double currentDigitalNumber = 0;

    QPushButton* createButton(const QString& text, const QFont btnFont);

    void digitalNumberClick();
    void operations();
    void mathOperations();


};
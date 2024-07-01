#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
    enteredNumberLabel = new QLabel("0", this);
    typeOperation = new QLabel(this);
    generalDigitalNumber = new QLabel("", this);




    int fontId = QFontDatabase::addApplicationFont(":/Calculator.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily);
    QFont btnFont(fontFamily);
    QFont generalFont(fontFamily);
    customFont.setBold(true);
    customFont.setPointSize(36);
    generalFont.setPointSize(20);


    enteredNumberLabel->setFont(customFont);
    enteredNumberLabel->setAlignment(Qt::AlignRight);
    enteredNumberLabel->setMinimumHeight(50);
    enteredNumberLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    enteredNumberLabel->setMouseTracking(true);
    generalDigitalNumber->setFont(generalFont);
    generalDigitalNumber->setAlignment(Qt::AlignRight);
    typeOperation->setFont(generalFont);


    QGridLayout* layout = new QGridLayout(this);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addStretch(); 
    hLayout->addWidget(generalDigitalNumber);
    hLayout->addSpacing(5); 
    hLayout->addWidget(typeOperation);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addSpacing(2); 
    vLayout->addWidget(enteredNumberLabel);
    
    layout->addLayout(vLayout, 0, 0, 1, 4);

    QStringList buttonLabels = {
        "CE", "C","⌫", "÷",
        "7", "8", "9", "X",
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "+/_", "0", ".", "="
    };

    int pos = 0;
    for (int row = 1; row <= 5; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (pos >= buttonLabels.size()) break;
            QPushButton* button = createButton(buttonLabels[pos], fontFamily);
            layout->addWidget(button, row, col);
            ++pos;
        }
    }

    setLayout(layout);
}

QPushButton* MainWindow::createButton(const QString& text, const QFont btnFont) {
    QPushButton* button = new QPushButton(text, this);
    if (text[0].isDigit() || text == ".") {
        connect(button, &QPushButton::clicked, this, &MainWindow::digitalNumberClick);
    }
    if (text == "=" || text == "-" || text == "+" || text == "X" || text == "÷") {
        connect(button, &QPushButton::clicked, this, &MainWindow::mathOperations);
    }
    if (text == "+/_" || text == "CE" || text == "C" || text == "⌫") {
        connect(button, &QPushButton::clicked, this, &MainWindow::operations);
    }
    if (text == "CE" || text == "C" || text == "÷") {
        button->setStyleSheet("background-color: #FF5733; color: white; font-weight: bold; font: 16pt");
    }
    else if (text == "⌫" ) {
        button->setStyleSheet("background-color: #FF5733; color: white; font-weight: bold; font: 14pt");
    }
    else if (text == "X" || text == "-" || text == "+" || text == "=") {
        button->setStyleSheet("background-color: #013220; color: white; font-weight: bold; font: 24pt");
    }
    else {
        button->setStyleSheet("background-color: #3375FF; color: white; font-weight: bold; font: 24pt");
    }
    button->setFont(btnFont);
    return button;
}

void MainWindow::digitalNumberClick()
{
    if (enteredNumberLabel->text().size() < 13) {
        QPushButton* clickNumberButton = qobject_cast<QPushButton*>(sender());
        if (!enteredNumberLabel->text().contains(".") && clickNumberButton->text() == ".") {
            enteredNumberLabel->setText(enteredNumberLabel->text() + ".");
        }
        else if(clickNumberButton->text() != ".") {
            currentDigitalNumber = (enteredNumberLabel->text() + clickNumberButton->text()).toDouble();
            QString numbersString = QString::number(currentDigitalNumber, 'g', 13);
            enteredNumberLabel->setText(numbersString);
        }
    }
    
}

void MainWindow::operations()
{
    QPushButton* clickButton = qobject_cast<QPushButton*>(sender());
    QString numbersString;
    if(clickButton->text() == "+/_") 
        currentDigitalNumber = (enteredNumberLabel->text()).toDouble() * -1;
    else if (clickButton->text() == "CE" || clickButton->text() == "C")
        currentDigitalNumber = 0;
    else if (clickButton->text() == "C")
    {
        generalDigitalNumber->setText("");
        typeOperation->setText("");
    }
    else if (clickButton->text() == "⌫")
    {
        numbersString = QString::number(currentDigitalNumber, 'g', 13);
        if (!numbersString.isEmpty() && currentDigitalNumber != 0) {
            numbersString.chop(1); 
            currentDigitalNumber = numbersString.toDouble();
        }
    }
    numbersString = QString::number(currentDigitalNumber, 'g', 13);
    enteredNumberLabel->setText(numbersString);
}
void MainWindow::mathOperations()
{
    QPushButton* clickButton = qobject_cast<QPushButton*>(sender());
    QString operation = typeOperation->text();
    double generalNumber = generalDigitalNumber->text().toDouble();

    if (operation == "÷")
        currentDigitalNumber = generalNumber / currentDigitalNumber;
    else if (operation == "X")
        currentDigitalNumber = generalNumber * currentDigitalNumber;
    else if (operation == "-")
        currentDigitalNumber = generalNumber - currentDigitalNumber;
    else if (operation == "+")
        currentDigitalNumber = generalNumber + currentDigitalNumber;

    QString buttonText = clickButton->text();
    QString numbersString = QString::number(currentDigitalNumber, 'g', 13);

    if (buttonText == "=" && !operation.isEmpty())
    {
        enteredNumberLabel->setText(numbersString);
        currentDigitalNumber = 0;
        generalDigitalNumber->setText("");
        typeOperation->setText("");
    }
    else if((enteredNumberLabel->text() != "0" || !generalDigitalNumber->text().isEmpty()) && buttonText != "=")
    {
        typeOperation->setText(buttonText);
        generalDigitalNumber->setText(numbersString);

        currentDigitalNumber = 0;
        enteredNumberLabel->setText(QString::number(currentDigitalNumber, 'g', 13));
    }
}
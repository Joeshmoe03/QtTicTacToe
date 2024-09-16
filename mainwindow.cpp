#include "mainwindow.h"

#include <QGridLayout>
#include <QtWidgets>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    QWidget *center = new QWidget;
    setCentralWidget(center);

    // set the grid layout with center
    QGridLayout *gridLayout = new QGridLayout(center);

    // x can start the game
    playerTurn = true;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = "";
        }
    }

    // buttons are named with row/column convention
    button00 = new QPushButton("");
    button01 = new QPushButton("");
    button02 = new QPushButton("");
    button10 = new QPushButton("");
    button11 = new QPushButton("");
    button12 = new QPushButton("");
    button20 = new QPushButton("");
    button21 = new QPushButton("");
    button22 = new QPushButton("");

    // arranging buttons in our grid layout
    gridLayout->addWidget(button00, 0, 0);
    gridLayout->addWidget(button01, 0, 1);
    gridLayout->addWidget(button02, 0, 2);
    gridLayout->addWidget(button10, 1, 0);
    gridLayout->addWidget(button11, 1, 1);
    gridLayout->addWidget(button12, 1, 2);
    gridLayout->addWidget(button20, 2, 0);
    gridLayout->addWidget(button21, 2, 1);
    gridLayout->addWidget(button22, 2, 2);

    // Use lambda function for specifying some behavior for changing button text and updating game turn + check win condition
    // NOTE: is there better widget/approach for doing this? https://stackoverflow.com/questions/19719397/qt-slots-and-c11-lambda
    connect(button00, &QPushButton::clicked, this, [this]() {tileClicked(button00, 0, 0); });
    connect(button01, &QPushButton::clicked, this, [this]() {tileClicked(button01, 0, 1); });
    connect(button02, &QPushButton::clicked, this, [this]() {tileClicked(button02, 0, 2); });
    connect(button10, &QPushButton::clicked, this, [this]() {tileClicked(button10, 1, 0); });
    connect(button11, &QPushButton::clicked, this, [this]() {tileClicked(button11, 1, 1); });
    connect(button12, &QPushButton::clicked, this, [this]() {tileClicked(button12, 1, 2); });
    connect(button20, &QPushButton::clicked, this, [this]() {tileClicked(button20, 2, 0); });
    connect(button21, &QPushButton::clicked, this, [this]() {tileClicked(button21, 2, 1); });
    connect(button22, &QPushButton::clicked, this, [this]() {tileClicked(button22, 2, 2); });
}

MainWindow::~MainWindow() {}

void MainWindow::tileClicked(QPushButton* button, int row, int col) {
    QString currentPlayer = playerTurn ? "X" : "O";

    // set the string according to who's turn it is
    button->setText(currentPlayer);
    board[row][col] = currentPlayer;

    // disable the button and swap the turn
    button->setDisabled(true);
    playerTurn = !playerTurn;

    // victory or stalemate condition means reset
    if (checkWin(currentPlayer) || boardFull()) {
        qDebug() << "GAME OVER!";
        resetBoard();
    }
}

bool MainWindow::checkWin(QString player) {
    // check all rows, columns, and diagonals for victory conditions
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    return false;
}

bool MainWindow::boardFull() {
    // chck that legal move still possible
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == "") {
                return false;

            }
        }
    }
    return true;
}

void MainWindow::resetBoard() {
    // wipe board at end and reset game
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = "";
        }
    }

    button00->setText("");
    button00->setEnabled(true);
    button01->setText("");
    button01->setEnabled(true);
    button02->setText("");
    button02->setEnabled(true);
    button10->setText("");
    button10->setEnabled(true);
    button11->setText("");
    button11->setEnabled(true);
    button12->setText("");
    button12->setEnabled(true);
    button20->setText("");
    button20->setEnabled(true);
    button21->setText("");
    button21->setEnabled(true);
    button22->setText("");
    button22->setEnabled(true);

    playerTurn = true;
}



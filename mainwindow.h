#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPushButton *button00;
    QPushButton *button01;
    QPushButton *button02;
    QPushButton *button10;
    QPushButton *button11;
    QPushButton *button12;
    QPushButton *button20;
    QPushButton *button21;
    QPushButton *button22;

    bool playerTurn;
    QString board[3][3];

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void tileClicked(QPushButton* button, int row, int col);

public:
    bool checkWin(const QString player);

public:
    void resetBoard();

public:
    bool boardFull();
};

#endif // MAINWINDOW_H

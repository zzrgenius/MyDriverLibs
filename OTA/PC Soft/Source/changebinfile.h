#ifndef CHANGEBINFILE_H
#define CHANGEBINFILE_H

#include <QMainWindow>

namespace Ui {
class ChangeBinFile;
}

class ChangeBinFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeBinFile(QWidget *parent = nullptr);
    ~ChangeBinFile();

private slots:
    void on_choiceFileBtn_clicked();

    void on_startBtn_clicked();

private:
    Ui::ChangeBinFile *ui;
};

#endif // CHANGEBINFILE_H

#include "changebinfile.h"
#include "ui_changebinfile.h"
#include "qfiledialog.h"
#include "qfile.h"
#include "qmessagebox.h"
#include "./CRC16/JQChecksum.h"
#include "qbytearray.h"
#include "qdatastream.h"
#include "qdebug.h"

ChangeBinFile::ChangeBinFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangeBinFile)
{
    ui->setupUi(this);
    ui->pageComBox->addItem("128");
    ui->pageComBox->addItem("256");
    ui->pageComBox->addItem("512");
    ui->pageComBox->addItem("1024");
}

ChangeBinFile::~ChangeBinFile()
{
    delete ui;
}

void ChangeBinFile::on_choiceFileBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                      "选择要转换的文件",
                                                      "./",
                                                      "Bin (*.bin)");
    ui->fileNameEdit->setText(fileName);

    if (false == fileName.isEmpty())
    {
        ui->startBtn->setEnabled(true);
        ui->startBtn->setText("启动转换");
        ui->statusBar->clearMessage();
        ui->fileSizeEdit->clear();
        ui->crcEdit->clear();
    }
}

void ChangeBinFile::on_startBtn_clicked()
{
    QFile file(ui->fileNameEdit->text());

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "警告", "文件打开失败", QMessageBox::Ok);
    }
    else
    {
        if (file.size() > 20*1024*1024)//文件大于20M
        {
            QMessageBox::warning(this, "警告", "文件超过20M", QMessageBox::Ok);
        }
        else
        {
            //读取文件
            const char flag[11] = "sinodod_V1";
            QByteArray arry = file.readAll();
            ui->fileSizeEdit->setText(QString::number(arry.size()));

            QByteArray headArr;
            if (0 == arry.indexOf(flag)) //已添加过转换头
            {
                ui->fileSizeEdit->clear();
                ui->crcEdit->clear();
                ui->statusBar->showMessage("转换失败!");
                QMessageBox::warning(this, "警告", "文件已处理过", QMessageBox::Ok);
            }
            else
            {
                //写入标志数据
                QByteArray head(flag, sizeof(flag));

                // CRC16写入缓存
                int pageSize = ui->pageComBox->currentText().toInt();
                auto crc = JQChecksum::crc16ForModbus(arry);
                char bytes[4];
                bytes[0] = (char)(crc & 0x00ff);
                bytes[1] = (char)((crc >> 8) & 0x00ff);
                head.append(bytes, 2);
                char showCRC[16];
                snprintf(showCRC, sizeof(showCRC), "%02X", crc);
                ui->crcEdit->setText(QString(showCRC));

                //数据长度写入缓存
                int fileLen = arry.size();
                bytes[0] = (char)(fileLen & 0x000000ff);
                bytes[1] = (char)((fileLen >> 8) & 0x000000ff);
                bytes[2] = (char)((fileLen >> 16) & 0x000000ff);
                bytes[3] = (char)((fileLen >> 24) & 0x000000ff);
                head.append(bytes, 4);

                //凑满一页大小
                pageSize -= head.size();
                char fill = 0;
                for (int i = 0; i < pageSize; i++)
                {
                    head.append(fill); //用0填充
                }

                //添加Bin文件数据
                head.append(arry);

                //写入新文件
                QString saveName = QFileDialog::getSaveFileName(this,
                                                                  "保存转换文件",
                                                                  "./",
                                                                  "Bin (*.bin)");

                if (!saveName.isEmpty()) //用户选择了文件
                {
                    QFile saveFile(saveName);
                    if (saveFile.open(QIODevice::WriteOnly))
                    {
                        saveFile.write(head.data(), head.size());
                        saveFile.flush();
                        saveFile.close();
                        ui->statusBar->showMessage("转换成功!");
                        ui->startBtn->setText("转换成功");
                    }
                }
                else
                {
                    ui->statusBar->showMessage("文件未保存");
                    ui->fileSizeEdit->clear();
                    ui->crcEdit->clear();
                }
            }
        }

        file.close();
    }
}

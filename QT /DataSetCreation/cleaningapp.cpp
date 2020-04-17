#include "cleaningapp.h"
#include "ui_cleaningapp.h"
#include "cleaningfunction.h"

#include <QFileDialog>
#include <iostream>

CleaningApp::CleaningApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CleaningApp)
{
    ui->setupUi(this);
}


CleaningApp::~CleaningApp()
{
    delete ui;
}


void CleaningApp::on_pushButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Open a file", "C://");
    //QMessageBox::information(this,"..",file_path);
    ui->label->setText(file_path);
    ui->label->setStyleSheet("color: red"); //FIXA

    std::string str = file_path.toStdString();
    str.c_str();

    Cleaning::SourceUrl = str;
}

void CleaningApp::on_pushButton_3_clicked() //The user selects parent folder
{
    QString parent_path = QFileDialog::getExistingDirectory(this, "Open a file", "C://");

    ui->label_2->setText(parent_path);
    ui->label_2->setStyleSheet("color: red");

    std::string str = parent_path.toStdString()+ "/"; //conversion to std::string
    str.c_str();

    Cleaning::DestUrl = str;
}

void CleaningApp::on_pushButton_2_clicked()//Run Button
{

        //Cleaning DataSet;
        if(Cleaning::SourceUrl != "" && Cleaning::DestUrl != "")
        {
            Cleaning::GetFileName();
            Cleaning::GenerateData();
            if(Cleaning::checkValid && Cleaning::CheckifMp4())
            {
                if(Cleaning::endofVideo)
                {
                   ui->textBrowser->clear();
                   ui->textBrowser->setPlainText("The images were successfully saved! Choose a new video to clean or exit the program by closing the window.");
                   std::cout << Cleaning::FPS << std::endl;
                }
            }
            else
            {
                ui->textBrowser->clear();
                ui->textBrowser->setPlainText("Input file is not valid, try another one.");
            }
        }
        else
        {
            ui->textBrowser->clear();
            ui->textBrowser->setPlainText("Select file and destination folder.");
        }

}

void CleaningApp::on_XResBox_editingFinished()
{
    Cleaning::xRes = ui->XResBox->value();
}

void CleaningApp::on_YResBox_3_editingFinished()
{
    Cleaning::yRes = ui->YResBox_3->value();
}

void CleaningApp::on_FrameCountBox_editingFinished()
{
    Cleaning::FrameCtrl = ui->FrameCountBox->value();
}


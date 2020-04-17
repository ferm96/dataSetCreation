#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CleaningApp; }
QT_END_NAMESPACE

class CleaningApp : public QMainWindow
{
    Q_OBJECT

public:
    CleaningApp(QWidget *parent = nullptr);
    ~CleaningApp();

private slots:
    void on_pushButton_clicked(); //Get source URL
    void on_pushButton_2_clicked(); //Run cleaning function
    void on_pushButton_3_clicked(); //Get destination folder URL
    void on_XResBox_editingFinished(); //Set horisontal resolution
    void on_YResBox_3_editingFinished(); //Set vertical resolution
    void on_FrameCountBox_editingFinished(); //Set how many images to save per second

private:
    Ui::CleaningApp *ui;
};

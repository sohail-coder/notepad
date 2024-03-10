#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextStream"
#include "QCloseEvent"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::handleTextChanged);
    is_modified = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if (is_modified) {
        // Prompt the user to save changes
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save Changes", "Do you want to save changes?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            on_actionSave_triggered();
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }
    file_path = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    if (is_modified) {
        // Prompt the user to save changes
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save Changes", "Do you want to save changes?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            on_actionSave_triggered();
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }
    file_path = QFileDialog::getOpenFileName(this,"Open File","","*.txt");
    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"File Error","File not found or File format error");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    if(file_path.length()==0)
            file_path = QFileDialog::getSaveFileName(this,"Open File","","*.txt");
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"File Error","File not found or File format error");
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    file_path = QFileDialog::getSaveFileName(this,"Open File","","*.txt");
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"File Error","File not found or File format error");
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (is_modified) {
        // Prompt the user to save changes
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save Changes", "Do you want to save changes?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            on_actionSave_triggered();
        } else if (reply == QMessageBox::Cancel) {
            event->ignore(); // Ignore the close event
            return;
        }
    }
    event->accept(); // Accept the close event
}

void MainWindow::on_actionExit_triggered()
{
    QCloseEvent closeEvent;
    MainWindow::closeEvent(&closeEvent);
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionabout_triggered()
{
    QString string = "Name: Notedpad++\n";
    string+="Company: Sohail Enterprices ltd\n";
    string+="2024 All copyrights Reserved\n";
    QMessageBox::information(this,"About",string);

}
void MainWindow::handleTextChanged()
{
    is_modified = true;
}

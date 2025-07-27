#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ui->text_input->setText(settings.value("input_text").toString());
    this->ui->text_output->setText(settings.value("output_text").toString());

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_button_input_clicked()
{
    QString input = QFileDialog::getExistingDirectory(this,"Ordner wählen");
    if (!input.isEmpty())
        this->ui->text_input->setText(input);
}


void MainWindow::on_button_output_clicked()
{
    QString output = QFileDialog::getExistingDirectory(this,"Ordner wählen");
    if (!output.isEmpty())
        this->ui->text_output->setText(output);
}


void MainWindow::on_text_output_textChanged(const QString &arg1)
{
    this->settings.setValue("output_text", arg1);
    if (QDir(arg1).exists())
    {
        target_dir.setPath(arg1);
        target_dir.setSorting(QDir::Name | QDir::IgnoreCase);
    }

}


void MainWindow::on_text_input_textChanged(const QString &arg1)
{
    this->scan(arg1);
    this->settings.setValue("input_text", arg1);
}

void MainWindow::scan(QString path)
{
    if (QDir(path).exists())
    {
        dir.setPath(path);
        dir.setSorting(QDir::Name | QDir::IgnoreCase);
        files = dir.entryList(QDir::Files, QDir::Name | QDir::IgnoreCase);
        this->next();
    }
}

void MainWindow::next()
{
    while (!files.first().toLower().endsWith(".jpg") && !files.first().toLower().endsWith(".png"))
    {
        this->files.removeFirst();
    }


    this->ui->text_filename->setText(files.first());
    this->current = dir.absoluteFilePath(files.first());
    QImage img(this->current);
    if (img.width() > this->ui->spin_max_width->value())
    {
        img = img.scaledToWidth(this->ui->spin_max_width->value());
    }



    this->ui->pic_view->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::openPreview(const QString path)
{
    QFileInfo info(path);
    if (info.exists() && info.isFile()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
    } else {
        qWarning() << "Datei existiert nicht:" << path;
    }
}


void MainWindow::on_button_yes_clicked()
{
    QFile::copy(this->current,target_dir.absoluteFilePath(files.first()));
    this->on_button_no_clicked();
}


void MainWindow::on_button_no_clicked()
{
    if (this->files.isEmpty())
        return;

    this->files.removeFirst();
    this->next();
}


void MainWindow::on_button_preview_clicked()
{
    this->openPreview(this->current);
}


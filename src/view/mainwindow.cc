/*!
 * @file mainwindow.cc
 * @author hodorsta
 * @brief Содержит реализацию функций класса MainWindow
 */
#include "./mainwindow.h"

#include "../controller/controller.h"
#include "./ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), expression_(controller) {
  graph_ = new Graph(expression_);
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_LBracket, SIGNAL(clicked()), this,
          SLOT(DigitsNumbers()));
  connect(ui->pushButton_RBracket, SIGNAL(clicked()), this,
          SLOT(DigitsNumbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(Funcions()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(DeliteSign()));
}

MainWindow::~MainWindow() {
  if (ui) delete ui;
  if (graph_) delete graph_;
  if (expression_) delete expression_;
}

void MainWindow::DigitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  ui->result->setText(ui->result->text() + button->text());
}

void MainWindow::Funcions() {
  QPushButton *button = (QPushButton *)sender();
  ui->result->setText(ui->result->text() + button->text() + "(");
}

void MainWindow::DeliteSign() {
  QString slice = ui->result->text();
  slice.chop(1);
  ui->result->setText(slice);
}

void MainWindow::on_pushButton_AC_clicked() {
  ui->result->setText("");
  ui->error->setText("All Right");
  ui->DSpinBox_Xmax->setValue(10.00);
  ui->DSpinBox_Ymax->setValue(10.00);
  graph_->close();
}

void MainWindow::on_pushButton_equal_clicked() {
  ui->error->setText("All Right");
  QString input_expression = ui->result->text();
  double x_val = ui->DSpinBox_X->value();
  double result = expression_->Calculation(input_expression, x_val);
  if (!expression_->GetErr()) {
    QString output = QString::number(result, 'g', 7);
    ui->result->setText(output);
  } else {
    if (expression_->GetErr() == 1) {
      ui->error->setText("Find error in input");
    } else {
      ui->error->setText("ERROR!!!");
    }
    ui->result->setText(input_expression);
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  graph_->show();
  QString input_expression = ui->result->text();
  double x_max = ui->DSpinBox_Xmax->text().toDouble();
  double y_max = ui->DSpinBox_Ymax->text().toDouble();
  graph_->DrawGraph(input_expression, x_max, y_max);
}

}  // namespace s21

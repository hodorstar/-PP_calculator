/*!
 * @file
 * @author hodorsta
 * @brief Заголовочный файл с описанием класса MainWindow
 */

#ifndef CPP3_S21_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H
#define CPP3_S21_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H

#include <QMainWindow>

#include "../controller/controller.h"
#include "./graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
/*!
 * @brief  Класс MainWindow осущевствляет отрисовку внешнего вида приложения.
 * Представляет собой часть модуля представления в в паттерне MVC.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graph *graph_;
  s21::Controller *expression_;

 private slots:
  void DigitsNumbers();
  void Funcions();
  void on_pushButton_AC_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_graph_clicked();
  void DeliteSign();
};
}  // namespace s21
#endif  // CPP3_S21_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H

/*!
 * @file
 * @author hodorsta
 * @brief Заголовочный файл с описанием класса Graph
 */

#ifndef CPP3_S21_SMARTCALC_V2_0_1_SRC_VIEW_GRAPH_H
#define CPP3_S21_SMARTCALC_V2_0_1_SRC_VIEW_GRAPH_H

#include <QDialog>
#include <QWidget>
#include <vector>

#include "../controller/controller.h"
#include "../lib/qcustomplot.h"
#include "./ui_graph.h"
namespace Ui {
class Graph;
}

namespace s21 {
/*!
 * @brief  Класс Graph осущевствляет отрисовку графика функции. Представляет
 * собой часть модуля представления в в паттерне MVC.
 */
class Graph : public QDialog {
  Q_OBJECT

 public:
  Graph(Controller *controller, QWidget *parent = nullptr);
  ~Graph();

  void DrawGraph(QString input_expression, double x_max, double y_max);

 private:
  Ui::Graph *ui;
  s21::Controller *expression_;
  std::pair<std::vector<double>, std::vector<double>> vector_xy_;
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_1_SRC_VIEW_GRAPH_H

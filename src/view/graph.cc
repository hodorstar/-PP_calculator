/*!
 * @file graph.cc
 * @author hodorsta
 * @brief Содержит реализацию функций класса Graph
 */
#include "./graph.h"

#include "ui_graph.h"

namespace s21 {

Graph::Graph(Controller *controller, QWidget *parent)
    : QDialog(parent), ui(new Ui::Graph), expression_(controller) {
  ui->setupUi(this);
}

Graph::~Graph() {
  if (ui) delete ui;
  if (expression_) delete expression_;
}

void Graph::DrawGraph(QString input_expression, double x_max, double y_max) {
  ui->error->setText("All Right");
  ui->formula->setText(input_expression);

  QScreen *screen = QGuiApplication::primaryScreen();

  QRect screenGeometry = screen->geometry();
  int width = screenGeometry.width();

  double step = x_max / (width * 100);
  vector_xy_ = expression_->CalcGraph(input_expression, x_max, step);
  if (!expression_->GetErr()) {
    QVector<double> q_x(vector_xy_.first.begin(), vector_xy_.first.end());
    QVector<double> q_y(vector_xy_.second.begin(), vector_xy_.second.end());

    ui->widget_graph->addGraph();
    ui->widget_graph->graph(0)->setData(q_x, q_y);
    ui->widget_graph->xAxis->setLabel("x");
    ui->widget_graph->yAxis->setLabel("y");
    ui->widget_graph->xAxis->setRange(-x_max, x_max);
    ui->widget_graph->yAxis->setRange(-y_max, y_max);
    ui->widget_graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget_graph->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->widget_graph->replot();
  } else {
    ui->widget_graph->clearGraphs();
    ui->widget_graph->replot();
    ui->error->setText("Find error in input");
  }
}

}  // namespace s21

#ifndef RUNRESULTS_H
#define RUNRESULTS_H

#include "mcml/mcml.h"
#include <QWidget>
#include <sstream>

extern OutClass out_temp;

namespace Ui {
class RunResults;
}

class RunResults : public QWidget {
  Q_OBJECT
public:
  static RunResults *getInstance() {
    if (!theRunResults)
      theRunResults = new RunResults();
    return theRunResults;
  }
  explicit RunResults(QWidget *parent = 0);
  RunResults(const RunResults &) = delete;
  RunResults &operator=(const RunResults &) = delete;

  ~RunResults();
  void getOutputData();
  void showAllTheResults();

private slots:
  void on_View_diff_reflect_2d_Button_clicked();

  void on_View_Abs_prob_layer_Button_clicked();

  void on_View_diff_reflect_rdl_Button_clicked();

  void on_View_diff_reflect_agl_Button_clicked();

  void on_View_1D_Prob_z_Button_clicked();

  void on_View_2D_Prob_rz_Button_clicked();

  void on_View_total_trans_2d_Button_clicked();

  void on_View_total_trans_agl_Button_clicked();

  void on_View_total_trans_rdl_Button_clicked();

private:
  Ui::RunResults *ui;
  OutClass out_param;
  static RunResults *theRunResults;
  void setRAT();
};

template <typename T> QString Convert2String(const T &t) {
  std::stringstream temp;
  temp << t;
  return QString::fromStdString(temp.str());
}

QString LinkDataFromVector(const QVector<double> &vec);
void SetDialog_1D(QDialog *dlg, const QVector<double> &vec,
                  QString &plain_text);
void SetDialog_2D(QDialog *dlg, const QVector<QVector<double>> &vec,
                  QString &plain_text);

#endif // RUNRESULTS_H

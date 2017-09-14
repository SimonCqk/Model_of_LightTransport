#include "runresults.h"
#include "ui_runresults.h"
#include<algorithm>
#include <QDebug>
#include <QDialog>
#include <QPlainTextEdit>
#include <QVBoxLayout>>
#include<QtCharts>

using namespace QtCharts;

RunResults *RunResults::theRunResults = nullptr;

OutClass out_temp;
InputClass in_temp;

QString LinkDataFromVector(const QVector<double> &vec) {
  QString str = "";
  size_t size = vec.size();
  for (size_t i = 0; i < size; ++i) {
    if (!((i + 1) % 5)) // 5 number each line.
      str += (QString::number(vec[i], 'f', 5) + "\n");
    else
      str += (QString::number(vec[i], 'f', 5) + ",");
  }
  return str + "\n";
}

RunResults::RunResults(QWidget *parent)
    : QWidget(parent), ui(new Ui::RunResults) {
  ui->setupUi(this);

  this->setAutoFillBackground(true);
  QString bground_path = ":/image/image/Photon.jpg";
  QPixmap bground; // set background image
  bground.load(bground_path);
  QPalette palette;
  // set image scaled
  palette.setBrush(this->backgroundRole(),
                   QBrush(bground.scaled(this->size(), Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation)));
  // boring setting for white background fonts shown in UI.
  this->setPalette(palette);
  QPalette font_color;
  font_color.setColor(QPalette::WindowText, Qt::white);
  ui->label->setPalette(font_color);
  ui->label_2->setPalette(font_color);
  ui->label_3->setPalette(font_color);
  ui->label_4->setPalette(font_color);
  ui->label_5->setPalette(font_color);
  ui->label_6->setPalette(font_color);
  ui->label_7->setPalette(font_color);
  ui->label_8->setPalette(font_color);
  ui->label_9->setPalette(font_color);
  ui->label_10->setPalette(font_color);
  ui->label_11->setPalette(font_color);
  ui->label_12->setPalette(font_color);
  ui->label_13->setPalette(font_color);
  ui->label_14->setPalette(font_color);

  ui->SpecRefEdit->setReadOnly(true);
  ui->AbsFracEdit->setReadOnly(true);
  ui->DiffRefEdit->setReadOnly(true);
  ui->TransEdit->setReadOnly(true);
}

RunResults::~RunResults() { delete ui; }

void RunResults::getOutputData() { this->out_param = out_temp; }

void RunResults::showAllTheResults() { setRAT(); }

void RunResults::setRAT() {
  ui->SpecRefEdit->setText(Convert2String<double>(out_param.out->spec_reflect));
  ui->DiffRefEdit->setText(Convert2String<double>(out_param.out->diff_reflect));
  ui->AbsFracEdit->setText(Convert2String<double>(out_param.out->abs_prob));
  ui->TransEdit->setText(Convert2String<double>(out_param.out->total_trans));
}

void RunResults::on_View_diff_reflect_2d_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text = "# Viewer for 2D distribution of diffuse reflectance. "
                       "[1/(cm2 sr)] #\n   \n";
  SetDialog_2D(viewer, out_param.out->diff_reflect_2d, plain_text);
}

void RunResults::on_View_Abs_prob_layer_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text =
      "# Viewer for absorption probability of each layer #\n   \n";
  SetDialog_1D(viewer, out_param.out->abs_prob_layer, plain_text);
}

void RunResults::on_View_diff_reflect_rdl_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text = "# Viewer for 1D radial distribution of diffuse "
                       "reflectance. [1/cm2] #\n   \n";
  SetDialog_1D(viewer, out_param.out->diff_reflect_rdl, plain_text);
}

void RunResults::on_View_diff_reflect_agl_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text = "# Viewer for 1D angular distribution of diffuse "
                       "reflectance. [1/sr] #\n   \n";
  SetDialog_1D(viewer, out_param.out->diff_reflect_agl, plain_text);
}

void RunResults::on_View_1D_Prob_z_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text =
      "# Viewer for 1D probability density over z. [1/cm] */ #\n   \n";
  SetDialog_1D(viewer, out_param.out->abs_prob_z, plain_text);
}

void RunResults::on_View_2D_Prob_rz_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text = "# Viewer for 2D probability density in turbid media "
                       "over r & z. [1/cm3] #\n   \n";
  SetDialog_2D(viewer, out_param.out->abs_prob_rz, plain_text);
}

void RunResults::on_View_total_trans_2d_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text = "# Viewer for 2D distribution of total transmittance. "
                       "[1/(cm2 sr)] #\n   \n";
  SetDialog_2D(viewer, out_param.out->total_trans_2d, plain_text);
}

void RunResults::on_View_total_trans_agl_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text = "# Viewer for 1D angular distribution of transmittance. "
                       "[1/sr] */ #\n   \n";
  SetDialog_1D(viewer, out_param.out->total_trans_agl, plain_text);
}

void RunResults::on_View_total_trans_rdl_Button_clicked() {
  QDialog *viewer = new QDialog();
  QString plain_text = "# Viewer for 1D radial distribution of transmittance. "
                       "[1/cm2] */ #\n   \n";
  SetDialog_1D(viewer, out_param.out->total_trans_rdl, plain_text);
}

void SetDialog_1D(QDialog *dlg, const QVector<double> &vec,
                  QString &plain_text) {
  dlg->setFixedSize(QSize(350, 200));
  dlg->setFont(QFont("Consolas"));
  dlg->setWindowModality(Qt::WindowModal);
  dlg->setWindowIcon(QIcon(":/image/logo"));
  QPlainTextEdit *view_data = new QPlainTextEdit();
  view_data->setFont(QFont("Consolas"));
  view_data->setReadOnly(true);
  plain_text += LinkDataFromVector(vec);
  view_data->setPlainText(plain_text);

  QPushButton *Close = new QPushButton("Close");
  Close->setFont(QFont("Consolas"));

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(view_data);
  layout->addWidget(Close);

  dlg->setLayout(layout);
  dlg->show();

  QCoreApplication::connect(Close, &QPushButton::clicked, dlg, &QDialog::close);
}

void SetDialog_2D(QDialog *dlg, const QVector<QVector<double>> &vec,
                  QString &plain_text) {
  dlg->setFixedSize(QSize(350, 200));
  dlg->setFont(QFont("Consolas"));
  dlg->setWindowModality(Qt::WindowModal);
  dlg->setWindowIcon(QIcon(":/image/logo"));
  QPlainTextEdit *view_data = new QPlainTextEdit();
  view_data->setFont(QFont("Consolas"));
  view_data->setReadOnly(true);
  for (const auto &item : vec) {
    plain_text += LinkDataFromVector(item);
  }
  view_data->setPlainText(plain_text);

  QPushButton *Close = new QPushButton("Close");
  Close->setFont(QFont("Consolas"));

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(view_data);
  layout->addWidget(Close);

  dlg->setLayout(layout);
  dlg->show();

  QCoreApplication::connect(Close, &QPushButton::clicked, dlg, &QDialog::close);
}

void Draw1DScatterChart(const QVector<double>& vec,const QString& name
                        ,const int& type){ // type: 1-radial , 2-angular ,3-single axis z
    if(type<=0||type>4){                   // 4-each layer
         QMessageBox::critical(0,QString("Type Error!"),QString("Invalid Input Type of Asix."));
        return;
    }
    QChart *chart = new QChart();
    chart->setTitle(name);
    chart->setTitleFont(QFont("Consolas",10));
    QScatterSeries *series=new QScatterSeries(chart);
    series->setMarkerSize(qreal(6.0));
    series->setUseOpenGL(true);
    QValueAxis *axisX=new QValueAxis();
    int max_value=static_cast<int>(*std::max(vec.cbegin(),vec.cend()));
    int index=0;
    switch (type) {
    case 1:{
        axisX->setTitleText("1/cm2");
        axisX->setTitleFont(QFont("Consolas"));
        axisX->setGridLineVisible(true);
        axisX->setTitleFont(QFont("Consolas"));
        const double d_alpha=1/(4*PI*in_temp.input->nr*in_temp.input->nr);
        for(const auto& item:vec){
            series->append((d_alpha*index++),item);
        }
        axisX->setRange(0,d_alpha*index+1);
        break;
    }
    case 2:{
        axisX->setTitleText("1/sr");
        axisX->setTitleFont(QFont("Consolas"));
        axisX->setGridLineVisible(true);
        axisX->setTitleFont(QFont("Consolas"));
        const double d_sr=1/(4*PI);
        for(const auto& item:vec){
            series->append((d_sr*index++),item);
        }
        axisX->setRange(0,d_sr*index+1);
        break;
    }
    case 3:{
        axisX->setTitleText("1/cm");
        axisX->setTitleFont(QFont("Consolas"));
        axisX->setGridLineVisible(true);
        axisX->setTitleFont(QFont("Consolas"));
        const double d_z=1/in_temp.input->nz;
        for(const auto& item:vec){
            series->append((d_z*index++),item);
        }
        axisX->setRange(0,d_z*index+1);
        break;
    }
    case 4:{
        axisX->setTitleText("layer");
        axisX->setTitleFont(QFont("Consolas"));
        axisX->setGridLineVisible(true);
        axisX->setRange(0,vec.size()+1);
        axisX->setTitleFont(QFont("Consolas"));
        const double num_layer=in_temp.input->num_layers;
        for(int i=1;i<=num_layer;++i){
            series->append(i,vec[i]);
        }
        break;
    }
    default:
        break;
    }
    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->setAxisX(axisX);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView=new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setWindowTitle("Scatter of "+ name);
    chartView->setFont(QFont("Consolas"));
    chartView->resize(400, 300);
    chartView->show();
}

void Draw1DSpLineChart(const QVector<double>& vec,const QString& name
                       ,const int& type){ // type: 1-radial , 2-angular ,3-single axis z
   if(type<=0||type>4){                   // 4-each layer
       QMessageBox::critical(0,QString("Type Error!"),QString("Invalid Input Type of Asix."));
       return;
   }
   QChart *chart = new QChart();
   chart->setTitle(name);
   chart->setTitleFont(QFont("Consolas",10));
   QScatterSeries *series=new QScatterSeries(chart);
   series->setMarkerSize(qreal(6.0));
   series->setUseOpenGL(true);
   QValueAxis *axisX=new QValueAxis();
   int max_value=static_cast<int>(*std::max(vec.cbegin(),vec.cend()));
   int index=0;
   switch (type) {
   case 1:{
       axisX->setTitleText("1/cm2");
       axisX->setTitleFont(QFont("Consolas"));
       axisX->setGridLineVisible(true);
       axisX->setTitleFont(QFont("Consolas"));
       const double d_alpha=1/(4*PI*in_temp.input->nr*in_temp.input->nr);
       for(const auto& item:vec){
           series->append((d_alpha*index++),item);
       }
       axisX->setRange(0,d_alpha*index+1);
       break;
   }
   case 2:{
       axisX->setTitleText("1/sr");
       axisX->setTitleFont(QFont("Consolas"));
       axisX->setGridLineVisible(true);
       axisX->setTitleFont(QFont("Consolas"));
       const double d_sr=1/(4*PI);
       for(const auto& item:vec){
           series->append((d_sr*index++),item);
       }
       axisX->setRange(0,d_sr*index+1);
       break;
   }
   case 3:{
       axisX->setTitleText("1/cm");
       axisX->setTitleFont(QFont("Consolas"));
       axisX->setGridLineVisible(true);
       axisX->setTitleFont(QFont("Consolas"));
       const double d_z=1/in_temp.input->nz;
       for(const auto& item:vec){
           series->append((d_z*index++),item);
       }
       axisX->setRange(0,d_z*index+1);
       break;
   }
   case 4:{
       axisX->setTitleText("layer");
       axisX->setTitleFont(QFont("Consolas"));
       axisX->setGridLineVisible(true);
       axisX->setRange(0,vec.size()+1);
       axisX->setTitleFont(QFont("Consolas"));
       const double num_layer=in_temp.input->num_layers;
       for(int i=1;i<=num_layer;++i){
           series->append(i,vec[i]);
       }
       break;
   }
   default:
       break;
   }
   chart->addSeries(series);
   chart->legend()->hide();
   chart->createDefaultAxes();
   chart->setAxisX(axisX);
   chart->setAnimationOptions(QChart::SeriesAnimations);

   QChartView *chartView=new QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);
   chartView->setWindowTitle("Scatter of "+ name);
   chartView->setFont(QFont("Consolas"));
   chartView->resize(400, 300);
   chartView->show();
}

void RunResults::on_View_diff_reflect_rdl_Chart_clicked()
{
    Draw1DSpLineChart(out_temp.out->diff_reflect_rdl,QString("radial distribution of diffuse reflectance"),1);
}


void RunResults::on_View_1D_Prob_z_Chart_clicked()
{
    Draw1DScatterChart(out_temp.out->abs_prob_z,QString("probability density over z"),3);
}

void RunResults::on_View_diff_reflect_agl_Chart_clicked()
{
    Draw1DScatterChart(out_temp.out->diff_reflect_agl,QString("angular distribution of diffuse reflectance"),2);
}

void RunResults::on_View_Abs_prob_layer_Chart_clicked()
{
    Draw1DScatterChart(out_temp.out->abs_prob_z,QString("each layer's absorption probability"),4);
}

void RunResults::on_View_total_trans_agl_Chart_clicked()
{
    Draw1DSpLineChart(out_temp.out->abs_prob_z,QString("radial distribution of transmittance"),2);
}

void RunResults::on_View_total_trans_rdl_Chart_clicked()
{
    Draw1DSpLineChart(out_temp.out->abs_prob_z,QString("angular distribution of transmittance"),1);
}

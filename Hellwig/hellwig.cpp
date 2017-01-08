#include "hellwig.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsItem>
#include "DataParser.h"
#include "Scene.h"
#include "Utils.h"

Q_DECLARE_METATYPE(std::vector <uint>);
Q_DECLARE_METATYPE(std::vector <double>);

Hellwig::Hellwig(QWidget *parent)
    : QMainWindow(parent)
    , m_BestCombIdx(0)
	, m_ZoomFactor(1.0)
	, m_Scene(new CScene(this))
{
	InitUi();
    InitToolBar();
    InitConnections();
}

Hellwig::~Hellwig()
{

}

// INIT
//////////////////////////////////////////////////////////////////////////
void Hellwig::InitUi()
{
	ui.setupUi(this);
	ui.graphicsView->setScene(m_Scene);
}

void Hellwig::InitToolBar()
{
    QAction* act = ui.mainToolBar->addAction(QIcon(":/Resources/folder_vertical_open.png"), tr("Load data file"), this, &Hellwig::OnLoadDataTriggered);
    act->setShortcut(QKeySequence::Open);
    ui.mainToolBar->addSeparator();
    act = ui.mainToolBar->addAction(QIcon(":/Resources/calculator.png"), tr("Calc Helwigg!"), this, &Hellwig::OnCalcHellwigVariableChoice);
    act->setShortcut(QKeySequence(tr("Ctrl+Shift+C")));
    act = ui.mainToolBar->addAction(QIcon(":/Resources/calc_kmnk.png"), tr("Calc KMNK!"), this, &Hellwig::OnCalcKmnk);
    act->setShortcut(QKeySequence(tr("Ctrl+Shift+X")));
	ui.mainToolBar->addSeparator();
	act = ui.mainToolBar->addAction(QIcon(":/Resources/chart_line.png"), tr("Generate chart"), this, &Hellwig::OnGenerateChart);
	act->setShortcut(QKeySequence(tr("Ctrl+Shift+G")));
    ui.mainToolBar->addSeparator();
    act = ui.mainToolBar->addAction(QIcon(":/Resources/broom.png"), tr("Clear"), this, &Hellwig::OnClearAll);
    act->setShortcut(QKeySequence(tr("Ctrl+Delete")));
}


void Hellwig::InitConnections()
{
    // buttons
    connect(ui.pushButton_calc_hellwig,     &QPushButton::clicked, this, &Hellwig::OnCalcHellwigVariableChoice);
    connect(ui.pushButton_clear_hellwig,    &QPushButton::clicked, this, &Hellwig::ClearHellwig);
    connect(ui.pushButton_kmnk_calc,        &QPushButton::clicked, this, &Hellwig::OnCalcKmnk);
    connect(ui.pushButton_kmnk_clear,       &QPushButton::clicked, this, &Hellwig::ClearKmnk);
	connect(ui.pushButton_graph_zoom_in,	&QPushButton::clicked, this, &Hellwig::OnGraphZoomIn);
	connect(ui.pushButton_graph_zoom_out,	&QPushButton::clicked, this, &Hellwig::OnGraphZoomOut);
	connect(ui.pushButton_graph_clear,      &QPushButton::clicked, this, &Hellwig::ClearChart);

    // combo
    connect(ui.comboBox_comb, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Hellwig::OnCombComboIndexChanged);
}

// CALC
//////////////////////////////////////////////////////////////////////////
void Hellwig::TableDataSetSize(uint rows, uint columns)
{
    ui.tableWidget_Data->setRowCount(rows);
    ui.tableWidget_Data->setColumnCount(columns);
    QStringList headers;
    headers << "Y";
    for (int i = 1; i < columns; i++)
        headers << "X" + QString::number(i);
    ui.tableWidget_Data->setHorizontalHeaderLabels(headers);
}

void Hellwig::TableDataPassLoadedData(const SDataIn& data)
{
    uint rows = data.data.size();
    for (uint i = 0; i < rows; i++)
    {
        uint columns = data.data[i].size();
        for (uint j = 0; j < columns; j++)
        {
            QTableWidgetItem* it = GetTableItem(ui.tableWidget_Data, i, j);
            QString cell = QString::number(data.data[i][j]);
            it->setText(cell);            
        }
    }
}

void Hellwig::TableR0SetSize(uint rows, uint columns)
{
    ui.tableWidget_MatrixR0->setRowCount(rows);
    ui.tableWidget_MatrixR0->setColumnCount(columns);
    QStringList headers;
    for (int i = 0; i < rows; i++)	
        headers << "X" + QString::number(i + 1);	
    ui.tableWidget_MatrixR0->setVerticalHeaderLabels(headers);
}

void Hellwig::TableR0CalcData(const SDataIn& data)
{
    for (int i = 0; i < data.x_num; i++)
    {
        double correl = CMath::Correl(data, 0, i + 1); // cause under idx 0 we store Y
        QTableWidgetItem* it = GetTableItem(ui.tableWidget_MatrixR0, i, 0);
        it->setText(QString::number(correl));
    }
}

void Hellwig::TableRSetSize(uint rows, uint columns)
{
    ui.tableWidget_MatrixR->setRowCount(rows);
    ui.tableWidget_MatrixR->setColumnCount(columns);
    QStringList headers;
    for (int i = 0; i < rows; i++)   
        headers << "X" + QString::number(i + 1);    
    ui.tableWidget_MatrixR->setVerticalHeaderLabels(headers);
    ui.tableWidget_MatrixR->setHorizontalHeaderLabels(headers);
}

void Hellwig::TableRCalcData(const SDataIn& data)
{
    for (uint i = 0; i < data.x_num; i++)
    {
        for (uint j = 0; j < data.x_num; j++)
        {
            QTableWidgetItem* it = GetTableItem(ui.tableWidget_MatrixR, i, j);
            double correl = (i == j) ? 1.0 : CMath::Correl(data, i + 1, j + 1);
            it->setText(QString::number(correl));
        }
    }
}

void Hellwig::CalcAllCombinations()
{
    std::vector <uint> vec;
    for (int i = 1; i <= m_Data.x_num; i++)
        vec.push_back(i);

    for (int i = 1; i <= m_Data.x_num; i++)
    {
        std::vector <uint> result(i, 0);
        CalcCombinations(vec, i, 0, result);
        ui.label_comb_num->setText(QString("Combinations number: %1").arg(ui.comboBox_comb->count()));
    }
}

void Hellwig::CalcCombinations(const std::vector <uint>& vec, const int& len, const int& start, std::vector <uint> result)
{
    if (len == 0) 
    {
        QString str;
        for (const uint& num : result)
        {
            str += "X" + QString::number(num) + ", ";
        }
        str.chop(2);
        ui.comboBox_comb->addItem(str, QVariant::fromValue<std::vector<uint>>(result));
        return;
    }
    for (int i = start; i <= vec.size() - len; i++) 
    {
        result[result.size() - len] = vec[i];
        CalcCombinations(vec, len - 1, i + 1, result);
    }
}

void Hellwig::CalcCapacity()
{
    m_BestCombIdx = 0;
    double best_H = 0.0;
    for (int i = 0; i < ui.comboBox_comb->count(); i++)
    {
        std::vector <uint> combo_vec = ui.comboBox_comb->itemData(i, Qt::UserRole).value<std::vector<uint>>();
        std::vector <double> individual;
        for (const uint& num : combo_vec)
        {
            double r = pow(ui.tableWidget_MatrixR0->item(num - 1, 0)->text().toDouble(), 2);
            double de = 0.0;
            for (int h = 0; h < combo_vec.size(); h++)
            {
                de += abs(ui.tableWidget_MatrixR->item(num - 1, combo_vec[h] - 1)->text().toDouble());
            }
            individual.push_back(r / de);
        }

        double H = 0.0;
        for (double h : individual)
            H += h;

        ui.comboBox_comb->setItemData(i, QVariant::fromValue<std::vector<double>>(individual), ECombComboRoles::IndividualCapacityVec);
        ui.comboBox_comb->setItemData(i, H, ECombComboRoles::IntegralCapacity);

        if (H > best_H)
        {
            best_H = H;
            m_BestCombIdx = i;
        }
    }

    ui.comboBox_comb->setCurrentIndex(m_BestCombIdx);
    ui.label_best_comb->setText(QString("Best combination: %1").arg(ui.comboBox_comb->itemText(m_BestCombIdx)));
}

void Hellwig::PrepareBestCombMatrix(uint rows_count, uint columns_count, arma::mat& out)
{
	out.reshape(rows_count, columns_count);
	std::vector <uint> comb_vec = ui.comboBox_comb->itemData(m_BestCombIdx, ECombComboRoles::CombinationVec).value<std::vector<uint>>();
	for (int i = 0; i < columns_count; i++)
	{
		if (i < comb_vec.size())
		{
			for (int j = 0; j < rows_count; j++)
				out(j, i) = ui.tableWidget_Data->item(j, comb_vec[i])->text().toDouble();
		}
		else
		{
			for (int j = 0; j < rows_count; j++)
				out(j, i) = 1.0;
		}
	}
}

QString Hellwig::PrepareDaString(const arma::mat& mat)
{
	QString da;
	for (int i = 0; i < mat.n_rows; i++)
	{
		da += QString::number(sqrt(mat(i, i))) + "\n";
	}
	return da;
}

void Hellwig::CalcY(uint rows_count, const arma::vec& vec, const std::vector <uint>& comb_vec)
{
	m_CalcY.clear();
	m_CalcY.resize(rows_count, 0.0);
	for (int i = 0; i < rows_count; i++)
	{
		for (int j = 0; j < comb_vec.size(); j++)
		{
			m_CalcY[i] += vec[j] * ui.tableWidget_Data->item(i, comb_vec[j])->text().toDouble();
		}
		m_CalcY[i] += *vec.end();
	}
}

double Hellwig::CalcR2(uint rows_count)
{
	double sum1 = 0.0;
	double sum2 = 0.0;
	double avg_y = CMath::CalcAvg(m_Data, 0);

	std::vector <double> y_std_vec;
	m_Data.GetY(y_std_vec);
	for (int i = 0; i < rows_count; i++)
	{
		sum1 += (m_CalcY[i] - avg_y) * (m_CalcY[i] - avg_y);
		sum2 += (y_std_vec[i] - avg_y) * (y_std_vec[i] - avg_y);
	}
	return sum1 / sum2;
}

double Hellwig::CalcV(double su)
{
	return su / CMath::CalcAvg(m_Data, 0) * 100.0;
}

void Hellwig::DrawChart(double& max_x, double& max_y)
{
	double x_mod = 100.0;
	double y_mod = 500.0;

	QPen pen_b;
	pen_b.setWidth(2);
	QPen pen_r(QColor(255, 0, 0, 255));
	pen_r.setWidth(5);
	QPen pen_g(QColor(0, 255, 0, 255));
	pen_g.setWidth(5);
	QBrush brush_r(QColor(255, 0, 0, 255));
	QBrush brush_g(QColor(0, 255, 0, 255));

	std::vector <double> y_std_vec;
	m_Data.GetY(y_std_vec);
	QPointF last_y(0.0, -(m_CalcY[0] / y_mod));
	QPointF last_calc_y(0.0, -(y_std_vec[0] / y_mod));
	m_Scene->addEllipse(last_y.x() - 5.0, last_y.y() - 5.0, 10.0, 10.0, pen_b, brush_r)->setZValue(1.0);
	m_Scene->addEllipse(last_calc_y.x() - 5.0, last_calc_y.y() - 5.0, 10.0, 10.0, pen_b, brush_g)->setZValue(1.0);
	for (int i = 1; i < m_CalcY.size(); i++)
	{
		QPointF y((double)i * x_mod, -(m_CalcY[i] / y_mod));
		QPointF calc_y((double)i * x_mod, -(y_std_vec[i] / y_mod));
		m_Scene->addLine(QLineF(last_y, y), pen_r);
		m_Scene->addLine(QLineF(last_calc_y, calc_y), pen_g);
		last_y = y;
		last_calc_y = calc_y;
		m_Scene->addEllipse(y.x() - 5.0, y.y() - 5.0, 10.0, 10.0, pen_b, brush_r)->setZValue(1.0);
		m_Scene->addEllipse(calc_y.x() - 5.0, calc_y.y() - 5.0, 10.0, 10.0, pen_b, brush_g)->setZValue(1.0);

		max_x = (y.x() > max_x) ? y.x() : max_x;
		max_y = (y.y() < max_y) ? y.y() : max_y;
		max_x = (calc_y.x() > max_x) ? calc_y.x() : max_x;
		max_y = (calc_y.y() < max_y) ? calc_y.y() : max_y;
	}
}

void Hellwig::DrawHelpers(const double& max_x, const double& max_y)
{
	QPen pen_b;
	pen_b.setCapStyle(Qt::RoundCap);
	pen_b.setWidth(2);
	double mod = 100.0;
	QLineF v_line(0.0, 0.0, 0.0, max_y - 200.0);
	QLineF h_line(0.0, 0.0, max_x + 150.0, 0.0);
	m_Scene->addLine(v_line, pen_b);
	m_Scene->addLine(h_line, pen_b);

	int h_count = (int)(h_line.length() / mod);
	for (int i = 1; i < h_count; i++)
	{
		double temp = (double) i * mod;
		m_Scene->addLine(temp, -10.0, temp, 10.0, pen_b);
	}

	int v_count = (int)(v_line.length() / mod);
	for (int i = 1; i < v_count; i++)
	{
		double temp = (double) i * (-mod);
		m_Scene->addLine(-10.0, temp, 10.0, temp, pen_b);
	}
}

void Hellwig::SetLabelsKmnkData(const QString& da, double su, double v, double r2)
{
	ui.label_kmnk_Da_result->setText(da);
	ui.label_kmnk_Su->setText(QString("Su: %1").arg(su));
	ui.label_kmnk_v->setText(QString("v: %1%").arg(v));
	ui.label_kmnk_R2->setText(QString("R2: %1").arg(r2));
	ui.label_kmnk_chosen->setText("Chosen variables combination: " + ui.comboBox_comb->itemText(m_BestCombIdx));
}

void Hellwig::SetResultLabels(const QString& da, const arma::vec& vec)
{
	QString result;
	std::vector <uint> comb_vec = ui.comboBox_comb->itemData(m_BestCombIdx, ECombComboRoles::CombinationVec).value<std::vector<uint>>();
	for (int i = 0; i < vec.n_elem; i++)
	{
		if (vec(i) >= 0.0)
			result += "+ ";

		if (i < comb_vec.size())
			result += QString::number(vec(i)) + "x" + QString::number(comb_vec[i]) + " ";
		else
			result += QString::number(vec(i)) + " ";
	}

	if (result[0] == '+')
		result[0] = ' ';

	QString result2(" ");
	QStringList da_list = da.split("\n");
	da_list.pop_back();
	for (QString str : da_list)
	{
		result2 += "(" + str + ")" + "    ";
	}
	ui.label_kmnk_result->setText(result);
	ui.label_kmnk_result_2->setText(result2);
}

QTableWidgetItem* Hellwig::GetTableItem(QTableWidget* table, uint row, uint column)
{
    QTableWidgetItem* it = table->item(row, column);
    if (!it)
    {
        it = new QTableWidgetItem();
        table->setItem(row, column, it);
        it->setFlags(it->flags() & ~Qt::ItemIsEditable);
    }
    return it;
}


void Hellwig::ClearData()
{
    ui.tableWidget_Data->clear();
    m_Data.Clear();
}


void Hellwig::ClearRR0()
{
    ui.tableWidget_MatrixR->clear();
    ui.tableWidget_MatrixR0->clear();
}


void Hellwig::ClearHellwig()
{
    ui.label_comb_num->setText("Combinations number: 0");
    ui.label_best_comb->setText("Best combination: 0");
    ui.label_int_cap->setText("Integral capacity: H0 = 0");
    ui.tableWidget_indv_cap->clear();
    ui.comboBox_comb->clear();
}

void Hellwig::ClearKmnk()
{
    ui.label_kmnk_chosen->setText("Chosen variables combination:");
    ui.label_kmnk_result->setText("");
	ui.label_kmnk_result_2->setText("");
    ui.label_kmnk_Su->setText("Su:");
    ui.label_kmnk_R2->setText("R2:");
    ui.label_kmnk_v->setText("v:");
    ui.label_kmnk_Da_result->setText("");
	m_CalcY.clear();
}

void Hellwig::ClearChart()
{
	m_Scene->clear();
}

// SLOTS
//////////////////////////////////////////////////////////////////////////
bool Hellwig::OnLoadDataTriggered()
{
    if (!m_Data.IsEmpty())
    {
        if (QMessageBox::warning(this, tr("Warning!"), tr("You will lost current data. Are you sure?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
            return false;
    }

    m_Data.Clear();
    QString file_path;

#ifdef _DEBUG | DEBUG
    file_path = QFileDialog::getOpenFileName(this, tr("Open data file"), QString("data.data"), "*.data");
#else
    file_path = QFileDialog::getOpenFileName(this, tr("Open data file"));
#endif

    if (CDataParser::ParseData(file_path, m_Data))
    {
        TableDataSetSize(m_Data.data.size(), m_Data.x_num + 1);
        TableDataPassLoadedData(m_Data);
        TableR0SetSize(m_Data.x_num, 1);
        TableR0CalcData(m_Data);
        TableRSetSize(m_Data.x_num, m_Data.x_num);
        TableRCalcData(m_Data);
        return true;
    }

    QMessageBox::critical(this, tr("Error"), tr("Application couldn't load given data!"));
    return false;
}

bool Hellwig::OnCalcHellwigVariableChoice()
{
    if (m_Data.data.empty())
    {
        if (!OnLoadDataTriggered())
            return false;
    }

    CalcAllCombinations();
    CalcCapacity();
    return true;
}

bool Hellwig::OnCalcKmnk()
{
    if (m_Data.data.empty()
        || ui.comboBox_comb->count() < 1)
    {
        if (!OnCalcHellwigVariableChoice())
            return false;
    }

	uint columns_count = m_Data.x_num;
	uint rows_count = ui.tableWidget_Data->rowCount();
	std::vector <uint> comb_vec = ui.comboBox_comb->itemData(m_BestCombIdx, ECombComboRoles::CombinationVec).value<std::vector<uint>>();

	arma::mat mat_x;
	std::vector <double> y_std_vec;
	PrepareBestCombMatrix(rows_count, columns_count, mat_x);
	m_Data.GetY(y_std_vec);

	double su = 0.0;
	double v = 0.0;
	double r2 = 0.0;
	try
	{
		arma::mat mat_y(y_std_vec);
		arma::vec vec_y(y_std_vec);
		arma::mat mat_x_trans = mat_x.t();
		arma::vec vec_a = (mat_x_trans * mat_x).i() * (mat_x_trans * vec_y);
		arma::mat mat_a(vec_a);
		arma::mat mat_su2 = (1.0 / (double)(rows_count - 3)) * ((mat_y.t() * mat_y) - mat_y.t() * mat_x * mat_a);
		arma::mat mat_d2a = mat_su2(0, 0) * (mat_x_trans * mat_x).i();

		QString da = PrepareDaString(mat_d2a);
		CalcY(rows_count, vec_a, comb_vec);
		su = sqrt(mat_su2(0, 0));
		v = CalcV(su);
		r2 = CalcR2(rows_count);

		SetLabelsKmnkData(da, su, v, r2);
		SetResultLabels(da, vec_a);
	}
	catch (std::runtime_error)
	{
		QMessageBox::critical(this, tr("Error!"), tr("Error occured during kmnk calc. Probably wrong matrices."));
		return false;
	}
    return true;
}

bool Hellwig::OnGenerateChart()
{
	if (m_Data.data.empty()
		|| ui.comboBox_comb->count() < 1
		|| m_CalcY.empty())
	{
		if (!OnCalcKmnk())
			return false;
	}

	double max_x = 0.0;
	double max_y = 0.0;
	DrawChart(max_x, max_y);
	DrawHelpers(max_x, max_y);
	m_Scene->setSceneRect(QRectF(-150.0, max_y - 300.0, abs(max_x) + 450.0, abs(max_y) + 350.0));
	return true;
}

void Hellwig::OnClearAll()
{
    ClearData();
    ClearRR0();
    ClearHellwig();
	ClearKmnk();
	ClearChart();
}

void Hellwig::OnCombComboIndexChanged(int idx)
{
    ui.tableWidget_indv_cap->clear();
    double H = ui.comboBox_comb->itemData(idx, ECombComboRoles::IntegralCapacity).toDouble();
    ui.label_int_cap->setText(QString("Integral capacity: H%1 = %2").arg(idx + 1).arg(H));

    QStringList headers;
    std::vector <double> ind_vec = ui.comboBox_comb->itemData(idx, ECombComboRoles::IndividualCapacityVec).value<std::vector<double>>();
    ui.tableWidget_indv_cap->setColumnCount(1);
    ui.tableWidget_indv_cap->setRowCount(ind_vec.size());
    for (int i = 0; i < ind_vec.size(); i++)
    {
        headers << "h" + QString::number(idx + 1) + "_" + QString::number(i + 1);
        QTableWidgetItem* it = GetTableItem(ui.tableWidget_indv_cap, i, 0);
        it->setText(QString::number(ind_vec[i]));
    }
    ui.tableWidget_indv_cap->setVerticalHeaderLabels(headers);
}

void Hellwig::OnGraphZoomIn()
{
	m_ZoomFactor += 0.1;
	QTransform transform;
	transform.scale(m_ZoomFactor, m_ZoomFactor);
	ui.graphicsView->setTransform(transform);
}

void Hellwig::OnGraphZoomOut()
{
	m_ZoomFactor -= 0.1;
	QTransform transform;
	transform.scale(m_ZoomFactor, m_ZoomFactor);
	ui.graphicsView->setTransform(transform);
}

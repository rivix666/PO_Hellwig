#include "hellwig.h"
#include <QFileDialog>
#include <QMessageBox>

#include "DataParser.h"
#include "Utils.h"

Q_DECLARE_METATYPE(std::vector <uint>);
Q_DECLARE_METATYPE(std::vector <float>);

Hellwig::Hellwig(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    InitWidgets();
    InitToolBar();
    InitConnections();
}

Hellwig::~Hellwig()
{

}

// INIT
//////////////////////////////////////////////////////////////////////////
void Hellwig::InitWidgets()
{
    ui.tableWidget_Data->setSortingEnabled(false);

}

void Hellwig::InitToolBar()
{
    QAction* act = ui.mainToolBar->addAction(QIcon(":/Resources/folder_vertical_open.png"), tr("Load data file"), this, &Hellwig::OnLoadDataTriggered);
    act->setShortcut(QKeySequence::Open);
    act = ui.mainToolBar->addAction(QIcon(":/Resources/calculator.png"), tr("Calc Helwigg!"), this, &Hellwig::OnCalcHellwigVariableChoice);
    act->setShortcut(QKeySequence(tr("Ctrl+Shift+C")));
    act = ui.mainToolBar->addAction(QIcon(":/Resources/broom.png"), tr("Clear"), this, &Hellwig::OnClearAll);
    act->setShortcut(QKeySequence(tr("Ctrl+Delete")));
}


void Hellwig::InitConnections()
{
    connect(ui.pushButton_calc_hellwig,  &QPushButton::clicked, this, &Hellwig::OnCalcHellwigVariableChoice);
    connect(ui.pushButton_clear_hellwig, &QPushButton::clicked, this, &Hellwig::ClearHellwig);
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
        float correl = CMath::Correl(data, 0, i + 1); // cause under idx 0 we store Y
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
            float correl = (i == j) ? 1.0f : CMath::Correl(data, i + 1, j + 1);
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
    for (int i = 0; i < ui.comboBox_comb->count(); i++)
    {
        std::vector <uint> combo_vec = ui.comboBox_comb->itemData(i, Qt::UserRole).value<std::vector<uint>>();
        std::vector <float> individual;
        for (const uint& num : combo_vec)
        {
            float r = pow(ui.tableWidget_MatrixR0->item(num - 1, 0)->text().toFloat(), 2);
            float de = 0.0f;
            for (int h = 0; h < combo_vec.size(); h++)
            {
                de += abs(ui.tableWidget_MatrixR->item(num - 1, combo_vec[h] - 1)->text().toFloat());
            }
            individual.push_back(r / de);
        }

        float H = 0.0f;
        for (float h : individual)
            H += h;

        ui.comboBox_comb->setItemData(i, QVariant::fromValue<std::vector<float>>(individual), ECombComboRoles::IndividualCapacityVec);
        ui.comboBox_comb->setItemData(i, H, ECombComboRoles::IntegralCapacity);
    }
}

void Hellwig::ChooseBestCapacity()
{
    int idx = 0;
    float H = 0.0f;
    for (int i = 0; i < ui.comboBox_comb->count(); i++)
    {
        float temp = ui.comboBox_comb->itemData(i, ECombComboRoles::IntegralCapacity).toFloat();
        if (temp > H)
        {
            H = temp;
            idx = i;
        }
    }

    ui.comboBox_comb->setCurrentIndex(idx);
    ui.label_best_comb->setText(QString("Best combination: %1").arg(ui.comboBox_comb->itemText(idx)));
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

void Hellwig::OnCalcHellwigVariableChoice()
{
    if (m_Data.data.empty())
    {
        if (!OnLoadDataTriggered())
            return;
    }

    CalcAllCombinations();
    CalcCapacity();
    ChooseBestCapacity();
}

void Hellwig::OnClearAll()
{
    ClearData();
    ClearRR0();
    ClearHellwig();
}

void Hellwig::OnCombComboIndexChanged(int idx)
{
    ui.tableWidget_indv_cap->clear();
    float H = ui.comboBox_comb->itemData(idx, ECombComboRoles::IntegralCapacity).toFloat();
    ui.label_int_cap->setText(QString("Integral capacity: H%1 = %2").arg(idx + 1).arg(H));

    QStringList headers;
    std::vector <float> ind_vec = ui.comboBox_comb->itemData(idx, ECombComboRoles::IndividualCapacityVec).value<std::vector<float>>();
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

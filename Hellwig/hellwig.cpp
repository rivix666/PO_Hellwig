#include "hellwig.h"
#include <QFileDialog>
#include <QMessageBox>

#include "DataParser.h"
#include "Utils.h"

Q_DECLARE_METATYPE(std::vector <uint>);

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
    act = ui.mainToolBar->addAction(QIcon(":/Resources/broom.png"), tr("Clear"), this, &Hellwig::OnClearAll);
}


void Hellwig::InitConnections()
{
    connect(ui.pushButton_calc_hellwig,  &QPushButton::clicked, this, &Hellwig::OnCalcHellwigVariableChoice);
    connect(ui.pushButton_clear_hellwig, &QPushButton::clicked, this, &Hellwig::ClearHellwig);
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

void Hellwig::ComboCombinationsCalc(const std::vector <uint>& vec, const int& len, const int& start, std::vector <uint> result)
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
        ComboCombinationsCalc(vec, len - 1, i + 1, result);
    }
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
    ui.listWidget_indv_cap->clear();
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

    std::vector <uint> vec;
    for (int i = 1; i <= m_Data.x_num; i++)
        vec.push_back(i);

     for (int i = 1; i <= m_Data.x_num; i++)
     {
         std::vector <uint> result(i, 0);
         ComboCombinationsCalc(vec, i, 0, result);      
         ui.label_comb_num->setText(QString("Combinations number: %1").arg(ui.comboBox_comb->count()));
    }
}

void Hellwig::OnClearAll()
{
    ClearData();
    ClearRR0();
    ClearHellwig();
}

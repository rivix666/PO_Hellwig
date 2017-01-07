#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_hellwig.h"
#include "Utils.h"

class Hellwig : public QMainWindow
{
	Q_OBJECT

public:
	Hellwig(QWidget *parent = 0);
	~Hellwig();

private:
    // Init
    void InitWidgets();
    void InitToolBar();
    void InitConnections();

    void TableDataSetSize(uint rows, uint columns);
    void TableDataPassLoadedData(const SDataIn& data);
    void TableR0SetSize(uint rows, uint columns);
    void TableR0CalcData(const SDataIn& data);
    void TableRSetSize(uint rows, uint columns);
    void TableRCalcData(const SDataIn& data);
//     void ComboCombinationsCalc()

    // Aux
    QTableWidgetItem* GetTableItem(QTableWidget* table, uint row, uint column);

    Ui::HellwigClass ui;
    SDataIn m_Data;

private slots:
    void OnLoadDataTriggered();
    void OnCalcHellwigVariableChoice();
};

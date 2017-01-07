#pragma once
#include <QtWidgets/QMainWindow>
#include <armadillo> 
#include "ui_hellwig.h"
#include "Utils.h"

class QGraphicsScene;

class Hellwig : public QMainWindow
{
    Q_OBJECT

public:
    Hellwig(QWidget *parent = 0);
    ~Hellwig();

private:
    // Init
    void InitToolBar();
    void InitConnections();

    void TableDataSetSize(uint rows, uint columns);
    void TableDataPassLoadedData(const SDataIn& data);
    void TableR0SetSize(uint rows, uint columns);
    void TableR0CalcData(const SDataIn& data);
    void TableRSetSize(uint rows, uint columns);
    void TableRCalcData(const SDataIn& data);

    // Aux
    void CalcAllCombinations();
    void CalcCombinations(const std::vector <uint>& vec, const int& len, const int& start, std::vector <uint> result);
    void CalcCapacity();
	void PrepareBestCombMatrix(uint rows_count, uint columns_count, arma::mat& out);
	QString PrepareDaString(const arma::mat& mat);
	void CalcY(uint rows_count, const arma::vec& vec, const std::vector <uint>& comb_vec);
	double CalcR2(uint rows_count);
	double CalcV(double su);

	void SetLabelsKmnkData(const QString& da, double su, double v, double r2);
	void SetResultLabels(const QString& da, const arma::vec& vec);
    QTableWidgetItem* GetTableItem(QTableWidget* table, uint row, uint column);

    void ClearData();
    void ClearRR0();
    void ClearHellwig();
    void ClearKmnk();
	void ClearChart();

    Ui::HellwigClass ui;
	QGraphicsScene* m_Scene;
    SDataIn m_Data;
	std::vector <double> m_CalcY;
    int m_BestCombIdx;

private slots:
    bool OnLoadDataTriggered();
    bool OnCalcHellwigVariableChoice();
    bool OnCalcKmnk();
	bool OnGenerateChart();
    void OnClearAll();
    void OnCombComboIndexChanged(int idx);
};

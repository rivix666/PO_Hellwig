#pragma once
#include <Qt>
#include <vector>
#include <math.h>

#define RELEASE(x) { delete x; x = nullptr; }
#define SAFE_RELEASE(x) { if (x) { delete x; x = nullptr; } }

typedef unsigned int uint;
typedef std::vector <std::vector <double>> TDataVec;

namespace ECombComboRoles
{
    enum TYPE
    {
        CombinationVec = Qt::UserRole,
        IndividualCapacityVec,
        IntegralCapacity,
    };
};

struct SDataIn
{
    SDataIn() : x_num(0) {};

    uint x_num;
    TDataVec data;

    bool IsEmpty()
    {
        return data.empty();
    }

    void Clear()
    {
        data.clear();
        x_num = 0;
    }

	void GetY(std::vector <double>& out)
	{
		for (std::vector <double> vec : data)
			out.push_back(vec[0]);
	}
};

class CMath
{
public:
    static double Correl(const SDataIn& data, uint col0, uint col1)
    {
        double avg_col0 = CalcAvg(data, col0);
        double avg_col1 = CalcAvg(data, col1);

        double counter = 0.0;
        double denominator = 0.0;
        double sum_de0 = 0.0;
        double sum_de1 = 0.0;
        for (const std::vector <double>& vec : data.data)
        {
            counter += (vec[col0] - avg_col0) * (vec[col1] - avg_col1);
            sum_de0 += pow((vec[col0] - avg_col0), 2);
            sum_de1 += pow((vec[col1] - avg_col1), 2);
        }
        denominator = sqrt(sum_de0 * sum_de1);

        return counter / denominator;
    }

    static double CalcAvg(const SDataIn& data, uint col)
    {
        double avg = 0.0;
        for (const std::vector <double>& vec : data.data)
            avg += vec[col];

        avg /= (double)data.data.size();
        return avg;
    }

    static uint CalcAllCombinationsNum(uint num)
    {
        uint result = num;
        for (int i = 2; i <= num; i++)
        {
            result += CalcCombinationNum(num, i);
        }
        return result;
    }

    static uint CalcCombinationNum(uint n, uint k)
    {
        return Strong(n) / (Strong(k) * Strong(n - k));
    }

    static uint Strong(uint num)
    {
        uint result = 1;
        for (uint i = 2; i <= num; i++)       
            result *= i;
        return result;
    }
};

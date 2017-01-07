#pragma once
#include "Utils.h"
#include <QString>

class CDataParser
{
public:
    CDataParser() {};
    ~CDataParser() {};

    static bool ParseData(const QString& file_path, SDataIn& out);
};


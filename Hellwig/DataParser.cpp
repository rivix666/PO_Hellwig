#include "DataParser.h"
#include <QFile>
#include <QTextStream>

bool CDataParser::ParseData(const QString& file_path, SDataIn& out)
{
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) 
    {
        std::vector <float> vec;
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        out.x_num = (out.x_num < fields.size()) ? fields.size() : out.x_num;
        for (const QString& str : fields)
        {
            vec.push_back(str.toFloat());
        }
        out.data.push_back(vec);
    }

    out.x_num--;
    return true;
}

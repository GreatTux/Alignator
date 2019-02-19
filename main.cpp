#include <QCoreApplication>

#include <QVector>
#include <QHash>
#include <QRegularExpression>
#include <iostream>

int main(int, char *[])
{
    QStringList list;

    std::string in;
    while(std::getline(std::cin, in))
    {
        list << QString::fromStdString(in);
    }

    QHash<int, int> linePadding;
    QVector<int> colCount;

    const QString delimiter = "<<";

    // Split lines
    foreach(const QString& line, list)
    {
        QStringList parts = line.split(delimiter);

        int count = 0;

        // Get the tab size of the line from the first part
        linePadding[line.indexOf(QRegularExpression("\\S"))]++;

        foreach(const QString& part, parts)
        {
            QString simp = part.trimmed();
            int length = simp.length();
            if(colCount.size() <= count)
            {
                colCount.push_back(length);
            }
            else
            {
                if(colCount.at(count) < length)
                    colCount[count] = length;
            }
            count++;
        }
    }

    // Get the max occurence in linePadding
    int tabSize = 0;
    int max = 0;
    auto i = linePadding.constBegin();
    while (i != linePadding.end())
    {
        if(i.value() > max)
        {
            max = i.value();
            tabSize = i.key();
        }
        ++i;
    }

    // Construct output
    foreach(const QString& line, list)
    {
        QStringList parts = line.split(delimiter);

        int count = 0;

        std::cout << QString().fill(' ', tabSize).toStdString();

        foreach(const QString& part, parts)
        {
            QString out = part.trimmed();

            // Not Last part
            if(count+1 < parts.size())
            {
                out = out.leftJustified(colCount[count], ' ');
            }

            std::cout << out.toStdString();
            if(count+1 < parts.size())
            {
                std::cout << " " << delimiter.toStdString() << " ";
            }

            count++;
        }

        std::cout << std::endl;
    }

    return 0;
}

#include <QCoreApplication>
#include <QFileInfo>
#include <QTextStream>

#include <unistd.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream cin(stdin);
    QTextStream cout(stdout);

    QString path;

    if (argc > 1)
        path = argv[1];
    else
    {
        cout << "Enter file path: ";
        cout.flush();
        path = cin.readLine();
    }

    QFileInfo info(path);

    while (true)
    {
        if (!info.exists())
        {
            cout << "No such file: " + path << "\n";
            return 0;
        }
        usleep(1000);
        cout << info.size() << "\n";
        cout.flush();
    }

    return 0;
}
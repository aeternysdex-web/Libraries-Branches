#include "Newspaper.h"
using namespace std;

Newspaper::Newspaper(int paperId, const string& paperTitle, int paperYear,
    int paperIssueNumber, int paperCirculation, const string& paperPublisher)
    : LibraryItem(paperId, paperTitle, paperYear),
    issueNumber(paperIssueNumber), circulation(paperCirculation), publisher(paperPublisher) {}

int Newspaper::getIssueNumber() const { return issueNumber; }
int Newspaper::getCirculation() const { return circulation; }
string Newspaper::getPublisher() const { return publisher; }

string Newspaper::getType() const { return "Газета"; }
int Newspaper::getLoanDays() const { return 3; }

void Newspaper::printInfo(ostream& out) const {
    LibraryItem::printInfo(out); 
    out << "Номер выпуска: " << issueNumber << "\n";
    out << "Тираж: " << circulation << "\n";
    out << "Издатель: " << publisher << "\n";
}

void Newspaper::readFrom(istream& in) {
    LibraryItem::readFrom(in); 
    cout << "Номер выпуска: ";
    issueNumber = readNumber(in);
    cout << "Тираж: ";
    circulation = readNumber(in);
    cout << "Издатель: ";
    getline(in, publisher);
}

double Newspaper::calculateLossCost(int currentYear, ostream& out) const {
    const double BASE_PRICE = 2.0;
    double k = 1.0; 
    out << "Базовая цена газеты: " << BASE_PRICE << " руб.\n";
    out << "Коэффициент ценности (чем реже издание, тем он больше): 1.0 для газеты\n";
    if (circulation < 700) {
        k += 1.0;
        out << "  +1.0: малый тираж(меньше 700)\n";
    }
    if (currentYear - getYear() > 50) {
        k += 0.5;
        out << "  +0.5: старый выпуск(старше 50 лет)\n";
    }
    out << "Итоговый коэффициент: " << k << "\n";
    double cost = BASE_PRICE * k;
    out << "Стоимость утери: " << BASE_PRICE << " x " << k << " = " << cost << " руб.\n";
    return cost;
}

bool Newspaper::canTakeHome(int currentYear) const {
    const int MIN_CIRCULATION = 700;
    const int MAX_AGE = 15;
    bool smallCirculation = circulation < MIN_CIRCULATION;
    bool tooOld = currentYear - getYear() > MAX_AGE;
    return !smallCirculation && !tooOld;
}

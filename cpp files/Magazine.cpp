#include "Magazine.h"
#include "Collection.h"
using namespace std;

Magazine::Magazine(int magId, const string& magTitle, int magYear,
    const string& magTopic, int magIssueNumber, const string& magTargetAudience)
    : LibraryItem(magId, magTitle, magYear),
    topic(magTopic), issueNumber(magIssueNumber), targetAudience(magTargetAudience) {}

string Magazine::getTopic() const { return topic; }
int Magazine::getIssueNumber() const { return issueNumber; }
string Magazine::getTargetAudience() const { return targetAudience; }

string Magazine::getType() const { return "Журнал"; }
int Magazine::getLoanDays() const { return 7; }

void Magazine::printInfo(ostream& out) const {
    LibraryItem::printInfo(out);
    out << "Тематика: " << topic << "\n";
    out << "Номер выпуска: " << issueNumber << "\n";
    out << "Целевая аудитория: " << targetAudience << "\n";
}

void Magazine::readFrom(istream& in) {
    LibraryItem::readFrom(in);
    cout << "Тематика: ";
    getline(in, topic);
    cout << "Номер выпуска: ";
    issueNumber = readNumber(in);
    targetAudience = chooseAudience(in);
}

double Magazine::calculateLossCost(int currentYear, ostream& out) const {
    const double BASE_PRICE = 8.0;
    double k = 1.0;
    out << "Базовая цена журнала: " << BASE_PRICE << " руб.\n";
    out << "Коэффициент ценности(чем реже издание, тем он больше): 1.0 для журнала\n";
    if (issueNumber == 1) {
        k += 0.5;
        out << "  +0.5: первый номер(коллекционный)\n";
    }
    if (currentYear - getYear() > 50) {
        k += 0.5;
        out << "  +0.5: старый журнал(старше 50 лет)\n";
    }
    out << "Итоговый коэффициент: " << k << "\n";
    double cost = BASE_PRICE * k;
    out << "Стоимость утери: " << BASE_PRICE << " x " << k << " = " << cost << " руб.\n";
    return cost;
}

bool Magazine::suitableFor(string_view audience) const {
    return targetAudience == audience;
}

string Magazine::chooseAudience(istream& in) {
    Collection<string> audiences;
    audiences.add(new string("дети"));
    audiences.add(new string("подростки"));
    audiences.add(new string("взрослые"));
    audiences.add(new string("пенсионеры"));

    cout << "Целевая аудитория:\n";
    audiences.print(cout);
    cout << "Выберите номер: ";
    int number = readNumber(in);
    if (number < 1 || number > audiences.getCount()) {
        number = 3;
        cout << "Некорректный выбор, выбрано: " << *audiences.get(number - 1) << "\n";
    }
    return *audiences.get(number - 1);   
}

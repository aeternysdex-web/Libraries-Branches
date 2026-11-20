#include "Magazine.h"
#include "InvalidDataException.h"
#include "OutOfRangeException.h"
#include "Collection.h"
#include <format>
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
    string newTopic;
    getline(in, newTopic);
    if (newTopic.empty()) throw InvalidDataException("тематика не может быть пустой");
    cout << "Номер выпуска: ";
    int newIssueNumber = readNumber(in);
    if (newIssueNumber <= 0) throw InvalidDataException("номер выпуска должен быть больше 0");
    string newAudience = chooseAudience(in);
    topic = newTopic;
    issueNumber = newIssueNumber;
    targetAudience = newAudience;
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
    audiences.add(make_unique<string>("дети"));
    audiences.add(make_unique<string>("подростки"));
    audiences.add(make_unique<string>("взрослые"));
    audiences.add(make_unique<string>("пенсионеры"));

    cout << "Целевая аудитория:\n";
    audiences.print(cout);
    cout << "Выберите номер: ";
    int number = readNumber(in);
    if (number < 1 || number > audiences.getCount()) {
        throw OutOfRangeException(format("номер аудитории {} вне диапазона 1..{}", number, audiences.getCount()));
    }
    return *audiences.get(number - 1);
}

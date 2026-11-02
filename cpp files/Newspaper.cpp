#include "Newspaper.h"
using namespace std;

Newspaper::Newspaper(int paperId, const string& paperTitle, int paperYear,
                     int paperIssueNumber, int paperCirculation, const string& paperPublisher)
    : LibraryItem(paperId, paperTitle, paperYear),
      issueNumber(paperIssueNumber), circulation(paperCirculation), publisher(paperPublisher) {
}

Newspaper::~Newspaper() {}

int Newspaper::getIssueNumber() const { return issueNumber; }
int Newspaper::getCirculation() const { return circulation; }
string Newspaper::getPublisher() const { return publisher; }
void Newspaper::setIssueNumber(int newIssueNumber) { issueNumber = newIssueNumber; }
void Newspaper::setCirculation(int newCirculation) { circulation = newCirculation; }
void Newspaper::setPublisher(const string& newPublisher) { publisher = newPublisher; }

string Newspaper::getType() const { return "Газета"; }
int Newspaper::getLoanDays() const { return 3; }

bool Newspaper::canTakeHome(int currentYear) const {
    const int MIN_CIRCULATION = 700;
    const int MAX_AGE = 15;
    bool smallCirculation = circulation < MIN_CIRCULATION;
    bool tooOld = currentYear - getYear() > MAX_AGE;
    return !smallCirculation && !tooOld;
}

#include "Magazine.h"
using namespace std;

Magazine::Magazine(int magId, const string& magTitle, int magYear,
                   const string& magTopic, int magIssueNumber, const string& magTargetAudience)
    : LibraryItem(magId, magTitle, magYear),
      topic(magTopic), issueNumber(magIssueNumber), targetAudience(magTargetAudience) {
}

Magazine::~Magazine() {}

string Magazine::getTopic() const { return topic; }
int Magazine::getIssueNumber() const { return issueNumber; }
string Magazine::getTargetAudience() const { return targetAudience; }
void Magazine::setTopic(const string& newTopic) { topic = newTopic; }
void Magazine::setIssueNumber(int newIssueNumber) { issueNumber = newIssueNumber; }
void Magazine::setTargetAudience(const string& newTargetAudience) { targetAudience = newTargetAudience; }

string Magazine::getType() const { return "Журнал"; }
int Magazine::getLoanDays() const { return 7; }

bool Magazine::suitableFor(const string& audience) const {
    return targetAudience == audience;
}

#pragma once
#include "LibraryItem.h"

class Magazine : public LibraryItem {
private:
    std::string topic;
    int issueNumber;
    std::string targetAudience;

public:
    Magazine(int magId, const std::string& magTitle, int magYear,
             const std::string& magTopic, int magIssueNumber, const std::string& magTargetAudience);
    ~Magazine() override;

    std::string getTopic() const;
    int getIssueNumber() const;
    std::string getTargetAudience() const;
    void setTopic(const std::string& newTopic);
    void setIssueNumber(int newIssueNumber);
    void setTargetAudience(const std::string& newTargetAudience);

    std::string getType() const override;
    int getLoanDays() const override;
    bool suitableFor(const std::string& audience) const;
};

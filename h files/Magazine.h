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
    ~Magazine() override = default;

    std::string getTopic() const;
    int getIssueNumber() const;
    std::string getTargetAudience() const;

    std::string getType() const override;
    int getLoanDays() const override;
    void printInfo(std::ostream& out) const override;
    void readFrom(std::istream& in) override;
    double calculateLossCost(int currentYear, std::ostream& out) const override;

    bool suitableFor(std::string_view audience) const;

    static std::string chooseAudience(std::istream& in);

};

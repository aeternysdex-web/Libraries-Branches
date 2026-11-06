#pragma once
#include "LibraryItem.h"

class Newspaper : public LibraryItem {
private:
    int issueNumber;
    int circulation; // тираж
    std::string publisher;

public:
    Newspaper(int paperId, const std::string& paperTitle, int paperYear,
        int paperIssueNumber, int paperCirculation, const std::string& paperPublisher);
    ~Newspaper() override = default;

    int getIssueNumber() const;
    int getCirculation() const;
    std::string getPublisher() const;

    std::string getType() const override;
    int getLoanDays() const override;
    void printInfo(std::ostream& out) const override;
    void readFrom(std::istream& in) override;
    double calculateLossCost(int currentYear, std::ostream& out) const override;

    bool canTakeHome(int currentYear) const;

};

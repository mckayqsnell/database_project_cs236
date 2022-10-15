#ifndef PROJECT1_RULES_H
#define PROJECT1_RULES_H

#include "Stuff.h"
#include "Predicate.h"


class Rules: public Stuff {
private:
    int num_Rules;
    vector<Predicate*> predicates;
    Predicate* head_predicate;
public:
    Rules();
    ~Rules();
    void setNumRules(int numRules);
    void addPredicate(Predicate *predicate);
    void setHeadPredicate(Predicate *predicate);
    vector<Predicate*> getPredicateList();
    Predicate* getHeadPredicate();
    int getNumRules();
    string toString();
};


#endif //PROJECT1_RULES_H

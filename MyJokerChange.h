//
// Created by Daniel Meltzer on 23/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYJOKERCHANGE_H
#define CS_TAU_CPP_EX_2_MYJOKERCHANGE_H


#include <memory>
#include "JokerChange.h"
#include "MyPoint.h"

/**
 *
 */
class MyJokerChange: public JokerChange {
public:
    MyJokerChange(const std::shared_ptr<Point> &positionChange, char newCharRepresentation);

/**
     * get new position of joker
     * @return
     */
    const Point &getJokerChangePosition() const override;

    char getJokerNewRep() const override;

    ~MyJokerChange() override;

private:
    MyPoint positionChange;
    char newJokerRepresntation;
};


#endif //CS_TAU_CPP_EX_2_MYJOKERCHANGE_H

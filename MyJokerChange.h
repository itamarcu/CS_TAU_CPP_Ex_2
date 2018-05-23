//
// Created by Daniel Meltzer on 23/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYJOKERCHANGE_H
#define CS_TAU_CPP_EX_2_MYJOKERCHANGE_H


#include <memory>
#include "JokerChange.h"
#include "MyPoint.h"

/**
 * @authors Daniel Meltzer and Itamar Curiel
 * this class let's you express change in joker piece
 */
class MyJokerChange: public JokerChange {
public:

    /**
     * MyJokerChange constructor
     * @warning in case no change accord no need to create instance
     * @param positionChange joker position to change to
     * @param newJokerRepresentation  new joker representation to change to
     */
    MyJokerChange(const MyPoint &positionChange, char newJokerRepresentation);

   /**
    * get position change of joker
    * @return Point subclass instance for new position
    */
    const Point &getJokerChangePosition() const override;

    /**
     * get new char representation of joker
     * @return new char joker representation(after change)
     */
    char getJokerNewRep() const override;

    ~MyJokerChange() override;

private:
    MyPoint positionChange;
    char newJokerRepresentation;
};


#endif //CS_TAU_CPP_EX_2_MYJOKERCHANGE_H

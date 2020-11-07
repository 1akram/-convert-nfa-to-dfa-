#ifndef AFND_H_INCLUDED
#define AFND_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>



 //*********
#define true 1
#define false 0
//*******
const char ALPHA_BET[26]="abcdefghijklmnopqrstuvwxyz";


// Id manager  generate a unique number


//this is just a simulation for oop  to help understanding  how the program work


//  static class ids manager{
static int stateIDS= -1;
static int transitionIDS= -1;

// int newTransitionID()   implementation  in afnd.c
// void resetTransitionID()   implementation  in afnd.c
// int newStateID()   implementation  in afnd.c
// void resetStateID()   implementation  in afnd.c

// }

// class Transition {
 typedef struct transition{
     int id;// transition id unique number
    int  alphaBet;// alphaBet of transition
    int  stateId;//  id of the state where the transition go
    struct transition *nextTransition;// pointer of next transition

    //Transition * createTransition(int alphaBet,int stateId)        implementation in afnd.c
   //void addTransitionToState(State * state,Transition *transition )
    //void showTransition(Transition transition)
    //void showTransitions(Transition *transitions)
    //Transition *  findTransition(Transition *transitions,int transitionId)
   //void deleteTransition(Transition **transitions  , int transitionId)
   //void deleteAllTransitions(Transition ** transitions)

}Transition;
//}

// class State{
typedef struct state{
    int id;   // state id unique number
    int isStartState; //  define if this state is a start state or not  ( false or  true)
    int isEndState; //  define if this state is a end state or not
    Transition *transitions;// transitions of this state
    struct state *nextState; // next state

    //State *createState(int isStartState,int IsEndState)    implementation in afnd.c
    //void addStateToAfnd(Afnd *afnd,State*state)
   // void showState(State state)
   // void showStates(State* states)
    //State*  findState(Afnd *afnd,int stateId)
    //void deleteState(Afnd ** afnd  , int stateId)
    //void deleteAllStates(Afnd ** afnd)

}State;
//}

//class Afnd{
typedef struct afnd{
    int nbStates;
    int alphaBetSize;
    State *states;

    //Afnd * createAfnd(int alphaBetSize)
    //void showAfnd(Afnd*afnd)

}Afnd;
//}



// this structure used for converting from afnd to afd
typedef struct idsList{  //   structure to store a list of  state ids
    int id;
    struct idsList  *nextId;
}IdsList;
typedef struct col{// structure for simulate  table of transitions;
    int afdStateId; // afd state id
    IdsList* afndIds;// equivalent  states of afnd
    struct col  *nextCol;
}TableOfTransitions;



#endif // AFND_H_INCLUDED

#include "afnd.h"

void debug(char msg[]){ // this function just for debug  and track the program errors

    int b;
    printf("%s",msg);
    scanf("%d",&b);
}


int newTransitionID (){
    transitionIDS=transitionIDS+1;
    return transitionIDS;
}
void resetTransitionID (){
    transitionIDS=-1;
}
int newStateID (){
    stateIDS=stateIDS+1;
    return stateIDS;
}
void resetStateID (){
    stateIDS=-1;
}


// creation functions
Transition * createTransition(int alphaBet,int stateId){ // this function   create a new transition  and return it
    Transition* transition=(Transition*)malloc(sizeof(Transition));
     transition->id=newTransitionID();
    transition->alphaBet=alphaBet;
    transition->stateId=stateId;
    transition->nextTransition=NULL;
    return  transition;

}
State *createState(int isStartState,int IsEndState){ // this function create a new state and return it
    State* state=(State*)malloc(sizeof(State));
    state->id=newStateID();
    state->isStartState=isStartState;
    state->isEndState=IsEndState;
    state->transitions=NULL;
    state->nextState=NULL;
    return state;
}
Afnd * createAfnd(int alphaBetSize){// create a new  afnd and return it
    resetStateID();// reset id to -1
    resetTransitionID();//reset id to -1
    Afnd *afnd=(Afnd*)malloc(sizeof(Afnd));
    afnd->alphaBetSize=alphaBetSize;
    afnd->nbStates=0;
    afnd->states=NULL;
    return afnd;
}
// end creation functions


//**********
//**********
//**********


// show ( print )functions
void showTransition(Transition transition){//this function show (print in the screen ) the information of transition one transition
     printf("  %d-\t transition with %c to state ( %d ) ",transition.id, ALPHA_BET[transition.alphaBet],transition.stateId);
}

void showTransitions(Transition *transitions){//this function show (print in screen) the information of all transitions of the state;

    if(transitions==NULL)
        return;
    showTransitions(transitions->nextTransition);//this function call it's self until the next transition ==null
    showTransition(*transitions);//call show transition function to print in screen information of transition
    printf("\n");
}

void showState(State state){// show (print)   informations of state
                                                    //       (n) = state
                                                    //      ->(n) = start state
                                                    //      *(n) = end state
                                                    //      so    ->*(n)   = start and end state in same time
    if(state.isStartState==true)//check if   state is a start state or not
        printf("->");
    if(state.isEndState==true)// check if   state is is a end state
        printf("*");
    printf("( %d )  : \n",state.id);
    showTransitions(state.transitions);//call function to show all transitions of this state
    printf("\n");

}

void showStates(State* states){// show informations of all states
    if(states==NULL)
        return;
    showStates(states->nextState);
    showState(*states);
    printf("\n");
}

void showAfnd(Afnd*afnd){

    if(afnd==NULL){
        printf(" afnd is empty \n");
        return;
    }

    printf("states number %d \n\n",afnd->nbStates);
    printf("AlphaBet : ");
    int i;
    for(i=0;i<afnd->alphaBetSize;i++)
        printf(" %c, ",ALPHA_BET[i]);
    printf("\n\n");
    showStates(afnd->states);
    printf("\n");



}
// end show functions
//*********
//*********

//delete functions

void deleteTransition(Transition **transitions  , int transitionId)// this function delete a transition who have the given id
{
    Transition  * tmp = *transitions;
    Transition*prev=NULL;
     if (tmp != NULL && tmp->id == transitionId)//if transition is the first one in the list of   transitions
    {
        *transitions = tmp->nextTransition;
        free(tmp);
        return;
    }

    while (tmp != NULL && tmp->id != transitionId)// search for transition
    {
        prev = tmp;
        tmp = tmp->nextTransition;
    }
    if (tmp == NULL) // if transition don't exist
        return;

    prev->nextTransition = tmp->nextTransition;

    free(tmp);  // free memory
}

 void deleteAllTransitions(Transition ** transitions){// this function delete all transition in the given state
    Transition *tmp;
    Transition *transition=*transitions;
    while( transition !=NULL){
            tmp=transition;
            transition= transition->nextTransition;
            free(tmp);
    }
    *transitions=transition; // set the pointer   to null
 }



 void deleteState(Afnd ** afnd  , int stateId)// this function delete a state who have the given id
{
    State  * tmp = (*afnd)->states;
    State*prev=NULL;

     if (tmp != NULL && tmp->id == stateId)//if state is the first one in the list of   states
    {
        (*afnd)->states = tmp->nextState;
    // when delete state you should delete all transition of the state first

        deleteAllTransitions(&(tmp->transitions));// out transitions

        // search and delete search and delete in transitions
        State*tmp1= (*afnd)->states;// list of states

        while(tmp1!=NULL){
                Transition *tr=tmp1->transitions;// list of transition of each state

            while(tr!=NULL){// while transitions not null do
                 if(tr->stateId==stateId){  // if transition  go to this state do

                     deleteTransition(&(tmp1->transitions),tr->id); // delete transition
                 }

                tr=tr->nextTransition;
            }
            tmp1=tmp1->nextState;
        }

         // end search and delete in transitions
        free(tmp);
        (*afnd)->nbStates=(*afnd)->nbStates - 1; // update the number of states
        return;
    }

    while (tmp != NULL && tmp->id != stateId)// search for state
    {
        prev = tmp;
        tmp = tmp->nextState;
    }
    if (tmp == NULL) // if state  don't exist
        return;

    prev->nextState = tmp->nextState;
    // when delete state you should delete all transition of the state first

    deleteAllTransitions(&(tmp->transitions));// out transitions
      // search and delete in transitions

    State*tmp1= (*afnd)->states;// list of states
    while(tmp1!=NULL){
            Transition *tr=tmp1->transitions;// list of transition of each state
        while(tr!=NULL){// while transitions not null do

            if(tr->stateId==stateId)// if transition  go to this state do
                deleteTransition(&(tmp1->transitions),tr->id); // delete transition
            tr=tr->nextTransition;
        }
        tmp1=tmp1->nextState;
    }

     // end  search and delete in transitions
    free(tmp);  // free memory
    (*afnd)->nbStates=(*afnd)->nbStates - 1; // update the number of states


}

 void deleteAllStates(Afnd ** afnd){ // delete all states in afnd

    State *tmp;
    State *state =   (*afnd) ->states;
    while( state !=NULL){ // check if there is a states in the afnd   i can use( nbStates >0) but i like this method
            tmp=state; // store the state in temp variable
            state= state->nextState;//move the pointer to next state
            deleteAllTransitions(&(tmp->transitions));// when delete state you should delete all transition of the state first
            free(tmp);// free memory
            (*afnd)->nbStates=(*afnd)->nbStates-1; // update the number of states
    }
     (*afnd) ->states=state; // set the pointer   to null
 }
//end delete functions


//**********
//**********
//**********

// append functions
void addTransitionToState(State * state,Transition *transition ){// this function add (append)  a transition to the given state
    transition->nextTransition= state->transitions;
    state->transitions=transition;
}

void addStateToAfnd(Afnd *afnd,State*state){ // add state to the given afnd
        state->nextState=afnd->states;
        afnd->states=state;
        afnd->nbStates=afnd->nbStates+1;
}
// end append functions
Transition*  findTransition(Transition *transitions,int transitionId){ // find a state by id  search in a afnd and return the state if exist or return null
    Transition *transition=transitions;
    while(transition != NULL){
        if(transition->id== transitionId){
            return transition;
        }
        transition=transition->nextTransition;
    }
    return NULL;
}


State*  findState(Afnd *afnd,int stateId){ // find a state by id  search in a afnd and return the state if exist or return null
    State *state=afnd->states;

    while(state != NULL){

        if(state->id== stateId){
            return state;
        }
        state=state->nextState;
    }
    return NULL;
}




int isExistInList(IdsList *idsList,int id){// check if the given id is exist in the list or not
    while(idsList!=NULL){
        if(idsList->id==id)
            return true;
        idsList=idsList->nextId;
    }
    return false;
}



int isThereEndStates(IdsList *idsList,Afnd *afnd){// check if there end states in the given list of states
    State *state;

while(idsList!=NULL){
    state=findState(afnd,idsList->id);

    if(state->isEndState==true){
         return true ;
    }
    idsList=idsList->nextId;
}
return false;
}



IdsList * addIdToList(IdsList * idsList,int id){// add id to a list of ids
    IdsList* ids =(IdsList*)malloc(sizeof(IdsList));
    ids->id=id;
    ids->nextId=idsList;
    idsList=ids;
    return idsList;
}

IdsList* getStartStates(Afnd *afnd){// get the start states in the afnd
IdsList * ids=NULL;
State *states=afnd->states;
while(states!=NULL){
    if(states->isStartState==true)// check if the state is start state if true add to a list of start states
        ids=addIdToList(ids,states->id);
    states=states->nextState;
}
return ids;//return list of start states
}

TableOfTransitions * addCol(TableOfTransitions * table ,int afdStateId,IdsList *afndIds){//add column  in table of transitions
    TableOfTransitions *col=(TableOfTransitions*)malloc(sizeof(TableOfTransitions));
    col->afdStateId=afdStateId;
    col->afndIds=afndIds;
    col->nextCol=NULL;
     if(table==NULL)// if table is empty add column else go to end of table
        return col;
    TableOfTransitions * tb=table;
     while(tb->nextCol!=NULL){// go to end of table and add new column
        tb=tb->nextCol;
     }
   tb->nextCol=col;
   return table;

}


IdsList* getStates(int alphabet,IdsList* statesIds,Afnd*afnd){// get list of states where the given states(statesIds)  go with the alphabet
    IdsList* ids=NULL;
    State * state;
    while(statesIds!=NULL){
        state=findState(afnd,statesIds->id);// find state with the given id
        Transition *transitions=state->transitions;
        while(transitions!=NULL){
            if(transitions->alphaBet==alphabet&&isExistInList(ids,transitions->stateId)==false) //check if state have transition withe given alphabet  if true check if  its not exist in states ids
                ids=addIdToList(ids,transitions->stateId); // add the id of state where the transition with given alphabet go
            transitions=transitions->nextTransition;
        }
        statesIds=statesIds->nextId;
    }
    return ids;
}

int isEqualList(IdsList *list1,IdsList* list2){// check if the given lists is equals
    int nbIdsInList1=0;
    int nbIdsInList2=0;
    IdsList* l1=list1;
    IdsList* l2=list2;
    while(l1!=NULL||l2!=NULL){// get number of ids in each list
        if(l1!=NULL){
            l1=l1->nextId;
            nbIdsInList1=nbIdsInList1+1;
        }
        if(l2!=NULL){
            l2=l2->nextId;
            nbIdsInList2=nbIdsInList2+1;
        }
    }

    if(nbIdsInList1!=nbIdsInList2)// if number of ids in each list not equal return false(the lists are not equal)
        return false;

    while(list1!=NULL){// number of ids in each list are equal   then check that all ids in list 1 exist in list 2
                                    // i noticed  that i can use isExistInList   late  after i write the code
        int isEqual=false;
        l2=list2;
        while(l2!=NULL){
            if(list1->id==l2->id){
                isEqual=true;
                break;
            }
            l2=l2->nextId;
        }
        if(isEqual==false)
            return false;
        list1=list1->nextId;
    }
    return true;

}


TableOfTransitions* isStateExistIntable(TableOfTransitions* table,IdsList *idsList){//check if the the given list of state ids is exist in table of transitions  like
    while(table!=NULL){
        if(isEqualList(idsList,table->afndIds)==true)
            return table;
        table=table->nextCol;
    }
    return NULL;
}
/*********/
void showIds(IdsList *ids){// just print the list of ids in screen;
while(ids!=NULL){
    printf("%d,",ids->id);
    ids=ids->nextId;
}

}

void deleteTableOfTransitions(TableOfTransitions*table){ //delete table  of transitions   to free the memory   delete  the list of ids in each column then delete the column;
    while(table!=NULL){
        while(table->afndIds!=NULL){// delete list of ids
            IdsList *tmpId=table->afndIds;
            table->afndIds=table->afndIds->nextId;
            free(tmpId);

        }
        TableOfTransitions* tmpCol=table; // delete column of table
        table=table->nextCol;
        free(tmpCol);
    }
}

/***********/
void convertAfndToAfd(Afnd* afnd,Afnd *afd){// convert afnd to afd

    TableOfTransitions * table=NULL;
    IdsList *statesIids=getStartStates(afnd);// get start states in afnd
    State* startState=createState(true,isThereEndStates(statesIids,afnd)); // create the equal state in dfa  of start states in afnd
    addStateToAfnd(afd,startState);// append the state to afd
    table=addCol(table,startState->id,statesIids); // add new column to table of transition with the start state
    TableOfTransitions *tb=table;
    printf("\ntable of transitions\n");
    printf("\n-----------------------\n");
    while(tb  !=NULL){
            int i;
             printf("\n(%d)  {",tb->afdStateId);showIds(tb->afndIds);printf("}\n" );
            for( i=0; i< afd->alphaBetSize ; i++){// fill table of transitions
                    statesIids=getStates(i,tb->afndIds,afnd);// get states that can go to them  with alphabet i (get transition of state afndIds with alphabet i)
                    printf("\t%c ==>{",ALPHA_BET[i]);showIds(statesIids);printf("}\n");
                    if(statesIids!=NULL&&isStateExistIntable(table,statesIids)==NULL){ // check if  there is any transition with   if true check if  it's doesn't exist in table
                        State*state=createState(false,isThereEndStates(statesIids,afnd));// if state doesn't exist create it and add it to afd and to transition tabel;
                        addStateToAfnd(afd,state);
                        table=addCol(table,state->id,statesIids);
                    }
            }
            printf("\n-----------------------\n");
        tb =tb->nextCol;
    }
    tb=table;
    while(tb!=NULL){
        int i;
       for( i=0; i< afd->alphaBetSize ; i++){// create the transition of afd  from table of transition
                    statesIids=getStates(i,tb->afndIds,afnd);
                    if(statesIids!=NULL){
                        TableOfTransitions *col=isStateExistIntable(table,statesIids);
                        State*state=findState(afd,tb->afdStateId);
                        addTransitionToState(state,createTransition(i,col->afdStateId));

                    }
            }
        tb =tb->nextCol;
    }
deleteTableOfTransitions(table);   // delete table of transition








}

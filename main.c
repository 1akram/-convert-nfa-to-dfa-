#include "afnd.c"





void main()
{
     int alphabet;

    while(true){
        system("cls");
        printf(" enter alphabet size : ");
        scanf("%d",&alphabet);
            if(alphabet<=26)  //check if alphabet is just from a to z
                break;
    }
    Afnd* afnd=createAfnd(alphabet);
    Afnd * afd= createAfnd(afnd->alphaBetSize);

    while(true){
            int choice;
            system("cls");//clear screen
            showAfnd(afnd);// show afnd in screen
            //menu
            printf("1 - add state \n");
            printf("2 - delete state \n");
            printf("3 - edit state(add or delete transition)\n");
             printf("4 - convert from afnd to afd\n");
            printf("5-exit");
            scanf("%d",&choice);
            if(choice==5)
                break;

            switch(choice){
                case 1:// add state to afnd
                    system("cls");
                    printf("is the state start state?\n1- yes\n2-no");
                    int isStartState;
                    scanf("%d",&isStartState);
                    if(isStartState==1)
                        isStartState=true;
                    else
                        isStartState=false;
                    printf("\nis the state end state?\n1- yes\n2-no");
                    int isEndstate;
                    scanf("%d",&isEndstate);
                    if(isEndstate==1)
                        isEndstate=true;
                    else
                        isEndstate=false;
                    State*state=createState(isStartState,isEndstate);
                        // create and add transition to a state
                    while(true){

                        system("cls");
                        showState(*state);
                        printf("! notice : you can't add transition to state doesn't exist  \n");
                        printf("1- add transition \n ");
                        printf("2- back");
                        scanf("%d",&choice);
                        if(choice!=1)
                            break;
                        int transitionAlphabet;
                        while(true){ //read the alphabet of transition
                            system("cls");
                            printf("enter transition alphabet\n");
                            for(choice=0;choice<afnd->alphaBetSize;choice++)
                                printf("%d-%c\n",choice,ALPHA_BET[choice]);
                            scanf("%d",&transitionAlphabet);
                            if(transitionAlphabet<afnd->alphaBetSize) //check if the alphabet correct
                                    break;
                        }
                        int stateId;
                        while(true){// read the state where transition should go
                            system("cls");
                            printf("enter state id where transition go  ");
                            scanf("%d",&stateId);
                            if(findState(afnd,stateId)!=NULL||state->id==stateId) // check if state exist in afnd or if its this state
                                break;
                        }
                    Transition * transition=createTransition(transitionAlphabet,stateId);
                    showTransition(*transition);
                    printf("\ndid you want to add this transition  to state%d?\n1- yes\n2-no",state->id);
                     scanf("%d",&choice);
                    if(choice==1)
                            addTransitionToState(state,transition);
                    else
                            deleteTransition(&(state->transitions),transition->id);
                    }
                    // end create and add transition to a state;
                    system("cls");
                    showState(*state);
                    printf("did you want to add this state to afnd?\n1- yes\n2-no");
                     scanf("%d",&choice);
                    if(choice==1)
                            addStateToAfnd(afnd,state);
                    else
                            deleteState(&afnd,state->id);


                    break;
                    //end add state to afnd
                case 2://delete state
                    system("cls");
                    printf("enter state id");
                    scanf("%d",&choice);
                    State *deletedState=findState(afnd,choice);//get the state
                    if(deletedState!=NULL){// check if state exist in afnd
                        system("cls");
                        showState(*deletedState);
                        printf("\ndid you want to delete this state?\n1- yes \n2-no ");//confirmation message
                        scanf("%d",&choice);
                        if(choice==1)
                            deleteState(&afnd,deletedState->id);

                    }
                     break;
                     //end delete state
                case 3:
                      // edit state
                        system("cls");
                        printf("enter the state id");
                        scanf("%d",&choice);
                        State *editState=findState(afnd,choice);
                        if(editState==NULL) //check if state exist or not
                            break;
                        while(true){

                            system("cls");
                            showState(*editState);
                            printf("! notice : you can't add transition to state doesn't exist  in afnd\n");
                            printf("1- add transition \n");
                            printf("2- delete transition\n");
                            printf("3- back");
                            scanf("%d",&choice);
                            if(choice==3)
                                break;
                            switch(choice){
                                case 1:
                                    system("cls");
                                    int transitionAlphabet;
                                    while(true){ //read the alphabet of transition
                                        system("cls");
                                        printf("enter transition alphabet\n");
                                        for(choice=0;choice<afnd->alphaBetSize;choice++)
                                            printf("%d-%c\n",choice,ALPHA_BET[choice]);
                                        scanf("%d",&transitionAlphabet);
                                        if(transitionAlphabet<afnd->alphaBetSize) //check if the alphabet correct
                                                break;
                                        }
                                    int stateId;
                                    while(true){// read the state where transition should go
                                        system("cls");
                                        printf("enter state id where transition go  ");
                                        scanf("%d",&stateId);
                                        if(findState(afnd,stateId)!=NULL) // check if state exist in afnd
                                            break;
                                    }
                                    Transition * transition=createTransition(transitionAlphabet,stateId);
                                    showTransition(*transition);
                                    printf("\ndid you want to add this transition  to state%d?\n1- yes\n2-no",editState->id);
                                     scanf("%d",&choice);
                                     if(choice==1)
                                            addTransitionToState(editState,transition);
                                     else
                                            deleteTransition(&(editState->transitions),transition->id);
                                // end create and add transition to a state;
                                    break;
                                case 2:
                                    system("cls");
                                    printf("enter transition id");
                                    scanf("%d",&choice);
                                    Transition *deletedTransition=findTransition(editState->transitions,choice);//get the transition
                                    if(deletedTransition!=NULL){// check if transition exist in the state
                                        system("cls");
                                        showTransition(*deletedTransition);
                                        printf("\ndid you want to delete this transition?\n1- yes \n2-no ");//confirmation message
                                        scanf("%d",&choice);
                                        if(choice==1)
                                            deleteTransition(&(editState->transitions),deletedTransition->id);

                                    }


                                    break;
                                }

                            }

                        break;
                case 4:
                             system("cls");
                             printf("\n \tafnd \n");
                             showAfnd(afnd);
                             convertAfndToAfd(afnd,afd);
                             printf("\n \tafd \n");
                             showAfnd(afd);
                             printf("\n 1- back ");//confirmation message
                             scanf("%d",&choice);
                             deleteAllStates(&afd);


                    break;

            }




    }


}


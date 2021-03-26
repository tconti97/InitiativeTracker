#include<iostream>
#include<string>
#include<queue>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>
using namespace std;

// Start of InitiativeEntry

class InitiativeEntry
{
    public:
        InitiativeEntry(); 
        InitiativeEntry(string inName, int inInitiative, int inMaxHP, int inArmorClass); 
        void changeCurrentHP(int x); 
        void updateAction(); 
        void updateBonusAction();
        void updateMovement();
        void printSomething(bool);
        void deathPrintSomething();
        int getInitiative();
        bool getAction();
        bool getBonusAction();
        bool getMovement();
        bool isDead();
        void deathSuccess();
        void deathFail();
        void deathReset();
    private:
        string name;
        int initiative, maxHP, currentHP, armorClass;
        short fails, saves;
        bool action, bonusAction, movement;
};

// Default Constructor
InitiativeEntry::InitiativeEntry()
{
    name = "test";
    initiative = 20;
    maxHP = 1;
    currentHP = maxHP;
    armorClass = 10;
    action = false;
    bonusAction = false;
    movement = false;
    fails = 0;
    saves = 0;
}

// Populated Constructor
InitiativeEntry::InitiativeEntry(string inName, int inInitiative, int inMaxHP, int inArmorClass)
{
    name = inName;
    initiative = inInitiative;
    maxHP = inMaxHP;
    currentHP = maxHP;
    armorClass = inArmorClass;
    action = false;
    bonusAction = false;
    movement = false;
    fails = 0;
    saves = 0;
}

// Updates Current HP: Positive values are healing, negative are damage.
void InitiativeEntry::changeCurrentHP(int x)
{
    currentHP += x;
    if(currentHP > maxHP)
    {
        currentHP = maxHP;
    }
    else if(currentHP < 0)
    {
        currentHP = 0;
    }
}

// Indicates used Action
void InitiativeEntry::updateAction()
{
    action = !action;
    cout << "Action: " << action << endl;
}

// Indicates used Bonus Action
void InitiativeEntry::updateBonusAction()
{
    bonusAction = !bonusAction;
}

// Indicates used Movement
void InitiativeEntry::updateMovement()
{
    movement = !movement;
}

// Displays stats of character to cmd prompt
void InitiativeEntry::printSomething(bool first_run = false)
{
    cout << initiative << "\t\t" << name << "\t" << currentHP << "/" << maxHP << "\t" << armorClass << "\t";
    if (first_run)
    {
        if(action)
        {
            cout << "*";
        }
        else
        {
            cout << "O";
        }
        cout << "\t";

        if(movement)
        {
            cout << "*";
        }
        else
        {
            cout << "O";
        }

        cout << "\t\t";

        if(bonusAction)
        {
            cout << "*";
        }
        else
        {
            cout << "O";
        }
    }
    cout << endl;
}

// Displays stats of character to cmd prompt including death saving throws
void InitiativeEntry::deathPrintSomething()
{
    cout << initiative << "\t\t" << name << "\t" << currentHP << "/" << maxHP << "\t";
    for (int i = 0; i < 3; i++)
    {
        if(saves > i)
        {
            cout << "* ";
        }
        else
        {
            cout << "O ";
        }  
    }

    cout << "\t\t";

    for (int i = 0; i < 3; i++)
    {
        if(fails > i)
        {
            cout << "* ";
        }
        else
        {
            cout << "O ";
        }  
    }
    cout << endl;
}

// Returns value of initiative
int InitiativeEntry::getInitiative()
{
    return initiative;
}

// Returns value of action
bool InitiativeEntry::getAction()
{
    return action;
}

// Returns value of bonusAction
bool InitiativeEntry::getBonusAction()
{
    return bonusAction;
}

// Returns value of movement
bool InitiativeEntry::getMovement()
{
    return movement;
}

// Determine if character is dead
bool InitiativeEntry::isDead()
{
    return (currentHP == 0);
}

// Increments Saving Throw
void InitiativeEntry::deathSuccess()
{
    saves++;
}

// Increments Saving Throw
void InitiativeEntry::deathFail()
{
    fails++;
}

// Sets saves and fails to 0;
void InitiativeEntry::deathReset()
{
    saves = 0;
    fails = 0;
}

// End of InitiativeEntry

// Start of InitiativeList

class InitiativeList
{
    public:
        InitiativeList();
        void sortInitiative();
        void add(InitiativeEntry);
        void pushInQueue(InitiativeEntry temp, int qsize);
        void FrontToLast(int qsize);
        InitiativeEntry &front();
        int size();
        void pop();
        void nextElement();
        void swapWithNext();
    private:
        queue<InitiativeEntry> battle;

};
InitiativeList::InitiativeList()
{
    // Do Nothing. <--
}

// Sorting Initiative, part 3
void InitiativeList::FrontToLast(int qsize) 
{  
    if (qsize <= 0) 
        return; 

    battle.push(battle.front()); 
    battle.pop(); 
  
    FrontToLast(qsize - 1); 
} 

// Sorting Initiative, part 2
void InitiativeList::pushInQueue(InitiativeEntry temp, int qsize) 
{ 
    if (battle.empty() || qsize == 0) 
    { 
        battle.push(temp); 
        return; 
    }

    else if (temp.getInitiative() >= battle.front().getInitiative()) 
    { 
        battle.push(temp); 
        FrontToLast(qsize); 
    } 
    else 
    { 
        battle.push(battle.front()); 
        battle.pop(); 
        pushInQueue(temp, qsize - 1); 
    } 
} 

// Sorting Initiative, part 1
void InitiativeList::sortInitiative()
{
    if (battle.empty()) 
        return; 
    InitiativeEntry temp = battle.front(); 
    battle.pop(); 
    sortInitiative(); 
    pushInQueue(temp, battle.size()); 
} 

// Pushes element to back of queue
void InitiativeList::add(InitiativeEntry toAdd)
{
    battle.push(toAdd);
}

// Returns reference to front of queue
InitiativeEntry &InitiativeList::front()
{
    return battle.front();
}

// Returns size of queue
int InitiativeList::size()
{
    return battle.size();
}

// Removes front element of battle queue
void InitiativeList::pop()
{
    battle.pop();
}

// Moves the front element to back of queue
void InitiativeList::nextElement()
{
    InitiativeEntry temp;

    if(battle.front().getAction())
    {
        battle.front().updateAction();
    }
    if(battle.front().getBonusAction())
    {
        battle.front().updateBonusAction();
    }
    if(battle.front().getMovement())
    {
         battle.front().updateMovement();
    }

    temp = battle.front();        
    pop();
    add(temp);
}

// Swaps the front element with the one behind it
void InitiativeList::swapWithNext()
{
    if(size() < 2)
    {
        cout << "Error: Not enough elements to swap!";
        return;
    }
    InitiativeEntry temp1, temp2;
    temp1 = front();
    pop();
    temp2 = front();
    pop();
    add(temp2);
    add(temp1);

    for(int i = 0; i < size()-2; i++)
    {
        nextElement();
    }
}

// End of InitiativeList

// Start of Functions


// End of Functions

int main()
{
    // Variable declarations
    string name;
    int initiative, maxHP, armorClass, change;
    char ans;
    InitiativeList myqueue;
    InitiativeEntry test, temp;

    // Random stuff
    const int NATURAL_1 = 1;
    const int NATURAL_20 = 20;
    int randNum;
    srand(time(NULL));

    // Populate queue with data - automatically.
    randNum = rand() % NATURAL_20 + NATURAL_1;
    test = InitiativeEntry("Flint", randNum+2, 63, 15);
    myqueue.add(test);
    randNum = rand() % NATURAL_20 + NATURAL_1;
    test = InitiativeEntry("Tapio", randNum+2, 36, 16);
    myqueue.add(test);
    randNum = rand() % NATURAL_20 + NATURAL_1;
    test = InitiativeEntry("Fog", randNum+4, 20, 15);
    //test = InitiativeEntry("Fog", 15, 20, 15);
    myqueue.add(test);
    randNum = rand() % NATURAL_20 + NATURAL_1;
    
    //test = InitiativeEntry("Iados", 15, 28, 12);
    myqueue.add(test);

/*
    // Populate queue with data - manually.
    while(1)
    {
        cout << "Enter name: ";
        getline(cin, name);

        cout << "Initiative: ";
        cin >> initiative;

        cout << "Max HP: ";
        cin >> maxHP;

        cout << "Armor Class: ";
        cin >> armorClass;

        test = InitiativeEntry(name, initiative, maxHP, armorClass);
        myqueue.add(test);

        cout << "Enter more?(Y/N): ";
        cin >> ans;
        cin.ignore();
        cout << endl;
        if(ans == 'Y')
            continue;
        else
        {
            break;
        }
    }
*/
    myqueue.sortInitiative(); // Sorts queue
    cout << "Initiative\tName\tHP\tAC" << endl;
    for(int i = 0; i < myqueue.size(); i++) // Displays the initiative in order
    {
        test = myqueue.front();
        test.printSomething();        
        myqueue.pop();
        myqueue.add(test);
    }

    cout << endl;

    do
    {
        if(myqueue.front().isDead())
        {
            cout << "Initiative\tName\tHP\tDeath Successes\tDeath Failures" << endl; // These two lines display the stats of the current character's turn and their death saving throws
            myqueue.front().deathPrintSomething();

            cout << endl;

            cout<< "Commands: \n" // Menu of actions to perform
                << "4) damage/heal (requires additional args)\n"
                << "5) remove\n"
                << "6) end turn\n"
                << "7) swap with next\n"
                << "8) Success\n"
                << "9) Failure\n"
                << "0) Add initiative\n"
                << "e) end program\n"
                << "Enter in a command: ";
        }
        else
        {
            cout << "Initiative\tName\tHP\tAC\tAction\tMovement\tBonus Action" << endl; // These two lines display the stats of the current character's turn
            myqueue.front().printSomething(true);

            cout << endl;

            cout<< "Commands: \n" // Menu of actions to perform
                << "1) use action\n"
                << "2) use movement\n"
                << "3) use bonus action\n"
                << "4) damage/heal (requires additional args)\n"
                << "5) remove\n"
                << "6) end turn\n"
                << "7) swap with next\n"
                << "0) Add initiative\n"
                << "e) end program\n"
                << "Enter in a command: ";
        }

        cin >> ans;
        cout << endl;

        if(ans == '1') // Marks Action as used
        {
            myqueue.front().updateAction();
            cout << "Action was used!" << endl;
        }
        else if(ans == '2') // Marks Movement as used
        {
            myqueue.front().updateMovement();
            cout << "Movement was used!" << endl;
        }
        else if(ans == '3') // Marks Bonus Action as used
        {            
            myqueue.front().updateBonusAction();
            cout << "Bonus Action was used!" << endl;
        }
        else if(ans == '4') // Updates the Current HP with the input from user
        {
            cout << "Enter in hp change (negative for damage, positive for hp): ";
            cin >> change;
            if(myqueue.front().isDead() && change > 0)
            {
                myqueue.front().deathReset();
            }
            myqueue.front().changeCurrentHP(change);   
        }
        else if(ans == '5') // Removes character from initiative
        {
            myqueue.pop();
        }
        else if(ans == '6') // Sets parts of turn to normal and moves to next initiative
        {
            myqueue.nextElement();
        }
        else if(ans == '7') // Swaps this entry with the one following it
        {
            myqueue.swapWithNext();
        }
        else if(ans == '8') // Death Saving Throw Success
        {
            myqueue.front().deathSuccess();
        }
        else if(ans == '9') // Death Saving Throw Failures
        {
            myqueue.front().deathFail();
        }
        else if(ans == '0') // Add new element
        {
            cin.ignore();
            cout << "Enter name: ";
            getline(cin, name);

            cout << "Initiative: ";
            cin >> initiative;

            cout << "Max HP: ";
            cin >> maxHP;

            cout << "Armor Class: ";
            cin >> armorClass;

            test = InitiativeEntry(name, initiative, maxHP, armorClass);
            myqueue.add(test);

            myqueue.sortInitiative(); // Sorts queue
            cout << "Initiative\tName\tHP\tAC" << endl;
            for(int i = 0; i < myqueue.size(); i++) // Displays the initiative in order
            {
                test = myqueue.front();
                test.printSomething();        
                myqueue.pop();
                myqueue.add(test);
            }
             cout << endl;
        }
        else if(ans == 'e') // End of Loop and Program
        {
            break;
        }

        if(myqueue.front().getAction() && myqueue.front().getBonusAction() && myqueue.front().getMovement())
        {
            myqueue.nextElement();
        }

    } while (true);
    
    //cout << "test";
    return 0;
}

// cd "c:\Users\tcont\Documents\C++\InitiativeTracker\" ; if ($?) { g++ -static-libstdc++ main.cpp -o main.exe } ; if ($?) { .\main }
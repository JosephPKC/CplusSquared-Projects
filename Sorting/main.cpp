#include <iostream>
#include <InsertionSorter.h>
#include <MergeSorter.h>
using namespace std;

void testInsertion(){
    InsertionSorter<int> I;
    I.insert(5);
    I.insert(2);
    I.insert(7);
    I.insert(6);
    I.insert(3);
    I.insert(10);
    I.insert(8);
    I.insert(1);
    I.insert(5);
    I.insert(5);
    I.insert(5);
    I.insert(5);
    cout << "This is the list now: " << endl;
    cout << I << endl;
    I.sort();
    cout << "Just sorted: " << endl;
    cout << I << endl;
}
void testMerge(){
    MergeSorter<int> I;
    I.insert(5);
    I.insert(2);
    I.insert(7);
    I.insert(6);
    I.insert(3);
    I.insert(10);
    I.insert(8);
    I.insert(1);
    I.insert(5);
    I.insert(5);
    I.insert(5);
    I.insert(5);
    cout << "This is the list now: " << endl;
    cout << I << endl;
    I.sort();
    cout << "Just sorted: " << endl;
    cout << I << endl;
}

int main()
{
//    testInsertion();
//    testMerge();
    int num;
    char choice;
    List<int> L;
    cout << "(A)dd number to list\n"
         << "(R)eset list\n"
         << "(S)ort list:\n"
         << "   (I)nsertion\n"
         << "   (M)erge\n";
    while(true){

        cin >> choice;
        switch(choice){
            case 'A':
            case 'a':{
//                if(cin >> choice){}

                cin >> num;
                L.insertE(num);
                break;
            }
            case'R':
            case'r':{
                Iterator<int> walker = L.begin();
                Iterator<int> end = ++L.end();
                while(walker != end){
                    L.remove(walker);
                    walker++;
                }
                break;
            }
            case 'S':
            case 's':{
                cin >> choice;
                if(tolower(choice) == 'i'){
                    InsertionSorter<int> IS(L);
                    IS.sort();
                    L = IS.list();
                }
                else if(tolower(choice) == 'm'){
                    MergeSorter<int> MS(L);
                    MS.sort();
                    L = MS.list();
                }
                else{
                    cout << "NOPE" << endl;
                }
                break;
            }
            case 'X':
            case 'x':{
                exit(1);
                break;
            }
            default:{
                cout << "TRY AGAIN" << endl;
                break;
            }
        }
        cout << L << endl;

    }

    return 0;
}


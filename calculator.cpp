#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class digit
{
    private://might have to change this
    digit *head;
    digit * tail;

    public:
    int data;
    digit *next = nullptr;
};

digit * writeNum(ifstream & file);
int digcmp(digit * left, digit *right);
char getOperator(ifstream & file);
void writeNum(digit * num, ofstream & file);
void deleteNum(digit * num);
digit * addNumbers(digit * left, digit * right);
digit * subNumbers(digit * left, digit * right);
void writeRecursive(digit * num, ofstream & file);
void setNeg(digit * num);
void printNum(digit * num);
void printRecursive(digit * num);
void subtractCarry(digit * head, digit * prev);
digit * clearLeadingZeros(digit * num);
void * addZero(digit *& num);
void * addEnd(digit *& res, int value);


//-----------------PROVIDED BY INSTRUCTOR-----------------
int main() {
    digit * left, * right, * result;
    int test;
    char op;
    ofstream outFile ("output.txt");
    ifstream inFile ("largeNumbers.txt");
    
    while (!inFile.eof()){
        left  = writeNum(inFile);
        right = writeNum(inFile);
        if (left == nullptr || right == nullptr) {
            // check after two reads if we didn't get numbers
            // in case of one extra newline at end of file
            break;
        }
        op = getOperator(inFile);

        if (op == '+'){
            result = addNumbers(left, right);
        } else {
            test = digcmp(left, right);
            if (test > 0) {
                result = subNumbers(left, right); // result will be positive
                result = clearLeadingZeros(result);
            } else if (test < 0) {
                result = subNumbers(right, left); // result will be negative
                result = clearLeadingZeros(result);
                setNeg(result);
            } else {
                result = new digit; // result of subtraction was zero
            }
        }
        writeNum(result, outFile);
        deleteNum(left);
        deleteNum(right);
        deleteNum(result);
        left = nullptr;
        right = nullptr;
        result = nullptr;
    }
    
    outFile.close();
    inFile.close();
    return 0;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
/* returns a number <0 || 0 || >0
*  <0 right number is larger
*   0  the numbers are equal
*  >0 left number is larger
*  only works if the number is stored with lowest significant at front of the list
*/
int digcmp(digit * left, digit * right){
    int result= 0;
    do // the assignment guarantees there will not be zero length numbers
    {
        if (left->data - right->data == 0){
        } // take no action
        else {
            result= left->data - right->data;
        }
        left = left->next;
        right = right->next;
    } while (left != nullptr && right != nullptr);
    if (left == nullptr && right != nullptr) {
        // right number is longer and therefore larger
        result= -1;
    }
    if (left != nullptr && right == nullptr) {
        // left number is longer and therefore larger
        result= 1;
    }
    return result;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
digit * writeNum(ifstream & file){
    if (file.eof())
    return nullptr;
    digit * head = new digit;
    digit * dig = head;

    char aChar;
    int num;

    file.get(aChar);
    while (aChar != '\n' && !file.eof()){
        num = int(aChar - '0');
        head->data = num;
        file.get(aChar);
        if (aChar != '\n'){
            dig = head;
            head = new digit;
            head->next = dig;
        }
    }
    return head;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
char getOperator(ifstream & file){
    char aChar;
    string toss;

    file.get(aChar);
    getline(file, toss);

    return aChar;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void printRecursive(digit * num){
    if (num == nullptr)
    return;
    printRecursive(num->next);
    cout << num->data;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void printNum(digit * num){
    printRecursive(num);
    cout << endl;

}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void writeRecursive(digit * num, ofstream & file) {
    if (num == nullptr)
    return;
    file << num->data;
    writeRecursive(num->next, file);
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void writeNum(digit * num, ofstream & file){
    writeRecursive(num, file);
    file << endl;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void deleteNum(digit * num){
    digit * n;
    while (num != nullptr)
    {
        n = num->next;
        delete num;
        num = n;
    }
}

// TODO: Implement function to add 2 numbers stored in 2 linked lists
digit * addNumbers(digit * left, digit * right){ // this function makes numbers in order.
   
    digit *cursorLeft = new digit;
    digit *cursorRight = new digit;
    digit * res = nullptr;
    cursorLeft = left;
    cursorRight = right;
    
    int countLeft = 0;
    int countRight = 0;
    //traverse both list to find number count and compare
    while(cursorLeft!=nullptr)
    {
        countLeft++;
        cursorLeft = cursorLeft->next;//updates to next node
    }
    while(cursorRight != nullptr)
    {   
        countRight++;
        cursorRight = cursorRight->next;
    }

    //this test works
    cout << "\nleft and right counters" <<endl;
    cout << countLeft << " "<<countRight<<endl;

    //top is longer than bot
    int difference;
    if(countLeft>countRight)
    {
        difference = countLeft-countRight;
        //ex 3 - 2 = 1
        cout <<"difference: " << difference <<endl;
        for(int a = 0;a<difference;a++)
        {
            addZero(right);
        }
    }else if(countLeft<countRight)
    {
        difference = countRight-countLeft;
        //ex 4 - 1 = 3
        cout <<"difference: " <<difference <<endl;
        for(int b =0; b < difference; b++)
        {
            addZero(left);
        }
    }
  
    cursorLeft = left;//reset the cursors
    cursorRight = right;
    /*
        traverse the left and right test
        CONCLUSION: both left and right list are working right
        res is the problem
    */
   cout << "left list"<<endl;
   while(cursorLeft!=nullptr)
   {
       cout << cursorLeft->data;
       cursorLeft = cursorLeft->next;
   }
    cout <<endl;
    cout << "right list" << endl;
    while(cursorRight!=nullptr)
    {
        cout << cursorRight->data;
        cursorRight = cursorRight->next;
    }
    cout <<endl;

    cursorRight = right;//resets the cursor
    cursorLeft = left;
    int num;
    while(cursorLeft!=nullptr)
    {
        num = cursorLeft->data+cursorRight->data;
        addEnd(res,num);
        cursorLeft = cursorLeft->next;
        cursorRight = cursorRight->next;


    }


    //testing out res;
    cout << "testing out"<<endl;
    digit * cur;
    cur = res;
    while(cur != nullptr)
    {
        cout << cur->data;
        cur = cur->next;
    }


    
    return res;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void subtractCarry(digit * head, digit * prev){
    if (head == nullptr){
        return;
        } // safety check only, this should never happen!
    if (head->data == 0){
        head->data = 9;
        subtractCarry(head->next, head);
    } else {
        head->data -= 1;
    }
}

// TODO: Implement function to subtract 2 numbers stored in 2 linked lists. Use provided helper functions
digit * subNumbers(digit * left, digit * right){
    return nullptr;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
digit * clearLeadingZeros(digit * num){
    digit * next;
    while (num->data == 0) {
        next = num->next;
        delete num;
        num = next;
        }
        return num;
    }
void setNeg(digit * num){
    num->data = -num->data;
}
///////////////////////////////////////////////////////////
void * addZero(digit *& head)
{
    digit*temp = new digit;
    temp->data = 0;
    temp->next = nullptr;

    digit * current = new digit;
    digit * prev = new digit;
    current = head;

    while(current!=nullptr)
    {//traverse with current and prev
        prev = current;
        current = current->next;
    }
    prev->next = temp;
    temp = current;
}
void * addEnd(digit*& res, int value)
{
    digit * temp = new digit;
    temp->data = value;
    temp->next = nullptr;

    if(res==nullptr)
    {
        res = temp;
        temp = nullptr;
    }
    else{
        digit * current;
        digit * prev;

        current = res;
        while(current!=nullptr)
        {
            prev = current;
            current = current ->next;
        }
        prev->next = temp;
    }
}

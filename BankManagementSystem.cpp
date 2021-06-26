/*
Bank manegement system is a manu driven customer data handling program
*/
#include<bits/stdc++.h>

using namespace std;
class Bank {
    private:
        string name;
        string fName;
    
        string address;
        int Balance = 0;
        long long int MobileNumber;
        long long int aadharNumber;
    public:
        void OpenAccount();
        void Deposite(int);
        long long int BalanceEnquiry();
        void Withdraw(int);
        void Display();
        void report();
        long long int retacno();
        void modify();
};
void Bank :: modify() {
    cout << "Enter Name :" << endl;
    cin.ignore();
    getline(cin, name);
    cout << "Enter Father's Name :" << endl;
    getline(cin, fName);
    cout << "Enter Address : " << endl;
    getline(cin, address);
    cout << "Enter mobile Number : " << endl;
    cin >> MobileNumber;

}

long long int Bank :: retacno() {
    return MobileNumber;
}
void Bank :: report() {
    cout << MobileNumber << "\t" << name << "\t\t" << fName << "\t\t\t" << Balance << endl; 

}

// new a/c open
void Bank :: OpenAccount() {
    Bank customer;
    cout << "\tEnter Name : " <<endl;
    cin.ignore();
    getline(cin, name);

    cout << "\tEnter Father's Name" << endl;
    getline(cin, fName);

    cout << "\tEnter Address" <<endl;
    getline(cin, address);

    cout << "\tEnter Mobile Number" <<endl;
    cin >> MobileNumber;

    cout << "\tEnter Aadhar Number" <<endl;
    cin >> aadharNumber;

    cout << "\tEnter initila amount to Deposit and initial amount is >= 500" << endl;
    cin >> Balance;

    cout << "\tYour Account Has Been Created Successfully ...." << endl;
    cout << "\tYour account number is : " << MobileNumber << endl;
    cout << "\tThanks for Choosing our bank!"<< endl << endl;
}
//Deposite function

void Bank :: Deposite(int amount) {
    cout << "\tyou Deposited successfully : " << amount << endl;
    Balance = Balance + amount;
    cout << "\tTotal Balance is : " << Balance << endl << endl;
}
//withdraw function
void Bank :: Withdraw(int amount) {
    Balance = Balance - amount;
    cout << "\tTranscation Successful ..." << endl;
    cout << "\tBalance : " << Balance << endl << endl;
}

// Balance Enquiry Function

long long int Bank :: BalanceEnquiry() {
    return Balance;
}
// showing details of customer 
void Bank :: Display() {
    cout << "\tCustomer Name : " << name << endl;
    cout << "\tFather's Name : " << fName << endl;
    cout << "\tAddress : " << address <<endl;
    cout << "\tMobile Number : " << MobileNumber << endl;
    cout << "\tAadhar Number : " << aadharNumber <<endl;
    cout << "\tAccount Number : " << MobileNumber << endl;
    cout << "\tBalance : " << Balance << endl << endl;

}

/*
function declaration
*/
void createAccount();
void displayAll();
void deleteRecord(long long int);
void searchRecord(long long int);
void depositeWithdraw(long long int, int);
void modifyRecord(long long int);

/**************************************************

*This function deposit and withdraw cash of a specific customer Record
*by taking account number and 1 for deposite and 2 for withdraw

***************************************************/

void depositeWithdraw(long long int n, int opt) {
    int amount;
    bool found = false;
    Bank b1;
    fstream File;
    File.open("bank.txt", ios :: binary | ios :: in | ios :: out);
    if (!File) {
        cout << "File could not be open !! press any key..." << endl;
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*> (&b1), sizeof(Bank));
        if (b1.retacno() == n) {
            b1.Display();
            if (opt == 1) {
                cout << "\n\n\t To deposit amount : " << endl;
                cout << "\n\nEnter the amount to be deposited : " << endl;
                cin >> amount;
                b1.Deposite(amount);
            }
            if (opt == 2) {
                cout << "\n\n\t To withdraw amount : " << endl;
                cout << "\n\nEnter the amount to be withdraw : " << endl;
                cin >> amount;
                if (b1.BalanceEnquiry() < 500) {
                    cout << "Insuficiant Balance..." << endl;
                }
                else {
                    b1.Withdraw(amount);
                }
            }
            int pos = (-1)*static_cast<int>(sizeof(b1));
            File.seekp(pos, ios :: cur);
            File.write(reinterpret_cast<char*> (&b1), sizeof(Bank));
            cout << "\n\n\t Record Updated..." << endl;
            found = true;
        }
    }
    File.close();
        if (found == false) {
            cout << " \n\n Record not found..." << endl;
        }
}

/**************************************************

*This modify a specific customer Record
*by taking account number

***************************************************/

void modifyRecord(long long int n) {
    bool found = false;
    Bank b1;
    fstream File;
    File.open("bank.txt", ios :: binary | ios :: in | ios :: out);
    if (!File) {
        cout << "File could not be open !! press any key...";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*> (&b1), sizeof(Bank));
        if (b1.retacno() == n) {
            b1.Display(); 
            cout << "\n\nEnter new details of account" << endl;
            b1.modify();
            int pos = (-1)*static_cast<int>(sizeof(Bank));
            File.seekp(pos, ios :: cur);

            File.write(reinterpret_cast<char*> (&b1), sizeof(Bank));
            cout << "\n\n\tRecord updated..." << endl;
            found = true;
        }
        
    }
    File.close();
    if (found == false) {
        cout << "\n\n Record Not found" << endl;
    }
}


/**************************************************

*This function show a specific customer Record
*by taking account number

***************************************************/

void searchRecord(long long int n) {
    Bank b1;
    bool flag = false;
    ifstream inFile;
    inFile.open("bank.txt", ios :: binary);
    if (!inFile) {
        cout << "File could not be found !! Press any key....";
        return;
    }
    cout << "\nBalance details\n";
    while (inFile.read(reinterpret_cast<char*> (&b1), sizeof(Bank))) {
        if (b1.retacno() == n) {
            b1.Display();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false) {
        cout << "\n\nAccont number doesn't exist";
    }
}

/**************************************************

*This function delete a specific customer Record
*by taking account number

***************************************************/

void deleteRecord(long long int n) {
    Bank b1;
    ifstream inFile;
    ofstream outFile;
    inFile.open("bank.txt", ios :: binary);
    if (!inFile) {
        cout << " File could not found press any key" << endl;
        return; 
    }
    outFile.open("tmp.txt", ios :: binary);
    inFile.seekg(0, ios :: beg);
    while (inFile.read(reinterpret_cast<char*> (&b1), sizeof(Bank))) {
        if (b1.retacno() != n) {
            outFile.write(reinterpret_cast<char*> (&b1), sizeof(Bank));
        }
    }
    inFile.close();
    outFile.close();
    remove("bank.txt");
    rename("tmp.txt", "bank.txt");
    cout << "record deleted" << endl;
}

/**************************************************

*This function display all  customer Record

***************************************************/


void displayAll() {
    Bank b1;
    ifstream inFile;
    inFile.open("bank.txt", ios :: binary);
    if (!inFile) {
        cout << "File could not found !! Press any key...." << endl;
        return;
    }
    cout << "\n\n\t\tAccount holder list\n\n" ;
    cout << "======================================================================\n";
    cout << "A/c no.          Name             Father Name             Balance\n";
    cout << "======================================================================\n";
    while (inFile.read(reinterpret_cast<char*> (&b1), sizeof(Bank))) {
        b1.report();
    }
    inFile.close();
}

/**************************************************

*This function create a customer Record
*and store it into file

***************************************************/

void createAccount() {
    Bank b1;
    b1.OpenAccount();
    ofstream fout;
    fout.open("bank.txt", ios :: app | ios :: binary);
    fout.write(reinterpret_cast<char*> (&b1), sizeof(Bank));
    fout.close();

}



//driver code

int main() {
    Bank customer;
    cout << endl << endl << "\t**********************************" <<endl <<endl;
    cout << "\t *****  Bank MAnagement System  *****" ;
    cout << endl <<endl << "\t***********************************" <<endl <<endl;
    system("pause");
    while (1) {
       int Option;
        system("CLS");
        cout << "\t1. Open Account" << endl;
        cout << "\t2. Delete" << endl;
        cout << "\t3. Modify" << endl;
        cout << "\t4. Search" <<endl;
        cout << "\t5. Display" <<endl;
        cout << "\t6. Deposit and withdraw " << endl;
        cout << "\t7. exit" << endl;
        
        cout << "\tChoose an option : " << endl;
        cin >> Option;

        switch (Option) {
            case 1: 
            createAccount();
            system("pause");
            break;

            case 2: 
            long long int n;
            cout << "Input A/c number : " << endl;
            cin >> n;
            deleteRecord(n);
            system("pause");
            break;

            case 3:
                long long int n1;
                cout << "Enter A/c Number: " << endl;
                cin >> n1;
                modifyRecord(n1);
                system("pause");
            break;

            case 4:
            long long int n2;
            cout << "Input Account number :" << endl;
            cin >> n2; 
            searchRecord(n2);
            system("pause");
            break;

            case 5:
            displayAll();
            system("pause");
            break;

           case 6:
            long long int n3;
            int opt;
            cout << "Enter a/c number :" << endl;
            cin >> n3;
            cout << "press 1 for deposit 2 for withdraw : " << endl;
            cin >> opt;
            depositeWithdraw(n3, opt);
            system("pause");
            break;

            case 7: 
            exit(0);

            default :
            cout << "\tWrong Choice" << endl;
        }    
     }
    return 0;
}

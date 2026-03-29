#include <iostream>
#include <fstream>
using namespace std;

class User
{
    string username, password, email;
    string srchName, srchPass, srchEmail;
    fstream file;
public:
    void login();
    void signUp();
    void forget();
};


int main()
{
    char choice;
    User person;

    cout << "1. Login\n";
    cout << "2. Sign Up\n"; 
    cout << "3. Forget Password\n";
    cout << "4. Exit\n";

    cout << "\tEnter Your Choice : ";
    cin >> choice;
    cin.ignore();

    switch(choice)
    {
        case '1' : person.login();
            break;
        case '2' : person.signUp();
            break;
        case '3' : person.forget();
            break;
        case '4' : cout << "Thank You\n" ;
            break;
        default :  cout << "Choose valid option !\n";
    }

    return 0;
}

void User::login()
{
    cout << "\n----- Login -----\n";

    file.open("./login_data.csv",ios::out | ios::app);
    cout << "Enter Username : ";
    getline(cin, username);
    cout << "Enter Password : ";
    getline(cin, password);
    cout << "Enter Email address : ";
    getline(cin, email);
    file << username << ',' << password << ',' << email << '\n';
    file.close();
}

void User::signUp()
{
    cout << "\n----- Sign Up -----\n";

    file.open("./login_data.csv", ios::in);
    cout << "Enter Your Username : ";
    getline(cin, srchName);
    cout << "Enter Your Password : ";
    getline(cin, srchPass);

    while(file.eof() == 0) // May be cause error , if error check    file.eof() != 0; && try first input out of loop than try loop
    {
        getline(file, username, ',');
        getline(file, password, ',');
        getline(file, email, '\n');

        if(srchName == username)
        {
            if(srchPass == password)
            {
                cout << "Sign Up Successfully ! \n";
                cout << "Your Email Address is : " << email << endl;
            }
            else
            {
                cout << "Wrong Password !\n" ;
            }
        }
    }

    file.close();
}

void User::forget()
{
    cout << "\n----- Forget Password -----\n";
    
    file.open("./login_data.csv", ios::in);
    cout << "Enter Your Username : ";
    getline(cin, srchName);
    cout << "Enter Your Email : ";
    getline(cin, srchEmail);

    while(file.eof() == 0)
    {
        getline(file, username, ',');
        getline(file, password, ',');
        getline(file,email, '\n');

        if(srchName == username)
        {
            if(srchEmail == email)
            {
                cout << "Password is found ! \n";
                cout << "Your password is : " << password << endl;
            }
            else
            {
                cout << "Password is not found !\n" ;
            }
        }
    }
    file.close();
}
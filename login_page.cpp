#include <iostream>
#include <fstream>
using namespace std;

/* feature still require -
    1.salting password
    2.file encription
    3.check whether a username is already exist or not
    4.restrictions while creating username
    5.check for valid email
    7.Use database rather than file system
    Advance : otp varification
*/

class User
{
    string username, password, email;     // for handling file data
    string srchName, srchPass, srchEmail; // for handling user search data
    fstream file;
    fstream temp;

public:
    void login();
    void signUp();
    void forgetPass();
    void updatePass();
};

char displayOption(int limit = 3) // here 3 is default arrgument
/*  This function display list again and again until either ther limit is over or user give correct response */
{
    if (limit == 0)
    {
        cout << "Your attempts are over!" << endl;
        return '5';
    }

    char choice;
    cout << "\t\t\t\t\t Attempt remaining " << limit - 1 << endl;
    cout << "1. Login\n";
    cout << "2. Sign Up\n";
    cout << "3. Forget Password\n";
    cout << "4. Update Password\n";
    cout << "5. Exit\n";
    cout << "\tEnter Your Choice : ";
    cin >> choice;
    cin.ignore();

    if (!(choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5'))
    {
        cout << "Choose valid option!" << endl;
        choice = displayOption(limit - 1);
    }

    return choice;
}

int main()
{
    User person;
    char choice = displayOption(3); // here 3 is it's limit when user give wrong input

    switch (choice) // this react according to choice
    {
    case '1':
        person.login();
        break;
    case '2':
        person.signUp();
        break;
    case '3':
        person.forgetPass();
        break;
    case '4':
        person.updatePass();
        break;
    default: // when choice = 5
        cout << "Thank You\n";
    }

    return 0;
}

void User::login()
/* This routine/function takes data from user and put it into file */
{
    cout << "\n----- Login -----\n";

    file.open("./userData.csv", ios::out | ios::app);
    cout << "Enter Username : ";
    getline(cin, username);
    cout << "Enter Password : ";
    getline(cin, password);
    cout << "Enter Email address : ";
    getline(cin, email);
    file << username << ',' << password << ',' << email << '\n';
    file.close();
    return;
}

void User::signUp()
/* In this function first take id & pass from user and then check it in that file */
{
    cout << "\n----- Sign Up -----\n";

    file.open("./userData.csv", ios::in);
    cout << "Enter Your Username : ";
    getline(cin, srchName);
    cout << "Enter Your Password : ";
    getline(cin, srchPass);

    bool IsUsername_found = false; // Use to print else message
    while (file.eof() != 1)
    {
        getline(file, username, ',');
        getline(file, password, ',');
        getline(file, email, '\n');

        if (srchName == username)
        {
            IsUsername_found = true;
            if (srchPass == password)
            {
                cout << "Sign Up Successfully ! \n";
                cout << "Hello," << username << endl;
                cout << "Your Email Address is : " << email << endl;
            }
            else
            {
                cout << "Wrong Password!\n";
            }
            break; // when username match it should be not check more & exit form loop
        }
    }
    !IsUsername_found ? cout << "Username not found !\n" : cout << "\n"; // terniary operator
    file.close();
    return;
}

void User::forgetPass()
/* In this routine, first check for username & email then show current password */
{
    cout << "\n----- Forget Password -----\n";

    cout << "Enter Your Username : ";
    getline(cin, srchName);
    cout << "Enter Your Email : ";
    getline(cin, srchEmail);

    bool IsUsername_found = false;
    file.open("./userData.csv", ios::in);
    while (file.eof() == 0)
    {
        getline(file, username, ',');
        getline(file, password, ',');
        getline(file, email, '\n');

        if (srchName == username)
        {
            IsUsername_found = true;
            if (srchEmail == email)
            {
                cout << "Password is found! \n";
                cout << "Your password is : " << password << endl;
            }
            else
            {
                cout << "Wrong email!\n";
            }
            break;
        }
    }
    !(IsUsername_found) ? cout << "User name not found!\n" : cout << endl;
    file.close();
    return;
}

void User::updatePass()
/* first check, Is given username & pass is valid or not, if valid than change pass to new form old and store them in new file . After completing the process the new file is rename as old file and the old file will be deleted */
{
    cout << "\n----- Update Password -----\n";

    cout << "Enter Username : ";
    getline(cin, srchName);
    cout << "Enter Current Password : ";
    getline(cin,srchPass);

    file.open("./userData.csv", ios::in);
    bool isValid = false;
    while (file.eof() == 0)
    {
        getline(file, username, ',');
        getline(file, password, ',');
        getline(file, email, '\n');

        if (username == srchName)
        {
            if (password == srchPass)
            {
                isValid = true;
            }
            else
            {
                cout << "Invalid password \n";
            }
            break;
        }
    }
    file.close();

    if (isValid)
    {
        string newPass;
        cout << "Enter New password : ";
        getline(cin, newPass);

        file.open("./userData.csv", ios::in);
        temp.open("./temp.csv", ios::out);
        while (file.eof() == 0)
        {
            getline(file, username, ',');
            getline(file, password, ',');
            getline(file, email, '\n');

            if (username == srchName)
            {
                password = newPass;
            }
            if(username != "")
            {
                temp << username << ',' << password << ',' << email << '\n';
            }
        }
        file.close();
        temp.close();

        remove("./userData.csv");
        rename("./temp.csv", "./userData.csv");
    }
    else
    {
        cout << "Not Valid Entry!\n";
    }

    return;
}

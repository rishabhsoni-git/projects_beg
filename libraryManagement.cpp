#include <iostream>
#include <stdlib>
#inlcude <fstream>
using namespace std;

class Book  // for book detail
{
protected:
//attributes
  string book_name;
  string book_title;
  string book_author;
  int unsigned book_no;
  int unsigned book_quantity_available;
//methods
  void issue_book();
  void return_book();
  void add_book();
  void remove_book();
  void order_book();
  void response();
public:
  void show_books();
};

class Student
{
public:
  string std_name;
  string std_course;
  string std_branch;
  int std_id;
  int std_rollno;
  int std_age;
  void request();
  void issue_book();
  void return_book();
};

int main(){
  cout << "Welcome to Ram Library\n" ;
  char user, choice;
  cout << "Who you are Librarian(L)/Student(S)?\n";
  cin >> user;

  if(user == 'l' || 'L'){
    cout << "librarian login!";
  }  
  else if(user == 's' || 'S'){
    cout << "Student login!";
  }
  else{
    cout << "wrong answer!\n";
    exit(0);
  }
  
  cout << "Choose an option : \n";
  cout << "1. Show Books\n";
  cout << "2. Issue Book\n";
  cout << "3. Return Book\n";
  cout << "Enter Option : ";
  cin >> choice;
  cin.ignore();
  return 0;
}

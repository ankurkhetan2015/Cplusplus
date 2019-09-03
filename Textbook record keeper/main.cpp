using namespace std;
#include <string>
#include <stdio.h>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <map>
#include <set>

//Book class
class Book{
    public:
    string title = "";
    string ISBN = "";
    string author = "";
    int month = 0;
    int year = 0;
    int edition = 0;
    //costs of books
    float newBook = 0;
    float used = 0;
    float rented = 0;
    float electronic = 0;
};

//Course class
class Course{
    public:
    int number = 0;
    string name = "";
    map<int, list<pair<char,string>>> sections;
};

bool valid_date(string input){
    int limiter = input.find("/");
    string month_str = input.substr(0, limiter);
    char char_month[month_str.length()+1];
    strcpy(char_month, month_str.c_str());
    for(char c : char_month){
        if(((int)c<48 || (int)c>57) && (int)c != 0){
            return false;
        }
    }
    int month = atoi(month_str.c_str());
    if(month> 12 || month <1){
        return false;
    }
    input.erase(0, limiter +1);
    int n = input.length();
    char char_array[n+1];
    strcpy(char_array, input.c_str());
    for(char c : char_array){
        if(((int)c<48 || (int)c>57) && (int)c != 0){
            return false;
        }
    }
    int year = atoi(input.c_str());

    return true;
}

bool valid_double(string input){
    try{
        float num = strtof(input.c_str(), NULL);
        int n = input.length();
        char char_array[n+1];
        strcpy(char_array, input.c_str());
        for(char c : char_array){
            if(((int)c<48 || (int)c>57) && (int)c != 0 && (int)c != 46){
                return false;
            }
        }
    } catch(...){
        return false;
    }
    return true;
}

bool valid_ISBN(string input){
    int n = input.length();
    char char_array[n+1];
    if( n != 13){
        return false;
    }
    strcpy(char_array, input.c_str());
    for(char c : char_array){
        if(((int)c<48 || (int)c>57) && (int)c != 0){
            return false;
        }
    }
    return true;
}

//function to print book details
void print_book(Book book){
    cout << "\nBook details: \n Title: " << book.title << "\n ISBN: " << book.ISBN << "\n Author: " << book.author << "\n Date: " << book.month << "/" << book.year;
    cout << "\n Edition: " << book.edition ;
    if(book.newBook != 0) {
        cout << "\n New Book cost: " << book.newBook;
    }
    if(book.used != 0) {
        cout << "\n Used book cost: " << book.used;
    }
    if(book.rented != 0) {
        cout << "\n Book rent: " << book.rented;
    }
    if(book.electronic != 0){
        cout << "\n E-Book cost: " <<book.electronic;
    }
    cout << "\n";
}

//function to print book details
void print_book_name(Book book){
    cout << "\nBook: \n Title: " << book.title << "\n ISBN: " << book.ISBN;
    cout << "\n";
}

//method to create a new book from given input
Book create_new_book(string input){
    Book book;
    //calculate word in the input
    int limiter = input.find(" ");
    if(valid_ISBN(input.substr(0, limiter))) {
        book.ISBN = input.substr(0, limiter);
    } else {
        return book;
    }
    input.erase(0, limiter +1);
    book.title = input;
    //return book
    return book;
}

//method to create course using the input
pair<string, Course> create_course(string input){
    Course course;
    int limiter = input.find(" ");
    string dept = input.substr(0, limiter);
    input.erase(0, limiter +1);
    limiter = input.find(" ");
    course.number = atoi(input.substr(0, limiter).c_str());
    input.erase(0, limiter +1);
    course.name = input;
    dept = dept + "-" + std::to_string(course.number);
    //returns a pair to be added to map
    return pair<string, Course>(dept, course);
}

//edit the characteristics of book based on input
Book edit_char_book(Book book, string input){
    int limiter = input.find(" ");
    string value = input.substr(0, limiter);
    input.erase(0, limiter +1);
    //see which character to change and calculate values accordingly
    if(value == "A"){
        book.author = input;
    }
    if(value == "E"){
        try{
            book.edition = atoi(input.c_str());
        } catch(...){
            cout << "Invalid edition";
            return book;
        }
    }
    if(value == "D"){
        if(!valid_date(input)){
            cout << "Invalid date";
            return book;
        }
        limiter = input.find("/");
        string month = input.substr(0, limiter);
        book.month = atoi(month.c_str());
        input.erase(0, limiter +1);
        book.year = atoi(input.c_str());
    }

    //change prices
    if(input == "N"){
        if(valid_double(value.c_str()))
            book.newBook = strtof(value.c_str(), NULL);
        else{
            cout << "Invalid cost";
        }
    }
    if(input == "U"){
        if(valid_double(value.c_str()))
            book.used = strtof(value.c_str(), NULL);
        else{
            cout << "Invalid cost";
        }
    }
    if(input == "R"){
        if(valid_double(value.c_str()))
            book.rented = strtof(value.c_str(), NULL);
        else{
            cout << "Invalid cost";
        }
    }
    if(input == "E"){
        if(valid_double(value.c_str()))
            book.electronic = strtof(value.c_str(), NULL);
        else{
            cout << "Invalid cost";
        }
    }
    return book;
}

//add method to add book to a particular section of course
Course add_book(Course course, string input, string ISBN){
    int limiter = input.find(" ");
    //calculate section
    int section = atoi(input.substr(0, limiter).c_str());
    input.erase(0, limiter +1);
    //if section already present
    if(course.sections.find(section) != course.sections.end()){
        map<int, list<pair<char,string>>>::iterator itr = course.sections.find(section);
        list<pair<char,string>> books = itr->second;
        bool present = false;
        for(pair<char,string> book : books) { //check if book already there, just update if optional or required
            if (book.second == ISBN) {
                book.first = input.front();
                present = true;
            }
        }
        if(!present) {//else
            books.push_front(pair<char, string>(input.front(), ISBN)); // add to the list
        }
        itr->second = books;
    } else { //create a new section
        list<pair<char,string>> books;
        books.push_front(pair<char,string>(input.front(),ISBN));
        course.sections.insert(pair<int, list<pair<char,string>>>(section, books));
    }
    return course; //return the new course
}

void print_unique(set<string> final,map<string, Book> books){ //print the unique values from a set
   for (set<string>::iterator it=final.begin(); it != final.end(); ++it){
       if(books.find(*it) != books.end()){
            print_book_name(books.find(*it)->second);
       }
   }
}

float get_min(Book book){
    float min = std::numeric_limits<float>::max();
    if(book.rented != 0 && book.rented < min){
        min = book.rented;
    }
    if(book.used != 0 && book.used < min){
        min = book.used;
    }
    if(book.newBook != 0 && book.newBook < min){
        min = book.newBook;
    }
    if(book.electronic != 0 && book.electronic < min){
        min = book.electronic;
    }
    return min;
}

float get_max(Book book){
    float max = std::numeric_limits<float>::min();
    if(book.rented != 0 && book.rented > max){
        max = book.rented;
    }
    if(book.used != 0 && book.used > max){
        max = book.used;
    }
    if(book.newBook != 0 && book.newBook > max){
        max = book.newBook;
    }
    if(book.electronic != 0 && book.electronic > max){
        max = book.electronic;
    }
    return max;
}

pair<pair<int,int>,pair<float,float>> print_min_max(Course course, map<string, Book> books, pair<pair<int,int>,pair<float,float>> values){
    map<int, list<pair<char,string>>> sections = course.sections;
    map<int, list<pair<char,string>>>::iterator itr;

    int num_min = values.first.first;
    int num_max = values.first.second;
    float total_min = values.second.first;
    float total_max = values.second.second;

    //if looking for a course, for each section
    for(itr = sections.begin(); itr != sections.end(); ++itr){ //for all sections
        int section = itr->first;
        float min = 0.0;
        float max = 0.0;
        //get the section values, if already there in values
        list<pair<char,string>> pairs = itr ->second;
        for (pair<char,string> book : pairs){
            if(book.first == 'R'){ //if book is required
                min = min + get_min(books.find(book.second)->second); //add min value
            }
            max = max + get_max(books.find(book.second)->second); //add max value for all books
        }
        cout << "Section " << section << ":" << "\n";
        cout << " Minimum" << min << "\n";
        cout << " Maximum" << max << "\n";
        total_max = total_max + max;
        total_min = total_min + min;
        num_min = num_min +1;
        num_max = num_max +1;
    }
    return pair<pair<int,int>,pair<float,float>>(pair<int,int>(num_min,num_max),pair<float,float>(total_min,total_max));
}

void print_course_books(Course course, int section, map<string, Book> books, bool sect){
    map<int, list<pair<char,string>>> sections = course.sections;
    map<int, list<pair<char,string>>>::iterator itr;
    //if looking for a course
    if(section == 0){
        set<string> output;
        for(itr = sections.begin(); itr != sections.end(); ++itr){ //for all sections
            list<pair<char,string>> pairs = itr ->second;
            if(sect) {
                set<string> output;
                cout << "\nSection " << itr->first << ": ";
                for (pair<char, string> book : pairs) {
                    output.insert(book.second); //insert to the set (to get unique values)
                }
                print_unique(output, books);
            } else  {
                for (pair<char, string> book : pairs) {
                    output.insert(book.second); //insert to the set (to get unique values)
                }
            }
        }
        if(!sect){
            print_unique(output, books);
        }
    } else { //get the particular section
        set<string> final;
        list<pair<char,string>> pairs = sections.find(section)->second;
        for (pair<char,string> book : pairs){
            final.insert(book.second); //insert to the set (to get unique values)
        }
        print_unique(final, books); //print the set
    }

}


int main(){

    map<string, Book> books; //all books
    map<string, Course> depts; //all courses

    while(true){
        string input;
        getline (std::cin,input);
        int limiter = input.find(" ");
        string token = input.substr(0, limiter);
        input.erase(0, limiter +1);
        //check for token to find what to do
        if(token == "B"){ //create new book and insert in map
            Book book = create_new_book(input);
            if(book.ISBN == ""){
                cout << "Invalid ISBN\n";
            } else {
                books.insert(pair<string, Book>(book.ISBN, book));
            }
        }
        if(token == "D" || token == "M"){ //edit book according to values
            limiter = input.find(" ");
            string ISBN = input.substr(0, limiter);
            if(valid_ISBN(ISBN)) {
                input.erase(0, limiter + 1);
                if (books.find(ISBN) != books.end()) {
                    map<string, Book>::iterator itr = books.find(ISBN);
                    Book book = itr->second;
                    itr->second = edit_char_book(book, input);
                } else { //if book not present throw the error
                    printf("Define the book first.");
                }
            } else {
                cout << "Invalid ISBN\n";
            }
        }
        if(token == "GB"){ //print details about a book
            limiter = input.find(" ");
            string ISBN = input.substr(0, limiter);
            if(valid_ISBN(ISBN)) {
                if (books.find(ISBN) != books.end()) {
                    map<string, Book>::iterator itr = books.find(ISBN);
                    Book book = itr->second;
                    print_book(book);
                } else { //if not present throw an error
                    printf("No such book defined.\n");
                }
            } else {
                cout << "Invalid ISBN\n";
            }
        }
        if(token == "PB"){ // print all books
            map<string, Book>::iterator itr;
            for (itr = books.begin(); itr != books.end(); ++itr){
                print_book_name(itr->second);
            }
        }
        if(token == "C"){ //create a new course and insert in dept
            depts.insert(create_course(input));
        }
        if(token == "A"){ //add books to prescribed list
            limiter = input.find(" ");
            string ISBN = input.substr(0, limiter);
            input.erase(0, limiter +1);
            if(valid_ISBN(ISBN)) {
                if (books.find(ISBN) != books.end()) { //check if book present
                    limiter = input.find(" ");
                    string dept = input.substr(0, limiter);
                    input.erase(0, limiter + 1);
                    limiter = input.find(" ");
                    string course = input.substr(0, limiter);
                    input.erase(0, limiter + 1);
                    dept = dept + "-" + course;
                    if (depts.find(dept) != depts.end()) { //check if course  present in dept
                        map<string, Course>::iterator itr = depts.find(dept);
                        Course course = itr->second;
                        itr->second = add_book(course, input, ISBN); //add book
                    } else { //throw error
                        printf("No such dept/course defined.\n");
                    }
                } else { //throw error
                    printf("No such book defined.\n");
                }
            } else {
                    cout << "Invalid ISBN\n";
                }
        }
        if(token == "PC"){ //print the coourses
            map<string, Course>::iterator itr;
            for (itr = depts.begin(); itr != depts.end(); ++itr){
                Course course = itr->second;
                cout << "\nCourse name : " << course.name <<  "\nCourse number : " << course.number;
            }
        }
       if(token == "GC" || token == "GS"){ //print books of course or section
            limiter = input.find(" ");
            string dept = input.substr(0, limiter);
            input.erase(0, limiter +1);
            limiter = input.find(" ");
            string course = input.substr(0, limiter);
            dept = dept + "-" + course;
            if(depts.find(dept) != depts.end()){ //check if dept present
                map<string, Course>::iterator itr = depts.find(dept);
                if(token == "GS"){ //if section is required
                    input.erase(0, limiter +1);
                    print_course_books(itr->second, atoi(input.c_str()), books, true); //books of that session
                } else {
                    print_course_books(itr->second, 0, books, true); //all books in that course
                }
            } else {
                printf("No such dept/course defined.\n");
            }
        }
        if(token == "PY"){ //print all books after a date
            if(valid_date(input)){
                limiter = input.find("/");
                int month = atoi(input.substr(0, limiter).c_str());
                input.erase(0, limiter +1);
                int year = atoi(input.c_str());
                for(map<string, Book>::iterator it = books.begin(); it != books.end(); ++it){ //get all books
                    Book book = it->second;
                    if(book.year > year || (book.year == year && book.month >= month)){ //get only latest ones
                        print_book(book);
                    }
                }
            } else {
                cout << "Invalid Date \n";
            }

        }
        if(token == "PD"){ //print all books of dept
            string dept = input;
            for(map<string,Course>::iterator iter = depts.begin(); iter != depts.end(); ++iter){
                string k =  iter->first;
                if(k.find(dept) != string::npos){ //for all courses print books
                    print_course_books(iter->second, 0, books, false);
                }else {
                    printf("No such dept/course defined.\n");
                 }
            }
        }
        if(token == "PM"){ //print out average
            string dept = input;
            pair<pair<int,int>,pair<float,float>> values; //store values of sections within courses
            for(map<string,Course>::iterator iter = depts.begin(); iter != depts.end(); ++iter){
                string k =  iter->first;
                cout << "\nCourse " << k.substr(k.find("-") +1) << "\n";
                if(k.find(dept) != string::npos){ //get all courses of departments
                   values = print_min_max(iter->second, books, values);
                }else {
                    printf("No such dept/course defined.\n");
                }
            }

            cout <<" \n";
            cout << "Average minimum cost of books: " << values.second.first/values.first.first << " \n"; //get average of min value of required books
            cout << "Average maximum cost of books: " << values.second.second/values.first.second << " \n"; //get average of max value of required books
        }
    }
}
/* PROBLEM STATEMENT : MOVIE BOOKING SYSTEM
 * LINEAR DATA STRUCTURE BASED PROJECT 
 * DATA STRUCTURES USED : LINKEDLISTS, QUEUES, MATRIX(2D ARRAYS)
 * Code is divided  into two modules :
 * 1. Employee (Admin)
 * 2. Customer
 * A. FUNCTIONS OF EMPLOYEE : 
 *   1. Add movie
 *   2. Delete Movie
 *   3. View Seat Matrix
 *   4. Display all Movies
 *   5. Check if theatre is full for a specific movie
 *   6. Deallocating seat when customer deletes his ticket
 * B. FUNCTIONS OF CUSTOMER : 
 *   1. Book new Ticket
 *   2. Delete booked Ticket
 *   3. Display a specific Ticket
 *   4. Display all tickets*/
#include<iostream>
#include<iomanip>
#include<limits>
using namespace std;
#include<string>
#define MAXROW 10
#define MAXCOL 10
int ID = 1;
class movieNode             // class to store information related to a single movie
{
        int id;
    public :
        string moviename, time, date;
        float price;
        movieNode* next;
        int SM[MAXROW][MAXCOL];
        movieNode()              // default constructor to store default values
        {
            id = 0;
            moviename = "";
            time = "";
            date = "";
            price = 0;
            next = NULL;
            for(int i = 0; i < MAXROW; i++)
            {
                for(int j = 0; j < MAXCOL; j++)
                    SM[i][j] = 0;
            }
        }
        movieNode(string moviename, string time, string date, float price)// paramertrized constructor to store assigned values
        {
            this->id = ID;
            this->moviename = moviename;
            this->time = time;
            this->date = date;
            this->price = price;
            next=NULL;
            for(int i = 0; i < MAXROW; i++)
            {
                for(int j = 0; j < MAXCOL; j++)
                    SM[i][j] = 0;
            }
            ID++;
        }
        friend class MovieList;
};
class MovieList        // class which is used to create list of movies
{
        movieNode* head;
    public:
        MovieList()
        {
            head = NULL;
        }
        ~MovieList()      // destructor to clear memory
        {
            movieNode* temp = head, *temp1;
            if(head)
            {
                if(head -> next)
                {
                    for(temp1 = head -> next; temp1 != NULL; temp1 = temp1 -> next)
                    {
                        delete temp;
                        temp = temp1;
                    }
                    delete temp;
                }
            }
        }
        void addMovie();     // to add more movies to movie list
        bool removeSeat(movieNode* , int, int);
        bool removeMovie();     // to remove a movie from movie list
        bool containsMovie(int);    
        bool displayMovies();
        void displaySeatMatrix();
        bool isFull(movieNode*);
        void seatMatrix(movieNode*);
        movieNode* helper(int);
        bool editMatrix(movieNode*, int, int);
};
bool MovieList :: isFull(movieNode* ptr)
{
    for(int i = 0; i < MAXROW; i++)
    {
        for(int j = 0; j < MAXCOL; j++)
        {
            if(ptr->SM[i][j] != 1)
                return false;
        }
    }
    return true;
} 
bool MovieList :: removeSeat(movieNode* ptr, int r, int c) // when some customer deletes his seat free the seat from seat matrix 
{
    if(ptr->SM[r][c] == 1)
    {
        ptr->SM[r][c] = 0;
        return true;
    }
    return false;
}
bool MovieList :: editMatrix(movieNode* ptr, int r, int c)   // mark seat booked when customer books his ticket
{
    if(ptr->SM[r][c] == 0)
    {
        ptr->SM[r][c] = 1;
        return true;
    }
    return false;
}
movieNode* MovieList :: helper(int id_movie) // returns pointer to movieNode of respective movie
{
    if(head == NULL)
        return NULL;
    movieNode* temp = head;
    while(temp)
    {
        if(temp -> id == id_movie)
            return temp;
        temp = temp -> next;
    }
    return NULL;
}
bool MovieList :: displayMovies() // to display all movies in list
{
    if(head == NULL)
    {
        cout<<"Movie List is Empty!"<<endl;
        return false;
    }
    cout<<"---------------------------------------------------------------------\n";
    cout<<left<<setfill(' ')<<setw(5)<<"ID"<<setw(20)<<"NAME"<<setw(15)<<"DATE"<<setw(10)<<"TIME"<<setw(10)<<"PRICE";
    cout<<"\n--------------------------------------------------------------------";

    movieNode* temp = head;
    while(temp)
    {
        cout<<"\n"<<left<<setfill(' ')<<setw(5)<<temp->id<<setw(20)<<temp->moviename<<setw(15)<<temp->date<<setw(10)<<temp -> time<<setw(10)<<temp -> price<<endl;
        temp = temp -> next;
    }
    cout<<"------------------------------------------------------------------------\n";

    return true;
}
void MovieList :: addMovie() // to add a new movie to list of movies
{
    float price_movie;
    string name_movie, time_movie, date_movie;
    getline(cin, name_movie);
    cout<<"Enter Movie name :- ";
    getline(cin, name_movie);
    cout<<"Enter Movie time :- ";
    getline(cin, time_movie);
    cout<<"Enter Movie date :- ";
    getline(cin, date_movie);
    cout<<"Enter Movie price :- ";
    cin>>price_movie;

    movieNode* newnode = new movieNode(name_movie, time_movie, date_movie, price_movie);
    if(head == NULL)     // if list is empty
        head = newnode;
    else                               // traverse till end of list
    { 
        movieNode* temp = head;
        while(temp -> next)
            temp = temp -> next; 
        temp -> next = newnode;
    }
}
bool MovieList :: removeMovie()
{
    if(head == NULL)  // if list is empty
    {
        cout<<"Movie List is Empty!"<<endl;
        return false;
    }
    int id_movie;
    cout<<"Enter movie id :- ";
    cin>>id_movie;
    if(containsMovie(id_movie))
    {
        movieNode* temp = head, *prev = NULL;
        if(head -> id == id_movie)  // deleting first movie
        {
            prev = head;
            head = head -> next;
            delete prev;
            return true;
        }
        while(temp && temp -> id != id_movie) // traverse till you dont find the movie with given id
        {
            prev = temp;
            temp = temp -> next;
        }
        prev -> next = temp -> next;
        delete temp;
        return true;
    }
    else
        cout<<"No such movie id exists!"<<endl;
    return false;
}
bool MovieList :: containsMovie(int id_movie) // function to know whether movie is in movielist 
{
    movieNode* temp = head;
    if(head == NULL)
        return false;
    while(temp)
    {
        if(temp -> id == id_movie)
            return true;
        temp = temp -> next;
    }
    return false;
}
void MovieList :: displaySeatMatrix() // display seat matrix of given movie
{
    int id;
    cout<<"Enter movie ID :- ";
    cin>>id;
    if(containsMovie(id))
    {
        movieNode* temp = head;
        cout<<"\nSeat Matrix :\n";
        for(; temp -> id != id; temp = temp -> next);
        for(int i = 0; i < MAXROW; i++)
        {
            for(int j = 0; j < MAXCOL; j++)
            {
                if(temp->SM[i][j] == 0)
                    cout<<"_ ";
                else
                    cout<<"x ";
            }
            cout<<endl;
        }
    }
    else
        cout<<"No such Movie!"<<endl;
}
void MovieList :: seatMatrix(movieNode* ptr)  // function to display seat matrix of given movie
{
    for(int i = 0; i < MAXROW; i++)
    {
        for(int j = 0; j < MAXCOL; j++)
        {
            if(ptr->SM[i][j] == 0)
                cout<<"_ ";
            else
                cout<<"x ";
        }
        cout<<endl;
    }
}
class customerNode    // class to store information of a single customer
{
        int row, col, id_movie;
        string name, date, show_time, movie_name;
        float price;
        customerNode *next;
    public:
        friend class customerList;
        customerNode() // default constructor to set values to default values
        {
            row = 0;
            col = 0;
            name = "";
            date = "";
            price = 0;
            show_time = "";
            movie_name = "";
            id_movie = 0;
            next = NULL;
        }
        customerNode(int Row, int Col,string Name, int Id_movie)  // parameterized constructor to set values to assigned values
        {
            row = Row;
            col = Col;
            name = Name;
            id_movie = Id_movie;
            next = NULL;
        }
};
class customerList     // to store a list of cutomers
{
        customerNode *front, *rear;
    public:
        customerList()
        {
            front = NULL;
            rear = NULL;
        }
        ~customerList()
        {
            customerNode* temp = front, *temp1;
            if(front)
            {
                if(front -> next)
                {
                    for(temp1 = front -> next; temp1 != NULL; temp1 = temp1 -> next)
                    {
                        delete temp;
                        temp = temp1;
                    }
                    delete temp;
                }
            }
        }
        void assign(customerNode*, MovieList& m, int id);
        void addTicket(MovieList& m);
        void displayTicket(MovieList& m);
        void displayAllTickets();
        void deleteTicket(MovieList& m);
};
void customerList :: assign(customerNode* temp, MovieList& m, int id) // to assign values related to movie from movieid
{
    movieNode* temp1 = m.helper(id);
    temp -> movie_name = temp1 -> moviename;
    temp -> show_time = temp1 -> time;
    temp -> price = temp1 -> price;
    temp -> date = temp1 -> date;
}
void customerList :: deleteTicket(MovieList& m)
{
    int id, r, c;
    bool flag1 = m.displayMovies();         // returns false if no movies are present
    if(!flag1)
    {
        cout<<"No booked tickets!"<<endl;
        return;
    }
    cout<<"Enter movie id :- ";
    cin>>id;
    movieNode* temp1 = m.helper(id);   // returns the pointer to movie node

    if (temp1 == NULL) {
        cout << "Invalid ID!\n";
        return;
    }

    cout<<"Enter row of your seat :- ";
    cin>>r;
    cout<<"Enter col of your seat :- ";
    cin>>c;
    bool flag = m.removeSeat(temp1, r, c); // free seat
    if(!flag)
    {
        cout<<"This seat wasnt booked! "<<endl;
        return;
    }
    customerNode* temp = front, *prev = NULL;
    if(front == NULL) // empty queue
    {
        cout<<"Empty Ticket list"<<endl;
        return;
    }
    if(temp -> row == r && temp -> col == c && front == rear) // only one node in queue
    {
        delete front;
        front = NULL;
        rear = NULL;
        cout<<"Ticket is deleted"<<endl;
        return;
    }
    if(temp -> row == r && temp -> col == c) // delete first node in queue
    {
        prev = front;
        front = front -> next;
        delete prev;
        cout<<"Ticket is deleted"<<endl;
        return;
    }
    else
    {
        while(temp && (temp -> row != r || temp -> col != c)) // till we reach end or the given customer node
        {
            prev = temp;
            temp = temp -> next;
        }
        if(temp == NULL)
        {
            cout<<"No such ticket!"<<endl;
            return;
        }
        prev -> next = temp -> next;
    }
    cout<<"Ticket is deleted"<<endl;
    delete temp;
}
void customerList :: displayTicket(MovieList& m) // display booked ticket
{
    if(front == NULL)  // empty queue
    {
        cout<<"No tickets are booked! "<<endl;
        return;
    }
    int id;
    cout<<"\nEnter movie id : ";
    cin>>id;
    movieNode* temp1 = m.helper(id);   // returns the pointer to movie node 
    if(temp1 == NULL)          // if movie isnt present
    {
        cout<<"Invalid ID !"<<endl;
        return;
    }
    string c;
    getline(cin, c);
    string fullname;
    cout<<"Enter your full name : ";
    getline(cin, fullname);
    customerNode* temp = front;
    while(temp && (temp -> name != fullname || temp1 -> moviename != temp -> movie_name))      // find by name 
        temp = temp -> next;
    if(!temp)
        cout<<"No such seat booked!"<<endl;
    else
    {   
    	cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------\n";
    	cout<<left<<setfill(' ')<<setw(20)<<"NAME"<<setw(20)<<"MOVIE"<<setw(15)<<"DATE"<<setw(18)<<"TIME"<<setw(18)<<"PRICE"<<setw(13)<<"ROW"<<setw(13)<<"COL"<<endl;
    	cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------";

    	cout<<"\n"<<left<<setfill(' ')<<setw(20)<<temp->name<<setw(20)<<temp->movie_name<<setw(15)<<temp->date<<setw(18)<<temp->show_time<<setw(18)<<temp->price<<setw(13)<<temp->row<<setw(13)<<temp->col<<endl;
        cout<<"\n-----------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout<<endl;
    }
}
void customerList :: addTicket(MovieList& m) // add new tickets
{
    int rows, cols;
    string name, time, show_date,movie;
    int i = 0, num_tickets = 0;
    bool flag = m.displayMovies();      // returns flase if no movies are present
    if(!flag)
    {
        cout<<"First Add Movies! "<<endl;
        return;
    }
    cout<<"\n\nEnter the no. of tickets you'd like to book : ";
    cin>>num_tickets;
    do
    {
        int id;
        cout<<"\nEnter movie id :- ";
        cin>>id; 
        movieNode* temp = m.helper(id);          // returns the pointer to movie node
        if(temp == NULL)
        {
            cout<<"Invalid ID !"<<endl;
            continue;
        }
        if(m.isFull(temp))   // if seat matrix of that movie is full 
        {
            cout<<"MOVIE HOUSEFULL! "<<endl;
            return;
        }
        m.seatMatrix(temp); // display seat matrix of that movie
        
        while(true)
        {
            cout<<"\nEnter the row for the seat to be booked : ";
            cin>>rows;
            cout<<"\nEnter the column for the seat to be booked : ";
            cin>>cols;
            if(rows < 0 || rows >= MAXROW || cols < 0 || cols >= MAXCOL) // if invalid input is given
                cout<<"\nYou have exceeded the rows or columns";
            else
            {
                bool editted = m.editMatrix(temp, rows, cols);   // to book the seat in the seat matrix
                if(!editted)
                    cout<<"This seat is already taken! "<<endl;
                else
                    break;
            }
        }
        string c;
        getline(cin, c);
        cout<<"Enter your full name : ";
        getline(cin, name);
        customerNode* newnode = new customerNode(rows, cols, name, id);
        assign(newnode, m, id);
        if(front == NULL)          // first customer
        {
            front = newnode;
            rear = newnode;
        }
        else                          // add customer to end of the list
        {
            rear -> next = newnode;
            rear = rear -> next;
        }
        i++;
        cout<<"\nSeat booked successfully! \n"<<endl;
    }while(i != num_tickets);
}
void customerList :: displayAllTickets() // display all tickets
{
    if(!front)
    {
        cout<<"No booked tickets!"<<endl;
        return;
    }
	customerNode *ptr = front;
	cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<left<<setfill(' ')<<setw(20)<<"NAME"<<setw(20)<<"MOVIE"<<setw(15)<<"DATE"<<setw(18)<<"TIME"<<setw(18)<<"PRICE"<<setw(13)<<"ROW"<<setw(13)<<"COL"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------";
    while(ptr != NULL)
    {
        cout<<"\n"<<left<<setfill(' ')<<setw(20)<<ptr->name<<setw(20)<<ptr->movie_name<<setw(15)<<ptr->date<<setw(18)<<ptr->show_time<<setw(18)<<ptr->price<<setw(13)<<ptr->row<<setw(13)<<ptr->col;
        ptr = ptr->next;
    }
    cout<<"\n-----------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<endl;
}      
int main()
{
    int choice, choice1, choice2;
    string pass, w;
    MovieList m;     // created a list of movies
    customerList c;   // created a queue of cutomers
    while(true)
    {
        cout<<"\n\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n     Movie Ticket Booking System ";
        cout<<"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n              WELCOME !";
        cout<<"\n1. Enter as employee "<<endl;
        cout<<"2. Enter as customer "<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<<"\nEnter Your Choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1: 
                cout<<"Enter the password :- ";
                getline(cin, w);
                getline(cin, pass);
                if(pass != "admin123")
                {
                    cout<<"Wrong password! "<<endl;
                    choice1 = 5;
                }
                else
                    choice1 = 1;
                while(choice1 != 5)
                {
                    cout<<"\n\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                    cout<<"\n     Movie Ticket Booking System ";
                    cout<<"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                    cout<<"\n              WELCOME !";
                    cout<<"\n 1. Add New Movie  ";
                    cout<<"\n 2. Delete movie  ";
                    cout<<"\n 3. Show movie list ";
                    cout<<"\n 4. Display seat matrix of a Movie ";
                    cout<<"\n 5. Go BACK";
                    cout<<"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    cout<<"\nEnter Your Choice : ";
                    cin>>choice1;
                    switch(choice1)
                    {
                        case 1:
                            m.addMovie();
                            cout<<"\nMovie added successfully!\n";
                            cout<<"\nMovie List after addition of movie :\n";
                            m.displayMovies();
                            break;
                        case 2:
                            if(m.removeMovie())
                            {
                                cout<<"\nMovie deleted successfully!\n";
                                cout<<"\nMovie List after deletion of movie :\n";
                                m.displayMovies();
                            }
                            break;
                        case 3:
                            cout<<"\nShowing Movie List :\n";
                            m.displayMovies();
                            break;
                        case 4:
                            m.displaySeatMatrix();
                            break;
                    }
                }
                break;  
            case 2:
                do
                {
                    cout<<"\n\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                    cout<<"\n     Movie Ticket Booking System ";
                    cout<<"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                    cout<<"\n 1. Book Ticket";
                    cout<<"\n 2. Delete booked Ticket";
                    cout<<"\n 3. Show my ticket ";
                    cout<<"\n 4. Show all tickets";
                    cout<<"\n 5. Go Back \n";
                    cout<<"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    cout<<"\nEnter Your Choice : ";
                    cin>>choice2;
                    switch(choice2)
                    {
                        case 1:
                            cout<<"Movie List : "<<endl;
                            c.addTicket(m);
                            break;
                        case 2:
                            c.deleteTicket(m);
                            break;
                        case 3:
                            c.displayTicket(m);   
                            break;
                        case 4:
                            c.displayAllTickets();
                            break;
                    }
                }while(choice2 != 5);
                break;
            case 3:
                return 0;
        }
    }
}
/*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
1. Enter as employee
2. Enter as customer
3. Exit

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Enter the password :- 1234
Wrong password!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
1. Enter as employee
2. Enter as customer
3. Exit

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Enter the password :- admin123


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 2
Movie List is Empty!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 3

Showing Movie List :
Movie List is Empty!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
Enter movie ID :- 100
No such Movie!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Enter Movie name :- neerja
Enter Movie time :- 12:00 PM
Enter Movie date :- 12/09/201
Enter Movie price :- 120

Movie added successfully!

Movie List after addition of movie :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
1    neerja              12/09/201      12:00 PM  120
------------------------------------------------------------------------


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Enter Movie name :- raazi
Enter Movie time :- 03:00 PM
Enter Movie date :- 08/08/2021
Enter Movie price :- 200

Movie added successfully!

Movie List after addition of movie :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
1    neerja              12/09/201      12:00 PM  120

2    raazi               08/08/2021     03:00 PM  200
------------------------------------------------------------------------


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Enter Movie name :- chak de india
Enter Movie time :- 04:00 PM
Enter Movie date :- 03/08/2021
Enter Movie price :- 300

Movie added successfully!

Movie List after addition of movie :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
1    neerja              12/09/201      12:00 PM  120

2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 3

Showing Movie List :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
1    neerja              12/09/201      12:00 PM  120

2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
Enter movie ID :- 1

Seat Matrix :
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
Enter movie ID :- 2

Seat Matrix :
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
Enter movie ID :- 3

Seat Matrix :
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 2
Enter movie id :- 1

Movie deleted successfully!

Movie List after deletion of movie :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
Enter movie ID :- 1
No such Movie!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 3

Showing Movie List :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 5


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
1. Enter as employee
2. Enter as customer
3. Exit

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 2


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 2
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------
Enter movie id :- 100
Invalid ID!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 3
No tickets are booked!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
No booked tickets!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Movie List :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------


Enter the no. of tickets you'd like to book : 2

Enter movie id :- 1
Invalid ID !

Enter movie id :- 2
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _

Enter the row for the seat to be booked : 4

Enter the column for the seat to be booked : 4
Enter your full name : aditi kajale

Seat booked successfully!


Enter movie id :- 2
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ x _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _

Enter the row for the seat to be booked : 4

Enter the column for the seat to be booked : 4
This seat is already taken!

Enter the row for the seat to be booked : 3

Enter the column for the seat to be booked : 4
Enter your full name : shilpa kajale

Seat booked successfully!



 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
-----------------------------------------------------------------------------------------------------------------------------------------------------
NAME                MOVIE               DATE           TIME              PRICE             ROW          COL
-----------------------------------------------------------------------------------------------------------------------------------------------------
aditi kajale        raazi               08/08/2021     03:00 PM          200               4            4
shilpa kajale       raazi               08/08/2021     03:00 PM          200               3            4
-----------------------------------------------------------------------------------------------------------------------------------------------------



 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Movie List :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------


Enter the no. of tickets you'd like to book : 1

Enter movie id :- 3
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _

Enter the row for the seat to be booked : 2

Enter the column for the seat to be booked : 2
Enter your full name : anushka

Seat booked successfully!



 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Movie List :
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------


Enter the no. of tickets you'd like to book : 3

Enter movie id :- 3
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ x _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _

Enter the row for the seat to be booked : 5

Enter the column for the seat to be booked : 5
Enter your full name : yogesh

Seat booked successfully!


Enter movie id :- 3
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ x _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ x _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _

Enter the row for the seat to be booked : 1

Enter the column for the seat to be booked : -1

You have exceeded the rows or columns
Enter the row for the seat to be booked : 100

Enter the column for the seat to be booked : 8

You have exceeded the rows or columns
Enter the row for the seat to be booked : 5

Enter the column for the seat to be booked : 5
This seat is already taken!

Enter the row for the seat to be booked : 3

Enter the column for the seat to be booked : 3
Enter your full name : sakshi

Seat booked successfully!


Enter movie id :- 2
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ x _ _ _ _ _
_ _ _ _ x _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _

Enter the row for the seat to be booked : 6

Enter the column for the seat to be booked : 6
Enter your full name : jui

Seat booked successfully!



 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
-----------------------------------------------------------------------------------------------------------------------------------------------------
NAME                MOVIE               DATE           TIME              PRICE             ROW          COL
-----------------------------------------------------------------------------------------------------------------------------------------------------
aditi kajale        raazi               08/08/2021     03:00 PM          200               4            4
shilpa kajale       raazi               08/08/2021     03:00 PM          200               3            4
anushka             chak de india       03/08/2021     04:00 PM          300               2            2
yogesh              chak de india       03/08/2021     04:00 PM          300               5            5
sakshi              chak de india       03/08/2021     04:00 PM          300               3            3
jui                 raazi               08/08/2021     03:00 PM          200               6            6
-----------------------------------------------------------------------------------------------------------------------------------------------------



 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 3

Enter movie id : 2
Enter your full name : aditi kajale
-----------------------------------------------------------------------------------------------------------------------------------------------------
NAME                MOVIE               DATE           TIME              PRICE             ROW          COL
-----------------------------------------------------------------------------------------------------------------------------------------------------
aditi kajale        raazi               08/08/2021     03:00 PM          200               4            4

-----------------------------------------------------------------------------------------------------------------------------------------------------



 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 3

Enter movie id : 3
Enter your full name : aditi kajale
No such seat booked!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 2
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------
Enter movie id :- 2
Enter row of your seat :- 6
Enter col of your seat :- 6
Ticket is deleted


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
-----------------------------------------------------------------------------------------------------------------------------------------------------
NAME                MOVIE               DATE           TIME              PRICE             ROW          COL
-----------------------------------------------------------------------------------------------------------------------------------------------------
aditi kajale        raazi               08/08/2021     03:00 PM          200               4            4
shilpa kajale       raazi               08/08/2021     03:00 PM          200               3            4
anushka             chak de india       03/08/2021     04:00 PM          300               2            2
yogesh              chak de india       03/08/2021     04:00 PM          300               5            5
sakshi              chak de india       03/08/2021     04:00 PM          300               3            3
-----------------------------------------------------------------------------------------------------------------------------------------------------



 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 2
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------
Enter movie id :- 100
Invalid ID!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 2
---------------------------------------------------------------------
ID   NAME                DATE           TIME      PRICE
--------------------------------------------------------------------
2    raazi               08/08/2021     03:00 PM  200

3    chak de india       03/08/2021     04:00 PM  300
------------------------------------------------------------------------
Enter movie id :- 3
Enter row of your seat :- 7
Enter col of your seat :- 1
This seat wasnt booked!


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1. Book Ticket
 2. Delete booked Ticket
 3. Show my ticket
 4. Show all tickets
 5. Go Back

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 5


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
1. Enter as employee
2. Enter as customer
3. Exit

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 1
Enter the password :- admin123


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
Enter movie ID :- 2

Seat Matrix :
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ x _ _ _ _ _
_ _ _ _ x _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 4
Enter movie ID :- 3

Seat Matrix :
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ x _ _ _ _ _ _ _
_ _ _ x _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ x _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
 1. Add New Movie
 2. Delete movie
 3. Show movie list
 4. Display seat matrix of a Movie
 5. Go BACK
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 5


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Movie Ticket Booking System
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              WELCOME !
1. Enter as employee
2. Enter as customer
3. Exit

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Your Choice : 3
*/


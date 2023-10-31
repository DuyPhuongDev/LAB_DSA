#include<iostream>
#include<cstring>
using namespace std;

class Book
{
private:
    char *title;
    char *authors;
    int publishingYear;

public:
    Book()
    {
        /*
         * STUDENT ANSWER
         */
         title = nullptr;
         authors = nullptr;
         publishingYear=0;
    }

    Book(const char *title, const char *authors, int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        this->title = new char[strlen(title)+1];
        for(unsigned int i=0;title[i]!='\0';i++){
            this->title[i]=title[i];
        }
        this->title[strlen(title)] = '\0';
        this->authors = new char[strlen(authors)+1];
        for(unsigned int i=0;authors[i]!='\0';i++){
            this->authors[i]=authors[i];
        }
        this->authors[strlen(authors)] = '\0';
        this->publishingYear = publishingYear;
    }

    ~Book()
    {
        /*
         * STUDENT ANSWER
         */
        if(title) delete[] title;
        if(authors) delete[] authors;
    }
    
    friend class Printer;
};

class Printer
{
public:
    /*
    Giai tich 1
    Nguyen Dinh Huy
    Nguyen Thi Xuan Anh
    2000
    */
    static void printBook(const Book book)
    {
        /*
         * STUDENT ANSWER
         */
        cout<<book.title<<'\n';
        int len = strlen(book.authors);
        for(int i=0;i<len;i++){
            if(book.authors[i]==','){
                for(int j = i+1;j<len;j++) book.authors[j] = book.authors[j+1];
                len--;
            }
        }
        book.authors[len]='\0';
        char *token = strtok(book.authors,",");
        //cout<<token<<'\n';
        while(token!=NULL){
            cout<<token<<'\n';
            token = strtok(NULL,",");
        }
        cout<<book.publishingYear<<'\n';
    }
};

int main(){
    Book book1("Giai tich 1", "Nguyen Dinh Huy, Nguyen Thi Xuan Anh", 2000);
    Printer::printBook(book1);
    return 0;
}
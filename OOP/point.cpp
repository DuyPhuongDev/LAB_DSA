#include<iostream>
#include<string>
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
        char* authorsCopy = new char[strlen(book.authors) + 1];
        for(unsigned int i=0;authorsCopy[i]!='\0';i++){
            authorsCopy[i]=book.authors[i];        }
        authorsCopy[strlen(authorsCopy)] = '\0';
        cout<<book.title<<'\n';
        cout<<authorsCopy;
        int len = strlen(authorsCopy);
        for(int i=0;i<len;i++){
            if(authorsCopy[i]==','){
                for(int j = i+1;j<len;j++) authorsCopy[j] = authorsCopy[j+1];
                len--;
            }
        }
        authorsCopy[len]='\0';
        char *token = strtok(authorsCopy,",");
        //cout<<token<<'\n';
        while(token!=NULL){
            cout<<token<<'\n';
            token = strtok(NULL,",");
        }
        cout<<book.publishingYear<<'\n';
    }
};
int main(){
    Book book1("Introduction to Algorithms", "Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein", 1990);
    Printer::printBook(book1);
    return 0;
}
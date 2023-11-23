#include<bits/stdc++.h>
#include "Vector.cpp"

#define int long long

using namespace std;
class Answer {
private:
    Vector<string> ans;
public:
    Answer() {
        ans.assign({"", "", "", ""});
    }
    string getAns(int i) {return ans[i];}
    void setAns(int i, string s) {ans[i] = s;}
    friend istream& operator>> (istream& is, Answer& a) {
        for (int i = 0; i < 4; i++) getline(is, a.ans[i]);
        return is;
    }
    friend ostream& operator<< (ostream& os, Answer& a) {
        for (int i = 0; i < 4; i++) os << a.ans[i] << endl;
        return os;
    }
};

// biểu diễn 1 câu hỏi trong đề thi + câu trả lời + câu tl đúng

/*Mỗi Test chứa 1 Answer
    số nguyên correctAns biểu diễn câu trả lời đúng*/
class Test {
private:
    string Question; //chuỗi biểu diễn câu hỏi 
    Answer Ans; // chứa các câu hỏi
    int correctAns; // số nguyên là câu trả lời đúng
public:
    Test() {}
    //lấy 1 câu hỏi
    string getQs() {return Question;}
    //lấy câu trả lời
    string getAnswer(int i) {return Ans.getAns(i);}
    //lấy câu trả lời đúng
    int getCorrectAns() {return correctAns;}
    //thiết lập câu trả lời đúng
    void setCorrectAns(int x) {correctAns = x;}
    //thiết lập giá trị của câu hỏi thứ i
    void setAnswer(int i, string s) {Ans.setAns(i, s);}
    friend istream& operator>> (istream& is, Test& t) {
        getline(is, t.Question);
        is >> t.Ans;
        is >> t.correctAns;
        is.ignore();
        return is;
    }
    friend ostream& operator<< (ostream& os, Test& t) {
        os << t.Question << endl;
        os << t.Ans;
        os << t.correctAns;
        return os;
    }
};
main() {
    ifstream input; ofstream output;
    input.open("input_26.txt");
    output.open("output_26.txt");

    int n; 
    input >> n; input.ignore();

    Vector<Test> LTest  ;
    for (int i = 0; i < n; i++) {
        Test temp;
        //nhập từ tệp
        input >> temp;
        LTest.push_back(temp);
    }
    for (int i = 0; i < n; i++) {
        output << LTest[i] << endl;
    }

    srand(time(NULL));

    int k;
    do {
        cout << "Enter number of questions of new test: ";
        cin >> k;
    } while (k > n);

    Vector<Test> newTest;

    set<int> se;
    while (se.size() < k) {
        int num = rand();
        num %= n;
        se.insert(num);
    }
    //push k câu hỏi và câu trả lời vào newtest
    for (auto x : se) {
        newTest.push_back(LTest[x]);
    }

    for (int i = 0; i < newTest.size(); i++) {
        int num = rand();
        num %= 4;
        // 0 <= num <=3
        if (num == newTest[i].getCorrectAns()){
          newTest[i].setCorrectAns(3 - num); 
          cout << "Phan tu thu 7989: " << i<< "  " << num << endl; 
        } 
        else if (3 - num == newTest[i].getCorrectAns()){
          newTest[i].setCorrectAns(num);  
          cout << "Phan tu thu: " << i<< "  " << 3-num << endl;
        }  
        string tg1 = newTest[i].getAnswer(num);
        string tg2 = newTest[i].getAnswer(3 - num);
        newTest[i].setAnswer(num, tg2);
        newTest[i].setAnswer(3 - num, tg1);
    }
    

    int user_point = 0;
    for (int i = 0; i < newTest.size(); i++) {
        cout << newTest[i].getQs() << endl;
        for (int j = 0; j < 4; j++) {
            cout << j << ". " << newTest[i].getAnswer(j) << endl;
        }
        int user_ans; cin >> user_ans;
        if (user_ans == newTest[i].getCorrectAns()) ++user_point;
    }

    cout << "You got " << user_point << "/" << newTest.size() << " point! Congrats!!!";

}
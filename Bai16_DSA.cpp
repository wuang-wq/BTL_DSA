#include <bits/stdc++.h>
using namespace std;

class BigNumber {
private:
    vector<int> digits;
public:
    BigNumber() {}

    BigNumber(const string& s) {
        for (char c : s) {
            digits.push_back(c - '0');
        }
        //  reverse(digits.begin(), digits.end());
    }

    friend istream& operator>>(istream& in, BigNumber& a) {
        string s;
        in >> s;
        a = BigNumber(s);
        return in;
    }


    friend ostream& operator<<(ostream& out, const BigNumber& a) {
        for (int d : a.digits) {
            out << d;
        }
        return out;
    }

void add_zero(int sz) 
{	
    // Đảo ngược vector lại khi thêm số 0 vào.
    reverse(digits.begin(),digits.end()); 

    while (digits.size() < sz) 
        digits.push_back(0); 

    reverse(digits.begin(), digits.end());
}

// Xóa các số 0 vô nghĩa ở đầu một số nguyên lớn a.
                    void del_zero() 
                    { 	
                        reverse(digits.begin(), digits.end()); 
                        
                        while (digits.size() >= 2) 
                        {
                            if (digits.back() == 0) 
                                digits.pop_back();
                            else 
                                break;
                        }

                        reverse(digits.begin(), digits.end());
                    }

    BigNumber operator+( BigNumber& other)  {
    BigNumber result;
    
    // Tìm độ dài lớn nhất giữa hai số.
    int sz = max(digits.size(), other.digits.size());

    // Tạo bản sao của this và other để thay đổi độ dài mà không ảnh hưởng đến đối tượng gốc.
    BigNumber a_copy = *this;
    BigNumber b_copy = other;

    // Đảm bảo cả hai số có cùng độ dài bằng cách thêm số 0 vào đầu.
    a_copy.add_zero(sz);
    b_copy.add_zero(sz);

    // Thực hiện phép cộng từng chữ số.
    int carry = 0;
    for (int i = sz-1; i >= 0; i--) {
        int sum = a_copy.digits[i] + b_copy.digits[i] + carry;
        carry = sum / 10;
        sum %=10;
        result.digits.push_back(sum);
    } 
    result.digits.push_back(carry);
    reverse(result.digits.begin(), result.digits.end());
    result.del_zero();
    return result;
}



//Thực hienj phép trừ
    BigNumber operator-( BigNumber& other)  {
    BigNumber result;
     
    // Tìm độ dài lớn nhất giữa hai số.
    int sz = max(digits.size(), other.digits.size());

    // Tạo bản sao của this và other để thay đổi độ dài mà không ảnh hưởng đến đối tượng gốc.
    BigNumber a_copy = *this;
    BigNumber b_copy = other;

    // Đảm bảo cả hai số có cùng độ dài bằng cách thêm số 0 vào đầu.
    a_copy.add_zero(sz); 
    b_copy.add_zero(sz); 

    // Thực hiện phép trừ từng chữ số.
    int carry = 0;   
    for (int i = sz-1; i >=0; i--) {
        int hieu = a_copy.digits[i] - b_copy.digits[i] - carry;
        if(hieu < 0){
            hieu += 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        result.digits.push_back(hieu);
    }

    // Nếu còn dư, thêm nó vào kết quả.
    if (carry) {
        result.digits.push_back(carry);
    }

    reverse(result.digits.begin(), result.digits.end());

    result.del_zero();
    return result;
}

    BigNumber operator*( BigNumber& other)  {
        BigNumber result;
        result.digits.resize(digits.size() + other.digits.size() +1);

        reverse(digits.begin(), digits.end());
        reverse(other.digits.begin(), other.digits.end());

        for (int i = 0; i < digits.size(); i++) {
            for (int j = 0; j < other.digits.size() ; j++) {
                result.digits[i + j] += (digits[i] * other.digits[j]);
                result.digits[i + j + 1] += (result.digits[i + j] / 10);
                result.digits[i + j] %= 10;
            }
        }
        result.digits.push_back(0);
        for (int i = 0; i < result.digits.size() - 1; ++i) {
            result.digits[i + 1] += (result.digits[i] / 10);
            result.digits[i] %= 10;
        }

        // while (result.digits.size() > 1 && result.digits.back() == 0) {
        //     result.digits.pop_back();
        // }
        reverse(result.digits.begin(), result.digits.end());
        result.del_zero();
        return result;
    }


string toString() const {
    string result;
    bool leadingZero = true; // Đánh dấu các số 0 ở đầu chuỗi.

    for (int i = digits.size() - 1; i >= 0; i--) {
        result += to_string(digits[i]);
    }

    // Trường hợp đặc biệt khi số ban đầu là 0, trả về chuỗi "0".
    if (result.empty()) {
        result = "0";
    }

    // Trường hợp số âm, thêm dấu trừ vào chuỗi kết quả.
    if (digits.size() > 0 && digits.back() < 0) {
        result += '-';
    }

    reverse(result.begin(), result.end());
    return result;
}



};

//tính số fibonanci thứ n
        BigNumber fibonacci(int n){
            if(n==0){
                return BigNumber("0");
            }
            if(n==1){
                return BigNumber("1");
            }

            BigNumber f0("0"), f1("1"), fn;
            for(int i=2; i<=n; i++){
                fn = f0 + f1;
                f0 = f1;
                f1 = fn;
                // cout << "So fibonacci thu " << i << ":  "<< fn << endl;
            }
            
            return fn;
        }

//tinh giai thua
        BigNumber factorial(int n) {
            BigNumber result("1");

            for (int i = 2; i <= n; i++) {
                // result = result * BigNumber(to_string(i));
                BigNumber c = BigNumber(to_string(i));
                result = result * c;
                // cout <<"Gia tri thu "<< i-1 <<": " << result<< endl;
                
            }

            return result;
        }

int main() {
    // >> a
    int m; 
    cout <<"Nhap M: "; 
    cin >> m;
    if(m <0) {
        cout<<"m la so am"<< endl;
        return 1;
    }
    BigNumber result = fibonacci(m);
    cout << "Fibonacci(" << m << ") = " << result.toString() << endl; 

    // >> b
    int k; 
    cout << "Nhap K: "; 
    cin >> k;
    if(k <0) {
        cout<<"k la so am"<< endl;
        return 1;
    }
    BigNumber gt = factorial(k);
    cout << k << "! = " << gt.toString() << endl;

    return 0;
}

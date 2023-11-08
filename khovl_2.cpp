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
    // Đảo ngược vector lại để tối ưu thời gian khi thêm số 0 vào.
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

// Cân bằng độ dài hai số a và b bằng cách thêm các số 0 vào đầu.
void change(const BigNumber& other) 
{ 
    int sz = max(digits.size(), other.digits.size());
    add_zero(sz);
    add_zero(sz);
}
//Thực hienj phép cộng
//     BigNumber operator+( BigNumber& other) const {
//     BigNumber result;
//     reverse(other.digits.begin(), other.digits.end());
//     // Tìm độ dài lớn nhất giữa hai số.
//     int sz = max(digits.size(), other.digits.size());

//     // Tạo bản sao của this và other để thay đổi độ dài mà không ảnh hưởng đến đối tượng gốc.
//     BigNumber a_copy = *this;
//     BigNumber b_copy = other;

    
//     // Đảm bảo cả hai số có cùng độ dài bằng cách thêm số 0 vào đầu.
//     a_copy.add_zero(sz); 
//     b_copy.add_zero(sz); 

//     // Thực hiện phép cộng từng chữ số.
//     int carry = 0;
//     for (int i = sz-1; i >=0; i--) {
//         int sum = a_copy.digits[i] + b_copy.digits[i] + carry;
//         result.digits.push_back(sum % 10);
//         carry = sum / 10;
//     }

//     // Nếu còn dư, thêm nó vào kết quả.
//     if (carry) {
//         result.digits.push_back(carry);
//     }
//     reverse(result.digits.begin(), result.digits.end());

//     result.del_zero();
//     //tách các chữ số
//     // for(int digit : result.digits){
//     //        cout << digit << " ";
//     //     }
//     return result;
// }







    BigNumber operator+( BigNumber& other)  {
    BigNumber result;
    
    // Tìm độ dài lớn nhất giữa hai số.
    int sz = max(digits.size(), other.digits.size());
    reverse(digits.begin(), digits.end());
    reverse(other.digits.begin(), other.digits.end());
    // Tạo bản sao của this và other để thay đổi độ dài mà không ảnh hưởng đến đối tượng gốc.
    BigNumber a_copy = *this;
    BigNumber b_copy = other;

    // Đảm bảo cả hai số có cùng độ dài bằng cách thêm số 0 vào đầu.
    a_copy.add_zero(sz);
    b_copy.add_zero(sz);

    // Thực hiện phép cộng từng chữ số.
    int carry = 0;
    for (int i = 0; i < sz; ++i) {
        int sum = a_copy.digits[i] + b_copy.digits[i] + carry;
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }

    // Nếu còn dư, thêm nó vào kết quả.
    if (carry) {
        result.digits.push_back(carry);
    }

    return result;
}











//Thực hienj phép trừ
    BigNumber operator-( BigNumber& other)  {
    BigNumber result;
    // reverse(digits.begin(), digits.end());
    // reverse(other.digits.begin(), other.digits.end());
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
    //tách các chữ số
    // for(int digit : result.digits){
    //        cout << digit << " ";
    //     }
    return result;
}

    BigNumber operator*( BigNumber& other)  {
        BigNumber result;
        result.digits.resize(digits.size() + other.digits.size() +1);

        // cout <<"Sz ban dau:  " << result.digits.size() << endl;


        reverse(digits.begin(), digits.end());
        reverse(other.digits.begin(), other.digits.end());


        for (int i = 0; i<digits.size(); i++) {
            for (int j = 0; j < other.digits.size() ; j++) {
                result.digits[i + j] += (digits[i] * other.digits[j]);
                // cout << "KQ dc them tai: " << i << " va " << j << " la:  " <<  result.digits[i+j] << endl;
                result.digits[i + j + 1] += (result.digits[i + j] / 10);
                result.digits[i + j] %= 10;
            }
        }
        result.digits.push_back(0);
        for (int i = 0; i < result.digits.size() - 1; ++i) {
            result.digits[i + 1] += (result.digits[i] / 10);
            result.digits[i] %= 10;
            // cout<<result.digits[i]<<endl;
        }

        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }
        reverse(result.digits.begin(), result.digits.end());
        result.del_zero();
        return result;
    }



};

int main() {
    BigNumber a, b;
    int n;
    cout << "Nhap so nguyen lon a: ";
    cin >> a;
    cout << "Nhap so nguyen lon b: ";
    cin >> b;
    cout << "Nhap so nguyen n: ";
    cin >> n;
    
cout <<"KQ nhan mot so lon voi mot so lon: " << a * b << endl;
    cout << "KQ tong mot so lon voi mot so lon: " << a+b << endl;

    cout << "KQ hieu mot so lon voi mot so lon: " << a-b << endl;

    BigNumber n_as_bigNumber = to_string(n);
    // Nhân số lớn a và số nhỏ n. Chuyển n qua số lớn để nhân.
    BigNumber product = a * n_as_bigNumber;
    cout << "KQ nhan mot so lon voi 1 so nho: " << product << endl;    


    return 0;
}






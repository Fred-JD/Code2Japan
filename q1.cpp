// December 2020
// by Seak Jian De

#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void print_2d_vec(const vector<vector<char>> vec);
int convert_char2int(const char c);

// DataType that store cordinate of the map
struct cordinate
{   
    int col;
    int row;
};

// Function Calculate the Sum
int generate_output(const vector<int> vec)
{
    int sum = 0;
    for (auto x : vec) {
        sum += x;
    }
    return sum;
}

// Function swap the boom
void swap_sort_vec(const vector<vector<char>> vec_char, const vector<cordinate> vec_cor, vector<int> *vec_int)
{
    for (int i = 0; i < vec_int->size(); i++)
    {
        if (i > vec_cor.size()) {
            break;
        }

        int col = vec_cor[i].col;
        int row = vec_cor[i].row;
        int num = convert_char2int(vec_char[col][row]);

        if (num > vec_int->at(i)) {
            vec_int->at(i) = num;
        }
        else {
            break;
        }
    }
}

// Function that sort the element of the data
vector<int> sort_vec(const vector<vector<char>> vec)
{
    vector<int> vec_int;
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec[i].size(); j++){
            if(vec[i][j] != '*'){
                int num = convert_char2int(vec[i][j]);
                vec_int.push_back(num);
            }
        }
    }
    sort(vec_int.begin(), vec_int.end());
    return vec_int;
}

// Function that remove the element when boom
vector<vector<char>> after_bomb(const vector<vector<char>> vec)
{
    vector<vector<char>> vec_result;
    vector<cordinate> vec_bomb;
    // Copy vec to vec_result
    for (int i = 0; i < vec.size(); i++)
    {
        vec_result.push_back(vec[i]);
    }
    // Update the bomb cordinate into a new vector
    cordinate bomb_cor;
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            if (vec[i][j] == 'B') {
                bomb_cor.row = i;
                bomb_cor.col = j;
                vec_bomb.push_back(bomb_cor);
            }
        }
    }

    // cout << "size : " << vec_bomb.size() << endl;
    for (int k = 0; k < vec_bomb.size(); k++)
    {
        int col = vec_bomb[k].col;
        int row = vec_bomb[k].row;
        
        for (int i = 0; i < vec.size(); i++) {
            for (int j = 0; j < vec[0].size(); j++){
                vec_result[i][col] = '*';
                vec_result[row][j] = '*';
            }
        }
    }

    return vec_result;
}

// Find the maximum number from the vector that consit
vector<cordinate> max_num_cor(const vector<vector<char>> vec, int num_swap)
{
    vector<vector<char>> copy_vec;
    vector<cordinate> vec_cor;
    int max;

    // Copy vector
    for (int i = 0; i < vec.size(); i++)
    {
        copy_vec.push_back(vec[i]);
    }

    for (int k = 0; k < num_swap; k++){
        cordinate cor;
        max = 0;
        for (int i = 0; i < copy_vec.size(); i++){
            for (int j = 0; j < copy_vec[0].size(); j++){
                if (copy_vec[i][j] > max && copy_vec[i][j] != 'B'){
                    max = copy_vec[i][j];
                    cor.col = i;
                    cor.row = j;
                }
            }
        }

        copy_vec[cor.col][cor.row] = 0;
        vec_cor.push_back(cor);
    }

    return vec_cor;
}

// Function that swap the largest and smallest value
vector<cordinate> max_num_cor2(const vector<vector<char>> vec, int num_swap)
{
    vector<vector<char>> copy_vec;
    vector<cordinate> vec_cor;
    vector<vector<char>> vec_after_bomb;
    int max;

    // Copy vector
    for (int i = 0; i < vec.size(); i++)
    {
        copy_vec.push_back(vec[i]);
    }

    vec_after_bomb = after_bomb(vec);

    for (int k = 0; k < num_swap; k++) {
        cordinate cor;
        max = 0;
        for (int i = 0; i < copy_vec.size(); i++) {
            for (int j = 0; j < copy_vec[i].size(); j++) {
                if (vec_after_bomb[i][j] == '*' && copy_vec[i][j] > max && copy_vec[i][j] != 'B'){
                    max = copy_vec[i][j];
                    cor.col = i;
                    cor.row = j;
                }
            }
        }
        copy_vec[cor.col][cor.row] = 0;
        vec_cor.push_back(cor);
    }
    return vec_cor;
}

int convert_char2int(const char c)
{
    int num;
    stringstream str;
    str << c;
    str >> num;

    return num;
} 

void print_2d_vec(const vector<vector<char>> vec)
{
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec[0].size(); j++)
        {
            cout << vec[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void swap_num(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    vector<vector<char>> char_2d;

    int n, m, k;
    cout << "Enter Input Value\n";
    cin >> n >> m >> k;
    
    string str;

    for (int i = 0; i < n; i++)
    {
        vector<char> vec_char;
        vec_char.clear();

        cin >> str;
        char str_array[m + 1];

        strcpy(str_array, str.c_str());

        for (int j = 0; j < m; j++)
        {
            vec_char.push_back(str_array[j]);
        }
        char_2d.push_back(vec_char);
    }
    
    // Print the vector out
    cout << endl;
    cout << "The input matrix\n";
    print_2d_vec(char_2d);

    vector<cordinate> vec_cordinate = max_num_cor2(char_2d, k);

    vector<vector<char>> vec_after_bomb = after_bomb(char_2d);
    print_2d_vec(vec_after_bomb);

    vector<int> vec_int = sort_vec(vec_after_bomb);
    cout << "Element to add according position without swap\n";
    for (auto x : vec_int)
        cout << x << " ";
    cout << endl;

    if (k > 0)
        swap_sort_vec(char_2d, vec_cordinate, &vec_int);

    cout << "After Swaping\n";
    for (auto x : vec_int)
        cout << x << " ";
    cout << endl;

    int output = generate_output(vec_int);
    cout << "\nOutput : " << output << endl;
}
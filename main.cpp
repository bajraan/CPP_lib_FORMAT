#include <iostream>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

enum result
{
    fail,
    pass
};

std::vector<std::string>    split 
(
    const   std::string &s, 
    char    delim
){
                            
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}


std::vector<std::string>    str_parse_by_char 
(
    string  input, 
    char    delimiter
){
	std::string parsed;
	stringstream input_stringstream(input);
	vector<string> ret;
	while (getline(input_stringstream,parsed,delimiter))
		ret.push_back(parsed);
	return ret;
}



/**
 * Splits a string into substrings using a delimiter character.
 *
 * This function takes an input string and a delimiter character, and splits
 * the input string into substrings at the occurrences of the delimiter character.
 *
 * @param input     The input string to be split.
 * @param delimiter The delimiter character used for splitting the string.
 * @return          A vector containing the resulting substrings.
 *
 * @example
 *     std::string input = "Hello,world";
 *     std::vector<std::string> result = str_parse_by_char(input, ',');
 *
 *     // Result:
 *     // result[0] = "Hello"
 *     // result[1] = "world"
 *
 * @note
 *     - The function works only for single-byte characters.
 *     - The delimiter character is not included in the resulting substrings.
 *     - If the delimiter character is not found in the input string, the whole input string is returned as a single substring.
 */
std::vector<std::string>    str_parse_by_char
(
    const std::string&  input, 
    char                delimiter
){
    std::vector<std::string> ret;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != std::string::npos) {
        ret.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(delimiter, start);
    }

    ret.push_back(input.substr(start));

    return ret;
}



/**
 * Splits a string into substrings using multiple delimiter characters.
 *
 * This function takes an input string and multiple delimiter characters, and splits
 * the input string into substrings at the occurrences of those delimiter characters.
 *
 * @param input The input string to be split.
 * @param args  The delimiter characters used for splitting the string.
 * @return      A vector containing the resulting substrings.
 *
 * @tparam T   The types of the delimiter characters. Different character types (e.g., char, wchar_t) can be used.
 *
 * @example
 *     std::string input = "Hello,world|open|close";
 *     std::vector<std::string> result = str_parse_by_char_multi(input, ',', '|');
 *
 *     // Result:
 *     // result[0] = "Hello"
 *     // result[1] = "world"
 *     // result[2] = "open"
 *     // result[3] = "close"
 *
 * @note
 *     - The function works only for single-byte characters.
 *     - The result may contain empty substrings if multiple delimiter characters appear consecutively.
 *     - The order of the delimiter characters is significant. Substrings are created in the order of occurrence
 *       of the delimiter characters in the input string.
 */
template <typename... T>
std::vector<std::string>    str_parse_by_char_multi
(
    const std::string& input, 
    T...               args
){
    std::vector<std::string> ret;
    std::vector<char> delimiters{args...};
    size_t start = 0;

    for (size_t i = 0; i < input.length(); i++) {
        for (const auto& delimiter : delimiters) {
            if (input[i] == delimiter) {
                ret.push_back(input.substr(start, i - start));
                start = i + 1;
                break;
            }
        }
    }

    ret.push_back(input.substr(start));
    return ret;
}


std::vector<std::string>    str_parse_by_str
(
    string  s, 
    string  delimiter
){
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::vector<std::string>    str_parse_by_regex
(
    const std::string str,
    const std::string regex_str
){
    std::regex regexz(regex_str);
    return {std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
            std::sregex_token_iterator()};
}

void TEST_ALL(void);
void TEST_00__str_parse_by_char(void);
void TEST_00__str_parse_by_char_multi(void);


int main() {
	
    //TEST_ALL();
	TEST_00__str_parse_by_char();
    TEST_00__str_parse_by_char_multi();
	
	return 0;
}
void TEST_ALL(void)
{
    TEST_00__str_parse_by_char();
    TEST_00__str_parse_by_char_multi();
}
void TEST_00__str_parse_by_char(void)
{
    cout << endl;
    cout << "=== TEST_00__str_parse_by_char ===" << endl;
    cout << endl;


    bool test_result = false;
    const int  test_qty    = 1;
    struct DATA
    {
        string  input;
        string  exp_output[22];
        char    delimiter;
    };

    DATA TestTable[test_qty] =
    {
        "41 42 43 54 46 7B 34 35 43 31 31 5F 31 35 5F 55 35 33 46 55 4C 7D",
        "41","42","43","54","46","7B","34","35","43","31","31","5F","31","35","5F","55","35","33","46","55","4C","7D",
        ' '
    };


    for(int i =0; i<test_qty; i++)
    {
        std::vector<std::string> ret = split (TestTable[i].input , TestTable[i].delimiter);

        for (size_t j = 0; j < ret.size(); j++) {   
            if(TestTable[i].exp_output[j] == ret[j]) test_result = pass;
            else                                     test_result = fail;
        }

        test_result ? cout << "Test Pass" : cout << "Test_Fail";
        cout << endl;
    }
    // print CTF solution
    std::vector<std::string> ret = split (TestTable[0].input , ' ');
    for (const auto& i : ret) {
            cout << (char)std::stoi(i, nullptr, 16);
    }cout << endl;
}

void TEST_00__str_parse_by_char_multi(void)
{
    cout << endl;
    cout << "=== TEST_00__str_parse_by_char_multi ===" << endl;
    cout << endl;


    bool test_result = false;

    string input = "To+jest=prosty=test+raz=dwa";
    std::vector<std::string> exp_output = {"To", "jest", "prosty", "test", "raz", "dwa"};

    std::vector<std::string> ret = str_parse_by_char_multi (input , '+','=');

    for (size_t j = 0; j<ret.size(); j++) {   
        if(exp_output[j] == ret[j]) test_result = pass;
         else                        test_result = fail;
    }
    cout << "Test 01 result: ";
    test_result ? cout << "Test Pass" : cout << "Test_Fail";
    cout << endl;
    cout << "Input:  "<< input << endl;
    cout << "Output: "; for(auto i:ret) cout << i << " ";
    cout << endl;
}
// Guess a sentence provided by the user
# include <iostream>
# include <random>
# include <numeric>
using namespace std;

char get_random_letter(){
    // Generate a random letter
    const string alphabet = "abcdefghijklmnopqrstuvwxyz_";
    const size_t max_index = alphabet.length() - 1;

    int mynum = rand() % (max_index+1);

    char rand_char = alphabet[mynum];

    return rand_char;
}

string generate_random_string(int num_chars) {

    string random_string;

    const string alphabet = "abcdefghijklmnopqrstuvwxyz_";
    const size_t max_index = alphabet.length() - 1;

    for (int i = 0; i < num_chars; i ++) {
        int mynum = rand() % (max_index + 1);

        char rand_char = alphabet[mynum];

        random_string = random_string + rand_char;
    }

    return random_string;
}

float score(string str_target, string str_candidate, int num_chars) {

    float score = 0;

    for (int i = 0; i < num_chars; i++) {
        if (str_target[i] == str_candidate[i]) {
            score += 1;
        }
    }

    return score / num_chars;
}

int guess_full_string(string str1_target) {
    int num_chars = str1_target.length();

    float accuracy = 0;
    int iterations = 0;

    string str1_candidate;

    while (abs(accuracy - 1.) > 1e-6) {
        str1_candidate = generate_random_string(num_chars);

        accuracy = score(str1_target, str1_candidate, num_chars);

        iterations += 1;
        if (iterations % 1000000 == 0) {
            cout << "Number of iterations: " << iterations << endl;
        }
    }

    return iterations;
}

void score_array(float accuracy[], const string str_target, const string str_candidate, const int num_chars) {

    for (int i = 0; i < num_chars; i ++) {
        if (str_candidate[i] == str_target[i]) {
            accuracy[i] = 1;
        } else {
            accuracy[i] = 0;
        }
    }
}

float total_score(const float accuracy[], int num_chars) {

    float total_sum = 0;

    for (int i=0; i<num_chars; i++) {
        total_sum += accuracy[i] / num_chars;
    }
    return total_sum;

}

string get_candidate(string str_candidate, const float accuracy[], const int num_chars) {

    for (int i = 0; i < num_chars; i++){
        if (accuracy[i] != 1){
            str_candidate[i] = get_random_letter();
        }
    }

    return str_candidate;
}

int guess_individual_letter(const string str1_target) {

    int num_chars = str1_target.length();
    int num_iterations = 1;

    string str_candidate = generate_random_string(num_chars);

    float accuracy[num_chars];
    float total_acc;

    score_array(accuracy, str1_target, str_candidate, num_chars);
    total_acc = total_score(accuracy, num_chars);

    while (abs(total_acc - 1.) > 1e-6) {

        str_candidate = get_candidate(str_candidate, accuracy, num_chars);
        score_array(accuracy, str1_target, str_candidate, num_chars);
        total_acc = total_score(accuracy, num_chars);
        num_iterations += 1;

        if (num_iterations % 100 == 0) {
            cout << "Current guess: " << str_candidate << endl;
            cout << "Number of iterations: " << num_iterations << endl;
            cout << "Accuracy: " << total_acc << endl;
            bool tryout = (total_acc == 1);
            cout << tryout << endl;
        }
    }

    cout << "Final string: " << str_candidate << endl;
    cout << "  Total score: " << total_acc << endl;

    return num_iterations;
}


int main() {

    string str1_target;
    cout << "Enter string target (whitespace as '_'): " << endl;
    getline(cin, str1_target);
    cout << "Target string: >" << str1_target <<  "<" << endl;

    int num_iterations;
    // num_iterations = guess_full_string(str1_target);  // uses the function to discard any incorrect strings
    num_iterations = guess_individual_letter(str1_target);  // keeps correct letters in next guess

    cout << "Total iterations: " << num_iterations << endl;
	return 0;
}

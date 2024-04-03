#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>
using namespace std;

class Timer
{
public:
	chrono::time_point<chrono::steady_clock> start, end;
	chrono::duration<float> duration;


	Timer()
	{
		start = chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		end = chrono::high_resolution_clock::now();
		duration = end - start;

		float resultat = duration.count();
		cout << "You lefted time: " << resultat << "sec\n";
	}
};


class Shubenutzya {
public:
	struct Word {
		string WORD;

		Word(const string& word) : WORD{ word } {}
	};

	vector<Word> words;

	string descrypt(string& encrypt_word) {
		string decrypted_word = encrypt_word;
		for (char& c : decrypted_word) {

			if (isalpha(c)) {

				if (c == 'a' || c == 'A') {
					c += 25;
				}
				else {
					c--;
				}
			}
		}
		return decrypted_word;
	}
	Shubenutzya(const string& filename) {
		ifstream fin(filename);
		if (fin.is_open()) {
			string enscrypt_word;
			while (fin >> enscrypt_word) {
				words.push_back(Word(descrypt(enscrypt_word)));
			}
			fin.close();
		}
		else {
			throw runtime_error("Unable to open file\n");
		}
	}

	Word Random() {
		random_device rd;
		mt19937 gen(rd());
		shuffle(words.begin(), words.end(), gen);
		return words.front();
	}

	friend ostream& operator<< (ostream& out, const Shubenutzya::Word& s) {
		out << s.WORD;
		return out;
	}
};

void draw(int errors) {
	switch (errors) {
	case 0:
		cout << "  ________" << endl;
		cout << "  |       |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "__|__" << endl;
		break;
	case 1:
		cout << "  ________" << endl;
		cout << "  |       |" << endl;
		cout << "  |       O" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "__|__" << endl;
		break;
	case 2:
		cout << "  ________" << endl;
		cout << "  |       |" << endl;
		cout << "  |       O" << endl;
		cout << "  |       |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "__|__" << endl;
		break;
	case 3:
		cout << "  ________" << endl;
		cout << "  |       |" << endl;
		cout << "  |       O" << endl;
		cout << "  |      /|" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "__|__" << endl;
		break;
	case 4:
		cout << "  ________" << endl;
		cout << "  |       |" << endl;
		cout << "  |       O" << endl;
		cout << "  |      /|\\" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "__|__" << endl;
		break;
	case 5:
		cout << "  ________" << endl;
		cout << "  |       |" << endl;
		cout << "  |       O" << endl;
		cout << "  |      /|\\" << endl;
		cout << "  |      /" << endl;
		cout << "  |" << endl;
		cout << "__|__" << endl;
		break;
	case 6:
		cout << "  ________" << endl;
		cout << "  |       |" << endl;
		cout << "  |       O" << endl;
		cout << "  |      /|\\" << endl;
		cout << "  |      / \\" << endl;
		cout << "  |" << endl;
		cout << "__|__" << endl;
		break;
	}
}

int main() {
	setlocale(LC_ALL, "ukr");
	Timer timer;
	int count_attempt = 6;
	Shubenutzya shb("Shubenutzya.txt");
	Shubenutzya::Word word = shb.Random();
	string search_word = word.WORD;
	string guessed_word(search_word.size(), '_');

	int errors = 0;
	do
	{
		char guess;
		cin >> guess;
		bool found_letter = false;
		for (size_t i = 0; i < search_word.size(); i++)
		{
			if (search_word[i] == guess)
			{
				guessed_word[i] = guess;
				found_letter = true;
			}
		}
		if (!found_letter)
		{
			cout << "Sorry, but this letter uncorected\n";
			count_attempt--;
			errors++;
			draw(errors);
			cout << "Attempts left: " << count_attempt << endl;

		}

		if (guessed_word == search_word)
		{
			cout << "You win!" << endl;
			break;
		}


	} while (count_attempt > 0);

	if (count_attempt == 0)
	{
		cout << "Sorry, but you lose!";
		draw(errors);
	}

	cout << "Information: \n";
	cout << "Attempts left: " << count_attempt << endl;
	cout << "Searched word: " << search_word << endl;
	cout << "Your letters: " << guessed_word << endl;

}
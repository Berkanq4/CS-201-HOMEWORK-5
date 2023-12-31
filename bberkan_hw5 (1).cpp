#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Movie {
	string name;
	int year;
	string genre;
};


void sortMovies(vector<Movie>& movies) {
	int n = movies.size();
	bool swapped;
	for (int i = 0; i < n - 1; i++) {
		swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (movies[j].year < movies[j + 1].year) {

				swap(movies[j], movies[j + 1]);
				swapped = true;
			}
			else if (movies[j].year == movies[j + 1].year) {

				if (movies[j].name > movies[j + 1].name) {
					swap(movies[j], movies[j + 1]);
					swapped = true;
				}
			}
		}

		if (!swapped) {
			break;
		}
	}
}

string toLower(const string& str) {
	string lowerStr;


	for (char c : str) {

		if (c >= 'A' && c <= 'Z') {
			lowerStr += c + ('a' - 'A');
		}
		else {

			lowerStr += c;
		}
	}

	return lowerStr;
}
std::string capitalize_first_letters(std::string input) {
	bool is_first_letter = true;
	for (char& c : input) {
		if (is_first_letter && c >= 'a' && c <= 'z') {
			c = c - 'a' + 'A';
		}
		is_first_letter = c == ' ';
	}
	return input;
}


int main() {
	vector <Movie> movies;
	bool zues = true;
	int year_one, year_two;
	cout << "Welcome to the movie recommender program!" << endl;
	cout << endl;
	cout << "Please enter the movie list filename: ";
	string file_name;
	cin >> file_name;
	ifstream file(file_name);
	while (!file.is_open()) {
		cout << "Please check filename! Enter a correct movie list filename: ";
		cin >> file_name;
		file.open(file_name);
	}
	string movieList;
	while (getline(file, movieList)) {
		if (movieList.at(movieList.length() - 1) == '\r')
			movieList.pop_back();
		int total = 0;
		int count = 0;
		string s;
		istringstream input(s);
		string movie_name, movie_genre;
		int movie_year;
		string bos = "";

		int sondan_bosluk = movieList.rfind(" ");
		movie_genre = movieList.substr(sondan_bosluk + 1);
		movie_year = stoi(movieList.substr(sondan_bosluk - 4, 4));
		movie_name = movieList.substr(0, sondan_bosluk - 5);


		//int intofyear = stoi(movie_year);

		/*
		for (int i = 0; i < movieList.size(); i++) {

			if (isdigit(movieList[i])){
				string movie_name  = movieList.substr(0, i + 1);

			}
		}
		for (int i = i +1 ; i < movieList.size(); i++) {
			if (isalpha(movieList[i])) {
				int year_end = i-1;
				int movie_year = stoi(movieList.substr(i + 1, 4));
			}
		}
		for (int i = i + 5; i < movieList.size(); i++) {
			string movie_genre = movieList.substr(i + 5);
		}
		*/
		/*
		size_t nameEnd = movieList.find(';');
		string name = movieList.substr(0, nameEnd);
		size_t yearEnd = movieList.find(';', nameEnd + 1);
		int year = stoi(movieList.substr(nameEnd + 1, yearEnd - nameEnd - 1));
		string genre = movieList.substr(yearEnd + 1);
		*/
		movies.push_back({ movie_name,movie_year,movie_genre });

	}
	/*
	for (const auto& x : movies) {
		cout << x.name << " " << x.year << " " << x.genre << endl;
	}
	*/

	sortMovies(movies);

	while (true) {
		if (zues) {
			cout << "Please select your action:" << endl;
			cout << "1. Select the genre of the movie that you want to watch" << endl;
			cout << "2. Select the year of the movie that you want to watch" << endl;
			cout << "3. Exit program" << endl;
			cout << endl;
			zues = false;
		}

		cout << "Enter your choice: ";
		int choice;
		cin >> choice;

		if (choice == 1) {

			cout << "Please enter the genre of the movie you want to watch: ";
			string genre;
			cin >> genre;
			string loweredgen = toLower(genre);
			string capital_gen = capitalize_first_letters(loweredgen);
			cout << endl;
			bool found = false;
			bool girdi = false;
			for (const auto& movie : movies) {
				

				if (capital_gen.compare(movie.genre) == 0) {
					if (!girdi) {
						girdi = true;
						cout << genre << " movies from newest to oldest:" << endl;
					}
					found = true;
					cout << "Movie name: " << movie.name << " Release Year: " << movie.year << endl;
				}

			}
			if (!found) {
				cout << "There are no " << genre << " movies!" << endl;
			}
			cout << endl;

		}

		else if (choice == 2) {
			bool girdi1 = false;
			bool girdi2 = false;
			cout << "Please enter the year of the movie you want to watch: ";
			string year;
			cin >> year;
			int count = 0;
			bool second_year = false;
			/*
			while (input >> year) {
				count++;
				if (count == 1)
					year_one = year;
				else if (count == 2) {
					year_two = year;
				}
			}
			*/
			if (year.find('-') != -1) {
				second_year = true;
			}
			//bool year2 = true;
			/*
			string number_asstring = to_string(year);
			if (number_asstring.size() > 4) {
				year2 = true;
			}
			else {
				year2 = false;
			}
			*/
			bool found = false;
			if (!second_year) {
				for (const auto& movie : movies) {
					if (movie.year == stoi(year)) {
						if (!girdi1) {
							girdi1 = true;
							cout << "Movies released in " << year << " from A to Z:" << endl;
						}
						found = true;
						cout << "Movie name: " << movie.name << " Genre: " << movie.genre << endl;
					}
				}
				if (!found) {
					cout << "There are no movies released in " << year << "!" << endl;
				}
			}
			else if (second_year) {
				for (const auto& movie : movies) {
					if (movie.year >= stoi(year.substr(0, 4)) && movie.year <= stoi(year.substr(5))) {
						if (!girdi2) {
							girdi2 = true;
							cout << "Movies released between the years " << year.substr(0, 4) << '-' << year.substr(5) << " from A to Z with decreasing year ordering:" << endl;
						}
						found = true;
						
						cout << "Movie name: " << movie.name << " Release Year: " << movie.year << " Genre: " << movie.genre << endl;
					}
				}
				if (!found) {
					cout << "There are no movies released between " << year.substr(0, 4) << " " << year.substr(5) << endl;
				}

			}
			cout << endl;
		}

		else if (choice == 3) {
			cout << "Thank you..." << endl;
			break;
		}

		else {
			cout << "Invalid action!" << endl;
			cout << endl;
		}


		

		
	}
	return 0;
}
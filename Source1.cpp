#include <iostream>
#include <string>
#include <limits> // for std::numeric_limits
#include <fstream>

int authentication = 0;
char username[10];
char password[10];

template <typename T>
T get_input(const std::string &strQuery);

std::string get_username();
std::string get_password();
void save_user(const std::string &username, const std::string &password);

void login();
void register_user();
void main_menu();

int main() {
	main_menu();
}

template <typename T>
T get_input(const std::string &strQuery) {
	std::cout << strQuery << "\n> ";
	T out = T();
	while (!(std::cin >> out)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
		std::cout << "Error!" "\n";
		std::cout << strQuery << "\n";
	}
	return out;
}

void writeToFile(std::string username) {
	std::ofstream writefile;
	std::string file = username + ".txt";
	writefile.open(file.c_str());
	writefile << password;
	writefile.close();
	main_menu();
}

void login() {
	std::cout << "Loginning in... Please wait..." "\n";
	std::cout << "Username: ";
	std::cin >> username;
	std::cout << "Password: ";
	std::cin >> password;

	if (std::strcmp(username, "admin") == 0 && std::strcmp(password, "adminpass") == 0) {
		authentication = 1;
	}
	if (authentication) {
		std::cout << "access granted\n";
		std::cout << (char)authentication;
	}
	else {
		std::cout << "Wrong username and password\n";
	}
}

void registerPassword() {
	std::cout << "Please enter password:" << "\n";
	std::cin >> password;
	std::cout << "Please renter your password:" << "\n";
	std::cin >> password2;
	if (password == password2) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		writeToFile(username);
		exit(1);
	}
	else {
		std::cout << "Passwords do not match. Please re-enter your password." << "\n";
		registerPassword();
	}
}

void register_user() {
	std::string username = get_username();
	std::string password = get_password();
	save_user(username, password);
}

std::string get_username() {
	std::string username = get_input <std::string>("Please enter a username.");
	std::cout << "Username: \"" << username << "\"\n";

	while (get_input <int>("Confirm? [0|1]") != 1) {
		username = get_input <std::string>("Please enter a username.");
		std::cout << "Username: \"" << username << "\"\n";
	}

	return username;
}

std::string get_password() {
	std::string password1 = get_input <std::string>("Please enter your password.");
	std::string password2 = get_input <std::string>("Please re-enter your password.");

	while (password1 != password2) {
		std::cout << "Error! Passwords do not match." "\n";
		password1 = get_input <std::string>("Please enter your password.");
		password2 = get_input <std::string>("Please re0enter your password.");
	}

	return password1;
}

void save_user(const std::string &username, const std::string &password) {
	std::string filename = username + ".txt";
	std::ofstream file(filename);
	file << password << "\n";
}

void main_menu() {
	int choice = get_input <int>(
		"Hello! Would you like to log in or register?" "\n"
		"[1] Login" "\n"
		"[2] Register" "\n"
		"[3] Exit");

	switch (choice) {
	case 1:
		login();
		break;
	case 2:
		register_user();
		break;
	}
}
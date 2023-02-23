#include <winbase.h>
#include <winnt.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

/**
 * Считываем содержимое файла через винапи в строку.
 * В случае ошибки процесс останавливаем и пишем в консоль.
 */
void read(const std::string & fileName, std::string & fileData) {
	HANDLE hd = 0;
	unsigned long size = 0;

	// Открываем файл на чтение
	hd = CreateFileA(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hd == INVALID_HANDLE_VALUE) {
		std::cout << "Error while opening file to read!\n";
		exit(-1);
	}

	// узнаем размер
	size = GetFileSize(hd, &size);
	if (size == INVALID_FILE_SIZE) {
		std::cout << "Error while checking file size!\n";
		exit(-1);
	}

	// читаем данные из файла.
	char * dest = (char*) calloc(size, sizeof(char));
	unsigned long justRead = 0;
	char * cur = dest;

	// цикл нужен на случай, если файл большой и придется читать частями
	while (cur != dest + size) {
		int res = ReadFile(hd, cur, dest + size - cur, &justRead, NULL);

		if (res == 0) {
			std::cout << "Problem while reading from file\n";
			exit(-1);
		}

		cur += justRead;
	}

	// закрываем файл
	CloseHandle(hd);

	// создаем строку
	fileData = dest;

	// чистим память
	free(dest);
}

bool isDelim(char c) {
	return c == ' ' || c == '\n';
}

/**
 * Токенизируем строку, используя разделители.
 * Токены лежат в обратном порядке.
 */
void tokenize(const std::string & s, std::vector<std::string> & result) {
	int end = s.length()+1;
	// пробегаемся по строке, собираем в процессе токены
	for (int i = s.length() - 1; i >= 0; i--) {
		char c = s[i];
		if (isDelim(c)) {
			int start = i+1;
			if (start != end) {
				result.push_back(s.substr(start, end-start-1));
			}
			end = start;
		}
	}
	if (end > 0) {
		result.push_back(s.substr(0, end-1));
	}
}

/**
 * Записываем вектор из токенов в файл. Токены разделены пробелами. В конце тоже пробел.
 * В случае ошибки процесс останавливаем и пишем в консоль.
 */
void write(const std::vector<std::string> & tokens, const std::string & fileName) {
	HANDLE hd = 0;

	// открываем файл на запись
	hd = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hd == INVALID_HANDLE_VALUE) {
		std::cout << "Error while opening file to write!\n";
		exit(-1);
	}

	// записываем все токены
	for (auto t : tokens) {
		t += " ";// добавляем пробел
		const char * token = t.c_str();

		const char * cur = token;
		int total = t.length();
		unsigned long justWritten = 0;

		// записываем полностью
		while (cur != token + total) {
			int res = WriteFile(hd, token, token + total - cur, &justWritten, NULL);

			if (res == 0) {
				std::cout << "Problem while writing to file\n";
				exit(-1);
			}

			cur += justWritten;
		}
	}

	// закрываем файл
	CloseHandle(hd);
}

/**
 * Копируем сожержимое одного в другой. При этом реверсируем порядок слов
 */
void copy(const std::string & inFileName, const std::string & outFileName) {
	std::string fileData;
	std::vector<std::string> tokens;

	read(inFileName, fileData);
	tokenize(fileData, tokens);
	write(tokens, outFileName);
}

int main() {
	std::string inFileName = "test.txt";
	std::string outFileName = "out.txt";

	std::cin >> inFileName >> outFileName;

	copy(inFileName, outFileName);

	return 0;
}

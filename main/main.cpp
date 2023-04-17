#define SIZE 10
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
FILE* fptr = NULL;
void menu() {
	printf("0. Zakoncz program \n");
	printf("1. Wstaw element \n");
	printf("2. Usun element \n");
	printf("3. Wyswietl kolekcje \n");
	printf("4. Zapisz kolekcje do pliku \n");
	printf("5. Przywroc kolekcje z pliku \n");

}
void clearCMD() {
	system("cls");
}

void result(int returnedValue) {
	if (returnedValue == 0) {
		printf("Pomyslnie wykonano akcje \n");
	}
	else if (returnedValue == 1) {
		printf("Nie udalo sie wstawic wartosci. Kolekcja jest pelna.\n");
	}
	else if (returnedValue == 2) {
		printf("Nie mozna wykonac akcji. Kolekcja jest pusta \n");
	}
	else if (returnedValue == 3) {
		printf("Nie zapisano twojej kolekcji, poniewaz jest ona pusta \n");
	}
	else if (returnedValue == 4) {
		printf("Nie udalo sie uzyskac dostepu do pliku \n");
	}
	else if (returnedValue == 5) {
		printf("Nie udalo sie usunac wartosci. Ten element nie istnieje \n");
	}
	else {
		printf("Wystapil nieznany blad");
	}
}

int insertIntoCollection(int value, int* index, int* array) {
	if (*index < SIZE) {
		*(array + *index) = value;
		*index = (*index) + 1;
		return 0;
	}
	else {
		return 1;
	}

}
int getValue() {
	int value = 0;
	printf("Podaj liczbe ktora chcesz wstawic do kolekcji \n");
	if (scanf("%d", &value) < 1) {
		exit(1);
	}
	return value;

}

void showCollection(int* index, int* array) {
	if (*index > 0) {
		printf("Twoje wartosci w kolekcji to: \n");
	}
	else {
		printf("Twoja kolekcja nie posiada zadnych elementow \n");
	}

	for (int i = 0; i < *index; i++) {
		printf("Wartosc %d => %d \n", i + 1, *(array + i));
	}
}
int deleteFromCollection(int* index, int* array) {
	if (*index > 0) {
		int value = 0;
		printf("Twoja kolekcja ma %d elementow \n", *index);
		printf("Ktory element chcesz usunac? \n");
		if (scanf("%d", &value) < 1) {
			exit(1);
		};
		if (value <= *index)
		{
			*index = *index - 1;
			for (int i = 0; i < SIZE - value; i++) {
				*(array + value - 1 + i) = *(array + value + i);
			}
			*(array + SIZE - 1) = NULL;
			return 0;
		}
		else {
			return 5;
		}
	}
	else {
		return 2;
	}
}

int saveInFile(int* index, int* array) {
	if (*index > 0) {
		fptr = fopen("collection.txt", "w");
		if (!fptr) return 4;
		fprintf(fptr, "%d", *array);
		for (int i = 1; i < *index; i++) {
			fprintf(fptr, "\n%d", *(array + i));
		}

		fclose(fptr);
		return 0;
	}
	else {
		return 3;
	}
}
int recoverFromFile(int* index, int* array) {
	int number;
	fptr = fopen("collection.txt", "r");
	if (!fptr) return 4;
	*index = 0;
	while (!feof(fptr))
	{
		fscanf(fptr, "%d", &number);
		*(array + *index) = number;
		*index = *index + 1;
	}

	fclose(fptr);
	return 0;

}
int main()
{
	int myArray[SIZE];
	int* array = myArray;
	int option = 0;
	int index = 0;

	do {
		menu();
		if (scanf("%d", &option) < 1) {
			exit(1);
		}
		clearCMD();
		switch (option) {
		case 0:
			clearCMD();
			printf("Zakonczyles program \n");
			return 0;
		case 1:
			clearCMD();
			result(insertIntoCollection(getValue(), &index, array));
			break;
		case 2:
			clearCMD();
			result(deleteFromCollection(&index, array));
			break;
		case 3:
			clearCMD();
			showCollection(&index, array);
			break;
		case 4:
			clearCMD();
			result(saveInFile(&index, array));
			break;
		case 5:
			clearCMD();
			result(recoverFromFile(&index, array));
			break;

		}


	} while (option != 0);
}

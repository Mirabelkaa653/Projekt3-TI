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
	switch (returnedValue) {
	case 0:
		printf("Pomyslnie wykonano akcje \n");
		break;
	case 1:
		printf("Nie udalo sie wstawic wartosci. Kolekcja jest pelna.\n");
		break;
	case 2:
		printf("Nie mozna wykonac akcji. Kolekcja jest pusta \n");
		break;
	case 3:
		printf("Nie zapisano twojej kolekcji, poniewaz jest ona pusta \n");
		break;
	case 4:
		printf("Nie udalo sie uzyskac dostepu do pliku \n");
		break;
	case 5:
		printf("Nie udalo sie usunac wartosci. Ten element nie istnieje \n");
		break;
	case 6:
		printf("Twoja kolekcja nie posiada zadnych elementow \n");
		break;
	default:
		printf("Wystapil nieznany blad");
		break;
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

int insertIntoCollection(int value, int* index, int* ary) {
	if (*index < SIZE) {
		ary[*index] = value;
		*index = (*index) + 1;
		return 0;
	}
	return 1;
}

int showCollection(int* index, int* ary) {
	if (*index > 0) {
		printf("Twoje wartosci w kolekcji to: \n");
	}
	else {
		return 6;
	}

	for (int i = 0; i < *index; i++) {
		printf("Wartosc %d => %d \n", i + 1, *(ary + i));
	}
	return 0;
}

int deleteFromCollection(int* length, int* ary) {
	if (*length > 0) {
		int index = 0;

		printf("Twoja kolekcja ma %d elementow \n", *length);
		printf("Ktory element chcesz usunac? \n");

		if (scanf("%d", &index) < 1) {
			exit(1);
		}
		if (index <= *length)
		{
			*length = *length - 1;
			for (int i = 0; i < SIZE - index; i++) {
				ary[index - 1 + i] = ary[index + i];
			}
			*(ary + SIZE - 1) = NULL;
			return 0;
		}
		return 5;
	}
	return 2;
}

int saveInFile(int* index, int* ary) {
	if (*index > 0) {
		fptr = fopen("collection.txt", "w");

		if (!fptr) return 4;

		fprintf(fptr, "%d", *ary);

		for (int i = 1; i < *index; i++) {
			fprintf(fptr, "\n%d", *(ary + i));
		}
		fclose(fptr);
		return 0;
	}
	return 3;
}

int recoverFromFile(int* index, int* ary) {
	int number;

	fptr = fopen("collection.txt", "r");

	if (!fptr) return 4;
	*index = 0;
	while (!feof(fptr))
	{
		fscanf(fptr, "%d", &number);
		*(ary + *index) = number;
		*index = *index + 1;
	}
	fclose(fptr);
	return 0;
}

int main()
{
	int myAry[SIZE];
	int* ary = myAry;
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
			printf("Zakonczyles program \n");
			return 0;
		case 1:
			result(insertIntoCollection(getValue(), &index, ary));
			break;
		case 2:
			result(deleteFromCollection(&index, ary));
			break;
		case 3:
			result(showCollection(&index, ary));
			break;
		case 4:
			result(saveInFile(&index, ary));
			break;
		case 5:
			result(recoverFromFile(&index, ary));
			break;
		}
	} while (option != 0);
}

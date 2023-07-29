#include "stdafx.h"
#include "sqlite3.h"
#include "stdio.h"

using namespace std;

static int callback(void *notused, int coln, char **rows, char **colnm)
{

	int i;
	static int b = 1;
	// печать названий столбцов
	if (b) // печатать только один раз 
	{
		for (i = 0; i<coln; i++)
			printf("  %s      \t", colnm[i]);
		printf("\n");
		b = 0;
	}
	// печать разделителя строк
	for (i = 0; i<coln; i++)
		printf("---------\t");
	printf("\n");
	//печать значений
	for (i = 0; i<coln; i++)
		printf("   %s\t    |", rows[i]);
	printf("\n");

	return 0;
}

int _tmain(int argc, char* argv[])


{
	sqlite3 *db;
	char *zErrMsg = 0;
	char str[50];
	int error, a, NN, id1, id2;
	char sqlText[200];

	// Открытие БД
	error = sqlite3_open("library1.db", &db);

	if (error) {

		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}


	error = sqlite3_exec(db, "CREATE TABLE author (id INTEGER PRIMARY KEY AUTOINCREMENT,NAMEauthor VARCHAR(50));", callback, 0, &zErrMsg);
	if (error)
	{

		fprintf(stderr, "Can't create tables1: %s\n", sqlite3_errmsg(db));

	}
	//Создание таблицы 1
	error = sqlite3_exec(db, "CREATE TABLE book (id INTEGER PRIMARY KEY AUTOINCREMENT,NAMEbook VARCHAR(50),id_author INTEGER(10), FOREIGN KEY (id_author) REFERENCES author (id));", callback, 0, &zErrMsg);
	if (error)
	{

		fprintf(stderr, "Can't create tables2: %s\n", sqlite3_errmsg(db));

	}




	//Создание таблицы 3
	error = sqlite3_exec(db, "CREATE TABLE visitor (id INTEGER PRIMARY KEY AUTOINCREMENT,NAMEvisitor VARCHAR(50));", callback, 0, &zErrMsg);
	if (error)
	{

		fprintf(stderr, "Can't create tables3: %s\n", sqlite3_errmsg(db));

	}

	//Создание таблицы 4
	error = sqlite3_exec(db, "CREATE TABLE bookvisitor (id INTEGER PRIMARY KEY AUTOINCREMENT,id_book INTEGER(10),id_visitor INTEGER(10),return_a_book VARCAR(5),FOREIGN KEY(id_book) REFERENCES book(id),FOREIGN KEY(id_visitor) REFERENCES visitor(id));", callback, 0, &zErrMsg);
	if (error)
	{

		fprintf(stderr, "Can't create tables4: %s\n", sqlite3_errmsg(db));

	}
	NN = 1;
	do
	{
		printf(" change table book:          1 \n change table author:        2 \n change table visitor:       3 \n change table bookvisitor:   4 \n");
		printf(" view table book:            5 \n viev table author:          6 \n viev table visitor:         7 \n viev table bookvisitor:     8 \n");
		printf("all the books and authors:   9 \n debtors books:              10 \n DELETE debtors:            11 \n");
		printf("Select an action: \n");
		scanf_s("%i", &a);
		switch (a) {
		case 1:
			printf("Insert NAMEBOOK and id_autor \n");
			scanf_s("%s%i", &str, 50, &id1);
			sprintf_s(sqlText, "INSERT INTO book (NAMEbook,id_author) VALUES ('%s','%i');", str, id1);
			error = sqlite3_exec(db, sqlText, callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't insert tables1: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 2:
			printf("Insert NAMEauthor\n");
			scanf_s("%s", &str, 50);
			sprintf_s(sqlText, "INSERT INTO author (NAMEauthor) VALUES ('%s');", str);
			error = sqlite3_exec(db, sqlText, callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't insert tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 3:
			printf("Insert NAMEvisitor\n");
			scanf_s("%s", &str, 50);
			sprintf_s(sqlText, "INSERT INTO visitor (NAMEvisitor) VALUES ('%s');", str);
			error = sqlite3_exec(db, sqlText, callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't insert tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 4:
			printf("insert id_dook and id_visitor\n");
			scanf_s("%i%i", &id2, &id1);
			sprintf_s(sqlText, "INSERT INTO bookvisitor (id_book,id_visitor) VALUES ('%i','%i');", id2, id1);
			error = sqlite3_exec(db, sqlText, callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't insert tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 5:
			error = sqlite3_exec(db, "SELECT * FROM book;", callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't select tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 6:
			error = sqlite3_exec(db, "SELECT * FROM author;", callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't select tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 7:
			error = sqlite3_exec(db, "SELECT * FROM visitor;", callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't select tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 8:
			error = sqlite3_exec(db, "SELECT * FROM bookvisitor;", callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't select tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 9:
			error = sqlite3_exec(db, "SELECT book.NAMEbook, author.NAMEauthor FROM book LEFT OUTER JOIN author ON book.id_author=author.id;", callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't select tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 10:
			error = sqlite3_exec(db, "SELECT bookvisitor.id_book,visitor.NAMEvisitor FROM bookvisitor, visitor WHERE bookvisitor.id_visitor=visitor.id;", callback, 0, &zErrMsg);
			if (error)
			{
				fprintf(stderr, "Can't select tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 11:
			printf("insert id_dook and id_visitor\n");
			scanf_s("%i%i", &id2, &id1);
			sprintf_s(sqlText, "DELETE FROM bookvisitor WHERE id_book='%i' and id_visitor='%i';", id2, id1);
			error = sqlite3_exec(db, sqlText, callback, 0, &zErrMsg);

			if (error)
			{
				fprintf(stderr, "Can't select tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		case 12:
			printf("insert  id_author\n");
			scanf_s("%i", &id1);
			sprintf_s(sqlText, "SELECT id_autor FROM NAMEbook WHERE id='%i' ;", id1);
			error = sqlite3_exec(db, sqlText, callback, 0, &zErrMsg);

			if (error)
			{
				fprintf(stderr, "Can't select tables: %s\n", sqlite3_errmsg(db));
			}
			break;
		default: printf("invalid input: \n");
		}

		printf("continue or not(1 or 0): \n");
		scanf_s("%i", &NN);

	} while (NN != 0);
	sqlite3_close(db);

	getchar();

	return 0;
}
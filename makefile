# makefile for producing main.out

CC = gcc
FLAGS = -Wall -Werror -ansi

main.out: encrypt.c menu.c menu_import.c menu_patient.c linkedlist.c login.c main.c
	$(CC) $(FLAGS) -o main.out encrypt.c menu.c menu_import.c menu_patient.c linkedlist.c login.c main.c -lm

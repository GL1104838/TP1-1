/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   main.c
* Author: Gabriel
*
* Created on 4 octobre 2016, 22:16
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//struct variable { char lettre; int valeur; };
/*utilisable doit etre entre 0 et 1 et est initialisee a 0. Elle devient 1
* lorsque la variable est utilisable.*/

/*
* Procedure principale
*/
struct stackElement{ char valeur; struct stackElement* next; };
struct stack{ struct stackElement* top; };

void push(struct stack* stk, char element){
	//Ajoute un stackElement sur le top du stack stk
	struct stackElement* current;
	current = malloc(sizeof(struct stackElement));
	current->valeur = element;

	if (stk->top == NULL){
		// S'éxecute lorsque la pile est vide
		stk->top = current;
		stk->top->next = NULL; //initialise le next à NULL
	}
	else{
		// S'éxecute lorsque la pile n'est pas vide
		current->next = stk->top;
		stk->top = current;
	}
}

char pop(struct stack* stk){
	//Retire l'élément au top de la pile et retourne sa valeur
	if (stk->top == NULL){
		// Attrape l'exception lorsque la pile est vide
		printf("Erreur! Pile Vide.\n");
	}
	else{
		// S'exécute lorsque la pile n'est pas vide
		char c;
		struct stackElement* current;
		current = malloc(sizeof(struct stackElement));
		current = stk->top;
		c = current->valeur;
		stk->top = stk->top->next;
		free(current); // libère l'espace mémoire

		return c;
	}
}

struct stack* reverse(struct stack* stk1){
	//Renverse les éléments de la pile
	//Doit obligatoirement être appelé sous forme [stk = reverse(stk)] puisque la pile initiale est vidée.
	if (stk1->top != NULL){
		//Si la pile n'est pas vide
		struct stack* stk2;
		stk2 = malloc(sizeof(struct stack));
		stk2->top = NULL;
		while (stk1->top != NULL){
			push(stk2, pop(stk1));
		}
		return stk2;
	}
	else{
		//Si la pile est vide
		printf("Erreur! Pile Vide non renversible puisque vide.\n");
	}
}

void addition(struct stack* stk, struct stack* stk1, struct stack* stk2){
	//Méthode permettant l'addition de deux nombres

	//Initialisation des variables
	int a; // Nombre 1
	int b; // Nombre 2
	int keepOne; // Combien doit-on ajouter au prochain calcul
	
	//Initialisation du nombre d'ajout au prochain calcul à 0
	keepOne = 0;

	while (stk1->top != NULL && stk2->top != NULL){
		/*Additionne les unités avec les unités, dizaines avec les dizaines etc afin
			d'obtenir une précision infinie.*/
		if (stk1->top == NULL) {
			/*Transforme a en 0 pour le calcul puisque le nombre 1
				ne possède pas de chiffre dans cette colonne.*/
			a = 0;
		}
		else{
			//Donne à a la valeur du top de la pile du nombre1
			a = pop(stk1) - '0';
			printf("a = %d\n", a);
		}
		if (stk2->top == NULL){
			/*Transforme b en 0 pour le calcul puisque le nombre 2
				ne possède pas de chiffre dans cette colonne.*/
			b = 0;
		}
		else{
			//Donne à b la valeur du top de la pile du nombre2
			b = pop(stk2) - '0';
			printf("b = %d\n", b);
		}
		if (keepOne == 1){
			//Incrémente a si le calcul précédent était supérieur ou égal à 10
			a++;
			keepOne = 0;
		}
		if (a + b >= 10){
			//Garde 1 pour le prochain calcul si a+b est >= à 10 et donne les unités du résultat à stk3
			keepOne = 1;
			push(stk, (a + b) - 10);
		}
		else{
			//Donne la valeur de a+b à stk3
			push(stk, a + b);
		}
	}
}

int main(int argc, char** argv)
{
	//Initialisation du stack
	struct stack *stk;
	stk = malloc(sizeof(struct stack));
	stk->top = NULL; //Initialise le top à null. Important de garder.

	//Affichage initial sur la console
	printf("> ");
	fflush(stdout);
	
	//Lecture du input de l'utilisateur et remplissage du stack
	char c = getchar();
	while (c != '\n'){
		push(stk, c);
		c = getchar();
	}
	//Reversion du stack
	stk = reverse(stk);

	//Initialisation des stack des nombres à évaluer
	struct stack *stk1;
	stk1 = malloc(sizeof(struct stack));
	stk1->top = NULL;
	struct stack *stk2;
	stk2 = malloc(sizeof(struct stack));
	stk2->top = NULL;

	//Rempli la pile stk1 avec le premier nombre
	while (stk->top->valeur != ' '){
		/*@TODO: Include exceptions si y'a pas de ' ' avant le EOF et
			vérifier que seulement des chiffres ou des variables sont acceptés. */
		push(stk1, pop(stk));
	}
	pop(stk); //Retire le ' ' de la pile
	//Rempli la pile stk2 avec le deuxième nombre
	while (stk->top->valeur != ' '){
		/*@TODO: Include exceptions si y'a pas de ' ' avant le EOF et
		vérifier que seulement des chiffres ou des variables sont acceptés. */
		if (stk->top->valeur == '='){
			printf("$$$ money shot $$$");
		}
		push(stk2, pop(stk));
	}
	pop(stk); // Retire le ' ' de la pile

	//Prend le symbole d'opération
	char operateur = pop(stk);

	switch (operateur){
		case('+') :
			printf("dingleberries");
			addition(stk, stk1, stk2);
			break;
		default:
			printf("bumbleberries");
			break;
	}

	getchar(); //Uniquement pour afficher la console
}

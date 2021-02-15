#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//declaretion des constants
#define CANDIDATS_MAX 1000
#define CANDIDATS_MIN 3
#define VOTERS_MAX 100000
#define VOTERS_MIN 4
//declaretion des variables globales
char candidats[CANDIDATS_MAX][64];
char voters[VOTERS_MAX][64];
int candidats_results[CANDIDATS_MAX];
int voters_count, candidats_count, excluded_count;
char qualified[CANDIDATS_MAX][64];
int	qualified_results[CANDIDATS_MAX];
int qualified_count = 0;
//cette fonction permet de trouver l'element minimum d'un tableau
int min_array(int array[], int length) {
	
	int min = array[0];

	for(int i=1; i<length; i++) {
		if( min > array[i])
			min = array[i];
	}
	return min;
}
//cette fonction permet de trouver l'element maximum d'un tableau
int max_array(int array[], int length) {
	int max = array[0];

	for(int i=1; i<length; i++) {
		if( max < array[i])
			max = array[i];
	}
	return max;
}
//cette function permet de reinitialiser un tableau
void init_array(int array[],int size,int value)
{

	for (int i = 0 ; i < size ;i++ )
	{
		array[i] = value;
	}
}
//cette function permet de remplir la table (candidats)
void get_candidats()
{	
	printf("\tENTREE DES CANDIDATS: \n");
	for(int i = 0 ; i < candidats_count ; i++)
	{
			printf("veuillez entrer le nom du candidat %d: ",i);
			scanf("%s",candidats[i]);


}
//cette function permet de remplir la table (voters)
void get_voters()
{
	printf("\tENTREE DES ELECTEURS: \n");
	for(int i = 0 ; i < voters_count ; i++)
	{
			printf("entrer CIN no. %d: ",i);
			scanf("%s",voters[i]);

	}
}
//cette function permet d'ifficher les candidats
void show_condidats()
{
		for(int i = 0 ; i < candidats_count ; i++)
	{
			printf("candidat no. %d : %s\n",i, candidats[i]);
	}
}
//cette function permet de tester si tout les candidats on le meme nombre de votes
int check_equality()
{
	int value = candidats_results[0];
	for(int i = 0 ; i < candidats_count ; i++)
	{
		if(candidats_results[i] != value)
		{
			return 0;
		}
	}
	return 1;
}
//cette function permet d'ifficher les candidats et leurs poursantage
void show_vote()
{
	for(int i = 0 ; i < candidats_count ; i++)
	{
		printf("le candidat  %s a %d votes (%.2f %%)\n",candidats[i], candidats_results[i], (float)candidats_results[i]/voters_count * 100);
	}
}
//cette foction ramplis la table de vote candidats_results
//aussi elle rerifie si l'electeur a choisis un candidats qui n'existe pas 
//aussi elle verifie si touts les candidats on le meme nombre de votes
void get_vote()
{
	int vote;
	int equality;
	
	show_condidats();
	
	do
	{
		init_array(candidats_results,candidats_count,0);
		for (int i = 0 ; i < voters_count ; i++)
		{
			do{
				printf("cher(e) electeur %s choisisserez votre candidat: ",voters[i]);
				scanf("%d",&vote);

			}while(vote >=candidats_count);
			candidats_results[vote]++;
		}
		equality = check_equality(candidats_results);
		if(equality)
		{
			
			printf("touts les candidats ont le meme nombre de votes !\n");
			printf("le tour doit etre refait\n");
			printf("**************************************************\n");
			show_condidats();
		}
		
	}while(equality);
}
//cette fonction exclu un ou plusieurs candidats qui on le meme nombre de votes moins de 15%
void exclude_phase_1() {
	float percent;
	for(int i=0; i<candidats_count; i++) {
		percent = (float)candidats_results[i]/(float)voters_count*100;
		if(percent > 15) {
			strcpy(qualified[qualified_count],candidats[i]);
			qualified_count++;
		}
	}
}
//cette fonction exclu un ou plusieurs candidats qui on le meme nombre de votes monimum
void exclude_phase_2() {

	int min = min_array(candidats_results,candidats_count);

	for(int i=0; i<candidats_count; i++) {
		if(candidats_results[i] > min) {
			strcpy(qualified[qualified_count],candidats[i]);
			qualified_count++;
		}
	}
}
// cette fonction permet d'afficher les quandidats qualifie
void show_qualified() {
	
	printf("les candidats qualifie: \n\n");
	for(int i = 0 ; i < qualified_count ; i++)
	{
			printf("%s\n",qualified[i]);
	}
}
// cette fonction permet de copier les candidats qualifie dans la table (candidats) 
// et initialise la table (qualified) et aussi sa taille
void phase_transition() {

	candidats_count = qualified_count;
	for(int i = 0 ; i < qualified_count ; i++)
	{
	
			strcpy(candidats[i], qualified[i]);
			strcpy(qualified[i], "");
	}
	qualified_count = 0;
}

void elect_president() {

	int count, elected, max_result;

	do {
		//appelle au fonction pour remplir et afficher les votes 
		get_vote();
		show_vote();
		//initialization du conteur pour eviter un problem d'affichage
		count = 0;
		//sauvgarder le nombre maximal du table resultats dans max_result
		//on va l'utiliser pour trouver si 2 candidats au plus ont le meme nombre de vote maximal
		max_result = max_array(candidats_results,candidats_count);
		for(int i=0; i<candidats_count; i++) {
			if(candidats_results[i] == max_result) {
				elected = i;
				count++;
			}
		}
		printf("**************************************************\n");
		printf("\nnombre de candidats ayant le maximum de votes : %d\n", count);
		printf("nombre de votes naximal : %d\n", max_result);
	}while(count>1);

	printf("President elu : %s\n", candidats[elected]);
}


int main() {
	
	printf("\n\tBIENVENU\n");
	printf("**************************************************\n");
	do
	{
		printf("donner le nombre de candidats : ");
		scanf("%d",&candidats_count);

	}while(candidats_count < CANDIDATS_MIN);
	
	
	do
	{
		printf("donner le nombre d'electeurs : ");
		scanf("%d",&voters_count);

	}while(voters_count < VOTERS_MIN);
	
	
	get_candidats();
	printf("**************************************************\n");
	get_voters();

	printf("\n\tPremier tour d'elections\n");
	printf("**************************************************\n");
	get_vote();
	printf("**************************************************\n");
	show_vote();
	printf("**************************************************\n");
	exclude_phase_1();
	show_qualified();
	if(qualified_count == 1){
		printf("\n\tPresident elu: %s\n", qualified[0]);
		return 0;
	}

	phase_transition();
	
	printf("\n\tDeuxieme tour d'elections\n");
	printf("**************************************************\n");
	get_vote();
	printf("**************************************************\n");
	show_vote();
	printf("**************************************************\n");
	exclude_phase_2();
	show_qualified();
	if(qualified_count == 1){
		printf("President elu: %s\n", qualified[0]);
		return 0;
	}

	phase_transition();

	printf("\n\tTroisieme tour d'elections\n");
	printf("**************************************************\n");
	elect_president();

	return 0;
}
}


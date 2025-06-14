#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct supplement {
	char* firma;
	double raw_material;
	double payment;
} SUPPLEMENT;

void mem_alloc(SUPPLEMENT** supplements, int* sup_vol) {
	supplements[*sup_vol] = (SUPPLEMENT*)malloc(sizeof(SUPPLEMENT));
	(supplements[*sup_vol]->firma) = (char*)malloc(9 * sizeof(char));
}

void add_sup(SUPPLEMENT** supplements, int* sup_vol) {
	mem_alloc(supplements, sup_vol);
	printf("Supplier: ");
	scanf_s("%s", supplements[*sup_vol]->firma, 9);
	printf("\n");
	printf("Material volume: ");
	scanf_s("%lf", &(supplements[*sup_vol]->raw_material));
	printf("\n");
	printf("Cost: ");
	scanf_s("%lf", &(supplements[*sup_vol]->payment));
	printf("\n");
	(*sup_vol)++;
}

void remove_sup(SUPPLEMENT** supplements, int* sup_vol) {
	int cur_sup = 0, matching_sup = 0, needed_sup = 0, matching_sup_vol = 0;
	SUPPLEMENT** matching_supplements = (SUPPLEMENT**)malloc(sizeof(SUPPLEMENT*));
	SUPPLEMENT* cur_sup_buffer = (SUPPLEMENT*)calloc(1, sizeof(SUPPLEMENT));
	cur_sup_buffer->firma = (char*)calloc(1, sizeof(char));
	char* var = (char*)malloc(9);
	printf("Supplier or Material volume or Cost: ");
	scanf_s("%s", var, 9);
	printf("\n");
	printf("          Supplier        Material volume        Cost\n\n");
	while (cur_sup < *sup_vol) {
		if (strcmp(supplements[cur_sup]->firma, var) == 0 || supplements[cur_sup]->raw_material == strtod(var, NULL) || supplements[cur_sup]->payment == strtod(var, NULL)) {
			matching_supplements = (SUPPLEMENT**)realloc(matching_supplements, (matching_sup_vol + 1) * sizeof(SUPPLEMENT*));
			matching_supplements[matching_sup_vol] = (SUPPLEMENT*)malloc(sizeof(SUPPLEMENT));
			matching_supplements[matching_sup_vol] = supplements[cur_sup];
			matching_sup_vol++;
		}
		while (matching_sup < matching_sup_vol) {
				printf("%5d.    %8s        %11.5lf            %8.2lf\n\n",
					matching_sup + 1, matching_supplements[matching_sup]->firma, matching_supplements[matching_sup]->raw_material, matching_supplements[matching_sup]->payment);
				matching_sup++;
		}
		cur_sup++;
	}
	cur_sup = 0;
	matching_sup = 0;
	if (matching_sup_vol != 0) {
		printf("Enter the needed supplement number: ");
		scanf_s("%d", &needed_sup);
		while (cur_sup < *sup_vol) {
			if (supplements[cur_sup] == matching_supplements[needed_sup - 1] && supplements[cur_sup + 1] != NULL) {
				while (cur_sup < *sup_vol - 1) {
					supplements[cur_sup] = supplements[cur_sup + 1];
					supplements[cur_sup + 1] = cur_sup_buffer;
					cur_sup++;
				}
				free(cur_sup_buffer->firma);
				free(cur_sup_buffer);
				break;
			}
			cur_sup++; 
		}
	}
	free(matching_supplements);
	free(var);
	(*sup_vol)--;
}

void search_sup(SUPPLEMENT** supplements, int* sup_vol) {
	int cur_sup = 0, matching_sup = 0;
	SUPPLEMENT** matching_supplements = (SUPPLEMENT**)malloc(sizeof(SUPPLEMENT*));
	char* var = (char*)malloc(9);
	char s[2];
	printf("Supplier name: ");
	scanf_s("%s", var, 9);
	printf("\n");
	printf("          Supplier        Material volume        Cost\n\n");
	while (cur_sup < *sup_vol) {
		if (strcmp(supplements[cur_sup]->firma, var) == 0) {
			printf("%5d.    %8s        %11.5lf            %8.2lf\n\n",
				matching_sup + 1, supplements[cur_sup]->firma, supplements[cur_sup]->raw_material, supplements[cur_sup]->payment);
			matching_sup++;
		}
		cur_sup++;
	}
	free(var);
	printf("Type any letter and press \"Enter\" to return to menu\n\n");
	scanf_s("%s", s, 1);
}

void search_pay(SUPPLEMENT** supplements, int* sup_vol) {
	int cur_sup = 0, matching_sup = 0;
	SUPPLEMENT** matching_supplements = (void*)malloc(sizeof(SUPPLEMENT*));
	double var;
	char s[2];
	printf("Material Cost: ");
	scanf_s("%lf", &var);
	printf("\n");
	printf("          Supplier        Material volume        Cost\n\n");
	while (cur_sup < *sup_vol) {
		if (supplements[cur_sup]->payment == var) {
			printf("%5d.    %8s        %11.5lf            %8.2lf\n\n",
				matching_sup + 1, supplements[cur_sup]->firma, supplements[cur_sup]->raw_material, supplements[cur_sup]->payment);
			matching_sup++;
		}
		cur_sup++;
	}
	printf("Type any letter and press \"Enter\" to return to menu\n\n");
	scanf_s("%s", s, 1);
}

void list(SUPPLEMENT** supplements, int* sup_vol) {
	int i = 0;
	char s[2];
	printf("          Supplier        Material volume        Cost\n\n");
	while (i < *sup_vol) {
		printf("%5d.    %8s        %11.5lf            %8.2lf\n\n", i+1, supplements[i]->firma, supplements[i]->raw_material, supplements[i]->payment); i++ ;
	}
	printf("Type any letter and press \"Enter\" to return to menu\n\n");
	scanf_s("%s", s, 1);
	
}

void mem_free(SUPPLEMENT** supplements, int* sup_vol) {
	int i = 0;
	while (i < *sup_vol) { free(supplements[i]->firma); free(supplements[i]); i++; }
}

void exit_main(int option, int *exit_flag) {
	if (option == 6) { *exit_flag = 1; }
}

int main(void) {
	int exit_flag = 0, option, sup_vol = 0;
	SUPPLEMENT** supplements = (SUPPLEMENT**)malloc(sizeof(SUPPLEMENT*));
	while (exit_flag == 0) {
		system("cls");
		printf("\n\n\tAdd a new supplement ................ 1\n\n\tRemove a supplement ................. 2\n\n\t"
			"List all supplements ................ 3\n\n\tSearch for a supplier ............... 4\n\n\t"
			"Search for unfinished payments ...... 5\n\n\tExit ................................ 6\n\n");
		scanf_s("%d", &option);
		system("cls");
		printf("\n");
		supplements = (SUPPLEMENT**)realloc(supplements, (sup_vol + 1) * sizeof(SUPPLEMENT*));
		switch (option) {
			case 1: add_sup(supplements, &sup_vol); break;
			case 2: remove_sup(supplements, &sup_vol); break;
			case 3: list(supplements, &sup_vol); break;
			case 4: search_sup(supplements, &sup_vol); break;
			case 5: search_pay(supplements, &sup_vol); break;
			case 6: exit_main(option, &exit_flag); break;
			default: printf("Invalid option\n\n"); break;
		}
	}
	if (sup_vol > 0) { mem_free(supplements, &sup_vol); }
	free(supplements);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
typedef struct supplement {
	char firma;
	double raw_material;
	double payment;
} SUPPLEMENT;

void add(SUPPLEMENT** supplements, int* sup_vol) {
	supplements[*sup_vol] = (SUPPLEMENT*)malloc(sizeof(SUPPLEMENT));
	printf("Supplier: ");
	scanf_s("%c", &(supplements[*sup_vol]->firma));
	printf("\n");
	printf("Material volume: ");
	scanf_s("%lf", &(supplements[*sup_vol]->raw_material));
	printf("\n");
	printf("Cost: ");
	scanf_s("%lf", &(supplements[*sup_vol]->payment));
	printf("\n");
	*sup_vol++;
}

void remove(SUPPLEMENT** supplements, int* sup_vol) {
	int cur_sup = 0, matching_sup = 0, needed_sup = 0, matching_sup_vol = 0;
	SUPPLEMENT** matching_supplements = (SUPPLEMENT**)malloc(sizeof(SUPPLEMENT*));
	int var;
	printf("Supplier or Material volume or Cost:");
	scanf_s("%d\n", &var);
	printf("		  Supplier		  Material volume		   Cost\n");
	while (cur_sup++ < *sup_vol) {
		if (supplements[cur_sup]->firma == var || supplements[cur_sup]->raw_material == (double)var, NULL || supplements[cur_sup]->payment == (double)var) {
			matching_supplements = (SUPPLEMENT**)realloc(matching_supplements, (matching_sup_vol + 1) * sizeof(SUPPLEMENT*));
			matching_supplements[matching_sup_vol] = supplements[cur_sup];
			if (supplements[cur_sup + 1] != NULL) { supplements[cur_sup + 1] = supplements[cur_sup]; }
			*sup_vol--;
			matching_sup_vol++;
		}
		while (matching_sup++ < matching_sup_vol) {
				printf("%5d.    %8c           %5.5lf                   %5.2lf\n",
					matching_sup + 1, supplements[*sup_vol]->firma, supplements[*sup_vol]->raw_material, supplements[*sup_vol]->payment);
		}
	}
	printf("Enter the needed supplement number: ");
	scanf_s("%d\n", &needed_sup);
	free(matching_supplements[needed_sup]);
	free(matching_supplements);
}

void search_sup(SUPPLEMENT** supplements, int* sup_vol) {
	int cur_sup = 0, matching_sup = 0, needed_sup = 0, matching_sup_vol = 0;
	SUPPLEMENT** matching_supplements = (SUPPLEMENT**)malloc(sizeof(SUPPLEMENT*));
	int var;
	printf("Supplier or Material volume or Cost: ");
	scanf_s("%d\n", &var);
	printf("		  Supplier		  Material volume		   Cost\n");
	while (cur_sup++ < *sup_vol) {
		if (supplements[cur_sup]->firma == var) {
			matching_supplements = (SUPPLEMENT**)realloc(matching_supplements, (matching_sup_vol + 1) * sizeof(SUPPLEMENT*));
			matching_supplements[matching_sup_vol] = supplements[cur_sup];
			matching_sup_vol++;
		}
		while (matching_sup++ < matching_sup_vol) {
			printf("%5d.    %8c           %5.5lf                   %5.2lf\n",
				matching_sup + 1, supplements[*sup_vol]->firma, supplements[*sup_vol]->raw_material, supplements[*sup_vol]->payment);
		}
	}
}

void search_pay(SUPPLEMENT** supplements, int* sup_vol) {
	int cur_sup = 0, matching_sup = 0, needed_sup = 0, matching_sup_vol = 0;
	SUPPLEMENT** matching_supplements = (void*)malloc(sizeof(SUPPLEMENT*));
	int var;
	printf("Supplier or Material volume or Cost:");
	scanf_s("%d\n", &var);
	printf("		  Supplier		  Material volume		   Cost\n");
	while (cur_sup++ < *sup_vol) {
		if (supplements[cur_sup]->payment == var) {
			matching_supplements = (SUPPLEMENT**)realloc(matching_supplements, (matching_sup_vol + 1) * sizeof(SUPPLEMENT*));
			matching_supplements[matching_sup_vol] = supplements[cur_sup];
			matching_sup_vol++;
		}
		while (matching_sup++ < matching_sup_vol) {
			printf("%5d.    %8c           %5.5lf                   %5.2lf\n",
				matching_sup + 1, supplements[*sup_vol]->firma, supplements[*sup_vol]->raw_material, supplements[*sup_vol]->payment);
		}
	}
}

void list(SUPPLEMENT** supplements, int* sup_vol) {
	int i;
	printf("Supplier		Material volume		   Cost\n");
		while (i++ < *sup_vol) {
			if (supplements[i] != NULL) {
				printf("%8c           %5.5lf                   %5.2lf\n", supplements[*sup_vol]->firma, supplements[*sup_vol]->raw_material, supplements[*sup_vol]->payment);
			}
		}
}

void clear(SUPPLEMENT** supplements, int* sup_vol) {
	int i;
	while (i < *sup_vol) { free(supplements[i]); }
}

void exit_main(int option, int *exit_flag) {
	if (option == 6) { *exit_flag = 1; }
}

int main(void) {
	int *exit_flag, option, *sup_vol;
	SUPPLEMENT** supplements;
	*exit_flag = 0;
	*sup_vol = 0;
	while (*exit_flag == 0) {
		printf("Add a new supplement           ...... 1\nRemove a supplement           ...... 2\nList all supplements           ...... 3\nSearch for a supplier           ...... 4\n\
Search for unfinished payments ...... 5\nExit							   ...... 6");
		supplements = (SUPPLEMENT**)malloc(*sup_vol * sizeof(SUPPLEMENT*));
		scanf_s("%d\n", &option);
		switch (option) {
			case 1: add(supplements, sup_vol); break;
			case 2: remove(supplements, sup_vol); break;
			case 3: list(supplements, sup_vol); break;
			case 4: search_sup(supplements, sup_vol); break;
			case 5: search_pay(supplements, sup_vol); break;
			case 6: exit_main(option, exit_flag); break;
		}
		clear(supplements, sup_vol);
		free(supplements);
	}
	return 0;
}
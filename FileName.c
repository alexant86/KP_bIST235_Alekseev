#include<stdio.h>
#include<locale.h>
#include<math.h>
#include<stdlib.h>
struct plitka {
	int type_material;
	float  shirina_plitka;
	float  high_plitka;
};
struct vanna {
	float col_vo_material;
	float s_with_openings;
	float s_without_openings;
};
void scanf_plitka(struct plitka* P);
void calculat_without_openings(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V);
float s_wall(float high, float length_wall);
float s_open(float open_hgh[], float open_sh[], float klv_open);
void scanf_vanna(float* l_w, float* h_w);
float scanf_open(float open_sh[], float open_hgh[]);
float klv_material(struct plitka* P, struct vanna* V, float s);
int otch(struct vanna* V, struct plitka* P);
void calculat_with_openings(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V);
void calculat(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V, int s);
int main()
{
	struct plitka P;
	struct vanna V;
	setlocale(LC_CTYPE, "RUS");
	float open_sh[5];
	float open_hgh[5];
	float length_wall, high;
	int d;
	float klv_open = 0;
	int s = 0;
	char ct;
	puts("***********************************************************************************************************");
	puts("*����������� ��� ������� ������������ ���������� �������������� �������� ��� ��������� ���� ������ �������* \n*� ������ �������� �������,���� � ������� �������                                                         *");
	puts("***********************************************************************************************************");
	printf(" _________________________________________________________________________________________________________");
	puts("\n|��������!!!!!!!!                                                                                         |\n|��� ����� ������, � ������ ��� ����� ����� � ������ ����, � ����� ����� � ������ ������,                |\n|������ ������������ ��������� ���������                                                                  |\n|����, ���� ������� ���� ����� ������ ������� ������, ��������� �������� ���� ������.                    |");
	puts("|_________________________________________________________________________________________________________|\n");
	puts("***********************************************************************************************************");
	puts("*�������� ������� ����                                                                                    *");
	puts("***********************************************************************************************************");
	printf("*1 - ������ ��������� ������                                                                              *\n*2 - ������ ��������� ������                                                                             *\n*3 - ������ ��������� ������                                                                              *\n*4 - ���������� ������� ������                                                                            *\n*5 - ������ ����������� ���-�� ���������                                                                  *\n*6 - ��������� �����                                                                                      *\n*7 - ���������� ���������                                                                                 *\n");
	puts("***********************************************************************************************************");
	while (1) {
		puts("������� ����� ������ ����");
		scanf("%d", &d);
		switch (d) {
		case 1:
			scanf_vanna(&length_wall, &high);
			break;
		case 2:
			klv_open = scanf_open(open_sh, open_hgh);
			break;
		case 3:
			scanf_plitka(&P);
			break;
		case 4:
			printf("���� ������ ������ ������� ������ ������� � ������ ������, ������� 1");
			printf("\n���� ������ ������ ������� ������ ������� ��� ����� ������, ������� 2\n");
			scanf("%d", &s);
			while (s != 1 && s != 2) {
				puts("�� ������ ������ 1 ��� 2");
				printf("���� ������ ������ ������� ������ ������� � ������ ������, ������� 1\n");
				printf("���� ������ ������ ������� ������ ������� ��� ����� ������, ������� 2\n");
				scanf("%d", &s);
			}
			calculat(length_wall, high, open_sh, open_hgh, klv_open, &V, s);
			if (V.s_with_openings <= 0 && s == 1) {
				puts("� ��������� �� �� ���� ��������� ��� ����� ������\n��������� ��������� ��� �������� ��� ��� ������� �� ����� ���� �������������");
				return 0;
			}
			break;
		case 5:
			printf("������� 2, ���� ������ ������ ���������� ��������� ��� ������");
			printf("\n������� 1, ���� ������ ������ ���������� ��������� � �������\n");
			scanf("%d", &s);
			while (s != 1 && s != 2) {
				puts("�� ������ ������ 1 ��� 2.");
				printf("������� 2, ���� ������ ������ ���������� ��������� ��� ������");
				printf("\n������� 1, ���� ������ ������ ���������� ��������� � �������\n");
				scanf("%d", &s);
			}
			if (s == 2) {
				printf("����������� ���-�� ���������:%lf �\n", ceil(klv_material(&P, &V, V.s_without_openings)));
			}
			else if (s == 1) {
				printf("����������� ���-�� ���������:%lf �\n", ceil(klv_material(&P, &V, V.s_with_openings)));
			}
			break;
		case 6:
			printf("����� ������� �������\n");
			otch(&V, &P);
			break;
		case 7:
			return 0;
		default:
			scanf("%c", &ct);
			puts("�� �� ������� ����� ����");
		}
	}
}
void calculat_with_openings(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V) {
	V->s_with_openings = s_wall(l_w, h_w) - s_open(open_hgh, open_sh, klv_open);
	V->s_without_openings = s_wall(l_w, h_w);
	printf("������� ������ ������� � ������ ������ = %.3f �^2\n", V->s_with_openings);
}
float s_wall(float high, float length_wall) {
	return 4 * high * length_wall;
}
float s_open(float open_hgh[], float open_sh[], float klv_open) {
	float s = 0;
	for (int i = 0; i < klv_open; i++) {
		s = s + open_hgh[i] * open_sh[i];
	}
	return s;
}
void scanf_plitka(struct plitka* P) {
	int flag;
	char flag_1;
	float sh_p;
	float high_p;
	printf("�������� ��� ������������� ���������\n1.������������ ������\n2.���������� �������\n3.����������� ������\n");
	scanf("%d", &flag);
	switch (flag) {
	case 1:
		puts("�� �������:������������ ������");
		break;
	case 2:
		puts("�� �������:���������� �������");
		break;
	case 3:
		puts("�� �������:����������� ������");
		break;
	default:
		scanf("%c", &flag_1);
		puts("�� �� ������� ��� ������������� ���������");
		printf("�������� ��� ������������� ���������\n1.������������ ������\n2.���������� �������\n3.����������� ������\n");
		scanf("%d", &flag);
	}
	P->type_material = flag;
	printf("������� ������ ������ - �\n");
	scanf("%f", &sh_p);
	while (sh_p <= 0) {
		puts("�� ����� ������������ ��������\n���������� ��� ���");
		printf("������� ������ ������ - �\n");
		scanf("%f", &sh_p);
	}
	P->shirina_plitka = sh_p;
	printf("������� ������ ������ - �\n");
	scanf("%f", &high_p);
	while (high_p <= 0) {
		puts("�� ����� ������������ ��������\n���������� ��� ���");
		printf("������� ������ ������ - �\n");
		scanf("%f", &high_p);
	}
	P->high_plitka = high_p;
}
void scanf_vanna(float* l_w, float* h_w) {
	puts("������� ������ ����� - �");
	scanf("%f", l_w);
	while (*l_w <= 0) {
		puts("�� ����� ������������ ��������");
		puts("������� ������ ����� - �");
		scanf("%f", l_w);
	}
	puts("������� ������ ����� - �");
	scanf("%f", h_w);
	while (*h_w <= 0) {
		puts("�� ����� ������������ ��������");
		puts("������� ������ ����� - �");
		scanf("%f", h_w);
	}
}
float scanf_open(float open_sh[], float open_hgh[]) {
	float klv_open;
	printf("������� ���-�� ������\n");
	scanf("%f", &klv_open);
	while (klv_open != ceil(klv_open) || klv_open <= 0) {
		puts("�� ����� ������������ ��������\n���������� ��� ���");
		printf("������� ���-�� ������\n");
		scanf("%f", &klv_open);
	}
	for (int i = 0; i < klv_open; i++) {
		printf("������� ������ %d ����� �\n", i + 1);
		scanf("%f", &open_sh[i]);
		while (open_sh[i] <= 0) {
			puts("�� ����� ������������ ��������\n���������� ��� ���");
			printf("������� ������ %d ����� �\n", i + 1);
			scanf("%f", &open_sh[i]);
		}
	}
	for (int i = 0; i < klv_open; i++) {
		printf("������� ������ %d ����� �\n", i + 1);
		scanf("%f", &open_hgh[i]);
		while (open_hgh[i] <= 0) {
			puts("�� ����� ������������ ��������\n���������� ��� ���");
			printf("������� ������ %d ����� �\n", i + 1);
			scanf("%f", &open_hgh[i]);
		}
	}
	return klv_open;
}
int otch(struct vanna* V, struct plitka* P) {
	char fname[20] = "vanna.txt";
	FILE* out;
	if ((out = fopen(fname, "a")) == NULL) {
		printf("������ �������� ����� ��� ������");
		return 1;
	}
	fprintf(out, "��� ���������:%d\n", P->type_material);
	fprintf(out, "\n������ ������:%.4f �\n", P->shirina_plitka);
	fprintf(out, "\n������ ������:%.4f �\n", P->high_plitka);
	fprintf(out, "\n������� ������ ������� � ������ ������ %f �^2\n", V->s_with_openings);
	fprintf(out, "\n������� ������ ������� ��� ����� ������ %f �^2\n", V->s_without_openings);
	fprintf(out, "\n����������� ���-�� ��������� ��� ��������� ���� ������ ������� ��������:%f � ������ ������ = %.0f �^2\n", V->s_with_openings, ceil(V->s_with_openings / (P->shirina_plitka * P->high_plitka)));
	fprintf(out, "\n����������� ���-�� ��������� ��� ��������� ���� ������ ������� ��������:%f ��� ����� ������ = %.0f �^2\n", V->s_without_openings, ceil(V->s_without_openings / (P->shirina_plitka * P->high_plitka)));
	fclose(out);
	return 0;
}
float klv_material(struct plitka* P, struct vanna* V, float s) {
	V->col_vo_material = (s) / (P->shirina_plitka * P->high_plitka);
	return (s) / (P->shirina_plitka * P->high_plitka);
}
void calculat_without_openings(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V) {
	V->s_without_openings = s_wall(l_w, h_w);
	V->s_with_openings = s_wall(l_w, h_w) - s_open(open_hgh, open_sh, klv_open);
	printf("������� ������ ������� ��� ����� ������ = %f �^2\n", V->s_without_openings);
}
void calculat(float l_w, float h_w, float open_sh[], float open_hgh[], float klv_open, struct vanna* V, int s) {
	if (s == 2) {
		calculat_without_openings(l_w, h_w, open_sh, open_hgh, klv_open, V);
	}
	else if (s == 1) {
		calculat_with_openings(l_w, h_w, open_sh, open_hgh, klv_open, V);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void state(int player, int now, int player_money);
void chance(int* player);
void fate(int* player);

int b()
{
	int player0 = 0,player1=0;
	int player[2];	//���a���
	char Richman[44];	//�g�a���A
	int dice = 0;	//��l
	int now0=0, now1=0;	//���a�Ҧb��m
	char choise=' ';	//���

	srand(time(NULL));	//�ɶ��ü�

	//��l��
	for (int i = 0; i < 2; i++)	//���a���
	{
		player[i] = 3000;
	}
	for (int i = 0; i < 44; i++)	//�g�a���A
	{
		Richman[i] = ' ';
	}

	//��� �}�ҷs�C��(n)�άO�~��e�@���C��(p)
	printf("�}�ҷs�C��(n)�άO�~��e�@���C��(p): ");
	scanf(" %c", &choise);

	//���b
	while (choise != 'n' && choise != 'p')
	{
		printf("��J���~�A�Э��s��J!	");
		scanf("%c", &choise);
	}

	//�~��W��
	if (choise != 'n')	
	{
		FILE* rich = fopen("game.dat", "a+");	//�}��
		fscanf(rich, "%d,%d,", &player0,&player1);
		fread(&Richman, sizeof(Richman), 1, rich);
		/*for (int i = 0; i < 44; i++)
		{
			fscanf(rich, ",%c", &Richman[i]);
		}*/
		
		player[0] = player0;
		player[1] = player1;
		fclose(rich);	//���ɮ�
	}

	//��X���a���A
	state(0, now0, player[0]);
	state(1, now1, player[1]);

	while (true)
	{
		//���a0
		//��� �� g �䬰���l�A�� q �䬰���}�{�� --- ���a0
		printf("����g���䬰���l�A����q���䬰���}�{��: ");
		scanf(" %c", &choise);

		//���b
		while (choise != 'g' && choise != 'q')
		{
			printf("��J���~�A�Э��s��J!	");
			scanf("%c", &choise);
		}

		//����C��
		if (choise == 'g')
		{
			dice = (rand() % 6) + 1;	//�Y��l

			printf("���a0 ���l %d\n", dice);	//��X��l�I��

			now0 += dice;	//��s���a0��m

			//�P�_��m�ƬO�_�b0~43
			if (now0 > 43)
			{
				now0 -= 44;
			}

			//��
			if (now0 == 0 || now0 == 22)
			{
				printf("�𮧤@��\n");
			}
			//���|
			else if (now0 == 11 || now0 == 33)
			{
				printf("��o�@�����|\n");
				chance(&player[0]);
			}
			//�R�B
			else if (now0 == 5 || now0 == 16 || now0 == 27 || now0 == 40)
			{
				printf("��o�@���R�B\n");
				fate(&player[0]);

				//�P�_�O�_���X�ӭt
				if (player[0] <= 0)
				{
					printf("���a1 WINNER!!\n\tGAME OVER\n");	//���a1�ӧQ
					break;	//���X while
				}
			}
			//��L
			else
			{
				//�P�_�g�a�O�_�w�Q�ʶR
				//���Q�ʶR
				if (Richman[now0] == ' ')
				{
					//�P�_�O�_����������i�ʶR
					if (player[0] >= 500)
					{
						printf("��m %d�ثe�O�L�H���A���a0 �ʶR\n",now0);

						//�ʤJ�g�a
						player[0] -= 500;
						Richman[now0] = 'a';

						//�P�_�O�_���X�ӭt
						if (player[0] <= 0)
						{
							printf("���a1 WINNER!!\n\tGAME OVER\n");	//���a1�ӧQ
							break;	//���X while
						}
					}
				}
				//�w�Q�ʶR
				else
				{
					if (Richman[now0] == 'b')	//�g�a�O��⪺
					{
						printf("�g�a�O��⪺\n");

						player[0] -= 200;	//�@��

						//�P�_�O�_���X�ӭt
						if (player[0] <= 0)
						{
							printf("���a1 WINNER!!\n\tGAME OVER\n");	//���a1�ӧQ
							break;	//���X while
						}
					}
				}
			}
			state(0, now0, player[0]); //���A��X
			printf("\n");
		}
		//���}�{��
		else
		{
			player0 = player[0];
			player1 = player[1];
			FILE* rich = fopen("game.dat", "w+");	//�}��
			fprintf(rich, "%d,%d,", player0, player1);
			for (int i = 0; i < 44; i++)
			{
				fprintf(rich, "%c", Richman[i]);
			}
			fclose(rich);	//���ɮ�
			break;
		}


		//���a1
		//��� �� g �䬰���l�A�� q �䬰���}�{�� 
		printf("����g���䬰���l�A����q���䬰���}�{��: ");
			scanf(" %c", &choise);

		//���b
		while (choise != 'g' && choise != 'q')
		{
			printf("��J���~�A�Э��s��J!	");
			scanf("%c", &choise);
		}

		//����C��
		if (choise == 'g')
		{
			dice = (rand() % 6) + 1;	//�Y��l

			printf("���a1 ���l %d\n", dice);	//��X��l�I��

			now1 += dice;	//��s���a0��m

			//�P�_��m�ƬO�_�b0~43
			if (now1 > 43)
			{
				now1 -= 44;
			}

			//��
			if (now1 == 0 || now1 == 22)
			{
				printf("�𮧤@��\n");
			}
			//���|
			else if (now1 == 11 || now1 == 33)
			{
				printf("��o�@�����|\n");
				chance(&player[1]);
			}
			//�R�B
			else if (now1 == 5 || now1 == 16 || now1 == 27 || now1 == 40)
			{
				printf("��o�@���R�B\n");
				fate(&player[1]);

				//�P�_�O�_���X�ӭt
				if (player[1] <= 0)
				{
					printf("���a0 WINNER!!\n\tGAME OVER\n");	//���a0�ӧQ
					break;	//���X while
				}
			}
			//��L
			else
			{
				//�P�_�g�a�O�_�w�Q�ʶR
				//���Q�ʶR
				if (Richman[now1] == ' ')
				{
					//�P�_�O�_����������i�ʶR
					if (player[1] >= 500)
					{
						//�ʤJ�g�a
						printf("��m %d�ثe�O�L�H���A���a1 �ʶR\n", now1);
						player[1] -= 500;
						Richman[now1] = 'b';

						//�P�_�O�_���X�ӭt
						if (player[1] <= 0)
						{
							printf("���a0 WINNER!!\n\tGAME OVER\n");	//���a0�ӧQ
							break;	//���X while
						}
					}
				}
				//�w�Q�ʶR
				else
				{
					if (Richman[now1] == 'a')	//�g�a�O��⪺
					{
						printf("�g�a�O��⪺\n");

						player[1] -= 200;	//�@��

						//�P�_�O�_���X�ӭt
						if (player[1] <= 0)
						{
							printf("���a0 WINNER!!\n\tGAME OVER\n");	//���a0�ӧQ
							break;	//���X while
						}
					}
				}
			}
			state(1, now1, player[1]); //���A��X
			printf("\n");
		}
		//���}�{��
		else
		{
			player0 = player[0];
			player1 = player[1];
			FILE* rich = fopen("game.dat", "w+");	//�}��
			fprintf(rich, "%d,%d,", player0, player1);
			for (int i = 0; i < 44; i++)
			{
				fprintf(rich, "%c", Richman[i]);
			}
			fclose(rich);	//���ɮ�
			break;
		}
	}
	return 0;
}

//���a���A
void state(int player, int now, int player_money)
{
	printf("���a%d ��m %d ��� %d\n", player, now, player_money);
}

//���|
void chance(int* player)
{
	int money = 0;
	
	srand(time(NULL));	//�ɶ��ü�

	money = rand() % 5001;
	*player += money;	//�[��
	printf("�W�[��� %d ��", money);
}

//�R�B
void fate(int* player)
{
	int money = 0;

	srand(time(NULL));	//�ɶ��ü�

	money = rand() % 1001;
	*player -= money;	//����
	printf("������� %d ��", money);
}




























//	< main function --- ��k�G(����) >

/*
* 
	//�~��W��
	if (choise != 'n')
	{
		FILE* rich = fopen("game.dat", "a+");	//�}��
		fscanf(rich, "%d,%d,", &player0,&player1);
		fread(&Richman, sizeof(Richman), 1, rich);
		/*for (int i = 0; i < 44; i++)
		{
			fscanf(rich, ",%c", &Richman[i]);
		}

		//���}�{��
		else
		{
			player0 = player[0];
			player1 = player[1];
			FILE* rich = fopen("game.dat", "w+");	//�}��
			fprintf(rich, "%d,%d,", player0, player1);
			for (int i = 0; i < 44; i++)
			{
				fprintf(rich, "%c", Richman[i]);
			}
			fclose(rich);	//���ɮ�
			break;
		}

		//���}�{��
		else
		{
			player0 = player[0];
			player1 = player[1];
			FILE* rich = fopen("game.dat", "w+");	//�}��
			fprintf(rich, "%d,%d,", player0, player1);
			for (int i = 0; i < 44; i++)
			{
				fprintf(rich, "%c", Richman[i]);
			}
			fclose(rich);	//���ɮ�
			break;
		}
	}
	return 0;
}
*/

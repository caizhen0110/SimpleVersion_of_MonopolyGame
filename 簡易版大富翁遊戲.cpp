#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void state(int player, int now, int player_money);
void chance(int* player);
void fate(int* player);

int b()
{
	int player0 = 0,player1=0;
	int player[2];	//玩家基金
	char Richman[44];	//土地狀態
	int dice = 0;	//骰子
	int now0=0, now1=0;	//玩家所在位置
	char choise=' ';	//選擇

	srand(time(NULL));	//時間亂數

	//初始化
	for (int i = 0; i < 2; i++)	//玩家基金
	{
		player[i] = 3000;
	}
	for (int i = 0; i < 44; i++)	//土地狀態
	{
		Richman[i] = ' ';
	}

	//選擇 開啟新遊戲(n)或是繼續前一次遊戲(p)
	printf("開啟新遊戲(n)或是繼續前一次遊戲(p): ");
	scanf(" %c", &choise);

	//防呆
	while (choise != 'n' && choise != 'p')
	{
		printf("輸入錯誤，請重新輸入!	");
		scanf("%c", &choise);
	}

	//繼續上次
	if (choise != 'n')	
	{
		FILE* rich = fopen("game.dat", "a+");	//開檔
		fscanf(rich, "%d,%d,", &player0,&player1);
		fread(&Richman, sizeof(Richman), 1, rich);
		/*for (int i = 0; i < 44; i++)
		{
			fscanf(rich, ",%c", &Richman[i]);
		}*/
		
		player[0] = player0;
		player[1] = player1;
		fclose(rich);	//關檔案
	}

	//輸出玩家狀態
	state(0, now0, player[0]);
	state(1, now1, player[1]);

	while (true)
	{
		//玩家0
		//選擇 按 g 鍵為丟骰子，按 q 鍵為離開程式 --- 玩家0
		printf("按’g’鍵為丟骰子，按’q’鍵為離開程式: ");
		scanf(" %c", &choise);

		//防呆
		while (choise != 'g' && choise != 'q')
		{
			printf("輸入錯誤，請重新輸入!	");
			scanf("%c", &choise);
		}

		//執行遊戲
		if (choise == 'g')
		{
			dice = (rand() % 6) + 1;	//擲骰子

			printf("玩家0 丟骰子 %d\n", dice);	//輸出骰子點數

			now0 += dice;	//更新玩家0位置

			//判斷位置數是否在0~43
			if (now0 > 43)
			{
				now0 -= 44;
			}

			//休息
			if (now0 == 0 || now0 == 22)
			{
				printf("休息一次\n");
			}
			//機會
			else if (now0 == 11 || now0 == 33)
			{
				printf("獲得一次機會\n");
				chance(&player[0]);
			}
			//命運
			else if (now0 == 5 || now0 == 16 || now0 == 27 || now0 == 40)
			{
				printf("獲得一次命運\n");
				fate(&player[0]);

				//判斷是否分出勝負
				if (player[0] <= 0)
				{
					printf("玩家1 WINNER!!\n\tGAME OVER\n");	//玩家1勝利
					break;	//跳出 while
				}
			}
			//其他
			else
			{
				//判斷土地是否已被購買
				//未被購買
				if (Richman[now0] == ' ')
				{
					//判斷是否有足夠基金可購買
					if (player[0] >= 500)
					{
						printf("位置 %d目前是無人的，玩家0 購買\n",now0);

						//購入土地
						player[0] -= 500;
						Richman[now0] = 'a';

						//判斷是否分出勝負
						if (player[0] <= 0)
						{
							printf("玩家1 WINNER!!\n\tGAME OVER\n");	//玩家1勝利
							break;	//跳出 while
						}
					}
				}
				//已被購買
				else
				{
					if (Richman[now0] == 'b')	//土地是對手的
					{
						printf("土地是對手的\n");

						player[0] -= 200;	//罰款

						//判斷是否分出勝負
						if (player[0] <= 0)
						{
							printf("玩家1 WINNER!!\n\tGAME OVER\n");	//玩家1勝利
							break;	//跳出 while
						}
					}
				}
			}
			state(0, now0, player[0]); //狀態輸出
			printf("\n");
		}
		//離開程式
		else
		{
			player0 = player[0];
			player1 = player[1];
			FILE* rich = fopen("game.dat", "w+");	//開檔
			fprintf(rich, "%d,%d,", player0, player1);
			for (int i = 0; i < 44; i++)
			{
				fprintf(rich, "%c", Richman[i]);
			}
			fclose(rich);	//關檔案
			break;
		}


		//玩家1
		//選擇 按 g 鍵為丟骰子，按 q 鍵為離開程式 
		printf("按’g’鍵為丟骰子，按’q’鍵為離開程式: ");
			scanf(" %c", &choise);

		//防呆
		while (choise != 'g' && choise != 'q')
		{
			printf("輸入錯誤，請重新輸入!	");
			scanf("%c", &choise);
		}

		//執行遊戲
		if (choise == 'g')
		{
			dice = (rand() % 6) + 1;	//擲骰子

			printf("玩家1 丟骰子 %d\n", dice);	//輸出骰子點數

			now1 += dice;	//更新玩家0位置

			//判斷位置數是否在0~43
			if (now1 > 43)
			{
				now1 -= 44;
			}

			//休息
			if (now1 == 0 || now1 == 22)
			{
				printf("休息一次\n");
			}
			//機會
			else if (now1 == 11 || now1 == 33)
			{
				printf("獲得一次機會\n");
				chance(&player[1]);
			}
			//命運
			else if (now1 == 5 || now1 == 16 || now1 == 27 || now1 == 40)
			{
				printf("獲得一次命運\n");
				fate(&player[1]);

				//判斷是否分出勝負
				if (player[1] <= 0)
				{
					printf("玩家0 WINNER!!\n\tGAME OVER\n");	//玩家0勝利
					break;	//跳出 while
				}
			}
			//其他
			else
			{
				//判斷土地是否已被購買
				//未被購買
				if (Richman[now1] == ' ')
				{
					//判斷是否有足夠基金可購買
					if (player[1] >= 500)
					{
						//購入土地
						printf("位置 %d目前是無人的，玩家1 購買\n", now1);
						player[1] -= 500;
						Richman[now1] = 'b';

						//判斷是否分出勝負
						if (player[1] <= 0)
						{
							printf("玩家0 WINNER!!\n\tGAME OVER\n");	//玩家0勝利
							break;	//跳出 while
						}
					}
				}
				//已被購買
				else
				{
					if (Richman[now1] == 'a')	//土地是對手的
					{
						printf("土地是對手的\n");

						player[1] -= 200;	//罰款

						//判斷是否分出勝負
						if (player[1] <= 0)
						{
							printf("玩家0 WINNER!!\n\tGAME OVER\n");	//玩家0勝利
							break;	//跳出 while
						}
					}
				}
			}
			state(1, now1, player[1]); //狀態輸出
			printf("\n");
		}
		//離開程式
		else
		{
			player0 = player[0];
			player1 = player[1];
			FILE* rich = fopen("game.dat", "w+");	//開檔
			fprintf(rich, "%d,%d,", player0, player1);
			for (int i = 0; i < 44; i++)
			{
				fprintf(rich, "%c", Richman[i]);
			}
			fclose(rich);	//關檔案
			break;
		}
	}
	return 0;
}

//玩家狀態
void state(int player, int now, int player_money)
{
	printf("玩家%d 位置 %d 基金 %d\n", player, now, player_money);
}

//機會
void chance(int* player)
{
	int money = 0;
	
	srand(time(NULL));	//時間亂數

	money = rand() % 5001;
	*player += money;	//加錢
	printf("增加基金 %d 元", money);
}

//命運
void fate(int* player)
{
	int money = 0;

	srand(time(NULL));	//時間亂數

	money = rand() % 1001;
	*player -= money;	//扣錢
	printf("扣除基金 %d 元", money);
}




























//	< main function --- 方法二(部分) >

/*
* 
	//繼續上次
	if (choise != 'n')
	{
		FILE* rich = fopen("game.dat", "a+");	//開檔
		fscanf(rich, "%d,%d,", &player0,&player1);
		fread(&Richman, sizeof(Richman), 1, rich);
		/*for (int i = 0; i < 44; i++)
		{
			fscanf(rich, ",%c", &Richman[i]);
		}

		//離開程式
		else
		{
			player0 = player[0];
			player1 = player[1];
			FILE* rich = fopen("game.dat", "w+");	//開檔
			fprintf(rich, "%d,%d,", player0, player1);
			for (int i = 0; i < 44; i++)
			{
				fprintf(rich, "%c", Richman[i]);
			}
			fclose(rich);	//關檔案
			break;
		}

		//離開程式
		else
		{
			player0 = player[0];
			player1 = player[1];
			FILE* rich = fopen("game.dat", "w+");	//開檔
			fprintf(rich, "%d,%d,", player0, player1);
			for (int i = 0; i < 44; i++)
			{
				fprintf(rich, "%c", Richman[i]);
			}
			fclose(rich);	//關檔案
			break;
		}
	}
	return 0;
}
*/

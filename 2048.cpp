#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#define satr 4
#define soton 4
#define KB_UP 5
#define KB_DOWN 2
#define KB_LEFT 1
#define KB_RIGHT 3
struct game
{
    int board[satr][soton];
    int score=0;
    int date;
    int maxnumber;
};
struct user
{
    char name[50];
    int pasword;
    game games; 
};
user list[10] ;
user gamer;
game g;
int flag=0 ;
int userpos=0 ;
int indexx = 0 ;

FILE *fp;
void startmenue() ;
void signup() ;
void login() ;
void gameboard() ;
void  Initialization() ;
void Randomization( int temparray[] , int n) ;
void print() ;
int findmax(int arr[satr][soton]) ;
void check() ;
void go_left() ;
void rotate(int n) ;
void compact(int i) ;
void copy(int board[4][4]) ;
void addnewblocks() ;
int randnumber() ;
void restart() ;
void savegame() ;
void loadfile() ;
int main()
{
    startmenue();
    return 0;
}
void startmenue()
{
    std::cout<<"**start menue**"<<"\n"<<"Enter'S' to Signup"<<"\n"<<"Enter'L' to Login"<<"\n""Enter'E' to Exit"<<"\n";
    char firstrecomend ;
    std::cin >> firstrecomend ;
    if(firstrecomend =='E' || firstrecomend =='e')
    {
        system("clear") ;
        std::cout<<"You Exit from the program.";
        exit(0);
    }
    if(firstrecomend=='S' || firstrecomend =='s')
    {
        system("clear") ;
        //cout << "sign up" ;
        signup();
        return;
    }
    if(firstrecomend=='L' || firstrecomend =='l')
    {
        system("clear") ;
        //std::cout << "login"  ;
        login();
        return;
    }
    else
    {
        system("clear") ;
        std::cout << "Invalid Input \n please try again \n"  ;
        startmenue() ;
        return ;
    }
}
void signup()
{
        std::cout << "Enter'B' To Go Back"<<"\n"<<"Press Any Key To Continue"<<"\n";
        char back;
        std::cin >> back ; 
        if(back=='B' || back == 'b' )
        {
            system( "clear" ) ;
            startmenue();
        }
        else
        {
            user Registrant ;
            std::cout<<"Enter Your username:"<<"\n";
            scanf("%s",Registrant.name);
            std::cout<<"Enter Your Password:"<<"\n";
            scanf("%d",&Registrant.pasword);
            fp=fopen("users_data", "a+b");
            if(fp==NULL)
            {
                std::cout<<"Error in opening file";
                exit(0);
            }
            fseek(fp ,0, SEEK_END);
            int pos= ftell(fp);
            int count=pos/sizeof(user);
            for(int i=0 ; i<count ; ++i)
            {
                fseek(fp , i*sizeof(user) , SEEK_END );
                fread(&list[i].name ,sizeof(user), 1 , fp );
                if(strcmp(list[i].name ,Registrant.name )==0)
                {
                    std::cout<<"Your Username Is Repetitive Please signup again"<<"\n";
                    fclose(fp);
                    system("clear");
                    startmenue();
                    return;
                }

            }
            fseek(fp ,0, SEEK_END);
            fwrite(&Registrant, sizeof(user) , 1 , fp);
            system("clear");
            std::cout<<"Your signup was seccesfull"<<"\n";
            startmenue();
            return;

        }
}
void login()
{
    fp=fopen("users_data", "a+b");
    fseek(fp ,0, SEEK_END);
    int pos= ftell(fp);
    int count=pos/sizeof(user);

    if(pos==0)
    {
        std::cout<<"Error in opening file,please signup first"<<"\n";
        startmenue();
        return;

    }
    std::cout<<"Enter Your username:"<<"\n";
    scanf("%s",gamer.name);
    std::cout<<"Enter Your Password:"<<"\n";
    scanf("%d",&gamer.pasword);

    for(int index=0 ; index<count ; ++index)
    {
        fseek(fp , index*sizeof(user) , SEEK_SET);
        fread(&list[index].name ,sizeof(user), 1 , fp );
        fread(&list[index].pasword ,sizeof(user), 1 , fp );
        if(strcmp(list[index].name ,gamer.name )==0 && list[index].pasword==gamer.pasword)
        {
            std::cout<<"Your login was seccesfull"<<"\n";
            userpos = index ;
            gameboard();
            indexx = index ;
            return;
        }
    }
    std::cout<<"Your login was  not seccesfull please try again"<<"\n"<<"Enter'B' To Go Back"<<"\n"<<"Press Any Key To Continue"<<"\n";
    char back;
    std::cin >> back ;
    system("clear");
    if(back=='B' || back=='b')
    {
        startmenue();
        return;
    }
    login();
    return;
}
void gameboard()
{
    char input ;
    int gc;//game command
    bool booll=true;

    std::cout<<"Enter each one you want:"<<"\n"<<"1-->play new game"<<"\n"<<"2-->load last game"<<"\n"<<"3-->change your password"<<"\n";
    //flag=1;
    while(booll)
    {
    booll=true;
    std::cin >> input ;
    switch(input)
    {
    case '1' :
        Initialization();
        system("clear");
        print();
        flag=1;//game started
        booll=false;
        break;
    case '2' :
        loadfile();
        booll=false;
        break;
    case '3' :
        //paswordchange();
        booll=false;
        break;
    default:
        std::cout<<"Innalid Input\n"<<"Please Enter correct Number\n";
        break;
    }
    }
    //game prosses
    while(flag==1)
    {
    flag=1;
    std::cin >> gc ;
    switch(gc)
    {
    case KB_UP:
        rotate(3);
        go_left();
        check(); // up
        rotate(1);
        system("clear");
        print();
        break;
    case KB_DOWN:
        rotate(1);
        go_left();
        check(); // down
        rotate(3);
        system("clear");
        print();
        break;
    case KB_RIGHT:
        rotate(2);
        go_left();
        check(); // right
        rotate(2);
        system("clear");
        print();
        break;
    case KB_LEFT:
        go_left(); //left
        check();
        system("clear");
        print();
        break;
    case 6 :
        savegame();
        break;
    case 0 :
        restart();
        system("clear");
        print();
        flag=1;
        break;
    }
    } 
    return;
}
void  Initialization()
{
    int temparray[4];
    Randomization(temparray , 4);
    if(temparray[0]==temparray[2]&& temparray[1]==temparray[3])
    {
        Initialization();
        return ;
    }

    g.board[temparray[0]][temparray[1]]=2;
    g.board[temparray[2]][temparray[3]]=2;
}
void Randomization( int temparray[] , int n)
{
    srand(time(0));
    for(int i=0 ; i<n ;++i)
        temparray[i]=rand()%4 ;
}
void print()
{
	for (int i = 0; i < 4; i++) 
    {
		printf("\n|-----|-----|-----|-----|\n|");
		for (int j = 0; j < 4; j++) 
        {
			if (g.board[i] == 0) 
            {
				printf("%5c|", '*');
			} else 
            {
				printf("%5d|", g.board[i][j]);
			}
		}
	}
	printf("\n|-----|-----|-----|-----|\n");
    std::cout<<"\n"<<"Your Score :"<<g.score<<"\n"<<"Maxnumber in board:"<<findmax(g.board)<<"\n"<<"Date:"<<g.date<<"\n";
    std::cout<<"Enter(0) to restart"<<"\n"<<"Enter(6) to save this game";

}
int findmax(int arr[satr][soton])
{
    int maxx=0;
    for(int s=0 ;s<satr ; s++)
    for(int d=0 ; d<soton ; d++ )
    {
        if(arr[s][d]>maxx)
        maxx=arr[s][d];
    }
    return(maxx);

}
void check()
{
    int count=0;
    for(int i=0 ; i<satr ; ++i)
    for(int j=0 ; j<soton ; ++j)
    {
        if(g.board[i][j]==0)
        ++count;
        if(g.board[i][j]==2048)
        {
            flag=0;
            std::cout<<"you win";
        }
    }
    if(count!=0)
        addnewblocks();
    else
    {
        flag=0;
        std::cout<<"you loose...";
        fclose(fp);
        exit(0);
    }
}
void go_left()
{
    int newindex=0;
    for(int i=0 ;i<satr ; ++i)
    {
        compact(i);
        for(int c=0;c<soton ; ++c )
        {
            if(g.board[i][c]==g.board[i][c+1])
            {
                g.board[i][c]+=g.board[i][c+1];
                g.board[i][c+1]=0;
                g.score+=g.board[i][c];

            }
            compact(i);
        }
    }
}
void rotate(int n)//n time rotate
{
    for(;n>0;--n)
    {
        int sameboard[4][4];
        copy(sameboard);
        for (int j = 0; j < 4; j++)
        for (int i = 3; i >= 0; i--)
            g.board[i][j]=sameboard[4-j-1][i];

    }
}
void compact(int i)
{
    //loop for compact numbers in to left side
    int newindex=0;
    for(int j=0; j<soton ;++j)
    {
        if(g.board[i][j]!=0)
        {
            g.board[i][newindex]=g.board[i][j];
            newindex++;
        }
    }
    for(; newindex<soton ; ++newindex)
        g.board[i][newindex]=0;
}
void copy(int board[4][4])
{
    for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
        board[i][j]=g.board[i][j];

}
void addnewblocks()
{
    bool b=true;
    int temparray[2];
    while(b)
    {
        Randomization(temparray , 2);
		if( g.board[temparray[0]][temparray[1]]==0)
        b=false;
    }
    g.board[temparray[0]][temparray[1]]=randnumber();


}
int randnumber()
{
    srand(time(0));
    int tmp =rand()%100;
    if(tmp>=0&&tmp<65)
    return(2);
    if(tmp>=65&&tmp<90)
    return(4);
    if(tmp>=90&&tmp<96)
    return(8);
    if(tmp>=96&&tmp<98)
    return(16);
    else
    return(32);
}
void savegame()
{
    
    fp=fopen("users_data", "a+b");
    for(int s=0 ;s<satr ; s++)
    for(int d=0 ; d<soton ; d++ )
    {
        gamer.games.board[s][d]=g.board[s][d];
    }
    gamer.games.score=g.score;
    gamer.games.maxnumber=g.maxnumber;
    gamer.games.date=g.date;
    fseek(fp , indexx*sizeof(user) , SEEK_SET);
    fread(&gamer ,sizeof(user), 1 , fp );
    fclose(fp);
    system("clear");
    startmenue();
}
void restart()
{
    for(int s=0 ;s<satr ; s++)
    for(int d=0 ; d<soton ; d++ )
    {
        g.board[s][d]=0;
    }
    g.score=0;
    g.maxnumber=0;
    return;
}
void loadfile()
{
    fp=fopen("users_data", "a+b");
    fseek(fp , indexx*sizeof(user) , SEEK_SET);
    fread(&list[indexx].games,sizeof(user), 1 , fp );
	if (list[indexx].games.score == 0)
    {
		std::cout<<"no game loaded, start new game";
        gameboard();
		return;
	}
	for (int i = 0; i <satr; i++)
	{
		for (int j = 0; j <soton; j++)
		{
			g.board[i][j]=list[indexx].games.board[i][j];
		}
    }
    g.score=list[indexx].games.score;
    g.date=list[indexx].games.date;
    print();
    std::cout<<"Enter'B' To Go Back"<<"\n";
    char back;
    std::cin >> back ;
    if(back=='B')
    {
        gameboard();
        return;
    }
    else
    {
        flag=1;
        return;
    }

}
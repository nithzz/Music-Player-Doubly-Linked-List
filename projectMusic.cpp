#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include<conio.h>
#include <cstdlib>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto
void gotoXY(int,int); // function defined below if this is new to you.

class Music
{
public:
    string song_name;
    Music* prev;
    Music* next;
}*head = NULL;

//prototype
void playSong(string audiofile_str);
void addSong_Beginning(string song[]);
void addSong_After(string song[]);
void addSong_ending(string song[]);
void displayPlaylist();
void deleteSong();
int numberOfSongs();
int numberOfSongs();
void swapSongs(string *a, string *b);
void shufflePlaylist();

void playSong(string audiofile_str)
{
    char block = 178;
    system("cls");
    fstream fp;
    fp.open(audiofile_str, ios::in);
    if ( !fp )
    {
       cout<<"\nAudio file couldn't run..!!"<<endl;
    }
    else
    {
         gotoXY(95,22);
         cout<<audiofile_str;
         for(int i=80; i<=120;++i)
            {
                gotoXY(i,23); cout<<"-";
            }
       gotoXY(80,24);
       cout<<block<<block;
       gotoXY(80,25);
       cout<<block<<block;
       gotoXY(95,25);
       cout<<"Playing..."<<endl;
       gotoXY(120,25);
       cout<<block<<block;
       gotoXY(120,26);
       cout<<block<<block;
       for(int i=80; i<=120;++i)
            {
                gotoXY(i,27); cout<<"-";
            }
       PlaySound(audiofile_str.c_str(), NULL, SND_SYNC);
    }
    fp.close();
    system("cls");
}

void availableSongs(string songList[])
{
    gotoXY(80,24);cout << " AVAILABLE SONGS  ";
    int y = 26;
    for(int i=0;i<5;i++)
    {
        gotoXY(84,y);cout << songList[i];
        y++;
    }
}
void addSong_Beginning (string song[])
{
    system("cls");
    char block = 178;

    Music* new_song = new Music;
    bool check = false;

    availableSongs(song);
    gotoXY(95,22); cout<<block<<block<<"  ADD SONG  "<<block<<block;
    gotoXY(80,38);cout<< "NAME OF THE SONG :  ";
    cin >> new_song->song_name;
    new_song->prev = NULL;

    for(int i=0;i<10;i++)
    {
        if(song[i]==new_song->song_name)
           check = true;
    }
    new_song->song_name.append(".wav");
    if(check)
    {
        if(head == NULL)
        {
    		head = new_song;
            new_song->next = NULL;
		}
        else
        {
    		new_song->next = head;
            head = new_song;
        }
       gotoXY(70,40);cout << " THIS SONG HAS BEEN ADDED TO YOUR PLAYLIST!! ";
    }
    else
    {
         cout << " \n\n\n\t\t\t\t\t\t\t\t\tTHIS SONG IS CURRENTLY NOT AVAILABLE IN OUR LIBRARY ";
    }
     Sleep(500);
     system("cls");

}
void addSong_After (string song[])
{
    system("cls");
    char block = 178;

    string next_song;
    Music* new_song = new Music;
    Music* temp_song = head;
    bool check = false;

    availableSongs(song);
    gotoXY(95,22); cout<<block<<block<<"  ADD SONG  "<<block<<block;
    gotoXY(80,38);cout<< "NAME OF THE SONG :  ";
    cin >> new_song->song_name;
    gotoXY(80,39);cout << "PRECEEDING SONG NAME : ";
    cin >> next_song;

    for(int i=0;i<10;i++)
    {
        if(song[i]==new_song->song_name)
           check = true;
    }
    new_song->song_name.append(".wav");
    if(check)
    {
        if(head==NULL)
        {
    		head = new_song;
            new_song->next = NULL;

		}
        else
        {
                while (temp_song->song_name != next_song )
                {
                    temp_song = temp_song -> next;
                }
            new_song->prev = temp_song;
            new_song->next = temp_song->next;
            if(temp_song->next !=NULL)
        		(temp_song->next)->prev = new_song;
            temp_song->next = new_song;
        }
        gotoXY(80,41); cout << " THIS SONG HAS BEEN ADDED TO YOUR PLAYLIST!! ";
    }
    else
    {
        cout << " \n\n\n\t\t\t\t\t\t\t\t\tTHIS SONG IS CURRENTLY NOT AVAILABLE IN OUR LIBRARY ";
    }
    Sleep(500);
    system("cls");
}

void addSong_ending(string song[])
{
    system("cls");
    char block = 178;

    Music *new_song = new Music;
    Music *currentSong;
    currentSong = head;
    bool check = false;

    availableSongs(song);
    gotoXY(95,22); cout<<block<<block<<"  ADD SONG  "<<block<<block;
    gotoXY(80,38);cout<< "NAME OF THE SONG :  ";
    cin>>new_song->song_name;
    new_song->next  = NULL;

    for(int i=0;i<10;i++)
    {
        if(song[i]==new_song->song_name)
        {
            check = true;
        }

    }
    new_song->song_name.append(".wav");
    if(check==true)
    {
        while (currentSong->next != NULL)
        {
            currentSong = currentSong->next;
        }
        new_song->prev = currentSong;
        currentSong->next = new_song;
        gotoXY(80,41); cout << " THIS SONG HAS BEEN ADDED TO YOUR PLAYLIST!! ";
    }
    else
    {
         cout << " \n\n\n\t\t\t\t\t\t\t\t\tTHIS SONG IS CURRENTLY NOT AVAILABLE IN OUR LIBRARY ";
    }
    Sleep(500);
    system("cls");
}

void displayPlaylist()
{
  system("cls");
  char block = 178;
  int i=24;
  Music *currentSong;
  currentSong  = head;
  gotoXY(95,22); cout<<block<<block<<" YOUR PLAYLIST "<<block<<block;
  for(int j=80; j<=130;++j)
    {
        gotoXY(j,23); cout<<"-";
    }
  	while (currentSong != NULL)
  	{
     		gotoXY(80,i);cout<<block;
    		gotoXY(100,i); cout<<currentSong->song_name;
     		gotoXY(130,i);cout<<block;
     		currentSong = currentSong->next;
     		i+=2;
  	}
  	for(int j=80; j<=130;++j)
    {
        gotoXY(j,i-1); cout<<"-";
    }
    sleep(4);
    system("cls");
}

void deleteSong()
{
    system("cls");
    char block = 178;
	Music *currentSong,*dummySong;
  currentSong = head;
  string songName;
  gotoXY(95,22); cout<<block<<block<<" DELETE SONG "<<block<<block;
  gotoXY(90,24); cout<<" SONG TO BE DELETED : ";
  cin>>songName;
  songName.append(".wav");
  if(songName == head->song_name)
  {
      head = currentSong->next;
      currentSong->prev = NULL;
  }
  else
  {
     while (currentSong->song_name != songName)
    {
    dummySong = currentSong;
    currentSong = currentSong->next;
    }
  dummySong->next = currentSong->next;
 (currentSong->next)->prev = dummySong;
  }
 gotoXY(95,26); cout<<" SONG DELETED ";
 sleep(500);
 system("cls");
}

int numberOfSongs()
{
		Music* temp_song = head;
    int n = 0;
    while(temp_song != NULL)
    {
    		n++;
        temp_song  =  temp_song->next;
    }
    return n;
}
void swapSongs(string *a, string *b)
{
    string temp = *a;
    *a = *b;
    *b = temp;
}
void shufflePlaylist(Music** head)
{
     Music* temp_song = *head;
		int no_songs = numberOfSongs();
    int i = 0;
    cout<<no_songs;
    string shuffleArray[no_songs];
    while(temp_song!= NULL)
    {
    		shuffleArray[i] = (temp_song)->song_name;
        temp_song = (temp_song)->next;
        i++;
    }
    /*for(int i=0;i<no_songs;i++)
    {
        cout<<shuffleArray[i]<<endl;
    }*/
    srand (time(0));
    for (int i = no_songs-1; i > 0 ; i--)
    {
    		int j = rand() % (i+1);
    		//cout<<j<<endl;
        swapSongs(&shuffleArray[i],&shuffleArray[j]);
    }
    Music* startShuffle = new Music;
    Music* tempShuffle = new Music;
    startShuffle->song_name = shuffleArray[0];
    startShuffle->prev = startShuffle->next = NULL; //????
    tempShuffle = startShuffle;
    for ( int i = 1; i < no_songs ;i++)
    {
    		Music* shuffleSong = new Music;
        shuffleSong->next = NULL;
        shuffleSong->song_name = shuffleArray[i];
        tempShuffle->next = shuffleSong;
        shuffleSong->prev = tempShuffle;

        tempShuffle = shuffleSong;
    }
    //cout<< "\nHERE'S YOUR SHUFFLED PLAYLIST"<<endl;
    *head = startShuffle;
     displayPlaylist();

}
void songgggg()
{
    static Music *currentSong = head;
    Music *current;
    current = head;
    //cout<<currentSong->song_name;
    static  string name = currentSong->song_name;
    while(current->song_name != name)
        {
          current = current->next;
        }
        playSong(current->song_name);
        if(current->next != NULL)
        {
             currentSong = currentSong->next;
            name = currentSong->song_name;
        }
      system("cls");
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
}


int main()
{
    int choice;
    char response;
    int menu_item=0, run, x=24;
		bool running = true;
	  char block = 178;
    Music *currentSong;
    currentSong = head;

    string songList[10] = {"song1","song2","song3","song4","song5"};
    while(running)
    {
        gotoXY(95,22); cout << block<<block<<"  MUSIC APP  "<< block<<block;

        gotoXY(70,24);cout<<" INSERT A SONG AT THE BEGINNING OF THE PLAYLIST ";
        gotoXY(70,25);cout<<" INSERT A SONG AT THE END OF THE PLAYLIST ";
        gotoXY(70,26);cout<<" INSERT A SONG INBETWEEN THE PLAYLIST ";
        gotoXY(70,27);cout<<" SHUFFLE THE PLAYLIST";
        gotoXY(70,28);cout<<" DELETE A SONG ";
        gotoXY(70,29);cout<<" DISPLAY PLAYLIST ";
        gotoXY(70,30);cout<<" PLAY SONG ";
        gotoXY(70,31);cout<<" CLOSE THE PLAYLIST ";
        system("pause>nul");
        if(GetAsyncKeyState(VK_DOWN) && x != 31) //down button pressed
			{
				gotoXY(68,x); cout << "  ";
				x++;
				gotoXY(68,x); cout << "->";
				menu_item++;
				continue;

			}
			if(GetAsyncKeyState(VK_UP) && x != 24) //up button pressed
			{
				gotoXY(68,x); cout << "  ";
				x--;
				gotoXY(68,x); cout << "->";
				menu_item--;
				continue;
			}
			if(GetAsyncKeyState(VK_RETURN))
            {
                switch(menu_item)
                {
                case 0:
                    {

                        addSong_Beginning(songList);
                        break;
                    }
                case 1:
                    {

                        addSong_ending(songList);
                        break;
                    }
                case 2:
                    {

                        addSong_After(songList);
                        break;
                    }
                case 3:
                    {

                        shufflePlaylist(&head);
                        break;
                    }
                case 4:
                    {
                        deleteSong();
                        break;
                    }
                case 5:
                    {
                        displayPlaylist();
                         break;

                    }
                case 6:
                    {
                        songgggg();
                        break;
                    }
                case 7:
                    {

                        running = false;
                        break;
                    }

                }
            }
    }

  return 0;

}










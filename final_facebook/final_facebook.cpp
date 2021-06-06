#include<iostream>
#include<fstream>
#include<cstring>
#include<string.h>
using namespace std;

void stringcopy(char * s1, char * s2)
{
	int i;
	for ( i = 0; s1[i] != 0; i++)
	{
		s1[i] = s2[i];
	}
	s1[i] = '\0';
}



class Object
{
private:
	char * id;
public:
	Object()
	{
		id = nullptr;
	}

	~Object()
	{
		delete[] id;
	}

	void print_Object()
	{
		cout << id;
	}

	Object(char * _id)
	{
		if (_id != nullptr)
		{
			id = new char[strlen(_id) + 1];
		stringcopy(id, _id);
		}
	}

	char * getid()
	{
		return id;
	}

	void setid(char * _id)
	{
		if (id != nullptr)
		{
			delete[] id;
		}

		id = new char[strlen(_id) + 1];
		stringcopy(id, _id);
	}

};


class Date
{
private:
	int day;
	int month;
	int year;
	

public:

	static Date currentdate;
	
	Date()
	{
		day = 0;
		month = 0;
		year = 0;
	}

	~Date()
	{
    
		//nothing to dealloacate
		 
	}
	
	bool operator ==(Date rhs)
	{
		if ((day == rhs.day || day == rhs.day - 1) && (month == rhs.month) && (year == rhs.year))
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	void printdate()
	{
		cout << day <<" /" << month <<" /"<< year;

	}

	void setcurrentdate(int d, int m, int y)
	{
		currentdate.day = d;
		currentdate.month = m;
		currentdate.year = y;

	}


	void loaddate(ifstream & fin)
	{
		fin >> day;
		fin >> month;
		fin >> year;
	}

	Date getcurrentdate()
	{
		return currentdate;
	}


};

Date Date::currentdate(1, 1, 1960);

class Page :public Object
{
private:
	char * title;
	
public:
	Page()
	{
		title = 0;
	}

	~Page()
	{

		cout << "destructor of Page calles " << endl;
		if (title != 0)
		{
			delete[] title;
		}
	
	}

	void print_page()
	{
		print_Object();
		cout << " " << title << endl;
	}

	void printtitle()
	{
		cout << title;
	}


	void loaddataofpages(ifstream & fin)
	{
		char buffer[50];
		fin >> buffer;
		setid(buffer);

		fin.getline(buffer, 50);
		title = new char(strlen(buffer) + 1);
		stringcopy(title, buffer);

	}


};
 

class User :public Object
{
public:
	char * fname;
	char * lname;

	User ** friendlist;
	Page ** likedpages;


	//temporary storage for friends
	char ** temp_friends;

	//temporary storage for pages
	char ** temp_pages;

	Post ** timelinepost;

public:

	User()
	{
		fname = 0;
		lname = 0;

		friendlist = 0;
		likedpages = 0;

		temp_friends = 0;
		temp_pages = 0;
	}

	~User()
	{
		if (lname != 0)
			delete[] lname;

		if (fname != 0)
			delete[] fname;

		if (friendlist != 0)
			delete[] friendlist;

		if (likedpages != 0)
			delete[] likedpages;
		if (timelinepost != 0)
		{
			for (int i = 0; i < 10; i++)
			{
				if (timelinepost[i] != 0)
				{
					delete[i] timelinepost;
				}

			}

			delete[] timelinepost;
		}

	}

	char ** getlikedpagesid()
	{
		return temp_pages;
	}


	void setpagelist(Page ** _pagelist)
	{
		likedpages = _pagelist;
	}

	void settemppageid(char ** _temp_pages)
	{
		temp_pages = _temp_pages;
	}


	char ** getfriendsid()
	{
		return temp_friends;
	}

	void setfriendlist(User ** _friendlist)
	{
		friendlist = _friendlist;
	}

	void settempfiendid(char ** _temp_friends)
	{
		temp_friends = _temp_friends;
	}

	void print_user()
	{
		print_Object();
		cout << fname << " " << lname << endl;
	}

	void printing_name()
	{
		cout << fname << " " << lname;
	}

	


	void viewfriendlist()
	{
		cout << "----------------------------------------------" << endl;
		cout << "COMMAND===VIEW FRIENDLST" << endl;
		cout << fname << " " << lname << "----FRIENDLIST" << endl;
		if (friendlist != 0)
		{
			for (int i = 0; i < 10; i++)
			{
				if (friendlist[i] != 0)
				{
					friendlist[i]->print_user();
				}
			}
		}
	}



	void viewpageliked()
	{
		cout << "----------------------------------------------" << endl;
		cout << "COMMAND===VIEW LIKED PAGES" << endl;
		cout << fname << " " << lname << "----LIKED PAGES" << endl;

		if (likedpages != 0)
		{
			for (int i = 0; i < 10; i++)
			{
				if (likedpages[i] != 0)
				{
					likedpages[i]->print_page();
				}
			}
		}



	}


	void loaddataofusers(ifstream & fin)
	{

		int lenght = 0;

		char buffer[50];

		// id
		fin >> buffer;
		setid(buffer);

		//fname
		fin >> buffer;
		lenght = strlen(buffer);
		fname = new char[lenght + 1];
		stringcopy(fname, buffer);

		//lname
		fin >> buffer;
		lenght = strlen(buffer);
		lname = new char[lenght + 1];
		stringcopy(fname, buffer);

		temp_friends = new char*[10];

		fin >> buffer;
		//coping the friend list id's
		for (int i = 0; buffer[0] != '-' || buffer[1] != '1'; i++)
		{

			temp_friends[i] = new char(strlen(buffer) + 1);
			stringcopy(temp_friends[i], buffer);
			fin >> buffer;
		}

		//coping the pages list
		temp_pages = new char *[10];
		fin >> buffer;

		for (int i = 0; buffer[0] != '-' || buffer[1] != '1'; i++)
		{
			temp_pages[i] = new char(strlen(buffer) + 1);
			stringcopy(temp_pages[i], buffer);
			fin >> buffer;
		}




	}


	void settimelinepost(Post * p)
	{
		if (timelinepost != 0)
		{
			timelinepost = new Post*[10];
		}

		for (int i = 0; i < 10; i++)
		{
			timelinepost[i] = p;
		}
	}

	void viewhome()
	{
		cout << "----------------------------------------------" << endl;
		cout << "COMMAND===VIEW HOME" << endl;
		cout << fname << " " << lname << "----LIKED PAGES" << endl;
		cout << "show the post's between " << Date::getcurrentdate() << "and" << Date::getcurrentdate() - 1 << endl;

		if (friendlist != 0)
		{
			for (int i = 0; friendlist[i] != 0; i++)
			{
		         	 
			}
		}


		if (likedpages != 0)
		{
			for (int i = 0; likedpages[i] != 0; i++)
			{

			}
		}

	}


	void viewtimeline()
	{
		cout << "----------------------------------------------" << endl;
		cout << "COMMAND===VIEW TIMELINE" << endl;
		cout << fname << " " << lname<< endl;


		if (timelinepost != 0)
		{
			for (int i = 0; timelinepost[i] != 0; i++)
			{
				timelinepost[i]->print_post;
			}

		}

	}



};

class Post :public Object
{
private:
	char * discription;
	Date Time;
	Object ** likeby;
	Object * sharedby;
	Comment ** comment;

private:
	Post()
	{
		discription = 0;
		likeby = 0;
		sharedby = 0;
	}
	



public:
	void loaddataofposts(ifstream & fin)
	{
		char buffer[100];
		fin >> buffer;
		//set the id
		setid(buffer);

		//receving time from file
		Time.loaddate(fin);

		fin.getline(buffer, 100);
		discription = new char[strlen(buffer) + 1];
		stringcopy(discription, buffer);

	}


	~Post()
	{
		if (discription != 0)
		{
			delete[] discription;
		}

		if (likeby != 0)
		{
			delete[] likeby;
				 
		}


	}

	void setlikedby(Object * l)
	{
		if (likeby != 0)
		{
			likeby = new Object *[10];

		}

		for (int i = 0; i < 10; i++)
		{
			if (likeby != 0)
			{
				likeby[i] = l;
			}
		}
	}


	void setsharedby(Object * _sharedby)

	{
		sharedby = _sharedby;
	}

	void setcomment(Comment * _comment)
	{
		if (comment!=0)
		{
			comment = new Comment*[10];
		}

		for (int i = 0; i < 10; i++)
		{
			if (_comment != 0)
			{
				comment[i] = _comment;
			}
		}

	}

	void print_post()
	{



		cout << discription;
		cout << Time.printdate << " ";

		if (comment != 0)
		{
			for (int i = 0; comment[i] != 0; i++)
			{
				comment[i]->print_comment;
			}
		}

	}

};


class Comment :public Object
{
private:
	char * text;
	Object * commentby;
public:
	Comment()
	{
		text = 0;
		commentby = 0;
	}

	~Comment()
	{
		if (text != 0)
		{
			delete[] text;
		}
	}

	void print_comment()
	{

		commentby->print_Object();//gives the id who comment it
		cout << "write" << text;

	}

	void setcommentby(Object * _commentby)
	{
		commentby = _commentby;
	}

	Object * getcomment()
	{
		return commentby;
	}

	void settext(char * t)
	{
		text = t;
	}

	Comment(char * str, Object * com)
	{

		//copy constructor
		text = new char(strlen(str) + 1);
		strcpy(text, str);
		commentby = com;

	}





};


class Facebook
{
private:
	Page ** pages;
	User ** users;
	Post ** posts;

	static int totalpages;
	static int totalusers;
	static int totalposts;
	static int totalcomments;
	User * currentuser;
public:

	void loaddata()
	{
		ifstream fin;
		int total = 0;
		char buffer[50] ;

		//opening the pages file
		fin.open("pages.txt");
		if (fin.is_open())
		{

			fin >> totalpages;
			pages = new Page*[totalpages];

			for (int i = 0; i < totalpages; i++)
			{
				pages[i] = new Page;
				pages[i]->loaddataofpages(fin);
			}

			fin.close();
		}

		else
		{
			cout << "error in opening the file" << endl;
		}

		//opening the users file
		fin.open("users.txt");
		if (fin.is_open())
		{
			fin >> totalusers;
			users = new User *[totalusers];
			for (int i = 0; i < totalusers; i++)
			{
				users[i] = new User;
				users[i]->loaddataofusers(fin);
			}

			fin.close();

		}

		else
		{
			cout << "ERROR IN Opeing the fike" << endl;
		}



		//opening the posts file
		fin.open("posts.txt");


		if (fin.is_open())
		{

			fin >> totalposts;
			posts = new Post *[totalposts];

			for (int p = 0; p < totalposts; p++)
			{
				posts[p] = new Post;
				posts[p]->loaddataofposts(fin);

				//for share by
				fin >> buffer;
				for (int j = 0; j < totalusers; j++)
				{
					int temp = 0;
					temp = strcmp(users[p]->getid(), buffer);
					if (temp == 0)
					{
						posts[p]->setsharedby(users[j]);
						users[j]->settimelinepost(posts[p]);

					}
				}



				//for likers
				fin >> buffer;

				if (buffer[0] != '-' || buffer[1] != '1')
				{

					for (int k = 0; buffer[0] != '-' || buffer[1] != '1'; k++)
					{
						for (int i = 0; i < totalusers; i++)
						{
							int temp = 0;
							temp = strcmp(users[i]->getid(), buffer);
							if (temp == 0)
							{
								posts[p]->setlikedby(users[i]);
							}

						}
					}


					for (int i = 0; i < totalpages; i++)
					{
						int temp = 0;
						temp = strcmp(pages[i]->getid(), buffer);
						if (temp == 0)
						{
							posts[p]->setlikedby(pages[i]);
						}
					}

				}
			}


		}


		//opening the comments file

		fin.open("commnets.txt");
		if (fin.is_open())
		{
			fin >> totalcomments;
			char buffer[100];

			for (int i = 0; i < totalcomments; i++)
			{
				Comment * temp = new Comment;
				fin >> buffer;
				temp->setid(buffer); //setting the id

				fin >> buffer;

				for (int i = 0; i < totalposts; i++)
				{
					int temp2 = 0;
					temp2 = strcmp(posts[i]->getid(), buffer);
					if (temp2 == 0)
					{
						//linking that comment with the post
						posts[i]->setcomment(temp);
					}


				}

				fin >> buffer;
				for (int i = 0; i < totalusers; i++)
				{
					int temp3 = 0;
					temp3 = strcmp(users[i]->getid(), buffer);
					if (temp3 == 0)
					{
						//linking the connenction between who comment on it
						temp->setcommentby(users[i]);

					}
				}



				fin.getline(buffer, 100);
				temp->settext(buffer);


			}


			fin.close();

		}






		void setcurrentuser(char * str)
		{
			for (int i = 0; i < totalusers; i++)
			{
				int temp = 0;
				temp = strcmp(users[i]->getid(), str);
				if (temp == 0)
				{
					currentuser = users[i];

				}
				if (currentuser != 0)
				{

					currentuser->printing_name();
					cout << "has been successfully added as current user" << endl;
				}

			}

		}


	


		void run()
		{
			setcurrentuser("u7");

			if (currentuser != 0)
			{
				currentuser->viewfriendlist();
				currentuser->viewpageliked();
				currentuser->viewhome();
				currentuser->viewtimeline();


			}

		}



		void linking()
		{
			//linking the users with the pages

			for (int i = 0; i < totalusers; i++)
			{
				int j = 0;

				Page ** likedpages;
				char ** temppages = users[i]->getlikedpagesid();

				if (temppages[i][0] != '-' || temppages[i][1] != '1')
				{
					likedpages = new Page*[10];

					for (int i = 0; i < totalpages; i++)
					{
						int temp2 = 0;
						temp2 = strcmp(pages[i]->getid(), temppages[j]);

						if (temp2 == 0)
						{
							likedpages[i] = pages[i];
							j++;
						}

						pages[i]->setlikedpages(likedpages);

					}

				}
			}

			for (int i = 0; temppages[i][0] != '-' || temppages[i][1] != '1'; i++)
			{
				if (temppages != 0)
				{
					delete[i] temppages;
				}


			}

			delete[] temppages;


		}


		// linking users with its friends

		for (int i = 0; i < totalusers; i++)
		{
			int j = 0;


			char ** tempuser = users[i]->getid();
			User ** listfriends;


			if (tempuser[j][0] != '-' || tempuser[j][1] != '1')
			{

				listfriends = new User *[10];

				for (int i = 0; i < totalusers; i++)
				{
					int temp3 = 0;

					temp3 = strcmp(users[i]->getid(), tempuser[j]);
					if (temp3 == 0)
					{
						listfriends[i] = users[i];
						j++;

					}
					users[i]->setfriendlist(listfriends);


				}
			}

		}


		for (int i = 0; tempusers[i][0] != '-' || tempusers[i][1] != '1'; i++)
		{
			if (tempusers != 0)
			{
				delete[i]tempusers;
			}

		}

		delete[] tempusers;

	}

}




	

	~Facebook()
	{
		if (pages != 0)
		{
			for (int i = 0; i < totalpages; i++)
			{
				if (pages[i] != 0)
				{
					delete[i] pages;
				}
				delete[] pages;
			}
		}

		if (users != 0)
		{
			for (int i = 0; i < totalusers; i++)
			{
				if (users[i] != 0)
				{
					delete[i] users;
				}
				delete[] users;
			}
		}

		if (posts != 0)
		{
			delete[] posts;
		}

	}

	

};



	int	Facebook::totalpages = 0;
	int Facebook::totalusers = 0;
	int Facebook::totalposts = 0;
	int Facebook::totalcomments = 0;

	int main()
	{
		Facebook fb;
		fb.loaddata();
		fb.linkng();

		fb.run();
		system("pause");
	}

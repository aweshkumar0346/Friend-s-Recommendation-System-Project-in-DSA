#include <iostream>
#include <vector>
//#include <stdlib.h>
#include <fstream>

//#include <TIME.H>

//#include <unistd.h>
using namespace std;

// a vertex represents a person
// each vertex will have a friendlist vector/array
// a list of liked posts/array of 100
// details of vertex

// total 5 friends
//class QueueNode;
//class QueueP;
int SIZE=10;
class QueueNode{
	public:
		int fr;
		int rating;
		
		QueueNode(){}
		QueueNode(int p, int r){ fr=p;rating=r;}
};

class QueueP{
	public:
		QueueNode array[10];
		int size;
		QueueP();
		void insert(int p, int r);
		int top();
		void display();
		void dequeue();
};
QueueP::QueueP(){
	size=0;
}
void QueueP::insert(int p, int r)
{	
	size++;
	
	if(size>9)
	cout<<"Queue too full enter again"<<endl;
	
	else if(size==1)
	{  
	     QueueNode q(p,r);
		array[size]=q;
	}
	else{
	   //cout<<"÷";
	   
	QueueNode q(p,r);
	array[size]=q;
	int sizetemp=size;
	
	//heapify
	while(sizetemp>13)
	{
	if(array[sizetemp].rating>array[sizetemp/2].rating)
	{
		QueueNode temp=array[sizetemp];
		array[sizetemp]=array[sizetemp/2];
		array[sizetemp/2]=temp;
		sizetemp=sizetemp/2;
	}
	else break;
	}
	
	
}
}
int QueueP::top()
{
	return array[1].fr;
}

void QueueP::display()
{
	cout<<"Showing friends from closest friend to least close friend"<<endl;
	
	while(size>=1)
	{	
		int i=1;
		cout<<"Person "<<array[i].fr<<"with friendship score "<<array[i].rating<<endl;
		array[i]=array[size];
		size--;
		while(2*i<=size)
		{
		if(array[((2*i)+1)].rating>=array[(2*i)].rating)
		{
			QueueNode t9=array[2*i+1];
			array[2*i+1]=array[i];
			array[i]=t9;
			i=2*i+1;
		}
		else
		{
			QueueNode t9=array[2*i];
			array[2*i]=array[i];
			array[i]=t9;
			i=2*i;
		}
		}
	}
}
//class queueNode{
//	
//	public:""
class vertex
{
  public:
	string name;
	vector<int> friendRequestFrom;
	vector<int> Likedposts; // hash table
	//array of 100, if index 0 then post not liked else liked // and randomize the liked posts
	vertex();
	int friends[10]; //friends
	//void addFriend();
	//void acceptRequest();
//	void removeFriend();
	//void likePost(int p);
	//void dislikePost(int p2);
	//void sendReq();
	void NodeInfo();
};



vertex::vertex()
{
	for (int i = 0; i < SIZE; i++)
	{
		friends[i] = 0;
	}
}

void vertex::NodeInfo()
{
	cout << endl
		 << "Name : " << name << endl;
	cout << "Friend Requests : ";
	//have to edit this after making the graph
	for (int i = 0; i < friendRequestFrom.size(); i++)
	{
		cout << endl
			 << "Friend requests from person number : " << friendRequestFrom[i] << endl;
	}
	cout << "Liked posts: " << endl;
	for (int i = 0; i < Likedposts.size(); i++)
	{
		cout << endl
			 << Likedposts[i] << endl;
	}
	cout << name << " is friends with " << endl;
	for (int i = 0; i < SIZE; i++)
	{
		if (friends[i] == 1)
			cout << endl
				 << i  << endl;
	}
}

class Graph
{
  public:
	vertex friends[10];
	Graph();
	Graph(vertex *arr, int n); //weight calculator
	int weight[10][10];
	void updateWeight();
	void calculateClosest(int n1);
	void displayGraph();
	int calWeight(int i, int j);
	void addFriend(int Person);
	void acceptRequest(int Person );
	void showFriendshipLevel(int person);
	void showMutuals(int person);
};

void Graph::showFriendshipLevel(int person)
{
	QueueP q1;
	for(int i=0;i<=9;i++)
	{
		if(i==person)
		continue;
		
		if(weight[person][i]==0)
		continue;
		
		q1.insert(i,weight[person][i]);
	}
	q1.display();
	
}
void Graph::showMutuals(int person)
{
		QueueP q1;
	for(int i=0;i<=9;i++)
	{
		if(i==person)
		continue;
		
		if(weight[person][i]==0)
		continue;
		
		q1.insert(i,weight[person][i]);
	}
	int mutual=q1.top();
	cout<<"Person "<<mutual<<" is the closest friend of person "<<person<<endl;
	
	cout<<"People you may know"<<endl;
	for(int c5=0;c5<10;c5++)
	{
		if(c5==person)
		continue;
		
		if(friends[mutual].friends[c5]==1 && friends[person].friends[c5]!=1)
		cout<<endl<<"Person "<<c5<<endl;
	}
}
void Graph::acceptRequest(int Person)
{
	int temp;
	cout<<endl<<"Showing friend Requests"<<endl;
	for(int i=0;i<friends[Person].friendRequestFrom.size();i++)
	cout<<friends[Person].friendRequestFrom[i]<<endl;
	
	cout<<endl<<"Enter Person Number whose request you wanna accept"<<endl;
	
	cin>>temp;
	
		for(int i=0;i<friends[Person].friendRequestFrom.size();i++)
		{
			if(temp==friends[Person].friendRequestFrom[i])
			{
				if(friends[Person].friends[temp]==1)
				cout<<"You are already friends"<<endl;
				
				else
				{friends[Person].friends[temp]=1;
				friends[temp].friends[Person]=1;
				cout<<endl<<"Friends added\n Graph updated\n: "<<endl;
				displayGraph();
				
				}
				
			//	friendRequestFrom.erase(friendRequestFrom.begin() + temp);
				return;
			}
		}
		cout<<"You didnt get a f.riend request from them. You may send them friend request to add them\n"<<endl;
	
}
void Graph::addFriend(int Person)
{
	int f;
	cout<<"Enter the person Number you want to send friend request to : "<<endl;
	cin>>f;
	
	if(f>=SIZE||f<0)
	cout<<"Error! Invalid friend number. Enter again!!"<<endl;
	
	else
	{
		if(friends[Person].friends[f]==1)
		cout<<"You are already friends"<<endl;
		
		else
	{	friends[f].friendRequestFrom.push_back(Person);
	cout<<"Friend Request sent"<<endl;
	
	}
	}
	
}
Graph::Graph()
{
	for (int j = 0; j < SIZE; j++)
	{
		for (int k = 0; k < SIZE; k++)
		{
			weight[j][k] = 0;
		}
	}
}
Graph::Graph(vertex *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		friends[i] = arr[i];
	}

	// initializing weight to be zero

	for (int j = 0; j < SIZE; j++)
	{
		for (int k = 0; k < SIZE; k++)
		{
			weight[j][k] = 0;
		}
	}
	updateWeight();
}
int Graph::calWeight(int i, int j)
{
	int w = 0;
	// calc number of mutual friends, similar liked posts
	for (int c1 = 0; c1 < friends[i].Likedposts.size(); c1++)
	{
		for (int c2 = 0; c2 < friends[j].Likedposts.size(); c2++)
		{
			if (friends[i].Likedposts[c1] == friends[j].Likedposts[c2])
				w++;
		}
	}
	//calculate mutuals

	for (int c3 = 0; c3 < SIZE; c3++)
	{
		if (friends[i].friends[c3] == 1)
		{
			if (friends[j].friends[c3] == 1)
			{
				w++;
			}
		}
	}

	return w;
}
void Graph::updateWeight()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (j == i)
				continue;

			//another loop to check isFriend

			if (friends[i].friends[j] == 1)
			{
				weight[i][j] = calWeight(i, j) + 1;
			//	weight[i][j]=1;
			}

			//compares similar friends
			//compare similar liked posts
		}
	}
}
void Graph::displayGraph()
{	
updateWeight();
	for (int i = 0; i < SIZE; i++)
	{cout<<"\t";
		for (int j = 0; j < SIZE; j++)
		{
			cout << weight[i][j] << " ";
		}
		cout << endl;
	}
}


//		int person
//}
int main()
{
	vertex f0,f1, f2, f3, f4, f5,f6,f7,f8,f9;
	f0.name = "Saleem";
	f1.name = "Ali";
	f2.name = "Bilal";
	f3.name = "Ahmed";
	f4.name = "Hamza";
	f5.name = "Rohit";
	f6.name = "Awesh";
	f7.name = "Ahmed";
	f8.name = "Farhan";
	f9.name = "Hussain";

/*	f1.friendRequestFrom.push_back(3);
	f1.friendRequestFrom.push_back(4);

	f2.friendRequestFrom.push_back(5);
	f2.friendRequestFrom.push_back(1);

	f3.friendRequestFrom.push_back(1);
	f3.friendRequestFrom.push_back(4);

	f4.friendRequestFrom.push_back(5);
	f4.friendRequestFrom.push_back(1);

	f5.friendRequestFrom.push_back(4);
	f5.friendRequestFrom.push_back(3);
*/
	f0.friends[1] = 1;
	f0.friends[3] = 1;
	f0.friends[4] = 1;
	f0.friends[5] = 1;
	f0.friends[7] = 1;
	
	f1.friends[0] = 1;  //2
//	f1.friends[2] = 1;
	f1.friends[6] = 1;  //5
	f1.friends[8]=1;	//6
	f1.friends[9] = 1;  //5
	f1.friends[2]=1;
	
	
	f2.friends[1] = 1;  //1
	f2.friends[3] = 1;  //3
	f2.friends[5] = 1;
	f2.friends[7] = 1;  //3
	f2.friends[4] = 1;

	f3.friends[0] = 1;  //2
	f3.friends[2] = 1;  //4
	f3.friends[4] = 1;
	f3.friends[7] = 1;  //4
	f3.friends[9] = 1;

	
	
	f4.friends[0] = 1; //5
	f4.friends[2] = 1;  //3
	f4.friends[8] = 1;	//9
	f4.friends[3] = 1;  //3
	f4.friends[6] = 1;	

	
	f5.friends[0] = 1;	
	f5.friends[2] = 1;
	f5.friends[6] = 1;
	f5.friends[9] = 1;
	f5.friends[8] = 1;
	

	
	f6.friends[1] = 1;
	f6.friends[4] = 1;
	f6.friends[5] = 1;
	f6.friends[7] = 1;
	f6.friends[8] = 1;


	f7.friends[0] = 1;
	f7.friends[2] = 1;
	f7.friends[3] = 1;
	f7.friends[6] = 1;
	f7.friends[9] = 1;
	
	f8.friends[1] = 1;
	f8.friends[4] = 1;
	f8.friends[5] = 1;
	f8.friends[6] = 1;
	f8.friends[9] = 1;	
	
	
	
	f9.friends[1] = 1;
	f9.friends[3] = 1;
	f9.friends[5] = 1;
	f9.friends[7] = 1;
	f9.friends[8] = 1;
	
	ifstream f;
	int p;
	
	f.open("LikedPosts0.txt");
	while(!f.eof())
	{
		f>>p;
		f0.Likedposts.push_back(p);
	}
	f.close();

	f.open("LikedPosts1.txt");
	while(!f.eof())
	{
		f>>p;
		f1.Likedposts.push_back(p);
	}
	f.close();


	f.open("LikedPosts2.txt");
	while(!f.eof())
	{
		f>>p;
		f2.Likedposts.push_back(p);
	}
	f.close();

	f.open("LikedPosts3.txt");
	while(!f.eof())
	{
		f>>p;
		f3.Likedposts.push_back(p);
	}
	f.close();

	f.open("LikedPosts4.txt");
	while(!f.eof())
	{
		f>>p;
		f4.Likedposts.push_back(p);
	}
	f.close();

	f.open("LikedPosts5.txt");
	while(!f.eof())
	{
		f>>p;
		f5.Likedposts.push_back(p);
	}
	f.close();

	f.open("LikedPosts6.txt");
	while(!f.eof())
	{
		f>>p;
		f6.Likedposts.push_back(p);
	}
	f.close();

	f.open("LikedPosts7.txt");
	while(!f.eof())
	{
		f>>p;
		f7.Likedposts.push_back(p);
	}
	f.close();

	f.open("LikedPosts8.txt");
	while(!f.eof())
	{
		f>>p;
		f8.Likedposts.push_back(p);
	}
	f.close();

	f.open("LikedPosts9.txt");
	while(!f.eof())
	{
		f>>p;
		f9.Likedposts.push_back(p);
	}
	f.close();

	
	vertex arr[SIZE];
	arr[0]=f0;
	arr[1] = f1;
	arr[2] = f2;
	arr[3] = f3;
	arr[4] = f4;
	arr[5] = f5;
	arr[6] = f6;
	arr[7] = f7;
	arr[8] = f8;
	arr[9] = f9;
	

//	f1.NodeInfo();
//	f2.NodeInfo();
//	f3.NodeInfo();
//	f4.NodeInfo();
	Graph g1(arr, SIZE);
	g1.updateWeight();
	g1.displayGraph();
	
//	
//	
	//f1.NodeInfo();
//	for (int i=0;i<5;i++)
//cout<<g1.friends[0].friends[i];
//	g1.updateWeight();
//	g1.displayGraph();

int t3;
int t;
while(1)
{

	cout<<"\nEnter Account's Username from 0-9\n ";
	cin>>t3;
	for(int j=0;j<20;j++)
	cout<<"-_-";
	cout<<endl<<"\n\n\nEntering "<<g1.friends[t3].name<<"'s account\n";
	cout<<"1.Account's Info"<<endl;
	cout<<"2.See Friend Requests"<<endl;
	cout<<"3.Send Friend Req"<<endl;
	cout<<"4.Accept Friend's Request"<<endl;
	cout<<"5.See Liked Posts"<<endl;
	cout<<"6.Like Post"<<endl;
	cout<<"7.Show friendship Level"<<endl;
	cout<<"8.See mutual friends"<<endl;
	cout<<"9.Log Out"<<endl;
	while(1)
	{
	
	cin>>t;
	if(t==1)
	g1.friends[t3].NodeInfo();
	
	else if(t==2)
	{ cout<<"\nFriend Requests :\n";
	int jz=0;
		for(int count=0;count<g1.friends[t3].friendRequestFrom.size();count++)
	{	cout<<g1.friends[t3].friendRequestFrom[count]<<endl;
	jz++;
	}
	if(jz==0)
	cout<<"You haven't recieved any friend request yet :((((\n maybe you should send a friend request to someone\n Press 3 to send a request\n";
	}
	
	else if(t==3)
	{
		g1.addFriend(t3);
	}
	else if(t==4)
	{
		g1.acceptRequest(t3);
	}
	else if(t==5)
	{
		for (int c1 = 0; c1 < g1.friends[t3].Likedposts.size(); c1++)
		cout<<endl<<g1.friends[t3].Likedposts[c1]<<endl;
	}
	else if(t==6)
	{
		cout<<endl<<"Enter the serial number of the post you wanna like"<<endl;
		int post;
		cin>>post;
		g1.friends[t3].Likedposts.push_back(post);
		cout<<"Post Liked"<<endl;
	}
	else if(t==7)
	{	g1.updateWeight();
		cout<<"Showing Friendship level \n"<<endl;
		g1.showFriendshipLevel(t3);
		//use heap
	}
	else if(t==8)
	{	
		g1.updateWeight();
		g1.showMutuals(t3);
	}
	else
	break;
	}
	}	
	
}

// the class graph will have an array of nodes
//these nodes each will have a person and their data
//calculate (friendship)// a weighted graph
//suggest friends using heap
//log into a person
// like posts
//unlike posts
//add friends

//menu
// log into a user
//enter id and password
//if it verifies then log in
// see the following options
// like postsh
// add friends
//see mutuals



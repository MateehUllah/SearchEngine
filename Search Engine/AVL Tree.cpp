#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
//tokernizer
vector<string> tokenize(string line, char delimiter)
{
	string temp;
	vector<string> v;
	for (int i = 0; i < line.size(); i++) 
	{
		if (i != line.size() - 1) 
		{
			
			if (line[i] != delimiter)
			{
				temp = temp + line[i];
			}
			else {
		
				if (temp != "") 
				{
					v.push_back(temp);
					temp = "";
				}
			}
		}
		else {
			if (line[i] != delimiter) {
				temp = temp + line[i];
			}
			if (temp!= "") {
				v.push_back(temp);
			}
		}
	}
	return v;
}
bool checkURL(string URL)
{
	string cmp = "http://www.";
	bool flag = false;
	for (int i = 0; i < cmp.size(); i++)
	{
		if (URL[i] == cmp[i])
		{
			flag = true;
		}
		else {
			return false;
		}
	}
	return true;
}
bool CheckDigit(string keyword)
{
	if (keyword >= "0" && keyword <= "9")
	{
		return true;
	}
	else {
		return false;
	}
}
template<typename T>
class SinglyNode
{
private:
	SinglyNode<T>* Next;
	T Data;
public:
	SinglyNode()
	{
		Next = NULL;
		Data = "";
	}
	void setNext(SinglyNode<T>* Next)
	{
		this->Next = Next;
	}
	void setData(T Data)
	{
		this->Data = Data;
	}
	SinglyNode<T>* getNext()
	{
		return this->Next;
	}
	T getData()
	{
		return Data;
	}
	~SinglyNode()
	{
		if (Next != NULL)
		{
			Next = NULL;
		}
	}
};
template<class T>
class SinglyLinkedList {
private:
	SinglyNode<T>* Head;
	SinglyNode<T>* Current;
	SinglyNode<T>* LastCurrent;
public:
	SinglyLinkedList()
	{
		Head = new SinglyNode<T>();
		Head->setNext(NULL);
		Current = NULL;
		LastCurrent = NULL;
	}
	//Adding 
	void Insert(T Data)
	{
		if (Current != NULL)
		{
			SinglyNode<T>* Temp = Head->getNext();
			while (Temp != NULL)
			{
				if (Data == Temp->getData())
				{
					return;
				}
				Temp = Temp->getNext();
			}
		}
		SinglyNode<T>* Temp = new SinglyNode<T>();
		Temp->setData(Data);
		if (Current != NULL)
		{
			Temp->setNext(Current->getNext());
			Current->setNext(Temp);
			LastCurrent = Current;
			Current = Temp;
		}
		else {
			Head->setNext(Temp);
			Temp->setNext(NULL);
			Current = Temp;
			LastCurrent = Head;
		}
	}
	T getFirst()
	{
		return (Head->getNext())->getData();
	}
	void Remove()
	{
		if (Current != NULL && Current != Head)
		{
			LastCurrent->setNext(Current->getNext());
			delete Current;
			Current = LastCurrent->getNext();
		}
		else {
			cout << "List is not created yet." << endl;
		}
	}
	bool MoveNext()
	{
		if (Current == NULL)
		{
			return false;
		}
		LastCurrent = Current;
		Current = LastCurrent->getNext();
		if (Current == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	int CountNode()
	{
		SinglyNode<T>* Temp = Current;
		Current = Head;
		int sum = 0;
		for (int i = 0; MoveNext(); i++)
		{
			sum = sum + 1;
		}
		Current = Temp;
		return sum;
	}
	void Display()
	{
		Current = Head->getNext();
		int i = 1;
		while (Current != NULL)
		{
			cout << i << " " << Current->getData() << endl;
			MoveNext();
			i++;
		}
	}
};
template<typename T>
class TreeNode
{
private:
	string word;
	SinglyLinkedList<string> URL;
	TreeNode<T>* Left;
	TreeNode<T>* Right;
	int height;
public:
	TreeNode()
	{
		this->word = "";
		this->Left = NULL;
		this->Right = NULL;
		this->height = 0;
	}
	void addURL(string url)
	{
		URL.Insert(url);
	}
	SinglyLinkedList<string> getURL()
	{
		return this->URL;
	}
	void addWord(string word)
	{
		this->word = word;
	}
	string getFirstUrl()
	{
		return this->URL.getFirst();
	}
	string getWord()
	{
		return this->word;
	}
	TreeNode<T>* getRight()
	{
		return this->Right;
	}
	TreeNode<T>* getLeft()
	{
		return this->Left;
	}
	void setRight(TreeNode<T>* Right)
	{
		this->Right = Right;
	}
	void setLeft(TreeNode<T>* Left)
	{
		this->Left = Left;
	}
	void setHeight(int height)
	{
		this->height = height;
	}
	int getHeight()
	{
		return height;
	}
	bool isLeaf()
	{
		if ((this->Left == NULL) && (this->Right == NULL))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
class AVL
{
private:
	TreeNode<string>* root;
	TreeNode<string>* insert(TreeNode<string>* root, TreeNode<string>* Temp)
	{
		if (root == NULL)
		{
			root = Temp;
		}
		if (Temp->getWord().compare(root->getWord()) < 0)
		{
			root->setLeft(insert(root->getLeft(), Temp));
		}
		else if (Temp->getWord().compare(root->getWord()) > 0) {
			root->setRight(insert(root->getRight(), Temp));
		}
		else {
			string url = Temp->getFirstUrl();
			root->addURL(url);
			return root;
		}
		int balancefactor = calBalanceFactor(root);
		if (balancefactor > 1 && (Temp->getWord().compare(root->getLeft()->getWord()) < 0))
		{
			return rightRotate(root);
		}
		if (balancefactor < -1 && (Temp->getWord().compare(root->getRight()->getWord()) > 0))
		{
			return leftRotate(root);
		}
		if (balancefactor > 1 && (Temp->getWord().compare(root->getLeft()->getWord()) < 0))
		{
			root = doubleLeftRightRotate(root);
		}
		if (balancefactor < -1 && (Temp->getWord().compare(root->getRight()->getWord()) < 0))
		{
			root = doubleRightLeftRotate(root);
		}
		return root;
	}
public:
	AVL()
	{
		root = NULL;
	}
	void search(string Word)
	{
		if (root->getWord() == Word)
		{
			SinglyLinkedList<string>obj = root->getURL();
			cout << obj.CountNode() << " result(s) found" << endl;
			obj.Display();
		}
		else
		{
			TreeNode<string>* Temp1;
			TreeNode<string>* Temp2;
			Temp1 = root;
			Temp2 = root;
			while (Word.compare(Temp1->getWord()) != 0 && Temp2 != NULL)
			{
				Temp1 = Temp2;
				if (Word.compare(Temp1->getWord()) < 0)
				{
					Temp2 = Temp1->getLeft();
				}
				else
				{
					Temp2 = Temp1->getRight();
				}
			}
			if (Word.compare(Temp1->getWord()) == 0)
			{
				SinglyLinkedList<string>obj = Temp1->getURL();
				cout << obj.CountNode() << " result(s) found" << endl;
				obj.Display();
			}
			else
			{
				cout << "Result not found." << endl;
			}
		}
	}
	int height(TreeNode<string>* root)
	{
		if (root == NULL)
		{
			return -1;
		}
		else {
			int leftheight = height(root->getLeft());
			int rightheight = height(root->getRight());
			if (leftheight > rightheight)
			{ 
				return (leftheight + 1);
			}
			else {
				return (rightheight + 1);
			}
		}
	}
	void setRoot(TreeNode<string>* root)
	{
		this->root = root;
	}
	int calBalanceFactor(TreeNode<string>* root) {
		if (root == NULL)
		{
			return -1;
		}
		return height(root->getLeft()) - height(root->getRight());
	}
	TreeNode<string>* rightRotate(TreeNode<string>* root)
	{
		TreeNode<string>* k1 = root->getLeft();
		TreeNode<string>* Temp = k1->getRight();
		k1->setRight(root);
		root->setLeft(Temp);
		return k1;
	}
	TreeNode<string>* leftRotate(TreeNode<string>* root) {
		TreeNode<string>* k1 = root->getRight();
		TreeNode<string>* temp = k1->getLeft();
		k1->setLeft(root);
		root->setRight(temp);
		return k1;
	}
	 void avlInsert(string word,string url)
	 {
		 TreeNode<string>* Temp = new TreeNode<string>();
		 Temp->addWord(word);
		 Temp->addURL(url);
		 root = insert(root, Temp);
		 setRoot(root);
	 }
	 TreeNode<string>* doubleLeftRightRotate(TreeNode<string>* root)
	 {
		 root->setLeft(leftRotate(root->getLeft()));
		 return rightRotate(root);
	 }
	 TreeNode<string>* doubleRightLeftRotate(TreeNode<string>* root)
	 {
		 root->setRight(rightRotate(root->getRight()));
		 return leftRotate(root);
	 }
	~AVL()
	{
		if (root != NULL)
		{
			root = NULL;
		}
	}
	
};
void AddWord(AVL& obj, string urll, string keywordline)
{

}
void main()
{
	SinglyLinkedList<string>object;
	string url = "";
	string keywords = "";
	string word = "";
	string fileName = "";
	string id;
	string urlline;
	string keywordline;
	vector<string>str;
	cout << "Enter the file Name:" << endl << ">";
	cin >> fileName;
	AVL obj;
	ifstream fin;
	fin.open(fileName);
	if (fin)
	{
		while (!fin.eof())
		{
			fin >> id;
			fin >> urlline;
			getline(fin, keywords);
			getline(fin, keywords);
			char delimiter = ' ';
			vector<string> v;
			v = tokenize(keywords, delimiter);
			for (int i = 0; i < v.size(); i++)
			{
				obj.avlInsert(v[i], urlline);
			}
		}
			cout << "File Loaded successfully." << endl;
		fin.close();
		string key;
		cout << "Please enter a word to search:" << endl << ">";
		cin >> key;
		obj.search(key);
	}
	else {
		cout << "Sorry!!!.There is no such file.Invalid Input!!!" << endl;
	}
}

 

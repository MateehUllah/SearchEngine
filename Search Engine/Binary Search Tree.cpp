#include<iostream>
#include<fstream>
#include<string>
using namespace std;
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
	//Removing from current
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
class TreeNode {
private:
	string word;
	SinglyLinkedList<string> URL;
	TreeNode<T>* Left;
	TreeNode<T>* Right;
public:
	TreeNode()
	{
		this->word = "";
		this->Left = NULL;
		this->Right = NULL;
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
class BST
{
private:
	TreeNode<string>* root;
public:
	BST() {

		root = NULL;
	}
	//insertion
	void insert(string URL, string keyword)
	{
		TreeNode<string>* Temp = new TreeNode<string>();
		Temp->addURL(URL);
		Temp->addWord(keyword);
		if (root != NULL)
		{
			TreeNode<string>* Temp1;
			TreeNode<string>* Temp2;
			Temp1 = root;
			Temp2 = root;
			while (keyword.compare(Temp1->getWord()) != 0 && Temp2 != NULL)
			{
				Temp1 = Temp2;
				if (keyword.compare(Temp1->getWord()) < 0)
				{
					Temp2 = Temp1->getLeft();
				}
				else
				{
					Temp2 = Temp1->getRight();
				}
			}
			if (keyword.compare(Temp1->getWord()) == 0)
			{
				Temp1->addURL(URL);
				delete Temp;
			}
			else if (keyword.compare(Temp1->getWord()) < 0)
			{
				Temp1->setLeft(Temp);
			}
			else
			{
				Temp1->setRight(Temp);
			}
		}
		else
		{
			root = Temp;
		}
	}
	//searching
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
	~BST()
	{
		if (root != NULL)
		{
			root = NULL;
		}
	}
};
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
void main()
{
    string url;
    string keywords;
    string word;
	string fileName = "";
	cout << "Enter the file Name:" << endl << ">";
	cin >> fileName;
    BST obj;
    ifstream fin;
    fin.open(fileName);//"Assignment_data.txt"
    if (fin)
    {
        while (!fin.eof())
        {
            fin >> keywords;
            if (checkURL(keywords) == true)
            {
               
                url = keywords;
            }
            else if(CheckDigit(keywords)==false)
            {
               word=keywords;
            }
            
            obj.insert(url, word);
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
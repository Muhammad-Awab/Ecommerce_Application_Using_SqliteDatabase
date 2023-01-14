#pragma once

using namespace std;
class bucket
{
	int data;
	bucket* link;
public:
	bucket()
	{
		data = 0;
		link = NULL;
	}
	void setdata(int d)
	{
		data = d;
	}
	void setlink(bucket *b)
	{
		link = b;
	}
	int getdata()
	{
		return data;
	}
	bucket* getlink()
	{
		return link;
	}
};
class BUC
{
	bucket* top;
public:
	BUC()
	{
		top = NULL;
	}
	void push(int data)
	{
		bucket* temp;
		temp = new bucket();
		if (!temp) {
			cout << "\nHeap Overflow";
			exit(1);
		}
		temp->setdata(data);

		temp->setlink(top);
		top = temp;
	}
	int isEmpty()
	{
		return top == NULL;
	}
	int peek()
	{
		if (!isEmpty())
		{
			return top->getdata();
		}
		else
		{
			exit(1);
		}
	}
	void bpop()
	{
		bucket* temp;
		if (top == NULL) \
		{
			cout << "\nStack Underflow" << endl;
			exit(1);
		}
		else
		{
			temp = top;
			top = top->getlink();
			temp->setlink(NULL);
			free(temp);
		}
		cout << "Your Trolli No is :" << top->getdata() << endl;
		cout << "                  ___" << endl;
		cout << "                 /  |" << endl;
		cout << "  ______________/   --" << endl;
		cout << " |___/__ /___/_|     " << endl;
		cout << " |__/___/___/__|     " << endl;
		cout << " |_/___/___/___|     " << endl;
		cout << "    _______/         " << endl;
		cout << "     O   O           " << endl;
	}
	void bdisplay()
	{
		bucket* temp;
		if (top == NULL)
		{
			cout << "\nStack Underflow";
			exit(1);
		}
		else
		{
			temp = top;
			while (temp != NULL)
			{
				cout << temp->getdata() << " ";
				temp = temp->getlink();
			}
		}
	}
};


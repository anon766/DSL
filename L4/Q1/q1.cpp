# include <bits/stdc++.h>
using namespace std;
class Node
{
	public: 
		Node* child[26];
		bool end;
		string definition;
		Node()
		{
			for(int i=0; i<26; i++)
				child[i]=NULL;
			end=false;
		}
};
class Trie
{
	public:
		Node* root;
		Trie()
		{
			root=new Node();
		}
		void insert(string word, string definition)
		{
			Node* temp=root;
			for(int i=0; i<word.length(); i++)
			{
				int index=word[i]-'A';
				if(temp->child[index]==NULL)
					temp->child[index]=new Node();
				temp=temp->child[index];
			}
			temp->end=true;
			temp->definition=definition;
		}
		void search(string word)
		{
			Node* temp=root;
			transform(word.begin(), word.end(), word.begin(), ::toupper);
			for(int i=0; i<word.length(); i++)
			{
				int index=word[i]-'A';
				if(temp->child[index]==NULL)
					break;
				temp=temp->child[index];
			}
			if(temp->end)
			{
				cout<<temp->definition<<"\n";
				return;
			}
			cout<<"Invalid word\n";
		}
};
int main()
{
	Trie dictionary;
	ifstream fin("L4_P1_input.csv");
	int a=1;
	string input,word,definition;
	while(getline(fin, input, ';'))
	{
		word=input;
		getline(fin, input, '\r');
		definition=input;
		dictionary.insert(word, definition);
	}
	fin.close();
	cout<<"Enter word: ";
	cin>>word;
	dictionary.search(word);
}
		
	

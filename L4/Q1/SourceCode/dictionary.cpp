#include "dictionary.h"
#include "ui_dictionary.h"
#include <bits/stdc++.h>
/**
 * Initalises the UI and connects the seach button to the search function.
 */
Dictionary::Dictionary(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dictionary)
{
    ui->setupUi(this);
    //QPushButton ok;
    //ok = Dictionary::findChild<QPushButton>("Search");
    connect(ui->Input, SIGNAL(returnPressed()), ui->pushButton, SIGNAL(clicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(searchPressed()));
}
/**
 * Destructor for the UI.
 */
Dictionary::~Dictionary()
{
    delete ui;
}
/**
 * Calls the search function upon receiving text and outputs the meaning.
 */
void Dictionary::searchPressed()
{
    QString word=ui->Input->text();
    QString meaning=search(word);
    ui->Output->setPlainText(meaning);
}
/**
 * Inserts a word into the trie.
 * @param word The word to be inserted
 * @param definition The definition of the word to be outputted
 */
void Trie::insert(QString word, QString definition)
{
    Node* temp=root;
    for(int i=0; i<word.length(); i++)
    {
        qint8 index=word[i].toLatin1()-65;
        if(temp->child[index]==nullptr)
            temp->child[index]=new Node();
        temp=temp->child[index];
    }
    temp->end=true;
    temp->definition=definition;
}
/**
 * Seaches a word in the dictionary and returns its meaning.
 * @param word The word whose definition is to be outputted.
 */
QString Trie::search(QString word)
{
    Node* temp=root;
    word=word.toUpper();
    for(int i=0; i<word.length(); i++)
    {
        int index=word[i].toLatin1()-'A';
        if(temp->child[index]==nullptr)
            break;
        temp=temp->child[index];
    }
    if(temp->end)
    {
        return temp->definition;
    }
    return "Invalid word";
}

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QMainWindow>

namespace Ui {
class Dictionary;
}

class Node
{
    public:
        Node* child[26];
        bool end;
        QString definition;
        Node()
        {
            for(int i=0; i<26; i++)
                child[i]=nullptr;
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
        void insert(QString word, QString definition);
        QString search(QString word);

};


class Dictionary : public QMainWindow, public Trie
{
    Q_OBJECT

public:
    explicit Dictionary(QWidget *parent = nullptr);
    ~Dictionary();

private:
    Ui::Dictionary *ui;
private slots:
    void searchPressed();
};

#endif // DICTIONARY_H


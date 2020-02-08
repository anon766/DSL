#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QMainWindow>

namespace Ui {
class Dictionary;
}
/**
 * Defines a node of the trie.
 */
class Node
{
    public:
        Node* child[26];//!<All possible 26 letters that follow
        bool end;//!<Checks whether the end of the word has been reached.
        QString definition;//!<Stores the definition of the word.
        Node()
        {
            for(int i=0; i<26; i++)
                child[i]=nullptr;
            end=false;
        }
};
/**
 * The trie that contains the root node to the dictionary.
 */
class Trie
{
    public:
        Node* root;//!<root of the trie.
        Trie()
        {
            root=new Node();
        }
        void insert(QString word, QString definition);
        QString search(QString word);

};

/**
 * Class of UI.
 */
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


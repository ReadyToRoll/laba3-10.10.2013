#include <iostream>
#include <stdlib.h>

using namespace std;

struct node
{
    int n;
    int count;
    node*left,*right;
};

class Tree
{

public:
    node*root;
    Tree();
    Tree(int t);
    void delTree(node *wer);
    ~Tree();
    void push(node*&wer,int data);// Вставка элемента в дерево
    void show(node*wer);          // Вывод дерева на экран
    void Union(Tree &b);    //объединение
    void Union1(node*wer,Tree &buf);
    void difference(Tree &b);    //разность
    void difference1(node*wer,Tree &buf, Tree &tr2);
    void interseption(Tree &b);    //пересечение
    void interseption1(node*wer,Tree &buf, Tree &tr2);
    void interseption2(node*wer,Tree &buf, node*root);
    node*check(node*wer,int key);
};

node* Tree::check(node*wer,int key)
{
    if(wer==0) return 0;
    else if(key<wer->n) return check(wer->left,key);
    else if(key>wer->n) return check(wer->right,key);
    else return wer;
}

Tree::Tree(int t)
{
    root=0;
    for(int i=0; i<t; i++)
    {
        int k=rand()%100;
        if(check(root,k)==0)
            push(root,k);
        else
            t++;
    }
}

Tree::Tree()
{
    root=0;
}

Tree::~Tree()
{
    delTree(root);
}

void Tree::Union(Tree &tr2)
{
    Tree buf;
    Union1(root,buf);
    Union1(tr2.root,buf);
    cout<<endl<<"Union:"<<endl;
    buf.show(buf.root);
    cout<<endl<<endl;
    buf.~Tree();
}

void Tree::Union1(node*wer,Tree &buf)
{
    if(wer!=0)
    {
        Union1(wer->left,buf);
        push(buf.root,wer->n);
        Union1(wer->right,buf);
    }
}

void Tree::difference(Tree &tr2)
{
    Tree buf;
    difference1(root,buf,tr2);
    cout<<endl<<"difference:"<<endl;
    buf.show(buf.root);
    cout<<endl<<endl;
    buf.~Tree();
}

void Tree::difference1(node*wer,Tree &buf,Tree &tr2)
{
    if(wer!=0)
    {
        difference1(wer->left,buf,tr2);
        if(tr2.check(tr2.root,wer->n)==0)
            push(buf.root,wer->n);
        difference1(wer->right,buf,tr2);
    }
}

void Tree::interseption(Tree &tr2)
{
    Tree buf;
    interseption1(root,buf,tr2);
    interseption2(tr2.root,buf,root);
    cout<<endl<<"Interseption:"<<endl;
    buf.show(buf.root);
    cout<<endl<<endl;
    buf.~Tree();
}

void Tree::interseption1(node*wer,Tree &buf,Tree &tr2)
{
    if(wer!=0)
    {
        interseption1(wer->left,buf,tr2);
        if(tr2.check(tr2.root,wer->n)!=0)
            push(buf.root,wer->n);
        interseption1(wer->right,buf,tr2);
    }
}

void Tree::interseption2(node*wer,Tree &buf,node*root)
{
    if(wer!=0)
    {
        interseption2(wer->left,buf,root);
        if(check(root,wer->n)!=0)
            push(buf.root,wer->n);
        interseption2(wer->right,buf,root);
    }
}

void Tree::delTree(node *wer)
{
    if(root!=0)
    {
        if(wer->left!=0)delTree(wer->left);
        if(wer->right!=0)delTree(wer->right);
        delete wer;
    }
}
void Tree::push(node*&wer,int data)
{
    if(wer==0)
    {
        wer=new node;
        wer->n=data;
        wer->left=0;
        wer->right=0;
        wer->count=1;
    }
    else if(data<wer->n)push(wer->left,data);
    else if(data>wer->n)push(wer->right,data);
    else wer->count++;
}

void Tree::show(node*wer)
{
    if(wer!=0)
    {
        show(wer->left);
        cout<<wer->n<<" ";
        show(wer->right);
    }
}

int main()
{
    int w=0,n;
    cout<<"Input a size of set: ";
    cin>>n;
    Tree tr(n);
    Tree tr2(n);
    do
    {
        cout<<"select the required operation:"<<endl;
        cout<<" 1 - push element to set"<<endl;
        cout<<" 2 - show set"<<endl;
        cout<<" 3 - is in set"<<endl;
        cout<<" 4 - union"<<endl;
        cout<<" 5 - difference"<<endl;
        cout<<" 6 - interception"<<endl;
        cout<<" 8 - exit"<<endl<<endl;
        cin>>w;
        switch(w)
        {
        case 1:
            int data;
            cout<<"Enter value ";
            cin>>data;
            if(tr.check(tr.root,data)!=0)
                cout<<"value already in set"<<endl;
            else
                tr.push(tr.root,data);
            break;
        case 2:
            if(tr.root==0)
                cout<<"First Set empty";
            else
            {
                cout<<"Set 1:"<<endl;
                tr.show(tr.root);
            }
            cout<<endl<<endl;
            if(tr2.root==0)
                cout<<"Second Set empty";
            else
            {
                cout<<"Set 2:"<<endl;
                tr2.show(tr2.root);
            }
            cout<<endl<<endl;
            break;
        case 3:
        {
            if(tr.root==0)
                cout<<"Tree empty";
            else
            {
                node *u;
                int key;
                cout<<"enter value to check: ";
                cin>>key;
                if((u=tr.check(tr.root,key))!=0)
                {
                    cout<<u->count<<" piece checked"<<endl<<endl;
                }
                else cout<<"Nothing";
            }
            break;
        }
        case 4:
        {
            cout<<"Set 1:"<<endl;
            tr.show(tr.root);
            cout<<endl<<"Set 2:"<<endl;
            tr2.show(tr2.root);
            tr.Union(tr2);
            break;
        }
        case 5:
        {
            cout<<"Set 1:"<<endl;
            tr.show(tr.root);
            cout<<endl<<"Set 2:"<<endl;
            tr2.show(tr2.root);
            tr.difference(tr2);
            break;
        }
        case 6:
        {
            cout<<"Set 1:"<<endl;
            tr.show(tr.root);
            cout<<endl<<"Set 2:"<<endl;
            tr2.show(tr2.root);
            tr.interseption(tr2);
            break;
        }
        case 8:
            break;
        }
    }
    while(w!=8);
    tr.~Tree();
    tr2.~Tree();
}

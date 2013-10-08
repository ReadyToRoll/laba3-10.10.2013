#include <iostream>
#include <stdlib.h>

using namespace std;

struct node
{
    int n;
    node*left,*right;
};

class Tree
{
private:
    node*root;
    void Union(node*wer,Tree &buf);
    void difference(node*wer,Tree &buf, Tree &tr2);
    void intersection(node*wer,Tree &buf, Tree &tr2);
    void intersection(node*wer,Tree &buf, node*root);
public:
    Tree operator+(Tree &b);
    Tree operator-(Tree &b);
    Tree operator*(Tree &b);
    Tree();
    Tree(int t);
    Tree (const Tree &ob);
    void copyTree(node *&rootnew, node *rootold);
    void delTree(node *wer);
    ~Tree();
    void push(node*&wer,int data);// Вставка элемента в дерево
    void push(int data);
    void show();          // Вывод дерева на экран
    void show(node*wer);
    node*check(int key);
    node*check(node*wer,int key);
    bool is_empty();
    Tree& operator = (const Tree &ob);
};

Tree& Tree::operator = (const Tree &ob)
{
    if(this==&ob) return *this;
    delTree(root);
    copyTree(root,ob.root);
    return *this;
}

Tree::Tree (const Tree &ob)
{
    if (ob.root==0)
        root=0;
    else
    {
        root=new node;
        root->n=ob.root->n;
        root->left=0;
        root->right=0;
        copyTree(root, ob.root);
    }
}

void Tree::copyTree(node *&rootnew, node *rootold)
{
    if (rootold->left!=0)
    {
        push(rootnew, (rootold->left)->n);
        copyTree(rootnew, rootold->left);
    }
    if (rootold->right!=0)
    {
        push(rootnew, (rootold->right)->n);
        copyTree(rootnew, rootold->right);
    }
}
node* Tree::check(int key)
{
    if(root==0) return 0;
    else if(key<root->n) return check(root->left,key);
    else if(key>root->n) return check(root->right,key);
    else return root;
}

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

Tree Tree::operator+(Tree &tr2)
{
    Tree buf;
    Union(root,buf);
    Union(tr2.root,buf);
    return buf;
}

void Tree::Union(node*wer,Tree &buf)
{
    if(wer!=0)
    {
        Union(wer->left,buf);
        push(buf.root,wer->n);
        Union(wer->right,buf);
    }
}

Tree Tree::operator-(Tree &tr2)
{
    Tree buf;
    difference(root,buf,tr2);
    return buf;
}

void Tree::difference(node*wer,Tree &buf,Tree &tr2)
{
    if(wer!=0)
    {
        difference(wer->left,buf,tr2);
        if(tr2.check(tr2.root,wer->n)==0)
            buf.push(wer->n);
        difference(wer->right,buf,tr2);
    }
}

Tree Tree::operator*(Tree &tr2)
{
    Tree buf;
    intersection(root,buf,tr2);
    intersection(tr2.root,buf,root);
    return buf;
}

void Tree::intersection(node*wer,Tree &buf,Tree &tr2)
{
    if(wer!=0)
    {
        intersection(wer->left,buf,tr2);
        if(tr2.check(tr2.root,wer->n)!=0)
            push(buf.root,wer->n);
        intersection(wer->right,buf,tr2);
    }
}

void Tree::intersection(node*wer,Tree &buf,node*root)
{
    if(wer!=0)
    {
        intersection(wer->left,buf,root);
        if(check(root,wer->n)!=0)
            push(buf.root,wer->n);
        intersection(wer->right,buf,root);
    }
}

void Tree::delTree(node *wer)
{
    if(wer==0)return;
    else if((wer->left==0)&&(wer->right==0))
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
    }
    else if(data<wer->n)push(wer->left,data);
    else if(data>wer->n)push(wer->right,data);
}

void Tree::push(int data)
{
    if(root==0)
    {
        root=new node;
        root->n=data;
        root->left=0;
        root->right=0;
    }
    else if(data<root->n)push(root->left,data);
    else if(data>root->n)push(root->right,data);
}

void Tree::show()
{
    if(root!=0)
    {
        show(root->left);
        cout<<root->n<<" ";
        show(root->right);
    }
}

bool Tree::is_empty()
{
    if(root==0)
        return true;
    else
        return false;
}

void Tree::show(node*root)
{
    if(root!=0)
    {
        show(root->left);
        cout<<root->n<<" ";
        show(root->right);
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
        cout<<" 6 - intersection"<<endl;
        cout<<" 7 - exit"<<endl<<endl;
        cin>>w;
        switch(w)
        {
        case 1:
            int data;
            cout<<"Enter value ";
            cin>>data;
            if(tr.check(data)!=0)
                cout<<"value already in set"<<endl;
            else
                tr.push(data);
            break;
        case 2:
            if(tr.is_empty()==true)
                cout<<"First set empty";
            else
            {
                cout<<"Set 1:"<<endl;
                tr.show();
            }
            cout<<endl<<endl;
            if(tr2.is_empty()==true)
                cout<<"Second set empty";
            else
            {
                cout<<"Set 2:"<<endl;
                tr2.show();
            }
            cout<<endl<<endl;
            break;
        case 3:
        {
            if(tr.is_empty()==true)
                cout<<"Tree empty";
            else
            {
                node *u;
                int key;
                cout<<"enter value to check: ";
                cin>>key;
                if((u=tr.check(key))!=0)
                {
                    cout<<"Founded"<<endl<<endl;
                }
                else cout<<"Nothing";
            }
            break;
        }
        case 4:
        {
            cout<<"Set 1:"<<endl;
            tr.show();
            cout<<endl<<"Set 2:"<<endl;
            tr2.show();
            cout<<endl;
            Tree tr3;
            tr3=tr+tr2;
            tr3.show();
            break;
        }
        case 5:
        {
            cout<<"Set 1:"<<endl;
            tr.show();
            cout<<endl<<"Set 2:"<<endl;
            tr2.show();
            cout<<endl;
            Tree tr3;
            tr3=tr-tr2;
            tr3.show();
            break;
        }
        case 6:
        {
            cout<<"Set 1:"<<endl;
            tr.show();
            cout<<endl<<"Set 2:"<<endl;
            tr2.show();
            cout<<endl;
            Tree tr3;
            tr3=tr*tr2;
            tr3.show();
            break;
        }
        case 7:
            break;
        }
    }
    while(w!=7);
}

/*
 * @Author: Eternal4869 
 * @Date: 2021-11-02 16:39:11 
 * @Last Modified by: Eternal4869
 * @Last Modified time: 2021-11-03 15:36:46
 */
#include <iostream>
using namespace std;

/*
@author         Eternal4869
Finish Time     2021-10
*/

template <class ElemType>
struct BinTreeNode
{
    ElemType data;                     //数据元素
    BinTreeNode<ElemType> *leftChild;  //左孩子指针
    BinTreeNode<ElemType> *rightChild; //右孩子指针

    //构造函数模板
    BinTreeNode();                                                                                                       //无参构造函数模板
    BinTreeNode(const ElemType &item, BinTreeNode<ElemType> *lChild = nullptr, BinTreeNode<ElemType> *rChild = nullptr); //已知元素值，指向左右孩子的指针构造一个结点
};

//二叉树结点类模板实现部分
template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode()
{
    leftChild = rightChild = nullptr; //叶子节点左右孩子都为空
}

template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode(const ElemType &item, BinTreeNode<ElemType> *lChild, BinTreeNode<ElemType> *rChild)
{
    data = item;
    leftChild = lChild;
    rightChild = rChild;
}

template <class ElemType>
class BinTree
{
private:
    //二叉树数据部分
    BinTreeNode<ElemType> *root;
    //辅助函数部分
    BinTreeNode<ElemType> *CopyTreeHelp(const BinTreeNode<ElemType> *r);                                       //复制二叉树
    void DestroyHelp(BinTreeNode<ElemType> *&r);                                                               //销毁以r为根的二叉树
    void PreOrderHelp(const BinTreeNode<ElemType> *r) const;                                                   //先序遍历
    void InOrderHelp(const BinTreeNode<ElemType> *r) const;                                                    //中序遍历
    void PostOrderHelp(const BinTreeNode<ElemType> *r) const;                                                  //后续遍历
    int HeightHelp(const BinTreeNode<ElemType> *r) const;                                                      //返回二叉树的高
    int NodeCountHelp(const BinTreeNode<ElemType> *r) const;                                                   //返回二叉树的结点个数
    int LeavesCountHelp(const BinTreeNode<ElemType> *r) const;                                                 //返回二叉树叶子结点数
    BinTreeNode<ElemType> *ParentHelp(const BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const; //返回cur的双亲

    //二叉树方法声明及重载编译系统默认方法声明
public:
    BinTree();                                                                 //无参构造函数模板
    virtual ~BinTree();                                                        //析构函数模板
    BinTreeNode<ElemType> *GetRoot() const;                                    //返回二叉树的根
    bool Empty() const;                                                        //判断二叉树是否为空
    bool GetElem(const BinTreeNode<ElemType> *cur, ElemType &e) const;         //用e返回结点cur的元素值
    bool SetElem(const BinTreeNode<ElemType> *cur, ElemType &e);               //将结点cur的值设置为e
    void PreOrder() const;                                                     //先序遍历
    void InOrder() const;                                                      //中序遍历
    void PostOrder() const;                                                    //后序遍历
    void LevelOrder() const;                                                   //二叉树的层次遍历
    int NodeCount() const;                                                     //求二叉树结点的个数
    BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *cur) const;  //返回二叉树结点cur的左孩子
    BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *cur) const; //返回二叉树结点cur的右孩子
    BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *cur) const;     //返回二叉树结点cur的双亲
    void InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e);       //为二叉树结点cur插入左孩子
    void InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e);      //为二叉树结点cur插入右孩子
    void DeleteLeftChild(BinTreeNode<ElemType> *cur);                          //删除左子树
    void DeleteRightChild(BinTreeNode<ElemType> *cur);                         //删除右子树
    int Height() const;                                                        //求二叉树的高
    int LeavesCount() const;                                                   //返回二叉树叶子结点数
    BinTree(const ElemType &e);                                                //建立以e为根的二叉树
    BinTree(const BinTree<ElemType> &copy);                                    //复制构造函数模板
    BinTree(BinTreeNode<ElemType> *r);                                         //建立以r为根的二叉树
    BinTree<ElemType> &operator=(const BinTree<ElemType> &copy);               //重载赋值函数
};

template <class ElemType>
void BinTree<ElemType>::DestroyHelp(BinTreeNode<ElemType> *&r)
{
    if (r != nullptr) //如果r不是空的
    {
        DestroyHelp(r->leftChild);  //销毁左子树
        DestroyHelp(r->rightChild); //销毁右子树
        delete r;                   //销毁根结点
        r = nullptr;
    }
}

/*
以下三种遍历，都通过递归算法实现
*/
template <class ElemType>
void BinTree<ElemType>::PreOrderHelp(const BinTreeNode<ElemType> *r) const
{
    if (r != nullptr)
    {
        cout << r->data;             //访问根结点，输出数据值
        PreOrderHelp(r->leftChild);  //遍历左子树
        PreOrderHelp(r->rightChild); //遍历右子树
    }
}

template <class ElemType>
void BinTree<ElemType>::InOrderHelp(const BinTreeNode<ElemType> *r) const
{
    if (r != nullptr)
    {
        InOrderHelp(r->leftChild);  //遍历左子树
        cout << r->data;            //访问根结点，输出数据值
        InOrderHelp(r->rightChild); //遍历右子树
    }
}

template <class ElemType>
void BinTree<ElemType>::PostOrderHelp(const BinTreeNode<ElemType> *r) const
{
    if (r != nullptr)
    {
        PostOrderHelp(r->leftChild);  //遍历左子树
        PostOrderHelp(r->rightChild); //遍历右子树
        cout << r->data;              //访问根结点，输出数据值
    }
}

/*
非递归算法
*/

template <class ElemType>
int BinTree<ElemType>::HeightHelp(const BinTreeNode<ElemType> *r) const
{
    if (r == nullptr)
    {
        return 0; //空二叉树高度为0
    }
    else
    {
        int lHeight, rHeight;
        lHeight = HeightHelp(r->leftChild);                 //左子树高度
        rHeight = HeightHelp(r->rightChild);                //右子树高度
        return (lHeight > rHeight ? lHeight : rHeight) + 1; //该二叉树的高度为左、右子树最大高度+1
    }
}

template <class ElemType>
int BinTree<ElemType>::NodeCountHelp(const BinTreeNode<ElemType> *r) const
{
    if (r == nullptr)
    {
        return 0; //空二叉树结点为0
    }
    else
    {
        return NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild) + 1; //非空二叉树结点个数为左子树、右子树结点个数之和+1
    }
}

template <class ElemType>
int BinTree<ElemType>::LeavesCountHelp(const BinTreeNode<ElemType> *r) const
//计算叶子结点辅助函数
{
    if (r == nullptr) //递归终止条件
    {
        return 0;
    }
    else
    {
        int lLeaves, rLeaves;
        lLeaves = LeavesCountHelp(r->leftChild);
        rLeaves = LeavesCountHelp(r->rightChild);
        if (r->leftChild == nullptr && r->rightChild == nullptr) //叶子节点获取数值
        {
            return lLeaves + rLeaves + 1;
        }
        else //非叶子结点获取数值
        {
            return lLeaves + rLeaves;
        }
    }
}

//TODO
template <class ElemType>
//返回cur的双亲
BinTreeNode<ElemType> *BinTree<ElemType>::ParentHelp(const BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const //unsure
{
    if (r != nullptr)
    {
        PostOrderHelp(r->leftChild);  //遍历左子树
        PostOrderHelp(r->rightChild); //遍历右子树
        if (r == cur)
        {
            return r;
        }
    }
}

template <class ElemType>
BinTree<ElemType>::BinTree()
{
    root = nullptr;
}

template <class ElemType>
BinTree<ElemType>::~BinTree()
{
    DestroyHelp(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::GetRoot() const
{
    return root;
}

template <class ElemType>
bool BinTree<ElemType>::Empty() const
{
    return root == nullptr;
}

template <class ElemType>
bool BinTree<ElemType>::GetElem(const BinTreeNode<ElemType> *cur, ElemType &e) const
{
    if (cur == nullptr)
    {
        return false;
    }
    else
    {
        e = cur->data;
        return true;
    }
}

template <class ElemType>
bool BinTree<ElemType>::SetElem(const BinTreeNode<ElemType> *cur, ElemType &e)
{
    if (cur == nullptr)
    {
        return false;
    }
    else
    {
        cur->data = e;
        return true;
    }
}

template <class ElemType>
void BinTree<ElemType>::PreOrder() const
{
    PreOrderHelp(root);
}

template <class ElemType>
void BinTree<ElemType>::InOrder() const
{
    InOrderHelp(root);
}

template <class ElemType>
void BinTree<ElemType>::PostOrder() const
{
    PostOrderHelp(root);
}

//TODO
template <class Elemtype>
void BinTree<Elemtype>::LevelOrder() const //unsure
//层次遍历
{
}

template <class ElemType>
int BinTree<ElemType>::NodeCount() const
{
    return NodeCountHelp(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::CopyTreeHelp(const BinTreeNode<ElemType> *r) //unsure
//操作结果：将以r为根的二叉树复制成新的二叉树，并返回新二叉树的根
{
    if (r == nullptr)
    {
        return nullptr;
    }
    else
    {
        root = r;
        root->leftChild = CopyTreeHelp(r->leftChild);
        root->rightChild = CopyTreeHelp(r->rightChild);
        return r;
    }
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::LeftChild(const BinTreeNode<ElemType> *cur) const //unsure
{
    return cur->leftChild;
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::RightChild(const BinTreeNode<ElemType> *cur) const //unsure
{
    return cur->rightChild;
}

//TODO
template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::Parent(const BinTreeNode<ElemType> *cur) const
{
    return ParentHelp(cur);
}

template <class ElemType>
void BinTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e) //unsure
{
    cur->leftChild = new BinTreeNode<ElemType>(e);
}

template <class ElemType>
void BinTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e) //unsure
{
    cur->rightChild = new BinTreeNode<ElemType>(e);
}

template <class ElemType>
void BinTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType> *cur) //unsure
{
    DestroyHelp(cur->leftChild);
}

template <class ElemType>
void BinTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType> *cur) //unsure
{
    DestroyHelp(cur->rightChild);
}

template <class ElemType>
int BinTree<ElemType>::Height() const
{
    return HeightHelp(root);
}

template <class ElemType>
int BinTree<ElemType>::LeavesCount() const //计算叶子结点
{
    return LeavesCountHelp(root);
}

template <class ElemType>
BinTree<ElemType>::BinTree(const ElemType &e) //unsure
{
    root = new BinTreeNode<ElemType>(e);
}

//TODO
template <class ElemType>
BinTree<ElemType>::BinTree(const BinTree<ElemType> &copy) //unsure
{
}

template <class ElemType>
BinTree<ElemType>::BinTree(BinTreeNode<ElemType> *r) //unsure
{
    CopyTreeHelp(r);
}

//TODO
template <class ElemType>
BinTree<ElemType> &BinTree<ElemType>::operator=(const BinTree<ElemType> &copy) //unsure
{
}

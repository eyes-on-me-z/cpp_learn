#include "Stack.h"


//初始化和销毁
void StackInit(Stack *pst)
{
    assert(pst);
    pst->_a = (STDataType*)malloc(sizeof(STDataType) * 4);
    pst->_top = 0;
    pst->_capacity = 4;

}
void StackDestory(Stack *pst)
{
    assert(pst);
    free(pst->_a);
    pst->_a = NULL;
    pst->_top = 0;
    pst->_capacity = 0;
}
//入栈
void StackPush(Stack *pst, STDataType x)
{
    assert(pst);
    //增容
    if (pst->_top == pst->_capacity)
    {
        pst->_capacity *= 2;
        STDataType *tmp = (STDataType*)realloc(pst->_a, sizeof(STDataType) * pst->_capacity);
        if (tmp == NULL)
        {
            exit(-1);
        }
        else
        {
            pst->_a = tmp;
        }
    }

    pst->_a[pst->_top] = x;
    pst->_top++;
}
//出栈
void StackPop(Stack *pst)
{
    assert(pst);
    assert(pst->_top > 0);
    pst->_top--;
}
//获取数据个数
int StackSize(Stack *pst)
{
    assert(pst);
    return pst->_top;
}
//返回1是空，0是非空
int StackEmpty(Stack *pst)
{
    assert(pst);
    return pst->_top == 0 ? 1 : 0;
}
//获取栈顶数据
STDataType StackTop(Stack *pst)
{
    assert(pst);
    assert(pst->_top > 0);
    return pst->_a[pst->_top - 1];
}
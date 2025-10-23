#pragma once
#include <iostream>
#include <assert.h>
#include <stdlib.h>

using namespace std;

typedef int STDataType;

typedef struct Stack
{
    STDataType *_a;
    int _top;
    int _capacity;
}Stack;

//初始化和销毁
void StackInit(Stack *pst);
void StackDestory(Stack *pst);
//入栈
void StackPush(Stack *pst, STDataType x);
//出栈
void StackPop(Stack *pst);
//获取数据个数
int StackSize(Stack *pst);
//返回1是空，0是非空
int StackEmpty(Stack *pst);
//获取栈顶数据
STDataType StackTop(Stack *pst);
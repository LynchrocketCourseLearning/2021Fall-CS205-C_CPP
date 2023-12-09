# 左值(`lvalue`)与纯右值(`prvalue`)

## `lvalue`

>简单的来说，能取地址的变量一定是左值，有名字的变量也一定是左值，最经典的`void fun(p&& shit)`，其中`shit`也是左值，因为右值引用是左值（所以才会有`move`，`forward`这些函数的产生，其中`move`出来一定是右值，`forward`保持变量形式和之前的不变，就是为了解决右值引用是左值的问题）。
>
>至于为什么不能把等号左边看成左值，因为在C++中，等号是可以运算符重载的，等号完全可以重载成为等号左边为右值的形式。
>
>函数名是左值.
>
>解引用操作符`*`同样返回左值.

## `prvalue`

> 纯右值是传统右值的一部分，纯右值是表达式产生的中间值，不能取地址。
>
> 左值可以隐式转换到右值, 反之不可.
>
> 取地址操作符`&`返回的是纯右值.

# 函数指针的赋值

函数指针的赋值有两种方式:

```cpp
void foo() {
    
}
void (*p1) = foo;
void (*p2) = &foo;	//p1和p2是等价的
```

1. 使用取址操作符`&`时:

   `&foo`返回了一个纯右值(`prvalue`)并直接赋值给`p1`

2. 不使用时:

   左值`foo`隐式转换成纯右值再赋值给`p1`

# 函数指针的调用

函数调用操作符`()`中指明函数的操作数可以是以下类型:

> 1. lvalue expression that refers to a function(一个指向函数的左值表达式)
> 2. pointer to function(一个指向函数的指针)

因此, 对上面的例子有以下三种调用方式:

```cpp
foo();
(*p1)();
p2();
```

其中第一种调用方法对应着上述第一种类型, 通过一个左值表达式(函数名)作为函数调用操作符的操作数; 第二种调用方法同样对应第一种类型, 因为解引用表达式`*p1`返回一个左值; 而第三种调用方法则对应第二种类型, 将函数指针作为操作数进行调用.

# 参考资料

1. [函数指针](https://en.cppreference.com/w/cpp/language/pointer)
2. [函数调用操作符](https://en.cppreference.com/w/cpp/language/operator_other)
3. [cppreference中的value部分](https://en.cppreference.com/w/cpp/language/value_category)
4. [一篇对左值和右值的理解](https://nettee.github.io/posts/2018/Understanding-lvalues-and-rvalues-in-C-and-C/)
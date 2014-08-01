local a = 10;

class CTest
{
    constructor()
    {
        print("class Ctor called!\n");
    }
    
    function AddAToA(otherA)
    {
        return otherA + m_a;
    }

    m_a = 20;
};

function foo(i, f, s)
{ 
    print("Called foo(), i=" + i + ", f=" + f + ", s='" + s + "'\n");
    
    local classtest = CTest();

    return callback_foo(classtest.AddAToA(a));
}
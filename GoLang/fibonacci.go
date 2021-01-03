package GoLang

// this example came from Algorithmswithgo.com

func Fibonacci(numb int) int{
    if numb <= 1{
        println(numb)
        return numb
    }
    
    numb2 := 0
    numb1 := 1
    var fibo int
    
    println(numb2)

    for i := 2; i <= numb; i++{
        fibo = numb1 + numb2
        numb2 = numb1
        numb1 = fibo
        println(numb1)
    }
    return fibo
}

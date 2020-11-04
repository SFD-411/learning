package GoLang

import(
    "fmt"
    "testing"
)

func TestFibonacci(t *testing.T){
    tests := []struct{
        numb int
        want int
    }{
        {0, 0},
        {1, 1},
        {2, 1},
        {3, 2},
        {4, 3},
        {6, 8},
        {7, 13},
        {14, 377},
        {22, 17711},
        {41, 165580141},
    }
    for _, tc := range tests{
        t.Run(fmt.Sprintf("numb=%v", tc.numb), func(t *testing.T){
            got := Fibonacci(tc.numb)
            if got != tc.want{
                t.Fatalf("Fibonacci() = %v, wanted %v", got, tc.want)
            }
        })
    }
}

package GoLang

import(
    "fmt"
    "testing"
)

func TestDec2Base(t *testing.T){
    tests := []struct{
        decimal, base int
        want string
    }{
        {1, 2, "1"},
        {2, 2, "10"},
        {3, 2, "11"},
        {4, 2, "100"},
        {8, 2, "1000"},
        {15, 2, "1111"},
        {100, 2, "1100100"},
        {100, 16, "64"},
        {4000, 2, "111110100000"},
        {4000, 16, "FA0"},
        {3735928559, 2, "11011110101011011011111011101111"},
        {3735928559, 16, "DEADBEEF"},
    }
    for _, tc := range tests{
        t.Run(fmt.Sprintf("%v to base %v", tc.decimal, tc.base), func(t *testing.T){
            got := Dec2Base(tc.decimal, tc.base)
            if got != tc.want{
                t.Fatalf("DecToBase() = %v; wanted %v", got, tc.want)
            } else {
                println(tc.decimal, "to base", tc.base, "equals", got)
            }
        })
    }
}

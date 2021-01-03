package GoLang

import(
    "fmt"
    "testing"
)

func TestReverse(t *testing.T){
    tests := []struct{
        word string
        want string
    }{
        {"cat", "tac"},
        {"hyperbole", "elobrepyh"},
        {"erehwon", "nowhere"},
        {"abcdefghijklmnopqrstuvwxyz", "zyxwvutsrqponmlkjihgfedcba"},
    }
    for _, tc := range tests{
        t.Run(fmt.Sprintf("%v", tc.word), func(t *testing.T){
            got := Reverse(tc.word)
            if got != tc.want{
                t.Fatalf("Reverse() = %v; want %v", got, tc.want)
            } else {
                println(tc.want, " is the reverse of ", tc.word)
            }
        })
    }
}

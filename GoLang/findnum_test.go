package GoLang

import(
    "fmt"
    "testing"
)

func TestFindNum(t *testing.T){
    tests :=[]struct{
        list []int
        numb int
        want bool
    }{
        {[]int{1, 2, 3, 4, 5}, 1, true},
        {[]int{1, 2, 3, 4, 5}, 2, true},
        {[]int{1, 2, 3, 4, 5}, 3, true},
        {[]int{1, 2, 3, 4, 5}, 4, true},
        {[]int{1, 2, 3, 4, 5}, 5, true},
        {[]int{1, 2, 3, 4, 5}, 0, false},
   		{[]int{-1, -1, -1, -1, -1, -1, -1, -1}, -1, true},
		{[]int{-1, -1, -1, -1, -1, -1, -1, -1}, 1, false},
    }
    for _, tc := range tests{
        t.Run(fmt.Sprintf("(%v,%v)", tc.list, tc.numb), func(t *testing.T){
            got := FindNum(tc.list, tc.numb)
            if got != tc.want {
                t.Fatalf("FindNum() =  %v, want %v", got, tc.want)
            }
        })
    }
}

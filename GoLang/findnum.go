package GoLang

// Example taken from Gophercises Num_In_List

func FindNum(list[]int, numb int) bool {
    for _, num := range list{
        if num == numb{
            return true
        }
    }
    return false
}

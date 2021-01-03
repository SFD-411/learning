package GoLang

func Reverse(word string) string{
    var tempStr string
    for i := len(word)-1; i >= 0; i--{
        tempStr = tempStr + string(word[i])
    }
    return tempStr
}

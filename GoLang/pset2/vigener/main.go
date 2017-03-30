package main

import (
	"fmt"
	"bufio"
	"os"
	"strings"
)

var (
	letterA = byte('A')
	letterZ = byte('Z')
	letterSmallA = byte('a')
	letterSmallZ = byte('z')
)

func getTextFromConsole() string {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Input text: ")
	input, _ := reader.ReadString('\n')
	return input
}

func getKeyFromConsole() string {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Input key: ")
	input, _ := reader.ReadString('\n')
	return input
}

func encryptText(text string, key string) (string){
	inArray := []byte(text)
	inKey := []byte(key)
	j:=0

	for i:=0;i<len(text);i++{
		if (isAlpha(inArray[i])){
			inArray[i]=cryptChar(inArray[i],inKey[j])
			if j+1 < len(key)-1 {
				j++
			} else {
				j =0
			}
		}
	}

	return string(inArray)
}

func cryptChar (char byte, key byte) byte{
	if (isUpper(char)) {
		char = ((char - letterA + (toUpper(key) - letterA)) % 26)+letterA-6
	} else {
		char = ((char - letterSmallA + (toUpper(key) - letterA)) % 26)+letterSmallA-6
	}
	return char
}

func isAlpha (char byte) (bool) {
	if (char>=letterA && char<=letterZ) ||
		(char>=letterSmallA && char<=letterSmallZ) {
		return true
	}
	return false
}

func isUpper (char byte) (bool){
	return char>=letterA && char<=letterZ
}

func toUpper (char byte) byte {
	str := string(char)
	strings.ToUpper(str)
	outByte := []byte(str)
	return outByte[0]
}

func printEncryptedText(text string) {
	fmt.Print("Encrypted text:")
	fmt.Print(text)
}

func main() {
	fmt.Println("This program encrypts text via Vigener algorythm: ")
	printEncryptedText(encryptText(getTextFromConsole(),getKeyFromConsole()))
	fmt.Print("")
}

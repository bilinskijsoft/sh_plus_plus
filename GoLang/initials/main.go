package main

import (
	"fmt"
	"regexp"
	"bufio"
	"os"
)

func getNameFromConsole() string {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Input name: ")
	input, _ := reader.ReadString('\n')
	return input
}

func getInitials(name string) string {
	re :=regexp.MustCompile("([a-z])|(\\s)")
	initials := re.ReplaceAllString(name,"")
	return initials
}

func printInitials(initials string) {
	fmt.Print("Your initials:")
	fmt.Print(initials)
}

func main() {

	printInitials(getInitials(getNameFromConsole()))
}

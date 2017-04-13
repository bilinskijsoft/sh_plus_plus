package main

import (
	"fmt"
	"regexp"
	"io/ioutil"
	"strings"
	"os"
	"strconv"
	"sync"
)

var (
	wordsInDictionary int = 0
	wordsInText int = 0
	misspells int = 0
)

func getFileNameToCheck() string {
	fileName := ""
	fmt.Print("Enter file name: ")
	fmt.Scanf("%s", &fileName)

	return fileName
}

func showResults(totalWords int, misspelledWords int, wordsInText int) {
	log("WORDS IN DICTIONARY: " + strconv.Itoa(totalWords))
	log("WORDS MISSPELLED: " + strconv.Itoa(misspelledWords))
	log("WORDS IN TEXT: " + strconv.Itoa(wordsInText))
}

func loadFile(fileName string) string {
	bs, err := ioutil.ReadFile(fileName)

	if err != nil {
		return ""
	}

	return string(bs)
}

func checkText(text string, dictionary string, wg *sync.WaitGroup) {
	log("Checking... Please wait...")
	wordsInDictionary = strings.Count(dictionary, "\n")
	ch := make(chan string,10)

	re := regexp.MustCompile("([a-zA-Z\\'])+")
	words := re.FindAllString(text, -1)

	go logMisspellings(ch)

	for _,value := range words {
		wordsInText++
		wg.Add(1)
		go checkWord(value, dictionary, ch, wg)
	}

}

func checkWord(word string, dictionary string, ch chan string, wg *sync.WaitGroup) {
	re := regexp.MustCompile(strings.ToLower(word + "\\n"))

	if re.MatchString(dictionary) == false {
		ch <- word
	}

	wg.Done()
}

func logMisspellings(ch chan string) {
	os.Remove("misspellings.txt")
	file, err := os.Create("misspellings.txt")

	if err != nil {
		// handle the error here
		return
	}

	defer file.Close()

	for {
		word := <- ch
		file.WriteString(word + "\n")
		misspells++
	}
}

func log(text string) {
	fmt.Println("[LOG]: ", text)
}

func main() {
	wg := sync.WaitGroup{}
	log("Misspellings will be writen to file 'misspellings.txt'")
	checkText(loadFile(getFileNameToCheck()),loadFile("large.txt"), &wg)

	wg.Wait()
	showResults(wordsInDictionary,misspells,wordsInText)
}

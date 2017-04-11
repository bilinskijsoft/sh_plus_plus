package main

import (
	"fmt"
	"crypto/sha1"
	"os"
	"log"
	"bufio"
	"container/list"
)

var (
	hashMap = make(map[string]string)
	wordsInDictionary int
	wordsInText int
	misspelledWords int
)

func getHash(s string) string {
	h := sha1.New()
	h.Write([]byte(s))
	bs := h.Sum([]byte{})
	return string(bs)
}

func isInDictionary(word string) bool {
	wordFromHash,_ := hashMap[getHash(word)]

	return wordFromHash = word
}

func loadDictionary(dictionary string, ch chan string){
	// Open file for reading
	file, err := os.Open(dictionary)
	if err != nil {
		log.Fatal(err)
		return
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		wordsInDictionary++
		hashMap[getHash(scanner.Text())] = scanner.Text()
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
		return
	}
	ch <-""
	return
}

func getFileNameToCheck() string {
	fileName := ""
	fmt.Print("Enter file name: ")
	fmt.Scanf("%s", &fileName)

	return fileName
}

func showResults(misspelledWordsArray *list.List, totalWords int, misspelledWords int, wordsInText int) {
	for e := misspelledWordsArray.Front(); e != nil; e = e.Next() {
		fmt.Println(e.Value)
	}
	fmt.Println("\nWORDS IN DICTIONARY: ", totalWords)
	fmt.Println("WORDS MISSPELLED: ", misspelledWords)
	fmt.Println("WORDS IN TEXT: ", wordsInText)
}

func loadFileForCheck(fileName string, wordsArray *list.List,ch chan string) {
	<-ch
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
		return
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanWords)

	for scanner.Scan() {
		wordsInText++
		if !isInDictionary(scanner.Text()) {
			misspelledWords++
			wordsArray.PushBack(scanner.Text())
		}
	}
	ch <- ""
}


func main() {
	var ch chan string = make(chan string)

	misspelledWordsArray := list.New()

	go loadDictionary("large.txt", ch)
	go loadFileForCheck(getFileNameToCheck(),misspelledWordsArray, ch)
	fmt.Println("Checking... Please wait.")
	<-ch
	showResults(misspelledWordsArray,wordsInDictionary,misspelledWords,wordsInText)
}
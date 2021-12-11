package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	data, _ := os.ReadFile("input.txt")

	var input []int
	for _, char := range strings.ReplaceAll(string(data), "\n", "") {
		input = append(input, int(char-'0'))
	}

	steps := 0
	totalflashes := 0
	for {
		steps++
		stepflashes := 0
		flashed := make(map[int]int)

		for i := range input {
			input[i] = input[i] + 1
		}

		for {
			didflash := false
			for i := range input {
				_, flash := flashed[i]
				if input[i] > 9 && !flash {
					flashed[i] = 1
					totalflashes++
					stepflashes++
					increaseEnergy(input, i)
					didflash = true
				}
			}
			if !didflash {
				break
			}
		}

		for x := range flashed {
			input[x] = 0
		}

		// Part 1
		if steps == 100 {
			fmt.Printf("Part 1: %v\n", totalflashes)
		}

		// Part 2
		if stepflashes == 100 {
			fmt.Printf("Part 2: %v\n", steps)
			break
		}
	}
}

func increaseEnergy(input []int, i int) {
	ix := i % 10
	iy := i / 10
	for y := iy - 1; y < iy+2; y++ {
		for x := ix - 1; x < ix+2; x++ {
			index := 10*y + x
			if index != i && x >= 0 && x < 10 && y >= 0 && y < 10 {
				input[index] = input[index] + 1
			}
		}
	}
}

package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
)

func Printdm(dm []int) {
	str := ""
	for i := range len(dm) {
		if dm[i] == -1 {
			str += "."
		} else {
			str += strconv.Itoa(dm[i])
		}
	}
	fmt.Println(str)
}

func main() {
	// Load input from file
	disk_map_bytes, err := os.ReadFile("9_input.txt")
	if err != nil {
		log.Fatal(err)
	}
	disk_map_str := string(disk_map_bytes)
	// fmt.Println(disk_map_str)

	// Iterate over disk map to index and expand blocks
	index := 0
	empty_blocks := 0
	disk_map_int_expand := make([]int, 0)
	for i := range len(disk_map_str) {
		repeats, _ := strconv.Atoi(string(disk_map_str[i]))
		if i%2 == 0 {
			for _ = range repeats {
				disk_map_int_expand = append(disk_map_int_expand, index)
			}
			index++
		} else {
			for _ = range repeats {
				disk_map_int_expand = append(disk_map_int_expand, -1)
			}
			empty_blocks += repeats
		}
	}
	// Printdm(disk_map_int_expand)

	// Defragment by filling empty blocks
	defragmented_blocks := 0
	for i := len(disk_map_int_expand) - 1; i >= 0; i-- {
		element_a := disk_map_int_expand[i]
		if element_a != -1 {
			for j := range i {
				element_b := disk_map_int_expand[j]
				if element_b == -1 {
					disk_map_int_expand[j] = element_a
					disk_map_int_expand[i] = element_b
					defragmented_blocks++
					// Printdm(disk_map_int_expand)
					break
				}
			}
		}
		if defragmented_blocks == empty_blocks {
			break
		}
	}

	// Calculate checksum result
	checksum := 0
	for i := range len(disk_map_int_expand) {
		element := disk_map_int_expand[i]
		if element != -1 {
			checksum += i * element
		}
	}
	fmt.Println("Checksum value is", checksum)
}

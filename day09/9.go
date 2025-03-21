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
			for range repeats {
				disk_map_int_expand = append(disk_map_int_expand, index)
			}
			index++
		} else {
			for range repeats {
				disk_map_int_expand = append(disk_map_int_expand, -1)
			}
			empty_blocks += repeats
		}
	}
	// Printdm(disk_map_int_expand)

	// Defragment by filling empty blocks
	defragmented_blocks := 0
	block_size := 1
	for i := len(disk_map_int_expand) - 1; i >= 0; i -= block_size {
		block_size = 1
		element_a := disk_map_int_expand[i : i+1]
		index := element_a[0]
		if index != -1 {
			if block_defrag := false; block_defrag { // PART B - DEFRAG IN BLOCKS
				for i_min := i - 1; i_min >= 0; i_min-- {
					if disk_map_int_expand[i_min] == disk_map_int_expand[i] {
						element_a = disk_map_int_expand[i_min : i+1]
						block_size = len(element_a)
					}
				}
			}

			for j := range i {
				element_b := disk_map_int_expand[j : j+1]
				if element_b[0] == -1 {
					invalid_block := false
					element_b = disk_map_int_expand[j : j+block_size]
					for k := range block_size {
						jk := j + k
						if disk_map_int_expand[jk] != -1 {
							invalid_block = true
							break
						}
					}
					if invalid_block {
						continue
					}
					new_slice := make([]int, 0)
					new_slice = append(new_slice, disk_map_int_expand[:j]...)
					new_slice = append(new_slice, element_a...)
					new_slice = append(new_slice, disk_map_int_expand[j+block_size:i-block_size+1]...)
					new_slice = append(new_slice, element_b...)
					new_slice = append(new_slice, disk_map_int_expand[i+1:]...)
					disk_map_int_expand = new_slice

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

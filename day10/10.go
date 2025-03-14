package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

type pos struct {
    x int
    y int
}

type TopoMap [][]int

func (tm TopoMap) Start() ([]pos) {
    starts := make([]pos, 0)
    for x := range len(tm) {
        for y := range len(tm[0]) {
            if tm[x][y] == 0 {
                starts = append(starts, pos{x, y})
            }
        }
    }
    return starts
}

func (tm TopoMap) Walk(p pos) ([]pos) {
    current_pos_value := tm[p.x][p.y]
    if current_pos_value == 9 {
        return []pos{p}
    } else {
        final_pos_list := make([]pos ,0)
        if p.x+1 < len(tm) && tm[p.x+1][p.y] == current_pos_value+1 {
            final_pos_list = append(final_pos_list, tm.Walk(pos{p.x+1, p.y})...)
        }
        if p.x-1 >=0 && tm[p.x-1][p.y] == current_pos_value+1 {
            final_pos_list = append(final_pos_list, tm.Walk(pos{p.x-1, p.y})...)
        }
        if p.y+1 < len(tm[0]) && tm[p.x][p.y+1] == current_pos_value+1 {
            final_pos_list = append(final_pos_list, tm.Walk(pos{p.x, p.y+1})...)
        }
        if p.y-1 >=0 && tm[p.x][p.y-1] == current_pos_value+1 {
            final_pos_list = append(final_pos_list, tm.Walk(pos{p.x, p.y-1})...)
        }
        return final_pos_list
    }
}

func main() {
    // Initialise variables
    topographic_map := make(TopoMap, 0)
    trailhead_score := 0
    trailhead_rating := 0

    // Load input from file
    file, err := os.Open("10_input.txt")
    if err != nil {
        log.Fatal(err)
    }
    defer file.Close()
    scanner := bufio.NewScanner(file)
    line_num := 0
    for scanner.Scan() {
        topographic_map = append(topographic_map, make([]int, 0))
        for _, char := range scanner.Text() {
            height, _ := strconv.Atoi(string(char))
            topographic_map[line_num] = append(topographic_map[line_num], height)
        }
        line_num++
    }
    if err := scanner.Err(); err != nil {
        log.Fatal(err)
    }

    // Find trailheads
    starting_positions := topographic_map.Start()

    // Find path lengths per trailhead
    for _, pos := range starting_positions {
        // De-duplicate paths visiting same end point
        duplicate_path_list := topographic_map.Walk(pos)
        trailhead_rating += len(duplicate_path_list)  // PART B

        // Find number of unique final positions
        tmp_pos_map := make(map[int]map[int]bool)
        tmp_count := 0
        for _, pos2 := range duplicate_path_list {
            if tmp_pos_map[pos2.x] == nil {
                tmp_pos_map[pos2.x] = make(map[int]bool)
            }
            tmp_pos_map[pos2.x][pos2.y] = true
        }
        for _, submap := range tmp_pos_map {
            tmp_count += len(submap)
        }
        trailhead_score += tmp_count  // PART A
    }

    // Results
    fmt.Println("Total trailhead score:", trailhead_score)
    fmt.Println("Total trailhead rating:", trailhead_rating)
}

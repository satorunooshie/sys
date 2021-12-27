package main

import (
	"flag"
	"fmt"
	"os"
	"sort"
	"strings"

	"github.com/satorunooshie/sys/constants"
)

type option struct {
	a
	t
}

type a struct {
	*bool
}

type t struct {
	*bool
}

type normal struct{}

func (n *normal) run(fileInfos []os.FileInfo) {
	for _, v := range fileInfos {
		if strings.HasPrefix(v.Name(), ".") {
			continue
		}
		printFileName(v)
	}
}

func newOption() *option {
	return &option{
		a: a{bool: flag.Bool("a", false, "do not ignore entries starting with .")},
		t: t{bool: flag.Bool("t", false, "sort by time, newest first")},
	}
}

func (a *a) isA() bool {
	return a != nil && a.bool != nil && *a.bool
}

func (a *a) run(fileInfos []os.FileInfo) {
	for _, v := range fileInfos {
		printFileName(v)
	}
}

func (t *t) isT() bool {
	return t != nil && t.bool != nil && *t.bool
}

func (t *t) run(fileInfos []os.FileInfo) {
	sort.SliceStable(fileInfos, func(i, j int) bool {
		return fileInfos[i].ModTime().After(fileInfos[j].ModTime())
	})
	n := normal{}
	n.run(fileInfos)
}

func printFileName(v os.FileInfo) {
	if v.IsDir() {
		fmt.Print(constants.Red)
	}
	fmt.Println(v.Name())
	if v.IsDir() {
		fmt.Print(constants.Normal)
	}
}
